// readPET.C
// Written by Andrew Crabb.
// Read GE PET data in Advance (IE) or Scanditronix (IMA) format,
// and write to raw or Analyze output formats.

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
#include <vector>
#include <string>

#include "Advance.h"
#include "PET.h"
#include "Scanditronix.h"

int processSwitches( vector<string> &filenames, string &newid );
int whatHaveWeHere( vector<string> &infiles );
void say( const char *str );

// Globals.
vector<int>	slices;
int		modelType;

static const string disclaimer = "\
***************************************************************************\n\
* 			 NOT FOR CLINICAL USE                             *\n\
*                                                                         *\n\
* This software is to be used only for research and educational purposes. *\n\
* Clinical applications of this software are not permitted.               *\n\
* This software has NOT been evaluated by the USFDA for any clinical use. *\n\
*                                                                         *\n\
*			     NO WARRANTY                                  *\n\
*                                                                         *\n\
* This program is distributed in the hope that it will be useful, but     *\n\
* WITHOUT ANY WARRANTY; without even the implied warranty of              *\n\
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *\n\
* General Public License for more details (www.gnu.org/copyleft/gpl.txt)  *\n\
***************************************************************************";

static const string endres = "\n\
* The Logan and Patlak algorithms are implemented in bilinear form.     \n\
* E.g.,the Logan equation is computed as                                \n\
* INTEGRAL(Ct(t))=DV*INTEGRAL(Cp(t))+K*Ct(T) instead of the more        \n\
* traditional form where Ct(T) appears in the denominator. The reason   \n\
* for this approach is that Ct(T) has large variance in voxelwise data, \n\
* thus dividing by that term introduces considerable variability in the \n\
* calculation. Using the bilinear form where Ct(T) no longer appears in \n\
* the denominator, the variability is substantially reduced.            \n\
*                                                                       \n\
* Logan and Patlak code is written and maintained by                    \n\
* Christopher J. Endres  (endres@jhmi.edu)                              \n\
* Please contact him for further information.                           \n\
\n";

int main( int argc, char **argv ) {
  char		inputFilename[200];
  vector<string> infiles;
  string	str;
  string	newid;	// Kludgy way to pass this param around.
			// Better to have opts be a stuct rather than int.
  PET		*pet;
  int		opts;

  if( argc < 2 ) {
    say( "readPET: A PET file translation program for GE file formats." );
    say( "Copyright (C) 2000-2005, Andrew Crabb\n");
    say( "usage: readPET <inputfiles> [-abdhilmptvw]" );
    say( "-a   : Analyze:     Convert to Analyze format." );
    say( "-b   : Becquerels:  Use units of MBq/cc (default is nCi/cc)." );
    say( "-d   : Debug:       Print debugging information." );
    say( "-h   : Header:      Print short header to screen." );
    say( "-i ID: Ident:       Replace subject ID with supplied ID value." );
    say( "-l   : Long Header: Print LONG! header to screen." );
    say( "-m   : Mean Image:  Calculate mean image and write to disk." );
    say( "-p S : Parametric:  Calculate parametric image files." );
    say( "                    Model/slice range str S: -pMXX or -pMXX-YY." );
    say( "                    Model M = (P)atlak or (L)ogan." );
    say( "                    Slices XX to YY (0 indexed) inclusive." );
    say( "-t   : Times:       Write temporal information to text file." );
    say( "-v   : Volume:      Save all frames in one volume file." );
    say( "-w   : Write:       Write data frames to disk." );
    say( "Notes: Switches may be combined." );
    say( "       Input files may be GE Scanditronix or GE ADVANCE." );
    say( "       Output PET image files are decay corrected." );
    say( "" );
    //    cout << endres << endl;
    cout << disclaimer << endl;
    exit( -1 );
  }

  // infiles initially holds all cmd line arguments.
  for ( int i = 1; i < argc; i++ ) {
    str = argv[i];
    infiles.push_back( str );
  }
  // processSwitches returns all non-switch cmd line arguments.
  opts = processSwitches( infiles, newid );
  cout << "readPET: newid " << newid << endl;
  switch( whatHaveWeHere( infiles )) {
  case PET::ADVANCE:
    pet = new Advance( opts );
    break;
  case PET::SCANDITRONIX:
    pet = new Scanditronix;
    break;
  default:
    if ( infiles.size() )
      cerr << "Unknown file type: " << infiles[0] << endl;
    else
      cerr << "No input file supplied" << endl;
    exit( 0 );
  }

  // ***  KLUDGE  ***
  pet->kludgeSetID( newid );

  if ( pet->read( infiles, opts )) 
    exit( 1 );

  if ( opts & ( PET::OPT_WRIT | PET::OPT_VOLU ))
    pet->write( opts );

  if ( opts & PET::OPT_PARA ) {
    if ( !pet->initializeParametric( modelType ))
      pet->parametric( opts, slices );
  }

  if ( opts & PET::OPT_MEAN ) {
    pet->makeMean( opts );
    pet->writeMean( opts );
  }
  
  if ( opts & ( PET::OPT_TIME ))
    pet->writeTimes();

  delete( pet );
  exit( 0 );
}

// processSwitches(): Set option switches from cmd line arguments.
// Returns: Array of every argv that doesn't start with '-'.
// Modifies: Global array slices.

int processSwitches( vector<string> &infiles, string &newid ) {
  char		c;
  int		pos = 0;
  string	s;
  int		opts = 0;

  int i = 0;
  while ( i < infiles.size() ) {
    s = infiles[i];
    c = s[0];
    if ( c == '-' ) {
      infiles.erase( infiles.begin() + i );  // Remove switch from file list
      switch( tolower( s[1] )) {
      case 'a': opts += PET::OPT_ANAL;	       // Write Analyze headers.
	        opts += PET::OPT_WRIT; break;  // Implies write to disk.
      case 'b': opts += PET::OPT_MBQ;  break;  // Use MBq/cc not nCi/cc.
      case 'd': opts += PET::OPT_DEBG; break;  // Print debugging info.
      case 'h': opts += PET::OPT_SHDR; break;  // Print short header.
      case 'l': opts += PET::OPT_LHDR; break;  // Print long header.
      case 'm': opts += PET::OPT_MEAN; break;  // Write mean to disk.
      case 't': opts += PET::OPT_TIME; break;  // Write temporal info file.
      case 'v': opts += PET::OPT_VOLU; break;  // All vol to one file.
      case 'w': opts += PET::OPT_WRIT; break;  // Write frames to disk.
	// ----------------------------------------
      case 'i':				       // Use new subj ident.
	opts += PET::OPT_IDEN; 
	if ( infiles.size() > i ) {
	  string tmpid = infiles[i];
	  cout << "readPET(): infiles[" << i + 1 << "] = >" << tmpid << "<" << endl;
	  char newc = tmpid[0];
	  // If valid arg, keep it and skip over.
	  if ( newc != '-' ) {
	    newid = tmpid;
	    infiles.erase( infiles.begin() + i );
	  }
	}

	// newid will be zero length if new ID not supplied.
	if ( newid.length() == 0 ) {
	  cerr << "Error: No ident supplied for option '-i'" << endl;
	  exit( 1 );
	}

	cout << "readPET: option i new value >" << newid << "<" << endl;

	break;
	// ----------------------------------------
      case 'p':				       // Parametric.
	opts += PET::OPT_PARA;
	char startbuf[10], endbuf[10];
	int start = 0, end = 0;
	
	// Make sure that a model is specified.
	char c = (s.size() >= 3) ? toupper( s[2] ) : 0;
	switch( c ) {
	case 'L':  modelType = PET::MODEL_LOGAN; break;
	case 'P':  modelType = PET::MODEL_PATLAK; break;
	default:
	  cerr << "Error: Must use model type P or L with switch p" << endl;
	  exit( 1 );
	}
 
	string		begstr, endstr;
	int		it0, it1;
	vector<string>::iterator ptr = infiles.begin() + i;
	infiles.erase( ptr, ptr );

	// begstr, endstr hold first and second groups of digits.
	// Delete leading characters from s.
	s = s.substr( 3 );
	it0 = s.find_first_not_of( "0123456789", 0 );
	begstr = s.substr( 0, it0 );
	it1 = s.find_first_of( "0123456789", it0 + 1 );
	endstr = s.substr( it1 );
	
	if ( begstr.size() )
	  start = atoi( begstr.c_str() );
	if ( endstr.size() )
	  end = atoi( endstr.c_str() );

 	// Fill in the range between start & end.
	pos = 0;
	slices.push_back( start++ );
	while ( start <= end )
	  slices.push_back( start++ );
	pos = 0;
	cout << "Slices = ";
	for ( int j = 0; j < slices.size(); j++ )
	  cout << slices[pos++] << " ";
	cout << endl;
	break;  // Parametric modeling.
      }
    } else {
      // Not a switch: Treat as data file and keep in infiles.
      i++;
    }
  }
  return( opts );
}

// Return an identifier of the type of input file we are dealing with.

int whatHaveWeHere( vector<string> &infiles ) {
  Advance	advance;
  Scanditronix	scanditronix;
  int		ret = PET::UNKNOWN;

  if ( infiles.size() ) {
    if ( advance.isDataFile( infiles[0] ))
      ret = PET::ADVANCE;
    if ( scanditronix.isDataFile( infiles[0] ))
      ret = PET::SCANDITRONIX;
  }
  return ret;
}

void say( const char *str ) {
  cout << str << endl;
}
