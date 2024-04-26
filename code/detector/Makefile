BUILD_DIR=Build
PROJECT=detector


$(BUILD_DIR)/$(PROJECT).elf: Core/Src/*
	cmake -S . -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)


$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf
	arm-none-eabi-objcopy -O binary $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).bin


boot: $(BUILD_DIR)/$(PROJECT).bin
	st-flash write $(BUILD_DIR)/$(PROJECT).bin 0x08000000
	st-flash reset
