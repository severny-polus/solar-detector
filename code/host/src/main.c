#include "detector.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PERIOD 100
#define RADS_TO_ANGLES (180.0 / 3.141592654)

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

  float max[5] = {0};

  while (1)
  {
    float phi, theta;
    if (detector_read_angles(detector, &phi, &theta) == -1)
    {
      printf("соединение потеряно\n");
      return -1;
    }

    printf("phi = %.3f, theta = %.3f", phi * RADS_TO_ANGLES,
           theta * RADS_TO_ANGLES);

    printf("\n");

    usleep(PERIOD * 1000);
  }

  return 0;
}
