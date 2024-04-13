# Датчик солнца

## Подключение и сборка

При простом подключении платы к питанию, она начинает выполнять код, загруженный в неё ранее. Чтобы обновить код платы, необходимо проделать следующие шаги.

### Под Linux

1. Подключить плату к компьютеру, зажав кнопку `BOOTSEL`. Это откроет режим загрузки кода.

2. Открыть папку проекта в редакторе или командной строке.
3. Отредактировать `Makefile`, установив в переменную `PICO` путь монтирования платы. Она будет использоваться при сборке.
    > Если плата не смотнирована, смонтировать её командой `mount` и затем установить.
    ```
    PICO=<путь монтирования>
    ```
4. Выполнить:
    ```
    make boot
    ```
    Эта команда автоматически соберёт и загрузит код в плату. После этого плата перейдёт в режим питания.
