PROJECT=host
BUILD_DIR=build


$(BUILD_DIR)/$(PROJECT): src/*
	cmake -S . -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)


host: $(BUILD_DIR)/$(PROJECT)
	sudo $(BUILD_DIR)/$(PROJECT)
