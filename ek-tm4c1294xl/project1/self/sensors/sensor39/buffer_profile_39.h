/*------------------------------------------------------------------------------
buffer_profile_39.h


------------------------------------------------------------------------------*/

#ifndef __BUFFER_PROFILE_39
#define __BUFFER_PROFILE_39


typedef struct
{
  bool          fExists;
  time          tmTime;
  ulong         mdwValue[4];
} profile39;


#endif



void    InitProfile39(void);
void    AddProfile39(time  tmTime, ulong  mdwValue[4]);

void    DeltaProfile39(void);
profile39 GetProfile39(uchar  i);
uchar   GetProfileSize39(void);
bool    IsProfileOveflow39(void);
