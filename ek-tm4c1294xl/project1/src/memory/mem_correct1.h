/*------------------------------------------------------------------------------
MEM_CORRECT1,H


------------------------------------------------------------------------------*/

#ifndef __CORRECT1
#define __CORRECT1


// �������� ��� ��������� ������� ������ � �����, �� ������� � ���������� ������, �� ������� �� ����� ���������
typedef struct
{
// ������� ������� ��������� �������
uint            mpwPosValueCurr[15],
                mpwNegValueCurr[15],
                mpwPosValuePrev[15],
                mpwNegValuePrev[15];

// ������� ��������� ��������� �������
uint            mpwPosCountCurr[15],
                mpwNegCountCurr[15],
                mpwPosCountPrev[15],
                mpwNegCountPrev[15];
} correct1;



extern  correct1                Correct1;


#endif
