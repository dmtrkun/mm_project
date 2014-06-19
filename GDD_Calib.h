/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_CALIB_H_
#define	 _GDD_CALIB_H_

#ifdef GDD_CALIB_PUB
#define GDD_CALIBPUB
#else
#define GDD_CALIBPUB extern
#endif

GDD_CALIBPUB void CreateCalib(void);
GDD_CALIBPUB void CreatePrimitivesForCalib(void);
GDD_CALIBPUB WORD msgCalib(WORD objMsg, GFX_GOL_OBJ_HEADER* pObj, GFX_GOL_MESSAGE* pMsg);
#endif
