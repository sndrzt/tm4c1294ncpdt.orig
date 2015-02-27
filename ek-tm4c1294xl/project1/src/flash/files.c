/*------------------------------------------------------------------------------
FILES.C

 ������� ������/������ ������ �� ���������
------------------------------------------------------------------------------*/

#include        <string.h>
#include        "../main.h"
#include        "../memory/mem_flash.h"
#include        "at45.h"



void    OpenOut(uint  wPage)
{
  wPageOut = wPage;
  wByteOut = 0;

  bBlockOut = 0;
}


void    OpenOut2(uint  wPage)
{
  wPageOut = wPage;
  wByteOut = 0;
}


boolean Save(void  *pbBase, uint  wSize, format  fo)
{
uint    wFree;
uint    i;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memcpy(mpbPageOut + wByteOut, pbBase, wFree);                                

      if (SafePageWrite(fo) == FALSE) return FALSE; // ���������� �����

      OpenOut2(wPageOut + 1);                   // ���������������� � ������ ��������� ��������

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


boolean Clean(uint  wSize, format  fo)
{
uint    wFree;

  while (wSize > 0)
  {
    wFree = wFREEPAGE_SIZE - wByteOut;          // ������ ��������� ����� ������

    if (wSize > wFree)                          // ���� ������ ������ ������� ��������� ����� ������
    {                                           // ��������� �� ��������� �����
      memset(mpbPageOut + wByteOut, 0, wFree);

      if (SafePageWrite(fo) == FALSE) return FALSE; // ���������� �����

      OpenOut2(wPageOut + 1);                   // ���������������� � ������ ��������� ��������

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


boolean CloseOut(format  fo)
{
  return SafePageWrite(fo);
}



boolean OpenIn(uint  wPage)
{
  wPageIn = wPage;
  wByteIn = 0;

  return( SafePageRead() );
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



boolean SaveBuff(uint wPage, void *pbBuff, uint wSize, format  fo)
{
  OpenOut(wPage);

  if (Save(pbBuff, wSize, fo) == FALSE)
    return FALSE;

  return CloseOut(fo);
}


boolean LoadBuff(uint wPage, void *pbBuff, uint wSize)
{
  OpenIn(wPage);
  return Load(pbBuff, wSize);
}



boolean SaveFile(file const *pfl)
{
  return SaveBuff(pfl->wPage, pfl->pbBuff, pfl->wSize, pfl->foSelf);
}


boolean LoadFile(file const *pfl)
{
  return LoadBuff(pfl->wPage, pfl->pbBuff, pfl->wSize);
}
