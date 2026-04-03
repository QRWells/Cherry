# Cherry (C++) Agent Notes

This repo is a small toy renderer written in C++. `Cherry` builds as a single binary and currently renders to a binary PPM (`P6`) file.

## Quick Start (CMake + vcpkg)

Cherry is set up for vcpkg manifest mode and uses a vendored `vcpkg/` directory.

Configure:
```bash
cmake --preset Clang-Debug
# or: cmake --preset Clang-Release
```

Build:
```bash
cmake --build --preset Debug
# or: cmake --build --preset Release
```

Run:
```bash
./out/build/Clang-Debug/src/Cherry --help
./out/build/Clang-Debug/src/Cherry --size 64x64 --spp 1 -o out.ppm
```

Notes:
- Presets live in `CMakePresets.json`.
- The vcpkg toolchain is wired through the presets (`vcpkg/scripts/buildsystems/vcpkg.cmake`).
- If you add new `.cc` files, you must list them in `src/CMakeLists.txt` (this target is not globbed).

## Quick Start (xmake)

There is also an xmake build (`xmake.lua` and `src/xmake.lua`). It uses xmake packages for dependencies (including `cli11`).

```bash
xmake
xmake run Cherry -- --help
```

## Code Layout

- `src/Cherry.cc`: Program entrypoint. CLI-based renderer runner (CLI11).
- `include/` and `src/` mirror module structure:
  - `core/`: camera, scene, renderer base class, ray tracer, rasterizer (mostly stub).
  - `integrator/`: `PathIntegrator`, `NormalIntegrator`.
  - `material/`, `light/`, `object/`, `acceleration/` (BVH), `math/`, `utility/`.
- `utility/render_script/`: JSON render-script parsing into `RenderData` (factories are TODO/incomplete).

## CLI Behavior (Current)

The `Cherry` binary supports:
- `--width`, `--height`, `--size WxH`
- `--spp`
- `--integrator path|normal`
- `-o, --output <name-or-path>`: `SavePpm()` appends `.ppm`; passing `foo.ppm` is accepted.
- `--threads`: sets OpenMP thread count when OpenMP is enabled

For quick local sanity checks, prefer tiny renders:
```bash
./Cherry --size 16x16 --spp 1 -o /tmp/cherry_smoke.ppm
```

## Formatting / Lint

- `.clang-format` is based on Google style.
- `.clang-tidy` is strict (`WarningsAsErrors: "*"`) and includes many check groups.

Practical guidance:
- Keep changes small and localized.
- When touching headers, make sure they compile cleanly across translation units (avoid adding heavy includes to commonly used headers unless necessary).

## Dependencies

Managed via vcpkg manifest (`vcpkg.json`) and linked in `src/CMakeLists.txt`.

Current notable deps:
- `fmt`
- `nlohmann-json`
- `magic-enum`
- `cli11`
- OpenMP (optional; used by `RayTracer`)

When adding a dependency, update:
- `vcpkg.json` (manifest)
- `src/CMakeLists.txt` (find_package + target_link_libraries)
- `src/xmake.lua` (add_requires/add_packages), if keeping xmake working

