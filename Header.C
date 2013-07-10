// Header.C

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <iterator>

#include "Header.h"

using namespace std;

HeaderElement::HeaderElement( const HeaderElement &rhs ) {
  _name.assign( rhs.name() );
  _value.assign( rhs.value() );
  // cout << "HeaderElement::HeaderElement(" << _name << ")" << endl;
}

const string HeaderElement::toString( void ) {
  ostringstream s;
  s << setw(20) << _name << ": " << _value;
  return string( s.str() );
}

int HeaderElement::setValue( const string &value ) {
  _value.assign( value );
  return( 0 );
}

int HeaderElement::intValue( void ) {
  int		intVal;

  sscanf( _value.c_str(), "%d", &intVal );
  return intVal;
}

long int HeaderElement::longValue( void ) {
  int		longVal = 0;

  return( longVal );
}

float HeaderElement::floatValue( void ) {
  float		floatVal;

  sscanf( _value.c_str(), "%f", &floatVal );
  return( floatVal );
}

HeaderGroup::HeaderGroup( const string &name, int opt ) {
  _name.assign( name );
  _options = opt;
}

HeaderGroup::HeaderGroup( const HeaderGroup &rhs ) {
  _name.assign( rhs.name() );
  for (map<string, HeaderElement *>::const_iterator iter = rhs._elements.begin();
       iter != rhs._elements.end(); iter++ ) {
    _elements[(*iter).first] = new HeaderElement( *((*iter).second) );
  }
  _elementNames = rhs._elementNames;
  // cout << "HeaderGroup::HeaderGroup(" << _name << "): " << _elements.size() << " elements" << endl;
}

const string HeaderGroup::valueOf( const string &elementName ) {
  return _elements[elementName]->value();
}

int HeaderGroup::addElements( const vector<string> &tokens ) {
  for ( vector<string>::const_iterator iter = tokens.begin(); 
	iter != tokens.end(); iter++ ) {
    addElement( new HeaderElement( *iter ));
  }
  return( 0 );
}

// Store the new element in a map, and name in ordinal index in vector.

int HeaderGroup::addElement( HeaderElement *element ) { 
  _elements[element->name()] = element;
  _elementNames.push_back( element->name() );
  return( 0 );
}

int HeaderGroup::setElement( const string &name, const string &value ) {
//   cout << "HeaderGroup::setElement(" << name << ", " << value << ")" << endl;
  _elements[name]->setValue( value );
  return( 0 );
}

int HeaderGroup::setElements( vector<string> &values, ifstream &input ) {
  vector<string>::iterator valIter, namIter;
  int		i = 0;
  
//   cout << "HeaderGroup::setElements(" << _name << "): " << _elementNames.size() << " names, " << values.size() << " values" << endl;
  // Values and names are in the same order; traverse both vectors.
  for ( valIter = values.begin(), namIter = _elementNames.begin(); 
	valIter != values.end(); valIter++, namIter++ ) {
    setElement( *namIter, *valIter );
  }
  return( 0 );
}

const string HeaderGroup::toString( void ) {
  string	ret;
  vector<string>::iterator ptr;
  ostringstream s;

  int i = 0;
   for ( ptr = _elementNames.begin(); ptr != _elementNames.end(); ptr++ ) {
     if ( ptr == _elementNames.begin() )
       continue;
     // s << setw(4) << i++ << _elements[*ptr]->toString() << "\n";
     s << _elements[*ptr]->toString() << "\n";
   }
  return string( s.str() );
}

HeaderElement *HeaderGroup::elementAt( const string &elementName ) {
  return _elements[elementName];
}

HeaderElement *HeaderGroup::elementAt( int indx ) {
  return elementAt( _elementNames[indx] );
}

const vector<string> *HeaderGroup::elementNames( void ) {
  vector<string> *names = new vector<string>;

  for ( vector<string>::iterator ptr = _elementNames.begin(); 
	ptr != _elementNames.end(); ptr++ ) {
    names->push_back( *ptr );
  }
  return names;
}

int HeaderGroup::indexOfElement( const string &name ) {
  int		count = 0, indx = -1;
  vector<string>::iterator ptr;

  for ( ptr = _elementNames.begin(); ptr != _elementNames.end(); ptr++ ) {
    if ( (*ptr).compare( name ) == 0 ) {
      indx = count;
      break;
    }
    count++;
  }
  return indx;
}

Image::Image( void ) {
  _pixelVals = 0;
  _meanVals = 0;
  _numMeanFrames = 0;
  cout << "Image::Image()" << endl;
}

Image::Image( ImageGroup *parent ) {
  const vector<string> *names = parent->elementNames();
  string	name;

  for ( vector<string>::const_iterator iter = names->begin(); 
	iter != names->end(); iter++ ) {
    name = *iter;
    _elementNames.push_back( name );
    _elements[name] = new HeaderElement( name );
  }
  _pixelVals = 0;
  _meanVals = 0;
  _numMeanFrames = 0;
}

void Image::setIndex( const vector<int> indx ) {
  _index = indx;
}

char *Image::getPixelVals( void ) {
  return( _pixelVals );
}

// Store values as normal, then pixel values.

int Image::setElements( vector<string> &values, ifstream &input ) {
  vector<string>::iterator namIter, valIter;

  for ( namIter = _elementNames.begin(), valIter = values.begin(); 
	valIter != values.end(); namIter++, valIter++ ) {
    setElement( *namIter, *valIter );
  }
  // Pixel values.
  int pos0 = input.tellg();
  readBlob( input, &_pixelVals );
  int pos1 = input.tellg();
  skipBlob( input, tmp );
  int pos2 = input.tellg();
  int readB = pos1 - pos0;
  int skipB = pos2 - pos1;
//    cout << "Image::setElements(): readB " << readB << ", skipB " << skipB << endl;
  return( 0 );
}

// Sum given data to integer array for later division and storage.

int Image::addData( Image *image ) {
  char		*imagePixels = image->getPixelVals();
  short		*imgPtr;
  int		i, *iPtr;

  cout << "Image::addData()" << endl;
  if ( _meanVals == 0 ) {
    // First data added to this Image (slice).
    _meanVals = new char( 16384 * sizeof( int ));
    memset( _meanVals, 0, 16384 * sizeof( int ));
  }
  
  // Iterate overincoming pixels, adding to existing vals.
  iPtr = (int *)_meanVals;
  imgPtr = (short *)imagePixels;
  for ( int i = 0; i < 16384; i++ ) {
    *iPtr = ( *iPtr + *imgPtr );
    iPtr++;
    imgPtr++;
  }
  _numMeanFrames++;
  return 0;
}

// Divide previously summed pixel vals to give mean frame.

int Image::calculateMeanData( void ) {
  short		*sPtr, val;
  int		*iPtr = (int *)_meanVals;

  if ( _pixelVals == 0 ) {
    _pixelVals = new char( 16384 * sizeof( short ));
    memset( _pixelVals, 0, 16384 * sizeof( short ));
  }
  
  sPtr = (short *)_pixelVals;
  for ( int i = 0; i < 16384; i++ ) {
    val = *iPtr / _numMeanFrames;
    *sPtr = val;
    iPtr++;
    sPtr++;
  }
  return 0;
}

float Image::sliceMax( void ) {
  float max = elementAt( "max_pixel_value" )->floatValue();
  return( max );
}
 
float Image::sliceMin( void ) {
  float min = elementAt( "min_pixel_value" )->floatValue();
  return( min );
}

int ImageGroup::writeData( int fr, int sl, ofstream &outfile, int opt ) {
  Image		*image = imageAt( fr, sl );
  long		imageSize = image->elementAt( "image_size" )->intValue();
  float		scaleFactor = image->elementAt( "scale_factor" )->floatValue();
  char		*pixelVals = image->getPixelVals();
  short		sval, svals[16384];
  short		sval0, sval1, sval2, sval3;
  char		cval0, cval1, cval2, cval3;
  char		*csrc, *cdst;
  char		*cptr = (char *)pixelVals;
  short		*sptr = (short *)pixelVals;

  // cout << "ImageGroup::writeData(" << fr << ", " << sl << "): factor " << scaleFactor << endl;

  scaleFactor *= _convFactor;
  if ( isBigEndian() ) {
    // No byte swap.
    for ( int i = 0; i < 16384; i++ ) {
      sval = sptr[i];
      svals[i] = (short)(sval * scaleFactor);
    }
  } else {
    // Swap bytes for PC.
    for ( int i = 0; i < 16384; i++ ) {
      csrc = (char *)&(sptr[i]);
      cdst = (char *)&sval;
      cdst[0] = csrc[1];
      cdst[1] = csrc[0];
      svals[i] = (short)(sval * scaleFactor);
    }
  }

  // Analyze format files are reversed in Y; need to swap order of rows.
  // Even number of rows, so can work towards the middle from both ends.
  // Rows are 128 pixels (256 bytes).
  if ( opt & PET::OPT_ANAL && !(opt & PET::OPT_PARA )) {
    char buff[256], *src, *dest, *cptr;
    cptr = (char *)svals;
    for ( int i = 0; i < 64; i++ ) {
      src = cptr + i * 256;	      // i'th row from start.
      dest = cptr + (127 - i) * 256;  // i'th row from end.
      memcpy( buff, src, 256 );  // 128 shorts from start to buff.
      memcpy( src, dest, 256 );
      memcpy( dest, buff, 256 );
    }
  }

  outfile.write( (char *)svals, 16384 * sizeof( short ) );
  if ( outfile.bad() ) {
    cerr << "ImageGroup::writeData() error" << endl;
    return( -1 );
  }
  return( 0 );
}

ImageGroup::ImageGroup( const string &name, int opt ) : HeaderGroup( name, opt ) {
  _convFactor = ( opt & PET::OPT_MBQ ) ? 1 : MBQ_TO_NCI;
}

// ImageGroup keeps vector of HeaderGroups, one per Image object.
// The newly stored object is a clone of this, to ensure initialized.

int ImageGroup::setElements( vector<string> &values, ifstream &input ) {
  Image		*image = new Image( this );

  // cout << "ImageGroup::setElements()" << endl;
  // Parse values then store image pointers in map of [frame, slice].
  image->setElements( values, input );
  _images.push_back( image );

  return( 0 );
}

// Store [frame, slice] index for images.  Frame 0 indexed; slice 1 indexed.
// Relies upon Frames having been sorted first.

void ImageGroup::sortMembers( Advance *parent ) {
  ImagePtr	image;
  int		frame, slice;
  int		indx = 0;
  vector<int>	v(10);

  for ( vector<ImagePtr>::iterator iter = _images.begin(); 
	iter != _images.end(); iter++ ) {
    image = *iter;
    string	frameID  = image->elementAt( _frameIDIndex )->value();
    frame = parent->frameIndex( frameID );
    slice = image->elementAt( _sliceIDIndex )->intValue();
    // imageIndex indexes <frame, slice> to index into images[]
    v[_FRMINDX] = frame;
    v[_SLIINDX] = slice;
    _imageIndex[v] = indx;
    (*iter)->setIndex( v );
    // Keep a track of how many images (total slices) and frames.
    _frameCount[frame]++;
    indx++;
  }
}

int ImageGroup::identElements( void ) {
  _frameIDIndex   = indexOfElement( "frame_id" );
  _sliceIDIndex   = indexOfElement( "slice_number" );

//   cout << "ImageGroup::identElements(): frameIndex " << _frameIDIndex << ", sliceIndex " << _sliceIDIndex << endl;
  return( 0 );
}

// Group 'Image' has multi images: Don't print them all.

const string ImageGroup::toString( void ) {
  int		i = 0;
  ostringstream ret;

  ret << "ImageGroup__toString() has " << _images.size() << " images like" << endl;
  ret << imageAt( 0, 0 )->toString();
  return string( ret.str() );
}


int ImageGroup::calculateDimensions( void ) {
  Image		*image = imageAt( 0, 0 );
  int		indx;

  _numImages = _images.size();
  _numFrames = _frameCount.size();
  _numSlices = _numImages / _numFrames;
  
//   cout << "ImageGroup::calculateDimensions(): numImages " << _numImages << ", numFrames " << _numFrames << ", numSlices " << _numSlices << endl;
  // cout << imageAt( 0, 0 )->toString();
  cout << "----------------------------------------" << endl;

  _imageX = image->elementAt( "image_array_width" )->intValue();
  _imageY = image->elementAt( "image_array_height" )->intValue();
  _imageZ = image->elementAt( "image_depth" )->intValue();
  _imageDepth = image->elementAt( "image_depth" )->intValue();

  _pixelWidth = image->elementAt( "pixel_width" )->floatValue();
  _pixelHeight = image->elementAt( "pixel_height" )->floatValue();
  _sliceThickness = image->elementAt( "image_thickness" )->floatValue();

//   cout << "ImageGroup::calculateDimensions(), imageX " << _imageX << ", imageY " << _imageY << ", imageZ " << _imageZ << ", pixelWidth " << _pixelWidth << ", pixelHeight " << _pixelHeight << endl;

  return( 0 );
}

float ImageGroup::getMax( int fr ) {
  float slmax, frmax = -10000.0;

  for ( int sl = 0; sl < _numSlices; sl++ ) {
    Image *image = imageAt( fr, sl );
    slmax = image->sliceMax();
    frmax = ( slmax > frmax ) ? slmax : frmax;
  }
  return frmax;
}

float ImageGroup::getMin( int fr ) {
  float slmin, frmin = 10000.0;

  for ( int sl = 0; sl < _numSlices; sl++ ) {
    Image *image = imageAt( fr, sl );
    slmin = image->sliceMin();
    frmin = ( slmin < frmin ) ? slmin : frmin;
  }
  return frmin;
}

float ImageGroup::getMax( void ) {
  float		frmax, max = -10000.0;

  for ( int fr = 0; fr < _numFrames; fr++ ) {
    frmax = getMax( fr );
    max = ( frmax > max ) ? frmax : max;
  }
  return max;
}

float ImageGroup::getMin( void ) {
  float		frmin, min = 10000.0;

  for ( int fr = 0; fr < _numFrames; fr++ ) {
    frmin = getMin( fr );
    min = ( frmin < min ) ? frmin : min;
  }
  return min;
}

float ImageGroup::minValue( void ) {
  int		min;

  sscanf( _elements["min_pixel_value"]->value().c_str(), "%d", &min );
  return float( min );
}

float ImageGroup::maxValue( void ) {
  int		max;

  sscanf( _elements["max_pixel_value"]->value().c_str(), "%d", &max );
  return float( max );
}

Image *ImageGroup::imageAt( int frame, int slice ) {
  vector<int> v(10);
  
  v[0] = frame;
  v[1] = slice;
  return( _images[_imageIndex[v]] );
}

ImageGroup *ImageGroup::makeMean( void ) {
  ImageGroup	*meanFrame = new ImageGroup( string("mean"), 0 );

  cout << "ImageGroup::makeMean()" << endl;
  for ( int sl = 0; sl < _numSlices; sl++ ) {
    cout << "ImageGroup::makeMean(" << sl << ")" << endl;
    for ( int fr = 0; fr < _numFrames; fr++ ) {
      meanFrame->addImageData( sl, imageAt( fr, sl ));
    }
  }
  meanFrame->calculateMeanData();
  return meanFrame;
}

// Add given image's data to given slice.  Create slice if not present.

int ImageGroup::addImageData( int sl, Image *image ) {
  vector<int>	v;
  map<vector<int>, int>::iterator mapIter;
  Image		*meanSlice;

  cout << "ImageGroup::addImageData()" << endl;
  v[0] = 0;		// Frame no. always 0 for mean image.
  v[1] = sl;
  mapIter = _imageIndex.find( v );
  if ( mapIter == _imageIndex.end() ) {
    cout << "ImageGroup::addImageData() creating slice " << sl << endl;
    // This slice image does not exist.
    meanSlice = new Image( this );
    _images[sl] = meanSlice;
    _imageIndex[v] = sl;
  } else {
    cout << "ImageGroup::addImageData() using slice " << sl << endl;
    meanSlice = _images[(*mapIter).second];
  }
  // Now mapIter points to an Image for this slice.
  meanSlice->addData( image );
  return 0;
}

int ImageGroup::calculateMeanData( void ) {
  for ( int sl = 0; sl < _numSlices; sl++ ) {
    _images[sl]->calculateMeanData();
  }
  return 0;
}

int ImageGroup::writeMean( ofstream &outfile, int options ) {
  int ret = 0;

  for ( int sl = 0; sl < _numSlices && ret == 0; sl++ ) {
    ret += writeData( 0, sl, outfile, options );
  }
  return ret;
}

Frame::Frame( FrameGroup *parent ) {
  const vector<string> *names = parent->elementNames();
  string	name;

  for ( vector<string>::const_iterator iter = names->begin(); 
	iter != names->end(); iter++ ) {
    name = *iter;
    _elementNames.push_back( name );
    _elements[name] = new HeaderElement( name );
  }

  _frameIDIndex  = parent->_frameIDIndex;
  _acqStart      = parent->_acqStart;
  _acqDuration   = parent->_acqDuration;
}

const string Frame::acqStart( void ) {
  return elementAt(_acqStart)->value();
}

const string Frame::toString( void ) {
  ostringstream s;
  s << "frame[" << _frameIndex << "]: " << acqStart();
  return string( s.str() );
}

void Frame::setRange( float frmax, float frmin ) {
  _frmax = frmax;
  _frmin = frmin;
}

int FrameGroup::identElements( void ) {
  _frameIDIndex  = indexOfElement( "frame_id" );
  _acqStart      = indexOfElement( "acq_start" );
  _acqDuration   = indexOfElement( "acq_duration" );

//   cout << "FrameGroup::identElements(): frameIndex " << _frameIDIndex << ", acqStart " << _acqStart << ", acqDuration " << _acqDuration << endl;
  return( 0 );
}

int FrameGroup::setElements( vector<string> &values, ifstream &input ) {
  Frame		*frame = new Frame( this );
  
  // Parse values then store frame pointers in vector.
  frame->setElements( values, input );
  string framestr = frame->elementAt( _frameIDIndex )->value();
  _frames[framestr] = frame;

  skipBlob( input, tmp );
  // cout << "FrameGroup::setElements(" << framestr << ")" << endl;
  return( 0 );
}

const string FrameGroup::toString( void ) {
  map<string, FramePtr>::const_iterator iter;

  ostringstream ret;
  ret << "FrameGroup__toString() has " << _frames.size() << " frames" << endl;
  ret << "FrameGroup__toString() output suspended to avoid colon value" << endl;
//   iter = _frames.begin();
//   ret << "--------------------" << endl;
//   ret << (*iter).second->toString() << endl;
//   ret << "--------------------" << endl;

  // Need this for detailsADV to get frame count.
  ret << "Frames : " << _frames.size() << endl;
  
//   // Local array of Frames to be sorted by time.
//   for ( iter = _frames.begin(); iter != _frames.end(); iter++ )
//     ret << (*iter).second->toString() << endl;
  return string( ret.str() );
}

int FrameGroup::frameIndex( const string &frameStr ) {
  return _frameMap[ frameStr ];
}

class SortFrameByTime {
public:
  bool operator()( const FramePtr &lhs, const FramePtr &rhs ) {
    const string lhsStart = lhs->acqStart();
    const string rhsStart = rhs->acqStart();
    bool ret = ( lhsStart < rhsStart );
    return( ret );
  }
};

// Create index into _frames to allow access by ordinal index.

void FrameGroup::sortMembers( Advance *parent ) {
  vector <FramePtr> frames;
  map<string, FramePtr>::iterator iter;
  
  // Local array of Frames to be sorted by time.
  for ( iter = _frames.begin(); iter != _frames.end(); iter++ )
    frames.push_back( (*iter).second );
  sort( frames.begin(), frames.end(), SortFrameByTime() );

  // Store posn index in each Frame, keep external index.
  _frameIndex.erase( _frameIndex.begin(), _frameIndex.end() );
  int	indx = 0;
  for ( iter = _frames.begin(); iter != _frames.end(); iter++ ) {
    _frameIndex.push_back( (*iter).first );
    _frameMap[ (*iter).second->elementAt( _frameIDIndex )->value()] = indx;
    (*iter).second->setIndex( indx++ );
  }

}

void FrameGroup::printFrameTimes( vector<FramePtr> &frames, const string &msg ) {
  vector<FramePtr>::iterator iter;
  
  cout << "FrameGroup::printFrameTimes(" << msg << ") begin" << endl;
  for ( iter = frames.begin(); iter != frames.end(); iter++ )
    cout << (*iter)->toString() << endl;
  cout << "FrameGroup::printFrameTimes(" << msg << ") end" << endl;
}

void FrameGroup::setRange( int frame, float frmax, float frmin ) {
  _frames[_frameIndex[frame]]->setRange( frmax, frmin );
}

const string FrameGroup::valueOfFrame( const string &elementName, int frmno ) {
  Frame		*frame = _frames[_frameIndex[frmno]];
//   string	value = frame->valueOf( elementName );
//   cout << "Header::FrameGroup::valueOf(" << frmno << ", " << elementName << ") returning >" << value << "<" << endl;
  return string( frame->valueOf( elementName ));
}


int CountrateGroup::setElements( vector<string> &values, ifstream &input ) {
  HeaderGroup::setElements( values, input );
  skipBlob( input, tmp );
  return( 0 );
}

int ImagesetGroup::setElements( vector<string> &values, ifstream &input ) {
  HeaderGroup::setElements( values, input );
  skipBlob( input, tmp );
  skipBlob( input, tmp );
  skipBlob( input, tmp );
  return( 0 );
}

int HeaderGroup::skipBlob( ifstream &input, string &name ) {
  long size, pos;
  char tmpBuf[3000];

  pos = input.tellg();
  input.getline( tmpBuf, 2048 );
  sscanf( tmpBuf, "%d", &size );
  getline( input, name );
  input.getline( tmpBuf, 20 );

  if ( size != 0 ) {
    input.seekg( size, ios::cur );
    input.getline( tmpBuf, 2048 );
  } else {
    input.getline( tmpBuf, 2048 );
  }
  pos = input.tellg();
  return( 0 );
}

int HeaderGroup::readBlob( ifstream &input, char **vals ) {
  long size, pos0, pos1, nchar;
  char tmpBuf[3000], name[200];

  input.getline( tmpBuf, 2048 );	// Size line.
  sscanf( tmpBuf, "%d", &size );	// No. chars to read.
  input.getline( name, 200 );		// Name line.
  input.getline( tmpBuf, 20 );		// 'binary'.

  if ( size != 0 ) {
    *vals = new char[size];
    int poss = input.tellg();
    input.read( *vals, size );

    int post = input.tellg();
    int diff = post - poss;
    // cout << "HeaderGroup::readBlob(" << size << ") = " << diff << endl;

    input.getline( tmpBuf, 2048 );
  } else {
    input.getline( tmpBuf, 2048 );
  }
  return( 0 );
}

int HeaderGroup::isBigEndian( void ) {
  short		n = 1;

  return ((char *)&n)[0] == 0;
}

int DateTime::parse( void ) {
  sscanf( _dateString.c_str(), "%d-%d-%d %d:%d:%d", &_year, &_month, &_day, &_hour, &_minute, &_second );
  // cout << "DateTime::parse(" << _dateString << ")" << _month << "/" << _day << "/" << _year << "  " <<  _hour << ":" << _minute << ":" << _second << endl;
  return 0;
}

int DateTime::toSec( void ) {
  return( _hour * 3600 + _minute * 60 + _second );
}

const string DateTime::toString( void ) {
  ostringstream s;
  char buff[100];

  sprintf( buff, "%02d/%02d/%02d   %02d:%02d:%02d", _month, _day, _year, _hour, _minute, _second );
//   s << _month << "/" << _day << "/" << _year << "   " << _hour << ":" _minute << ":" << _second;
  return string( buff );
}
