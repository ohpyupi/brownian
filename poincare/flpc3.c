#include <stdio.h>
#include <gsl/gsl_errno.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>

/*PRL FLACH et al.*/
/* d2y/dt2 + r*dy/dt + cos(y) + v*cos(2*y+0.4) + E1*sin(wt) +E2*sin(2*w*t+a) = 0 */
/*figure (3) r=0, v=0.6, w=2.4, E1=-2.3, E2=-1.38, a=0.7 */

/*Multiple parameteres to be defined withen structure parameters*/

typedef struct par {
    double w;
    double r;
    double v;
    double E1;
    double E2;
    double a;
};

/*Defintion of the differential equation above*/

int func (double t, const double y[], double f[], void *params)
{

	struct par p  = *(struct par *)params;

	f[0] = y[1];
	f[1] = -cos(y[0]) -p.v*cos(2*y[0]+0.4) -p.E1*sin(p.w*t) - p.E2*sin(2*p.w*t+p.a);
	return GSL_SUCCESS;
}

/*Definition of the Jacobian, corresponding to the equation above*/

int jac (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
    struct par p = *(struct par *)params;
	gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, 2, 2);
	gsl_matrix * m = &dfdy_mat.matrix;
	gsl_matrix_set (m, 0, 0, 0.0);
	gsl_matrix_set (m, 0, 1, 1.0);
	gsl_matrix_set (m, 1, 0, sin(y[0]) + 2*p.v*sin(2*y[0]+0.4));
	gsl_matrix_set (m, 1, 1, 0.0);
	dfdt[0] = 0.0;
	dfdt[1] = -p.E1*p.w*cos(p.w*t) - 2*p.w*p.E2*cos(2*p.w*t+p.a);
	return GSL_SUCCESS;

}

/*Main procedure of ODEIV*/

int 
main (void)
{
	int i, j, k;

  struct par params;
  params.w = 2.4;
  params.r = 0;
  params.v = 0.6;
  params.E1 = -2.3;
  params.E2 = -1.38;
  params.a = 0.7;

	double dt = 2*M_PI/params.w;
  int nsteps = 1e5/dt;
		
	for (j = 0; j < 21; j++)
	{
		for (k = 0; k < 11; k ++)
		{
			gsl_odeiv2_system sys = {func, jac, 2, &params};
	
			gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_bsimp, 1e-3, 1e-3, 1e-3);

			double t = 0.0;

			double yj = -3.140 +  0.314*j; 
			double dyk = -0.005 + 0.001*k;
			double y[2] = {yj, dyk};

			for (i = 1 ; i<=nsteps; i++)
			{
				double ti = i*dt;
				int status = gsl_odeiv2_driver_apply (d, &t, ti, y);

				if (status != GSL_SUCCESS)
					{
						printf("error, return value%d\n", status);
						break;
					}
				printf("%.5e %.5e %.5e %.5e\n", t, y[0], y[1], fmod(y[0],(2*M_PI)));
			}

			gsl_odeiv2_driver_free (d);
		}
	}
	return 0;
}
