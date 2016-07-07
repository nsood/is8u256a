/************************************************************/
/*				Copy Right (C) HED.Inc						*/
/*				All Right Reserved							*/
/*文件名称：CIU98320a_24lc128.h							*/
/*作    者：												*/
/*当前版本：V1.0.0											*/
/*日    期：2012-08-26										*/
/*功能描述：	   											*/
/*修改内容：初版做成										*/
/************************************************************/
#ifndef __CIU98320A_24LC128_H__
#define __CIU98320A_24LC128_H__

#ifndef CIU09320A_24LC128
#define LC128_EXT		extern
#else
#define LC128_EXT
#endif

LC128_EXT	void ByteWrite(UINT16 address,UINT8 data);
LC128_EXT UINT8 RandomRead(UINT16 address);
LC128_EXT void PageWrite(UINT16 address,UINT8 *pData);
LC128_EXT void SequentialRead(UINT8 *pData,UINT16 address,UINT8 bytelen);

#endif
