//	Copyright 2011 Johns Hopkins University
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.


#include <stdio.h>
#include <float.h>
#include <math.h>
#include "turblib.h"
#include <time.h>
#include <pthread.h>
/*
 * Requesting entire snapshots of isotropic turbulence
 */


int main(int argc, char *argv[]) {

	char * authtoken = "edu.arizona.math.cmhyett-92e5a8a6";
	char * dataset = "isotropic1024coarse";
	enum TemporalInterpolation temporalInterp = NoTInt;
        enum SpatialInterpolation spatialInterp = NoSInt;
        
	float t = 0.3F;

	float dx = 2.0f * 3.14159265f / 1024.0f;
        float filter_width = 1*dx;
        
        long int windowSize = 32; /* we're pulling 32x32x32 cutouts at a time */
        long int N = (int) windowSize*windowSize*windowSize;
        
	float points[N][3];    /* input of x,y,z */
	float result[N][4];

        unsigned int xStart, yStart, zStart;
        
        time_t tStart;
        time_t tEnd;

        FILE *pOutputFile; 
	/*
	If selecting a dataset without time evolution (e.g. isotropic4096), certain getFunctions such as getPosition do not work.
	*/

        for (xStart = 0; xStart < (1024-windowSize); xStart += windowSize) {
          /* Initialize gSOAP */
          soapinit();

          /* Enable exit on error.  See README for details. */
          turblibSetExitOnError(1);

          for (yStart = 0; yStart < (1024-windowSize); yStart += windowSize) {
            for (zStart = 0; zStart < (1024-windowSize); zStart += windowSize) {

              long int i, j, k;
        
              for (i = 0; i < windowSize; i++) {
                for (j = 0; j < windowSize; j++) {
                  for (k = 0; k < windowSize; k++) {
                    int iInd = (i*windowSize*windowSize);
                    int jInd = (j*windowSize);
                    points[iInd+jInd+k][0] = (float) i*filter_width;
                    points[iInd+jInd+k][1] = (float) j*filter_width;
                    points[iInd+jInd+k][2] = (float) k*filter_width;
                  }
                }
              }

              tStart = time(NULL);

              printf("\nRequesting velocity and pressure at %ld points...\n", N);
              getVelocityAndPressure(authtoken, dataset, t, spatialInterp, temporalInterp, N, points, result);

              tEnd = time(NULL);

              printf("Time of execution in minutes = %e\n", (tEnd - tStart)/60.0);
              printf("xStart = %d, yStart = %d, zStart = %d\n", xStart, yStart, zStart);

              /* incrementally store results */
              if ( (pOutputFile = fopen("isotropicTurbSnapshot_1024Coarse_t0.bin", "a")) == NULL) {
                printf("Could not open output file!\n");
                exit(1);
              }
              fwrite(result, sizeof(result), (size_t) 4*N, pOutputFile);
              fclose(pOutputFile);
            }
          }
          /* Free gSOAP resources */
          soapdestroy();
        }

	return 0;
}
