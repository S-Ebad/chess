#pragma once
#include <expected>
#include <format>
#include <memory>
#include <nanosvg.h>
#include <nanosvgrast.h>
#include <span>
#include <string>

// A simple NSVG wrapper in C++
namespace renderer {
using NSVGResult = std::expected<class NSVG, std::string>;

// Owns a parsed SVG image and frees it automatically.
class NSVG {
public:
  // Parses an SVG file. Returns the image, or an error message if the file
  // can't be parsed or has no size.
  static NSVGResult from_file(const std::string &path) {
    constexpr float SVG_DPI = 96.0f;
    auto nsvg = NSVG{nsvgParseFromFile(path.c_str(), "px", SVG_DPI)};

    if (!nsvg.m_image || nsvg->width <= 0 || nsvg->height <= 0) {
      return std::unexpected(std::format("Failed to load SVG: {}", path));
    }

    return nsvg;
  }

  // Draws the SVG into the RGBA pixel buffer `dst` (w x h), shifted by tx/ty and
  // resized by `scale`. `stride` is the number of bytes per row (normally w * 4).
  // Returns true on success, or false if the shared rasterizer couldn't be created.
  [[nodiscard("Check whether rasterization succeeded")]]
  bool rasterize(float tx, float ty, float scale, std::span<unsigned char> dst, int w, int h,
                 int stride) {
    auto *rasterizer = get_rasterizer();

    if (!rasterizer) {
      return false; // failed to rasterize
    }

    nsvgRasterize(rasterizer, m_image.get(), tx, ty, scale, dst.data(), w, h, stride);
    return true;
  }

  // Returns a read-only pointer to the underlying image, e.g. svg->width.
  const NSVGimage *operator->() const {
    return m_image.get();
  }

private:
  // Takes ownership of an image returned by nsvgParseFromFile (may be null).
  explicit constexpr NSVG(NSVGimage *image) : m_image{image, &nsvgDelete} {
  }

  // Returns the one rasterizer shared by every SVG, created on the first call and
  // freed when the program exits. Returns null if creation failed.
  [[nodiscard]]
  static NSVGrasterizer *get_rasterizer() {
    static auto rasterizer = std::unique_ptr<NSVGrasterizer, decltype(&nsvgDeleteRasterizer)>(
        nsvgCreateRasterizer(), &nsvgDeleteRasterizer);

    return rasterizer.get();
  }

  std::unique_ptr<NSVGimage, decltype(&nsvgDelete)> m_image;
};
} // namespace renderer
