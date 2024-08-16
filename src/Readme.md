## Code Modularization

The codebase is organized into several distinct modules, each with a specific responsibility in managing the functionality of the keyboard firmware. This modular structure enhances maintainability, scalability, and the ability to adapt the firmware for different configurations and future enhancements.

### 1. Keystroke Module

**Responsibilities:**
- The Keystroke module is responsible for scanning the keyboard matrix, which consists of rows and columns, to detect key presses.
- It periodically checks each row and column to determine if a key is pressed.
- When a key press is detected, the module places the corresponding data into the keystroke queue for other modules to consume.
- In the case of a split keyboard, where the keyboard is divided into separate parts, the Keystroke module directly communicates with the `comm_internal` module to send the key press data from one half of the keyboard to the other.

### 2. Comm_Internal Module

**Responsibilities:**
- The `comm_internal` module manages communication between different parts of a split keyboard.
- It receives data from the peripherals (i.e., the separate parts of the keyboard) and forwards this data to the `brain` module for further processing.
- Currently, `comm_internal` uses the I2C protocol for communication, but it is designed to be adaptable and may support Bluetooth in the future.

### 3. Brain Module

**Responsibilities:**
- The `brain` module is the core processing unit that reads data from the keystroke queue.
- It converts the column and row pair information from the Keystroke module into actual key values, based on a predefined key map.
- The key map used by the Brain module is defined in the configuration specific to the keyboard model.

### 4. Comm_External Module

**Responsibilities:**
- The `comm_external` module serves as the interface between the keyboard and the computer.
- It identifies the device to the computer as a keyboard and sends key press data received from the `brain` module.
- Currently, `comm_external` defines a USB keyboard HID (Human Interface Device), allowing the keyboard to communicate with the computer via USB.
- Like `comm_internal`, this module is designed with future enhancements in mind and may also support Bluetooth communication.

### Future Adaptability

The modular design of the codebase makes it easy to extend or modify the functionality of the keyboard. For instance:
- The `comm_internal` and `comm_external` modules are designed to support Bluetooth in addition to their current communication protocols.
- The modular architecture allows for easy integration of new features or modifications without affecting the entire codebase.

This modular approach ensures that the codebase remains clean, maintainable, and scalable, enabling the keyboard firmware to evolve with future hardware changes and user requirements.
