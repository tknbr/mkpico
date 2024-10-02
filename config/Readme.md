## Configuration Folder Overview

The `config` folder is dedicated to holding all the configuration settings for the different parts of the project. This modular configuration structure allows for easy management and customization of various components of the firmware.

### 1. FreeRTOSConfig.h

**Purpose:**
- `FreeRTOSConfig.h` contains the configuration settings for the FreeRTOS kernel.
- It defines various parameters like task priorities, stack sizes, tick rates, and other kernel-level settings required by FreeRTOS to operate within the environment.

### 2. Compile.h

**Purpose:**
- `compile.h` contains two important defines: `PERIPHERAL` and `CONTROLLER`.
- These defines determine whether the compiled firmware image will be for the peripheral or the controller part of the keyboard.
- **Future Enhancement:** The goal is to eventually move this configuration to the Makefile so that users won't need to modify this file directly.

### 3. Task_Internal.h

**Purpose:**
- `task_internal.h` holds configuration details related to tasks within the firmware.
- This includes default sleep times, sizes of communication queues, default task priorities, and other task-specific settings that influence the behavior and performance of the system.

### 4. Tusb_Config.h

**Purpose:**
- `tusb_config.h` provides the basic configuration settings for the TinyUSB library.
- It includes settings related to USB device functionality, such as endpoint sizes, buffer sizes, and other parameters that TinyUSB requires to manage USB communication.

### 5. Keyboard-Specific Configurations

**Purpose:**
- The `config` folder also contains a subfolder for each keyboard supported by the firmware. Currently, there is one folder called `selenium_s`.
- Each keyboard-specific folder contains the following files:
  - **gpios.h:** Defines the GPIOs associated with each column and row of the keyboard matrix. This file maps the physical layout of the keyboard to the microcontroller's GPIO pins.
  - **keymap.h:** Provides the layout of the rows and columns, linking the physical keyboard matrix to the logical keymap.
  - **keymap.c:** Contains the definition of the keyboard's layout and the specific location of each key. This file is where the actual key mappings (e.g., which key corresponds to which row/column) are defined.
  - **pcb:** this folder contains the schematic and pcb files for the keyboard.

  ![selenium s pcb](../../main/img/selenium_s_pcb.png)  
  <center>Selenium s (34 keys split mechanical keyboard) pcb</center>

### Summary

The `config` folder is the backbone of the project's configuration management, encapsulating all necessary settings to customize the FreeRTOS kernel, task behaviors, USB communication, and keyboard layouts. By modularizing these settings into distinct files and folders, the project ensures that configurations are easy to manage, modify, and extend, making the firmware highly adaptable to different hardware configurations and future enhancements.
