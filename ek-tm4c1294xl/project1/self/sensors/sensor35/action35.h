/*------------------------------------------------------------------------------
action35.h


------------------------------------------------------------------------------*/

#ifndef __ACTION35
#define __ACTION35


typedef enum
{
  E35_REPEAT_START         = 0,
  E35_REPEAT_ERROR_TIMEOUT = 1,

  E35_ROUTER_ERROR_SIZE    = 2,
  E35_ROUTER_ERROR_ERROR   = 3,
  E35_ROUTER_ERROR_COMMAND = 4,

  E35_SENSOR_SUCCESS       = 5,
  E35_SENSOR_FAILURE       = 6
} event35;


typedef enum
{
  A35_WAIT      = 0,
  A35_SUCCESS   = 1,
  A35_ERROR     = 2
} action35;


typedef struct
{
  bool          fLog;
  event35       enEvent;
  action35      enAction;
  uint          wData;
} step35;


typedef struct
{
  time          tiNow;
  event35       enEvent;
  uint          wData;
} log35;


typedef struct
{
  time          tiNow;
  uint          wCounter;
} counter35;


#endif