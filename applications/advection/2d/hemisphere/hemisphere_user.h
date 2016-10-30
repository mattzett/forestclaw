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

#ifndef HEMISPHERE_USER_H
#define HEMISPHERE_USER_H

#include <fclaw2d_clawpatch.h>
#include <fc2d_clawpack46.h>
#include <fc2d_clawpack5.h>

#include "../all/clawpack_user.h"


#ifdef __cplusplus
extern "C"
{
#if 0
}
#endif
#endif


typedef struct user_options
{
    int example;
    int claw_version;
    double alpha;
    int is_registered;

} user_options_t;


#if 0

#define HEMISPHERE46_SETAUX_MANIFOLD FCLAW_F77_FUNC(hemisphere46_setaux_manifold,   \
                                                    HEMISPHERE46_SETAUX_MANIFOLD)
void HEMISPHERE46_SETAUX_MANIFOLD(const int* mbc, const int* mx, const int* my,
                                  const double* xlower, const double* ylower,
                                  const double* dx, const double* dy,
                                  const int* maux, double aux[],
                                  const int* blockno,
                                  double xd[], double yd[], double zd[],
                                  double area[]);



#define USER46_SETAUX_MANIFOLD FCLAW_F77_FUNC(user46_setaux_manifold,   \
                                              USER46_SETAUX_MANIFOLD)
void USER46_SETAUX_MANIFOLD(const int* mbc, const int* mx, const int* my,
                                  const double* xlower, const double* ylower,
                                  const double* dx, const double* dy,
                                  const int* maux, double aux[],
                                  const int* blockno,
                                  double xd[], double yd[], double zd[],
                                  double area[]);


#define USER5_SETAUX_MANIFOLD FCLAW_F77_FUNC(user5_setaux_manifold,     \
                                             USER5_SETAUX_MANIFOLD)
void USER5_SETAUX_MANIFOLD(const int* mbc, const int* mx, const int* my,
                                  const double* xlower, const double* ylower,
                                  const double* dx, const double* dy,
                                  const int* maux, double aux[],
                                  const int* blockno,
                                  double xd[], double yd[], double zd[],
                                  double area[]);
#endif

void hemisphere_link_solvers(fclaw2d_domain_t *domain);

const user_options_t* hemisphere_user_get_options(fclaw2d_domain_t* domain);


void hemisphere_patch_setup(fclaw2d_domain_t *domain,
                            fclaw2d_patch_t *this_patch,
                            int this_block_idx,
                            int this_patch_idx);

fclaw2d_map_context_t* fclaw2d_map_new_pillowsphere(const double scale[],
                                                    const double shift[],
                                                    const double rotate[]);

fclaw2d_map_context_t* fclaw2d_map_new_pillowsphere5(const double scale[],
                                                     const double shift[],
                                                     const double rotate[],
                                                     const double alpha);


#ifdef __cplusplus
#if 0
{
#endif
}
#endif

#endif
