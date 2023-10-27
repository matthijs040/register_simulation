#pragma once

namespace arch {

enum class architectures {
  x86,
  x86_64,
  ARM2,
  ARM3,
  ARM4T,
  ARM5,
  ARM6,
  ARM6T2,
  ARM7,
  ARM7A,
  ARM7R,
  ARM7M,
  ARM7S,
  ARM64,
  MIPS,
  SUPERH,
  POWERPC,
  POWERPC64,
  SPARC,
  M68K,
  unknown
};

// Adapted from:
// https://stackoverflow.com/questions/152016/detecting-cpu-architecture-compile-time
consteval architectures get_architecture() {
#if defined(__x86_64__) || defined(_M_X64)
  return architectures::x86_64;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
  return architectures::x86;
#elif defined(__ARM_ARCH_2__)
  return architectures::ARM2;
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
  return architectures::ARM3;
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
  return architectures::ARM4T;
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
  return architectures::ARM5;
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
  return architectures::ARM6T2;
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) ||                   \
    defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) ||                    \
    defined(__ARM_ARCH_6ZK__)
  return architectures::ARM6;
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) ||                   \
    defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) ||                    \
    defined(__ARM_ARCH_7S__)
  return architectures::ARM7;
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) ||                  \
    defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return architectures::ARM7A;
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) ||                  \
    defined(__ARM_ARCH_7S__)
  return architectures::ARM7R;
#elif defined(__ARM_ARCH_7M__)
  return architectures::ARM7M;
#elif defined(__ARM_ARCH_7S__)
  return architectures::ARM7S;
#elif defined(__aarch64__) || defined(_M_ARM64)
  return architectures::ARM64;
#elif defined(mips) || defined(__mips__) || defined(__mips)
  return architectures::MIPS;
#elif defined(__sh__)
  return architectures::SUPERH;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) ||  \
    defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) ||            \
    defined(_ARCH_PPC)
  return architectures::POWERPC;
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
  return architectures::POWERPC64;
#elif defined(__sparc__) || defined(__sparc)
  return architectures::SPARC;
#elif defined(__m68k__)
  return architectures::M68K;
#else
  return architectures::unknown;
#endif
}
} // namespace arch
