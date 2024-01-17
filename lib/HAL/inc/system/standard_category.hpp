#pragma once

#include "error_category.hpp"
#include "error_values.hpp"

namespace error {

class standard_category : public error::category {
public:
  constexpr virtual const char *name() const noexcept { return "standard"; }

  constexpr virtual const char *message(int code) const noexcept {
    switch (static_cast<standard_value>(code)) {
    case standard_value::success:
      return "success";
    case standard_value::eperm:
      return "Operation not permitted";
    case standard_value::enoent:
      return "No such file or directory";
    case standard_value::esrch:
      return "No such process";
    case standard_value::eintr:
      return "Interrupted system call";
    case standard_value::eio:
      return "I/O error";
    case standard_value::enxio:
      return "No such device or address";
    case standard_value::e2big:
      return "Argument list too long";
    case standard_value::enoexec:
      return "Exec format error";
    case standard_value::ebadf:
      return "Bad file number";
    case standard_value::echild:
      return "No child processes";
    case standard_value::eagain:
      return "Try again";
    case standard_value::enomem:
      return "Out of memory";
    case standard_value::eacces:
      return "Permission denied";
    case standard_value::efault:
      return "Bad address";
    case standard_value::enotblk:
      return "Block device required";
    case standard_value::ebusy:
      return "Device or resource busy";
    case standard_value::eexist:
      return "File exists";
    case standard_value::exdev:
      return "Cross-device link";
    case standard_value::enodev:
      return "No such device";
    case standard_value::enotdir:
      return "Not a directory";
    case standard_value::eisdir:
      return "Is a directory";
    case standard_value::einval:
      return "Invalid argument";
    case standard_value::enfile:
      return "File table overflow";
    case standard_value::emfile:
      return "Too many open files";
    case standard_value::enotty:
      return "Not a typewriter";
    case standard_value::etxtbsy:
      return "Text file busy";
    case standard_value::efbig:
      return "File too large";
    case standard_value::enospc:
      return "No space left on device";
    case standard_value::espipe:
      return "Illegal seek";
    case standard_value::erofs:
      return "Read-only file system";
    case standard_value::emlink:
      return "Too many links";
    case standard_value::epipe:
      return "Broken pipe";
    case standard_value::edom:
      return "Math argument out of domain of func";
    case standard_value::erange:
      return "Math result not representable";
    case standard_value::edeadlk:
      return "Resource deadlock would occur";
    case standard_value::enametoolong:
      return "File name too long";
    case standard_value::enolck:
      return "No record locks available";
    case standard_value::enosys:
      return "Function not implemented";
    case standard_value::enotempty:
      return "Directory not empty";
    case standard_value::eloop:
      return "Too many symbolic links encountered";
    case standard_value::enomsg:
      return "No message of desired type";
    case standard_value::eidrm:
      return "Identifier removed";
    case standard_value::echrng:
      return "Channel number out of range";
    case standard_value::el2nsync:
      return "Level 2 not synchronized";
    case standard_value::el3hlt:
      return "Level 3 halted";
    case standard_value::el3rst:
      return "Level 3 reset";
    case standard_value::elnrng:
      return "Link number out of range";
    case standard_value::eunatch:
      return "Protocol driver not attached";
    case standard_value::enocsi:
      return "No CSI structure available";
    case standard_value::el2hlt:
      return "Level 2 halted";
    case standard_value::ebade:
      return "Invalid exchange";
    case standard_value::ebadr:
      return "Invalid request descriptor";
    case standard_value::exfull:
      return "Exchange full";
    case standard_value::enoano:
      return "No anode";
    case standard_value::ebadrqc:
      return "Invalid request code";
    case standard_value::ebadslt:
      return "Invalid slot";
    case standard_value::ebfont:
      return "Bad font file format";
    case standard_value::enostr:
      return "Device not a stream";
    case standard_value::enodata:
      return "No data available";
    case standard_value::etime:
      return "Timer expired";
    case standard_value::enosr:
      return "Out of streams resources";
    case standard_value::enonet:
      return "Machine is not on the network";
    case standard_value::enopkg:
      return "Package not installed";
    case standard_value::eremote:
      return "Object is remote";
    case standard_value::enolink:
      return "Link has been severed";
    case standard_value::eadv:
      return "Advertise error";
    case standard_value::esrmnt:
      return "Srmount error";
    case standard_value::ecomm:
      return "Communication error on send";
    case standard_value::eproto:
      return "Protocol error";
    case standard_value::emultihop:
      return "Multihop attempted";
    case standard_value::edotdot:
      return "RFS specific error";
    case standard_value::ebadmsg:
      return "Not a data message";
    case standard_value::eoverflow:
      return "Value too large for defined data type";
    case standard_value::enotuniq:
      return "Name not unique on network";
    case standard_value::ebadfd:
      return "File descriptor in bad state";
    case standard_value::eremchg:
      return "Remote address changed";
    case standard_value::elibacc:
      return "Can not access a needed shared library";
    case standard_value::elibbad:
      return "Accessing a corrupted shared library";
    case standard_value::elibscn:
      return "lib section in a.out corrupted";
    case standard_value::elibmax:
      return "Attempting to link in too many shared libraries";
    case standard_value::elibexec:
      return "Cannot exec a shared library directly";
    case standard_value::eilseq:
      return "Illegal byte sequence";
    case standard_value::erestart:
      return "Interrupted system call should be restarted";
    case standard_value::estrpipe:
      return "Streams pipe error";
    case standard_value::eusers:
      return "Too many users";
    case standard_value::enotsock:
      return "Socket operation on non-socket";
    case standard_value::edestaddrreq:
      return "Destination address required";
    case standard_value::emsgsize:
      return "Message too long";
    case standard_value::eprototype:
      return "Protocol wrong type for socket";
    case standard_value::enoprotoopt:
      return "Protocol not available";
    case standard_value::eprotonosupport:
      return "Protocol not supported";
    case standard_value::esocktnosupport:
      return "Socket type not supported";
    case standard_value::eopnotsupp:
      return "Operation not supported on transport endpoint";
    case standard_value::epfnosupport:
      return "Protocol family not supported";
    case standard_value::eafnosupport:
      return "Address family not supported by protocol";
    case standard_value::eaddrinuse:
      return "Address already in use";
    case standard_value::eaddrnotavail:
      return "Cannot assign requested address";
    case standard_value::enetdown:
      return "Network is down";
    case standard_value::enetunreach:
      return "Network is unreachable";
    case standard_value::enetreset:
      return "Network dropped connection because of reset";
    case standard_value::econnaborted:
      return "Software caused connection abort";
    case standard_value::econnreset:
      return "Connection reset by peer";
    case standard_value::enobufs:
      return "No buffer space available";
    case standard_value::eisconn:
      return "Transport endpoint is already connected";
    case standard_value::enotconn:
      return "Transport endpoint is not connected";
    case standard_value::eshutdown:
      return "Cannot send after transport endpoint shutdown";
    case standard_value::etoomanyrefs:
      return "Too many references: cannot splice";
    case standard_value::etimedout:
      return "Connection timed out";
    case standard_value::econnrefused:
      return "Connection refused";
    case standard_value::ehostdown:
      return "Host is down";
    case standard_value::ehostunreach:
      return "No route to host";
    case standard_value::ealready:
      return "Operation already in progress";
    case standard_value::einprogress:
      return "Operation now in progress";
    case standard_value::estale:
      return "Stale NFS file handle";
    case standard_value::euclean:
      return "Structure needs cleaning";
    case standard_value::enotnam:
      return "Not a XENIX named type file";
    case standard_value::enavail:
      return "No XENIX semaphores available";
    case standard_value::eisnam:
      return "Is a named type file";
    case standard_value::eremoteio:
      return "Remote I/O error";
    case standard_value::edquot:
      return "Quota exceeded";
    case standard_value::enomedium:
      return "No medium found";
    case standard_value::emediumtype:
      return "Wrong medium type";
    case standard_value::ecanceled:
      return "Operation Canceled";
    case standard_value::enokey:
      return "Required key not available";
    case standard_value::ekeyexpired:
      return "Key has expired";
    case standard_value::ekeyrevoked:
      return "Key has been revoked";
    case standard_value::ekeyrejected:
      return "Key was rejected by service";
    case standard_value::eownerdead:
      return "Owner died";
    case standard_value::enotrecoverable:
      return "State not recoverable";
    }
    return "Unknown";
  }

  static standard_category &get() noexcept {
    static standard_category instance;
    return instance;
  }
};
} // namespace error
