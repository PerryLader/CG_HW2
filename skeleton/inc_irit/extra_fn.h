/*****************************************************************************
*   "Irit" - the 3d polygonal solid modeller.				     *
******************************************************************************
* (C) Gershon Elber, Technion, Israel Institute of Technology                *
******************************************************************************
* Extra functions from external, public domain, sources.		     *
*****************************************************************************/

#ifndef	IRIT_EXTRA_FN_H
#define IRIT_EXTRA_FN_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* SVD decomposition. */
int SvdMatrix4x4(IrtHmgnMatType M,
		 IrtRType U[3][3],
		 IrtVecType S,
		 IrtRType V[3][3]);
void SvdMatrixNxN(IrtRType *M, IrtRType *U, IrtRType *S, IrtRType *V, int n);
void SvdDecomp(IrtRType **a, int m, int n, IrtRType *w, IrtRType **v);


typedef struct XtraSvdLSGenInfoStruct *XtraSvdLSGenInfoStructPtr;

XtraSvdLSGenInfoStructPtr SvdLeastSqrInit(IrtRType *A,
					  int NData,
					  int Nx,
					  IrtRType *RecipCondNum);
IrtRType SvdLeastSqr(XtraSvdLSGenInfoStructPtr SLSGI, IrtRType *x, IrtRType *b);
void SvdLeastSqrFree(XtraSvdLSGenInfoStructPtr SLSGI);

/* Matrix diagonalization. */
void JacobiMatrixDiag4x4(IrtRType M[4][4],
			 IrtRType U[4][4],
			 IrtRType D[4][4],
			 IrtRType V[4][4]);
void JacobiMatrixDiagNxN(IrtRType *M[],
			 IrtRType *U[],
			 IrtRType *D[],
			 IrtRType *V[],
			 int n);

/* Bezier interpolation. */
void BzrCrvInterp(IrtRType *Result, IrtRType *Input, int Size);

/* Irit internal random number generator. */
void MtIritSrandom(long Seed);
long MtIritRandom(void);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* IRIT_EXTRA_FN_H */
