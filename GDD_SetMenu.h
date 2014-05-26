/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_SETMENU_H_
#define	 _GDD_SETMENU_H_

#ifdef GDD_SETMENU_PUB
#define GDD_SETMENUPUB
#else
#define GDD_SETMENUPUB extern
#endif

GDD_SETMENUPUB unsigned int pswrd;
GDD_SETMENUPUB void CreateSetmenu(void);
GDD_SETMENUPUB void CreatePrimitivesForSetmenu(void);
GDD_SETMENUPUB WORD msgSetmenu(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
#endif
