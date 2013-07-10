// Timer.C

#include "Timer.h"

// Return the time now, in milliseconds.

long int Timer::millisec( void ) {
#if defined(__MINGW32_VERSION)
  // timeb and ftime() are obsolete, but available in Win32/mingw.
  struct timeb	t;
  ftime( &t );
  return( t.time * 1000 + t.millitm );
# else
  // Everyone else (Unix, Mac OS X) use gettimeofday().
  struct timeval	t;
  struct timezone	tz;
  gettimeofday( &t, &tz );
  return( t.tv_sec * 1000 + t.tv_usec / 1000 );
#endif
}

