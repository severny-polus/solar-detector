#include <stddef.h>

typedef struct Detector
{
  int fd;
  float *values;
} Detector;

Detector *detector_open(char *device_name);
void values_to_angles(const float *values, float *phi, float *theta);
const float *detector_read_values(Detector *d);
void detector_read_angles(Detector *d, float *phi, float *theta);
