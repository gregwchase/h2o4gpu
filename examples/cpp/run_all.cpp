#include <cstdio>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include "examples.h"
#include "reader.h"
#include "timer.h"

typedef float real_t;

int main(int argc, char **argv) {
  using namespace std;
  double t;

  size_t rows=0, cols=0;
  /*
  printf("\nLogistic Regression.\n");
  t = Logistic<real_t>(7000, 100000);
  printf("Solver Time: %e sec\n", t);
  */

  //  int rows=450016; // BARELY succeeds in 2000 iterations with cols=213 and no adpative rho.  Fails with adaptive rho.  No big changes with Eq constant changes.

  //int rows=5000;
  //  int rows=450000; // testing, succeeds with adaptive rho, but fails without adaptive rho
  //  int rows=450020; // testing, fails with or without adaptive rho

  
  //  int  rows=450000; // fails without adaptive rho, works perfectly fine with adaptive rho.
  //  int rows=450050;
  //  int cols=212;

  //  extern int bwcheck(void);
  //  bwcheck();
  //  return(0);

  if (argc!=7) {
    printf("usage: %s %s", argv[0], " <nGPUs> <nLambdas> <nAlphas> <intercept?1:0> <standardize?1:0> <validFraction>\n");
    exit(-1);
  }

  int nGPUs=atoi(argv[1]);
  int nLambdas=atoi(argv[2]);
  int nAlphas=atoi(argv[3]);
  int intercept=atoi(argv[4]);
  int standardize=atoi(argv[5]);
  double validationFraction=atof(argv[6]);

  std::vector<real_t> A;
  std::vector<real_t> b;
  cout << "START FILL DATA\n" << endl;
  double t0 = timer<double>();
  fillData(rows,cols,"train.txt", A, b);
  double t1 = timer<double>();
  cout << "END FILL DATA. Took " << t1 - t0 << " secs" << endl;

  /*
  printf("\nLasso: rows=%d n=%d.\n",rows,n);
  t = Lasso<real_t>(rows, n);
  printf("Lasso rows=%d n=%d Solver Time: %e sec\n", rows,n,t);
  */


  printf("\nElastic Net: rows=%d cols=%d ngpus=%d nlambdas=%d nalphas=%d intercept=%d standardize=%d validFraction=%g\n",rows,cols,nGPUs,nLambdas,nAlphas,intercept,standardize,validationFraction);
  t = ElasticNet<real_t>(A, b, nGPUs, nLambdas, nAlphas, intercept, standardize, validationFraction);
  printf("\nElastic Net: rows=%d cols=%d ngpus=%d nlambdas=%d nalphas=%d intercept=%d standardize=%d validFraction=%g time=%e secs\n",rows,cols,nGPUs,nLambdas,nAlphas,intercept,standardize,validationFraction,t);

  fflush(stdout);
  fflush(stderr);
  

  /*
  printf("\nLinear Program in Equality Form.\n");
  t = LpEq<real_t>(1000, 200);
  printf("Solver Time: %e sec\n", t);

  printf("\nLinear Program in Inequality Form.\n");
  t = LpIneq<real_t>(1000, 200);
  printf("Solver Time: %e sec\n", t);

  printf("\nNon-Negative Least Squares.\n");
  t = NonNegL2<real_t>(1000, 200);
  printf("Solver Time: %e sec\n", t);

  printf("\nSupport Vector Machine.\n");
  t = Svm<real_t>(1000, 200);
  printf("Solver Time: %e sec\n", t);
*/

  return 0;
}

