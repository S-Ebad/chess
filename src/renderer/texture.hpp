#pragma once
#include <expected>
#include <raylib.h>
#include <string>
#include <utility>

namespace renderer {
class Texture;
using TextureResult = std::expected<Texture, std::string>;

class Texture {
public:
  constexpr Texture() : m_texture{} {
  }
  static TextureResult from_file(const std::string &path, int width);

  ~Texture() {
    if (m_texture.id != 0) {
      UnloadTexture(m_texture);
    }
  }

  // no copies
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  Texture(Texture &&other) noexcept : m_texture{std::exchange(other.m_texture, Texture2D{})} {
  }

  Texture &operator=(Texture &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    if (m_texture.id != 0) {
      UnloadTexture(m_texture);
    }

    m_texture = std::exchange(other.m_texture, Texture2D{});
    return *this;
  }

  Texture2D *operator->() {
    return &m_texture;
  }
  const Texture2D *operator->() const {
    return &m_texture;
  }

  Texture2D &operator*() {
    return m_texture;
  }
  const Texture2D &operator*() const {
    return m_texture;
  }

private:
  explicit Texture(Texture2D texture) : m_texture{texture} {
  }

  Texture2D m_texture;
};
} // namespace renderer
