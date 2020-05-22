/*------------------------------------------------------------------------------
device38.c

���������� CE318
------------------------------------------------------------------------------*/

#include "../../main.h"





uchar  const  MaskAND[8]    = { 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF };
uchar  const  MaskAND2[8]   = { 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF };
uchar  const  MaskSETbit[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
//                          ��  ��  ��  ��  ��   ��   ��   ��   ��   ��   ��   ��   ��(���+1)
uint   const  mwMon[13]  = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };

#define ZeroYear    2012
#define DayPerYear  365
#define SecPerDay   86400
#define SecPerHour  3600
#define SecPerMin   60
#define SecPerYear  (ulong)31536000 //DayPerYear*SecPerDay

#define MAX_BYTES_DECODE 100


typedef struct
{// BCD
 uchar Sec;   //�������
 uchar Min;   //������
 uchar Hour;  //����
 uchar Week;  //���� ������
 uchar Day;   //�����
 uchar Mon;   //�����
 uchar Year;  //���
 uchar Status; //������ ������������� �������
 uchar Status2;//�������������� ������
 uchar CRChi; //CRC16
 uchar CRClo; //CRC16
} DateTime;


//������������� (�������� MAX_BYTES_DECODE ������� ���� - ��. ������ ������) - ����� ������������ ���� ���� 0x80 ����������
//�������������� ������ ���������� ������� �� ������� ������
//*pbData - �������/�������� �����
//bS = ���� .0 - =1 �� ��������
//          .7 - =0 ��� �����
//               =1 �� ������
//����������:
//     ���� .0..7  - ���������� �������������� ���� �� ������
//          .8..10 - ��� �������
//             .15 - =0 ���� "+"; =1 ���� "-"
uint DFF_Decoder(uchar  *pbData, uchar bS)
{
 uchar bj;
 uint  wi, wN;

 for(wN=0; wN<MAX_BYTES_DECODE; wN++) 
  if(*(pbData+wN) & 0x80) *(pbData+wN) &= 0x7F;
  else
  {
   *(pbData+wN+1) = 0;
   if(bS & 0x80) //����� �� ������
	if((*(pbData+wN) & 0x40) == 0) bS &= 0x7F; //���� "+"
   break;
  }

 if(wN == MAX_BYTES_DECODE) wN = MAX_BYTES_DECODE-1;

 bj = 0;
 for(wi=0; wi <= wN; wi++) 
 {//����������
  *(pbData+(wi - (wi/8))) = ((*(pbData+wi) >> bj) & (~MaskAND[bj])) |
	   	         ((*(pbData+wi+1) << (7-bj)) & MaskAND[bj]);
  if(bj == 7) bj = 0; //��������� ������ 
  else bj++;
 }

 wN -= (wN / 8); 

 if(bS & 0x01)
 {//������� ��� �������
  bS = (bS & 0x80) + (*pbData & 0x07); 
  for(wi=0; wi <= wN; wi++)            
   *(pbData+wi) = ((*(pbData+wi) >> 3) & 0x1F) |
                  ((*(pbData+wi+1) << 5) & 0xE0);
 }

 while(1)
 {//����������� ���������� ����� 
  if(*(pbData+wN) != 0x00) break;
  else if(wN == 0) break;
       else wN--;
 }

 if(bS & 0x80)
 {//������� �����
  for(bj=8; bj!=0; bj--) 
   if(*(pbData + wN) & MaskSETbit[bj-1]) break;
   else *(pbData + wN) |= MaskSETbit[bj-1];
 }

 return((wN+1) + (bS << 8));
}//uint DFF_Decoder(uchar  *pbData, uchar bS)

//����������� (max 0x7F ������� ���� - ��. ������ ������)
//������������ ������ ���������� ������� �� ������� ������
//*pbData - �������/�������� ����� (������ ���� ������� � 2 ���� ������ ��� ���-�� ������� ����!!!)
//bS = ���� .0..6 - ���������� ���������� ����
//          .7 - =0 ��� ����� "-"
//               =1 �� ������ "-" 
//����������: ���������� ���� ����� �����������
uchar DFF_�oder(uchar  *pbData, uchar bS)
{
 uchar bi, bj, bN, bPrev, bShift;

 if((bS & 0x7F) == 0) { *pbData = 0x00; return(1); } 

 bN = (bS & 0x7F) - 1;
 while(1)
 {//����������� ���������� �����
  if(*(pbData+bN) != 0x00) break;
  else if(bN == 0) break;
       else bN--;
 }

 bN++;

 for(bi=0; bi<(bN/8)+1; bi++) *(pbData+bN+bi) = 0; 

 if(bS & 0x80) //������� �����
  if( *(pbData+bN-1) & 0x80 ) bS = 1;//���� "-"
  else bS = 0;//���� "+"
 else bS = 0;//��� �����

 bShift = bN+(bN/8)+1; 
 bPrev = 0x00;
 bj = 0;
 for(bi=0; bi<=bN; bi++) //�������� ����
 {//��������
  *(pbData + bShift) =
	   ((*(pbData+bi) << bj) & MaskAND[7-bj]) |
	   ((bPrev >> (8-bj)) & (~MaskAND[7-bj]));

  bPrev = *(pbData+bi);
  bShift++;
  if(bj == 7)
  {
   bj = 1;
   *(pbData + bShift) = bPrev; 
   bShift++;
  }
  else bj++;
 }

 if( *(pbData+bShift-1) == 0x00 ) bShift--; //���� ��������� ���� ������

 bN = bShift - (bN+(bN/8)+1);
 bShift = bShift - bN;

 //������� ������� ����
 for(bi=0; bi<(bN-1); bi++) *(pbData+bShift+bi) |= 0x80;
 *(pbData+bShift+(bN-1)) &= 0x7F;

 if(bS) //������� ����� "-"
 {
  for(bi=7; bi!=0; bi--) 
   if(*(pbData + bShift + (bN-1)) & MaskSETbit[bi-1]) break;
   else *(pbData + bShift+ (bN-1)) |= MaskSETbit[bi-1];
 }

 //�������� ��������� �� ������� �����
 for(bi=0; bi<bN; bi++) *(pbData+bi) = *(pbData+bShift+bi);

 return(bN);
}//DFF_�oder

/*
//������� ������� �� ������ � ������ ��.��.�� ��.��.��
//���������� ����/����� � ������� DateTime (� BCD)
//DT.Status = 1,2 - ������ �������� �������
DateTime LongSecToTime(ulong lgSec) 
{
 DateTime DT;
 ulong lgT;

 DT.Status = 0;
 DT.Year = (ulong)lgSec / SecPerYear;
 if(DT.Year == 0) { DT.Status = 1; return(DT); };
 lgT = (ulong)lgSec - (ulong)DT.Year * (ulong)SecPerYear;
 DT.Sec = ((DT.Year-1) / 4) + 1;
 if( lgT < (ulong)DT.Sec*(ulong)SecPerDay ) DT.Year = DT.Year - 1; //"<=" ???
 DT.Sec = ((DT.Year-1) / 4) + 1;

 lgSec = lgSec - ((ulong)DT.Year * SecPerYear + (ulong)DT.Sec * SecPerDay);
 lgT = lgSec / SecPerDay;
 if((DT.Year % 4) == 0) DT.Sec = 1;
                   else DT.Sec = 0;
 if( lgT >= (DayPerYear + DT.Sec) ) { DT.Status = 2; return(DT); }
 for(DT.Mon=1; DT.Mon<13; DT.Mon++)
  if( DT.Mon > 1 )
  {
   if( lgT < (mwMon[DT.Mon]+DT.Sec) ) break;
  }
  else if( lgT < mwMon[DT.Mon] ) break;

 if( DT.Mon > 2) DT.Day = lgT - (mwMon[DT.Mon-1] + DT.Sec) + 1;
            else DT.Day = lgT - mwMon[DT.Mon-1] + 1;

 lgSec = lgSec - (lgT * (ulong)SecPerDay);
 DT.Hour = lgSec / SecPerHour;

 lgSec = lgSec - ((ulong)DT.Hour * SecPerHour);
 DT.Min = lgSec / SecPerMin;

 DT.Sec = lgSec - ((ulong)DT.Min * SecPerMin);

 DT.Year = (DT.Year + ZeroYear) - 2000;

 DT.Year = funHEXtoBCD(DT.Year);
 DT.Hour = funHEXtoBCD(DT.Hour);
 DT.Mon  = funHEXtoBCD(DT.Mon);
 DT.Min  = funHEXtoBCD(DT.Min);
 DT.Day  = funHEXtoBCD(DT.Day);
 DT.Sec  = funHEXtoBCD(DT.Sec);

 return(DT);
}//LongSecToTime

//������� ������� �� ������� ��.��.�� ��.��.�� � 4 ����� ������
ulong TimeToLongSec(DateTime DT)
{
 ulong lgT;

 DT.Year = funBCDtoHEX(DT.Year);
 DT.Hour = funBCDtoHEX(DT.Hour);
 DT.Mon  = funBCDtoHEX(DT.Mon);
 DT.Min  = funBCDtoHEX(DT.Min);
 DT.Day  = funBCDtoHEX(DT.Day);
 DT.Sec  = funBCDtoHEX(DT.Sec);

 DT.Year -= (ZeroYear - 2000);

 if((DT.Mon > 13) || (DT.Mon == 0)) return(0);//�������� �����

 if( (DT.Mon > 2) && ((DT.Year % 4) == 0) ) lgT = 1;
                                       else lgT = 0;

 lgT = lgT + DT.Day + mwMon[DT.Mon-1] + (ulong)DT.Year * DayPerYear + ((DT.Year-1) / 4);

 return(lgT * SecPerDay + (ulong)DT.Hour * SecPerHour + (ulong)DT.Min * SecPerMin + (ulong)DT.Sec);
}
*/
