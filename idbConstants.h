/*@Start***********************************************************
 * GEMS C include File
 * Copyright (C) 1992 The General Electric Company
 *
 *      File Name: idbConstants.h
 *      Developer(s):  Martin Carter and
 *                     Kacy Holder, CPU Inc.
 *
 * $Header: /usr/pet4/cvsroot/dragon/db/dbinc/idbConstants.h,v 1.44 1999/06/23 12:16:35 ross Exp $
 */

/*@Description
 *    This header file defines Dragon database constants, including
 *    definitions of valid attribute choices.
 */

/* Update History:
 *     03/10/92  -  MSC: DB Schema 8.0 Upgrade (KCH)
 *     06/12/92  -  MSD: DB Schema 8.2 Upgrade (KCH)
 *     07/15/92  -  MSD: Minor updates for Display (KCH)
 *     07/30/92  -  MSIE: DB Schema 8.5 Upgrade (KCH)
 *     09/10/92  -  MSE: DB Schema 8.6 Upgrade (KCH)
 *     01/21/93  -  MSF: DB Schema 8.9 Upgrade (KCH)
 *     02/05/93  -  MSF: DB Schema 8.9 Fixes (KCH)
 *     02/05/93  -  MSF: added new graph axis units (MTB)
 *     03/17/93  -  MSG: added new imageset units-(pixels-MTB)
 *     03/25/93  -  MSG: added concurrency options (KCH)
 *     05/24/93  -  MSH: added S_CMP_SINO smoothing params
 *     08/04/93  -  REL 1.5: DB Schema 9.0 (FJB)
 *     09/17/93  -  REL1.5: added idb_axis_units for plot (MTB)
 *     11/01/93  -  REL1.5 T+E additions (FJB)
 *     02/11/94  -  REL2.0 Schema 10.0 Rev A&B changes (FJB)
 *     03/04/94  -  Reverted to 64 char uncompressed ID's (FJB)
 *     04/11/94  -  Schema 10 - B updates (FJB)
 *     08/17/94  -  DICOM stings for REL2_0D (PJD)
 */

#ifndef idbConstants_INCL
#define idbConstants_INCL

/*********************************************************************
 * Length of string attributes (Informix data type CHAR)
 *
 *   Note that all of the string lengths are 1 character greater than
 *   the definition in the Dragon Database Tables document to account
 *   for the extra character needed by Informix.
 *
 *********************************************************************/

/* length of unique identifier fields */
#define IDB_LEN_ID_0150                  17  /* 10.0 FJB */
#define IDB_LEN_ID_SHARC                 17  /* 10.0 FJB */
#define IDB_LEN_ID                       65  /* 10.0 FJB 03/04/94 */
#define IDB_LEN_DB_ID                     8
#define IDB_LEN_TABLE_ID                  8
#define IDB_CNT_ID_INTS                   2

/* NOTE: If any of the above are changed,
 * check all *.ec and *.ecc files for  
 * hardcoded instances.
 */

#define IDB_LEN_AXES_COLOR               21  /* 8.2 */
#define IDB_LEN_BACKGROUND_COLOR         21  /* 8.2 */
#define IDB_LEN_BATCH_DESCRIPTION        41
#define IDB_LEN_CAL_DESCRIPTION          33  /* 8.0 */
#define IDB_LEN_CM_DESCRIPTION           33
#define IDB_LEN_CM_NAME                  33
#define IDB_LEN_COLOR                    21  /* 8.2 */
#define IDB_LEN_CONTRAST_AGENT           65  /* 10.0 FJB */  
#define IDB_LEN_COMPATIBLE_VERSION        6  /* 8.5 */
#define IDB_LEN_CURVE_LABEL              61  /* 8.0 */
#define IDB_LEN_CURVE_NAME               33  /* 8.0 */
#define IDB_LEN_DIAGNOSTICIAN            33
#define IDB_LEN_EXAM_DESC_0150           33  /* 10.0 FJB */
#define IDB_LEN_EXAM_DESC                65  /* 10.0 FJB */
#define IDB_LEN_FONT_NAME                33  /* 8.0 */
#define IDB_LEN_FONT_SIZE                 3  /* 8.0 */
#define IDB_LEN_FOR_IDENTIFIER           65  /* 10.0 FJB */
#define IDB_LEN_FOREGROUND_COLOR         21  /* 8.2 */
#define IDB_LEN_GRAPH_DESCRIPTION       129  /* 8.2 */
#define IDB_LEN_HOSPITAL_IDENTIFIER       9  /* 10.0 FJB */
#define IDB_LEN_HOSPITAL_NAME            33
#define IDB_LEN_IS_DESCRIPTION_0150      33  /* 10.0 FJB */
#define IDB_LEN_IS_DESCRIPTION           65  /* 10.0 FJB */
#define IDB_LEN_LABEL_FONT_NAME          33  /* 8.2 */
#define IDB_LEN_LANDMARK_ABBREV           3
#define IDB_LEN_LANDMARK_NAME_0150       33  /* 10.0 FJB */
#define IDB_LEN_LANDMARK_NAME            65  /* 10.0 FJB */
#define IDB_LEN_LEGEND_FONT_NAME         33  /* 8.2 */
#define IDB_LEN_LEGEND_FONT_SIZE          3  /* 8.2 */
#define IDB_LEN_MANUFACTURER_0150        21  /* 10.0 FJB */
#define IDB_LEN_MANUFACTURER             65  /* 10.0 FJB */
#define IDB_LEN_MODALITY                  5
#define IDB_LEN_OPERATOR                  5
#define IDB_LEN_PATIENT_HISTORY          61
#define IDB_LEN_PATIENT_ID               21
#define IDB_LEN_PATIENT_IDENTIFIER       65  /* 10.0 FJB */
#define IDB_LEN_PATIENT_NAME_0150        41  /* 10.0 FJB */
#define IDB_LEN_PATIENT_NAME             65  /* 10.0 FJB */
#define IDB_LEN_POINT_COLOR              21  /* 8.9 */  
#define IDB_LEN_RADIONUCLIDE              7  /* 8.0 */
#define IDB_LEN_REF_PHYSICIAN_0150       33  /* 10.0 FJB */
#define IDB_LEN_REF_PHYSICIAN            65  /* 10.0 FJB */
#define IDB_LEN_REQUISITION_0150         13  /* 10.0 FJB */
#define IDB_LEN_REQUISITION              17  /* 10.0 FJB */
#define IDB_LEN_ROI_NAME                 33
#define IDB_LEN_SCAN_DESCRIPTION_0150    33  /* 10.0 FJB */
#define IDB_LEN_SCAN_DESCRIPTION         65  /* 10.0 FJB */
#define IDB_LEN_SCANNER_DESC             33
#define IDB_LEN_STUDY_IDENTIFIER         17  /* 10.0 FJB */
#define IDB_LEN_SW_VERSION                6
#define IDB_LEN_TITLE                    33  /* 8.2 */
#define IDB_LEN_TITLE_FONT_NAME          33  /* 8.2 */
#define IDB_LEN_TITLE_FONT_SIZE           3  /* 8.2 */
#define IDB_LEN_TRACER_NAME              41
#define IDB_LEN_UNITS_STRING             15  /* 8.9 */
#define IDB_LEN_WC_CAL_DESCRIPTION       33  /* 8.0 */
#define IDB_LEN_WC_CAL_HARDWARE          41  /* 8.0 */
#define IDB_LEN_WHERE_IS_CORR           257
#define IDB_LEN_WHERE_IS_FRAME          257
#define IDB_LEN_X_AXIS_LABEL             33  /* 8.2 */
#define IDB_LEN_Y_AXIS_LABEL             33  /* 8.2 */



/*********************************************************************
 *          Other Informix definitions
 *********************************************************************/

#define IDB_LEN_DATETIME_STR             27
#define IDB_LEN_TABLE_NAME               19
#define IDB_LEN_DATABASE_NAME            19
#define IDB_LEN_FIELD_NAME               19


/*********************************************************************
 *          Image Database Names
 *            8.2: screensave deleted
 *            8.5: curvehistory deleted
 *********************************************************************/

#define IDB_ANNOTATION_TABLE           "annotation"
#define IDB_COLORMAP_TABLE             "colormap"
#define IDB_CORRECTIONCAL_TABLE        "correctioncal"
#define IDB_COUNTRATE_TABLE            "countrate"  /* 10.0 */
#define IDB_CURVE_TABLE                "curve"
#define IDB_CURVEPRESENTATION_TABLE    "curvepresentation "
#define IDB_EXAM_TABLE                 "exam"
#define IDB_FRAME_TABLE                "frame"
#define IDB_GRAPH_TABLE                "graph"  /* 8.0 */
#define IDB_IMAGE_TABLE                "image"
#define IDB_IMAGESET_TABLE             "imageset"
#define IDB_LANDMARK_TABLE             "landmark"
#define IDB_PATIENT_TABLE              "patient"
#define IDB_RADIONUCLIDE_TABLE         "radionuclide"
#define IDB_ROI_TABLE                  "roi"
#define IDB_SCAN_TABLE                 "scan"
#define IDB_TRACER_TABLE               "tracer"
#define IDB_WELLCOUNTERCAL_TABLE       "wellcountercal"

/*********************************************************************
 *          allowable attribute value choices
 *********************************************************************/
#define IDB_COMPATIBLE_VERSION_0100 "01.00"  /* 8.5 */
#define IDB_COMPATIBLE_VERSION_0150 "01.50"  /* 9.0 */
#define IDB_COMPATIBLE_VERSION_0200 "02.00"  /* 10.0 FJB */
#define IDB_COMPATIBLE_VERSION_0300 "03.00"  /* 11.0 WJB */
#define IDB_COMPATIBLE_VERSION_0400 "04.00"  /* 12.0 Reji Jose */
#define IDB_SW_VERSION "04.00"  /* 12.0 Reji Jose */
/* #define IDB_DEFAULT_SW_VERSION "02.00" *Removed 5/3/94 fjb */



/* ---------------------------------------------------------
 *      patient_entry choices (from acqPatientEntries)
 * --------------------------------------------------------- */
#define ACQ_HEAD_FIRST                    0
#define ACQ_FEET_FIRST                    1

/* ---------------------------------------------------------
 *      patient_position choices (from acqPatientPositions)
 * --------------------------------------------------------- */
#define ACQ_SUPINE                        0
#define ACQ_PRONE                         1
#define ACQ_LEFT_DECUB                    2
#define ACQ_RIGHT_DECUB                   3

/* ---------------------------------------------------------
 *      scan_perspective choices (from acqScanPerspectives)
 * --------------------------------------------------------- */
#define ACQ_TRANSAXIAL                    0
#define ACQ_RECTILINEAR                   1 /* 8.9 */

/* ---------------------------------------------------------
 *      scan_type choices (from acqScanTypes)
 * --------------------------------------------------------- */
#define ACQ_EMISSION                      0
#define ACQ_TRANSMISSION                  1

/* ---------------------------------------------------------
 *      scan_mode choices (from acqScanModes)
 * --------------------------------------------------------- */
#define ACQ_STATIC_MODE                   0
#define ACQ_DYNAMIC_MODE                  1
#define ACQ_GATED_MODE                    2
#define ACQ_WHOLE_BODY_MODE               3 /* 8.2 */
#define ACQ_LIST_MODE                     4 /* 8.9 */

/* ---------------------------------------------------------
 *      start_condition choices (from acqStartConditions)
 * --------------------------------------------------------- *
 *#define ACQ_START_WHEN_READY              0
 *#define ACQ_HARDKEY_START                 1
 *#define ACQ_EXTERNAL_TRIGGER_START        2
 *#define ACQ_START_ON_COUNT_RATE           3 * 10.0 FJB *
 *#define ACQ_2ND_HARDKEY_START             4 * 10.0 FJB *
 *
 * The acquisition team was expecting bit mapped values. Since
 * 2,3, and 4 above have never been used this was determined to
 * be a reasonable change that would not break any code     
 *                                                            */
#define ACQ_START_WHEN_READY              0x0 /* 10.0 FJB */
#define ACQ_HARDKEY_START                 0x1 /* 10.0 FJB */
#define ACQ_EXTERNAL_TRIGGER_START        0x2 /* 10.0 FJB */
#define ACQ_START_ON_COUNT_RATE           0x4 /* 10.0 FJB */
#define ACQ_2ND_HARDKEY_START             0x8 /* 10.0 FJB */
#define ACQ_PRESCRIBED_TIME               0x16/* 12.0 KR (Added for DICOM) */
#define ACQ_PRESCRIBED_COUNT_RATE         0x32/* 12.0 KR (Added for DICOM) */

/* ---------------------------------------------------------
 *      stop_condition choices (from acqStopConditions )
 *      multiple bits set if more than one stop condition.
 * --------------------------------------------------------- */
#define ACQ_ELAPSED_TIME_STOP             0x1
#define ACQ_COUNTS_STOP                   0x2
#define ACQ_SATURATION_STOP               0x4
#define ACQ_EXTERNAL_TRIGGER_STOP         0x8
#define ACQ_OP_STOP_KEY                   0x16 /* 12.0 KR (Added for DICOM) */

/* ---------------------------------------------------------
 *      delayed_events choices (from acqDelayedEvents)
 * --------------------------------------------------------- */
#define ACQ_NO_DELAYS                     0
#define ACQ_SEPARATE_DELAYS               1
#define ACQ_SUBTRACT_DELAYS               2

/* ---------------------------------------------------------
 *      axial_acceptance choices (from acqAxialAcceptances)
 * --------------------------------------------------------- */
#define ACQ_HI_RES_AXIAL_ACCEPT           0
#define ACQ_HI_SENS_AXIAL_ACCEPT          1
#define ACQ_3D_AXIAL_ACCEPT               2
#define ACQ_HI_RES_HI_SENS_AXIAL_ACCEPT   3
#define ACQ_CTC_AXIAL_ACCEPT              4

/* ---------------------------------------------------------
 *      theta_compression choices (from acqThetaCompressions)
 * --------------------------------------------------------- */
#define ACQ_STAND_THETA_COMPRESS          0
#define ACQ_2X_STAND_THETA_COMPRESS       1

/* ---------------------------------------------------------
 *      binning_mode choices (from acqBinningModes)
 * --------------------------------------------------------- */
#define ACQ_FIXED_FORWD_BINNING           0
#define ACQ_VAR_FORWD_BINNING             1
#define ACQ_FIXED_BACKWD_BINNING          2
#define ACQ_VAR_BACKWD_BINNING            3
#define ACQ_PHASE_SLICED_BINNING          4

/* ---------------------------------------------------------
 *      trig_rej_method choices (from acqTrigRejMethods)
 * --------------------------------------------------------- */
#define ACQ_CURRENT_TRIG_REJ              0
#define ACQ_CURRENT_AND_NEXT_N_TRIG_REJ   1
#define ACQ_NEXT_N_TRIG_REJ               2
#define ACQ_NONE_REJ                      3 /* 8.6 */

/* ---------------------------------------------------------
 *      actual_stop_cond choices (from acqTerminationCodes)  
 * --------------------------------------------------------- */
#define S_ACQ_ELAPSED_TIME_STOP           0
#define S_ACQ_TOTAL_COUNTS_STOP           1
#define S_ACQ_SATURATION_STOP             2
#define S_ACQ_EXT_TRIGGER_STOP            3
#define S_ACQ_PRESET_BEATS_STOP           4
#define S_ACQ_OP_STOP_KEY_STOP            5
#define S_ACQ_OP_PAUSE_KEY_STOP           6
#define S_ACQ_CLIENT_CANCELLED_STOP       7
#define S_ACQ_SYSTEM_FAILURE_STOP         8
#define S_ACQ_OUT_OF_UNLIST_DATA          9

/* ---------------------------------------------------------
 *      randoms_corr choices (from sharcRandomTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_RANDOMS                  0
#define S_CMP_REAL_TIME_SUBTRACT          1
#define S_CMP_DELAY_EVENT_SUBTRACT        2
#define S_CMP_CALC_FROM_SINGLES           3

/* ---------------------------------------------------------
 *      deadtime_corr choices (from sharcDeadtimeTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_DEADTIME                 0
#define S_CMP_DEADTIME                    1

/* ---------------------------------------------------------
 *      normalization_corr choices (from sharcNormalizationTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_NORMALIZATION            0
#define S_CMP_NORMALIZATION               1

/* ---------------------------------------------------------
 *      blankscan_corr choices (from sharcBlankscanypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_BLANKSCAN                0
#define S_CMP_BLANKSCAN                   1


/* ---------------------------------------------------------
 *      natural_log choices (from sharcLogTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_NATURAL_LOG              0
#define S_CMP_NATURAL_LOG                 1

/* ---------------------------------------------------------
 *      radial_reposition choices (from sharcRadialRepositionTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_RADIAL_REPOSITION        0
#define S_CMP_RADIAL_REPOSITION           1

/* ---------------------------------------------------------
 *      scatter_correction choices (from sharcScatterTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_SCATTER                  0
#define S_CMP_SCATTER                     1

/* ---------------------------------------------------------
 *      attenuation_corr choices (from sharcAttenuationTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_ATTEN                    0
#define S_CMP_CALCULATED_ATTEN            1
#define S_CMP_MEASURED_ATTEN              2
#define S_CMP_CONTOUR_ATTEN               3 /* 8.9 */
#define S_CMP_TRANS_W_EMISS_ATTEN         4 /* 8.9 */
#define S_CMP_AUTO_CONTOUR_ATTEN	  5 /* 9.0 */
#define S_CMP_OTHER_ATTEN                 6 /* 9.0 4096  types */
#define S_CMP_MILAN_SEG_ATTEN                   7 /* TBD */
/* ---------------------------------------------------------
 *      filter choices (from sharcBpFilterTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_BP_FILTER                0
#define S_CMP_RECTANGLE_FILTER            1
#define S_CMP_SINC_FILTER                 2
#define S_CMP_HANNING_FILTER              3
#define S_CMP_BUTTERWORTH_FILTER          4
#define S_CMP_HAMMING_FILTER              5 /* 8.9 */
#define S_CMP_PARZEN_FILTER               6 /* 8.9 */

/* ---------------------------------------------------------
 *      backprojection choices (from sharcBackprojectTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_BACKPROJECT              0
#define S_CMP_BACKPROJECT                 1

/* ---------------------------------------------------------
 *      decay_correction choices (from sharcDecayTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_DECAY                    0
#define S_CMP_DECAY                       1

/* ---------------------------------------------------------
 *      smoothing_type choices (from sharcSinoSmoothTypes)
 * ---------------------------------------------------------
 *        changed to hex 10.0 FJB  where 
 * #define S_CMP_NO_SINO_SMOOTH              0
 * #define S_CMP_SINO_SMOOTH                 1
 * #define S_CMP_SINO_ADAPT                  2   05/24/93   
 * #define S_CMP_SINO_SMOOTH_ADAPT           3   PETge03635 */
#define S_CMP_NO_SINO_SMOOTH              0x00
#define S_CMP_SINO_SMOOTH                 0x01
#define S_CMP_SINO_ADAPT                  0x02    
#define S_CMP_SINO_SMOOTH_ADAPT  (S_CMP_SINO_SMOOTH | S_CMP_SINO_ADAPT)           
#define S_CMP_SINO_TRANSAX_ANGLE_SMOOTH   0x04 

/* ---------------------------------------------------------
 *      roi_type choices (from roiTypes)
 * --------------------------------------------------------- */
#define DIS_ROI_LINE                          0
#define DIS_ROI_ELLIPTICAL                    1
#define DIS_ROI_RECTANGULAR                   2
#define DIS_ROI_POLYLINE                      3
#define DIS_ROI_CIRCLE                        4
#define DIS_ROI_SQUARE                        5

/* ---------------------------------------------------------
 *      type choices (from annoTypes)
 * --------------------------------------------------------- */
#define DIS_ANNO_TEXT                          0
#define DIS_ANNO_STD                           1  /* 8.0 */
#define DIS_ANNO_LINE                          2
#define DIS_ANNO_BITMAP                        3

/* ---------------------------------------------------------
 *      sex choices
 * --------------------------------------------------------- */
#define IDB_FEMALE                        1   /* 8.0 */
#define IDB_MALE                          2   /* 8.0 */
#define IDB_NO_SEX                        3   /* 8.0 */

/* ---------------------------------------------------------
 *      cal_type choices
 * --------------------------------------------------------- */
#define IDB_NORMALIZATION_CAL             0
#define IDB_BLANK_SCAN_CAL                1
#define IDB_3D_NORMALIZATION              2  /* 10.0 FJB */ 

/* ---------------------------------------------------------
 *      wc_cal_type choices
 * --------------------------------------------------------- */
#define IDB_2D_CONCURRENT                 0  /* 10.0 FJB */
#define IDB_3D                            1  /* 10.0 FJB */

/* ---------------------------------------------------------
 *      is_source and image_set_source choices
 * --------------------------------------------------------- */
#define IDB_SCAN                          0
#define IDB_REFORMAT                      1 /* 8.9 */
#define IDB_SET_MATH                      2 /* 8.9 */
#define IDB_CONST_MATH                    3 /* 8.9 */
#define IDB_SUM_MATH                      4 /* 8.9 */
#define IDB_POLAR                         5 /* 8.9 */
#define IDB_FDG_AUTO_RAD                  6 /* 8.9 */
#define IDB_O15_METAB                     7 /* 8.9 */
#define IDB_O15_EXTRACT                   8 /* 8.9 */
#define IDB_CBLOODFLOW                    9 /* 8.9 */
#define IDB_BLOOD_VOL                    10 /* 8.9 */
#define IDB_PATLAK_METAB                 11 /* 9.0 */
#define IDB_REFRM_BIN_SLC_MATH           12 /* 9.0 */
#define IDB_FILTER_MATH                  13 /* 9.0 */
#define IDB_METAB                        14 /* 9.0 */
#define IDB_DICOM_RECEIVE                15 /* 10.0 FJB */
#define IDB_IMAGE_REG                    16 /* 10.0 MEL */
#define IDB_NORMALS_DB_MEAN              17 /* 11.0 WJB */
#define IDB_NORMALS_DB_STD_DEV              18 /* 11.0 WJB */

/* ---------------------------------------------------------
 *      is_contents choices
 * --------------------------------------------------------- */
#define IDB_SINOGRAMS_REP                 0  /* 8.5 */
#define IDB_RECTILINEAR_IMAGES            1
#define IDB_TRANSAXIAL_IMAGES             2
#define IDB_SAGITTAL_IMAGES               3
#define IDB_CORONAL_IMAGES                4
#define IDB_OBLIQUE_IMAGES                5
#define IDB_BULLSEYE_IMAGES               6  /* 8.0 */
#define IDB_VLA_CARDIAC_IMAGES            7  /* 8.2 */
#define IDB_HLA_CARDIAC_IMAGES            8  /* 8.2 */
#define IDB_SA_CARDIAC_IMAGES             9  /* 8.2 */
#define IDB_SINOGRAMS_NO_REP             10  /* 8.5 */
#define IDB_REGISTERED_IMAGES            11  /* 10.0 MEL */
#define IDB_POLAR_IMAGES				 12  /* 10.0 lmk */
#define IDB_RECTILINEAR_IMAGES_MAX_PIXEL 13  /* 12.0 - KR (Added for DICOM) */

/* ---------------------------------------------------------
 *      is_type choices
 * --------------------------------------------------------- */
#define IDB_NATIVE_PET_IMAGES             0
#define IDB_SCANDITRONIX_IMAGES           1
#define IDB_OTHER_IMAGES                  2 /* 9.0 */
#define IDB_DICOM_MR_IOD                  3 /* 10.0 FJB */
#define IDB_DICOM_CT_IOD                  4 /* 10.0 B FJB */
#define IDB_DICOM_PET_IOD                 5 /* 12.0 - KR (Added for DICOM) */

/* ---------------------------------------------------------
 *      recon_method choices
 * --------------------------------------------------------- */
#define IDB_2D_FILT_BACK_PROJ             0  /* 10.0 FJB */
#define IDB_3D_KINAHAN_RODGERS            1  /* 10.0 FJB */

/* ---------------------------------------------------------
 *      compression choices                                     
 * --------------------------------------------------------- */
#define DIS_COMPRESSION_NONE              0
#define DIS_COMPRESSION_LOSSY             1 /* 12.0 KR (Added for DICOM) */

/* ---------------------------------------------------------
 *      event separation choices      (bitwise OR'd)
 * --------------------------------------------------------- */
#define IDB_EVENT_SEP_KEEP_TRANSMISSION  0x1
#define IDB_EVENT_SEP_KEEP_EMISSION      0x2
#define IDB_EVENT_SEP_KEEP_SCATTER       0x4
#define IDB_EVENT_SEP_KEEP_OTHER         0x8


/* ---------------------------------------------------------
 *       xxxxxx choices (from sharcWellCounterTypes)
 * --------------------------------------------------------- */
#define S_CMP_NO_WELLCOUNTER_CAL          0 /* NONE */
#define S_CMP_CAL_TO_NCI_PER_CC           1
#define S_CMP_CAL_TO_BQ_PER_CC            2
#define S_CMP_CAL_SLICE_TO_SLICE          3 /* 9.0 */
/*
 *The above are maintained for historical reasons while the 
 *following are added for clarity in the implementation
 */
#define IDB_SLICE_TO_SLICE            S_CMP_CAL_SLICE_TO_SLICE /* 9.0 */
#define IDB_SENSITIVITY_AND_ACTIVITY  S_CMP_CAL_TO_BQ_PER_CC   /* 9.0 */ 

/* ----------------------------------------------------------
 * T+E teo mask
 * ----------------------------------------------------------*/
#define S_CMP_NO_TEO_MASK		 0	/* 11/01/93 - fjb */
#define S_CMP_TEO_MASK			 1	/* 11/01/93 - fjb */

/* ----------------------------------------------------------
 * T+E Flag
 * ----------------------------------------------------------*/
#define S_CMP_NO_PEC			 0	/* 11/01/93 - fjb */
#define S_CMP_PEC_FROM_EMISSION_FILE	 1	/* 11/01/93 - fjb */
#define S_CMP_PEC_FROM_PEC_FILE 	 2	/* 11/01/93 - fjb */

/* ---------------------------------------------------------
 *      reserved patient ids for calibration
 * --------------------------------------------------------- */
#define IDB_BLANK_SCAN_RESERVED_PATIENT      "BLANK SCAN"
#define IDB_NORMAL_RESERVED_PATIENT          "NORMALZATION"
#define IDB_WELLCOUNT_RESERVED_PATIENT       "WELL COUNTER"
#define IDB_CTC_RESERVED_PATIENT             "CTC"
#define IDB_DIAG_ACQ_RESERVED_PATIENT        "DIAG ACQ"  /* 8.9 */
#define IDB_3D_NORMAL_RESERVED_PATIENT       "3D NORM,WCC"   /* 10.0 FJB */
#define IDB_USERS_NORMALS_RESERVED_PATIENT   "USER_NORMALS"   /* 11.0 WJB */

/* ----------------------------------------------------------
 *       DICOM strings for Release 2.0D - 94/08/17 PJD
 * ---------------------------------------------------------- */
#define IDB_OPERATOR_UNKNOWN	"DICM"
#define IDB_HOSPITAL_UNKNOWN	"DICOM"
#define IDB_MANU_UNKNOWN        "DICOM"
#define IDB_SCANNER_UNKNOWN     "DICOM image from CT or MR"
#define IDB_SCAN_DESC_UNKNOWN	"DICOM data"
#define IDB_PATIENT_UNKNOWN     "No Name"

/**************************************************************
 *  
 **************************************************************/


/**************************************************************
 *  Standard Function Prototypes
 **************************************************************/
void idbMakeID (char *theBuff);
void idbUnMakeID (char *theBuff,int theInts[]);
void ints2hex(int i1, int i2, char *s1);
void hex2ints(int *i1, int *i2, char *s1);
void idbConvertID(char *oldID, char *newID);


/* 8.2 - screensave deleted */
typedef enum {
  IDB_NONE,
  IDB_IMAGE,
  IDB_RAW,
  IDB_BOTH,
  IDB_ALL = 7
} IDBBranch;

/* several changes for 8.0 */
/* 8.2 - screensave deleted */
/* 8.5 - curve history deleted */
typedef enum {
  IDB_ANNOTATION_ID,          
  IDB_COLORMAP_ID,            
  IDB_CORRECTIONCAL_ID,       
  IDB_CURVE_ID,               
  IDB_CURVEPRESENTATION_ID,   
  IDB_EXAM_ID,                
  IDB_FRAME_ID,               
  IDB_GRAPH_ID,       
  IDB_IMAGE_ID,               
  IDB_IMAGESET_ID,            
  IDB_LANDMARK_ID,            
  IDB_PATIENT_ID,             
  IDB_RADIONUCLIDE_ID,        
  IDB_ROI_ID,                 
  IDB_SCAN_ID,                
  IDB_TRACER_ID,              
  IDB_WELLCOUNTERCAL_ID      
} idTypes;


/****** 8.0 Additions ******/

/* ---------------------------------------------------------
 *      patient type choices
 * --------------------------------------------------------- */
#define IDB_TYPE_PATIENT              0
#define IDB_TYPE_BLANK                1
#define IDB_TYPE_NORMALIZATION        2
#define IDB_TYPE_WELL_COUNT           3
#define IDB_TYPE_CTC                  4
#define IDB_TYPE_DIAG_ACQ             5 /* 8.9 */
#define IDB_TYPE_3D_NORM              6 /* 10.0 FJB */
#define IDB_TYPE_USERS_NORMALS        7 /* 11.0 WJB */

/* ---------------------------------------------------------
 *      True and False (because Frank asked for them)
 * --------------------------------------------------------- */
#define IDB_TRUE              1
#define IDB_FALSE             0


/* ---------------------------------------------------------
 *  Modality      
 * --------------------------------------------------------- */
#define IDB_PET_MODALITY      "PT"

/* ---------------------------------------------------------
 *  Manufacturer
 * --------------------------------------------------------- */
#define IDB_MANU_GE_PET       "GEMS"

/* ---------------------------------------------------------
 *  Coincidence Output Mode           from edcatPlaExternal.h
 * --------------------------------------------------------- */
#define E_PLA_CPM_CRYSTAL_ROW_MODE      800
#define E_PLA_CPM_TIMING_MODE           801

/* ---------------------------------------------------------
 *  Source Holder                     from sharcAcqExternal.h
 * --------------------------------------------------------- */
#define S_ACQ_NO_PIG                    0
#define S_ACQ_PIG1                      1
#define S_ACQ_PIG2                      2
#define S_ACQ_PIG3                      3

/* ---------------------------------------------------------
 *  Validity Info    (bitwise OR'd)    from Mike Britton
 * --------------------------------------------------------- */
#define IDB_RDF_HEADER_STORED    1
#define IDB_RDF_HEADER_VALID     2
#define IDB_RDF_HISTOGRAM_STORED 4
#define IDB_RDF_HISTOGRAM_VALID  8
#define IDB_RDF_SINGLES_STORED   16
#define IDB_RDF_SINGLES_VALID    32
#define IDB_RDF_DEADTIME_STORED  64
#define IDB_RDF_DEADTIME_VALID   128


/* ---------------------------------------------------------
 *      start_symbol choices    
 * --------------------------------------------------------- */
#define IDB_DIS_ANNO_NONE            0
#define IDB_DIS_ANNO_BITMAP          1
#define IDB_DIS_ANNO_ARROW           2


/* ---------------------------------------------------------
 *      line_type choices             from displayExternal.h
 * --------------------------------------------------------- */
#define IDB_DIS_LINE_SOLID                0
#define IDB_DIS_LINE_DASHDOT              1
#define IDB_DIS_LINE_LONGDASH             2
#define IDB_DIS_LINE_SHORTDASH            3
#define IDB_DIS_LINE_DOTS                 4
#define IDB_DIS_LINE_NONE                 5 /* 8.9 */
#define IDB_DIS_LINE_LSLDASH              6 /* 8.9 */


/* ---------------------------------------------------------
 *      curve_type choices            from Jeff Hallett         
 * --------------------------------------------------------- */
#define IDB_DIS_CURVE_FOREIGN              0
#define IDB_DIS_CURVE_TAC                  1
#define IDB_DIS_CURVE_PROFILE              2
#define IDB_DIS_CURVE_HISTOGRAM            3
#define IDB_DIS_CURVE_VAC                  4
#define IDB_DIS_CURVE_BLOOD_SAM            5
#define IDB_DIS_CURVE_AREA                 6  /* 8.2 */
#define IDB_DIS_CURVE_PATLAK               7  /* 9.0 */
#define IDB_DIS_CURVE_RATES                8  /* 10.0 FJB */
#define IDB_DIS_CURVE_O15ACT_TO_CBF        9  /* 10.0 FJB */
#define IDB_DIS_CURVE_TAC_MIDFRAME        10  /* 11.0 SMB */
#define IDB_DIS_CURVE_TAC_EFFECTIVE       11  /* 11.0 SMB */
#define IDB_DIS_CURVE_CARDIAC_POLAR_MAP   12  /* 12.0 KR (Added for DICOM) */

/* ---------------------------------------------------------
 *      statistics_type               from Jeff Hallett
 * --------------------------------------------------------- */
#define IDB_DIS_STATS_NONE                  0
#define IDB_DIS_STATS_MAX                   1
#define IDB_DIS_STATS_MIN                   2
#define IDB_DIS_STATS_STD_DEV               3
#define IDB_DIS_STATS_MEAN                  4  /* 8.2+ */
#define IDB_DIS_STATS_LENGTH                5  /* 8.2+ */
#define IDB_DIS_STATS_AREA                  6  /* 8.2+ */
#define IDB_DIS_STATS_AREA_PIXELS           7  /* 8.9 */


/* date time formatting string */
#define IDB_DATETIME_FORMAT_STR "%Y-%m-%d %H:%M:%S"

/* 8.2 New definitions */
/* ---------------------------------------------------------
 *      acceptance_flag
 * --------------------------------------------------------- */
#define IDB_HIGH_RESOLUTION                  0
#define IDB_HIGH_SENSITIVITY                 1
#define IDB_3D_ACQ             				 2

/* ---------------------------------------------------------
 *      units (from Image Set)
 * --------------------------------------------------------- */
#define IDB_UNITS_IS_COUNTS               0
#define IDB_UNITS_IS_MBQ                  1
#define IDB_UNITS_IS_STD_DEV              2 /* 8.5 */
#define IDB_UNITS_IS_MG_MIN_ML            3 /* 8.7 */
#define IDB_UNITS_IS_UMOL_MIN_ML          4 /* 8.9 */
#define IDB_UNITS_IS_ML_MIN_G             5 /* 8.9 */
#define IDB_UNITS_IS_ML_G                 6 /* 8.9 */
#define IDB_UNITS_IS_ONE_CM               7 /* 8.9 */
#define IDB_UNITS_IS_PROP_TO_CNTS         8 /* 8.9 */
#define IDB_UNITS_IS_OTHER                9 /* 8.9 */
#define IDB_UNITS_IS_GENERATED           10 /* 8.9 */
#define IDB_UNITS_IS_PERCENT             11 /* 8.9 */
#define IDB_UNITS_IS_ML_MIN_ML           12 /* 9.0 */
#define IDB_UNITS_IS_ML_ML               13 /* 9.0 */
#define IDB_UNITS_IS_G_ML                14 /* 10.0 FJB */
#define IDB_UNITS_IS_CM2_ML              15 /* 10.0 FJB */
#define IDB_UNITS_IS_COUNTS_SEC          16 /* 10.0 FJB */
#define IDB_UNITS_IS_CM2                 17 /* 10.0 SMB */
#define IDB_UNITS_IS_MAX_DEFINE          17 /* 10.0 SMB */
/* Note: This last value will be incremented each time
     *       a new units definition is added above it. */

/* ---------------------------------------------------------
 *      border types (Graph)
 * --------------------------------------------------------- */
#define IDB_NO_BORDER                     0
#define IDB_SOLID_BORDER                  1
#define IDB_SHADOWED_BORDER               2
#define IDB_RAISED_BORDER                 3

/* ---------------------------------------------------------
 *      grid (Graph)
 * --------------------------------------------------------- */
#define IDB_GRID_OFF                       0
#define IDB_GRID_ON                        1
#define IDB_GRID_X_ONLY                    2 /* 8.9 */
#define IDB_GRID_Y_ONLY                    3 /* 8.9 */


/* ---------------------------------------------------------
 *      legend location (Graph)
 * --------------------------------------------------------- */
#define IDB_LEGEND_LOC_N                   0
#define IDB_LEGEND_LOC_S                   1
#define IDB_LEGEND_LOC_E                   2
#define IDB_LEGEND_LOC_W                   3
#define IDB_LEGEND_LOC_NE                  4
#define IDB_LEGEND_LOC_NW                  5
#define IDB_LEGEND_LOC_SE                  6
#define IDB_LEGEND_LOC_SW                  7


/* ---------------------------------------------------------
 *      point symbol (Curve Presentation)
 * --------------------------------------------------------- */
#define IDB_POINT_SYM_NONE                 0
#define IDB_POINT_SYM_DOT                  1
#define IDB_POINT_SYM_BOX                  2
#define IDB_POINT_SYM_TRIANGLE             3
#define IDB_POINT_SYM_DIAMOND              4
#define IDB_POINT_SYM_STAR                 5
#define IDB_POINT_SYM_CROSS                6
#define IDB_POINT_SYM_VLINE                7 /* 8.9 */
#define IDB_POINT_SYM_HLINE                8 /* 8.9 */




/* ----------------------------------------------------------------------
 *      Floating point equivalence tolerances: for a given attribute,
 *      the floating point value of one record is considered equal to 
 *      the floating point value of another record if the values are
 *      within the equivalence tolerance.
 *      NOTE: The how_derived float fields aren't here, and will be added 
 *            later if needed.
 * ------------------------------------------------------------------- */

#define IDB_ETOL_SCN_GANTRY_TILT_ANGLE   0.1
#define IDB_ETOL_SCN_TRACER_ACTIVITY     0.0000001
#define IDB_ETOL_SCN_PRE_INJ_VOLUME      0.0000001
#define IDB_ETOL_SCN_POST_INJ_ACTIVITY   0.0000001
#define IDB_ETOL_SCN_HALF_LIFE           0.0000001
#define IDB_ETOL_SCN_POSITRON_FRACTION   0.0000001
#define IDB_ETOL_SCN_SOURCE1_ACTIVITY    0.0000001
#define IDB_ETOL_SCN_SOURCE1_HALF_LIFE   0.0000001
#define IDB_ETOL_SCN_SOURCE2_ACTIVITY    0.0000001
#define IDB_ETOL_SCN_SOURCE2_HALF_LIFE   0.0000001
#define IDB_ETOL_SCN_SOURCE_LOCATION     0.1
#define IDB_ETOL_FRM_TABLE_HEIGHT        0.1
#define IDB_ETOL_FRM_TABLE_Z_POSITION    0.1
#define IDB_ETOL_FRM_START_LOCATION      0.1
#define IDB_ETOL_WCC_MEAS_ACTIVITY       0.0000001
#define IDB_ETOL_IST_PATIENT_ROW_COS_L   0.0000001
#define IDB_ETOL_IST_PATIENT_ROW_COS_P   0.0000001
#define IDB_ETOL_IST_PATIENT_ROW_COS_S   0.0000001
#define IDB_ETOL_IST_PATIENT_COL_COS_L   0.0000001
#define IDB_ETOL_IST_PATIENT_COL_COS_P   0.0000001
#define IDB_ETOL_IST_PATIENT_COL_COS_S   0.0000001
#define IDB_ETOL_IST_ATTEN_COEFFICIENT   0.0000001 /* 8.9 */
#define IDB_ETOL_IST_BP_FILTER_CUTOFF    0.0000001 /* 8.9 */
#define IDB_ETOL_IST_BP_DFOV             0.0000001 /* 8.9 */
#define IDB_ETOL_IST_BP_CENTER_L         0.0000001 /* 8.9 */
#define IDB_ETOL_IST_BP_CENTER_P         0.0000001 /* 8.9 */
#define IDB_ETOL_IST_CAC_EDGE_THRES      0.2       /* 9.0 */
#define IDB_ETOL_IST_CAC_SKULL_OFF       0.0000001 /* 9.0 */
#define IDB_ETOL_IMG_PATIENT_L           0.0000001
#define IDB_ETOL_IMG_PATIENT_P           0.0000001
#define IDB_ETOL_IMG_PATIENT_S           0.0000001
#define IDB_ETOL_IMG_IMAGE_LOCATION      0.0000001
#define IDB_ETOL_IMG_IMAGE_THICKNESS     0.0000001
#define IDB_ETOL_IMG_MAX_PIXEL_VALUE     0.0000001
#define IDB_ETOL_IMG_MIN_PIXEL_VALUE     0.0000001
#define IDB_ETOL_IMG_DECAY_FACTOR        0.0000001
#define IDB_ETOL_IMG_SCALE_FACTOR        0.0000001
#define IDB_ETOL_IMG_PIXEL_WIDTH         0.0000001
#define IDB_ETOL_IMG_PIXEL_HEIGHT        0.0000001
#define IDB_ETOL_IMG_COEFFICIENT         0.0000001
#define IDB_ETOL_IMG_BP_CENTER_X         0.0000001 /* 8.9 */
#define IDB_ETOL_IMG_BP_CENTER_Y         0.0000001 /* 8.9 */
#define IDB_ETOL_IMG_ACTIV_FACTOR        0.0000001 /* 9.0 */
#define IDB_ETOL_ANN_START_X             0.0000001
#define IDB_ETOL_ANN_START_Y             0.0000001
#define IDB_ETOL_ANN_END_X               0.0000001
#define IDB_ETOL_ANN_END_Y               0.0000001
#define IDB_ETOL_ROI_CENTER_X            0.0000001
#define IDB_ETOL_ROI_CENTER_Y            0.0000001
#define IDB_ETOL_ROI_WIDTH               0.0000001
#define IDB_ETOL_ROI_HEIGHT              0.0000001
#define IDB_ETOL_ROI_ANGLE               0.0000001
#define IDB_ETOL_GPH_X_MAJOR_TICS        0.0000001
#define IDB_ETOL_GPH_X_AXIS_MIN          0.0000001
#define IDB_ETOL_GPH_X_AXIS_MAX          0.0000001
#define IDB_ETOL_GPH_Y_MAJOR_TICS        0.0000001
#define IDB_ETOL_GPH_Y_AXIS_MIN          0.0000001
#define IDB_ETOL_GPH_Y_AXIS_MAX          0.0000001
#define IDB_ETOL_RAD_HALF_LIFE           0.0000001
#define IDB_ETOL_RAD_POSITRON_FRACTION   0.0000001
#define IDB_ETOL_WEL_ACTIVITY_FACTOR     0.0000001 /* 9.0 */


/* 8.5 New definitions */
/* ---------------------------------------------------------
 *    window_level_type values
 * --------------------------------------------------------- */
#define IDB_WLT_ABSOLUTE                     0
#define IDB_WLT_PERCENT                      1
#define IDB_WLT_USER                         2 /* 8.9 */

/* ---------------------------------------------------------
 *    flip values
 * --------------------------------------------------------- */
#define IDB_FLIP_NONE                        0
#define IDB_FLIP_TB                          1
#define IDB_FLIP_LR                          2
#define IDB_FLIP_BOTH                        3

/* ---------------------------------------------------------
 *    graph axis values
 * --------------------------------------------------------- */
#define IDB_AXIS_UNITS_NONE                   0
#define IDB_AXIS_UNITS_MM                     1
#define IDB_AXIS_UNITS_COUNT                  2
#define IDB_AXIS_UNITS_MBQ                    3
#define IDB_AXIS_UNITS_NCI                    4
#define IDB_AXIS_UNITS_STD_DEV                5
#define IDB_AXIS_UNITS_MSEC                   6
#define IDB_AXIS_UNITS_MG_MIN_ML              7 /* 8.7 */
#define IDB_AXIS_UNITS_SEC                    8 /* 8.9 */
#define IDB_AXIS_UNITS_KBQ                    9 /* 8.9 */
#define IDB_AXIS_UNITS_UCI                   10 /* 8.9 */
#define IDB_AXIS_UNITS_KCOUNT                11 /* 8.9 added mtb*/
#define IDB_AXIS_UNITS_G_MIN_ML              12 /* 8.9 */
#define IDB_AXIS_UNITS_UMOL_MIN_ML           13 /* 8.9 */
#define IDB_AXIS_UNITS_MMOL_MIN_ML           14 /* 8.9 */
#define IDB_AXIS_UNITS_ML_MIN_G              15 /* 8.9 */
#define IDB_AXIS_UNITS_L_MIN_G               16 /* 8.9 */
#define IDB_AXIS_UNITS_ML_G                  17 /* 8.9 blood vol */
#define IDB_AXIS_UNITS_L_G                   18 /* 8.9 */
#define IDB_AXIS_UNITS_ONE_CM                19 /* 8.9 not scalable */
#define IDB_AXIS_UNITS_PROP_TO_CNTS          20 /* 8.9 */
#define IDB_AXIS_UNITS_OTHER                 21 /* 8.9 */
#define IDB_AXIS_UNITS_GENERATED             22 /* 8.9 */
#define IDB_AXIS_UNITS_PERCENT               23 /* 8.9 */
#define IDB_AXIS_UNITS_FREQ                  24 /* 8.9 hist */
#define IDB_AXIS_UNITS_PIXELS                25 /* 8.9 area */
#define IDB_AXIS_UNITS_ML_MIN_ML             26 /* 9.0 */
#define IDB_AXIS_UNITS_IS_ML_ML              27 /* 9.0 */
#define IDB_AXIS_UNITS_MIN                   28 /* 9.0 */
#define IDB_AXIS_UNITS_COUNTS_SEC            29 /* 10.0 FJB */
#define IDB_AXIS_UNITS_G_ML                  30 /* 10.0 SMB */
#define IDB_AXIS_UNITS_CM2_ML                31 /* 10.0 SMB */
#define IDB_AXIS_UNITS_CM2                   32 /* 10.0 SMB - area */




/* 8.9 New definitions */
/* ---------------------------------------------------------
 *    coordinate_system values (from annotation)
 * --------------------------------------------------------- */
#define IDB_ANNO_COORD_IMAGE                  0
#define IDB_ANNO_COORD_SCREEN                 1


/* MSG additions for concurrency control */
#define IDB_DIRTY_READ      0
#define IDB_COMMITTED_READ  1
#define IDB_LOCK_WAIT_TIME  2

/* Other 9.0 Additions */
/*----------------------------------------------------------
 *     roi.atten_corr_flag - needed to track used/modified
 *	nature of ROI
 */
#define IDB_NOT_ATTEN_CORR_ROI       0  /* 9.0 */
#define IDB_ATTEN_CORR_ROI           1  /* 9.0 */
#define IDB_ATTEN_CORR_ROI_MODIFIED  2  /* 9.0 */


/* Other 10.0 Additions */
/*----------------------------------------------------------
 *	colormap.interpolation_type
 *
 */
#define IDB_CONTINUOUS_COLORMAP       0  /* 10.0 B */
#define IDB_DISCRETE_COLORMAP         1  /* 10.0 B */
#define IDB_PWLINEAR_COLORMAP         2  /* 10.0 B */


/* Other 10.0 Additions */
/* ---------------------------------------------------------
 * Constants to support RDF Compression.
 * 
 */
#define IDB_RDF_NOT_COMPRESSED              0	/* 11.0 WJB */
#define IDB_RDF_USER_DEFINED_COMPRESSED     1	/* 11.0 WJB */
#define IDB_RDF_RIVN_REV_A_COMPRESSED       2	/* 11.0 WJB */

#endif
