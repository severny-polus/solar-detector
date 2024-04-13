PROJECT=solar-detector
PICO=/run/media/${USER}/RPI-RP21

build: src/*
	rm -rf build
	mkdir build

	PICO_SDK_PATH=/usr/share/pico-sdk cmake -S . -B build

	$(MAKE) -C build ${PROJECT} -j4

boot: build
	sudo cp build/${PROJECT}.uf2 ${PICO}
	sudo sync
