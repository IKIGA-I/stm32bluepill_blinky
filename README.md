# STM32 Bare Metal Blinky (CMake + Ninja + GCC)

**A hardware-agnostic, "from scratch" implementation of an embedded build system on Windows.**

## 🚀 Overview
This project demonstrates a professional **bare-metal firmware development environment** for the STM32F103 (Blue Pill). Unlike standard hobbyist projects that rely on vendor-supplied IDEs (STM32CubeIDE, Keil) or abstraction layers (Arduino/HAL), this project implements:

* **Direct Register Access:** Drivers written from scratch using memory-mapped I/O.
* **Custom Toolchain:** A cross-compilation pipeline using **CMake** and **Ninja** on Windows.
* **Startup Code:** Custom `startup.c` and linker scripts to manage the vector table and memory layout manually.
* **SWD Debugging:** Flashing and verification via **OpenOCD** and **ST-Link V2**.

## 🛠️ Tech Stack & Skills Demonstrated
* **Language:** C (C99), Assembly (Startup)
* **Build System:** CMake 3.20+, Ninja
* **Compiler:** Arm GNU Toolchain (`arm-none-eabi-gcc`)
* **Hardware Interface:** SWD (Serial Wire Debug) via OpenOCD
* **Concepts:** Memory Management (`.text`, `.data`, `.bss`), Linker Scripting, Cross-Compilation, Garbage Collection (`--gc-sections`).

## 🔌 Hardware Setup
* **Target Board:** STM32F103C8T6 "Blue Pill" (ARM Cortex-M3)
* **Programmer:** ST-Link V2 (Clone/Genuine)
* **Wiring:**

| ST-Link Pin | Blue Pill Pin | Function |
| :--- | :--- | :--- |
| 3.3V | 3.3 | Power |
| GND | GND | Ground |
| SWDIO | DIO (PA13) | Data |
| SWCLK | CLK (PA14) | Clock |

> **Note:** Ensure the **BOOT0** jumper is set to **0** (Low) to boot from Flash memory.

## 📂 Project Structure
```text
stm32_bare_metal/
├── CMakeLists.txt       # Build configuration & Cross-compilation setup
├── linker/
│   └── linker.ld        # Memory map (Flash/RAM definition) & Section placement

```
📝 Key Technical Implementation
1. The Build System (CMake)
CMake is configured to bypass the default host OS checks to enable cross-compilation for a generic embedded target.

CMake

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
2. Linker Script Optimization
This project uses -Wl,--gc-sections to optimize binary size. A critical challenge addressed was ensuring the Vector Table was not optimized away by the linker.

Fix: The linker script explicitly preserves the table using KEEP(*(.isr_vector)).

Fix: The startup code uses __attribute__((used)) to mark the table as essential.

3. Bare Metal Driver
The GPIO driver avoids HAL overhead by manipulating the RCC and GPIO registers directly:

C

/* Example: Enabling Port C Clock */
#define RCC_APB2ENR (*(volatile uint32_t *)(0x40021000 + 0x18))
RCC_APB2ENR |= (1 << 4); // Set Bit 4
💻 Build Instructions
1. Generate Build Files
Open a terminal in the project root:

PowerShell

cmake -S . -B build -G Ninja
2. Compile
PowerShell

cmake --build build
Output: Generates stm32_blink.bin and stm32_blink.hex in the build/ directory.

3. Flash to Hardware
Using OpenOCD with the ST-Link interface:

PowerShell

openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program build/stm32_blink.bin 0x08000000 verify reset exit"
🐛 Troubleshooting
Clone Chips: If OpenOCD reports an "UNEXPECTED idcode" (e.g., 0x2ba01477), it indicates a CKS32/CS32 clone chip. The flashing command typically works despite the warning.

No Blink: Verify BOOT0 is set to 0 and press the physical Reset button after flashing.
└── src/
    ├── main.c           # Application logic (GPIO Configuration)
    └── startup.c        # Vector Table, Reset Handler, & Variable Initialization
