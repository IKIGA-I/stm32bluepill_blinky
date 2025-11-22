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
└── src/
    ├── main.c           # Application logic (GPIO Configuration)
    └── startup.c        # Vector Table, Reset Handler, & Variable Initialization
