#pragma once

namespace ec {
enum class errc : int {
  // No error
  success = 0,
  // Operation not permitted
  eperm = 1,
  // No such file or directory
  enoent = 2,
  // No such process
  esrch = 3,
  // Interrupted system call
  eintr = 4,
  // I/O error
  eio = 5,
  // No such device or address
  enxio = 6,
  // Argument list too long
  e2big = 7,
  // Exec format error
  enoexec = 8,
  // Bad file number
  ebadf = 9,
  // No child processes
  echild = 10,
  // Try again
  eagain = 11,
  // Out of memory
  enomem = 12,
  // Permission denied
  eacces = 13,
  // Bad address
  efault = 14,
  // Block device required
  enotblk = 15,
  // Device or resource busy
  ebusy = 16,
  // File exists
  eexist = 17,
  // Cross-device link
  exdev = 18,
  // No such device
  enodev = 19,
  // Not a directory
  enotdir = 20,
  // Is a directory
  eisdir = 21,
  // Invalid argument
  einval = 22,
  // File table overflow
  enfile = 23,
  // Too many open files
  emfile = 24,
  // Not a typewriter
  enotty = 25,
  // Text file busy
  etxtbsy = 26,
  // File too large
  efbig = 27,
  // No space left on device
  enospc = 28,
  // Illegal seek
  espipe = 29,
  // Read-only file system
  erofs = 30,
  // Too many links
  emlink = 31,
  // Broken pipe
  epipe = 32,
  // Math argument out of domain of func
  edom = 33,
  // Math result not representable
  erange = 34,
  // Resource deadlock would occur
  edeadlk = 35,
  // File name too long
  enametoolong = 36,
  // No record locks available
  enolck = 37,
  // Function not implemented
  enosys = 38,
  // Directory not empty
  enotempty = 39,
  // Too many symbolic links encountered
  eloop = 40,
  // No message of desired type
  enomsg = 42,
  // Identifier removed
  eidrm = 43,
  // Channel number out of range
  echrng = 44,
  // Level 2 not synchronized
  el2nsync = 45,
  // Level 3 halted
  el3hlt = 46,
  // Level 3 reset
  el3rst = 47,
  // Link number out of range
  elnrng = 48,
  // Protocol driver not attached
  eunatch = 49,
  // No CSI structure available
  enocsi = 50,
  // Level 2 halted
  el2hlt = 51,
  // Invalid exchange
  ebade = 52,
  // Invalid request descriptor
  ebadr = 53,
  // Exchange full
  exfull = 54,
  // No anode
  enoano = 55,
  // Invalid request code
  ebadrqc = 56,
  // Invalid slot
  ebadslt = 57,
  // Bad font file format
  ebfont = 59,
  // Device not a stream
  enostr = 60,
  // No data available
  enodata = 61,
  // Timer expired
  etime = 62,
  // Out of streams resources
  enosr = 63,
  // Machine is not on the network
  enonet = 64,
  // Package not installed
  enopkg = 65,
  // Object is remote
  eremote = 66,
  // Link has been severed
  enolink = 67,
  // Advertise error
  eadv = 68,
  // Srmount error
  esrmnt = 69,
  // Communication error on send
  ecomm = 70,
  // Protocol error
  eproto = 71,
  // Multihop attempted
  emultihop = 72,
  // RFS specific error
  edotdot = 73,
  // Not a data message
  ebadmsg = 74,
  // Value too large for defined data type
  eoverflow = 75,
  // Name not unique on network
  enotuniq = 76,
  // File descriptor in bad state
  ebadfd = 77,
  // Remote address changed
  eremchg = 78,
  // Can not access a needed shared library
  elibacc = 79,
  // Accessing a corrupted shared library
  elibbad = 80,
  // .lib section in a.out corrupted
  elibscn = 81,
  // Attempting to link in too many shared libraries
  elibmax = 82,
  // Cannot exec a shared library directly
  elibexec = 83,
  // Illegal byte sequence
  eilseq = 84,
  // Interrupted system call should be restarted
  erestart = 85,
  // Streams pipe error
  estrpipe = 86,
  // Too many users
  eusers = 87,
  // Socket operation on non-socket
  enotsock = 88,
  // Destination address required
  edestaddrreq = 89,
  // Message too long
  emsgsize = 90,
  // Protocol wrong type for socket
  eprototype = 91,
  // Protocol not available
  enoprotoopt = 92,
  // Protocol not supported
  eprotonosupport = 93,
  // Socket type not supported
  esocktnosupport = 94,
  // Operation not supported on transport endpoint
  eopnotsupp = 95,
  // Protocol family not supported
  epfnosupport = 96,
  // Address family not supported by protocol
  eafnosupport = 97,
  // Address already in use
  eaddrinuse = 98,
  // Cannot assign requested address
  eaddrnotavail = 99,
  // Network is down
  enetdown = 100,
  // Network is unreachable
  enetunreach = 101,
  // Network dropped connection because of reset
  enetreset = 102,
  // Software caused connection abort
  econnaborted = 103,
  // Connection reset by peer
  econnreset = 104,
  // No buffer space available
  enobufs = 105,
  // Transport endpoint is already connected
  eisconn = 106,
  // Transport endpoint is not connected
  enotconn = 107,
  // Cannot send after transport endpoint shutdown
  eshutdown = 108,
  // Too many references: cannot splice
  etoomanyrefs = 109,
  // Connection timed out
  etimedout = 110,
  // Connection refused
  econnrefused = 111,
  // Host is down
  ehostdown = 112,
  // No route to host
  ehostunreach = 113,
  // Operation already in progress
  ealready = 114,
  // Operation now in progress
  einprogress = 115,
  // Stale NFS file handle
  estale = 116,
  // Structure needs cleaning
  euclean = 117,
  // Not a XENIX named type file
  enotnam = 118,
  // No XENIX semaphores available
  enavail = 119,
  // Is a named type file
  eisnam = 120,
  // Remote I/O error
  eremoteio = 121,
  // Quota exceeded
  edquot = 122,
  // No medium found
  enomedium = 123,
  // Wrong medium type
  emediumtype = 124,
  // Operation Canceled
  ecanceled = 125,
  // Required key not available
  enokey = 126,
  // Key has expired
  ekeyexpired = 127,
  // Key has been revoked
  ekeyrevoked = 128,
  // Key was rejected by service
  ekeyrejected = 129,
  // Owner died
  eownerdead = 130,
  // State not recoverable
  enotrecoverable = 131,

  // Aliases to the std::errc::values
  address_family_not_supported = eafnosupport,
  address_in_use = eaddrinuse,
  address_not_available = eaddrnotavail,
  already_connected = eisconn,
  argument_list_too_long = e2big,
  argument_out_of_domain = edom,
  bad_address = efault,
  bad_file_descriptor = ebadf,
  bad_message = ebadmsg,
  broken_pipe = epipe,
  connection_aborted = econnaborted,
  connection_already_in_progress = ealready,
  connection_refused = econnrefused,
  connection_reset = econnreset,
  cross_device_link = exdev,
  destination_address_required = edestaddrreq,
  device_or_resource_busy = ebusy,
  directory_not_empty = enotempty,
  executable_format_error = enoexec,
  file_exists = eexist,
  file_too_large = efbig,
  filename_too_long = enametoolong,
  function_not_supported = enosys,
  host_unreachable = ehostunreach,
  identifier_removed = eidrm,
  illegal_byte_sequence = eilseq,
  inappropriate_io_control_operation = enotty,
  interrupted = eintr,
  invalid_argument = einval,
  invalid_seek = espipe,
  io_error = eio,
  is_a_directory = eisdir,
  message_size = emsgsize,
  network_down = enetdown,
  network_reset = enetreset,
  network_unreachable = enetunreach,
  no_buffer_space = enobufs,
  no_child_process = echild,
  no_link = enolink,
  no_lock_available = enolck,
  no_message_available = enodata,
  no_message = enomsg,
  no_protocol_option = enoprotoopt,
  no_space_on_device = enospc,
  no_stream_resources = enosr,
  no_such_device_or_address = enxio,
  no_such_device = enodev,
  no_such_file_or_directory = enoent,
  no_such_process = esrch,
  not_a_directory = enotdir,
  not_a_socket = enotsock,
  not_a_stream = enostr,
  not_connected = enotconn,
  not_enough_memory = enomem,
  not_supported = eopnotsupp,
  operation_canceled = ecanceled,
  operation_in_progress = einprogress,
  operation_not_permitted = eperm,
  operation_not_supported = eopnotsupp,
  operation_would_block = eagain,
  owner_dead = eownerdead,
  permission_denied = eacces,
  protocol_error = eproto,
  protocol_not_supported = eprotonosupport,
  read_only_file_system = erofs,
  resource_deadlock_would_occur = edeadlk,
  resource_unavailable_try_again = eagain,
  result_out_of_range = erange,
  state_not_recoverable = enotrecoverable,
  stream_timeout = etime,
  text_file_busy = etxtbsy,
  timed_out = etimedout,
  too_many_files_open_in_system = enfile,
  too_many_files_open = emfile,
  too_many_links = emlink,
  too_many_symbolic_link_levels = eloop,
  value_too_large = eoverflow,
  wrong_protocol_type = eprototype
};

} // namespace ec