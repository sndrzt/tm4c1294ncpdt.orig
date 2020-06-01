/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dff.h"


int EncodeInt(__int64 value) {
  int num = 0; // ����� ���������� ���� (��� + 7 ���)
  char ch;
  while ((value >> (num * 7 - 1)) != -1 && (value >> (num * 7 - 1)) != 0 || num == 0) //������� ��������� �����������: ���������� ���� � ��������� ���������� ���� ���� ���� �����
  {
    if (send_buffer_position > send_buffer + PACKETMAXSIZE) // ���� ����� �� ������� ������ �������� ��������
    {
      send_buffer_position -= num;
      return 1;
    }
    ch = (char)(value >> (num * 7)); // ��������� 7 ���
    * send_buffer_position++ = ch | 0x80; // ������ � ������ lbf
    num++; //�������� ��������� 7 ���
  }*
  (send_buffer_position - 1) &= 0x7F; //������ ���� � ���������� �����
  return 0;
}



void left_shift2(uchar  *array, uint  wSize, uint  bits)
{
  uint b;
  for (b=0; b<bits; b++)
  {
    sint i;
    for (i=wSize-1; i >= 0; i--)
    {
      array[i] = array[i] << 1;

      if (i > 0)
      {
        uchar c = (array[i-1] >> 7) & 0x01;
        array[i] = array[i] | c;
      }
    }
  }
}


uchar*  DffPopDecodeBuff(uchar  *pb) {
  static uchar result[8];
  uchar buff[8];

//  InitPop(i);

  memset(&result, 0, sizeof(result));
  int bits = 0;

  do {
    memset(&buff, 0, sizeof(buff));
    buff[0] = (*pb /*InBuff(i)*/ & 0x7F);

    left_shift2(buff, sizeof(buff), bits);

    uint i;
    for (i=0; i < sizeof(result); i++)
      result[i] |= buff[i];

    bits += 4/*7*/;
  }
  while (*(pb++)/*InBuff(i++)*/ & 0x80);

  return result;
}



uint64_t DffPopDecodeLong64(uchar  i) {
  InitPop(i);

  uint64_t result = 0;
  int bits = 0;
  uint64_t ddw;

  do {
    ddw = (InBuff(i) & 0x7F);
    result += (ddw << bits);
    bits += 7;
  }
  while (InBuff(i++) & 0x80);

//  if (ddw >> 6)
//    result |= (0xffffffffffffffff << bits);

  return result;
}



uint64_t DffDecodeLong64(uchar  *pb) {
  uint64_t result = 0;
  int bits = 0;
  uint64_t ddw;

  do {
    ddw = (*pb & 0x7F);
    result += (ddw << bits);
    bits += 7;
  }
  while (*(pb++) & 0x80);

//  if (ddw >> 6)
//    result |= (0xffffffffffffffff << bits);

  return result;
}



ulong   DffDecodeLong(uchar  *pb) {
  ulong result = 0;
  int bits = 0;
  ulong dw;

  do {
    dw = (*pb & 0x7F);
    result += (dw << bits);
    bits += 7;
  }
  while (*(pb++) & 0x80);

//  if (dw >> 6)
//    result |= (0xffffffff << bits);

  return result;
}
