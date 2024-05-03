all: detector host


detector:
	$(MAKE) -C code/detector


host: 
	$(MAKE) -C code/host
	