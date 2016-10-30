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

#ifndef FCLAW2D_CLAWPATCH_H
#define FCLAW2D_CLAWPATCH_H

#include <fclaw2d_patch.h>
#include <fclaw2d_global.h>
#include <fclaw2d_domain.h>

#ifdef __cplusplus
extern "C"
{
#if 0
}                               /* need this because indent is dumb */
#endif
#endif

typedef enum
{
    FCLAW2D_BUILD_FOR_GHOST_AREA_COMPUTED = 0,
    FCLAW2D_BUILD_FOR_GHOST_AREA_PACKED,
    FCLAW2D_BUILD_FOR_UPDATE,
    FCLAW2D_BUILD_COSTOM
} fclaw2d_build_mode_t;


void fclaw2d_clawpatch_link_app (fclaw_app_t * app);
void fclaw2d_clawpatch_link_global (fclaw2d_global_t * global);

void* fclaw2d_clawpatch_new_patch();   /* Called in fclaw2d_patch */
void fclaw2d_clawpatch_delete_patch(void *cp);


void fclaw2d_clawpatch_grid_data(fclaw2d_domain_t* domain,
                                 fclaw2d_patch_t* this_patch,
                                 int* mx, int* my, int* mbc,
                                 double* xlower, double* ylower,
                                 double* dx, double* dy);


void fclaw2d_clawpatch_metric_data(fclaw2d_domain_t* domain,
                                   fclaw2d_patch_t* this_patch,
                                   double **xp, double **yp, double **zp,
                                   double **xd, double **yd, double **zd,
                                   double **area);

void fclaw2d_clawpatch_metric_data2(fclaw2d_domain_t* domain,
                                    fclaw2d_patch_t* this_patch,
                                    double **xnormals, double **ynormals,
                                    double **xtangents, double **ytangents,
                                    double **surfnormals, double ** edgelengths,
                                    double **curvature);

double* fclaw2d_clawpatch_get_area(fclaw2d_domain_t* domain,
                                   fclaw2d_patch_t* this_patch);

void fclaw2d_clawpatch_soln_data(fclaw2d_domain_t* domain,
                                 fclaw2d_patch_t* this_patch,
                                 double **q, int* meqn);

double *fclaw2d_clawpatch_get_q(fclaw2d_domain_t* domain,
                                fclaw2d_patch_t* this_patch);


double* fclaw2d_clawpatch_get_error(fclaw2d_domain_t* domain,
                                    fclaw2d_patch_t* this_patch);

size_t fclaw2d_clawpatch_size(fclaw2d_domain_t *domain);

void fclaw2d_clawpatch_timesync_data(fclaw2d_domain_t* domain,
                                     fclaw2d_patch_t* this_patch,
                                     fclaw_bool time_interp,
                                     double **q, int* meqn);

double *fclaw2d_clawpatch_get_q_timesync(fclaw2d_domain_t* domain,
                                         fclaw2d_patch_t* this_patch,
                                         int time_interp);

void fclaw2d_clawpatch_save_current_step(fclaw2d_domain_t* domain,
                                         fclaw2d_patch_t* this_patch);

int* fclaw2d_clawpatch_block_corner_count(fclaw2d_domain_t* domain,
                                          fclaw2d_patch_t* this_patch);

void fclaw2d_clawpatch_set_block_corner_count(fclaw2d_domain_t* domain,
                                              fclaw2d_patch_t* this_patch,
                                              int icorner, int block_corner_count);

void fclaw2d_clawpatch_setup_timeinterp(fclaw2d_domain_t* domain,
                                        fclaw2d_patch_t *this_patch,
                                        double alpha);

void fclaw2d_clawpatch_finegrid_neighbors(fclaw2d_domain_t* domain);

int fclaw2d_clawpatch_has_finegrid_neighbors(fclaw2d_domain_t* domain,
                                             fclaw2d_patch_t* this_patch);

void fclaw2d_clawpatch_restore_step(fclaw2d_domain_t* domain,
                                    fclaw2d_patch_t* this_patch);

void fclaw2d_clawpatch_save_step(fclaw2d_domain_t* domain,
                                 fclaw2d_patch_t* this_patch);


/* -----------------------------------------------------
   Define/build clawpatches
   ---------------------------------------------------- */

void fclaw2d_clawpatch_define(fclaw2d_domain_t* domain,
                              fclaw2d_patch_t *this_patch,
                              int blockno, int patchno,
                              fclaw2d_build_mode_t build_mode);

/* A callback for building the domain and repartitioning */
void fclaw2d_clawpatch_build(fclaw2d_domain_t *domain,
                             fclaw2d_patch_t *this_patch,
                             int this_block_idx,
                             int this_patch_idx,
                             void *user);

void fclaw2d_clawpatch_build_ghost(fclaw2d_domain_t *domain,
                                   fclaw2d_patch_t *this_patch,
                                   int blockno,
                                   int patchno,
                                   void *user);


void fclaw2d_clawpatch_build_from_fine(fclaw2d_domain_t *domain,
                                       fclaw2d_patch_t *fine_patches,
                                       fclaw2d_patch_t *coarse_patch,
                                       int blockno,
                                       int coarse_patchno,
                                       int fine0_patchno,
                                       fclaw2d_build_mode_t build_mode);

void fclaw2d_clawpatch_set_boundary_to_nan(fclaw2d_domain_t* domain,
                                           int minlevel,
                                           int maxlevel,
                                           int time_interp);

void fclaw2d_clawpatch_set_boundary_to_value(fclaw2d_domain_t* domain,
                                             int minlevel,
                                             int maxlevel,
                                             int time_interp,
                                             double value);

void fclaw2d_clawpatch_set_corners_to_value(fclaw2d_domain_t* domain,
                                            int minlevel,
                                            int maxlevel,
                                            int time_interp,
                                            double value);

void fclaw2d_clawpatch_set_corners_to_nan(fclaw2d_domain_t* domain,
                                          int minlevel,
                                          int maxlevel,
                                          int time_interp);


/* -----------------------------------------------------
   Build/pack/size for partitioning
   ---------------------------------------------------- */
size_t fclaw2d_clawpatch_partition_packsize(fclaw2d_domain_t* domain);


void cb_fclaw2d_clawpatch_partition_pack(fclaw2d_domain_t *domain,
                                         fclaw2d_patch_t *this_patch,
                                         int this_block_idx,
                                         int this_patch_idx,
                                         void *user);

void cb_fclaw2d_clawpatch_partition_unpack(fclaw2d_domain_t *domain,
                                           fclaw2d_patch_t *this_patch,
                                           int this_block_idx,
                                           int this_patch_idx,
                                           void *user);

void fclaw2d_clawpatch_initialize_after_partition(fclaw2d_domain_t* domain,
                                                  fclaw2d_patch_t* this_patch,
                                                  int this_block_idx,
                                                  int this_patch_idx);
void fclaw2d_clawpatch_initialize_after_regrid(fclaw2d_domain_t* domain,
                                               fclaw2d_patch_t* this_patch,
                                               int this_block_idx,
                                               int this_patch_idx);



/* -----------------------------------------------------
   Build/pack/size for ghost exchange
   ---------------------------------------------------- */
size_t fclaw2d_clawpatch_ghost_packsize(fclaw2d_domain_t* domain);

    void fclaw2d_clawpatch_ghost_unpack(fclaw2d_domain_t* domain,
                                        fclaw2d_patch_t* this_patch,
                                        int this_block_idx, int this_patch_idx,
                                        double *qdata, fclaw_bool time_interp);


void fclaw2d_clawpatch_ghost_pack(fclaw2d_domain_t *domain,
                                  fclaw2d_patch_t *this_patch,
                                  double *patch_data,
                                  int time_interp);

void fclaw2d_clawpatch_ghost_pack_location(fclaw2d_domain_t* domain,
                                           fclaw2d_patch_t* this_patch,
                                           void **q);

void fclaw2d_clawpatch_ghost_free_pack_location(fclaw2d_domain_t* domain,
                                                void **q);


#if 0
void fclaw2d_clawpatch_ghost_comm(fclaw2d_domain_t* domain,
                                  fclaw2d_patch_t* this_patch,
                                  double *qpack, int time_interp,
                                  int packmode);
#endif

void fclaw2d_clawpatch_copy_face(fclaw2d_domain_t *domain,
                                   fclaw2d_patch_t *this_patch,
                                   fclaw2d_patch_t *neighbor_patch,
                                   int iface,
                                   int time_interp,
                                   fclaw2d_transform_data_t *transform_data);

void fclaw2d_clawpatch_average_face(fclaw2d_domain_t *domain,
                                    fclaw2d_patch_t *coarse_patch,
                                    fclaw2d_patch_t *fine_patch,
                                    int idir,
                                    int iface_coarse,
                                    int p4est_refineFactor,
                                    int refratio,
                                    fclaw_bool time_interp,
                                    int igrid,
                                    fclaw2d_transform_data_t* transform_data);

void fclaw2d_clawpatch_interpolate_face(fclaw2d_domain_t *domain,
                                        fclaw2d_patch_t *coarse_patch,
                                        fclaw2d_patch_t *fine_patch,
                                        int idir,
                                        int iside,
                                        int p4est_refineFactor,
                                        int refratio,
                                        fclaw_bool a_time_interp,
                                        int igrid,
                                        fclaw2d_transform_data_t* transform_data);



void fclaw2d_clawpatch_copy_corner(fclaw2d_domain_t *domain,
                                     fclaw2d_patch_t *this_patch,
                                     fclaw2d_patch_t *corner_patch,
                                     int icorner,
                                     int time_interp,
                                     fclaw2d_transform_data_t *transform_data);

void fclaw2d_clawpatch_average_corner(fclaw2d_domain_t *domain,
                                      fclaw2d_patch_t *coarse_patch,
                                      fclaw2d_patch_t *fine_patch,
                                      int coarse_corner,
                                      int refratio,
                                      fclaw_bool time_interp,
                                      fclaw2d_transform_data_t* transform_data);

void fclaw2d_clawpatch_interpolate_corner(fclaw2d_domain_t* domain,
                                          fclaw2d_patch_t* coarse_patch,
                                          fclaw2d_patch_t* fine_patch,
                                          int coarse_corner,
                                          int refratio,
                                          fclaw_bool a_time_interp,
                                          fclaw2d_transform_data_t* transform_data);



#ifdef __cplusplus
#if 0
{                               /* need this because indent is dumb */
#endif
}
#endif

#endif /* !FCLAW2D_CLAWPATCH_H */
