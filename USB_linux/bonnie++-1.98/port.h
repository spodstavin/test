#ifndef PORT_UNIX_H
#define PORT_UNIX_H

#include "conf.h"




#ifndef _LARGEFILE64_SOURCE
#define _LARGEFILE64_SOURCE
#endif
#ifdef _LARGEFILE64_SOURCE
#define OFF_T_PRINTF "%lld"
#else
#define OFF_T_PRINTF "%d"
#endif

#if 0
#define false 0
#define true 1
#endif

// UNIX here
typedef struct timeval TIMEVAL_TYPE;

#ifdef _LARGEFILE64_SOURCE
#define OFF_TYPE off64_t
#define file_lseek lseek64
#define file_creat creat64
#define file_open open64
#else
#define OFF_TYPE off_t
#define file_lseek lseek
#define file_creat creat
#define file_open open
#endif

typedef int FILE_TYPE;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef const char * PCCHAR;
typedef char * PCHAR;
typedef PCHAR const CPCHAR;
typedef PCCHAR const CPCCHAR;
typedef void * PVOID;
typedef PVOID const CPVOID;
typedef const CPVOID CPCVOID;

typedef FILE_TYPE *PFILE_TYPE;

#define _strdup strdup

#ifdef NO_SNPRINTF
#define _snprintf sprintf
#else
#define _snprintf snprintf
#endif

#endif
