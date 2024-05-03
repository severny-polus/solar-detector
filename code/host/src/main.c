#include "detector.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 40
#define PERIOD 100

static float max[5] = {0};

int main(int argc, char **argv)
{
  char *uart_path = argv[1];
  if (uart_path == NULL)
  {
    printf("устройство не найдено\n");
    return -1;
  }

  UART *uart = malloc(sizeof(UART));
  if (uart_open(uart, uart_path) != 0)
  {
    return -1;
  }
  printf("найдено устройство: %s\n", uart_path);

  char buffer[BUFFER_SIZE] = {0};
  uart_read(uart, buffer, BUFFER_SIZE);
  while (1)
  {
    int n = uart_read(uart, buffer, BUFFER_SIZE);

    switch (n)
    {
    case 20:
      printf("max: ");

      float *values = (float *)buffer;
      for (int i = 0; i < n / sizeof(float); ++i)
      {
        if (values[i] > max[i])
        {
          max[i] = values[i];
        }
        printf("%.3f ", max[i]);
      }
      break;

    case 0:
      printf("соединение потеряно\n");
      return -1;

    default:
      printf("пропуск");
    }
    printf("\n");

    usleep(PERIOD * 1000);
  }

  return 0;
}
