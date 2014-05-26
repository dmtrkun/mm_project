/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_CLEAR_H_
#define	 _GDD_CLEAR_H_

#ifdef GDD_CLEAR_PUB
#define GDD_CLEARPUB
#else
#define GDD_CLEARPUB extern
#endif

GDD_CLEARPUB void CreateClear(void);
GDD_CLEARPUB void CreatePrimitivesForClear(void);
GDD_CLEARPUB WORD msgClear(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);

#endif
