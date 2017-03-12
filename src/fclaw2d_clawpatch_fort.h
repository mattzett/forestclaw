/*
Copyright (c) 2012 Carsten Burstedde, Donna Calhoun
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef FCLAW2D_CLAWPATCH_FORT_H
#define FCLAW2D_CLAWPATCH_FORT_H

/* this header file must come first */
#include <fclaw2d_defs.h>

#include <forestclaw2d.h>
#include <fclaw2d_convenience.h>

#include <fclaw_options.h>
#include <fclaw2d_transform.h>

#ifdef __cplusplus
extern "C"
{          /* Beginning of extern "C" */
#if 0
}
#endif
#endif

/* ------------------------------------------------------------------------ */

/* ----------------------------------------------------------------------------------
   Internal boundary conditions
   ---------------------------------------------------------------------------------- */

#define FCLAW2D_CLAWPATCH_FORT_ERROR FCLAW_F77_FUNC(fclaw2d_clawpatch_fort_error, \
                                                    FCLAW2D_CLAWPATCH_FORT_ERROR)

void FCLAW2D_CLAWPATCH_FORT_ERROR(int* blockno, int *mx, int *my, int* mbc, int* meqn,
                                  double *dx, double *dy, double *xlower,
                                  double *ylower, double *t, double q[],
                                  double error[]);


/* Not obvious that the user would want to generalize the conservation routine,
   so they are not in a 'default' file.*/

#define FCLAW2D_CLAWPATCH_FORT_CONSCHECK FCLAW_F77_FUNC(fclaw2d_clawpatch_fort_conscheck, \
                                                        FCLAW2D_CLAWPATCH_FORT_CONSCHECK)

void FCLAW2D_CLAWPATCH_FORT_CONSCHECK(int *mx, int *my, int* mbc, int* meqn,
                                      double *dx, double *dy,
                                      double* area, double *q, double* sum);

/* These are only needed if the user has not supplied their own routine to compute
   the area of the entire domain. Not obvious taht the user would want to
   generalize these routines. */
#define FCLAW2D_CLAWPATCH_FORT_AREA FCLAW_F77_FUNC(fclaw2d_clawpatch_fort_area, \
                                                   FCLAW2D_CLAWPATCH_FORT_AREA)

double FCLAW2D_CLAWPATCH_FORT_AREA(int *mx, int* my, int*mbc, double* dx,
                                   double* dy, double area[]);


#define FCLAW2D_CLAWPATCH_FORT_NORM FCLAW_F77_FUNC(fclaw2d_clawpatch_fort_norm, \
                                                   FCLAW2D_CLAWPATCH_FORT_NORM)

void FCLAW2D_CLAWPATCH_FORT_NORM(int *mx, int *my, int *mbc, int *meqn,
                                 double *dx, double *dy, double area[],
                                 double error[], double error_norm[]);


#if 0
typedef void (*fclaw2d_fort_exchange_face_ghost_t)(int* mx, int* my, int* mbc, int* meqn,
                                                   double qthis[], double qneighbor[],
                                                   int* iface,
                                                   fclaw2d_transform_data_t** transform_cptr);

typedef void (*fclaw2d_fort_exchange_corner_ghost_t)(int* mx, int* my, int* mbc, int* meqn,
                                                     double this_q[],double neighbor_q[],
                                                     int* icorner,
                                                     fclaw2d_transform_data_t** transform_cptr);


#define FCLAW2D_FORT_EXCHANGE_FACE_GHOST FCLAW_F77_FUNC(fclaw2d_fort_exchange_face_ghost, \
                                                       FCLAW2D_FORT_EXCHANGE_FACE_GHOST)

void FCLAW2D_FORT_EXCHANGE_FACE_GHOST(int* mx, int* my, int* mbc, int* meqn,
                                      double qthis[],double qneighbor[], int* iface,
                                      fclaw2d_transform_data_t** transform_cptr);


#define FCLAW2D_FORT_EXCHANGE_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_exchange_corner_ghost, \
                                                          FCLAW2D_FORT_EXCHANGE_CORNER_GHOST)

void FCLAW2D_FORT_EXCHANGE_CORNER_GHOST(int* mx, int* my, int* mbc, int* meqn,
                                        double this_q[],double neighbor_q[],
                                        int* icorner,
                                        fclaw2d_transform_data_t** transform_cptr);


#define FCLAW2D_FORT_AVERAGE_FACE_GHOST FCLAW_F77_FUNC(fclaw2d_fort_average_face_ghost, \
                                                       FCLAW2D_FORT_AVERAGE_FACE_GHOST)
void FCLAW2D_FORT_AVERAGE_FACE_GHOST(int* mx, int* my, int* mbc, int* meqn,
                                     double qcoarse[], double qfine[],
                                     double areacoarse[], double areafine[],
                                     const int& idir, const int& iside,
                                     const int& num_neighbors,
                                     const int& refratio, const int& igrid,
                                     const int& manifold, fclaw2d_transform_data_t** transform_cptr);

#define FCLAW2D_FORT_INTERPOLATE_FACE_GHOST FCLAW_F77_FUNC(fclaw2d_fort_interpolate_face_ghost, \
                                                           FCLAW2D_FORT_INTERPOLATE_FACE_GHOST)
void FCLAW2D_FORT_INTERPOLATE_FACE_GHOST(const int& mx, const int& my, const int& mbc,
                                         const int& meqn,
                                         double qthis[],double qcoarse[],
                                         const int& idir, const int& iside,
                                         const int& num_neighbors,
                                         const int& refratio, const int& igrid,
                                         fclaw2d_transform_data_t** transform_cptr);

#define FCLAW2D_FORT_AVERAGE_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_average_corner_ghost, \
                                                         FCLAW2D_FORT_AVERAGE_CORNER_GHOST)
void FCLAW2D_FORT_AVERAGE_CORNER_GHOST(int* mx, int* my, int* mbc, int* meqn,
                                       int* a_refratio,
                                       double qcoarse[], double qfine[],
                                       double areacoarse[], double areafine[],
                                       const int& manifold,
                                       const int& a_corner, fclaw2d_transform_data_t** transform_cptr);

#define FCLAW2D_FORT_INTERPOLATE_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_interpolate_corner_ghost, \
                                                             FCLAW2D_FORT_INTERPOLATE_CORNER_GHOST)
void FCLAW2D_FORT_INTERPOLATE_CORNER_GHOST(const int& mx, const int& my, const int& mbc,
                                           const int& meqn, const int& a_refratio, double this_q[],
                                           double neighbor_q[], const int& a_corner,
                                           fclaw2d_transform_data_t** transform_cptr);


#define FCLAW2D_FORT_MB_EXCHANGE_BLOCK_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_mb_exchange_block_corner_ghost, \
                                                                   FCLAW2D_FORT_MB_EXCHANGE_BLOCK_CORNER_GHOST)
void FCLAW2D_FORT_MB_EXCHANGE_BLOCK_CORNER_GHOST(const int& mx, const int& my,
                                                 const int& mbc, const int& meqn,
                                                 double qthis[], double qneighbor[], const int& icorner,
                                                 const int& iblock);



// Averaging at block boundaries between coarse and fine grids.
#define FCLAW2D_FORT_MB_AVERAGE_BLOCK_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_mb_average_block_corner_ghost,\
                                                                  FCLAW2D_FORT_MB_AVERAGE_BLOCK_CORNER_GHOST)
void  FCLAW2D_FORT_MB_AVERAGE_BLOCK_CORNER_GHOST(const int& mx, const int& my, const int& mbc,
                                                 const int& meqn,const int& refratio, double qcoarse[],
                                                 double qfine[],double areacoarse[], double areafine[],
                                                 const int& a_coarse_corner,
                                                 const int& blockno);

// Averaging at block boundaries between coarse and fine grids.
#define FCLAW2D_FORT_MB_INTERPOLATE_BLOCK_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_mb_interpolate_block_corner_ghost, \
                                                         FCLAW2D_FORT_MB_INTERPOLATE_BLOCK_CORNER_GHOST)
void  FCLAW2D_FORT_MB_INTERPOLATE_BLOCK_CORNER_GHOST(const int& mx, const int& my, const int& mbc,
                                                     const int& meqn,const int& refratio,
                                                     double qcoarse[],
                                                     double qfine[],const int& a_coarse_corner,
                                                     const int& blockno);


/* ----------------------------------------------------------------------------------
   Physical boundary conditions
   ---------------------------------------------------------------------------------- */
#define FCLAW2D_FORT_SET_PHYS_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_set_phys_corner_ghost, \
                                                          FCLAW2D_FORT_SET_PHYS_CORNER_GHOST)
void FCLAW2D_FORT_SET_PHYS_CORNER_GHOST(const int& mx, const int& my, const int& mbc,
                                        const int& meqn, double q[],const int& icorner,
                                        const double &t, const double& dt, const int mthbc[]);

#define FCLAW2D_FORT_EXCHANGE_PHYS_CORNER_GHOST FCLAW_F77_FUNC(fclaw2d_fort_exchange_phys_corner_ghost, \
                                                               FCLAW2D_FORT_EXCHANGE_PHYS_CORNER_GHOST)
void FCLAW2D_FORT_EXCHANGE_PHYS_CORNER_GHOST(const int& mx, const int& my, const int& mbc,
                                 const int& meqn, double qthis[],double qneighbor[],
                                 const int& icorner, const int& iside);

#endif


#ifdef __cplusplus
#if 0
{
#endif
}           /* end of extern "C" */
#endif

#endif
