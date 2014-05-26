/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_RUN_H_
#define	 _GDD_RUN_H_

#ifdef GDD_RUN_PUB
#define GDD_RUNPUB
#else
#define GDD_RUNPUB extern
#endif

//#define press2hight(press) ((press + 300) / (1100/194))
#define press2hight(press) (press / (1100/194))

GDD_RUNPUB void CreateRun(void);
GDD_RUNPUB void CreatePrimitivesForRun(void);
GDD_RUNPUB WORD msgRun(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
GDD_RUNPUB void UpdateRun(void);
#endif /*_GDD_RUN_H_*/
