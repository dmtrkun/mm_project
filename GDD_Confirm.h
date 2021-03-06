/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_CONFIRM_H_
#define	 _GDD_CONFIRM_H_

#ifdef GDD_CONFIRM_PUB
#define GDD_CONFIRMPUB
#else
#define GDD_CONFIRMPUB extern
#endif

GDD_CONFIRMPUB void CreateConfirm(void);
GDD_CONFIRMPUB void CreatePrimitivesForConfirm(void);
GDD_CONFIRMPUB WORD msgConfirm(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);

#endif  /*_GDD_CONFIRM_H_*/
