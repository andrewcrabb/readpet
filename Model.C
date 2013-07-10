// Model.C
// Base class for modeling functions.

#include <algorithm>
#include <vector>
#include <numeric>

#include "Model.h"

using namespace std;

bool unwanted( char c );

Model::Model( void ) {

}

Model::~Model( void ) {

}
/*---------------------------------------------------------*/
int Model::initModelPixelFit( Data *frameTimes ) {
  if (!(frameTimes->n)) {
    cerr << "frameTimes not initialized!" << endl;
    return( 1 );
  }
  assert( frameDuration = new double[frameTimes->n] );
  assert( fitThisData = new int[frameTimes->n] );
  assert( fitResult = new double[frameTimes->n] );

  copy( frameTimes->y, frameTimes->y + frameTimes->n, frameDuration );

  assert( tac = new Data( *frameTimes ) );
  assert( loganData = new Data(tac->n) );
  assert( z = new double[tac->n] );

  //DPTR IS A DATA POINTER, IT POINTS TO THE DATA TO BE FIT, WHICH
  //IN THIS CASE IS THE LOGAN TRANSFORMED DATA
  dptr = loganData;
}
/*---------------------------------------------------------*/
int Model::selectDataToFit( void ) {
  int		end = tac->n - 1, lwr = 0, upr = 0;
  double	duration = tac->x[end] + frameDuration[end] / 2.0;
  char		buff[100];
  vector<char>::iterator ptr;
  bool		invalid = true;

  while ( invalid ) {
    cout << "Enter time range (eg 0-90), study length " << duration << " minutes (<Return> to exit): ";
    cin.getline( buff, 99 );
    if ( !strlen( buff ))
      return 1;
    vector<char> v( buff, find( buff, buff + 99, '\0' ));
    ptr = remove_if( v.begin(), v.end(), unwanted );
    v.erase( ptr, v.end() );
    ptr = find( v.begin(), v.end(), '-' );
    if ( ptr < v.begin() || ptr >= v.end() ) {
      cout << "Error: Enter range separated by '-'" << endl;
      continue;
    }
    string s1( v.begin(), ptr );
    string s2( ptr + 1, v.end() );
    lwr = atoi( s1.c_str() );
    upr = atoi( s2.c_str() );
    invalid = false;
  }
  // Find the frames that fall within the scan range.
  int	i = 0, j = 0;
  vector<double> vi( tac->x, tac->x + tac->n );
  vector<double>::iterator ip1, ip2;
  ip1 = find_if( vi.begin(), vi.end(), 
		 bind1st( less_equal<double>(), (double)lwr ));
  ip2 = find_if( vi.begin(), vi.end(), 
		 bind1st( less_equal<double>(), (double)upr ));
  for (i = ip1 - vi.begin(), j = 0; i <= ip2 - vi.begin(); i++, j++)
    fitThisData[j]=i;
  nfit = ip2 - ip1;
  return 0;
  //NOTE RETURN=0 MEANS DATA WERE PROPERLY SELECTED!
}
/*---------------------------------------------------------*/
bool unwanted( char c ) {
  static string wanted( "0123456789-" );
  int pos = wanted.find( c );
  return ( pos < 0 || pos >= wanted.size() );
}
/*---------------------------------------------------------*/
int Model::loadInputFunction() {
  /**** This reads input function data.  It first determines
   * if the selected file exists, then a new Data object
   * is instantiated with Data(char *). 
   */
  int retn = 1;
  inputFunction = new Data;
  inputFunction->fill( "input function" );

  if ( inputFunction->n ) {
    if ( tac->n ) {
      initializeCalculation();
      retn = 0;
    } else {
      cerr << "Have an input function, but have not read in frameTimes!" << endl;
    }
  } else {
    cerr << "Input function data are absent" << endl;
  }
  //  cout << "Contents of inputFunction:" << endl;
  //inputFunction->dump();
  return retn;
}
/*---------------------------------------------------------*/
// initializeCalculation initializes values that are exclusively dependent
// on the inputfunction.  This speeds up pixel-by-pixel calculations since
// the input function is fixed for all pixels.

void Model::initializeCalculation( void ) {
  int i;
  assert( infuncIntegral = new double[tac->n] );

  //INTEGRATE INPUTFUNCTION TO TAC TIMES
  Data temp( *tac );
  temp.integrate( inputFunction );
  for( i = 0; i < loganData->n; i++)
    infuncIntegral[i] = temp.y[i];
}
