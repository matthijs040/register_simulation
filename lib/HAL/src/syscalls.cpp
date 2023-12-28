#include <cinttypes>
#include <cstdint>
#include <sys/stat.h>

extern "C" __attribute__((__weak__)) void _exit (int code) {
  while (true) {
  }
}

extern "C" int getentropy(void *, std::size_t) { return 0; }

extern "C" long _close(int) { return 0; }

extern "C" long _lseek(int, off_t, int) { return 0; }

extern "C" long _read(int, char *, int) { return 0; }

extern "C" long _write(int, const char *, int) { return 0; }

extern "C" long _fstat(int, struct stat *) { return 0; }

extern "C" long _kill() { return 0; }

extern "C" long _getpid() { return 0; }

extern "C" unsigned char *_sbrk(int) { return 0; }

extern "C" unsigned char *_isatty() { return 0; }