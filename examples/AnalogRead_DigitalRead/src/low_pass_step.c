#include <stdio.h>
#include "low_pass.h"
#include <math.h>


int main(int argc, char *argv[]) {
  double dT = 0.01;

  double tau1 = 2;
  double tau2 = 1;

  double step_time = 1;
  double duration = 5 * tau1 + step_time;
  double time = 0;

  lpf_t lpf1;
  lpf_t lpf2;

  double y1;
  double y2;
  

  initLPF(&lpf1, dT, tau1, 0);
  initLPF(&lpf2, dT, tau2, 0);

  double x = 0;
  printf("Time, X, Y1 (tau=%f), Y2 (tau=%f)\n", tau1, tau2);
  for (time = 0; time < duration; time += dT) {
    if (time > step_time) {
      x = 1;
    } else {
      x = 0;
    }
    y1 = filterLPF(&lpf1, x);
    y2 = filterLPF(&lpf2, x);
    printf("%f, %f, %f, %f\n", time, x, y1, y2);
  }
  return 0;
}
