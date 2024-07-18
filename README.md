### OpenAMP Virtual UART Example

This demo firmware is meant to run on a secondary core, such as the M4, on dual-core micro-controllers. It's provided for testing and verifying the Open-AMP implementation on MicroPython. The firmware opens a channel called "vuart-channel" and echoes back the data sent to it.

### Configuring and Building the Firmware

Note that this firmware needs to be built from source every time the main firmware changes, especially if OpenMV's firmware used. This is because the address of the reserved memory used by the second core, and to which its firmware is loaded, can change across firmware releases.

#### Clone the repository
To clone the repository, run the following command:
```bash
git clone https://github.com/iabdalkader/openamp_vuart
```

#### Configure the firmware

The address of the secondary core's memory, and its size, must be configured in `portable/stm32/port_config.h`. To find the address of the reserved memory and its size, `readelf` can be used on the main firmware:
```bash
arm-none-eabi-readelf -lS openmv_firmware.elf
[13] .core1_memory     NOBITS          70380000 1b2000 080000 00  WA  0   0  4
```

Set set the address of the second core's memory in `portable/stm32/port_config.h`, in `RAM_ORIGIN`, and its size in `RAM_LENGTH`. Using the example above:
```c
#define RAM_ORIGIN      0x70380000
#define RAM_LENGTH      512K
```
*Note that this step can be skipped for the MicroPython's upstream firmware, since it uses a fixed core memory location.*

#### Build the firmware
To build the firmware for STM32 micro-controllers, for example, run the following command:
```bash
cd openamp_vuart
make -j$(nproc) PORT=stm32
```
*Note that you need the ARM GNU toolchain (13 or higher) installed somewhere in the path.*
