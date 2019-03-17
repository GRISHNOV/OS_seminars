#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

#define STEP 0.00001
#define STEP_ITERATION 2000000000

double f(double x)
{
  return (1 / ((x + 1) * sqrt(x)));
}

int main()
{

  //printf("%li\n", sizeof(double));
  //double *x = (double *)malloc(30000000 * sizeof(double));
  //double *y = (double *)malloc(60000000 * sizeof(double));
  //double step = 0.00001;
  double step = STEP;
  //x[0] = 0.00001;
  double x_i = step;
  double y_i = f(x_i);
  double y_i_old;
  //y[0] = f(x_i);
  double S = 0;
  for (int i = 1; i < STEP_ITERATION; i++)
  {
    //x[i] = x[i - 1] + step;
    x_i = x_i + step;
    //y[i] = f(x_i);
    y_i_old = y_i;
    y_i = f(x_i);
    //S = S + y_i * step;
    S = S + (y_i + y_i_old) * step * 0.5;
    //printf("%.20f  < < <  %.20f\n", x[i],y[i]);
  }
  printf("%f\n", S);
  printf("%f <i_last> with %f <step>\n", x_i, step);

  // for (int i = 0; i < 10; i++)
  // {
  //   printf("%.20f\n" /*, x[i]*/, y[i]);
  // }
  // printf("\n\n");
  // for (int i = 10000000 - 10; i < 10000000; i++)
  // {
  //   printf("%.20f\n", /*x[i]*/ y[i]);
  // }

  //sleep(10);
  return 0;
}