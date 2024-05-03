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

int uart_open(UART *uart, const char *path)
{
  uart->fd = open(path, O_RDWR | O_NONBLOCK);
  if (uart->fd < 0)
  {
    printf("не удалось найти устройство: %s\n", path);
    return -1;
  }

  termios settings;
  if (tcgetattr(uart->fd, &settings) != 0)
  {
    printf("не удалось получить настройки tty\n");
    return -1;
  }
  cfsetispeed(&settings, B115200);
  cfsetospeed(&settings, B115200);
  cfmakeraw(&settings);
  if (tcsetattr(uart->fd, TCSANOW, &settings) != 0)
  {
    printf("не удалось применить настройки tty\n");
    return -1;
  }

  return 0;
}

size_t uart_read(UART *uart, char *buffer, size_t size)
{
  return read(uart->fd, buffer, size);
}