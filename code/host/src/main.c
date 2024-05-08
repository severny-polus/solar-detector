#include "detector.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PERIOD 100
#define RADS_TO_ANGLES (180.0 / 3.141592654)

static float max[5] = {0};

int main(int argc, char **argv)
{
  char *device_name = argv[1];
  if (device_name == NULL)
  {
    printf("устройство не найдено\n");
    return -1;
  }

  Detector *detector = detector_open(device_name);
  if (detector == NULL)
  {
    return -1;
  }
  printf("подключено устройство: %s\n", device_name);

  while (1)
  {
    const float *values = detector_read_values(detector);

    if (values == NULL)
    {
      printf("соединение потеряно\n");
      return -1;
    }

    for (size_t i = 0; i < 5; ++i)
    {
      printf("%.3f ", values[i]);
    }

    printf("| ");

    float phi, theta;
    values_to_angles(values, &phi, &theta);
    printf("phi = %.3f, theta = %.3f", phi * RADS_TO_ANGLES, theta * RADS_TO_ANGLES);

    printf("\n");

    usleep(PERIOD * 1000);
  }

  return 0;
}
