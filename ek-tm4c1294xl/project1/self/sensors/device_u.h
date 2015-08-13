/*------------------------------------------------------------------------------
DEVICE_U.H


------------------------------------------------------------------------------*/

void    QueryCloseU(void);
void    QueryOptionU(void);
void    QueryCorrectU(void);
void    QueryEnergyAbsU(uchar  ibLine);
void    QueryEnergyDayU(uchar  ibLine);
void    QueryEnergyMonU(uchar  ibLine);
void    QueryEnergySpecU(uchar  ibLine);
void    ReadEnergyU(uchar  ibLine);
void    ReadEnergyU_SkipLine(uchar  ibLine);

void    InitHeaderU(void);
void    QueryHeaderU(void);
void    ReadHeaderU(void);
void    ReadHeaderU_SkipLine(uchar  ibLine);
void    MakeDataU(uchar  ibHou);
bit     ReadDataU(void);

void    ReadCurrentU(void);

void    QueryParamU1(void);
void    QueryParamU2(void);
void    QueryParamU3(void);
void    QueryParamU4(void);
