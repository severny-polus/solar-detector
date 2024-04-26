#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

typedef struct termios termios;

// Source: https://programmersought.com/article/83564621437

int set_uart_settings(int fd)
{
  termios settings;
  if (tcgetattr(fd, &settings) != 0)
  {
    printf("failed to get port attributes\n");
    return -1;
  }
  cfsetispeed(&settings, B115200);
  cfsetospeed(&settings, B115200);
  cfmakeraw(&settings);
  if (tcsetattr(fd, TCSANOW, &settings) != 0)
  {
    printf("failed to set port attributes\n");
    return -1;
  }
}

int main()
{
  char *uart = "/dev/ttyUSB1"; // todo: вынести в аргументы

  int fd = open(uart, O_RDWR | O_NONBLOCK);
  if (fd < 0)
  {
    printf("failed to open %s\n", uart);
    return -1;
  }
  if (set_uart_settings(fd) != 0)
  {
    return -1;
  }

  char buffer[256] = {0};
  while (1) {
    size_t n = read(fd, buffer, 256);
    printf("%.*s", n, buffer);
    sleep(1);
  }

  return 0;
}