### OpenAMP Virtual UART Example

This demo firmware is meant to run on a secondary core, such as the M4, on dual-core micro-controllers. It's provided for testing and verifying the Open-AMP implementation on MicroPython. The firmware opens a channel called "vuart-channel" and echoes back the data sent to it.

### Configuring and building the firmware

Note that this firmware needs to be built from source every time the main firmware changes, especially if OpenMV's firmware used. This is because the address of the reserved memory used by the second core, and to which its firmware is loaded, can change across firmware releases.

#### Clone the repository
To clone the repository, run the following command:
```bash
git clone https://github.com/iabdalkader/openamp_vuart
```

#### Configure the firmware

*Note that this step can be skipped completely for the MicroPython's upstream firmware, since it uses a fixed shared memory region and a fixed core memory location.*

The address of the Open-AMP shared memory region and the address and size of secondary core's memory, must be configured in `portable/stm32/port_config.h`.

To find this information `readelf` can be used on the main firmware:
```bash
arm-none-eabi-readelf -lS openmv_firmware.elf
  [12] .openamp_memory   NOBITS          30030000 1bd000 010000 00  WA  0   0 32
  [13] .core1_memory     NOBITS          c0380000 1bd000 080000 00  WA  0   0 32
```
In this example, the Open-AMP shared memory region is placed at `0x30030000` and its size is `0x010000`. And the secondary core's memory is placed at `0xc0380000` and its size is `0x080000`. So the port config file, for STM32 for example, should look like the following:

```c
#define SHM_ORIGIN      0x30030000
#define SHM_LENGTH      64K

#define RAM_ORIGIN      0x70380000
#define RAM_LENGTH      512K

// If the secondary core's memory is in SDRAM, an MPU region size also needs to be defined.
#define RAM_MPU_REGION  MPU_REGION_SIZE_512KB
```

Note that on the STM32, when booting from SDRAM, the alias `0x70000000` (or `0x60000000` if the banks are swapped) should be used, but never `0xC0000000` or `0xD0000000`, as those addresses are by default set as **Never Execute**.

#### Build the firmware
To build the firmware for STM32 micro-controllers, for example, run the following command:
```bash
cd openamp_vuart
make -j$(nproc) PORT=stm32
```
*Note that you need the ARM GNU toolchain (13 or higher) installed somewhere in the path.*

### Deploying the firmware

If the firmware is a RAM-based image, copy the `elf` file to the filesystem storage and run the example scripts. If the image is a flash-based image, the `bin` file needs to be written to the flash, at its base address, using `JTAG` or `dfu-util`.
