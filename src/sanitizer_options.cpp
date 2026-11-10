extern "C" {
// Sanitizer runtimes read these hooks at startup. Unused (and harmless) in
// non-sanitized builds. Environment variables still override them.
//
// The runtime looks these up by exact name, so they must keep their reserved
// names and external linkage.
// NOLINTBEGIN(misc-use-internal-linkage,bugprone-reserved-identifier,readability-identifier-naming)

const char *__asan_default_options(void);
const char *__lsan_default_options(void);
const char *__lsan_default_suppressions(void);

// The GPU driver is unloaded before the leak check runs, so its frames show up
// as <unknown module>. Full unwinding reaches the still-loaded frames
// (libGLX, libgallium, ...) that the suppressions below can match. It makes
// malloc slower, which only matters in Debug.
const char *__asan_default_options(void) {
  return "fast_unwind_on_malloc=0";
}

// Don't print the "Suppressions used" table after every run.
const char *__lsan_default_options(void) {
  return "print_suppressions=0";
}

// The GPU/X11 driver stack allocates process-lifetime state it never frees.
// Suppress it so real leaks in our code still get reported.
const char *__lsan_default_suppressions(void) {
  return "leak:libGL\n"
         "leak:libEGL\n"
         "leak:_dri.so\n"
         "leak:libgallium\n"
         "leak:libLLVM\n"
         "leak:libdrm\n"
         "leak:libX11\n"
         "leak:libxcb\n"
         "leak:libdbus\n"
         "leak:ld-linux\n";
}
// NOLINTEND(misc-use-internal-linkage,bugprone-reserved-identifier,readability-identifier-naming)
}
