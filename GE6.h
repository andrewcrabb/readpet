// GE6.h

#ifndef GE6_H
#define GE6_H

#include <iostream>
#include <fstream>

using namespace std;

const int PET6_BYTES	= 4096;		// Header size.
const int PET6_DIM	= 128;		// Pixel dimensions.
const int PET6_PIXELS	= 16384;	// Pixel count.
const int PET6_SLICES	= 15;		// Slices per volume.
const int PET6_IDENT	= 6;		// Identifying first byte.
const int C11_HALFLIFE  = 1223;		// Seconds.

typedef unsigned short ushort;
typedef unsigned char uchar;

class GE6;

// Utility classes.
struct Peri6	{			
private:
  GE6		*parent;
  int		perx;		// perimeter x-coord
  int		pery;		// perimeter y-coord
public:
  Peri6( void ) {}
  Peri6( GE6 *par ) { parent = par; }
  Peri6( const Peri6 &rhs );
  void		read( ifstream &instr );
  void		read( ifstream &instr, int noisy );
  void		print( void );
};  // struct Peri6

struct Slice6 {
private:
  GE6		*parent;
  float		stot;		// total  counts/slice
  float		cal;		// slice calibration factors
  short int	min;		// minimum pixel in slice [2][2]
  float		mag;		// image magnification
  int		spos;		// slice position in file [1]
  float		sca;		// scatter/slice
  float		ran;		// randoms/slice
  float		dtc;		// dead time correction factor
  float		clv;		// cross-section level (mm + OM)
  float		xpan;		// x reconstruction
  float		ypan;		// y reconstruction
  Peri6		*peri[32];

  short		*pixels;	// [PET6_PIXELS * PET6_PIXELS]
  int		noisy;

public:
  Slice6( void );
  Slice6( GE6 *par );
  Slice6( const Slice6 &rhs );
  void		read( ifstream &instr );
  void		read( ifstream &instr, int noisy );
  void		print( void );
  void		readpixels( ifstream &instr );
  void		showpix( void );
  float		getMag( void ) { return mag; }
  short		*vals( void );
  void		setSliceNumber( int sli ) { spos = sli; }
  void		setData( float *fdat, int n );
  int		writeData( const char *oname, int options, int append );
  int		writeData( ofstream &ofile, int opt );
  float		getMax( void );
  float		getMin( void );
};  // struct Slice6

struct User6 {
private:
  GE6		*parent;
  char		*usr;		// user definable reals [4]
  char		*usi;		// user defineable longwords [4]
  char		*usc;		// user definable strings [10]
  int		noisy;
public:
  User6( void ) {}
  User6( GE6 *par ) { parent = par; }
  User6( const User6 &rhs );
  void		read( ifstream &instr );
  void		read( ifstream &instr, int noisy );
  void		print( void ) {}
};

class GE6 {
private:
  int		typ;		// Type of equipment [2]
  int		ncs;		// Number of slices [1]
  char		*site;		// Installation site [4]
  int		rev;		// Revision number [2]
  int		ndet;		// number of detectors per ring [2]
  int		npro;		// number of projections per slice [2]
  int		nmem;		// number of members in stat. proj. [2]
  int		nwob;		// number of wobble bins per member [1]
  float		cd1;		// cross-section distance (mm)
  float		csz;		// cross-section thickness (p) (mm)
  float		csx;		// cross-section thickness (x) (mm)
  char		*rid;		// run id [10]
  int		rin;		// identification number [4]
  int		etn;		// et-number (user def) [2]
  char		*pnm;		// patient name [24]
  int		brn;		// birth number [4]
  char		*ass;		// responsible technician [22]
  char		*doc;		// responsible doctor [22]
  int		daty;		// measurement dat year [1]
  int		datm;		// month [1]
  int		datd;		// day [1]
  int		timh;		// measurement time hour [1]
  int		timm;		// minute [1]
  int		tims;		// seconds [1]
  int		tihu;		// hundredths of seconds [1]
  char		*qes;		// question [12]
  char		*por;		// patient orientation [4]
  int		pan;		// patient angle [2]
  float		zdi;		// z-displacement (mm)
  int		nrv;		// number of revolutions per minute [2]
  int		nme;		// number of measurements [2]
  float		mtm;		// measurement time (duration)
  float		rprt;		// time in s. between rates-file reports
  char		*iso;		// isotope (eg GA_68) [6]
  float		half;		// halflife of isotope (user supplied)
  char		*car;		// carrier [8]
  float		act;		// activity
  char		*inp;		// injection place [4]
  char		*intt;		// injection type [4]*/
  int		itmh;		// injection time hour [1]
  int		itmm;		// minute [1]
  int		itms;		// second [1]
  char		*col;		// collimator type (' ' = standard) 
  int		samp;		// sampling mode (0 = stat X = bins) [1]
  int		dtyp;		// data type (0=word, 1=byte) 
  int		fov;		// field of view type [1]
  int		prjl;		// projection length in members [2]
  float		tilt;		// gantry tilt angle
  float		slew;		// gantry slew angle
  int		elv;		// energy level (keV) [2]
  float		tiw;		// time window (ns)
  char		*hcom;		// comments [20]
  int		styp;		// scan type (0=em, 1=tr, 2=bl, 3=norm) [1]
  int		blan;		// blank scan number [4]
  int		tran;		// transmission scan number [4]
  int		par;		// parameter file number [1]
  int		norm;		// norm file number [2]
  int		dpr;		// data present in file (1=present)  [1]
  char		*tmn;		// tape name (user def) [8]
  int		ferr;		// fifo errors [4]
  float		flos;		// fifo loss rate
  float		inva;		// invalid rate count
  float		trat;		// total count rate
  int		tac;		// type of attenuation corr. [2]
  int		imfm;		// image format (eg 128) [2]
  char		*imtp;		// image type (' ' = activity) [10]
  char		*imun;		// image scale unit (eg nCi/cc) [10]
  float		pxs;		// pixel size (mm/pixel)
  char		*ffn;		// filter function (eg 'BOHM') [4]
  float		fwd;		// filter width (mm)
  int		slot;		// slot on DAP disk [2]
  char		*cntx;		// slot on DAP disk [10]
  int		age;		// patient's age [1]
  char		*sex;		// patient's sex [1]
  int		max;		// highest pixel in image [2]
  char		*reserved;	// reserved
  float		sing[8];	// Singles count rate per detector
  float		xrat[8];	// Physiological input count rate
  User6		*user[5];
  float		cycl;		// gate cycle time low limit
  float		cych;		// gate cycle time high limit
  float		gtll;		// gate low limit (in % of cycle)
  float		gtlh;		// gate high limit (in & of cycle)
  int		grnr;		// gate number [1]
  int		gtyp;		// gate type [1]
  int		frnr;		// time frame number [2] [1]
  float		dcy;		// mtm duty cycle (in %)
  int		ngat;		// number of gating bins [1]
  int		nbts;		// number of beats per frame [2] [1]
  int		nbr;		// number of beats rejected [2] [1]
  float		avc;		// average heart cycle incl. rejected beats
  float		ypos;		// y position of the couch
  Slice6	*slic[30];
  float		offs[30] ;
  char		*pad;

  // Utility members.
  int		posn;		// Current position in input file.
  int		noisy;
  float		volMax;		// Max pixel val in vol.
  float		volMin;		// Min pixel val in vol.

  // class GE6
public:
  enum { SHORT_HEADER  = 0,
	 LONG_HEADER  = 1 };		// Full header info.
  GE6( void );
  GE6( const GE6 &rhs );
  int		isDataFile( const char *name );
  void		read( ifstream &instr );
  void		read( ifstream &instr, int noisy );
  void		printit( const char *sptr, int i );
  void		printit( const char *sptr, const char *s );
  void		print( int option );
  void		print( void );
  void		printTime( void );
  float		measureTime( void );
  float		scanTime( void );
  float		frameDuration( void ) { return mtm; }
  float		getMag( int slice ) { return slic[slice]->getMag(); }
  int		getNumSlices( void ) { return PET6_SLICES; }
  int		getPixelCount( void ) { return PET6_DIM; }
  Slice6	*getSlice( int num ) { return slic[num]; }
  const char	*getPnm( void ) { return pnm; }
  float		getMax( int sli = -1 );
  float		getMin( int sli = -1 );

  // Required by same fns in PET
  float		getSliceThickness( void ) { return cd1; }
  float		getPixelWidth( void ) { return pxs; }
  float		getPixelHeight( void ) { return pxs; }

  // Utility functions.
  int		getint1( ifstream &instr );
  int		getint1( ifstream &instr, int noisy );
  short		getint2( ifstream &instr );
  short		getint2( ifstream &instr, int noisy );
  int		getint4( ifstream &instr );
  int		getint4( ifstream &instr, int noisy );
  float		getfloat( ifstream &instr );
  float		getfloat( ifstream &instr, int noisy );
  char		*getstring( ifstream &instr, int len );
  char		*copystring( const char *str, const int len );
  char		*getstring( ifstream &instr, int len, int noisy );
  short		**vals( void );

};  // class GE6
#endif
