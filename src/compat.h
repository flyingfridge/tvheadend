/*
 *  Tvheadend - structures
 *  Copyright (C) 2007 Andreas Öman
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef COMPAT_H
#define COMPAT_H

#if ENABLE_ANDROID
#define S_IEXEC S_IXUSR
#define epoll_create1(EPOLL_CLOEXEC) epoll_create(n)
#define inotify_init1(IN_CLOEXEC) inotify_init()
#include <time64.h>
// 32-bit Android has only timegm64() and not timegm().
// We replicate the behaviour of timegm() when the result overflows time_t.
static inline time_t timegm(struct tm* const t);
time_t timegm(struct tm* const t) {
  // time_t is signed on Android.
  static const time_t kTimeMax = ~(1L << (sizeof(time_t) * CHAR_BIT - 1));
  static const time_t kTimeMin = (1L << (sizeof(time_t) * CHAR_BIT - 1));
  time64_t result = timegm64(t);
  if (result < kTimeMin || result > kTimeMax)
    return -1;
  return result;
}
#endif /* ENABLE_ANDROID */

#if (ENABLE_ANDROID || defined PLATFORM_FREEBSD) && !defined IPTOS_DSCP_MASK
#define	IPTOS_DSCP_MASK		0xfc
#define	IPTOS_DSCP(x)		((x) & IPTOS_DSCP_MASK)
#define	IPTOS_DSCP_AF11		0x28
#define	IPTOS_DSCP_AF12		0x30
#define	IPTOS_DSCP_AF13		0x38
#define	IPTOS_DSCP_AF21		0x48
#define	IPTOS_DSCP_AF22		0x50
#define	IPTOS_DSCP_AF23		0x58
#define	IPTOS_DSCP_AF31		0x68
#define	IPTOS_DSCP_AF32		0x70
#define	IPTOS_DSCP_AF33		0x78
#define	IPTOS_DSCP_AF41		0x88
#define	IPTOS_DSCP_AF42		0x90
#define	IPTOS_DSCP_AF43		0x98
#define	IPTOS_DSCP_EF		0xb8
#endif /* not defined IPTOS_DSCP_MASK */

#if (ENABLE_ANDROID || defined PLATFORM_FREEBSD) && !defined IPTOS_CLASS_MASK
#define	IPTOS_CLASS_MASK	0xe0
#define	IPTOS_CLASS(class)	((class) & IPTOS_CLASS_MASK)
#define	IPTOS_CLASS_CS0		0x00
#define	IPTOS_CLASS_CS1		0x20
#define	IPTOS_CLASS_CS2		0x40
#define	IPTOS_CLASS_CS3		0x60
#define	IPTOS_CLASS_CS4		0x80
#define	IPTOS_CLASS_CS5		0xa0
#define	IPTOS_CLASS_CS6		0xc0
#define	IPTOS_CLASS_CS7		0xe0

#define	IPTOS_CLASS_DEFAULT	IPTOS_CLASS_CS0

#endif /* not defined IPTOS_CLASS_MASK */

#endif /* COMPAT_H */
