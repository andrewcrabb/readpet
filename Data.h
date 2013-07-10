// DATA.H

#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

using namespace std;

#define MAX_DATA_SIZE 1024
#define MAX_STRING_LENGTH 128
#define MAX_FILENAME_SIZE 128
#define ABS(d) (d) > 0 ? (d):-(d)

#define STR_ARRAY_SIZE 25

/*
 * Declaration of the Data class
 * A Data object has two vectors of equal length that contain
 * data coordinates (e.g., Time, and Radioactivity Concentration)
 * the size of the vectors is also a private member of the class.
 * Currently, Data is a standalone class, i.e. no classes
 * are derived from Data.  The purpose of this class is to perform
 * any preprocessing of the data before they are used for modeling.
 * At that point, there is no need to further modify the data.
 * However, the Model class and its derived class NonLinear
 * still need access to the private members of Data.  Thus, those
 * classes are friends of 
 */

class Data {
public:
  Data();		// default constructor
  Data(int);            // constructor for a presized Data object
  Data(const Data &);   // copy constructor
  Data( const char *);		// read Data from file
  ~Data();              // destructor
	
  int fill( const string & );
  void dump( void );
  bool xEqual(const Data *) const;
	
  // I/O functions
  void writeData(char *);
	
  // Data processing functions
  void integrate(const Data *);

  // The members are also public.
  int    n;
  double *x;
  double *y;
};

#endif
