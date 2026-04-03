// Cherry.cpp: 定义应用程序的入口点。
//

#include "Cherry.h"

#include <CLI/CLI.hpp>

#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <utility>

#include "integrator/normal_integrator.h"

using namespace std;
using namespace cherry;
using namespace math;

namespace {
struct CliOptions {
  int width = 320;
  int height = 320;
  int spp = 128;
  string integrator = "path";
  string output = "binary";
  int threads = 0;
  string size;
};

auto StripPpmSuffix(string value) -> string {
  constexpr string_view kSuffix = ".ppm";
  if (value.size() >= kSuffix.size() &&
      value.compare(value.size() - kSuffix.size(), kSuffix.size(), kSuffix) ==
          0) {
    value.resize(value.size() - kSuffix.size());
  }
  return value;
}

auto ParseInt(string const& value, int& out) -> bool {
  if (value.empty()) return false;

  size_t idx = 0;
  long long v = 0;
  try {
    v = std::stoll(value, &idx, 10);
  } catch (...) {
    return false;
  }
  if (idx != value.size()) return false;
  if (v < std::numeric_limits<int>::min() ||
      v > std::numeric_limits<int>::max()) {
    return false;
  }

  out = static_cast<int>(v);
  return true;
}

auto ParseSizeWxH(string const& value, int& width, int& height) -> bool {
  auto const pos = value.find_first_of("xX");
  if (pos == string::npos) return false;

  auto const w_str = value.substr(0, pos);
  auto const h_str = value.substr(pos + 1);

  int w = 0;
  int h = 0;
  if (!ParseInt(w_str, w) || !ParseInt(h_str, h)) return false;
  if (w < 2 || h < 2) return false;

  width = w;
  height = h;
  return true;
}

auto MakeIntegrator(string const& name) -> shared_ptr<Integrator> {
  if (name == "normal") return make_shared<NormalIntegrator>();
  return make_shared<PathIntegrator>();
}

auto MakeDefaultScene(double aspect_ratio) -> shared_ptr<Scene> {
  // create camera
  auto camera =
      make_shared<PerspectiveCamera>(Vector3d{0, 0, -300}, Vector3d{0, 0, 0},
                                     Vector3d{0, 1, 0}, 60, aspect_ratio, 5,
                                     200);
  // create scene
  auto const kScene = make_shared<Scene>(camera);

  // create materials
  auto emitting = std::make_shared<DiffuseMaterial>(Vector3d(0.65), Vector3d(),
                                                    Vector3d(70, 65, 50));
  auto green2 =
      make_shared<MicrofacetMaterial>(Vector3d{0.14, 0.45, 0.091}, 0, 0);
  auto red = std::make_shared<DiffuseMaterial>(Vector3d{0.63, 0.065, 0.05});
  auto red2 =
      make_shared<MicrofacetMaterial>(Vector3d{0.63, 0.065, 0.05}, 0, 0);
  auto blue2 =
      make_shared<MicrofacetMaterial>(Vector3d{0.95, 0.96, 0.97}, 0.25);
  auto blue3 = make_shared<MicrofacetMaterial>(Vector3d{1, 0.86, 0.57}, 0.4);
  auto blue4 = make_shared<MicrofacetMaterial>(Vector3d{0.1, 0.23, 0.75}, 0.5);
  auto ref = make_shared<ReflectMaterial>(Vector3d(0.9), Vector3d(1, 0.8, 0.6));
  auto white = make_shared<DiffuseMaterial>(Point3{0.725, 0.71, 0.68});
  auto t = make_shared<DielectricMaterial>(Vector3d{1.0}, Vector3d{0.8}, 1.8);

  // create objects
  auto const kBack = make_shared<Cuboid>(Vector3d{-200, -200, 400},
                                         Vector3d{200, 200, 410}, white);
  auto const kRight = make_shared<Cuboid>(Vector3d{-210, -210, -1000},
                                          Vector3d{-200, 210, 400}, green2);
  auto const kLeft = make_shared<Cuboid>(Vector3d{200, -210, -1000},
                                         Vector3d{210, 210, 400}, red2);
  auto const kBottom = make_shared<Cuboid>(Vector3d{-200, -210, -1000},
                                           Vector3d{200, -200, 400}, white);
  auto const kTop = std::make_shared<Cuboid>(Point3{-200, 200, -1000},
                                             Point3{200, 210, 400}, white);
  auto const kFront = std::make_shared<Cuboid>(Vector3d{-200, -200, -310},
                                               Vector3d{200, 200, -300}, white);

  auto const kSp1 = make_shared<Sphere>(Vector3d{0, 150, 150}, 30, red2);
  auto const kSp2 = make_shared<Sphere>(Vector3d{100, 70, 300}, 40, blue2);
  auto const kSp3 = make_shared<Sphere>(Vector3d{0, 50, 200}, 30, ref);
  auto const kSp4 = make_shared<Sphere>(Vector3d{-50, 0, 150}, 40, t);
  auto const kSp5 = make_shared<Sphere>(Vector3d{100, 0, 100}, 20, green2);

  auto const kBox = make_shared<Cuboid>(Vector3d{-150, -200, 100},
                                        Vector3d{-50, -100, 150}, white);

  // add objects to the scene
  kScene->Add(kTop);
  kScene->Add(kBottom);
  kScene->Add(kLeft);
  kScene->Add(kBack);
  kScene->Add(kRight);
  kScene->Add(kFront);
  kScene->Add(kBox);
  kScene->Add(kSp1);
  kScene->Add(kSp2);
  kScene->Add(kSp3);
  kScene->Add(kSp4);
  kScene->Add(kSp5);

  return kScene;
}
}  // namespace

auto main(int argc, char** argv) -> int {
  CLI::App app{"Cherry - toy renderer"};
  app.set_help_flag("-h,--help", "Print this help message and exit");

  CliOptions opts{};

  app.add_option("--width", opts.width, "Image width")
      ->check(CLI::Range(2, std::numeric_limits<int>::max()));
  app.add_option("--height", opts.height, "Image height")
      ->check(CLI::Range(2, std::numeric_limits<int>::max()));
  app.add_option("--size", opts.size, "Image size as WxH, e.g. 800x600");
  app.add_option("--spp", opts.spp, "Samples per pixel")
      ->check(CLI::Range(1, std::numeric_limits<int>::max()));
  app.add_option("--integrator", opts.integrator, "Integrator: path|normal")
      ->check(CLI::IsMember({"path", "normal"}));
  app.add_option("-o,--output", opts.output,
                 "Output file base name/path (without .ppm)")
      ->capture_default_str();
  auto* threads_opt =
      app.add_option("--threads", opts.threads, "OpenMP thread count")
          ->check(CLI::Range(1, std::numeric_limits<int>::max()));

  try {
    app.parse(argc, argv);

    if (!opts.size.empty()) {
      if (!ParseSizeWxH(opts.size, opts.width, opts.height)) {
        throw CLI::ValidationError(
            "--size",
            "Expected WxH where W and H are integers >= 2 (e.g. 800x600)");
      }
    }

    opts.output = StripPpmSuffix(std::move(opts.output));
    if (opts.output.empty()) {
      throw CLI::ValidationError("--output", "Output must not be empty");
    }
  } catch (const CLI::ParseError& e) {
    int const rc = app.exit(e);
    return rc == 0 ? 0 : 2;
  }

  if (threads_opt->count() > 0) {
#if defined(_OPENMP)
    omp_set_num_threads(opts.threads);
#else
    cerr << "warning: --threads ignored (OpenMP not enabled)\n";
#endif
  }

  auto const width = static_cast<uint32_t>(opts.width);
  auto const height = static_cast<uint32_t>(opts.height);
  auto const aspect_ratio =
      static_cast<double>(width) / static_cast<double>(height);

  auto const scene = MakeDefaultScene(aspect_ratio);
  auto const integrator = MakeIntegrator(opts.integrator);

  auto renderer = RayTracer(scene, width, height, integrator,
                            static_cast<size_t>(opts.spp));
  renderer.Render();
  renderer.SavePpm(opts.output);

  return 0;
}
