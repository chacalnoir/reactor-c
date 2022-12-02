/* Windows API support for the C target of Lingua Franca. */

/*************
Copyright (c) 2021, The University of California at Berkeley.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************/

/** Windows API support for the C target of Lingua Franca.
 *
 *  @author{Soroush Bateni <soroush@utdallas.edu>}
 *
 * All functions return 0 on success.
 *
 * @see https://gist.github.com/Soroosh129/127d1893fa4c1da6d3e1db33381bb273
 */

#ifndef LF_WINDOWS_SUPPORT_H
#define LF_WINDOWS_SUPPORT_H

#include <windows.h>
#include <process.h>
#include <windef.h>
#include <stdint.h> // For fixed-width integral types

#if defined NUMBER_OF_WORKERS || defined LINGUA_FRANCA_TRACE
#if __STDC_VERSION__ < 201112L || defined (__STDC_NO_THREADS__) // (Not C++11 or later) or no threads support


/**
 * On Windows, one could use both a mutex or
 * a critical section for the same purpose. However,
 * critical sections are lighter and limited to one process
 * and thus fit the requirements of Lingua Franca.
 */
typedef CRITICAL_SECTION _lf_mutex_t;
/**
 * For compatibility with other platform APIs, we assume
 * that mutex is analogous to critical section.
 */
typedef _lf_mutex_t _lf_critical_section_t;

typedef CONDITION_VARIABLE _lf_cond_t;
typedef HANDLE _lf_thread_t;

// The one and only mutex lock.
extern _lf_mutex_t mutex;

// Condition variables used for notification between threads.
extern _lf_cond_t event_q_changed;

#else
#include "lf_C11_threads_support.h"
#endif
#endif

// Use 64-bit times and 32-bit unsigned microsteps
#include "lf_tag_64_32.h"

#define _LF_TIMEOUT ETIMEDOUT

#endif // LF_WINDOWS_SUPPORT_H

