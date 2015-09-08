/*------------------------------------------------------------------------------
WRAPPERS,H


------------------------------------------------------------------------------*/

#ifndef __WRAPPERS
#define __WRAPPERS


typedef struct
{
  float         flValue;
  bool          fValid;
} float2;


typedef struct
{
  double        dbValue;
  bool          fValid;
} double2;


typedef struct
{
  time          tiValue;
  bool          fValid;
} time2;



float2  GetFloat2(float  flValue, bool  fValid);
float2  GetFloat2Error(void);

double2 GetDouble2(double  dbValue, bool  fValid);
double2 GetDouble2Error(void);

time2   GetTime2(time  tiValue, bool  fValid);
time2   GetTime2Error(void);

#endif
