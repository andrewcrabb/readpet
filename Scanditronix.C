// Scanditronix.C
// GE 4096 PET scan subclass of PET.

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

#include "Scanditronix.h"
#include "Data.h"
#include "Model.h"
#include "ModelLogan.h"
#include "dbh.h"
#include "GE6.h"

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

Scanditronix::Scanditronix( void ) {
  meanFrame = 0;
}

int Scanditronix::isDataFile( string &filename ) {
  GE6		ge;

  return ge.isDataFile( filename.c_str() );
}

int Scanditronix::read( vector<string> &infiles, int options ) {
  GE6		*ge;
  ifstream	infile;

  for ( int i = 0; i < infiles.size(); i++ ) {
    infile.open( infiles[i].c_str() );
    if ( infile ) {
      // cout << "Opened " << infiles[i] << endl;
      ge = new GE6();
      ge->read( infile );
      frames.push_back( ge );
      infile.close();
      if ( i == 0 )
	makePrefix( ge->getPnm() );
    } else {
      return 1;
    }
  }

  _numFrame = infiles.size();
  _numSlice = NUMSLICE;
  _numImage = _numFrame * _numSlice;
  _numPixel = NUMPIXEL;
  return 0;  
}

int Scanditronix::writeSliceData( int fr, int sl, ofstream &ofile, int opt ) {
  Slice6	*sli = frames[fr]->getSlice( sl );

  return( sli->writeData( ofile, opt ));
}

int Scanditronix::parametric( int options, vector<int> &sli ) {
  GE6		*ge;
  int		pix, tsum, sl, append = 0, retn;
  short		*vptr, **vals;
  double	dsum, pixarray[200];
  double	*rslt = new double[2];
  float		lmin, lmax;
  
  PET::parametric( options, sli );
  ge = new GE6( *frames[0] );
  modMin =  1000.0f;
  modMax = -1000.0f;
  cout << "Modeling slices: ";
  for ( int slindx = 0; slindx < _slices.size(); slindx++ ) {
    lmin =  1000.0f;
    lmax = -1000.0f;
    sl = _slices[slindx];	
    for ( pix = 0; pix < _numPixel; pix++ ) {
      dsum = 0.0;
      for ( int fr = 0; fr < _numFrame; fr++ ) {
	ge = frames[fr];
	vals = ge->vals();
	vptr = vals[sl];
	pixarray[fr] = (double)vptr[pix];
	dsum += pixarray[fr];
      }
      tsum = int( dsum );
      if ( tsum > 0 )
	rslt = model->modelPixelFit( pixarray );
      else
	rslt[0] = rslt[1] = 0.0;	
      slopearr[pix] = rslt[0];
      intarr[pix] = rslt[1];
      lmin = ( rslt[0] < lmin ) ? rslt[0] : lmin;
      lmax = ( rslt[0] > lmax ) ? rslt[0] : lmax;
    }
    options |= PET::OPT_ANAL;
    Slice6 *slic = new Slice6( ge );
    slic->setSliceNumber( sl );
    slic->setData( slopearr, _numPixel );

//      img->setPixelRange( lmin, lmax );
    modMin = ( lmin < modMin ) ? lmin : modMin;
    modMax = ( lmax > modMax ) ? lmax : modMax;

    retn = slic->writeData( nSlope, options, append );
    append = 1;
    cout << sl << " ";
  }
  writeHeader( options );
  cout << endl;
  delete[] slopearr;
  delete[] intarr;
  return( retn );
}

int Scanditronix::makeMean( int options ) {
  Slice6	*sliptr;
  float		**sumvals;
  int		numpix = getImageX() * getImageY();
  int		i, sli;

  if ( frames.size() == 0 )
    return -1;
  meanFrame = new GE6( *frames[0] );

  // sumvals is a vol used to accumulate vals from each frame.
  sumvals = new float *[_numSlice];
  for ( i = 0; i < _numSlice; i++ ) {
    sumvals[i] = new float[numpix];
    for ( int pix = 0; pix < numpix; pix++ )
      sumvals[i][pix] = 0.0;
  }
  
  // Accumulate pixel vals over each frame.
  vector <short **> allvals;
  for ( i = 0; i < _numFrame; i++ )
    allvals.push_back( frames[i]->vals());

  map<vector<int>, float> factors;	// Index dim <frames, slices>.
  vector<int>	v(4);

  for ( int pix = 0; pix < numpix; pix++ )
    for ( sli = 0; sli < _numSlice; sli++ )
      for ( int frm = 0; frm < _numFrame; frm++ ) {
	v[0] = frm;
	v[1] = sli;
	// Fill in factors if not done before.
	if ( pix == 0 )
	  factors[v] = frames[frm]->getSlice( sli )->getMag() / 32000.0;
	// Add weighted pixel to sum.
	sumvals[sli][pix] += ( allvals[frm][sli][pix] * factors[v] );
      }

  // Sum weights over frames for each pixel in this slice.
  vector<float> weights( _numSlice, 0.0 );
  for ( int frm = 0; frm < _numFrame; frm++ ) {
    v[0] = frm;
    for ( sli = 0; sli < _numSlice; sli++ ) {
      v[1] = sli;	// Use v only to index over slices.
      weights[sli] += factors[v];
    }
  }

  float	weight;
  for ( sli = 0; sli < _numSlice; sli++ ) {
    weight = weights[sli];
    for ( int pix = 0; pix < numpix; pix++ )
      sumvals[sli][pix] /= weight;
  }
  
  // Store the newly calculated mean vals into the mean frame.
  for ( sli = 0; sli < _numSlice; sli++ )
    meanFrame->getSlice( sli )->setData( sumvals[sli], numpix );
  
  return 0;
}

int Scanditronix::writeMeanFrame( ofstream &outfile, int options ) {
  int		ret = 0;

  for ( int i = 0; i < _numSlice; i++ )
    if ( ret = meanFrame->getSlice( i )->writeData( outfile, options ))
      break;
  return ret;
}

// Methods overridden from class PET.

const string Scanditronix::getDataType( void ) {
  string *s = new string;
  return *s;
}

int Scanditronix::getImageX( void ) {
  return( frames.size() ? frames[0]->getPixelCount() : 0 );
}

int Scanditronix::getImageY( void ) {
  return( frames.size() ? frames[0]->getPixelCount() : 0 );
}

int Scanditronix::getNumSlice( void ) {
  return( frames.size() ? frames[0]->getNumSlices() : 0 );
}

int Scanditronix::getNumFrame( void ) {
  return 1;
}

int Scanditronix::getImgDepth( void ) {
  return 16;
}

float Scanditronix::getPixelWidth( void ) {
  return( frames.size() ? frames[0]->getPixelWidth() : 0.0 );
}

float Scanditronix::getPixelHeight( void ) {
  return( frames.size() ? frames[0]->getPixelHeight() : 0.0 );
}

float Scanditronix::getSliceThickness( void ) {
  return( frames.size() ? frames[0]->getSliceThickness() : 0.0 );
}

float Scanditronix::getMax( int fr, bool mean ) {
  float		ret = 0.0;

  if ( mean && meanFrame ) {
    ret = meanFrame->getMax();
  } else {
    if ( fr >= 0 && fr < _numFrame )
      ret =  frames[fr]->getMax(); 
  }
  return ret;
}

float Scanditronix::getMin( int fr, bool mean ) {
  float		ret = 0.0;

  if ( mean && meanFrame ) {
    ret = meanFrame->getMin();
  } else {
    if ( fr >= 0 && fr < _numFrame )
      ret =  frames[fr]->getMin(); 
  }
  return ret;
}

// Secs since midnight.

float Scanditronix::getScanTime( void ) {
  return frames[0]->scanTime();
}

// Secs since scan start.

float Scanditronix::getFrameStart( int fr ) {
  return frames[fr]->measureTime();
}

float Scanditronix::getFrameDurat( int fr ) {
  return frames[fr]->frameDuration();
}

const string Scanditronix::getPatientID( void ) {
  string *s;
  if ( frames.size() )
    s = new string( frames[0]->getPnm());
  else
    s = new string;
  s->erase(std::remove_if(s->begin(), s->end(), ::isspace), s->end());

  return *s;
}

