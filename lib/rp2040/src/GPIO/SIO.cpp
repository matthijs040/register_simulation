#include <rp2040/GPIO/SIO.hpp>

SIO::~SIO() {}

SIO::SIO() {}

void SIO::operator delete(void *addr) { static_cast<SIO *>(addr)->~SIO(); }

void *SIO::operator new(std::size_t size) {
  return USE_SIMULATED_REGISTERS
             ? simulated_peripheral<SIO>::operator new(size)
             : reinterpret_cast<SIO *>(base_address);
}