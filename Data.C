// Data.C

#include <iostream>
#include <iomanip>

#include <ctype.h>
#include <errno.h>
#include "Data.h"
#define SLENGTH 128

Data::Data() {
  n = 0;
  x = 0;
  y = 0;
}

Data::Data(int size) {
  if ( size > 0 && size < MAX_DATA_SIZE ) {
    n = size;
    x = new double[n];
    y = new double[n];
    
    for ( int i = 0; i < n; i++ ) {
      x[i] = 0.0;
      y[i] = 0.0;
    }
  }
}

Data::Data( const Data &init ) : n( init.n ) {
  x = new double[n];
  y = new double[n];
  for( int i = 0; i < n; i++ ) {
    x[i] = init.x[i];
    y[i] = init.y[i];
  }
}

// Instantiate a Data object using data read from a file.  First
// determine if the file exists Then determine if the file has data
// Data is first read into large presized arrays.  Then after the
// number of data elements is known, the data is copied to vectors
// precisely sized to hold that amount.  The large presized arrays are
// deleted.

Data::Data( const char *file_id ) {
  int i;

  char inputFilename[MAX_FILENAME_SIZE];
  cout << "Enter " << file_id << " file: ";
  cin >> inputFilename;

  ifstream inputFile( inputFilename , ios::in );
  if( !inputFile ) {			// File is absent
    cerr << "File " << inputFilename << " does not exist" << endl;
    cerr << "Exiting the program ... " << endl;
    exit( 1 );
  }
  double d1, d2;
  int num_float = 0;
		
  // First scan through header lines
  char buffer[SLENGTH];
		
  // nskip is the number of header lines
  int nskip=-1;
  while( ( num_float != 2 ) && !( inputFile.eof() ) ) {
    // Read in line
    inputFile.getline( buffer, SLENGTH );
			
      // Are tokens floating point?
    char *sptr=strtok( buffer, " \t\r" );
    num_float=0;
    while( sptr ) {       
      if( atof( sptr ) ) {	// Is a double
	sptr = strtok( NULL, " \t\r" );
	num_float++;
      } else {
	if( sptr[0] == '0' ) { // Is equal to zero
	  sptr = strtok( NULL, " \t\r" );
	  num_float++;
	} else {  // Is not a number
	  sptr=0;
	  num_float=0;
	}
      }
    }
    nskip++;
		
    i=1;
    while( ( inputFile >> d1 >> d2 ) )
      i++;
    n=i;
    inputFile.close();
		
    // cout << "n= " << n << endl;
		
    if( n > 0 ) {		// File has data
      x=new double[n];  // Size arrays
      assert(x != 0);
      y=new double[n];
      assert(y != 0);
			
      ifstream inputFile( inputFilename , ios::in );

      if( nskip > 0 ) {
	for( i = 0; i < nskip; i++)
	  inputFile.getline( buffer, SLENGTH );
      }
			
      for( i = 0; i < n; i++) {
	inputFile >> x[i] >> y[i];
      }
			
      inputFile.close();
    } else {
      cerr << "File contains no data!" << endl;
      exit(0);
    }
  }
}

Data::~Data() {
  if( x != 0 )
    delete [] x;
  if( y != 0 )
    delete [] y;
}

int Data::fill( const string &prompt ) {
  string	s;
  char		*cp1, *cp2, buff[100];
  float		f0, f1;

  cout << "Enter " << prompt << " file name: ";
  cin >> s;
  ifstream infile( s.c_str() );
  if ( !infile ) {
    cerr << "File " << s << " does not exist" << endl;
    return 1;
  }
  
  // Run through file to get number of comment and data lines.
  int	numcomment = 0, numdata = 0;

  while ( infile.getline( buff, 100 ))
    if (cp1 = strtok( buff, " \t\n" ))
      if ( !isdigit( *cp1 ) && (*cp1 != '.'))
	numcomment++;
      else
	numdata++;

//  infile.seekg( 0, ios::beg );
  infile.close();
  infile.open( s.c_str());
  // cout << "numcomment " << numcomment << ", numdata " << numdata << endl;

  // Read through data file, skipping header lines.
  int indx = 0;
  n = numdata;
  x = new double[numdata];
  y = new double[numdata];
  while ( infile.getline( buff, 100 )) {
    // cout << "buff >" << buff << "<" << endl;
    if (cp1 = strtok( buff, " \t\n" )) {
      // Definition of comment line: Starts with nondigit.
      if ( !isdigit( *cp1 ) && (*cp1 != '.')) {
	continue;
      }
      if (cp2 = strtok( NULL,  " \t\n" )) {
	f0 = atof( cp1 );
	f1 = atof( cp2 );
	x[indx] = (double)f0;
	y[indx] = (double)f1;
	// cout << " x >" << x << "<, y >" << y << "<" << endl;
	indx++;
      }
    }
  }
}

void Data::dump( void ) {
  for ( int i = 0; i < n; i++ ) {
    cout << setw(6) << setprecision(3) << i;
    cout << setw(10) << setprecision(3) << x[i];
    cout << setw(10) << setprecision(3) << y[i];
    cout << endl;
  }
}

/**** DATA::XEQUAL
 * Test to see if the x values of two data sets are equal.
 * This test is used to avoid unecessary function calls when
 * a reference tissue input function is used for Patlak or
 * Logan graphical analysis.
 */
bool Data::xEqual(const Data *dataComparedWith) const {
  if ( n != dataComparedWith->n )
    return false;
  for ( int i = 0; i < n; i++) {
    if ( x[i] != dataComparedWith->x[i] )
      return false;
  }
  return true;
}

/*---------------------------------------------------------*/
/**** DATA::WRITEDATA
 * For now this is just a debugging test function to ensure
 * Data has been properly read/processed.
 * Eventually, this will likely be used to print out the
 * original data and a corresponding model fit
 *****/
void Data::writeData(char *file_id) {
  char outputFilename[MAX_FILENAME_SIZE];
  cout << "Enter output file for the " << file_id << " : ";
  cin >> outputFilename;
  ofstream outputFile(outputFilename, ios::out);
  if( !outputFile ) {
    cerr << "Could not create output file" << endl;
    exit( 1 );
  }

  int i;
  for ( i = 0; i < n; i++ ) {
    outputFile.setf( ios::left );
    outputFile << setw(8) << i+1 
	       << setw(10) << x[i] 
	       << setw(10) << y[i] << endl;
  }
  outputFile.close();
}
