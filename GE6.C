// GE6.C

#include <iostream>
#include <fstream>
#include <iomanip>
#include <complex>
#include <string>

#include <strings.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "GE6.h"
#include "PET.h"

using namespace std;

int GE6::getint1( ifstream &instr ) {
  return getint1( instr, noisy );
}

int GE6::getint1( ifstream &instr, int debug ) {
  // unsigned char b[1];
  char		b[1];
  int		i = 0;
  unsigned char *ptr = (unsigned char *)&i;
  
  instr.read( b, 1 );
  // *(ptr + 3) = *b;
  i = (int)b[0];
  if ( debug )
    cout << hex << setfill('0') << setw(4) << "getint1(" << posn << "): [" << int(b[0]) << "]" << " returning " << dec << i << endl;
  posn += 1;
  return i;
}

short GE6::getint2( ifstream &instr ) {
  return getint2( instr, noisy );
}

short GE6::getint2( ifstream &instr, int debug ) {
  // unsigned char b[2];
  char b[2];
  int i = 0;
  unsigned char *ptr = (unsigned char *)&i;

  instr.read( b, 2 );
  // *(ptr + 3) = *(b + 1);
  // *(ptr + 2) = *(b + 0);
  i = int(b[1] << 8) + int(b[0]);

  // char b0, b1;
  // instr.read( &b1, 1 );
  // instr.read( &b0, 1 );
  // *(ptr + 3) = b0;
  // *(ptr + 2) = b1;
  // i = int(b0 << 8) + int(b1);

  if ( debug ) {
    cout << hex;
    
    cout << "getint2(" << setfill('0') << setw(4) << posn << "): ";
    cout << "[" << setw(2) << setfill('0') << int(b[0]);
    cout << " " << setw(2) << setfill('0') << int(b[1]);
    // cout << "[" << setw(2) << setfill('0') << int(b0);
    // cout << " " << setw(2) << setfill('0') << int(b1);
    cout << "]";
    cout << " returning " << dec << (short)i << endl;
  }
  posn += 2;
  return (short)i;
}

int GE6::getint4( ifstream &instr ) {
  return getint4( instr, noisy );
}

int GE6::getint4( ifstream &instr, int debug ) {
  // unsigned char b[4];
  char b[4];
  int i;
  unsigned char *ptr = (unsigned char *)&i;

  instr.read( b, 4 );
  // *(ptr + 3) = *( b + 0);
  // *(ptr + 2) = *( b + 1);
  // *(ptr + 1) = *( b + 2);
  // *(ptr + 0) = *( b + 3);
  *(ptr + 3) = *( b + 3);
  *(ptr + 2) = *( b + 2);
  *(ptr + 1) = *( b + 1);
  *(ptr + 0) = *( b + 0);

  if ( debug ) {
    cout << hex;
    cout << "getint4(" << setfill('0') << setw(4) << posn << "): ";
    cout << "[" << setw(2) << setfill('0') << int(b[0]);
    cout << " " << setw(2) << setfill('0') << int(b[1]);
    cout << " " << setw(2) << setfill('0') << int(b[2]);
    cout << " " << setw(2) << setfill('0') << int(b[3]);
    cout << "]";
    cout << " returning " << dec << i << endl;
  }
  posn += 4;
  return i;
}

float GE6::getfloat( ifstream &instr ) {
  return getfloat( instr, noisy );
}

/*
float GE6::getfloat( ifstream &instr, int debug ) {
  debug = 1;
  float f;
  instr >> f;
  cout << "getfloat: " << f << endl;
  return f;
}
*/


float GE6::getfloat( ifstream &instr, int debug ) {
  // unsigned char b[4];
  char b[4];
  float f;
  unsigned char *ptr = (unsigned char *)&f;

  instr.read( b, 4 );
  if ( instr.eof() ) 
    cerr << "GE6::getfloat() on EOF." << endl;
  if ( instr.bad() ) 
    cerr << "GE6::getfloat() bad." << endl;
  if ( instr.fail() ) 
    cerr << "GE6::getfloat() fail." << endl;

  // *(ptr + 1) = *(b + 0);
  // *(ptr + 0) = *(b + 1);
  // *(ptr + 3) = *(b + 2);
  // *(ptr + 2) = *(b + 3);

  *(ptr + 2) = *(b + 0);
  *(ptr + 3) = *(b + 1);
  *(ptr + 0) = *(b + 2);
  *(ptr + 1) = *(b + 3);

  f /= 4.0f;
  if ( debug ) {
    cout << hex;
    cout << "getfloat(" << setfill('0') << setw(4) << posn << "): ";
    cout << "[" << setw(2) << setfill('0') << (unsigned int)(b[0]);
    cout << " " << setw(2) << setfill('0') << (unsigned int)(b[1]);
    cout << " " << setw(2) << setfill('0') << (unsigned int)(b[2]);
    cout << " " << setw(2) << setfill('0') << (unsigned int)(b[3]);
    cout << "]";
    cout << " returning " << dec << f << endl;
  }
  posn += 4;
  return f;
}


char *GE6::getstring( ifstream &instr, int len ) {
  return getstring( instr, len, noisy );
}

char *GE6::getstring( ifstream &instr, int len, int debug ) {
  char *str = new char[len + 1];
  instr.read( str, len );
  str[len] = '\0';

  if ( debug ) {
    cout << "getstring(" << hex << posn << dec << ") length " << len << ":\t[";
    for ( int i = 0; i < len; i++ )
      cout << hex << setw(2) << setfill('0') << int(str[i]) << " ";
    cout << "]" << dec << endl;
  }
  
  posn += len;
  return str;
}

char *GE6::copystring( const char *str, const int len ) {
  char *ptr = new char[len + 1];
  strcpy( ptr, str );
  return( ptr );
}

GE6::GE6( void ) {
  posn = 0;
}

GE6::GE6( const GE6 &rhs ) {
  int	i;
  
  typ  = rhs.typ;
  ncs  = rhs.ncs;
  site = copystring( rhs.site, 4 );
  rev  = rhs.rev;
  ndet = rhs.ndet;
  npro = rhs.npro;
  nmem = rhs.nmem;
  nwob = rhs.nwob;
  cd1  = rhs.cd1;
  csz  = rhs.csz;
  csx  = rhs.csx;
  rid  = copystring( rhs.rid, 10 );
  rin  = rhs.rin;
  etn  = rhs.etn;
  pnm  = copystring( rhs.pnm, 24 );
  brn  = rhs.brn;
  ass  = copystring( rhs.ass, 22 );
  doc  = copystring( rhs.doc, 22 );
  daty = rhs.daty;
  datm = rhs.datm;
  datd = rhs.datd;
  timh = rhs.timh;
  timm = rhs.timm;
  tims = rhs.tims;
  tihu = rhs.tihu;
  qes  = copystring( rhs.qes, 12 );
  por  = copystring( rhs.por, 4 );
  pan  = rhs.pan;
  zdi  = rhs.zdi;
  nrv  = rhs.nrv;
  nme  = rhs.nme;
  mtm  = rhs.mtm;
  rprt = rhs.rprt;
  iso  = copystring( rhs.iso, 6 );
  half = rhs.half;
  car  = copystring( rhs.car, 8 );
  act  = rhs.act;
  inp  = copystring( rhs.inp, 4 );
  intt = copystring( rhs.intt, 4 );
  itmh = rhs.itmh;
  itmm = rhs.itmm;
  itms = rhs.itms;
  col  = copystring( rhs.col, 1 );
  samp = rhs.samp;
  dtyp = rhs.dtyp;
  fov  = rhs.fov;
  prjl = rhs.prjl;
  tilt = rhs.tilt;
  slew = rhs.slew;
  elv  = rhs.elv;
  tiw  = rhs.tiw;
  hcom = copystring( rhs.hcom, 20 );
  styp = rhs.styp;
  blan = rhs.blan;
  tran = rhs.tran;
  par  = rhs.par;
  norm = rhs.norm;
  dpr  = rhs.dpr;
  tmn  = copystring( rhs.tmn, 8 );
  ferr = rhs.ferr;
  flos = rhs.flos;
  inva = rhs.inva;
  trat = rhs.trat;
  tac  = rhs.tac;
  imfm = rhs.imfm;
  imtp = copystring( rhs.imtp, 10 );
  imun = copystring( rhs.imun, 10 );
  pxs  = rhs.pxs;
  ffn  = copystring( rhs.ffn, 4 );
  fwd  = rhs.fwd;
  slot = rhs.slot;
  cntx = copystring( rhs.cntx, 10 );
  age  = rhs.age;
  sex  = copystring( rhs.sex, 1 );
  max  = rhs.max;
  reserved = copystring( rhs.reserved, 64 );
  for ( i = 0; i < 8; i++ )
    sing[i] = rhs.sing[i];
  for ( i = 0; i < 8; i++ )
    xrat[i] = rhs.xrat[i];
  for (i = 0; i < 5; i++) {
    user[i] = new User6( *rhs.user[i] );
  }

  cycl = rhs.cycl;
  cych = rhs.cych;
  gtll = rhs.gtll;
  gtlh = rhs.gtlh;
  grnr = rhs.grnr;
  gtyp = rhs.gtyp;
  frnr = rhs.frnr;
  dcy  = rhs.dcy;
  ngat = rhs.ngat;
  nbts = rhs.nbts;
  nbr  = rhs.nbr;
  avc  = rhs.avc;
  ypos = rhs.ypos;
  
  for (i = 0; i < 30; i++) {
    slic[i] = new Slice6( *rhs.slic[i] );
  }
  for (i = 0; i < 30; i++)
    offs[i] = rhs.offs[i];
  pad = copystring( rhs.pad, 312 );
  // No need for slic[i]->readpixels() since have copied all slic[].
  volMax = rhs.volMax;
  volMin = rhs.volMin;
}

// isDataFile()
// Return 1 if this file is a GE6 data file, else 0.

int GE6::isDataFile( const char *name ) {
  ifstream instr( name );

  if ( !instr ) {
    cerr << "Cannot open " << name << endl;
    return( 0 );
  }
  int pos = instr.tellg();
  int type = getint2( instr, 0 );
  return( type == PET6_IDENT );
}

void GE6::read( ifstream &instr ) {
  read( instr, 0 );
}

void GE6::read( ifstream &instr, int nois ) {
  int		i;

  noisy = nois;
  posn = 0;
  typ  = getint2( instr );
  ncs  = getint1( instr );
  site = getstring( instr, 4 );
  rev  = getint2( instr );
  ndet = getint2( instr );
  npro = getint2( instr );
  nmem = getint2( instr );
  nwob = getint1( instr );
  cd1  = getfloat( instr );
  csz  = getfloat( instr );
  csx  = getfloat( instr );
  rid  = getstring( instr, 10 );
  rin  = getint4( instr );
  etn  = getint2( instr );
  pnm  = getstring( instr, 24 );
  brn  = getint4( instr );
  ass  = getstring( instr, 22 );
  doc  = getstring( instr, 22 );
  daty = getint1( instr );
  datm = getint1( instr );
  datd = getint1( instr );
  timh = getint1( instr );
  timm = getint1( instr );
  tims = getint1( instr );
  tihu = getint1( instr );
  qes  = getstring( instr, 12 );
  por  = getstring( instr, 4 );
  pan  = getint2( instr );
  zdi  = getfloat( instr );
  nrv  = getint2( instr );
  nme  = getint2( instr );
  mtm  = getfloat( instr );
  rprt = getfloat( instr );
  iso  = getstring( instr, 6 );
  half = getfloat( instr );
  car  = getstring( instr, 8 );
  act  = getfloat( instr );
  inp  = getstring( instr, 4 );
  intt = getstring( instr, 4 );
  itmh = getint1( instr );
  itmm = getint1( instr );
  itms = getint1( instr );
  col  = getstring( instr, 1 );
  samp = getint1( instr );
  dtyp = getint1( instr );
  fov  = getint1( instr );
  prjl = getint2( instr );
  tilt = getfloat( instr );
  slew = getfloat( instr );
  elv  = getint2( instr );
  tiw  = getfloat( instr );
  hcom = getstring( instr, 20 );
  styp = getint1( instr );
  blan = getint4( instr );
  tran = getint4( instr );
  par  = getint1( instr );
  norm = getint2( instr );
  dpr  = getint1( instr );
  tmn  = getstring( instr, 8 );
  ferr = getint4( instr );
  flos = getfloat( instr );
  inva = getfloat( instr );
  trat = getfloat( instr );
  tac  = getint2( instr );
  imfm = getint2( instr );
  imtp = getstring( instr, 10 );
  imun = getstring( instr, 10 );
  pxs  = getfloat( instr );
  ffn  = getstring( instr, 4 );
  fwd  = getfloat( instr );
  slot = getint2( instr );
  cntx = getstring( instr, 10 );
  age  = getint1( instr );
  sex  = getstring( instr, 1 );
  max  = getint2( instr );
  reserved = getstring( instr, 64, 0 );
  for ( i = 0; i < 8; i++ )
    sing[i] = getfloat( instr );
  for ( i = 0; i < 8; i++ )
    xrat[i] = getfloat( instr );
  for (i = 0; i < 5; i++) {
    user[i] = new User6( this );
    user[i]->read( instr, noisy );
  }

  cycl = getfloat( instr );
  cych = getfloat( instr );
  gtll = getfloat( instr );
  gtlh = getfloat( instr );
  grnr = getint1( instr );
  gtyp = getint1( instr );
  frnr = getint2( instr );
  dcy  = getfloat( instr );
  ngat = getint1( instr );
  nbts = getint2( instr );
  nbr  = getint2( instr );
  avc  = getfloat( instr );
  ypos = getfloat( instr );
  // cout << "---------- 0 ----------" << endl;
  
  for (i = 0; i < 30; i++) {
    // cout << "---------- slice " << i << " ----------" << endl;
    slic[i] = new Slice6( this );
    slic[i]->read( instr, noisy );
  }
  for (i = 0; i < 30; i++) {
    // cout << "---------- offs " << i << " ----------" << endl;
    offs[i] = getfloat( instr );
  }
  pad = getstring( instr, 312, 0 );
  // cout << "---------- 1 ----------" << endl;

  for (i = 0; i < ncs; i++) {
    // cout << "---------- readpixels " << i << " / " << ncs << " ----------" << endl;
    slic[i]->readpixels( instr );
  }

  // Calculate global vol min/max.
  volMax = -10000.0;
  volMin = 10000.0;
  for ( i = 0; i < ncs; i++ ) {
    // cout << "---------- ncs " << i << " ----------" << endl;
    volMax = ( slic[i]->getMax() > volMax ) ? slic[i]->getMax() : volMax;
    volMin = ( slic[i]->getMin() < volMin ) ? slic[i]->getMin() : volMin;
  }
  // cout << "---------- 2 ----------" << endl;
}

void GE6::printTime( void ) {
  cout << "Measurement time: " << timh << ":" << timm << ":" << tims << "." << tihu << endl;
}

void GE6::print( int option ) {
  if ( option == GE6::LONG_HEADER ) {
    print();
  } else {
    // Print only selected fields.
    cout << "Patient name: " << pnm << endl;
    cout << "Patients age: " << age << endl;
    cout << "Patients sex: " << sex << endl;
    cout << "Run id: " << rid << endl;
    cout << "Identification number: " << rin << endl;
    cout << "Measurement date: " << datm << "/" << datd << "/" << daty << endl;
    cout << "Measurement time: " << timh << ":" << timm << ":" << tims << "." << tihu << endl;
    cout << "Question: " << qes << endl;
    cout << "Number of measurements: " << nme << endl;
    cout << "Injection time: " << itmh << ":" << itmm << ":" << itms << endl;
    cout << "Responsible technician: " << ass << endl;
    cout << "Responsible doctor: " << doc << endl;
    cout << "Volume max: " << volMax << ", min: " << volMin << endl;
  }    
}

void GE6::print( void ) {
  int				 i;

  cout << "Type of equipment: " << typ << endl;
  cout << "Number of slices: " << ncs << endl;
  cout << "Installation site: " << site << endl;
  cout << "Revision number: " << rev << endl;
  cout << "Detectors/ ring: " << ndet << endl;
  cout << "Projections/slice: " << npro << endl;
  cout << "Members/proj.: " << nmem << endl;
  cout << "Wobble bins/member: " << nwob << endl;
  cout << "Cross section distance (mm): " << cd1 << endl;
  cout << "Cross section thickness (p)(mm): " << csz << endl;
  cout << "Cross section thickness (x)(mm): " << csx << endl;
  cout << "Run id: " << rid << endl;
  cout << "Identification number: " << rin << endl;
  cout << "ET number (user def): " << etn << endl;
  cout << "Patient name: " << pnm << endl;
  cout << "Patient birth number: " << brn << endl;
  cout << "Responsible technician: " << ass << endl;
  cout << "Responsible doctor: " << doc << endl;
  cout << "Measurement date: " << datm << "/" << datd << "/" << daty << endl;
  cout << "Measurement time: " << timh << ":" << timm << ":" << tims << "." << tihu << endl;
  cout << "Question: " << qes << endl;
  cout << "Patient orientation: " << por << endl;
  cout << "Patient angle: " << pan << endl;
  cout << "Z displacement (mm): " << zdi << endl;
  cout << "Number of rpm: " << nrv << endl;
  cout << "Number of measurements: " << nme << endl;
  cout << "Measurement duration: " << mtm << endl;
  cout << "Report rate: " << rprt << endl;
  cout << "Isotope: " << iso << endl;
  cout << "Halflife: " << half << endl;
  cout << "Carrier: " << car << endl;
  cout << "Activity: " << act << endl;
  cout << "Injection place: " << inp << endl;
  cout << "Injection type: " << intt << endl;
  cout << "Injection time: " << itmh << ":" << itmm << ":" << itms << endl;
  cout << "Collimator type: " << col << endl;
  cout << "Sampling mode: " << samp << endl;
  cout << "Data type: " << dtyp << endl;
  cout << "Field of View: " << fov << endl;
  cout << "Projecton length (members): " << prjl << endl;
  cout << "Gantry tilt (degrees): " << tilt << endl;
  cout << "Gantry slew (degrees): " << slew << endl;
  cout << "Energy level (kev): " << elv << endl;
  cout << "Time window (ns): " << tiw << endl;
  cout << "Comments: " << hcom << endl;
  cout << "Scan type: " << styp << endl;
  cout << "Blank scan number: " << blan << endl;
  cout << "Transmission scan number: " << tran << endl;
  cout << "Parameter file number: " << par << endl;
  cout << "Normalization file number: " << norm << endl;
  cout << "Data present (1 = present) : " << par << endl;
  cout << "Tape name: " << tmn << endl;
  cout << "Fifo errors: " << ferr << endl;
  cout << "Fifo loss rate: " << flos << endl;
  cout << "Invalid count rate: " << inva << endl;
  cout << "Total count rate: " << trat << endl;
  cout << "Type of attenuation correction: " << tac << endl;
  cout << "Image format: " << imfm << endl;
  cout << "Image type: " << imtp << endl;
  cout << "Image scale unit: " << imun << endl;
  cout << "Pixel size (mm): " << pxs << endl;
  cout << "Reconstruction filter: " << ffn << endl;
  cout << "Reconstruction filter width(mm): " << fwd << endl;
  cout << "DAP Disk slot: " << (short)slot << endl;
  cout << "Study context: " << cntx << endl;
  cout << "Patients age: " << age << endl;
  cout << "Patients sex: " << sex << endl;
  cout << "Highest pixel in image: " << max << endl;
  cout << "Singles count rate per detector\n" << endl;
  for (i = 0; i < 8; i++)
    cout << "\tDetector " << i + 1 << ": " << sing[i] << endl;
  cout << "Physiological input count rate per detector\n" << endl;
  for (i = 0; i < 8; i++)
    cout << "\tDetector " << i + 1 << ": " << xrat[i] << endl;
  // Skip user[5].
  cout << "Gate cycle time low limit: " << cycl << endl;
  cout << "Gate cycle time high limit: " << cych << endl;
  cout << "Gate low limit (%% cycle): " << gtll << endl;
  cout << "Gate high limit (%% cycle): " << gtlh << endl;
  cout << "Gate number: " << grnr << endl;
  cout << "Gate type: " << gtyp << endl;
  cout << "Time frame number: " << frnr << endl;
  cout << "Measurement time duty cycle (%%): " << dcy << endl;
  cout << "Number of gating bins: " << ngat << endl;
  cout << "Beats/frame: " << nbts << endl;
  cout << "Number of beats rejected: " << nbr << endl;
  cout << "Average heart cycle including rejected beats: " << avc << endl;
  cout << "Y position of the couch: " << ypos << endl;
  cout << "Slice info:\n" << endl;
  for (i = 0; i < ncs; i++) {
    cout << "\tSlice " << i + 1 << endl;
    slic[i]->print();
  }
  cout << "Slice Offset:\n" << endl;
  for (i = 0; i < ncs; i++)
    cout << "\tSlice " << i + 1 << " offset: " << offs[i] << endl;
}

short **GE6::vals( void ) {
  short **vals = new short *[15];

  for ( int i = 0; i < 15; i++ )
    vals[i] = slic[i]->vals();
  return vals;
}

// Return time in seconds between injection and beginning of frame.

float GE6::measureTime( void ) {
  int meas = timh * 3600 + timm * 60 + tims;
  int inje = itmh * 3600 + itmm * 60 + itms;

  return( (float)(meas - inje) );
}

// Seconds since midnight of scan start (start of frame 0).

float GE6::scanTime( void ) {
  int inje = itmh * 3600 + itmm * 60 + itms;
  return (float)inje;
}

// float getMax( int sli = -1 ); => called without param gives global.

float GE6::getMax( int sli ) {
  if ( sli < 0 )
    return volMax;
  else
    return ( slic[sli]->getMax() );
}

float GE6::getMin( int sli ) {
  if ( sli < 0 )
    return volMin;
  else
    return ( slic[sli]->getMin() );
}

User6::User6( const User6 &rhs ) {
  parent = rhs.parent;
  usr = parent->copystring( rhs.usr, 4 );
  usi = parent->copystring( rhs.usi, 4 );
  usc = parent->copystring( rhs.usc, 10 );
  noisy = rhs.noisy;
}

void User6::read( ifstream &instr ) {
  read( instr, 0 );
}

void User6::read( ifstream &instr, int nois ) {
  noisy = nois;
  usr = parent->getstring( instr, 4, 0 );
  usi = parent->getstring( instr, 4, 0 );
  usc = parent->getstring( instr, 10, 0 );
}

Slice6::Slice6( void ) {
  pixels = 0;
}

Slice6::Slice6( GE6 *par ) {
  parent = par;
  for ( int i = 0; i < 32; i++ )
    peri[i] = new Peri6( parent );
  pixels = 0;
}

Slice6::Slice6( const Slice6 &rhs ) {
  parent = rhs.parent;
  stot = rhs.stot;		// total  counts/slice
  cal = rhs.cal;		// slice calibration factors
  min = rhs.min;		// minimum pixel in slice [2][2]
  mag = rhs.mag;		// image magnification
  spos = rhs.spos;		// slice position in file [1]
  sca = rhs.sca;		// scatter/slice
  ran = rhs.ran;		// randoms/slice
  dtc = rhs.dtc;		// dead time correction factor
  clv = rhs.clv;		// cross-section level (mm + OM)
  xpan = rhs.xpan;		// x reconstruction
  ypan = rhs.ypan;		// y reconstruction
  for ( int i = 0; i < 32; i++ )
    peri[i] = new Peri6( *(rhs.peri[i]) );

  if ( rhs.pixels ) {
    pixels = new short[PET6_PIXELS];
    memcpy( pixels, rhs.pixels, PET6_PIXELS * sizeof( short ));
  } else {
    pixels = 0;
  }
  noisy = rhs.noisy;
}  

void Slice6::read( ifstream &instr ) {
  read( instr, 0 );
}

void Slice6::read( ifstream &instr, int nois ) {
  noisy = nois;

  stot = parent->getfloat( instr );
  cal = parent->getfloat( instr );
  min = ( short int )parent->getint2( instr );
  mag = parent->getfloat( instr );
  spos = parent->getint1( instr );
  sca = parent->getfloat( instr );
  ran = parent->getfloat( instr );
  dtc = parent->getfloat( instr );
  clv = parent->getfloat( instr );
  xpan = parent->getfloat( instr );
  ypan = parent->getfloat( instr );
  for ( int i = 0; i < 32; i++ )
    peri[i]->read( instr );

  // Decay correction is implemented as a scaling of the mag.
  float elapsed = parent->measureTime();
  float durat = parent->frameDuration();
  elapsed += durat / 2.0;
  // Assumption: C-11 isotope.
  float halflives = elapsed / C11_HALFLIFE;
  float factor = pow( (double)2.0, (double)halflives );
  mag *= factor;
}

void Slice6::readpixels( ifstream &instr ) {
  // Fill in the slice pixel values.
  char buff[PET6_PIXELS * 2];
  short val;
  unsigned char *ptr0 = (unsigned char *)&val;
  unsigned char *ptr1 = ptr0 + 1;  

  pixels = new short[PET6_PIXELS];
  instr.read( buff, PET6_PIXELS * 2 );

  for ( int i = 0; i < PET6_PIXELS; i++ ) {
    *(ptr0) = buff[i * 2 + 0];
    *(ptr1) = buff[i * 2 + 1];
    pixels[i] = short( float(val) * mag / 32000.0 );
  }
}

short *Slice6::vals( void ) { 
  return pixels; 
}

// setData()
// Copy the given values into the vals array of this slice.
// Scale to correct range -n..+32000 and set min, max, mag correctly.

void Slice6::setData( float *fdat, int n ) {
  float		factor, mn = 1000.0, mx = -1000.0;
  int		i;

  for ( i = 0; i < n; i++ ) {
    mn = ( fdat[i] < mn ) ? fdat[i] : mn;
    mx = ( fdat[i] > mx ) ? fdat[i] : mx;
  }
//    cout << "Slice6::setData(): mn = " << mn << ", mx = " << mx << endl;
  if ( pixels )
    delete[] pixels;
  pixels = new short[PET6_PIXELS];
  factor = 32000 / mx;
  for ( i = 0; i < n; i++ )
    pixels[i] = (short)( fdat[i] * factor );
  mag = mx;
  min = short( mn * factor );
}

int Slice6::writeData( const char *oname, int options, int append ) {
  int		ret;
  ofstream	fout;
  ios_base::openmode mode = append ? ios::app : ios::out;

  fout.open( oname, mode );
  if ( !fout.is_open() ) {
    printf( "Cannot open output file %s", oname );
    return( -1 );
  }
  ret = writeData( fout, options );
  fout.close();
  return ret;
}

int Slice6::writeData( ofstream &ofile, int opt ) {
  // Analyze format files are reversed in Y; need to swap order of rows.
  // Changed this 11/6/01 - parametric images always Analyze format.
  //    if ( opt & PET::OPT_ANAL && !(opt & PET::OPT_PARA )) {
  if ( opt & PET::OPT_ANAL ) {
    char tmp[256], *src, *dest, *cptr;
    cptr = (char *)pixels;
    for ( int i = 0; i < 64; i++ ) {
      src = cptr + i * 256;
      dest = cptr + (127 - i) * 256;
      memcpy( tmp, src, 256 );  // 128 shorts from start to tmp.
      memcpy( src, dest, 256 );
      memcpy( dest, tmp, 256 );
    }
  }

  // Special case if parametric: Float vals and scale from 32000 to mag.
  if ( opt & PET::OPT_PARA ) {
    float farr[PET6_PIXELS];
    float factor = mag / 32000.0f;
    for ( int i = 0; i < PET6_PIXELS; i++ )
      farr[i] = (float)pixels[i] * factor;
    ofile.write( (char *)farr, PET6_PIXELS * sizeof(float) );
    if ( ofile.bad() )
      return -1;
  } else {
    ofile.write( (char *)pixels, sizeof(short) * PET6_PIXELS );
    if ( ofile.bad() )
      return -1;
  }
  return 0;
}

void Slice6::print( void ) {
  cout << "\t\tTotal counts/slice: " << stot << endl;
  cout << "\t\tSlice calibration factors: " << cal << endl;
  cout << "\t\tMinimum pixel in slice: " << min << endl;
  cout << "\t\tImage magnification: " << mag << endl;
  cout << "\t\tSlice position in image file: " << spos << endl;
  cout << "\t\tScatter counts/slice: " << sca << endl;
  cout << "\t\tRandom counts/slice: " << ran << endl;
  cout << "\t\tDead time correction factor: " << dtc << endl;
  cout << "\t\tCross section level (mm + OM): " << clv << endl;
  cout << "\t\tX Reconstruction: " << xpan << endl;
  cout << "\t\tY Reconstruction: " << ypan << endl;
}  

void Slice6::showpix( void ) {
  short val;
  int pos = 0;

  for ( int i = 0; i < PET6_DIM; i++ ) {
    for ( int j = 0; j < PET6_DIM; j++ ) {
      val = pixels[pos];
      if ( val > 5000 )
	cout << "X ";
      else
	cout << "  ";
      pos++;
    }
    cout << endl;
  }
  cout << endl;
}

// Max pixel val in slice.

float Slice6::getMax( void ) {
  return mag;
}

// Min pixel val in slice.

float Slice6::getMin( void ) {
  return( (float)min * mag / 32000 );
}

Peri6::Peri6( const Peri6 &rhs ) {
  parent = rhs.parent;
  perx = rhs.perx;
  pery = rhs.pery;
}

void Peri6::read( ifstream &instr ) {
  perx = parent->getint1( instr, 0 );
  pery = parent->getint1( instr, 0 );
}
