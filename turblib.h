/* $Id: turblib.h,v 1.18 2009-12-06 16:01:01 eric Exp $ */
#ifndef TURBLIB_H_
#define TURBLIB_H_

#include "soapH.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define TURBLIB_VERSION "0.2"
#define TURB_ERROR_LENGTH 2048

/* Global gSOAP handle
 * TODO: Figure out how to pass this to/from Fortran
 */
extern struct soap __jhuturbsoap;

/* Spatial Interpolation Options */
enum SpatialInterpolation
{
  /* Spatial Interpolation Flags for GetVelocity & GetVelocityAndPressure */
  NoSInt = 0, /* No spatial interpolatio */
  Lag4 = 4,   /* 4th order Lagrangian interpolation in space */
  Lag6 = 6,   /* 4th order Lagrangian interpolation in space */
  Lag8 = 8,   /* 4th order Lagrangian interpolation in space */

  /* Spatial Differentiation and Interpolation Flags for GetVelocityGradient
   * and GetPressureGradient. */
  FD4NoInt = 40, /* 4th order finite differential scheme for grid values, no spatial interpolation */
  FD6NoInt = 60, /* 6th order finite differential scheme for grid values, no spatial interpolation */
  FD8NoInt = 80, /* 8th order finite differential scheme for grid values, no spatial interpolation */
  FD4Lag4 = 44,  /* 4th order finite differential scheme for grid values, 4th order Lagrangian interpolation in space */


  /* Old names, for backward compatibility */
  NoSpatialInterpolation = 0,
  Lagrangian4thOrder = 4,
  Lagrangian6thOrder = 6,
  Lagrangian8thOrder = 8
};

/* Temporal Interpolation Options */
enum TemporalInterpolation
{
  NoTInt = 0,   /* No temporal interpolation */
  PCHIPInt = 1, /* Piecewise cubic Hermit interpolation in time */

  /* Old names, for backward compatibility */
  NoTemporalInterpolation = 0,
  PCHIPInterpolation = 1
};

/* C */
void soapinit ();
void soapdestroy ();

/* Fortran */
void soapinit_ ();
void soapdestroy_ ();

/* C */
char *turblibGetErrorString ();
int turblibGetErrorNumber ();
void turblibPrintError ();
void turblibSetExitOnError (int);

/* Fortran */
void turblibgeterrorstring_ (char *dest, int len);
int turblibgeterrornumber_();
void turblibprinterror_();
void turblibsetexitonerror_(int *);

/* C */
int getVelocity (char *authToken,
  char *dataset, float time,
  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
  int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getvelocity_ (char *authToken,
  char *dataset, float *time,
  int *spatial, int *temporal,
  int *count, float datain[][3], float dataout[][3],
  int len_a, int len_d);

/* C */
int getVelocityAndPressure (char *authToken,
  char *dataset, float time,
  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
  int count, float datain[][3], float dataout[][4]);

/* Fortran */
int getvelocityandpressure_ (char *authToken,
  char *dataset, float *time,
  int *spatial, int *temporal,
  int *count, float datain[][3], float dataout[][4],
  int len_a, int len_d);

/* C */
int getPressureHessian(char *authToken,
      char *dataset, float time,
      enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
      int count, float datain[][3], float dataout[][6]);

/* Fortran */
int getpressurehessian_(char *authToken,
      char *dataset, float *time,
      int *spatial, int *temporal,
      int *count, float datain[][3], float dataout[][6],
      int len_a, int len_d);

/* C */
int getVelocityGradient(char *authToken,
      char *dataset, float time,
      enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
      int count, float datain[][3], float dataout[][9]);

/* Fortran */
int getvelocitygradient_(char *authToken,
      char *dataset, float *time,
      int *spatial, int *temporal,
      int *count, float datain[][3], float dataout[][9],
      int len_a, int len_d);

/* C */
int getPressureGradient(char *authToken,
      char *dataset, float time,
      enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
      int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getpressuregradient_(char *authToken,
      char *dataset, float *time,
      int *spatial, int *temporal,
      int *count, float datain[][3], float dataout[][3],
      int len_a, int len_d);

/* C */
int getVelocityHessian(char *authToken,
      char *dataset, float time,
      enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
      int count, float datain[][3], float dataout[][18]);

/* Fortran */
int getvelocityhessian_(char *authToken,
      char *dataset, float *time,
      int *spatial, int *temporal,
      int *count, float datain[][3], float dataout[][18],
      int len_a, int len_d);

/* C */
int getVelocityLaplacian(char *authToken,
      char *dataset, float time,
      enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
      int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getvelocitylaplacian_(char *authToken,
      char *dataset, float *time,
      int *spatial, int *temporal,
      int *count, float datain[][3], float dataout[][3],
      int len_a, int len_d);

/* C */
int nullOp(char *authToken, int count, 
      float datain[][3], float dataout[][3]);

/* Fortran */
int nullop_(char *authToken, int *count, 
      float datain[][3], float dataout[][3], 
      int len_a, int len_d);

///* C */
//int getBoxFilterVelocity(char *authToken,
//      char *dataset, float time,
//      float filterLength, int nylayers,
//      enum TemporalInterpolation temporal,
//      int count, float datain[][3], float dataout[][3]);
//
///* Fortran */
//int getboxfiltervelocity_(char *authToken,
//      char *dataset, float *time,
//      float *filterlength,
//      int *nlayers, int *temporal,
//      int *count, float datain[][3], float dataout[][3],
//      int len_a, int len_d);
//
///* C */
//int getBoxFilterPressure(char *authToken,
//      char *dataset, float time,
//      float filterLength, int nlayers,
//      enum TemporalInterpolation temporal,
//      int count, float datain[][3], float dataout[]);
//
///* Fortran */
//int getboxfilterpressure_(char *authToken,
//      char *dataset, float *time,
//      float *filterlength, 
//      int *nlayers,
//      int *temporal,
//      int *count, float datain[][3], float dataout[],
//      int len_a, int len_d);
//
///* C */
//int getBoxFilterSGSStress(char *authToken,
//      char *dataset, float time,
//      float filterLength, int nlayers,
//      enum TemporalInterpolation temporal,
//      int count, float datain[][3], float dataout[][6]);
//
///* Fortran */
//int getboxfiltersgsstress_(char *authToken,
//      char *dataset, float *time,
//      float *filterlength,
//      int *nlayers,
//      int *temporal,
//      int *count, float datain[][3], float dataout[][6],
//      int len_a, int len_d);
//
///* C */
//int getBoxFilterVelocityGradient(char *authToken,
//      char *dataset, float time,
//      float filterLength, int nlayers,
//      enum TemporalInterpolation temporal,
//      int count, float datain[][3], float dataout[][9]);
//
///* Fortran */
//int getboxfiltervelocitygradient_(char *authToken,
//      char *dataset, float *time,
//      float *filterlength,
//      int *nlayers,
//      int *temporal,
//      int *count, float datain[][3], float dataout[][9],
//      int len_a, int len_d);

/* C */
int getForce(char *authToken,
  char *dataset, float time,
  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
  int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getforce_(char *authToken,
  char *dataset, float *time,
  int *spatial, int *temporal,
  int *count, float datain[][3], float dataout[][3],
  int len_a, int len_d);

///*C*/ 
//int getPosition_new(char *authToken,
//  char *dataset, float startTime, float endTime, 
//  int nt,
//  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
//  int count, float datain[][3], float dataout[][3]);
//
///* Fortran */
//int getpositionnew_(char *authToken,
//  char *dataset, float *startTime, float *endTime,
//  int *nt,
//  int *spatial, int *temporal,
//  int *count, float datain[][3], float dataout[][3],
//  int len_a, int len_d);

///*C*/ 
//int getPosition_new2(char *authToken,
//  char *dataset, float startTime, float endTime, 
//  int nt,
//  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
//  int count, float datain[][3], float dataout[][3]);
//
///* Fortran */
//int getpositionnew2_(char *authToken,
//  char *dataset, float *startTime, float *endTime,
//  int *nt,
//  int *spatial, int *temporal,
//  int *count, float datain[][3], float dataout[][3],
//  int len_a, int len_d);

/*C*/ 
int getPosition(char *authToken,
  char *dataset, float startTime, float endTime, 
  float dt,
  enum SpatialInterpolation spatial,
  int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getposition_(char *authToken,
  char *dataset, float *startTime, float *endTime,
  float *dt,
  int *spatial,
  int *count, float datain[][3], float dataout[][3],
  int len_a, int len_d);

/* C */
int getRawVelocity (char *authToken,
  char *dataset, float time,
  int X, int Y, int Z, int Xwidth, int Ywidth, int Zwidth, char dataout[]);

/* C */
int getMagneticField (char *authToken,
  char *dataset, float time,
  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
  int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getmagneticfield_ (char *authToken,
  char *dataset, float *time,
  int *spatial, int *temporal,
  int *count, float datain[][3], float dataout[][3],
  int len_a, int len_d);

/* C */
int getRawMagneticField (char *authToken,
  char *dataset, float time,
  int X, int Y, int Z, int Xwidth, int Ywidth, int Zwidth, char dataout[]);

/* C */
int getVectorPotential (char *authToken,
  char *dataset, float time,
  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
  int count, float datain[][3], float dataout[][3]);

/* Fortran */
int getvectorpotential_ (char *authToken,
  char *dataset, float *time,
  int *spatial, int *temporal,
  int *count, float datain[][3], float dataout[][3],
  int len_a, int len_d);

/* C */
int getRawVectorPotential (char *authToken,
  char *dataset, float time,
  int X, int Y, int Z, int Xwidth, int Ywidth, int Zwidth, char dataout[]);

/* C */
int getPressure (char *authToken,
  char *dataset, float time,
  enum SpatialInterpolation spatial, enum TemporalInterpolation temporal,
  int count, float datain[][3], float dataout[]);

/* Fortran */
int getpressure_ (char *authToken,
  char *dataset, float *time,
  int *spatial, int *temporal,
  int *count, float datain[][3], float dataout[],
  int len_a, int len_d);

/* C */
int getRawPressure (char *authToken,
  char *dataset, float time,
  int X, int Y, int Z, int Xwidth, int Ywidth, int Zwidth, char dataout[]);

#ifdef  __cplusplus
}
#endif

#endif
