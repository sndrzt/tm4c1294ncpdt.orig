/*------------------------------------------------------------------------------
FILES.C

 ������� ������/������ ������ �� ���������
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "../main.h"
#include        "../mem_flash.h"
#include        "at45.h"



void    OpenOut(uint  wPage)
{
  wPageOut = wPage;

//  memset(&mpbPageOut, '\0', sizeof(mpbPageOut));
  wByteOut = 0;
}


bool    Save(void  *pbBase, uint  wSize)
{
uint    wFree;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite() == 0) return(0);      // ���������� �����

      OpenOut(wPageOut + 1);                    // ���������������� � ������ ��������� ��������

      pbBase += wFree;                          // ��������� �� ��������� ������� ��������� ������
      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ � �����
      memcpy(mpbPageOut + wByteOut, pbBase, wSize);                                  
      wByteOut += wSize;                        // ����������� ������� ���������� ������

      return(1);
    }
  }
}  


bool    CloseOut()
{
  return( SafePageWrite() );
}



bool    OpenIn(uint  wPage)
{
  wPageIn = wPage;

//  memset(&mpbPageIn, '\0', sizeof(mpbPageIn));
  wByteIn = 0;

  return( SafePageRead() );
}


bool    Load(void  *pbBase, uint  wSize)
{     
uint    wFree;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteIn;           // ������ ������������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ������������� ����� ������
    {                                           // ������ ������ �� ������
      memcpy(pbBase, mpbPageIn + wByteIn, wFree);

      if (OpenIn(wPageIn + 1) == 0) return(0);  // ������ � ����� ��������� ��������

      pbBase += wFree;                          // ��������� �� ��������� ������� ���������� ������
      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ �� ������
      memcpy(pbBase, mpbPageIn + wByteIn, wSize);
      wByteIn += wSize;                         // ����������� ������� ���������� ������

      return(1);
    }
  }
}

