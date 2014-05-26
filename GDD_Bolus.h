/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_BOLUS_H_
#define	 _GDD_BOLUS_H_

#ifdef GDD_BOLUS_PUB
#define GDD_BOLUSPUB
#else
#define GDD_BOLUSPUB extern
#endif

#define SET_BOLUS					0
#define DELIVERED_BOLUS		1
#define COMPLETED_BOLUS		2
#define STOPPED_BOLUS			3



GDD_BOLUSPUB void CreateBolus(void);
GDD_BOLUSPUB void CreatePrimitivesForBolus(void);
GDD_BOLUSPUB WORD msgBolus(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
#endif
