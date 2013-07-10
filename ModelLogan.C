// LOGAN.CPP

#include <stdio.h>

#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

#include "Model.h"
#include "ModelLogan.h"

using namespace std;
/*---------------------------------------------------------*/
ModelLogan::ModelLogan( void ) {
  loganData = 0;
  infuncIntegral = 0;
  z = 0;

  np = 2;
  assert( p = new double[np] );
  assert( perr = new double[np] );

  chisqr = 0.0;
}
/*---------------------------------------------------------*/
ModelLogan::~ModelLogan( void ) {
  int i;

  if( infuncIntegral != 0 )
    delete [] infuncIntegral;
  if( loganData != 0 )
    delete loganData;

  if( fitResult )
    delete [] fitResult;
  if( p )
    delete [] p;
  if( perr )
    delete [] perr;
  if( fitThisData )
    delete [] fitThisData;
  if( frameDuration )
    delete [] frameDuration;

  if( tac )
    delete tac;
  if( inputFunction )
    delete inputFunction;
}
/*---------------------------------------------------------*/
// initModelPixelFit()
// Overrides virtual function in base class Model.

int ModelLogan::initModelPixelFit( Data *frameTimes ) {
  ostream_iterator<double> outiter( cout, " " );

  // Base class performs std functions.
  Model::initModelPixelFit( frameTimes );

 if ( selectDataToFit() )
   return 1;

 //IF DATA ARE PROPERLY SELECTED, LOAD INPUT FUNCTION AND RETURN 0
 loadInputFunction();

 for( int i = 0; i < frameTimes->n; i++ )
   loganData->x[i] = infuncIntegral[i];

 cout << "Nfit = " << nfit << endl;
 sumxx = 0.0;
 for( int i = 0; i < nfit; i++)
   {
     sumxx+=loganData->x[fitThisData[i]]*loganData->x[fitThisData[i]];
   }

 // cout << "Contents of loganData : " << endl;
 // loganData->dump();
 return 0;

  /*  if ( !selectDataToFit() )
    return( loadInputFunction() );
    return 1; */
}

/*---------------------------------------------------------*/
void ModelLogan::printFit( void ) {
  int i, j;
  double denom;
  char outputFilename[MAX_FILENAME_SIZE];
  char fitFilename[MAX_FILENAME_SIZE];
  char paramFilename[MAX_FILENAME_SIZE];

  cout << "Enter output file (No extension): ";
  cin >> outputFilename;

  strcpy( fitFilename, outputFilename );
  strcat( fitFilename, ".fit" );

  strcpy( paramFilename, outputFilename );
  strcat( paramFilename, ".par" );

  ofstream outputFile( fitFilename, ios::out );
  if( !outputFile ) {
    cerr << "Could not create output file" << endl;
  } else {
    for( i = 0; i < (dptr->n); i++ ) {
      outputFile << setprecision(5) << setw(10) << dptr->x[i] << "  "
		 << setprecision(5) << setw(10) << dptr->y[i] << "  "
		 << setprecision(5) << setw(10) << fitResult[i] << endl;
    }
    outputFile.close();
  }

  ofstream paramFile( paramFilename, ios::out );
  if( !paramFile ) {
    cerr << "Could not create output file" << endl;
  } else {
    paramFile << "Analysis method: Logan" << endl;

    for ( i = 0; i < np; i++ ) {
      paramFile << "P[" << i+1 << "] = " << setprecision(4) << setw(10) << p[i];
      paramFile << " +/- " << setprecision(4) << setw(10) << perr[i] << endl;
    }
    paramFile << "Chisqr = " << chisqr << endl;
    paramFile << "Linear correlation coefficient = " << correlation << endl;
  }
}


/*---------------------------------------------------------*/
/**** LOGANTRANSFORM
 * This function takes a time-activity curve and an associated
 * input function and computes the Logan transformation of the
 * data (Logan et al., 1991 J. Cereb. Blood Flow Metab.)
 * For time-activity curve TAC, and input function INFUNC, the
 * Logan transformation is: y=Integral(TAC)/TAC(t) where t is
 * time, and x=Integral(INFUNC)/TAC(t).
*****/
void ModelLogan::loganTransform() {
  /**** This takes the time-activity curve (TAC) and infuncIntegral
   * (previously calculated in initializeCalculation) and computes
   * the Logan transformation of the data.
	*/

  Data temp(*tac);             
  temp.integrate(tac);
  int i;

  /*  for( i = 0; i < loganData->n; i++ ) {
    if( tac->y[i] > 1e-8 ) {
      loganData->x[i] = infuncIntegral[i] / tac->y[i];
      loganData->y[i] = temp.y[i] / tac->y[i];
    } else {
      loganData->x[i] = 0.0;
      loganData->y[i] = 0.0;
    }
    }*/

  for( i = 0; i < loganData->n; i++ )
    {
      loganData->y[i] = temp.y[i];
      z[i] = tac->y[i];
    }
}
/*---------------------------------------------------------*/	

double *ModelLogan::modelPixelFit( double *newdata ) {

  for ( int i = 0; i < tac->n; i++ ) {
//  printf( "%8.3f\n", newdata[i] );
// FIRST STUFF DATA INTO TAC VECTOR
    tac->y[i] = newdata[i];
  }
  loganTransform();
  fit();
  //  computeCorrelation();
  return p;
};

/*---------------------------------------------------------*/	
void ModelLogan::computeCorrelation( void ) {
  double xmean, ymean;
  double xsum, ysum;
  double xdiffsum2, ydiffsum2;
  int i, indx;

  xsum = ysum = 0.0;
  for ( i = 0; i < nfit; i++ ) {
    indx = fitThisData[i];
    xsum += dptr->x[ indx ];
    ysum += dptr->y[ indx ];
  }
  xmean = xsum / nfit;
  ymean = ysum / nfit;

  correlation = 0.0;
  xdiffsum2 = 0.0;
  ydiffsum2 = 0.0;

  for ( i = 0; i < nfit; i++ ) {
    indx = fitThisData[i];
    correlation += ( dptr->x[indx] - xmean )* ( dptr->y[indx] - ymean );
    xdiffsum2 += pow(( dptr->x[indx] - xmean ), 2.0 );
    ydiffsum2 += pow(( dptr->y[indx] - ymean ), 2.0 );
  }
  correlation /= sqrt( xdiffsum2 * ydiffsum2 );
}

/*---------------------------------------------------------*/
void ModelLogan::foo( void ) {
  int i;
  char user_input[80];
  // char *tok = ",-";
  // char *digits = "1234567890.";
  char strtest[20] = " ";
  strcat( strtest, ",-" );
  strcat( strtest, "1234567890." );
  strcat( strtest, "\t" );
  double startime, stoptime;
  char ui_char;

  int end=tac->n-1;
  double study_duration=tac->x[end]+frameDuration[end]/2.;
  cin.getline( user_input, 80 );
  cout << "Select time range (e.g. 0-90), study length is " ;
  cout << study_duration << " minutes: ";
  cin.getline( user_input, 80 );

  ui_char = user_input[0];
  i = 0;
  while( ui_char != '\0' && ( memchr( strtest, ui_char, 20 ) != NULL ) )
    {
      i++;
      ui_char=user_input[i];
    }

  if( ui_char != '\0' )
    {
      cerr << "User input is not in proper format, please try again." << endl;
      cout << "Select time range to fit, the study length is " ;
      cout << study_duration << " minutes: ";
      cin.getline( user_input, 80 );
    }

  char *sptr = strtok( user_input, "-" );
  startime = atof( sptr );
  sptr = strtok( NULL, "-" );
  stoptime = atof( sptr );

  if( ( startime < 0 ) || ( startime >= study_duration )) // Use default
    {
      startime=tac->x[0]-frameDuration[0]/2.;
      stoptime=study_duration;
      nfit=tac->n;      
    }
  else  // Use a subset of the data
    {
      if( stoptime > study_duration )
	stoptime=study_duration;
      else if( stoptime <= startime )
	{
	  cerr << "Invalid time range selected!" << endl;
	  cerr << "Exiting the program ... " << endl;
	  exit(1);
	}
    }

  int pos, nstop, nstart;
  /* Loop until the first scan following the selected start time
   * is reached.  This is the first fitted frame. */ 
  if( (stoptime > startime) && (startime < tac->x[end]) )
    {
      pos=0;
      while( ( pos < end ) && ( tac->x[pos] < startime ) )
	{
	  pos++;
	}
      nstart=pos;

      pos=0;
      while( ( pos < end ) && ( tac->x[pos] <= stoptime ) )
	{
	  pos++;
	}
      if( tac->x[pos] > stoptime )
	pos--;
      nstop=pos;
    }

  if( (stoptime <= startime) || (startime >= tac->x[end]) || 
      (nstop <= nstart ) )
    {
      cerr << "Invalid time range selected!" << endl;
      cerr << "Exiting the program ... " << endl;
      exit(1);
    }
  else
    {
      nfit = 0;
      for( i = nstart; i <= nstop; i++ )
	{
	  fitThisData[nfit]=i;
	  nfit++;
	}
      //cout << "Nfit =" << nfit << "Nstart =" << nstart;
      //cout << ", Nstop =" << nstop << endl;
    }
}
/*---------------------------------------------------------*/

// This performs a simple linear fit.  It is assumed that there is no
// error in x values.  This is virtual function fit (default) in class
// Model.  Note that even though class Model includes two Data objects
// as private class members, i.e. tac and inputFunciton, the linear
// fit function operates on the Data object pointed to by dptr, which
// usually will NOT be tac.  Instead, the linear fit will usually
// operate on transformed data - e.g. Logan or Patlak, that is derived
// from the original TAC and input function.

void ModelLogan::fit( void ) {
  int		i, indx;
  double	denom;
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
    //perr[0] = sqrt( sumzz / denom );
    //perr[1] = sqrt( sumxx / denom );
  } else {
    p[0] = p[1] = perr[0] = perr[1] = 0.0;
  }

  /*  for ( i = 0; i < dptr->n; i++) 
    fitResult[i] = p[0] * dptr->x[i] + p[1] * z[i];

  chisqr=0.0;
  for ( i = 0; i < nfit; i++ ) {
    indx = fitThisData[i];
    diff = dptr->y[indx] - fitResult[indx];
    chisqr += diff * diff;
    }*/
}
