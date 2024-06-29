#include <cinttypes>
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <sys/stat.h>

extern "C" __attribute__((__weak__)) void _exit(int code) {
  while (true) {
  }
}

extern "C" __attribute__((__weak__)) int _getentropy(void *, std::size_t) {
  return 0;
}

extern "C" __attribute__((__weak__)) long _close(int) { return 0; }

extern "C" __attribute__((__weak__)) long _lseek(int, off_t, int) { return 0; }

extern "C" __attribute__((__weak__)) long _read(int, char *, int) { return 0; }

extern "C" __attribute__((__weak__)) long _write(int, const char *, int) {
  return 0;
}

extern "C" __attribute__((__weak__)) long _fstat(int, struct stat *) {
  return 0;
}

extern "C" __attribute__((__weak__)) long _kill() { return 0; }

extern "C" __attribute__((__weak__)) long _getpid() { return 0; }

extern "C" __attribute__((__weak__)) unsigned char *_sbrk(int) { return 0; }

extern "C" __attribute__((__weak__)) unsigned char *_isatty() { return 0; }

extern "C" __attribute__((__weak__)) int __wrap_puts(const char *) { return 0; }

extern "C" __attribute__((__weak__)) int __wrap_printf(const char *format,
                                                       va_list) {
  return 0;
}

extern "C" __attribute__((__weak__)) int __wrap_vprintf(const char *, va_list) {
  return 0;
}

extern "C" __attribute__((__weak__)) int __wrap_vfprintf(FILE *, const char *,
                                                         va_list) {
  return 0;
}

extern "C" __attribute__((__weak__)) int __wrap_vsprintf(char *, const char *,
                                                         va_list) {
  return 0;
}

extern "C" __attribute__((__weak__)) int
__wrap_vsnprintf(char *, size_t, const char *, va_list) {
  return 0;
}

extern "C" __attribute__((__weak__)) float __wrap_remquo(float, float, int *) {
  return 0.0f;
}

extern "C" __attribute__((__weak__)) float __wrap_remquof(float, float, int *) {
  return 0.0f;
}

extern "C" __attribute__((__weak__)) int __wrap_putchar(char) {
  return 0;
}