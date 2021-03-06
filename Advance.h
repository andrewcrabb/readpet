// Advance.h
// Base class for a PET study time sequence (1 or more frames).

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

#ifndef ADVANCE_H
#define ADVANCE_H

#include <vector>
#include <string>

#include "PET.h"
#include "Header.h"

using namespace std;

class Analyze;
class Model;
class HeaderGroup;
class ImageGroup;
class DateTime;

class Advance : public PET {
 private:
  static const int	NUM_ADVANCE_PIXEL = 16384;
  map<string, HeaderGroup *> _groups;	// Defns of all, and vals of non Image.
  ImageGroup	*_meanFrame;
  DateTime	*_date;
  string	_kludgeNewID;

  // Non-inherited member functions.
  int		parseGroups( ifstream &input, int options );
  void		listGroups( void );
  int		readGroups( ifstream &input, int options );
  int		readHeaderLine( const string &line, vector<string> &tokens );
  void		printGroups( int options );
  const string	getValue( const string &group, const string &element );
 protected:
 public:
		Advance( void );
		Advance( int opt );
		~Advance( void );

  // Methods inherited from base class PET.
  int		read( vector<string> &infiles, int options );
  long		read( ifstream &input, int options );
  void		calculateRange( int options );
  int		isDataFile( string &filename );
  int		writeSliceData( int fr, int sl, ofstream &outfile, int opt);
  int		writeMeanFrame( ofstream &outfile, int options );
  // int		initializeParametric( int type );
  int		parametric( int options, vector<int> &sli );
  int		makeMean( int options );

  // Utility get-routines called by Advance objects.
  const string getDataType( void );
  int		getImageX( void );		// Image array width.
  int		getImageY( void );		// Image array height.
  int		getNumSlice( void );		// Slices per frame.
  int		getNumFrame( void );		// Frames per study.
  int		getImgDepth( void );		// Bits per pixel.
  float		getPixelWidth( void );		// Pixel X dim (mm).
  float		getPixelHeight( void );		// Pixel Y dim (mm).
  float		getSliceThickness( void );	// Pixel Z dim (mm).
  float		getMax( int fr, bool mean = false ); // Frm/mean nCi/cc.
  float		getMin( int fr, bool mean = false ); // Frm/mean nCi/cc.
  float		getScanTime( void);		// Secs since midnight.
  float		getFrameStart( int fr );	// Secs since scan start.
  float		getFrameDurat( int fr );	// Secs.
  virtual void writeTimes( void );		// Write temporal info file.
  const string getPatientID( void );
  int		kludgeSetID( const string &newid );
  int		frameIndex( const string &frameStr );
};

// Utility class for processing date/time strings from Advance headers.
// Format of date/time string is '2000-09-14 08:28:36'.

class AdvanceDate {
private:
  int		_year, _month, _day;
  int		_hour, _minute, _second;
public:
		AdvanceDate( void );
		AdvanceDate( string datestr );
//   int		AdvanceDate::toSec( void );
//   long		AdvanceDate::operator-( AdvanceDate &lhs );
  int		toSec( void );
  long		operator-( AdvanceDate &lhs );
};

#endif
