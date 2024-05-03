#include <stddef.h>

typedef struct UART
{
  int fd;
} UART;

int uart_open(UART *uart, char *device_name);
size_t uart_read(UART *uart, char *buffer, size_t size);
