// INTEGRATE.CPP
/**** DATA::INTEGRATE
 * This integrates a curve (i.e., Data object pointed to by dptr) 
 * from 0 to the times listed in x[0..n].  Results are stored in y[0..n]
 * Data for x less than 0 is ignored
 * Integration is performed by trapezoid rule
 *****/
#include "Data.h"
/*---------------------------------------------------------*/
void Data::integrate(const Data *dptr)
{
  double total = 0.0;
  double xtotal = 0.0;
  double ylast = 0.0;
  double xx;
  double interp;
  int index = 0;
  int end = dptr->n;

  for( int i = 0; i < n; i++) {
    xx = x[i]>0.0 ? x[i]:0.0;
    if( xx ==  0.0 )
      y[i] = 0.0;
    else {
      if( xx < xtotal ) {
	total = 0.0;
	xtotal = 0.0;
	ylast = 0.0;
      } 
      while( ( index < end ) && ( ( dptr->x[index] ) <=  xx ) ) {
	total += 0.5 * (dptr->y[index] + ylast) * (dptr->x[index]-xtotal);
	xtotal = dptr->x[index];
	ylast = dptr->y[index];
	index++;
      }
      if( index < end ) {
	interp = ylast + (dptr->y[index] - ylast) * (xx - xtotal)/
	  (dptr->x[index]-xtotal);
      } else {
	interp = dptr->y[end - 2] + (dptr->y[end - 1]-dptr->y[end - 2]) *
	  (xx - dptr->x[end - 2]) / (dptr->x[end - 1] - dptr->x[end - 2]);
      }
      y[i] = total+0.5*(interp+ylast)*(xx-xtotal);
    }  // if( xx =  = 0.0 )
  }  // for( int i = 0; i < n; i++)
}
/*---------------------------------------------------------*/
	
