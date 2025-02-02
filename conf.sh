export LIBS=""
export FCLAW=~/Projects/forestclaw
export FCLAW_BIN=$FCLAW/local/bin

./configure \
    --enable-mpi \
    --enable-clawpack \
    --disable-shared \
    --without-blas \
    F77="mpifort" \
    CC="mpicc" \
    CXX="mpicxx" \
#    LDFLAGS="-lgfortran"
#    CFLAGS="-Wall -O3 -DFCLAW2D_PATCHDIM=2 -DFCLAW2D_REFINEDIM=2" \
#    CXXFLAGS="-O3 -Wall -DFCLAW2D_PATCHDIM=2 -DFCLAW2D_REFINEDIM=2" \
#     FFLAGS=-lgfortran
#    FFLAGS="-fast -assume buffered_io" 
#    LIBS="-lmkl_intel_lp64 -lmkl_core -lmkl_sequential"
#    --enable-clawpack \
