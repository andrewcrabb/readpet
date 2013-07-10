// Timer.h
// Timer class for performance monitoring.

#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>

// Hack: Obsolete <sys/timeb.h> only timing routine available in Win32/mingw.
#if defined(__MINGW32_VERSION)
#include <sys/timeb.h>
#else
#include <sys/time.h>
#endif

class Timer {
 private:
  long int	_start, _end, _diff;
  long int	millisec( void );
 public:
  void		reset( void ) { _start = _end = _diff = 0; }
  void		start( void ) { _start = millisec(); }
  void		end( void ) { _end = millisec(); }
  int		elapse( void ) { return( _end - _start ); }
};

#endif
