#include "detector.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

typedef struct termios termios;

int uart_open(UART *uart, char *device_name)
{
  char device_path[20];
  sprintf(device_path, "/dev/%s", device_name);
  uart->fd = open(device_path, O_RDWR | O_NONBLOCK);
  if (uart->fd < 0)
  {
    printf("не удалось открыть устройство: %s\n", device_name);
    return -1;
  }

  termios settings;
  if (tcgetattr(uart->fd, &settings) != 0)
  {
    printf("не удалось получить настройки для устройства: %s\n", device_name);
    return -1;
  }
  cfsetispeed(&settings, B115200);
  cfsetospeed(&settings, B115200);
  cfmakeraw(&settings);
  if (tcsetattr(uart->fd, TCSANOW, &settings) != 0)
  {
    printf("не удалось применить настройки для устройства: %s\n", device_name);
    return -1;
  }

  return 0;
}

size_t uart_read(UART *uart, char *buffer, size_t size)
{
  return read(uart->fd, buffer, size);
}