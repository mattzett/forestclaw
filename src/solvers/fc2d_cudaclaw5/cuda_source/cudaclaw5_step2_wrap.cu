#include "../fc2d_cudaclaw5.h"
#include "../fc2d_cudaclaw5_fort.h"
#include "../fc2d_cudaclaw5_options.h"
#include "cudaclaw5_update_q.h"

double cudaclaw5_step2_wrap(fclaw2d_global_t *glob,
                            fclaw2d_patch_t *this_patch,
                            int this_block_idx,
                            int this_patch_idx,
                            double t,
                            double dt)
{
    fc2d_cudaclaw5_vtable_t*  cuclaw5_vt = fc2d_cudaclaw5_vt();
    fc2d_cudaclaw5_options_t* cudaclaw_options;
    int level;
    double *qold, *aux;
    int mx, my, meqn, maux, mbc;
    double xlower, ylower, dx,dy;

    FCLAW_ASSERT(cuclaw5_vt->fort_rpn2 != NULL);
    FCLAW_ASSERT(cuclaw5_vt->fort_rpt2 != NULL);

    cudaclaw_options = fc2d_cudaclaw5_get_options(glob);
    level = this_patch->level;

    fclaw2d_clawpatch_aux_data(glob,this_patch,&aux,&maux);
    fclaw2d_clawpatch_save_current_step(glob, this_patch);
    fclaw2d_clawpatch_grid_data(glob,this_patch,&mx,&my,&mbc,
                                &xlower,&ylower,&dx,&dy);
    fclaw2d_clawpatch_soln_data(glob,this_patch,&qold,&meqn);

    int mwaves = cudaclaw_options->mwaves;
    int maxm = fmax(mx,my);
    double cflgrid = 0.0;

    int mwork = (maxm+2*mbc)*(12*meqn + (meqn+1)*mwaves + 3*maux + 2);
    double* work = new double[mwork];

    int size = meqn*(mx+2*mbc)*(my+2*mbc);
    double* fp = new double[size];
    double* fm = new double[size];
    double* gp = new double[size];
    double* gm = new double[size];

    int ierror = 0;
    cudaclaw5_fort_flux2_t flux2 = CUDACLAW5_FLUX2;

    int* block_corner_count = fclaw2d_patch_block_corner_count(glob,this_patch);
    
#if 0
c     # Local variables
      integer i0faddm, i0faddp, i0gaddm, i0gaddp
      integer i0q1d, i0dtdx1, i0dtdy1
      integer i0aux1, i0aux2, i0aux3, i0next, mused, mwork1
      integer i0wave, i0s, i0amdq, i0apdq, i0ql, i0qr, i0auxl
      integer i0auxr

      integer i,j,m

c     Needed by Riemann solvers.  This should be fixed later by a 'context'
c     for a Riemann solver.
      double precision dtcom, dxcom,dycom,tcom
      integer icom, jcom
      common/comxyt/dtcom,dxcom,dycom,tcom,icom,jcom

c     # This should be set to actual time, in case the user wants it
c     # it for some reason in the Riemann solver.

c     # Set up work arrays (these are not used yet)

      i0faddm = 1
      i0faddp = i0faddm +   (maxm+2*mbc)*meqn
      i0gaddm = i0faddp +   (maxm+2*mbc)*meqn
      i0gaddp = i0gaddm + 2*(maxm+2*mbc)*meqn
      i0q1d   = i0gaddp + 2*(maxm+2*mbc)*meqn
      i0dtdx1 = i0q1d   +   (maxm+2*mbc)*meqn
      i0dtdy1 = i0dtdx1 +   (maxm+2*mbc)
      i0aux1  = i0dtdy1 +   (maxm+2*mbc)
      i0aux2  = i0aux1  +   (maxm+2*mbc)*maux
      i0aux3  = i0aux2  +   (maxm+2*mbc)*maux
c
c
      i0next  = i0aux3  + (maxm+2*mbc)*maux    !# next free space
      mused   = i0next - 1                    !# space already used
      mwork1  = mwork - mused           !# remaining space (passed to step2)

      if (mused.gt.mwork) then
         ierror = 1
         return
      endifid need for
c     # global array
c      call cudaclaw5_step2(maxm,maxmx,maxmy,meqn,maux, mbc,
c     &      mx,my, qold,aux,dx,dy,dt,
c     &      cfl,fm,fp,gm,gp,
c     &      work(i0faddm),work(i0faddp),
c     &      work(i0gaddm),work(i0gaddp),
c     &      work(i0q1d),work(i0dtdx1),work(i0dtdy1),
c     &      work(i0aux1),work(i0aux2),work(i0aux3),
c     &      work(i0next),mwork1,rpn2,rpt2,flux2,
c     &      mwaves,mcapa,method,mthlim,block_corner_count,ierror)
#endif

    CUDACLAW5_STEP2(&maxm,&meqn,&maux,&mbc,&mx,&my,qold,aux,
                    &dx,&dy,&dt,&cflgrid,fm,fp,gm,gp,cuclaw5_vt->fort_rpn2,
                    cuclaw5_vt->fort_rpt2,block_corner_count,&ierror);

    /* # update q */
    double dtdx, dtdy;
    dtdx = dt/dx;
    dtdy = dt/dy;
#if 1
    CUDACLAW5_FORT_UPDATE_Q(&meqn,&mx,&my,&mbc,&maux,
                            &dtdx,&dtdy,qold,fp,fm,
                            gp,gm,&cudaclaw_options->mcapa);
#else
    cudaclaw5_update_q(meqn,mx,my,mbc,dtdx,dtdy,qold,
                       fm,fp,gm,fp,mcapa);
#endif
    FCLAW_ASSERT(ierror == 0);

    delete [] fp;
    delete [] fm;
    delete [] gp;
    delete [] gm;
    delete [] work;

    return cflgrid;
}
