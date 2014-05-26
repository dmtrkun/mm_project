/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_SETPROG_H_
#define	 _GDD_SETPROG_H_

#ifdef GDD_SETPROG_PUB
#define GDD_SETPROGPUB
#else
#define GDD_SETPROGPUB extern
#endif

#ifdef GDD_SETPROG_PUB
#else
extern GFX_IMAGE_HEADER const* prog_images[];
#endif

GDD_SETPROGPUB void CreateSetprog(void);
GDD_SETPROGPUB void CreatePrimitivesForSetprog(void);
GDD_SETPROGPUB WORD msgSetprog(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
#endif
