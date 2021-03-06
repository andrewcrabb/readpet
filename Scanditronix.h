// Scanditronix.h

// This is part of the readPET program.
// Copyright (C) 1999-2005, Andrew Crabb
//
// The portions of this program written by Andrew Crabb are free software;
// you may redistribute and/or modify them under the terms of the GNU 
// General Public License as published by the Free Software Foundation 
// (www.fsf.org).
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

#ifndef SCANDITRONIX_H
#define SCANDITRONIX_H

#include <vector>

#include "PET.h"
#include "GE6.h"
#include "Model.h"
#include "ModelLogan.h"

using namespace std;

class Scanditronix : public PET {
private:
  enum { NUMSLICE = 15, NUMPIXEL = 16384 };
  vector<GE6 *>	frames;
  GE6		*meanFrame;
public:
  Scanditronix( void );
  int	isDataFile( string &filename );
  int	read( vector<string> &infiles, int options );
  long	read( ifstream &input, int options ) { return 1; }
  int	writeSliceData( int fr, int sl, ofstream &outfile, int opt );
  int	parametric( int options, vector<int> &slices );
  int	makeMean( int options );
  int	writeMeanFrame( ofstream &outfile, int options );

  // Methods overridden from class PET.
  const string	getDataType( void );
  int		getImageX( void );
  int		getImageY( void );
  int		getNumSlice( void );
  int		getNumFrame( void );
  int		getImgDepth( void );
  float		getPixelWidth( void );
  float		getPixelHeight( void );
  float		getSliceThickness( void );
  float		getMax( int fr, bool mean = false );
  float		getMin( int fr, bool mean = false );
  float		getScanTime( void );
  float		getFrameStart( int fr );
  float		getFrameDurat( int fr );
  void		writeTimes( void ) {}	// Write temporal info file.
  const string	getPatientID( void );
  int		kludgeSetID( const string &newid ) {}	// Implement me.
};

#endif
