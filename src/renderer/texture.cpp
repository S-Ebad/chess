#include "texture.hpp"
#include "renderer/nsvg.hpp"
#include <cmath>
#include <cstddef>
#include <expected>
#include <format>
#include <raylib.h>
#include <string>
#include <utility>
#include <vector>

namespace renderer {
TextureResult Texture::from_file(const std::string &path, int width) {
  NSVGResult result = NSVG::from_file(path);
  if (!result) {
    return std::unexpected(std::move(result.error()));
  }

  NSVG svg = std::move(*result);

  float scale = static_cast<float>(width) / svg->width;
  int height = static_cast<int>(std::ceil(svg->height * scale));

  std::vector<unsigned char> pixels(static_cast<std::size_t>(width * height * 4));

  auto success = svg.rasterize(0, 0, scale, pixels, width, height, width * 4);
  if (!success)
    return std::unexpected(std::format("Failed to rasterize SVG Image: {}", path));

  Image img{};
  img.data = pixels.data();
  img.width = width;
  img.height = height;
  img.mipmaps = 1;
  img.format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8;

  auto texture = LoadTextureFromImage(img);
  if (texture.id == 0) { // failed
    return std::unexpected(std::format("Failed to load texture: {}", path));
  }

  return renderer::Texture{texture};
}
} // namespace renderer
