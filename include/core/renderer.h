#ifndef CHERRY_CORE_RENDERER
#define CHERRY_CORE_RENDERER

#include <memory>
#include <string>
#include <vector>

#include "core/scene.h"
#include "math/vector.h"


namespace cherry {
class Renderer {
 public:
  Renderer(std::shared_ptr<Scene> scene, const uint64_t& width,
           const uint64_t& height);

  virtual ~Renderer() = default;

  virtual void Render() = 0;
  void SavePpm(const std::string& file_name = "binary") const;

 protected:
  std::vector<math::Vector3d> frame_buffer;
  uint64_t width;
  uint64_t height;
  std::shared_ptr<Scene> scene;
};
}  // namespace cherry
#endif  // !CHERRY_CORE_RENDERER
