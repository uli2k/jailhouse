/*
 * Licensed under the GNU General Public License version 2 with exceptions. See
 * LICENSE file in the project root for full license information
 */

#ifndef _osal_
#define _osal_

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef PACKED
#define PACKED_BEGIN
#define PACKED  __attribute__((__packed__))
#define PACKED_END
#endif

#include <stdint.h>
#include <stdarg.h>

/* General types */
typedef uint8_t             boolean;
#define TRUE                1
#define FALSE               0
typedef int8_t              int8;
typedef int16_t             int16;
typedef int32_t             int32;
typedef uint8_t             uint8;
typedef uint16_t            uint16;
typedef uint32_t            uint32;
typedef int64_t             int64;
typedef uint64_t            uint64;
typedef float               float32;
typedef double              float64;

typedef struct
{
	uint32 sec;		/*< Seconds elapsed since the Epoch (Jan 1, 1970) */
	uint32 usec;	/*< Microseconds elapsed since last second boundary */
} ec_timet;

typedef struct osal_timer
{
	ec_timet stop_time;
} osal_timert;

void osal_timer_start(osal_timert * self, uint32 timeout_us);
boolean osal_timer_is_expired(osal_timert * self);
void osal_usleep(uint32 usec);
ec_timet osal_current_time(void);
void osal_time_diff(ec_timet *start, ec_timet *end, ec_timet *diff);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, unsigned long n);
int vsprintf(char *buf, const char *fmt, va_list args);
int sprintf(char *buf, const char *fmt, ...);

#ifdef __cplusplus
}
#endif

#endif
