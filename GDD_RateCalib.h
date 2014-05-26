/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_RCALIB_H_
#define	 _GDD_RCALIB_H_

#ifdef GDD_RCALIB_PUB
#define GDD_RCALIBPUB
#else
#define GDD_RCALIBPUB extern
#endif

GDD_RCALIBPUB void CreateRCalib(void);
GDD_RCALIBPUB void CreatePrimitivesForRCalib(void);
GDD_RCALIBPUB WORD msgRCalib(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
#endif
