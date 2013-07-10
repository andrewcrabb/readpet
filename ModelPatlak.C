// ModelPatlak.C
// Subclass of Model.

#include "ModelPatlak.h"

ModelPatlak::ModelPatlak( void ) {

}

ModelPatlak::~ModelPatlak( void ) {
  if ( frameStart )
    delete frameStart;
  if ( frameStop )
    delete frameStop;
}

double *ModelPatlak::modelPixelFit( double *newdata ) {
  for ( int i = 0; i < dptr->n; i++ )
    dptr->y[i] = newdata[i];
  bilinearFit();
  return p;
};

int ModelPatlak::initModelPixelFit( Data *frameTimes ) {
  int i;

  // Base class performs std functions.
  Model::initModelPixelFit( frameTimes );

  assert( frameStart = new Data(tac->n) );
  assert( frameStop = new Data(tac->n) );

  double step;
  for ( i = 0; i < tac->n; i++ ) {
    step = frameDuration[i] / 2.0;
    frameStart->x[i] = tac->x[i] - step;
    frameStop->x[i] = tac->x[i] + step;
  }

  selectDataToFit();
  loadInputFunction();
  
  assert( z = new double[ tac->n ] );
  if( tac->xEqual( inputFunction ) ) {
    for( i = 0; i < tac->n; i++ )
      z[i] = inputFunction->y[i];
  } else {
    frameStart->integrate( inputFunction );
    frameStop->integrate( inputFunction );
      
    for( i = 0; i < tac->n; i++ )
      z[i] = ( frameStop->y[i] - frameStart->y[i] ) / frameDuration[i];
  }

  Data temp( *tac );
  temp.integrate( inputFunction);

  for ( i = 0; i < dptr->n; i++)
    dptr->x[i] = temp.y[i];

  sumxx = 0.0;
  for ( i = 0; i < nfit; i++ )
    sumxx += dptr->x[fitThisData[i]] * dptr->x[fitThisData[i]];
  return 0;
}

void ModelPatlak::bilinearFit( void ) {
  int		i, indx;
  double	diff, denom;
  double	sumxy=0.0, sumzy=0.0, sumzz=0.0, sumxz=0.0;

  for ( i = 0; i < nfit; i++ ) {
    indx = fitThisData[i];
    sumxy += dptr->x[indx] * dptr->y[indx];
    sumxz += dptr->x[indx] * z[indx];
    sumzy += dptr->y[indx] * z[indx];
    sumzz += z[indx] * z[indx];
  }

  denom = sumxx * sumzz - sumxz * sumxz;
  if ( denom > 1e-12 ) {
    p[0] = ( sumzz * sumxy - sumxz * sumzy ) / denom;
    p[1] = ( sumxx * sumzy - sumxz * sumxy ) / denom;
    perr[0] = sqrt( sumzz / denom );
    perr[1] = sqrt( sumxx / denom );
  } else {
    p[0] = p[1] = perr[0] = perr[1] = 0.0;
  }

  for ( i = 0; i < dptr->n; i++) 
    fitResult[i] = p[0] * dptr->x[i] + p[1] * z[i];

  chisqr=0.0;
  for ( i = 0; i < nfit; i++ ) {
    indx = fitThisData[i];
    diff = dptr->y[indx] - fitResult[indx];
    chisqr += diff * diff;
  }
}
