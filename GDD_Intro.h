/*****************************************************************************
 *****************************************************************************/

#ifndef _INTRO_H
#define _INTRO_H

#ifdef INTRO_PUB
#define INTROPUB
#else
#define INTROPUB extern
#endif

INTROPUB	void CreateIntro(void);
INTROPUB	void CreatePrimitivesForIntro(void);
INTROPUB	WORD msgIntro(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg);
INTROPUB	void UpdateIntro(void);
#endif // _INTRO_H
