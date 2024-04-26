boot:
	$(MAKE) -C code/detector boot


minicom: 
	sudo minicom -b 115200 -o -D /dev/ttyUSB0
	