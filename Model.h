// Model.h
// Base class for modeling functions.

#ifndef MODEL_H
#define MODEL_H

#include "Data.h"

// Class Logan contains two data sets - inputFunction: which is
// typically a plasma curve but may also be a tissue curve, and tac:
// which will normally be a tissue time-activity curve.  These data
// are analyzed with some quantitative procedure (Logan) that is
// described as follows: LoganID is a string description of the Model
// np is the number of parameters to be estimated p and perr are the
// estimated parameter values and their errors parameterID is a string
// description of the parameters fitResult contains the estimates of
// tac->y according to the Model.

class Model {
private:
protected:
  int		np;			//number of parameters
  double	*p;			//parameter values
  double	*perr;			//parameter errors

  Data		*inputFunction;
  Data		*dptr;

  int		nfit;
  double	*frameDuration;
  int		*fitThisData;
  double	*fitResult;
  Data		*tac;
  Data		*loganData;
  double	sumxx;
  double	chisqr;
  double	*infuncIntegral;
  double *z;

public:
  Model( void );
  virtual ~Model( void );
  // Virtual functions overridden in derived classes.
  virtual int	 initModelPixelFit( Data * );
  virtual double *modelPixelFit(double *newdata) = 0;

  // Nonvirtual functions inherited by derived classes.
  int		selectDataToFit( void );
  int		loadInputFunction( void );
  void		initializeCalculation( void );
};

#endif
