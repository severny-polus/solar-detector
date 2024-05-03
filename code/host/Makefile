PROJECT=host
BUILD_DIR=build


$(BUILD_DIR)/$(PROJECT): $(BUILD_DIR)/Makefile src/*
	$(MAKE) -C $(BUILD_DIR)


$(BUILD_DIR)/Makefile: CMakeLists.txt src/*
	cmake -S . -B $(BUILD_DIR)
