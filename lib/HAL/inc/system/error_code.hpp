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
    switch (code) {
    case 0:
      return "success";
    case ec::EPERM_:
      return "Operation not permitted";
    case ec::ENOENT_:
      return "No such file or directory";
    case ec::ESRCH_:
      return "No such process";
    case ec::EINTR_:
      return "Interrupted system call";
    case ec::EIO_:
      return "I/O error";
    case ec::ENXIO_:
      return "No such device or address";
    case ec::E2BIG_:
      return "Argument list too long";
    case ec::ENOEXEC_:
      return "Exec format error";
    case ec::EBADF_:
      return "Bad file number";
    case ec::ECHILD_:
      return "No child processes";
    case ec::EAGAIN_:
      return "Try again";
    case ec::ENOMEM_:
      return "Out of memory";
    case ec::EACCES_:
      return "Permission denied";
    case ec::EFAULT_:
      return "Bad address";
    case ec::ENOTBLK_:
      return "Block device required";
    case ec::EBUSY_:
      return "Device or resource busy";
    case ec::EEXIST_:
      return "File exists";
    case ec::EXDEV_:
      return "Cross-device link";
    case ec::ENODEV_:
      return "No such device";
    case ec::ENOTDIR_:
      return "Not a directory";
    case ec::EISDIR_:
      return "Is a directory";
    case ec::EINVAL_:
      return "Invalid argument";
    case ec::ENFILE_:
      return "File table overflow";
    case ec::EMFILE_:
      return "Too many open files";
    case ec::ENOTTY_:
      return "Not a typewriter";
    case ec::ETXTBSY_:
      return "Text file busy";
    case ec::EFBIG_:
      return "File too large";
    case ec::ENOSPC_:
      return "No space left on device";
    case ec::ESPIPE_:
      return "Illegal seek";
    case ec::EROFS_:
      return "Read-only file system";
    case ec::EMLINK_:
      return "Too many links";
    case ec::EPIPE_:
      return "Broken pipe";
    case ec::EDOM_:
      return "Math argument out of domain of func";
    case ec::ERANGE_:
      return "Math result not representable";
    case ec::EDEADLK_:
      return "Resource deadlock would occur";
    case ec::ENAMETOOLONG_:
      return "File name too long";
    case ec::ENOLCK_:
      return "No record locks available";
    case ec::ENOSYS_:
      return "Function not implemented";
    case ec::ENOTEMPTY_:
      return "Directory not empty";
    case ec::ELOOP_:
      return "Too many symbolic links encountered";
    case ec::ENOMSG_:
      return "No message of desired type";
    case ec::EIDRM_:
      return "Identifier removed";
    case ec::ECHRNG_:
      return "Channel number out of range";
    case ec::EL2NSYNC_:
      return "Level 2 not synchronized";
    case ec::EL3HLT_:
      return "Level 3 halted";
    case ec::EL3RST_:
      return "Level 3 reset";
    case ec::ELNRNG_:
      return "Link number out of range";
    case ec::EUNATCH_:
      return "Protocol driver not attached";
    case ec::ENOCSI_:
      return "No CSI structure available";
    case ec::EL2HLT_:
      return "Level 2 halted";
    case ec::EBADE_:
      return "Invalid exchange";
    case ec::EBADR_:
      return "Invalid request descriptor";
    case ec::EXFULL_:
      return "Exchange full";
    case ec::ENOANO_:
      return "No anode";
    case ec::EBADRQC_:
      return "Invalid request code";
    case ec::EBADSLT_:
      return "Invalid slot";
    case ec::EBFONT_:
      return "Bad font file format";
    case ec::ENOSTR_:
      return "Device not a stream";
    case ec::ENODATA_:
      return "No data available";
    case ec::ETIME_:
      return "Timer expired";
    case ec::ENOSR_:
      return "Out of streams resources";
    case ec::ENONET_:
      return "Machine is not on the network";
    case ec::ENOPKG_:
      return "Package not installed";
    case ec::EREMOTE_:
      return "Object is remote";
    case ec::ENOLINK_:
      return "Link has been severed";
    case ec::EADV_:
      return "Advertise error";
    case ec::ESRMNT_:
      return "Srmount error";
    case ec::ECOMM_:
      return "Communication error on send";
    case ec::EPROTO_:
      return "Protocol error";
    case ec::EMULTIHOP_:
      return "Multihop attempted";
    case ec::EDOTDOT_:
      return "RFS specific error";
    case ec::EBADMSG_:
      return "Not a data message";
    case ec::EOVERFLOW_:
      return "Value too large for defined data type";
    case ec::ENOTUNIQ_:
      return "Name not unique on network";
    case ec::EBADFD_:
      return "File descriptor in bad state";
    case ec::EREMCHG_:
      return "Remote address changed";
    case ec::ELIBACC_:
      return "Can not access a needed shared library";
    case ec::ELIBBAD_:
      return "Accessing a corrupted shared library";
    case ec::ELIBSCN_:
      return "lib section in a.out corrupted";
    case ec::ELIBMAX_:
      return "Attempting to link in too many shared libraries";
    case ec::ELIBEXEC_:
      return "Cannot exec a shared library directly";
    case ec::EILSEQ_:
      return "Illegal byte sequence";
    case ec::ERESTART_:
      return "Interrupted system call should be restarted";
    case ec::ESTRPIPE_:
      return "Streams pipe error";
    case ec::EUSERS_:
      return "Too many users";
    case ec::ENOTSOCK_:
      return "Socket operation on non-socket";
    case ec::EDESTADDRREQ_:
      return "Destination address required";
    case ec::EMSGSIZE_:
      return "Message too long";
    case ec::EPROTOTYPE_:
      return "Protocol wrong type for socket";
    case ec::ENOPROTOOPT_:
      return "Protocol not available";
    case ec::EPROTONOSUPPORT_:
      return "Protocol not supported";
    case ec::ESOCKTNOSUPPORT_:
      return "Socket type not supported";
    case ec::EOPNOTSUPP_:
      return "Operation not supported on transport endpoint";
    case ec::EPFNOSUPPORT_:
      return "Protocol family not supported";
    case ec::EAFNOSUPPORT_:
      return "Address family not supported by protocol";
    case ec::EADDRINUSE_:
      return "Address already in use";
    case ec::EADDRNOTAVAIL_:
      return "Cannot assign requested address";
    case ec::ENETDOWN_:
      return "Network is down";
    case ec::ENETUNREACH_:
      return "Network is unreachable";
    case ec::ENETRESET_:
      return "Network dropped connection because of reset";
    case ec::ECONNABORTED_:
      return "Software caused connection abort";
    case ec::ECONNRESET_:
      return "Connection reset by peer";
    case ec::ENOBUFS_:
      return "No buffer space available";
    case ec::EISCONN_:
      return "Transport endpoint is already connected";
    case ec::ENOTCONN_:
      return "Transport endpoint is not connected";
    case ec::ESHUTDOWN_:
      return "Cannot send after transport endpoint shutdown";
    case ec::ETOOMANYREFS_:
      return "Too many references: cannot splice";
    case ec::ETIMEDOUT_:
      return "Connection timed out";
    case ec::ECONNREFUSED_:
      return "Connection refused";
    case ec::EHOSTDOWN_:
      return "Host is down";
    case ec::EHOSTUNREACH_:
      return "No route to host";
    case ec::EALREADY_:
      return "Operation already in progress";
    case ec::EINPROGRESS_:
      return "Operation now in progress";
    case ec::ESTALE_:
      return "Stale NFS file handle";
    case ec::EUCLEAN_:
      return "Structure needs cleaning";
    case ec::ENOTNAM_:
      return "Not a XENIX named type file";
    case ec::ENAVAIL_:
      return "No XENIX semaphores available";
    case ec::EISNAM_:
      return "Is a named type file";
    case ec::EREMOTEIO_:
      return "Remote I/O error";
    case ec::EDQUOT_:
      return "Quota exceeded";
    case ec::ENOMEDIUM_:
      return "No medium found";
    case ec::EMEDIUMTYPE_:
      return "Wrong medium type";
    case ec::ECANCELED_:
      return "Operation Canceled";
    case ec::ENOKEY_:
      return "Required key not available";
    case ec::EKEYEXPIRED_:
      return "Key has expired";
    case ec::EKEYREVOKED_:
      return "Key has been revoked";
    case ec::EKEYREJECTED_:
      return "Key was rejected by service";
    case ec::EOWNERDEAD_:
      return "Owner died";
    case ec::ENOTRECOVERABLE_:
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
      : code_(ec::success_), category(standard_category::get()) {}

  constexpr error_code(int set_code, error_category &cat)
      : code_(set_code), category(cat) {}

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
};
