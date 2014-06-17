/*
Copyright (c) Fraunhofer ITWM - Carsten Lojewski <lojewski@itwm.fhg.de>, 2013-2014

This file is part of GPI-2.

GPI-2 is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License
version 3 as published by the Free Software Foundation.

GPI-2 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GPI-2. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GPI2_UTILITY_H
#define GPI2_UTILITY_H 1

#include <errno.h>
#include <sched.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <xmmintrin.h>

#ifdef DEBUG
#define gaspi_print_error(msg, ...)					\
  int errsv = errno;							\
  if( errsv != 0 )							\
    fprintf(stderr,"Error %d (%s) at (%s:%d):" msg "\n",errsv, (char *) strerror(errsv), __FILE__, __LINE__, ##__VA_ARGS__); \
      else								\
      fprintf(stderr,"Error at (%s:%d):" msg "\n", __FILE__, __LINE__, ##__VA_ARGS__) 
	
#define gaspi_verify_null_ptr(ptr)				\
  if(ptr == NULL)						\
    {								\
      gaspi_print_error ("Passed argument is a NULL pointer");	\
      return GASPI_ERROR;					\
    } 


#else
#define gaspi_print_error(msg, ...)
#define gaspi_verify_null_ptr(ptr)
#endif

#ifdef MIC
#define gaspi_delay()   _mm_delay_32(32)
#else
#define gaspi_delay()   _mm_pause()
#endif


#define MAX(a,b)  (((a)<(b)) ? (b) : (a))
#define MIN(a,b)  (((a)>(b)) ? (b) : (a))


ulong gaspi_load_ulong(volatile ulong *ptr);
float gaspi_get_cpufreq ();
int gaspi_get_affinity_mask (const int sock, cpu_set_t * cpuset);
inline int gaspi_thread_sleep(int msecs);

#endif
