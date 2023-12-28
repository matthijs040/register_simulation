#pragma once
namespace ec {

constexpr int success_ = 0;
// 	 	Operation not permitted
constexpr int EPERM_ = 1;
// 	 	No such file or directory
constexpr int ENOENT_ = 2;
// 	 	No such process
constexpr int ESRCH_ = 3;
// 	 	Interrupted system call
constexpr int EINTR_ = 4;
// 	 	I/O error
constexpr int EIO_ = 5;
// 	 	No such device or address
constexpr int ENXIO_ = 6;
// 	 	Argument list too long
constexpr int E2BIG_ = 7;
// 	 	Exec format error
constexpr int ENOEXEC_ = 8;
// 	 	Bad file number
constexpr int EBADF_ = 9;
// 	 	No child processes
constexpr int ECHILD_ = 10;
// 	 	Try again
constexpr int EAGAIN_ = 11;
// 	 	Out of memory
constexpr int ENOMEM_ = 12;
// 	 	Permission denied
constexpr int EACCES_ = 13;
// 	 	Bad address
constexpr int EFAULT_ = 14;
// 	 	Block device required
constexpr int ENOTBLK_ = 15;
// 	 	Device or resource busy
constexpr int EBUSY_ = 16;
// 	 	File exists
constexpr int EEXIST_ = 17;
// 	 	Cross-device link
constexpr int EXDEV_ = 18;
// 	 	No such device
constexpr int ENODEV_ = 19;
// 	 	Not a directory
constexpr int ENOTDIR_ = 20;
// 	 	Is a directory
constexpr int EISDIR_ = 21;
// 	 	Invalid argument
constexpr int EINVAL_ = 22;
// 	 	File table overflow
constexpr int ENFILE_ = 23;
// 	 	Too many open files
constexpr int EMFILE_ = 24;
// 	 	Not a typewriter
constexpr int ENOTTY_ = 25;
// 	 	Text file busy
constexpr int ETXTBSY_ = 26;
// 	 	File too large
constexpr int EFBIG_ = 27;
// 	 	No space left on device
constexpr int ENOSPC_ = 28;
// 	 	Illegal seek
constexpr int ESPIPE_ = 29;
// 	 	Read-only file system
constexpr int EROFS_ = 30;
// 	 	Too many links
constexpr int EMLINK_ = 31;
// 	 	Broken pipe
constexpr int EPIPE_ = 32;
// 	 	Math argument out of domain of func
constexpr int EDOM_ = 33;
// 	 	Math result not representable
constexpr int ERANGE_ = 34;
// 	 	Resource deadlock would occur
constexpr int EDEADLK_ = 35;
// 	 	File name too long
constexpr int ENAMETOOLONG_ = 36;
// 	 	No record locks available
constexpr int ENOLCK_ = 37;
// 	 	Function not implemented
constexpr int ENOSYS_ = 38;
// 	 	Directory not empty
constexpr int ENOTEMPTY_ = 39;
// 	 	Too many symbolic links encountered
constexpr int ELOOP_ = 40;
// 	 	No message of desired type
constexpr int ENOMSG_ = 42;
// 	 	Identifier removed
constexpr int EIDRM_ = 43;
// 	 	Channel number out of range
constexpr int ECHRNG_ = 44;
// 	 	Level 2 not synchronized
constexpr int EL2NSYNC_ = 45;
// 	 	Level 3 halted
constexpr int EL3HLT_ = 46;
// 	 	Level 3 reset
constexpr int EL3RST_ = 47;
// 	 	Link number out of range
constexpr int ELNRNG_ = 48;
// 	 	Protocol driver not attached
constexpr int EUNATCH_ = 49;
// 	 	No CSI structure available
constexpr int ENOCSI_ = 50;
// 	 	Level 2 halted
constexpr int EL2HLT_ = 51;
// 	 	Invalid exchange
constexpr int EBADE_ = 52;
// 	 	Invalid request descriptor
constexpr int EBADR_ = 53;
// 	 	Exchange full
constexpr int EXFULL_ = 54;
// 	 	No anode
constexpr int ENOANO_ = 55;
// 	 	Invalid request code
constexpr int EBADRQC_ = 56;
// 	 	Invalid slot
constexpr int EBADSLT_ = 57;
// 	 	Bad font file format
constexpr int EBFONT_ = 59;
// 	 	Device not a stream
constexpr int ENOSTR_ = 60;
// 	 	No data available
constexpr int ENODATA_ = 61;
// 	 	Timer expired
constexpr int ETIME_ = 62;
// 	 	Out of streams resources
constexpr int ENOSR_ = 63;
// 	 	Machine is not on the network
constexpr int ENONET_ = 64;
// 	 	Package not installed
constexpr int ENOPKG_ = 65;
// 	 	Object is remote
constexpr int EREMOTE_ = 66;
// 	 	Link has been severed
constexpr int ENOLINK_ = 67;
// 	 	Advertise error
constexpr int EADV_ = 68;
// 	 	Srmount error
constexpr int ESRMNT_ = 69;
// 	 	Communication error on send
constexpr int ECOMM_ = 70;
// 	 	Protocol error
constexpr int EPROTO_ = 71;
// 	 	Multihop attempted
constexpr int EMULTIHOP_ = 72;
// 	 	RFS specific error
constexpr int EDOTDOT_ = 73;
// 	 	Not a data message
constexpr int EBADMSG_ = 74;
// 	 	Value too large for defined data type
constexpr int EOVERFLOW_ = 75;
// 	 	Name not unique on network
constexpr int ENOTUNIQ_ = 76;
// 	 	File descriptor in bad state
constexpr int EBADFD_ = 77;
// 	 	Remote address changed
constexpr int EREMCHG_ = 78;
// 	 	Can not access a needed shared library
constexpr int ELIBACC_ = 79;
// 	 	Accessing a corrupted shared library
constexpr int ELIBBAD_ = 80;
// 	 	.lib section in a.out corrupted
constexpr int ELIBSCN_ = 81;
// 	 	Attempting to link in too many shared libraries
constexpr int ELIBMAX_ = 82;
// 	 	Cannot exec a shared library directly
constexpr int ELIBEXEC_ = 83;
// 	 	Illegal byte sequence
constexpr int EILSEQ_ = 84;
// 	 	Interrupted system call should be restarted
constexpr int ERESTART_ = 85;
// 	 	Streams pipe error
constexpr int ESTRPIPE_ = 86;
// 	 	Too many users
constexpr int EUSERS_ = 87;
// 	 	Socket operation on non-socket
constexpr int ENOTSOCK_ = 88;
// 	 	Destination address required
constexpr int EDESTADDRREQ_ = 89;
// 	 	Message too long
constexpr int EMSGSIZE_ = 90;
// 	 	Protocol wrong type for socket
constexpr int EPROTOTYPE_ = 91;
// 	 	Protocol not available
constexpr int ENOPROTOOPT_ = 92;
// 	 	Protocol not supported
constexpr int EPROTONOSUPPORT_ = 93;
// 	 	Socket type not supported
constexpr int ESOCKTNOSUPPORT_ = 94;
// 	 	Operation not supported on transport endpoint
constexpr int EOPNOTSUPP_ = 95;
// 	 	Protocol family not supported
constexpr int EPFNOSUPPORT_ = 96;
// 	 	Address family not supported by protocol
constexpr int EAFNOSUPPORT_ = 97;
// 	 	Address already in use
constexpr int EADDRINUSE_ = 98;
// 	 	Cannot assign requested address
constexpr int EADDRNOTAVAIL_ = 99;
// 	 	Network is down
constexpr int ENETDOWN_ = 100;
// 	 	Network is unreachable
constexpr int ENETUNREACH_ = 101;
// 	 	Network dropped connection because of reset
constexpr int ENETRESET_ = 102;
// 	 	Software caused connection abort
constexpr int ECONNABORTED_ = 103;
// 	 	Connection reset by peer
constexpr int ECONNRESET_ = 104;
// 	 	No buffer space available
constexpr int ENOBUFS_ = 105;
// 	 	Transport endpoint is already connected
constexpr int EISCONN_ = 106;
// 	 	Transport endpoint is not connected
constexpr int ENOTCONN_ = 107;
// 	 	Cannot send after transport endpoint shutdown
constexpr int ESHUTDOWN_ = 108;
// 	 	Too many references: cannot splice
constexpr int ETOOMANYREFS_ = 109;
// 	 	Connection timed out
constexpr int ETIMEDOUT_ = 110;
// 	 	Connection refused
constexpr int ECONNREFUSED_ = 111;
// 	 	Host is down
constexpr int EHOSTDOWN_ = 112;
// 	 	No route to host
constexpr int EHOSTUNREACH_ = 113;
// 	 	Operation already in progress
constexpr int EALREADY_ = 114;
// 	 	Operation now in progress
constexpr int EINPROGRESS_ = 115;
// 	 	Stale NFS file handle
constexpr int ESTALE_ = 116;
// 	 	Structure needs cleaning
constexpr int EUCLEAN_ = 117;
// 	 	Not a XENIX named type file
constexpr int ENOTNAM_ = 118;
// 	 	No XENIX semaphores available
constexpr int ENAVAIL_ = 119;
// 	 	Is a named type file
constexpr int EISNAM_ = 120;
// 	 	Remote I/O error
constexpr int EREMOTEIO_ = 121;
// 	 	Quota exceeded
constexpr int EDQUOT_ = 122;
// 	 	No medium found
constexpr int ENOMEDIUM_ = 123;
// 	 	Wrong medium type
constexpr int EMEDIUMTYPE_ = 124;
// 	 	Operation Canceled
constexpr int ECANCELED_ = 125;
// 	 	Required key not available
constexpr int ENOKEY_ = 126;
// 	 	Key has expired
constexpr int EKEYEXPIRED_ = 127;
// 	 	Key has been revoked
constexpr int EKEYREVOKED_ = 128;
// 	 	Key was rejected by service
constexpr int EKEYREJECTED_ = 129;
// 	 	Owner died
constexpr int EOWNERDEAD_ = 130;
// 	 	State not recoverable
constexpr int ENOTRECOVERABLE_ = 131;
} // namespace ec