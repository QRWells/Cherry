// Cherry.cpp: 定义应用程序的入口点。
//

#include "Cherry.h"

using namespace std;
using namespace cherry;
using namespace math;

int main() {
  // create camera
  auto camera =
      make_shared<PerspectiveCamera>(Vector3d{0, 0, -300}, Vector3d{0, 0, 0},
                                     Vector3d{0, 1, 0}, 60, 1, 5, 400);
  // create scene
  auto const kScene = make_shared<Scene>(camera);

  // create materials
  /*auto emitting = std::make_shared<DiffuseMaterial>(
      Vector3d(0.65), Vector3d(),
      8.0 * Vector3d(0.747 + 0.058, 0.747 + 0.258, 0.747) +
          15.6 * Vector3d(0.740 + 0.287, 0.740 + 0.160, 0.740) +
          18.4 * Vector3d(0.737 + 0.642, 0.737 + 0.159, 0.737));*/
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
  auto const back = make_shared<Cuboid>(Vector3d{-200, -200, 400},
                                        Vector3d{200, 200, 410}, white);
  auto const right = make_shared<Cuboid>(Vector3d{-210, -210, -1000},
                                         Vector3d{-200, 210, 400}, green2);
  auto const left = make_shared<Cuboid>(Vector3d{200, -210, -1000},
                                        Vector3d{210, 210, 400}, red2);
  auto const bottom = make_shared<Cuboid>(Vector3d{-200, -210, -1000},
                                          Vector3d{200, -200, 400}, white);
  auto const top = std::make_shared<Cuboid>(Point3{-200, 200, -1000},
                                            Point3{200, 210, 400}, white);
  auto const front = std::make_shared<Cuboid>(Vector3d{-200, -200, -310},
                                              Vector3d{200, 200, -300}, white);

  auto sp1 = make_shared<Sphere>(Vector3d{0, 150, 150}, 30, emitting);
  auto sp2 = make_shared<Sphere>(Vector3d{100, 70, 300}, 40, blue2);
  auto sp3 = make_shared<Sphere>(Vector3d{0, 50, 200}, 30, ref);
  auto sp4 = make_shared<Sphere>(Vector3d{-50, 0, 150}, 40, t);
  auto sp5 = make_shared<Sphere>(Vector3d{100, 0, 100}, 20, emitting);

  auto box = make_shared<Cuboid>(Vector3d{-150, -200, 100},
                                 Vector3d{-50, -100, 150}, white);

  // add objects to the scene
  kScene->Add(top);
  kScene->Add(bottom);
  kScene->Add(left);
  kScene->Add(back);
  kScene->Add(right);
  kScene->Add(front);
  kScene->Add(box);
  kScene->Add(sp1);
  kScene->Add(sp2);
  kScene->Add(sp3);
  kScene->Add(sp4);
  kScene->Add(sp5);

  auto const kItg = make_shared<PathIntegrator>();

  // create the ray tracer with the scene
  auto renderer = RayTracer(kScene, 480, 480, kItg);
  renderer.spp_ = 128;
  renderer.Render();
  renderer.SavePpm();

  std::cout << "Hello CMake." << endl;
  return 0;
}
