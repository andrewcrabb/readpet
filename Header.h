// Header.h
// Definitions of classes HeaderElement and HeaderGroup.

#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <map>
#include <string>

#include "Advance.h"

using namespace std;

class Advance;

// Descriptor of one header element.

class HeaderElement {
private:
  string	_name;
  string	_value;
public:
		HeaderElement( void ) {}
		HeaderElement( const string &name, const string &value = "" ) :
		  _name( name ), _value( value ) {}
		HeaderElement( const HeaderElement &rhs );
  const string	toString( void );
  const string	name( void ) const { return string( _name ); }
  const string	value( void ) const { return string( _value ); }
  int		intValue( void );
  long int	longValue( void );
  float		floatValue( void );
  int		setValue( const string &value );
};

// Group of header elements.

class HeaderGroup {
private:
protected:
  string	_name;
  map<string, HeaderElement *> _elements;	// Elements themselves.
  vector<string> _elementNames;		// Element names in order.
  int		_options;
public:
		HeaderGroup( void ) {}
		HeaderGroup( const string &name, int opt );
		HeaderGroup( const HeaderGroup &rhs );
  int		addElements( const vector<string> &tokens );
  int		addElement( HeaderElement *element );
  int		setElement( const string &name, const string &value );
  virtual int	setElements( vector<string> &values, ifstream &input );
  virtual int	identElements( void ) {   return( 0 ); }
  virtual void	sortMembers( Advance *parent ) {}
  virtual const string	toString( void );
  HeaderElement *elementAt( const string &elementName );
  HeaderElement *elementAt( int indx );
  int		indexOfElement( const string &name );
  int		addImage( vector<string> &values );
  int		skipBlob( ifstream &input, string &name );
  int		readBlob( ifstream &input, char **vals );
  int		isBigEndian( void );
  const string	name( void ) const { return( string( _name )); }
  const vector<string> *elementNames( void );
  const string	valueOf( const string &elementName );
  string	tmp;
};

// An Image holds one slice of a Frame.  ImageGroup holds multi Images.

class ImageGroup;

class Image : public HeaderGroup {
private:
  vector<int>	_index;
  char		*_pixelVals;
  char		*_meanVals;	// Use int rather than short for summing.
  int		_numMeanFrames;
public:
  Image( void );
  Image( ImageGroup *parent );
  // const string	toString( void );
  void		setIndex( const vector<int> indx );
  // int		writeData( ofstream &outfile, int opt );
  char		*getPixelVals( void );
  int		setElements( vector<string> &values, ifstream &input );
  int		addData( Image *image );
  int		calculateMeanData( void );
  float		sliceMax( void );
  float		sliceMin( void );
};
typedef Image *ImagePtr;

class ImageGroup : public HeaderGroup {
private:
  vector<ImagePtr> _images;
  map<vector<int>, int> _imageIndex;
  int		_frameIDIndex, _sliceIDIndex;
  int		_acqStart, _acqDuration;
  int		_numImages, _numFrames, _numSlices;
  int		_imageX, _imageY, _imageZ, _imageDepth;
  float		_pixelWidth, _pixelHeight, _sliceThickness;
  int		_minIndex, _maxIndex;
  int		_convFactor;		// MBq to NCi/CC
  map<int, int> _frameCount;
  static const int _FRMINDX = 0;
  static const int _SLIINDX = 1;
  static const int MBQ_TO_NCI = 27027;	// MBq to NCi/CC
public:
		ImageGroup( const string &name, int options );
  int		setElements( vector<string> &values, ifstream &input );
  int		identElements( void );
  void		sortMembers( Advance *parent );
  int		calculateDimensions( void );
  Image		*imageAt( int frame, int slice );
  ImageGroup	*makeMean( void );
  int		addImageData( int sl, Image *image );
  int		writeMean( ofstream &outfile, int options );
  int		calculateMeanData( void );

  float		minValue( void );
  float		maxValue( void );

  // These ones come in from Advance.h
  int		getImageX( void ) { return _imageX; }	// Image array width.
  int		getImageY( void ) { return _imageY; }	// Image array height.
  int		getImageZ( void ) { return _imageZ; }	// Image array height.
  int		getNumImage( void ) { return _numImages; } // Total slices.
  int		getNumSlice( void ) { return _numSlices; } // Slices per frame.
  int		getNumFrame( void ) { return _numFrames; } // Frames per study.
  int		getImgDepth( void ) { return _imageDepth;} // Bits per pixel.
  float		getPixelWidth( void ) { return _pixelWidth; }// Pixel X dim mm
  float		getPixelHeight( void ) { return _pixelHeight; }// Pixel Y dim.
  //  float	getSliceThickness( void ) { return getImageZ(); }// Pixel Z dim
  float		getSliceThickness( void ) { return _sliceThickness; }// Pixel Z dim
  float		getMax( int fr );		// Frm/mean nCi/cc.
  float		getMin( int fr );		// Frm/mean nCi/cc.
  float		getMax( void );			// Over all frames
  float		getMin( void );			// Over all frames
  float		getScanTime( void);		// Secs since midnight.
  float		getFrameStart( int fr );	// Secs since scan start.
  float		getFrameDurat( int fr );	// Secs.
  int		writeData( int fr, int sl, ofstream &outfile, int opt );
  const string	toString( void );
};

// A Frame holds values of one frame.  Multi Frames in a FrameGroup.

class FrameGroup;

class Frame : public HeaderGroup {
private:
  int		_frameIDIndex, _acqStart, _acqDuration;
  int		_frameIndex;		// Ordinal index of this frame.
  float		_frmax, _frmin;
public:
		Frame( void ) : _frameIndex( -1 ) {}
		Frame( FrameGroup *parent );
  void		setIndex( int i ) { _frameIndex = i; }
  void		setRange( float frmax, float frmin );
  const string	acqStart( void );
  const string	toString( void );
};

typedef Frame *FramePtr;

class FrameGroup : public HeaderGroup {
private:
  int		_frameIDIndex, _acqStart, _acqDuration;
  map<string, Frame *>	_frames;	// Maps frame ID to frame.
  map<string, int>	_frameMap;	// Maps frame ID to frame index.
  vector<string>	_frameIndex;	// Maps index to frame ID.
public:
  friend class Frame;
		FrameGroup( string &name, int opt ) : HeaderGroup( name, opt ) {}
  int		identElements( void );
  int		setElements( vector<string> &values, ifstream &input );
  void		sortMembers( Advance *parent );
  int		frameIndex( const string &frameStr );
  void		setRange( int frame, float frmax, float frmin );
  const string  valueOfFrame( const string &elementName, int frmno = 0 );
  void		printFrameTimes( vector<FramePtr> &f, const string &m = "" );
  const string	toString( void );
};

class CountrateGroup : public HeaderGroup {
public:
		CountrateGroup(string &name, int opt) : HeaderGroup(name, opt) {}
  int		setElements( vector<string> &values, ifstream &input );
};

class ImagesetGroup : public HeaderGroup {
public:
		ImagesetGroup(string &name, int opt) : HeaderGroup(name, opt) {}
  int		setElements( vector<string> &values, ifstream &input );
};

class DateTime {
private:
  string	_dateString;
  int		_year, _month, _day, _hour, _minute, _second;
public:
		DateTime( void ) {}
		DateTime( const string &date ) : _dateString( date ) {}
  int		parse( void );
  int		toSec( void );
  const string	toString( void );
};

#endif
