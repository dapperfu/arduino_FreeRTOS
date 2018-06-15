#include <stdio.h>

// Low pass filter structure.
typedef struct lpf {
  float alpha;
  float dt;
  float tau;
  float y1;
} lpf_t;

// Function to init a filter.
void initLPF(lpf_t *filter, float dt, float tau, float x0) {
  filter->dt = dt;
  filter->tau = tau;
  filter->alpha = filter->dt / (filter->tau + filter->dt);
  filter->y1 = x0 * filter->alpha;
}

// Filter a datapoint.
// https://en.wikipedia.org/wiki/Low-pass_filter#Discrete-time_realization
float filterLPF(lpf_t *filter, float x) {
  float y;
  y = filter->alpha + (1 - filter->alpha) * filter->y1;
  filter->y1 = y;
  return y;
}

int main(int argc, char *argv[]) {
  float dT = 0.1;

  float tau1 = 1;
  float tau2 = 0.5;

  float step_time = 1;
  float duration = 5 * tau1 + step_time;
  float time = 0;

  lpf_t lpf1;
  lpf_t lpf2;

  float y1;
  float y2;

  initLPF(&lpf1, dT, tau1, 0);
  initLPF(&lpf2, dT, tau2, 0);

  float x = 0;
  printf("Time, X, Y1 (tau=%f), Y2 (tau=%f)\n",tau1, tau2);
  for (time = 0; time<duration; time+=dT) {
	  if (time>step_time) {
		  x=1;
	  } else {
		  x=0;
	  }
	  y1=filterLPF(&lpf1, x);
	  y2=filterLPF(&lpf2, x);
	  printf("%f, %f, %f, %f\n", time, x, y1, y2);
  }
  return 0;
}
