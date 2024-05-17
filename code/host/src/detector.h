#include <stddef.h>

typedef struct Detector
{
  int fd;
  float *values;
} Detector;

Detector *detector_open(char *device_name);

const float *detector_read_values(Detector *d);
int detector_read_angles(Detector *d, float *phi, float *theta);

void values_to_angles(const float *values, float *phi, float *theta);
void update_max(float *max, const float *values);
