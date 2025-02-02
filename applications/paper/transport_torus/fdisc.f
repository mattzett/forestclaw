      double precision function  fdisc(blockno,xc,yc)
      implicit none

      double precision xc,yc, xp, yp, zp, rp
      integer blockno


      double precision pi, pi2
      common /compi/ pi, pi2

      double precision alpha, beta
      common /torus_comm/ alpha, beta

      integer example
      common /example_comm/ example  

      double precision init_radius
      common /initradius_comm/ init_radius

      double precision th, r0,x0,y0,z0,r
      double precision xc1, yc1, theta,phi

      call mapc2m_torus2(xc,yc,xp,yp,zp)

      r0 = init_radius
      if (example .eq. 0) then
          th = pi2*(0.25 + 1.d0/32.d0)
          x0 = cos(th)
          y0 = sin(th)
          z0 = alpha
      elseif (example .eq. 1) then
          xc1 = 0.5
          yc1 = 0.125
          call mapc2m_torus2(xc1,yc1,x0,y0,z0)
      else
         write(6,*) 'fdisc.f : example .gt. 1'
         stop
      endif

c     # Distance from thc
      r = sqrt((xp-x0)**2 + (yp-y0)**2 + (zp-z0)**2)      
      fdisc = r - r0 

c      call map_comp2torus(xc,yc,theta,phi)
c      fdisc = abs(theta-pi/2) - pi/8.d0

      end
