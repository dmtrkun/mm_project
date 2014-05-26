/*****************************************************************************
 *****************************************************************************/

#ifndef _ERROR_H
#define _ERROR_H

#ifdef ERROR_PUB
#define ERRORPUB
#else
#define ERRORPUB extern
#endif

#define HW_ERRTYPE	0

#define NO_ERR				0
#define EEPROM_ERR		1


ERRORPUB	void SetError(unsigned char err, unsigned char type);
ERRORPUB	unsigned int GetError(void);
ERRORPUB	 void CreateError(void);
ERRORPUB	 void CreatePrimitivesForError(void);
ERRORPUB	 WORD msgError(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);

#endif // _ERROR_H
