// LOGAN.H
// Graphical is a base class containing parameter information 
// that is fundamental to graphical analysis methods

#ifndef MODELLOGAN_H
#define MODELLOGAN_H

#include "Model.h"

class ModelLogan : public Model {
public:
  ModelLogan();
  ~ModelLogan();		  //Destructor
			      // Virtual functions!

  // Overridden virtual functions from base class Model.
  int		initModelPixelFit( Data * );
  double	*modelPixelFit(double *newdata);

  void loadTac();
  void loganTransform();
  void fit();
  void linearFit();
  void initializeParameters();
  void foo( void );
  void computeCorrelation();
  void printFit();

private:
  /**** Class Logan contains two data sets - inputFunction: which is
   * typically a plasma curve but may also be a tissue curve, and
   * tac: which will normally be a tissue time-activity curve.
   * These data are analyzed with some quantitative procedure (Logan)
   * that is described as follows:
   * LoganID is a string description of the Model
   * np is the number of parameters to be estimated
   * p and perr are the estimated parameter values and their errors
   * parameterID is a string description of the parameters
   * fitResult contains the estimates of tac->y according to the Model.
   */

  double correlation;

};

#endif
