/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_PRIME_H_
#define	 _GDD_PRIME_H_

#ifdef GDD_PRIME_PUB
#define GDD_PRIMEPUB
#else
#define GDD_PRIMEPUB extern
#endif

//GDD_PRIMEPUB float prime_vol;


GDD_PRIMEPUB void CreatePrime(void);
GDD_PRIMEPUB void CreatePrimitivesForPrime(void);
GDD_PRIMEPUB WORD msgPrime(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);
#endif
