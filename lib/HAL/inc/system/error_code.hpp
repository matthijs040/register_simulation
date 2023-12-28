#pragma once

#include "error_values.hpp"

class error_category {
public:
  constexpr virtual const char *name() const noexcept = 0;
  constexpr virtual const char *message(int code) const noexcept = 0;
  ~error_category() = default;
};

class standard_category : public error_category {
public:
  constexpr virtual const char *name() const noexcept { return "standard"; }

  constexpr virtual const char *message(int code) const noexcept {
    switch (static_cast<ec::errc>(code)) {
    case ec::errc::success:
      return "success";
    case ec::errc::eperm:
      return "Operation not permitted";
    case ec::errc::enoent:
      return "No such file or directory";
    case ec::errc::esrch:
      return "No such process";
    case ec::errc::eintr:
      return "Interrupted system call";
    case ec::errc::eio:
      return "I/O error";
    case ec::errc::enxio:
      return "No such device or address";
    case ec::errc::e2big:
      return "Argument list too long";
    case ec::errc::enoexec:
      return "Exec format error";
    case ec::errc::ebadf:
      return "Bad file number";
    case ec::errc::echild:
      return "No child processes";
    case ec::errc::eagain:
      return "Try again";
    case ec::errc::enomem:
      return "Out of memory";
    case ec::errc::eacces:
      return "Permission denied";
    case ec::errc::efault:
      return "Bad address";
    case ec::errc::enotblk:
      return "Block device required";
    case ec::errc::ebusy:
      return "Device or resource busy";
    case ec::errc::eexist:
      return "File exists";
    case ec::errc::exdev:
      return "Cross-device link";
    case ec::errc::enodev:
      return "No such device";
    case ec::errc::enotdir:
      return "Not a directory";
    case ec::errc::eisdir:
      return "Is a directory";
    case ec::errc::einval:
      return "Invalid argument";
    case ec::errc::enfile:
      return "File table overflow";
    case ec::errc::emfile:
      return "Too many open files";
    case ec::errc::enotty:
      return "Not a typewriter";
    case ec::errc::etxtbsy:
      return "Text file busy";
    case ec::errc::efbig:
      return "File too large";
    case ec::errc::enospc:
      return "No space left on device";
    case ec::errc::espipe:
      return "Illegal seek";
    case ec::errc::erofs:
      return "Read-only file system";
    case ec::errc::emlink:
      return "Too many links";
    case ec::errc::epipe:
      return "Broken pipe";
    case ec::errc::edom:
      return "Math argument out of domain of func";
    case ec::errc::erange:
      return "Math result not representable";
    case ec::errc::edeadlk:
      return "Resource deadlock would occur";
    case ec::errc::enametoolong:
      return "File name too long";
    case ec::errc::enolck:
      return "No record locks available";
    case ec::errc::enosys:
      return "Function not implemented";
    case ec::errc::enotempty:
      return "Directory not empty";
    case ec::errc::eloop:
      return "Too many symbolic links encountered";
    case ec::errc::enomsg:
      return "No message of desired type";
    case ec::errc::eidrm:
      return "Identifier removed";
    case ec::errc::echrng:
      return "Channel number out of range";
    case ec::errc::el2nsync:
      return "Level 2 not synchronized";
    case ec::errc::el3hlt:
      return "Level 3 halted";
    case ec::errc::el3rst:
      return "Level 3 reset";
    case ec::errc::elnrng:
      return "Link number out of range";
    case ec::errc::eunatch:
      return "Protocol driver not attached";
    case ec::errc::enocsi:
      return "No CSI structure available";
    case ec::errc::el2hlt:
      return "Level 2 halted";
    case ec::errc::ebade:
      return "Invalid exchange";
    case ec::errc::ebadr:
      return "Invalid request descriptor";
    case ec::errc::exfull:
      return "Exchange full";
    case ec::errc::enoano:
      return "No anode";
    case ec::errc::ebadrqc:
      return "Invalid request code";
    case ec::errc::ebadslt:
      return "Invalid slot";
    case ec::errc::ebfont:
      return "Bad font file format";
    case ec::errc::enostr:
      return "Device not a stream";
    case ec::errc::enodata:
      return "No data available";
    case ec::errc::etime:
      return "Timer expired";
    case ec::errc::enosr:
      return "Out of streams resources";
    case ec::errc::enonet:
      return "Machine is not on the network";
    case ec::errc::enopkg:
      return "Package not installed";
    case ec::errc::eremote:
      return "Object is remote";
    case ec::errc::enolink:
      return "Link has been severed";
    case ec::errc::eadv:
      return "Advertise error";
    case ec::errc::esrmnt:
      return "Srmount error";
    case ec::errc::ecomm:
      return "Communication error on send";
    case ec::errc::eproto:
      return "Protocol error";
    case ec::errc::emultihop:
      return "Multihop attempted";
    case ec::errc::edotdot:
      return "RFS specific error";
    case ec::errc::ebadmsg:
      return "Not a data message";
    case ec::errc::eoverflow:
      return "Value too large for defined data type";
    case ec::errc::enotuniq:
      return "Name not unique on network";
    case ec::errc::ebadfd:
      return "File descriptor in bad state";
    case ec::errc::eremchg:
      return "Remote address changed";
    case ec::errc::elibacc:
      return "Can not access a needed shared library";
    case ec::errc::elibbad:
      return "Accessing a corrupted shared library";
    case ec::errc::elibscn:
      return "lib section in a.out corrupted";
    case ec::errc::elibmax:
      return "Attempting to link in too many shared libraries";
    case ec::errc::elibexec:
      return "Cannot exec a shared library directly";
    case ec::errc::eilseq:
      return "Illegal byte sequence";
    case ec::errc::erestart:
      return "Interrupted system call should be restarted";
    case ec::errc::estrpipe:
      return "Streams pipe error";
    case ec::errc::eusers:
      return "Too many users";
    case ec::errc::enotsock:
      return "Socket operation on non-socket";
    case ec::errc::edestaddrreq:
      return "Destination address required";
    case ec::errc::emsgsize:
      return "Message too long";
    case ec::errc::eprototype:
      return "Protocol wrong type for socket";
    case ec::errc::enoprotoopt:
      return "Protocol not available";
    case ec::errc::eprotonosupport:
      return "Protocol not supported";
    case ec::errc::esocktnosupport:
      return "Socket type not supported";
    case ec::errc::eopnotsupp:
      return "Operation not supported on transport endpoint";
    case ec::errc::epfnosupport:
      return "Protocol family not supported";
    case ec::errc::eafnosupport:
      return "Address family not supported by protocol";
    case ec::errc::eaddrinuse:
      return "Address already in use";
    case ec::errc::eaddrnotavail:
      return "Cannot assign requested address";
    case ec::errc::enetdown:
      return "Network is down";
    case ec::errc::enetunreach:
      return "Network is unreachable";
    case ec::errc::enetreset:
      return "Network dropped connection because of reset";
    case ec::errc::econnaborted:
      return "Software caused connection abort";
    case ec::errc::econnreset:
      return "Connection reset by peer";
    case ec::errc::enobufs:
      return "No buffer space available";
    case ec::errc::eisconn:
      return "Transport endpoint is already connected";
    case ec::errc::enotconn:
      return "Transport endpoint is not connected";
    case ec::errc::eshutdown:
      return "Cannot send after transport endpoint shutdown";
    case ec::errc::etoomanyrefs:
      return "Too many references: cannot splice";
    case ec::errc::etimedout:
      return "Connection timed out";
    case ec::errc::econnrefused:
      return "Connection refused";
    case ec::errc::ehostdown:
      return "Host is down";
    case ec::errc::ehostunreach:
      return "No route to host";
    case ec::errc::ealready:
      return "Operation already in progress";
    case ec::errc::einprogress:
      return "Operation now in progress";
    case ec::errc::estale:
      return "Stale NFS file handle";
    case ec::errc::euclean:
      return "Structure needs cleaning";
    case ec::errc::enotnam:
      return "Not a XENIX named type file";
    case ec::errc::enavail:
      return "No XENIX semaphores available";
    case ec::errc::eisnam:
      return "Is a named type file";
    case ec::errc::eremoteio:
      return "Remote I/O error";
    case ec::errc::edquot:
      return "Quota exceeded";
    case ec::errc::enomedium:
      return "No medium found";
    case ec::errc::emediumtype:
      return "Wrong medium type";
    case ec::errc::ecanceled:
      return "Operation Canceled";
    case ec::errc::enokey:
      return "Required key not available";
    case ec::errc::ekeyexpired:
      return "Key has expired";
    case ec::errc::ekeyrevoked:
      return "Key has been revoked";
    case ec::errc::ekeyrejected:
      return "Key was rejected by service";
    case ec::errc::eownerdead:
      return "Owner died";
    case ec::errc::enotrecoverable:
      return "State not recoverable";
    }
    return "Unknown";
  }

  static standard_category &get() noexcept {
    static standard_category instance;
    return instance;
  }
};

class error_code {
private:
  int code_;
  error_category &category;

public:
  constexpr error_code() noexcept
      : code_(std::to_underlying(ec::errc::success)),
        category(standard_category::get()) {}

  constexpr error_code(int set_code, error_category &cat)
      : code_(set_code), category(cat) {}

  constexpr error_code(const error_code &other)
      : code_(other.code_), category(other.category) {}

  template <typename errc> constexpr error_code(errc error) {
    error_code(make_error_code(error));
  }

  constexpr error_code &operator=(const error_code &other) {
    code_ = other.code_;
    category = other.category;
    return *this;
  };

  constexpr operator bool() const noexcept { return code_ != 0; }

  constexpr const char *message() const noexcept {
    return category.message(code_);
  }

  constexpr const char *name() const noexcept { return category.name(); }

  constexpr int code() const noexcept { return code_; }

  constexpr void clear() noexcept { *this = error_code(); }

  template <typename errc>
  static constexpr error_code make_error_code(errc error);
};

template <> error_code error_code::make_error_code<ec::errc>(ec::errc code) {
  return error_code(std::to_underlying(code), standard_category::get());
}