// Low pass filter structure.
typedef struct lpf {
  float alpha;
  float dt;
  float tau;
  float y1;
} lpf_t;

void initLPF(lpf_t *filter, float dt, float tau, float x0);
float filterLPF(lpf_t *filter, float x);
