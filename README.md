# Pico I2C Device Library

The Pico I2C Device Library provides a straightforward interface for communicating with I2C devices using the Raspberry Pi Pico. It supports both read and write operations on I2C devices, making it easy to interface with a wide range of I2C-enabled components.

## Features

	•	Initialize I2C communication with configurable baud rate and GPIO pins.
	•	Perform read and write operations to interact with I2C devices.
	•	Supports flexible buffer sizes for I2C transactions.

## Installation

### Git

Add the Pico I2C Device Library as a submodule in your project.

```shell
git submodule add https://github.com/julienfdev/pico-i2c-device.git lib/pico-i2c-device
```

### CMake

Modify your CMakeLists.txt to include the Pico I2C Device Library.

-  After the `pico_sdk_init` call
`add_subdirectory(lib/pico-i2c-device)`

-  Add the library to your project
`target_link_libraries(your_project pico_i2c_device)`

## Usage

### Initialization

To use the I2C Device library, create an instance of the I2CDevice class by specifying the I2C address, I2C interface, baud rate, and the GPIO pins for SDA and SCL. Only the first parameter is required, and the rest have default values: `i2c0`, `100000` and `{4, 5}`.

```c++
#include "i2c_device.h"

int main() {
// I2C address 0x68, default I2C0, default baudrate 100000, pins 4 (SDA) and 5 (SCL)
I2CDevice device(0x68); 
return 0;
}
```


### Writing Data to a Register

To write data to a specific register of the I2C device, use the write method.
```c++
uint8_t data[2] = { 0x01, 0x02 };
device.write(0x10, data, 2); // Write 2 bytes to register 0x10
```

### Reading Data from a Register

To read data from a specific register of the I2C device, use the read method.

```c++
uint8_t result[4];
device.read(0x20, result, 4); // Read 4 bytes from register 0x20
```

### Customizing I2C Pins and Baudrate

You can customize the I2C pins and baud rate when creating an instance of the I2CDevice class. Please check the pinout diagram 
to make sure the selected pins are valid for I2C communication based on the interface you provided (or i2c0 by default).

```c++
I2CPins custom_pins = { 8, 9 }; // SDA = GPIO 8, SCL = GPIO 9
I2CDevice custom_device(0x68, i2c0, 400000, custom_pins); // I2C0, 400kHz baudrate, custom pins
```

### License

This project is licensed under the MIT License. See the LICENSE file for more details.