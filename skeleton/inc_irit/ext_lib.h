/******************************************************************************
* Ext_lib.h - header file for the extensions library.			      *
*******************************************************************************
* (C) Gershon Elber, Technion, Israel Institute of Technology                 *
*******************************************************************************
* Written by Gershon Elber, Aug 2009.					      *
******************************************************************************/

#ifndef IRIT_EXTEN_LIB_H
#define IRIT_EXTEN_LIB_H


#include "inc_irit/irit_sm.h"
#include "inc_irit/iritprsr.h"
#include "inc_irit/cagd_lib.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* FUnctions related to rectangular region tiling from curves. */
CagdCrvStruct *IrtExtC2SOrderCurves(CagdCrvStruct *CrvList, 
				    int IsBoolSumOrder);
IPObjectStruct *IrtExtC2SGeneral(CagdCrvStruct **CrvList,
				 IrtRType AngularDeviation,
				 IrtRType ConcaveCorners,
				 int CurveOutputType,
				 IrtRType SizeRectangle,
				 int NumSmoothingSteps,
				 const char **ErrorMsg,
				 const char *Name);

void IrtExtExampleFunction(IrtRType *R, IrtVecType V);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* IRIT_EXTEN_LIB_H */
