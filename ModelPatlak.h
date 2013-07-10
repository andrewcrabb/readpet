// ModelPatlak.h
// Subclass of Model.

#ifndef MODELPATLAK_H
#define MODELPATLAK_H

#include "Data.h"
#include "Model.h"

class ModelPatlak : public Model {
private:
  double	*z;
  Data		*frameStart, *frameStop;
  void		bilinearFit( void );
public:
  ModelPatlak( void );
  ~ModelPatlak( void );
  // Overridden virtual functions from base classes.
  int		initModelPixelFit( Data * );
  double	*modelPixelFit(double *newdata);
  // Nonvirtual functions inherited by derived classes.
};

#endif
