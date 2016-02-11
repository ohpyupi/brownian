#include <stdio.h>
#include <stdlib.h>
#include <gsl/gsl_errno.h>
#include <math.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_statistics.h>


typedef struct par 
{
	double w; 
	double r;
	double v;
	double E1;
	double E2;
	double a;
};

int func (double t, const double y[], double f[2], void *params)
{
	struct par p = *(struct par *)params;

	f[0] = y[1];
	f[1] = -cos(y[0]) -p.v*cos(2*y[0]+0.4) -p.E1*sin(p.w*t) - p.E2*sin(2*p.w*t+p.a);
  return GSL_SUCCESS;
}

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

int main(void)
{
	struct par params;
	params.w = 2.4;
	params.r = 0;
	params.v = 0.6;
	params.E1 = -2.3;
	params.E2 = -1.38;
	params.a = 0.7;

	
  int i,j,k;
	double const  y_i = -3.14, dydt_i = -0.005;
	double n = 21, m = 11;
	double tmax = 1e7;

	double *A = (double *) malloc (tmax*sizeof(double));
	double *C = (double *) malloc (tmax*sizeof(double)); 
	double *D = (double *) malloc (tmax*sizeof(double));
	double *V = (double *) malloc (tmax*sizeof(double));

	if (A==NULL)
	{
		printf("Error allocating memory!\n");
		return 1;
	}
	
	if (C==NULL)
	{
		printf("Error allocating memory!\n");
		return 1;
	}

	if (D==NULL)
	{
		printf("Error allocating memory!\n");
		return 1;
	}
	if (V==NULL)
	{
		printf("Error allocating memory!\n");
		return 1;
	}


	for (j=0; j < n; j++)
	{
		for (k=0; k < m; k++)
		{
		double y_j = y_i + 0.314*j;	
		double dydt_j = dydt_i + 0.001*k;
		double t = 0.0;
			
		double y[2] = {y_j, dydt_j};
	
		gsl_odeiv2_system sys = {func, jac, 2, &params};
		gsl_odeiv2_driver * d = gsl_odeiv2_driver_alloc_y_new (&sys, gsl_odeiv2_step_bsimp, 1e-3, 1e-6, 1e-6);

		for (i=0; i < tmax; i++)
		{
			double ti =  i;
			int status = gsl_odeiv2_driver_apply (d, &t, ti, y);
		
			if (status != GSL_SUCCESS)
			{
				printf("error, return value%d\n", status);
				break;
			}
			
			A[i] = A[i] + (y[0])/(n*m);
			C[i] = C[i] + (y[0]*y[0])/(n*m);
		}	
		gsl_odeiv2_driver_free (d);
		}
	}

		for (k=0; k < tmax; k++)
		{

			D[k] = A[k] * A[k];
			V[k] = C[k] - D[k];

			printf("%e %e %e\n",(double) k, A[k], V[k]);
		}
		free(A);
		free(C);
		free(D);
		free(V);

	return 0;
}
