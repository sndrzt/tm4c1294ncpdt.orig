/*------------------------------------------------------------------------------
FILES.C

 ������� ������/������ ������ �� ���������
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "at45.h"
#include        "files.h"



void    OpenOut(uint  wPage)
{
  wPageOut = wPage;
  wByteOut = 0;
}


void ClearOut(void)
{
  memset(&mpbPageOut, 0, sizeof(mpbPageOut));
}


boolean Save(void  *pbBase, uint  wSize)
{
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite() == FALSE) return FALSE; // ���������� �����

      OpenOut(wPageOut + 1);                    // ���������������� � ������ ��������� ��������

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO ��������� �� ��������� ������� ��������� ������
      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ � �����
      memcpy(mpbPageOut + wByteOut, pbBase, wSize);                                  
      wByteOut += wSize;                        // ����������� ������� ���������� ������

      return TRUE;
    }
  }
}  


boolean Clean(uint  wSize)
{
uint    wFree;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memset(mpbPageOut + wByteOut, 0, wFree);

      if (SafePageWrite() == FALSE) return FALSE; // ���������� �����

      OpenOut(wPageOut + 1);                    // ���������������� � ������ ��������� ��������

      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ � �����
    	memset(mpbPageOut + wByteOut, 0, wSize);
      wByteOut += wSize;                        // ����������� ������� ���������� ������

      return TRUE;
    }
  }
}


boolean CloseOut(void)
{
  return SafePageWrite();
}



boolean OpenIn(uint  wPage)
{
  wPageIn = wPage;
  wByteIn = 0;

  return( SafePageRead() );
}


void ClearIn(void)
{
  memset(&mpbPageIn, 0, sizeof(mpbPageIn));
}


boolean Load(void  *pbBase, uint  wSize)
{     
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteIn;           // ������ ������������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ������������� ����� ������
    {                                           // ������ ������ �� ������
      memcpy(pbBase, mpbPageIn + wByteIn, wFree);

      if (OpenIn(wPageIn + 1) == 0) return FALSE;  // ������ � ����� ��������� ��������

      for (i=0; i<wFree; i++)
    	  pbBase = (char *)pbBase + 1;                          // TODO ��������� �� ��������� ������� ��������� ������
      wSize  -= wFree;                          // ��������� ������ ����� ������
    }
    else
    {                                           // ������� ��� ������ �� ������
      memcpy(pbBase, mpbPageIn + wByteIn, wSize);
      wByteIn += wSize;                         // ����������� ������� ���������� ������

      return TRUE;
    }
  }
}



boolean SaveBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenOut(wPage);

  if (Save(pbBuff, wSize) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean CleanBuff(uint wPage, uint wSize)
{
  OpenOut(wPage);

  if (Clean(wSize) == FALSE)
    return FALSE;

  return CloseOut();
}


boolean LoadBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenIn(wPage);
  return Load(pbBuff, wSize);
}



boolean SaveFile(file const *pfl)
{
  return SaveBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}


boolean LoadFile(file const *pfl)
{
  return LoadBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}


// TODO ������ �������� � ������� ������� �������
