/*------------------------------------------------------------------------------
dff.c


------------------------------------------------------------------------------*/

uchar   DffEncode(int64_t  value, uchar*  send_buffer_position);

int EncodeInt(int64_t value, uint8_t *send_buffer_position);

uint64_t DffDecodePositive_(uchar  *pb);
uchar*  DffDecode(uchar  *pbIn, int64_t  *pdwOut);
uchar*  DffDecodePositive(uchar  *pbIn, int64_t  *pdwOut);

uchar  pucDecodeBitArr(uchar *pOut, uchar *pIn);
