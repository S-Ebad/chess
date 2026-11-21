#pragma once
#include <expected>
#include <raylib.h>
#include <string>
#include <utility>

namespace renderer {
class Texture;
using TextureResult = std::expected<Texture, std::string>;

// Owns a raylib GPU texture and unloads it automatically. Move-only.
class Texture {
public:
  // Creates an empty texture (id 0) that owns nothing.
  constexpr Texture() : m_texture{} {
  }

  // Loads an SVG file as a texture `width` pixels wide; the height keeps the
  // image's aspect ratio. Returns the texture, or an error message if any step fails.
  static TextureResult from_file(const std::string &path, int width);

  // Unloads the texture from the GPU, if this object holds one.
  ~Texture() {
    if (m_texture.id != 0) {
      UnloadTexture(m_texture);
    }
  }

  // no copies
  Texture(const Texture &) = delete;
  Texture &operator=(const Texture &) = delete;

  // Takes over `other`'s texture and leaves `other` empty.
  Texture(Texture &&other) noexcept : m_texture{std::exchange(other.m_texture, Texture2D{})} {
  }

  // Unloads the current texture (if any), takes over `other`'s, and leaves `other` empty.
  // Returns *this.
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

  // Returns a pointer to the raw raylib texture, e.g. texture->width.
  Texture2D *operator->() {
    return &m_texture;
  }
  const Texture2D *operator->() const {
    return &m_texture;
  }

  // Returns a reference to the raw raylib texture, e.g. DrawTexture(*texture, ...).
  Texture2D &operator*() {
    return m_texture;
  }
  const Texture2D &operator*() const {
    return m_texture;
  }

private:
  // Takes ownership of an already-loaded raylib texture.
  explicit Texture(Texture2D texture) : m_texture{texture} {
  }

  Texture2D m_texture;
};
} // namespace renderer
