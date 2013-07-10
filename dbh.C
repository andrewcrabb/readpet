// dbh.C
// Implementation of class dbh, Analyze header file structure.

#include <iostream>
#include <fstream>

#include "dbh.h"
#include "PET.h"

header_key::header_key( void ) {
  sizeof_hdr = 0;
  data_type[0] = '\0';
  db_name[0] = '\0';
  extents = 0;
  session_error = 0;
  regular = '\0';
  hkey_un0 = '\0';
}

void header_key::fill( PET *pet, int options ) {
  // These fields do not depend on the Advance object.
  regular = 'r';
  sizeof_hdr = sizeof(struct dsr);
  extents = 16384;

  // Fields that depend on the Advance object.
  strcpy( data_type, pet->getDataType().c_str() );
}

image_dimension::image_dimension( void ) {
  for ( int i = 0; i < 8; i++ ) {
    dim[i] = 0;
    pixdim[i] = 0.0;
  }
  vox_units[0] = '\0';
  cal_units[0] = '\0';
  unused1 = 0;
  datatype = 0;
  bitpix = 0;
  dim_un0 = 0;
  vox_offset = 0;
  roi_scale = 0;
  funused1 = 0;
  funused2 = 0;
  cal_max = 0;
  cal_min = 0;
  compressed = 0;
  verified = 0;
  glmax = 0;
  glmin = 0;
}

void image_dimension::print( void ) {
  int		i; 

  printf( "----------  image_dimension::print ----------\n" );
  for ( i = 0; i < 8; i++ )
    printf( "\tDim %d", i );
  printf( "\nCount" );
  for ( i = 0; i < 8; i++ )
    printf( "\t%-3d", dim[i] );
  printf( "\nDim" );
  for ( i = 0; i < 8; i++ )
    printf( "\t%-6.3f", pixdim[i] );
  printf( "\nVoxel units:\t%s\n", vox_units );
  printf( "Calibr. units:\t%s\n", cal_units );
  printf( "Data type:\t%d\n", datatype );
  printf( "Bits per pixel:\t%d\n", bitpix );
  printf( "Global max:\t%d\n", glmax );
  printf( "Global min:\t%d\n", glmin );
  printf( "------------------------------------------\n" );
  fflush(stdout);
}

void image_dimension::fill( PET *pet, int opt, int fr ) {
  dim[T_DIM] = 4;		// All Analyze files have time dimension.
  dim[X_DIM] = pet->getImageX();
  dim[Y_DIM] = pet->getImageY();

  // Num slices in vol depends if this is a modelled volume.
  int n = (opt & PET::OPT_PARA) ? pet->getNumModSlice() : pet->getNumSlice();
  dim[Z_DIM] = n;
  
  // No of frames in this file depends on whether saving as one vol.
  dim[N_DIM] = ( opt & PET::OPT_VOLU ) ? pet->getNumFrame() : 1;

  strcpy( cal_units, (opt & PET::OPT_MBQ ) ? "MBq/cc" : "nCi/cc" );
  sprintf( vox_units, "mm" );

  // 'Global' max depends on whether saving as one vol, and if using mean.
  bool mean = (opt & PET::OPT_MEAN) ? true : false;

  // Datatype is float for parametric images 0..10.
  if (opt & PET::OPT_PARA) {
    datatype = DT_FLOAT;
    bitpix = 32;
    // glmax/min in parametric vol actually max/min of modelled slices.
    glmax = int( pet->getModMax() );
    glmin = int( pet->getModMin() );
  } else {
    datatype = DT_SIGNED_SHORT;
    bitpix = pet->getImgDepth();
    glmax = int( pet->getMax( fr, mean ));
    glmin = int( pet->getMin( fr, mean ));
  }
  pixdim[X_DIM] = pet->getPixelWidth();
  pixdim[Y_DIM] = pet->getPixelHeight();
  pixdim[Z_DIM] = pet->getSliceThickness();

}

data_history::data_history( void ) {
  descrip[0] = '\0';
  aux_file[0] = '\0';
  orient = '\0';
  originator[0] = '\0';
  generated[0] = '\0';
  scannum[0] = '\0';
  patient_id[0] = '\0';
  exp_date[0] = '\0';
  exp_time[0] = '\0';
  hist_un0[0] = '\0';
  views = 0;
  vols_added = 0;
  start_field = 0;
  field_skip = 0;
  omax = omin = 0;
  smax = smin = 0;
}

// Take a string in form 'mm/dd/yyyy hh:mm:ss', return number of seconds.
//                        0123456789012345678
int toSec( const char *str ) {
  char	buff[100];
  int	tot = 0;
  int	h, m, s;

  fflush( stdout );
  str += 11;
  strncpy( buff, str, 2 );
  buff[2] = '\0';
  h = atoi( buff );
  str += 3;
  strncpy( buff, str, 2 );
  buff[2] = '\0';
  m = atoi( buff );
  str += 3;
  strncpy( buff, str, 2 );
  buff[2] = '\0';
  s = atoi( buff );
  // printf( "toSec(): h %d, m %d, s %d\n", h, m, s );
  return( h * 3600 + m * 60 + s );
}

void data_history::fill( PET *pet, int opt, int fr ) {
  float scnst = pet->getScanTime();
  float frmdu = pet->getFrameDurat( fr );
  float frmst = pet->getFrameStart( fr );
  float midPoint = frmst + frmdu / 2.0;

  // Use descrip field to hold frame start & duration and scan start.
  sprintf( descrip, "frmS %6d, frmD %6d, scanS %6d", 
	   (int)frmst, (int)frmdu, (int)scnst );
  // Use scannum field to hold frame no in study and frame midpoint (sec).
  sprintf( scannum, "%02d %d", fr, (int)midPoint );
  strcpy( patient_id, pet->getPatientID().c_str() );
  patient_id[9] = '\0';
  strcpy( exp_date, "exp_date" );
  strcpy( exp_time, "exp_time" );
}

void data_history::print( void ) {
  printf( "----------  data_history::print ----------\n" );
  printf( "descrip:    %s\n", descrip );
  printf( "scannum:    %s\n", scannum );
  printf( "patient_id: %s\n", patient_id );
  printf( "------------------------------------------\n" );
  fflush(stdout);
}

Analyze::Analyze( int noise ) {
  ds = NULL;
  noisy = noise;
}

Analyze::~Analyze( void ) {
  if ( ds )
    delete ds;
}

// Write an Analyze header to disk for the given PET-derived object.
//   pet:	Object to be written, derived from class PET.
//   nm:	Name of the output file.
//   opt:	Binary OR of options defined in Advance.h
//   fr:	Frame number.
void Analyze::writePET( PET *pet, const string &nm, int opt, int fr ) {
  char		buff[100];
  char		*ptr;
  ofstream	ofile;

  // Change the suffix of the file name.
  strcpy( buff, nm.c_str() );
  ptr = strchr( buff, '.' );
  strcpy( ptr, ".hdr" );

  ds = new dsr;
  ds->hk.fill( pet, opt );
  ds->dime.fill( pet, opt, fr );
  ds->hist.fill( pet, opt, fr );
  if ( (fr == 1) && noisy ) {
    ds->dime.print();
    ds->hist.print();
  }

  // Write the struct ds (size exactly 348 bytes) to disk.
  ofile.open( buff, ios::binary );
  if ( !ofile.is_open() ) {
    printf( "Cannot open output file %s", buff );
    exit( 1 );
  }
  ofile.write( (char *)ds, sizeof( struct dsr ) );
  ofile.close();
}
