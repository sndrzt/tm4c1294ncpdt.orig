/*------------------------------------------------------------------------------
FILES.C

 ������� ������/������ ������ �� ���������
------------------------------------------------------------------------------*/

#include        <string.h>
#include "../main.h"
#include "../memory/mem_flash.h"
#include "flash.h"
#include "files.h"



uint    wPageOut_, wPageIn_;



void    OpenOut(uint  wPage)
{
  wPageOut_ = wPage;
  wByteOut = 0;
}


void ClearOut(void)
{
  memset(&mpbPageOut, 0, sizeof(mpbPageOut));
}


bool Save(void  *pbBase, uint  wSize)
{
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wLEAF_BYTES - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite(wPageOut_) == false) return false; // ���������� �����

      OpenOut(wPageOut_ + 1);                    // ���������������� � ������ ��������� ��������

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO ��������� �� ��������� ������� ��������� ������
      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ � �����
      memcpy(mpbPageOut + wByteOut, pbBase, wSize);                                  
      wByteOut += wSize;                        // ����������� ������� ���������� ������

      return true;
    }
  }

  return true;
}  

/*
bool Clean(uint  wSize)
{
uint    wFree;

  while (wSize > 0)
  {
    wFree = wLEAF_BYTES - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memset(mpbPageOut + wByteOut, 0, wFree);

      if (SafePageWrite() == false) return false; // ���������� �����

      OpenOut(wPageOut + 1);                    // ���������������� � ������ ��������� ��������

      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ � �����
    	memset(mpbPageOut + wByteOut, 0, wSize);
      wByteOut += wSize;                        // ����������� ������� ���������� ������

      return true;
    }
  }
}
*/

bool CloseOut(void)
{
  return SafePageWrite(wPageOut_);
}



bool    OpenIn(uint  wPage)
{
  wPageIn_ = wPage;
  wByteIn = 0;

  return( SafePageRead(wPageIn_) );
}


void ClearIn(void)
{
  memset(&mpbPageIn, 0, sizeof(mpbPageIn));
}


bool Load(void  *pbBase, uint  wSize)
{     
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wLEAF_BYTES - wByteIn;           // ������ ������������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ������������� ����� ������
    {                                           // ������ ������ �� ������
      memcpy(pbBase, mpbPageIn + wByteIn, wFree);

      if (OpenIn(wPageIn_ + 1) == 0) return false;  // ������ � ����� ��������� ��������

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO ��������� �� ��������� ������� ��������� ������
      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ �� ������
      memcpy(pbBase, mpbPageIn + wByteIn, wSize);
      wByteIn += wSize;                         // ����������� ������� ���������� ������

      return true;
    }
  }

  return true;
}



bool SaveBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenOut(wPage);

  if (Save(pbBuff, wSize) == false)
    return false;

  return CloseOut();
}

/*
bool CleanBuff(uint wPage, uint wSize)
{
  OpenOut(wPage);

  if (Clean(wSize) == false)
    return false;

  return CloseOut();
}
*/

bool LoadBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenIn(wPage);
  return Load(pbBuff, wSize);
}



bool SaveFile(file const *pfl)
{
  return SaveBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}


bool LoadFile(file const *pfl)
{
  return LoadBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}


// TODO ������ �������� � ������� ������� �������
