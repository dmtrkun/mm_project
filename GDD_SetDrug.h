/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_SETDRUG_H_
#define	 _GDD_SETDRUG_H_

#ifdef GDD_SETDRUG_PUB
#define GDD_SETDRUGPUB
#else
#define GDD_SETDRUGPUB extern
#endif

#ifdef GDD_SETDRUG_PUB
#else
extern GFX_RESOURCE_HDR const* drug_images[];
#endif

GDD_SETDRUGPUB void CreateSetdrug(void);
GDD_SETDRUGPUB void CreatePrimitivesForSetdrug(void);
GDD_SETDRUGPUB WORD msgSetdrug(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg);
#endif
