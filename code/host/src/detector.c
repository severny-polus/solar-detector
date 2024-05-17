#include "detector.h"
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

typedef struct termios Termios;

#define NUM_ADC_CHANNELS 5
#define MAX_VALUES (2 * NUM_ADC_CHANNELS)
#define BUFFER_SIZE (MAX_VALUES * sizeof(float))

Detector *detector_new()
{
  Detector *d = malloc(sizeof(Detector));
  memset(d, 0, sizeof(Detector));
  d->values = calloc(MAX_VALUES, sizeof(float));
  return d;
}

// Открывает UART-канал к прибору, указанному в параметре.
//
// device_name должен быть строкой вида "ttyUSBX"
Detector *detector_open(char *device_name)
{
  Detector *d = detector_new();

  char device_path[20];
  sprintf(device_path, "/dev/%s", device_name);
  d->fd = open(device_path, O_RDWR | O_NONBLOCK);
  if (d->fd < 0)
  {
    printf("не удалось открыть устройство: %s\n", device_name);
    return NULL;
  }

  Termios settings;
  if (tcgetattr(d->fd, &settings) != 0)
  {
    printf("не удалось получить настройки для устройства: %s\n", device_name);
    return NULL;
  }
  cfsetispeed(&settings, B115200);
  cfsetospeed(&settings, B115200);
  cfmakeraw(&settings);
  if (tcsetattr(d->fd, TCSANOW, &settings) != 0)
  {
    printf("не удалось применить настройки для устройства: %s\n", device_name);
    return NULL;
  }

  return d;
}

// Конвертация значений фотодиодов в углы.
// Зависит от расположения фотодиодов на плате.
void values_to_angles(const float *values, float *phi, float *theta)
{
  double y = values[2] - values[0];
  double x = -values[3]; // TODO: Заменить фотодиод
  double z = values[4];

  double r = sqrt(x * x + y * y);

  *phi = (float)atan2(y, x);
  *theta = (float)atan2(r, z);
}

// Снятие значений с фотодиодов. Возвращает массив из 5 чисел типа float.
const float *detector_read_values(Detector *d)
{
  size_t n = read(d->fd, (char *)d->values, BUFFER_SIZE);

  while (n != NUM_ADC_CHANNELS * sizeof(float))
  {
    n = read(d->fd, (char *)d->values, BUFFER_SIZE);
    if (n == 0)
    {
      return NULL;
    }
  }

  return d->values;
}

// Прочесть значения с фотодиодов и конвертировать в углы.
void detector_read_angles(Detector *d, float *phi, float *theta)
{
  detector_read_values(d);
  values_to_angles(d->values, phi, theta);
}

// Обновить максимальные значения
void update_max(float *max, const float *values)
{
  for (size_t i = 0; i < NUM_ADC_CHANNELS; ++i)
  {
    if (values[i] > max[i])
    {
      max[i] = values[i];
    }
  }
}
