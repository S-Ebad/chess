#pragma once
#include <expected>
#include <nanosvgrast.h>
#include <raylib.h>
#include <string>
#include <utility>

namespace renderer {
class Texture;
using TextureResult = std::expected<Texture, std::string>;

class Texture {
public:
  static TextureResult from_file(const std::string &path, int width);

  ~Texture() {
    if (m_texture.id != 0)
      UnloadTexture(m_texture);
  }

  // no copies
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;
  Texture &operator=(Texture &&other) = delete;

  Texture(Texture &&other) noexcept : m_texture{std::exchange(other.m_texture, Texture2D{})} {
  }

private:
  Texture(Texture2D texture) : m_texture{texture} {
  }

  Texture2D m_texture;
};
} // namespace renderer
