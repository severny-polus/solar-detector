#include "detector.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 32

int main(int argc, char **argv)
{
  char *uart_path = argv[1];

  struct UART *uart = malloc(sizeof(UART));
  if (uart_open(uart, uart_path) != 0)
  {
    return -1;
  }
  printf("найдено устройство: %s\n", uart_path);

  char buffer[BUFFER_SIZE] = {0};
  while (1)
  {
    int n = uart_read(uart, buffer, BUFFER_SIZE);

    printf("n = %d: ", n);
    if (n == 20)
    {
      float *values = (float *)buffer;
      for (int i = 0; i < n / sizeof(float); ++i)
      {
        printf("%.3f ", values[i]);
      }
    }
    else
    {
      printf("reject");
    }
    printf("\n");

    sleep(1);
  }

  return 0;
}