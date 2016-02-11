#include <stdio.h>
#include <stdlib.h>

int main () 
{
	FILE *ifp, *ofp1, *ofp2;
	char outputFilename1[] = "pflight.dat";
	char outputFilename2[] = "nflight.dat";

	int k;
	float t, y, dy;
	double tmax = 1e9;
	double *A = (double *) malloc(tmax*sizeof(double));

	ifp = fopen("fl2.dat", "r");

	if (ifp == NULL)
	{
		fprintf(stderr, "Can't open input file in.list!\n");
		exit(1);
	};

	ofp1 = fopen(outputFilename1, "w");

	if (ofp1 == NULL)
	{
		fprintf(stderr, "Can't open output file 1 %s!\n", outputFilename1);
		exit(1);
	};

	ofp2 = fopen(outputFilename2, "w");

	if (ofp2 == NULL)
	{
		fprintf(stderr, "Can't open output file2 %s!\n", outputFilename2);
		exit(1);
	};


	for (k = 0; k < (int) tmax ; k++)
	{
		fscanf(ifp, "%e %e %e", &t, &y, &dy);
		A[k] = (double) y;
	}	

	double iflight = A[1] - A[0];
	int ijump, oldjump, newjump;

	if (iflight > 0.000)
	{
		ijump = 1;
	}
	else if (iflight < 0.000) 
	{
		ijump = -1;	
	}

	float ftime = 0;
	oldjump = ijump;
	int totflight = (int) tmax - 1;

	for (k = 0; k < totflight; k++)
	{
		double flight = A[k+1] - A[k];

		if (flight > 0)
		{
			newjump = 1;
		}
		else if (flight < 0)
		{
			newjump = -1;
		}
		
		if (newjump == oldjump)
		{
			ftime = ftime + 1;
		} 
		else
		{
			if (oldjump == 1)
			{
				fprintf(ofp1, "%f\n", ftime);
				ftime = 1;
				oldjump = -1;
			}
			else if (oldjump == -1)
			{
 				fprintf(ofp2, "%f\n", ftime);
				ftime = 1;
				oldjump = 1;
			}
		}	

		if (k == totflight - 1)
		{
			if (oldjump == 1)
			{
				fprintf(ofp1, "%f\n", ftime);
			}
			else
			{
				fprintf(ofp2, "%f\n", ftime);
			}
		} 		

	}
	
	free(A);

/*	
	for (k = 0; k < 9; k++)
	{
		printf("%e\n", A[k+1] - A[k]);
	}
*/

	fclose(ifp);
	fclose(ofp1);
	fclose(ofp2);
	return 0;
}
