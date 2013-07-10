// PET.C
// Base class for PET time series studies.

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

#include <iostream>

#include "dbh.h"
#include "PET.h"
#include "Data.h"
#include "ModelLogan.h"
#include "ModelPatlak.h"

PET::PET( int opt ) {
  _opts = opt;
  analyze = new Analyze( 1 );
  _numFrame = _numImage = _numSlice = _numPixel = 0;
}

PET::~PET( void ) {
  // 
}

int PET::write( int options ) {
  int		sl, fr;
  ofstream	outfile;
  char		outbuff[100];
  string	patid( getPatientID() );
  string	outname( getPatientID() );
  string	patname( _prefix );

  cout << "PET::write(): " << _numFrame << " frames of " << _numSlice << " slices." << endl;
  if ( options & OPT_VOLU ) {
    // Using one output file.
    // string outname( _prefix + "." );
    // string outname(  + "." );
    outname.append( "." );
    outname.append( (options & OPT_ANAL) ? "img" : "raw");
    outfile.open( outname.c_str(), ios::binary );
    if ( !outfile.is_open() )
      error( "Cannot open output file", outname );

    // Write the Analyze header if required.
    if ( options & OPT_ANAL )
      analyze->writePET( this, outname, options, 0 );
  }

  // Run through each frame and write to disk.
  std::transform(patname.begin(), patname.end(), patname.begin(), 
		 (int(*)(int)) toupper);

  for ( fr = 0; fr < _numFrame; fr++ ) {
    if ( !( options & OPT_VOLU )) {
      // New output file per frame if not writing to one file.

      // Changed this 4/2/07 ahc.  Can't remember why I was using patid
      // rather than abbreviated name for Analyze files.
//       sprintf( outbuff, "%s_%02d.%s", 
// 	       patid.c_str(), fr, (options & OPT_ANAL) ? "img" : "raw" );
      sprintf( outbuff, "%s_%02d.%s", 
	       patname.c_str(), fr, (options & OPT_ANAL) ? "img" : "raw" );


      outfile.open( outbuff, ios::binary );
      if ( !outfile.is_open() )
 	error( "Cannot open output file", outbuff );

      // Write the Analyze header if required.
      if ( options & OPT_ANAL )
	analyze->writePET( this, outbuff, options, fr );
    }
    // Call virtual fn. for specific PET slices.
    for ( int sl = 0; sl < _numSlice; sl++ ) {
      writeSliceData( fr, sl, outfile, options );
    }
    if ( !( options & OPT_VOLU ))
      outfile.close();
    cout << ((fr + 1) % 10) << flush;
  }
  cout << endl;
  if ( outfile.is_open() )
    outfile.close();
  return 0;
}

int PET::writeMean( int options ) {
  ofstream	outfile;
  char		nam[100];
  int		ret = 0;

  sprintf( nam, "%s_mean.%s", _prefix.c_str(), (options & OPT_ANAL) ? "img" : "raw");
  outfile.open( nam, ios::binary );
  if ( !outfile.is_open() )
    error( "Cannot open output file", nam );

  // Write the Analyze header if required.
  if ( options & PET::OPT_ANAL )
    analyze->writePET( this, nam, options, 0 );
  ret = writeMeanFrame( outfile, options );
  outfile.close();
  return ret;
}

void PET::error( const string &str1, const string &str2 ) {
  cerr << "ERROR: " << str1 << " " << str2 << endl;
  exit( 1 );
}

// Set up data structures to modeling routine.
int PET::initializeParametric( int type ) {
  switch ( modelType = type ) {
  case MODEL_LOGAN:  
    model = new ModelLogan; 
    break;
  case MODEL_PATLAK: 
    model = new ModelPatlak; 
    break;
  default: 
    return -1;
  }

  // Fill in dat structure with methods from derived classes.
  float		start, durat;
  Data		dat( _numFrame );

  for ( int i = 0; i < _numFrame; i++ ) {
    dat.x[i] = getFrameMid( i ) / 60.0;
    dat.y[i] = getFrameDurat( i ) / 60.0;
  }
  return( model->initModelPixelFit( &dat ) );
}

float PET::getFrameMid( int fr ) {
  return getFrameStart( fr ) + getFrameDurat( fr ) / 2.0;
}

void PET::makePrefix( const char *str ) {
  char	prefix[100];

  strcpy( prefix, str );
  for ( int i = 0; i < 8 && prefix[i]; i++ ) {
    if ( isspace( prefix[i] ) | ispunct( prefix[i] )) {
      prefix[i] = '\0';
      break;
    } else {
      prefix[i] = tolower( prefix[i] );
    }
  }
  prefix[8] = '\0';
  _prefix.assign( prefix );
//   cout << "PET::makePrefix(" << str << "): >" << _prefix << "<" << endl;
}

int PET::getNumModSlice( void ) {
  return _slices.size();
}

int PET::parametric( int options, vector<int> &sli ) {

  // If slices is empty, no slices specified - model all slices.
  if ( sli.size() == 0 )
    for ( int i = 0; i < _numSlice; i++ )
      _slices.push_back( i );
  else
    for ( int i = 0; i < sli.size(); i++ )
      _slices.push_back( sli[i] );
  slopearr = new float[_numPixel];
  intarr = new float[_numPixel];
  sprintf( nSlope, "%s_slope.img", _prefix.c_str() );

  return 0;
}

void PET::writeHeader( int options ) {
  analyze->writePET( this, nSlope, options, 0 );
}  
