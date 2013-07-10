/*@Start***********************************************************
 * GEMS C source File
 * Copyright (C) 1991 The General Electric Company
 *
 *  File Name: GEtypes.h
 *
 * $Header: /usr/pet4/cvsroot/system/GEtypes.h,v 1.5 1998/04/14 18:54:52 parthan Exp $
 */
 
/*@Description
* As per the Software C Coding Standards, July 2, 1991,
 * the Software Developer is required to use the typedef's
 * shown below in place of all basic data types.
 */

#ifndef GEtypes_INCL
#define GEtypes_INCL

#ifndef _AK_GLOBAL_H_   /* These variables are defined in ak_globas.h in
                           the access kit. - Vinay, Apr 14,1998. */


typedef char s8;
typedef unsigned char n8;
typedef short s16;
typedef unsigned short n16;
typedef long s32;
typedef unsigned long n32;
typedef float f32;
typedef double f64;


/* INSITE Type Definition */
typedef n8 INSITE[20];

#endif /*  _AK_GLOBAL_H_ */


#endif
