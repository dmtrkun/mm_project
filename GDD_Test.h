/*****************************************************************************
*
* Author               Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*
*****************************************************************************/
#ifndef	_GDD_TEST_H_
#define	 _GDD_TEST_H_

#ifdef GDD_TEST_PUB
#define GDD_TESTPUB
#else
#define GDD_TESTPUB extern
#endif

GDD_TESTPUB void CreateTest(void);
GDD_TESTPUB void UpdateTest(void);
GDD_TESTPUB void CreatePrimitivesForTest(void);
GDD_TESTPUB WORD msgTest(WORD objMsg, OBJ_HEADER* pObj, GOL_MSG* pMsg);

#endif
