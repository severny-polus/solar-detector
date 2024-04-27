#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#define BUFFER_SIZE 32

typedef struct termios termios;

typedef struct
{
  int fd;
} UART;

int uart_open(UART *uart, const char *path)
{
  uart->fd = open(path, O_RDWR | O_NONBLOCK);
  if (uart->fd < 0)
  {
    printf("failed to open file: %s\n", path);
    return -1;
  }

  termios settings;
  if (tcgetattr(uart->fd, &settings) != 0)
  {
    printf("failed to get tty settings\n");
    return -1;
  }
  cfsetispeed(&settings, B115200);
  cfsetospeed(&settings, B115200);
  cfmakeraw(&settings);
  if (tcsetattr(uart->fd, TCSANOW, &settings) != 0)
  {
    printf("failed to set tty settings\n");
    return -1;
  }

  return 0;
}

size_t uart_read(UART *uart, char *buffer, size_t size)
{
  return read(uart->fd, buffer, size);
}

int main()
{
  UART *uart = malloc(sizeof(UART));
  const char *uart_path = "/dev/ttyUSB1"; // todo: вынести в аргументы

  if (uart_open(uart, uart_path) != 0)
  {
    return -1;
  }

  char buffer[BUFFER_SIZE] = {0};
  while (1)
  {
    int n = uart_read(uart, buffer, BUFFER_SIZE);

    printf("n = %d: ", n);
    if (n == 20)
    {
      float *values = buffer;
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