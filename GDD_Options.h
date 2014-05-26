/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_OPTIONS_H_
#define	 _GDD_OPTIONS_H_

#ifdef GDD_OPTIONS_PUB
#define GDD_OPTIONSPUB
#else
#define GDD_OPTIONSPUB extern
#endif

GDD_OPTIONSPUB void CreateOptions(void);
GDD_OPTIONSPUB void CreatePrimitivesForOptions(void);
GDD_OPTIONSPUB WORD msgOptions(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
#endif
