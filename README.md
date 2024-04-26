# Датчик солнца

## Запуск программы

Чтобы запустить программу на компьютере-приёмнике, необходимо подключить датчик к питанию и присоединить UART-шнур. Далее выполнить команду

```
make host
```

## Прошивка контроллера

Для регистрации сигналов используется микроконтроллер `STM32F401CEU6`. Далее приведена инструкция по его прошивке.

### Linux

Прежде всего, скачать пакеты `gcc-arm-none-eabi` и `stlink`.

Чтобы загрузить код в плату, выполнить команду

```
make boot
```
