// Advance.C
// Container class for all the objects in a GE Advance PET scan.
 
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

#include <stdio.h>
#include <ctype.h>
#include <assert.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>

#include "Model.h"
#include "ModelLogan.h"
#include "GEtypes.h"
#include "idbConstants.h"
#include "Advance.h"
#include "dbh.h"
#include "Timer.h"
#include "Data.h"

using namespace std;

Advance::Advance( void ) : PET() {
  _meanFrame = 0;
}

Advance::Advance( int opt ) : PET( opt ) {
  _meanFrame = 0;
}

Advance::~Advance( void ) {
  for (map<string, HeaderGroup *>::iterator iter = _groups.begin(); 
       iter != _groups.end(); iter++) {
    delete (*iter).second;
  }
//   for (vector<HeaderGroup *>::iterator iter = _images.begin(); 
//        iter != _images.end(); iter++) {
//     delete *iter;
//   }
}

// read
// opts: Array of input file names (only first used for Advance)
// Returns: 0 on success otherwise 1.

int Advance::read( vector<string> &infiles, int options ) {
  const char	*fname = infiles[0].c_str();
  ifstream	input( fname, ios::binary );

  if ( input ) {
    return read( input, options );
  } else {
    cerr << "Can't open file " << fname << " for input\n" << endl;
    return 1;
  }
}

long Advance::read( ifstream &input, int options ) {
  Timer		s, t;
  int		i, pos, imagetime = 0;

  t.start();
  // Read export header information
  parseGroups( input, options );
//   listGroups();
  readGroups( input, options );
  calculateRange( options );
  makePrefix( getValue( "patient", "patient_name" ).c_str() );
  printGroups( options );

  t.end();
  cout << "Advance::read took " << t.elapse() << " ms" << endl;
  return( 0 );
}

// Determine the min and max over all slices in each frame (nCi/cc).
// NB: Although vals always in correct units, stored min/max are MBQ.

void Advance::calculateRange( int options ) {
  int		sl, fr;
  float		frmin, frmax;
  float		slmin, slmax;
  float		factor = ( options & OPT_MBQ ) ? 1.0 : MBQ_TO_NCI;
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  FrameGroup	*frameGroup = ( FrameGroup * )_groups["frame"];

  _numFrame = getNumFrame();
  _numSlice = getNumSlice();
  _numImage = _numFrame * _numSlice;
  _numPixel = NUM_ADVANCE_PIXEL;

  for ( fr = 0; fr < getNumFrame(); fr++ ) {
    frmin = imageGroup->getMin( fr ) * factor;
    frmax = imageGroup->getMax( fr ) * factor;
//     cout << "Advance::calculateRange(" << fr << "): factor " << factor << "(" << frmax << ", " << frmin << ")" << endl;
    frameGroup->setRange( fr, frmax, frmin );
  }
}

// Methods inherited from base class PET.

// Return 1 if this is an Advance data file.
int Advance::isDataFile( string &filename ) {
  string	buff;
  ifstream	infile( filename.c_str() );
  int		ret = 1;
  
  if ( infile.good() ) {
    getline( infile, buff );
    ret = !( buff.compare( 0, 8, "GEMS PET" ));
  }
  return ret;
}

// Write given slice to given file.  Note that sl param indexed from 0
// and slice order is reversed.

int Advance::writeSliceData( int fr, int sl, ofstream &outfile, int opt ) {
  ImageGroup	*imageGroup = (ImageGroup *)_groups["image"];
  int		slice = _numSlice - sl;

  return( imageGroup->writeData( fr, slice, outfile, opt ));
}

int Advance::makeMean( int options ) {
  ImageGroup	*imageGroup = (ImageGroup *)_groups["image"];

  _meanFrame = imageGroup->makeMean();
  return 0;
}

int Advance::writeMeanFrame( ofstream &outfile, int options ) {
  return( _meanFrame->writeMean( outfile, options ));
}

// int Advance::initializeParametric( int type ) {
//   cout << "############ Advance::initializeParametric() ############" << endl;
//   return( 0 );
// }

int Advance::parametric( int options, vector<int> &sli ) {
  cout << "############ Advance::parametric() ############" << endl;
  PET::parametric( options, sli );
  
  cout << "Advance::parametric(";
  for ( int slindx = 0; slindx < _slices.size(); slindx++ ) {
    if (slindx > 0) {
      cout << " ";
    }
    cout << _slices[slindx];
  }
  cout << ")" << endl;

  return( 0 );

//   double	pixarray[200];
//   double	*rslt = new double[2];
//   int		pix;
//   vector<int>	v(10);
//   GE_IMAGE	*img;
//   int		retn = 0;
//   float		slope, inter;
//   float		lmin, lmax;

//   // Call to parent class to perform common routines.
//   PET::parametric( options, sli );
//   // Use existing slice as model for new parametric slices.
//   v[SLIINDX] = 1;
//   v[FRMINDX] = 0;
//   // Model and write one slice at a time.
//   img = new GE_IMAGE( *mapping[v] );
//   // Call modeling functions for each pixel array over time.
//   int sl, append = 0;
//   modMin =  1000.0f;
//   modMax = -1000.0f;

//   cout << "Modeling slices: ";
//   for ( int slindx = 0; slindx < slices.size(); slindx++ ) {
//     // Slice index starts at 1, so slice 0 (inferior) is slice[numSlice].
//     sl = numSlice - slices[slindx];	
//     cout  << slices[slindx] << " ";
//     v[SLIINDX] = sl;
//     // Iterate over each pixel in this 128x128 slice.
//     lmin =  1000.0f;
//     lmax = -1000.0f;
//     for ( pix = 0; pix < numPixel; pix++ ) {
//       // Iterate over each frame for this pixel value.
//       for ( int fr = 0; fr < numFrame; fr++ ) {
//  	v[FRMINDX] = fr;
// 	ge_image = mapping[v];
// 	pixarray[fr] = (double)ge_image->pixValue( pix, options );
//       }
//       rslt = model->modelPixelFit( pixarray );
//       slope = rslt[0];
//       inter = rslt[1];
//       // This should be slopearr[pix] - Test all cases.
//         slopearr[numPixel - pix] = slope;
// //        slopearr[numPixel] = slope;
//       intarr[pix] = inter;
//       lmin = ( slope < lmin ) ? slope : lmin;
//       lmax = ( slope > lmax ) ? slope : lmax;
//     }
    
//     // ******************** ARBITRARY SCALING ********************
//     // Stored data +ve range is 0..32767.  -ve range by same scale.
//     // Additional scale by 100 since parametric images are 0..10.
//     // ******************** ARBITRARY SCALING ********************
//     float factor = 32767.0f / lmax;
//     for ( pix = 0; pix < numPixel; pix++ ) 
//       slopearr[pix] *= factor;
//     img->setPixelRange( lmin, lmax );
//     modMin = ( lmin < modMin ) ? lmin : modMin;
//     modMax = ( lmax > modMax ) ? lmax : modMax;
      
//     // Parametric slice is a clone of an existing slice for header info.
//     options |= OPT_ANAL;
//     img->setSliceNumber( sl );		// Set slice no to correct val.
//     img->setData( slopearr, numPixel );

//     // Write Analyze data files.
//     retn = img->writeData( nSlope, options, append );
//     append = 1;
//   }
//   cout << endl;

//   // Modelled vol range is known from slices - goes in header.
//   writeHeader( options );
//   delete[] slopearr;
//   delete[] intarr;
//   return( retn );
}

const string Advance::getDataType( void ) {
  return string( "SHORT" );
}

int Advance::getImageX( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getImageX();
}

int Advance::getImageY( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getImageY();
}

int Advance::getNumSlice( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getNumSlice();
}
  
int Advance::getNumFrame( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getNumFrame();
}

int Advance::getImgDepth( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getImgDepth();
}

float Advance::getPixelWidth( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getPixelWidth();
}

float Advance::getPixelHeight( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getPixelHeight();
  return( 0.0 );
}

float Advance::getSliceThickness( void ) {
  ImageGroup	*imageGroup = ( ImageGroup * )_groups["image"];
  return imageGroup->getSliceThickness();
  return( 0.0 );
}

float Advance::getScanTime( void) {
  return (float)_date->toSec();
}

float Advance::getFrameStart( int fr ) {
  string	scanDateStr = getValue( "scan", "scan_datetime" );
  AdvanceDate	scanDate( scanDateStr );
  FrameGroup	*frames = (FrameGroup *)_groups["frame"];
  string	acqStartStr = frames->valueOfFrame( "acq_start", fr );
  AdvanceDate	acqStart( acqStartStr );
  long		diffSec = acqStart - scanDate;
  
//   cout << "Advance::getFrameStart(" << fr << "): " << scanDateStr << ", " << acqStartStr << ": " << diffSec << endl;

  return (float)diffSec;
}

float Advance::getFrameDurat( int fr ) {
  FrameGroup	*frames = (FrameGroup *)_groups["frame"];
  string	acqDuratStr = frames->valueOfFrame( "acq_duration", fr );
  float		durat;

  sscanf( acqDuratStr.c_str(), "%f", &durat );
//   cout << "Advance::getFrameDurat(" << fr << "): " << acqDuratStr << ": " << durat << endl;

  return( durat );
}

const string Advance::getPatientID( void ) {
  if ( _kludgeNewID.size() ) {
    return _kludgeNewID;
  } else {
    return string( getValue( "patient", "patient_identifier" ));
  }
}

int Advance::kludgeSetID( const string &newid ) {
  _kludgeNewID = newid;
}

float Advance::getMax( int fr, bool mean ) {
  float		ret = 0.0;

  if ( mean && _meanFrame ) {
    ret = _meanFrame->getMax();
  } else {
    if ( fr >= 0 && fr < getNumFrame() ) {
      ImageGroup *imageGroup = ( ImageGroup * )_groups["image"];
      ret = imageGroup->getMax( fr );
    }
  }
  
  if (!( _opts & PET::OPT_MBQ ))
    ret *= (float)MBQ_TO_NCI;
  // cout << "Advance::getMax(" << fr << ", " << mean << ") returrning " << ret << endl;
  return ret;
}

float Advance::getMin( int fr, bool mean ) {
  float		ret = 0.0;

  if ( mean && _meanFrame ) {
    ret = _meanFrame->getMin();
  } else {
    if ( fr >= 0 && fr < getNumFrame() ) {
      ImageGroup *imageGroup = ( ImageGroup * )_groups["image"];
      ret = imageGroup->getMin( fr );
    }
  }
  
  if (!( _opts & PET::OPT_MBQ ))
    ret *= (float)MBQ_TO_NCI;
  // cout << "Advance::getMin(" << fr << ", " << mean << ") returrning " << ret << endl;
  return ret;
}

// ------------------------------------------------------------
// Non-inherited member functions.
// ------------------------------------------------------------

// New members that came out of class Header.
// Read, parse, and store header element defns.  Stored 1 per line in format:
// name|element1|element2| ... |element9|

int Advance::parseGroups( ifstream &input, int options ) {
  int		pos, indx, lin = 0;
  string	line, token, groupname;
  vector<string> tokens;
  HeaderGroup	*group;
  
  getline( input, line );
  while ( line.length() > 1 ) {
    if ( lin >= 8 ) {
      // Parse this line for header element titles.
      readHeaderLine( line, tokens );
      groupname.assign( tokens[0] );
      
      if ( groupname.compare( "image" ) == 0 ) {
	group = new ImageGroup( groupname, options );
      } else if ( groupname.compare( "frame" ) == 0 ) {
	group = new FrameGroup( groupname, options );
      } else if ( groupname.compare( "countrate" ) == 0 ) {
	group = new CountrateGroup( groupname, options );
      }  else if ( groupname.compare( "imageset" ) == 0 ) {
	group = new ImagesetGroup( groupname, options );
      } else {
	group = new HeaderGroup( groupname, options );
      }
      // Add elements to each group object, and define indexes.
      group->addElements( tokens );
      group->identElements();
      // Finished all HeaderElements in this line; store HeaderGroup.
      _groups[groupname] = group;
    }
    getline( input, line );
    lin++;
  }
  return 0;
}

void Advance::listGroups( void ) {
   cout << "Advance::listGroups() begin **************************" << endl;
  for ( map<string, HeaderGroup *>::iterator iter = _groups.begin();
	iter != _groups.end(); iter++ ) {
    string	groupName, elemNames;
    const vector<string> *elementNames = (*iter).second->elementNames();

    groupName = (*iter).second->name();
    ostringstream ostr;
    ostream_iterator<string> outiter(ostr, " ");
    copy( elementNames->begin(), elementNames->end(), outiter );
//     cout << "** Group " << groupName << " has " << elementNames->size() << " members:\n" << ostr.str() << endl;
     cout << "** Group " << groupName << " has " << elementNames->size() << " members" << endl;
  }
   cout << "Advance::listGroups() end **************************" << endl;
}

int Advance::readGroups( ifstream &input, int options ) {
  string	line;
  int		indx;
  string	name, tmp;
  vector<string> tokens;

  // Process each line.  Each element sets stream appropriately.
  // cout << "Advance::readGroups() begin **************************" << endl;
  int cnt = 0;
  while ( getline( input, line )) {
    // cout << "Advance::readGroups(" << cnt << "): " << line.length() << endl;
    readHeaderLine( line, tokens );
    name = tokens[0];
    _groups[name]->setElements( tokens, input );
    cnt++;
  }
  // cout << "Advance::readGroups() read " << cnt << " lines" << endl;

  // Have now read all header groups.  Multiple Frame groups need to be 
  // sorted by start time, then Image groups can determine their frame no.
  _groups["frame"]->sortMembers( this );
  _groups["image"]->sortMembers( this );

  // Get dimensions etc from frame and image groups.
  ImageGroup *imageGroup = ( ImageGroup * )_groups["image"];
  imageGroup->calculateDimensions();

  // Date and time are needed later.
  _date = new DateTime( _groups["scan"]->valueOf( "scan_datetime" ));
  _date->parse();

  // cout << "Advance::readGroups() end **************************" << endl;
  return( 0 );
}

int Advance::readHeaderLine( const string &line, vector<string> &tokens ) {
  int		indx, pos = 0;
  string	token;

  tokens.erase( tokens.begin(), tokens.end() );
  indx = line.find_first_of( "|", pos );
  while ( indx > 0 ) {
    token = line.substr( pos, ( indx - pos ));
    pos = indx + 1;
    indx = line.find_first_of( "|", pos );
    tokens.push_back( token );
  }
  return( 0 );
}

void Advance::printGroups( int options ) {
  HeaderGroup	*group;
  map<string, HeaderGroup *>::iterator iter;

  if ( _opts & PET::OPT_SHDR ) {
    int l = 0;
    for ( iter = _groups.begin();	iter != _groups.end(); iter++ ) {
      group = (*iter).second;
      cout << "---------- Group " << group->name() << " ----------" << endl;
      cout << group->toString() << endl;
    }
  }
}

const string Advance::getValue( const string &groupname, const string &element ) {
  HeaderGroup	*group = _groups[groupname];

  if ( group ) {
    return group->valueOf( element );
  } else {
    return string();
  }
}

// Return index into frame[] of given frame id str, or -1 if not present.
int Advance::frameIndex( const string &frameStr ) {
  FrameGroup	*frames = (FrameGroup *)_groups["frame"];
  
  return frames->frameIndex( frameStr );
}

AdvanceDate::AdvanceDate( void ) {
  _year = _month = _day = 0;
  _hour = _minute = _second = 0;
}

AdvanceDate::AdvanceDate( string datestr ) {
  sscanf( datestr.c_str(), "%d-%d-%d %d:%d:%d", &_year, &_month, &_day, &_hour, &_minute, &_second );
//   cout << "AdvanceDate::AdvanceDate(" << datestr << "): >" << _year << "< >" << _month << "< >" << _day << "< >" << _hour << "< >" << _minute << "< >" << _second << "<" << endl;
}

int AdvanceDate::toSec( void ) {
  return( _hour * 3600 + _minute * 60 + _second );
}

// Return the difference in seconds between two AdvanceDates.

long AdvanceDate::operator-( AdvanceDate &lhs ) {
  if (( lhs._day != _day ) || ( lhs._month != _month ))
    return -1;
  return( toSec() - lhs.toSec() );
}

// Save injection, frame start and frame duration times to a file.
// Normally you would save this info to the image file but in the case of 
// Analyze (and raw) files, there is no suitable field.
// Name:	subject_name.times
// Format: Comment lines start with '#'.
//	   FRAMES     Line 0:  Number of frames.
// 	   INJECTION  Line 1:  Injection time hh:mm:ss
// 	   FRAMEnn    n lines: Frame n start time (hh:mm:ss) and duration.

void Advance::writeTimes( void ) {
  char		outname[200];
  FILE		*outfile;
  float		scnst = getScanTime();
  int		numFrame = getNumFrame();

  sprintf( outname, "%s.times", getPatientID().c_str() );
  if (( outfile = fopen( outname, "w" )) == NULL ) {
    cout << "ERROR: Cannot open output file" << outname << endl;
    return;
  }

  fprintf( outfile, "# This file holds PET scan frame times.\n" );
  fprintf( outfile, "# FRAMES    line holds number of frames.\n" );
  fprintf( outfile, "# INJECTION line holds injection time (hh:mm:ss)\n" );
  fprintf( outfile, "# FRAMEnn   lines hold start time for frame n\n" );
  fprintf( outfile, "#           (hh:mm:ss) and duration (ss)\n" );

//   GE_DATE *scanT = (GE_DATE *)fields[SCAN]->fields[GE_SCAN::scanDatetime];
//   GE_DATE *frameT;
//   GE_LONG *durat;

  fprintf( outfile, "FRAMES\t\t%d\n", numFrame );
//   fprintf( outfile, "INJECTION\t%d\n", (int)scnst );
  fprintf( outfile, "INJECTION\t%s\n", _date->toString().c_str() );
  for ( int i = 0; i < numFrame; i++ ) {
    // frameT = (GE_DATE *)frame[i]->fields[GE_FRAME::acqStart];
    // durat  = (GE_LONG *)frame[i]->fields[GE_FRAME::acqDuration];
    float frmdu = getFrameDurat( i );
    float frmst = getFrameStart( i );
    fprintf( outfile, "FRAME%02d\t%d\t", i, (int)frmst );
    fprintf( outfile, "%d\n", (int)frmdu );
  }
  fclose( outfile );
}
