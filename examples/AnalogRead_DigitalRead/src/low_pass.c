#include "low_pass.h"

// Function to initialize a filter.
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
  y = filter->alpha*x + (1 - filter->alpha) * filter->y1;
  filter->y1 = y;
  return y;
}
