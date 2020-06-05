/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

#include "../../main.h"
#include "../../serial/ports.h"
#include "dff.h"



int     EncodeInt(int64_t  value, uchar  *pbOut) {
  int num = 0; // ����� ���������� ���� (lbf + 7 ���)
  char ch;

  // ������� ��������� �����������: ���������� ���� � ��������� ���������� ���� ���� ���� �������
  while ((value>>(num*7-1)) != -1 && (value>>(num*7-1)) != 0 || num==0) {
    ch = (char)(value>>(num*7));                          // ��������� 7 ���
    *pbOut++ = ch | 0x80;                                 // ������ � ������ lbf
    num++;                                                // �������� ��������� 7 ���
  }

  *(pbOut-1) &= 0x7F;                                     // ������ ���� lbf � ���������� �����
  return num;
}



uchar   DffEncode(int64_t  value, uchar  *pbOut) {
  int bytes = 0;
  int bits = 0;

  while (true)
  {
    int64_t new = value >> (bits - 1);
    bool f1 = (new != -1);
    bool f2 = (new != 0);
    bool f3 = (bytes == 0);
    bool f = ((f1 && f2) || f3);
    if (f == false) break; // ������� ��������� �����������: ���������� ���� � ��������� ���������� ���� ���� ���� �������

    char ch = (char)(value >> bits); // ��������� 7 ���

    *pbOut++ = ch | 0x80; // ������ � ������ lbf

    bytes++;
    bits += 7;
  }

  *(pbOut - 1) &= 0x7F; // ������ ���� � ���������� �����

  return bytes;
}



uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut) {
  int bits = 0;
  uint64_t ch;

  do {
    ch = (*pbIn & 0x7F);
    (*pdwOut) += (ch << bits);
    bits += 7;
  }
  while (*(pbIn++) & 0x80);

  if (ch >> 6)
    (*pdwOut) |= (0xffffffffffffffff << bits);

  return pbIn;
}


uchar*  DffDecodePositive(uchar  *pbIn, int64_t  *pdwOut) {
  int bits = 0;
  uint64_t ch;

  do {
    ch = (*pbIn & 0x7F);
    (*pdwOut) += (ch << bits);
    bits += 7;
  }
  while (*(pbIn++) & 0x80);

  return pbIn;
}
