#pragma once
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#define MY_NULL ((void *)0)
typedef uintptr_t my_size_t;

#ifdef __APPLE__

#define ERR_MSGS_MAC
const char *mac_error_msgs[134] = {
    [0] = "0",
    [EPERM] = "Operation not permitted",
    [ENOENT] = "No such file or directory",
    [ESRCH] = "No such process",
    [EINTR] = "Interrupted function call",
    [EIO] = "Input/output error",
    [ENXIO] = "No such device or address",
    [E2BIG] = "Arg list too long",
    [ENOEXEC] = "Exec format error",
    [EBADF] = "Bad file descriptor",
    [ECHILD] = "No child processes",
    [EDEADLK] = "Resource deadlock avoided",
    [ENOMEM] = "Cannot allocate memory",
    [EACCES] = "Permission denied",
    [EFAULT] = "Bad address",
    [ENOTBLK] = "Not a block device",
    [EBUSY] = "Resource busy",
    [EEXIST] = "File exists",
    [EXDEV] = "Improper link",
    [ENODEV] = "Operation not supported by device",
    [ENOTDIR] = "Not a directory",
    [EISDIR] = "Is a directory",
    [EINVAL] = "Invalid argument",
    [ENFILE] = "Too many open files in system",
    [EMFILE] = "Too many open files",
    [ENOTTY] = "Inappropriate ioctl for device",
    [ETXTBSY] = "Text file busy",
    [EFBIG] = "File too large",
    [ENOSPC] = "Device out of space",
    [ESPIPE] = "Illegal seek",
    [EROFS] = "Read-only file system",
    [EMLINK] = "Too many links",
    [EPIPE] = "Broken pipe",
    [EDOM] = "Numerical argument out of domain",
    [ERANGE] = "Numerical result out of range",
    [EAGAIN] = "Resource temporarily unavailable",
    [EINPROGRESS] = "Operation now in progress",
    [EALREADY] = "Operation already in progress",
    [ENOTSOCK] = "Socket operation on non-socket",
    [EDESTADDRREQ] = "Destination address required",
    [EMSGSIZE] = "Message too long",
    [EPROTOTYPE] = "Protocol wrong type for socket",
    [ENOPROTOOPT] = "Protocol not available",
    [EPROTONOSUPPORT] = "Protocol not supported",
    [ESOCKTNOSUPPORT] = "Socket type not supported",
    [ENOTSUP] = "Not supported",
    [EPFNOSUPPORT] = "Protocol family not supported",
    [EAFNOSUPPORT] = "Address family not supported by protocol family",
    [EADDRINUSE] = "Address already in use",
    [EADDRNOTAVAIL] = "Cannot assign requested address",
    [ENETDOWN] = "Network is down",
    [ENETUNREACH] = "Network is unreachable",
    [ENETRESET] = "Network dropped connection on reset",
    [ECONNABORTED] = "Software caused connection abort",
    [ECONNRESET] = "Connection reset by peer",
    [ENOBUFS] = "No buffer space available",
    [EISCONN] = "Socket is already connected",
    [ENOTCONN] = "Socket is not connected",
    [ESHUTDOWN] = "Cannot send after socket shutdown",
    [ETIMEDOUT] = "Connection timed out",
    [ECONNREFUSED] = "Connection refused",
    [ELOOP] = "Too many levels of symbolic links",
    [ENAMETOOLONG] = "File name too long",
    [EHOSTDOWN] = "Host is down",
    [EHOSTUNREACH] = "No route to host",
    [ENOTEMPTY] = "Directory not empty",
    [EPROCLIM] = "Too many processes",
    [EUSERS] = "Too many users",
    [EDQUOT] = "Disk quota exceeded",
    [ESTALE] = "Stale NFS file handle",
    [EBADRPC] = "RPC struct is bad",
    [ERPCMISMATCH] = "RPC version wrong",
    [EPROGUNAVAIL] = "RPC prog. not avail",
    [EPROGMISMATCH] = "Program version wrong",
    [EPROCUNAVAIL] = "Bad procedure for program",
    [ENOLCK] = "No locks available",
    [ENOSYS] = "Function not implemented",
    [EFTYPE] = "Inappropriate file type or format",
    [EAUTH] = "Authentication error",
    [ENEEDAUTH] = "Need authenticator",
    [EPWROFF] = "Device power is off",
    [EDEVERR] = "Device error",
    [EOVERFLOW] = "Value too large to be stored in data type",
    [EBADEXEC] = "Bad executable (or shared library)",
    [EBADARCH] = "Bad CPU type in executable",
    [ESHLIBVERS] = "Shared library version mismatch",
    [EBADMACHO] = "Malformed Mach-o file",
    [ECANCELED] = "Operation canceled",
    [EIDRM] = "Identifier removed",
    [ENOMSG] = "No message of desired type",
    [EILSEQ] = "Illegal byte sequence",
    [ENOATTR] = "Attribute not found",
    [EBADMSG] = "Bad message",
    [EMULTIHOP] = "Reserved",
    [ENODATA] = "No message available",
    [ENOLINK] = "Reserved",
    [ENOSR] = "No STREAM resources",
    [ENOSTR] = "Not a STREAM",
    [EPROTO] = "Protocol error",
    [ETIME] = "STREAM ioctl() timeout",
    [EOPNOTSUPP] = "Operation not supported on socket",
};
#endif

#ifdef __linux__

#define ERR_MSGS_LINUX                                                         \
  const char *linux_error_msgs[134] = {                                        \
      [0] = "Success",                                                         \
      [EPERM] = "Operation not permitted",                                     \
      [ENOENT] = "No such file or directory",                                  \
      [ESRCH] = "No such process",                                             \
      [EINTR] = "Interrupted system call",                                     \
      [EIO] = "Input/output error",                                            \
      [ENXIO] = "No such device or address",                                   \
      [E2BIG] = "Argument list too long",                                      \
      [ENOEXEC] = "Exec format error",                                         \
      [EBADF] = "Bad file descriptor",                                         \
      [ECHILD] = "No child processes",                                         \
      [EAGAIN] = "Resource temporarily unavailable",                           \
      [ENOMEM] = "Cannot allocate memory",                                     \
      [EACCES] = "Permission denied",                                          \
      [EFAULT] = "Bad address",                                                \
      [ENOTBLK] = "Block device required",                                     \
      [EBUSY] = "Device or resource busy",                                     \
      [EEXIST] = "File exists",                                                \
      [EXDEV] = "Invalid cross-device link",                                   \
      [ENODEV] = "No such device",                                             \
      [ENOTDIR] = "Not a directory",                                           \
      [EISDIR] = "Is a directory",                                             \
      [EINVAL] = "Invalid argument",                                           \
      [ENFILE] = "Too many open files in system",                              \
      [EMFILE] = "Too many open files",                                        \
      [ENOTTY] = "Inappropriate ioctl for device",                             \
      [ETXTBSY] = "Text file busy",                                            \
      [EFBIG] = "File too large",                                              \
      [ENOSPC] = "No space left on device",                                    \
      [ESPIPE] = "Illegal seek",                                               \
      [EROFS] = "Read-only file system",                                       \
      [EMLINK] = "Too many links",                                             \
      [EPIPE] = "Broken pipe",                                                 \
      [EDOM] = "Numerical argument out of domain",                             \
      [ERANGE] = "Numerical result out of range",                              \
      [EDEADLK] = "Resource deadlock avoided",                                 \
      [ENAMETOOLONG] = "File name too long",                                   \
      [ENOLCK] = "No locks available",                                         \
      [ENOSYS] = "Function not implemented",                                   \
      [ENOTEMPTY] = "Directory not empty",                                     \
      [ELOOP] = "Too many levels of symbolic links",                           \
      [ENOMSG] = "No message of desired type",                                 \
      [EIDRM] = "Identifier removed",                                          \
      [ECHRNG] = "Channel number out of range",                                \
      [EL2NSYNC] = "Level 2 not synchronized",                                 \
      [EL3HLT] = "Level 3 halted",                                             \
      [EL3RST] = "Level 3 reset",                                              \
      [ELNRNG] = "Link number out of range",                                   \
      [EUNATCH] = "Protocol driver not attached",                              \
      [ENOCSI] = "No CSI structure available",                                 \
      [EL2HLT] = "Level 2 halted",                                             \
      [EBADE] = "Invalid exchange",                                            \
      [EBADR] = "Invalid request descriptor",                                  \
      [EXFULL] = "Exchange full",                                              \
      [ENOANO] = "No anode",                                                   \
      [EBADRQC] = "Invalid request code",                                      \
      [EBADSLT] = "Invalid slot",                                              \
      [EBFONT] = "Bad font file format",                                       \
      [ENOSTR] = "Device not a stream",                                        \
      [ENODATA] = "No data available",                                         \
      [ETIME] = "Timer expired",                                               \
      [ENOSR] = "Out of streams resources",                                    \
      [ENONET] = "Machine is not on the network",                              \
      [ENOPKG] = "Package not installed",                                      \
      [EREMOTE] = "Object is remote",                                          \
      [ENOLINK] = "Link has been severed",                                     \
      [EADV] = "Advertise error",                                              \
      [ESRMNT] = "Srmount error",                                              \
      [ECOMM] = "Communication error on send",                                 \
      [EPROTO] = "Protocol error",                                             \
      [EMULTIHOP] = "Multihop attempted",                                      \
      [EDOTDOT] = "RFS specific error",                                        \
      [EBADMSG] = "Bad message",                                               \
      [EOVERFLOW] = "Value too large for defined data type",                   \
      [ENOTUNIQ] = "Name not unique on network",                               \
      [EBADFD] = "File descriptor in bad state",                               \
      [EREMCHG] = "Remote address changed",                                    \
      [ELIBACC] = "Can not access a needed shared library",                    \
      [ELIBBAD] = "Accessing a corrupted shared library",                      \
      [ELIBSCN] = ".lib section in a.out corrupted",                           \
      [ELIBMAX] = "Attempting to link in too many shared libraries",           \
      [ELIBEXEC] = "Cannot exec a shared library directly",                    \
      [EILSEQ] = "Invalid or incomplete multibyte or wide character",          \
      [ERESTART] = "Interrupted system call should be restarted",              \
      [ESTRPIPE] = "Streams pipe error",                                       \
      [EUSERS] = "Too many users",                                             \
      [ENOTSOCK] = "Socket operation on non-socket",                           \
      [EDESTADDRREQ] = "Destination address required",                         \
      [EMSGSIZE] = "Message too long",                                         \
      [EPROTOTYPE] = "Protocol wrong type for socket",                         \
      [ENOPROTOOPT] = "Protocol not available",                                \
      [EPROTONOSUPPORT] = "Protocol not supported",                            \
      [ESOCKTNOSUPPORT] = "Socket type not supported",                         \
      [EOPNOTSUPP] = "Operation not supported",                                \
      [EPFNOSUPPORT] = "Protocol family not supported",                        \
      [EAFNOSUPPORT] = "Address family not supported by protocol",             \
      [EADDRINUSE] = "Address already in use",                                 \
      [EADDRNOTAVAIL] = "Cannot assign requested address",                     \
      [ENETDOWN] = "Network is down",                                          \
      [ENETUNREACH] = "Network is unreachable",                                \
      [ENETRESET] = "Network dropped connection on reset",                     \
      [ECONNABORTED] = "Software caused connection abort",                     \
      [ECONNRESET] = "Connection reset by peer",                               \
      [ENOBUFS] = "No buffer space available",                                 \
      [EISCONN] = "Transport endpoint is already connected",                   \
      [ENOTCONN] = "Transport endpoint is not connected",                      \
      [ESHUTDOWN] = "Cannot send after transport endpoint shutdown",           \
      [ETOOMANYREFS] = "Too many references: cannot splice",                   \
      [ETIMEDOUT] = "Connection timed out",                                    \
      [ECONNREFUSED] = "Connection refused",                                   \
      [EHOSTDOWN] = "Host is down",                                            \
      [EHOSTUNREACH] = "No route to host",                                     \
      [EALREADY] = "Operation already in progress",                            \
      [EINPROGRESS] = "Operation now in progress",                             \
      [ESTALE] = "Stale file handle",                                          \
      [EUCLEAN] = "Structure needs cleaning",                                  \
      [ENOTNAM] = "Not a XENIX named type file",                               \
      [ENAVAIL] = "No XENIX semaphores available",                             \
      [EISNAM] = "Is a named type file",                                       \
      [EREMOTEIO] = "Remote I/O error",                                        \
      [EDQUOT] = "Disk quota exceeded",                                        \
      [ENOMEDIUM] = "No medium found",                                         \
      [EMEDIUMTYPE] = "Wrong medium type",                                     \
      [ECANCELED] = "Operation canceled",                                      \
      [ENOKEY] = "Required key not available",                                 \
      [EKEYEXPIRED] = "Key has expired",                                       \
      [EKEYREVOKED] = "Key has been revoked",                                  \
      [EKEYREJECTED] = "Key was rejected by service",                          \
      [EOWNERDEAD] = "Owner died",                                             \
      [ENOTRECOVERABLE] = "State not recoverable",                             \
      [ERFKILL] = "Operation not possible due to RF-kill",                     \
      [EHWPOISON] = "Memory page has hardware error",                          \
  };
#endif

char *my_strerror(int errnum);

void *my_memchr(const void *str, int c, my_size_t n);

my_size_t my_strcspn(const char *str1, const char *str2);

my_size_t my_strlen(const char *str);

char *my_strpbrk(const char *str1, const char *str2);

char *my_strrchr(const char *str, int c);

char *my_strstr(const char *haystack, const char *needle);

char *my_strtok(char *str, const char *delim);
// Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
// байтах строки, на которую указывает аргумент str. Возвращает указатаель на
// найденный байт либо налл
void *my_memchr(const void *str, int c, my_size_t n);

// Сравнивает первые n байтов str1 и str2.
// Возвращает разницу между символами по asci
int my_memcmp(const void *str1, const void *str2, my_size_t n);

// Копирует n символов из src в dest.
// Возвращает указатель на дест

void *my_memcpy(void *dest, const void *src, my_size_t n);

// Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
// указывает аргумент str.
// вовзращает указатель на измененную строку
void *my_memset(void *str, int c, my_size_t n);

// Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
// которую указывает аргумент str.
// Возвращает указатель на первое вхождение, либо null
char *my_strchr(const char *str, int c);

// Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов.
// Возвращает изменненую строку
char *my_strncat(char *dest, const char *src, my_size_t n);

// Сравнивает не более первых n байтов str1 и str2.
// Возвращает разницу по asci
int my_strncmp(const char *str1, const char *str2, my_size_t n);

// Копирует до n символов из строки, на которую указывает src, в dest.
// Возвращает указатель на измененную строку dest
char *my_strncpy(char *dest, const char *src, my_size_t n);

int my_sprintf(char *str, const char *format, ...);