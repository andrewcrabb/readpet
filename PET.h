// PET.h
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

#ifndef PET_H
#define PET_H

#include <vector>
#include <string>

using namespace std;

class Analyze;
class Model;

class PET {
 private:
 protected:
  enum		{ FRMINDX = 0, SLIINDX = 1 };
  enum		{ MAXFRAME = 100, MAXIMAGE = 2000 };

  int		_numFrame;	// Number of frames per study.
  int		_numImage;	// Number of slices per study.
  int		_numSlice;	// Number of slices per frame.
  int		_numPixel;	// Number of pixels per slice.
  Analyze	*analyze;
  string	_prefix;
  int		_opts;	     // Program-wide options, filled at construction.

  // Members common to derived classes for parametric modeling.
  char		nSlope[40], nInter[40];
  float		*slopearr, *intarr;
  vector<int>	_slices;
  Model		*model;		// Pointer to classes derived from Model.
  int		modelType;
  float		modMax, modMin;	// Extrema of modelled slices.

 public:
  enum		{ OPT_SHDR =   1,	// Print short header to screen.
		  OPT_LHDR =   2,	// Print long header to screen.
		  OPT_WRIT =   4,	// Write frames to disk.
		  OPT_MEAN =   8,	// Write mean image frame to disk.
		  OPT_MBQ  =  16,	// Use units of MBq/cc
		  OPT_VOLU =  32,	// Write as one 4D volume to disk.
		  OPT_ANAL =  64,	// Write Analyze headers to disk.
		  OPT_PARA = 128,	// Calculate parametric images.
		  OPT_DEBG = 256,	// Print debugging info.
		  OPT_TIME = 512,	// Write temporal info file.
		  OPT_IDEN = 1024 };	// New subject ident.
  enum		{ UNKNOWN = 0,		// PET file types.
		  ADVANCE = 1,
		  SCANDITRONIX = 2 };
  enum          { MODEL_UNKNOWN = 0,	// Model type.
		  MODEL_LOGAN = 1,
		  MODEL_PATLAK = 2 };
  enum		{ MBQ_TO_NCI = 27027 };	// Factor from MBq/cc to nCi/cc.

  // Non-overriddern functions.
//   PET( void );
  PET( int opt = 0 );
  ~PET( void );
  int		write( int options );
  int		writeMean( int options );
  void		error( const string &str1, const string &str2 );
  float		getFrameMid( int fr );		// Frame midpoint (sec).
  void		makePrefix( const char *str );	// Subject name for files.

  int		getNumModSlice( void );		// Modelled slices per frame.
  float		getModMax( void ) { return modMax; }
  float		getModMin( void ) { return modMin; }

  void  writeHeader( int options );

  // Virtual functions overridden by derived classes.
  virtual int	isDataFile( string &filename ) = 0;
  virtual int	read( vector<string> &infiles, int options ) = 0;
  virtual long	read( ifstream &input, int options ) = 0;
  virtual int	writeSliceData( int fr, int sl, ofstream &outfile, int opt) = 0;
  virtual int	writeMeanFrame( ofstream &outfile, int options ) = 0;
  virtual int	initializeParametric( int type );
  virtual int	parametric( int options, vector<int> &sli );
  virtual int	makeMean( int options ) = 0;

  // Utility get-routines called by Advance objects.
  virtual const string getDataType( void ) = 0;
  virtual int	getImageX( void ) = 0;		// Image array width.
  virtual int	getImageY( void ) = 0;		// Image array height.
  virtual int	getNumSlice( void ) = 0;	// Slices per frame.
  
  virtual int	getNumFrame( void ) = 0;	// Frames per study.
  virtual int	getImgDepth( void ) = 0;	// Bits per pixel.
  virtual float getPixelWidth( void ) = 0;	// Pixel X dim (mm).
  virtual float getPixelHeight( void ) = 0;	// Pixel Y dim (mm).
  virtual float getSliceThickness( void ) = 0;	// Pixel Z dim (mm).
  virtual float	getMax( int fr, bool mean = false ) = 0; // Frm/mean nCi/cc.
  virtual float	getMin( int fr, bool mean = false ) = 0; // Frm/mean nCi/cc.
  virtual float getScanTime( void) = 0;		// Secs since midnight.
  virtual float	getFrameStart( int fr ) = 0;	// Secs since scan start.
  virtual float	getFrameDurat( int fr ) = 0;	// Secs.
  virtual void	writeTimes( void ) = 0;		// Write temporal info file.
  // virtual const string getFrameDuratStr( int fr ) = 0;
  // virtual const string getFrameStartStr( int fr ) = 0;
  virtual const string getPatientID( void ) = 0;
  virtual int	kludgeSetID( const string &newid ) = 0;
};

#endif
