/*****************************************************************************
 *****************************************************************************/

#ifndef _PWRDOWN_H
#define _PWRDOWN_H

#ifdef PWRDOWN_PUB
#define PWRDOWNPUB
#else
#define PWRDOWNPUB extern
#endif

PWRDOWNPUB	 void CreatePwrdown(void);
PWRDOWNPUB	 void CreatePrimitivesForPwrdown(void);
PWRDOWNPUB	 WORD msgPwrdown(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);

#endif // _PWRDOWN_H
