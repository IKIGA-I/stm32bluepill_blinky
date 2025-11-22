cmake_minimum_required(VERSION 3.20)

# --- 1. TOOLCHAIN SETUP (MUST BE BEFORE 'project') ---
# Tell CMake we are building for a generic embedded system, not Windows
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Force compiler to be the ARM GCC we installed
set(CMAKE_C_COMPILER "arm-none-eabi-gcc")
set(CMAKE_ASM_COMPILER "arm-none-eabi-gcc")

# Skip the standard compiler check (which tries to run a test .exe and fails on bare metal)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# --- 2. PROJECT DEFINITION ---
project(stm32_blink C ASM)

# --- 3. FLAGS & SETTINGS ---
set(MCU_FLAGS "-mcpu=cortex-m3 -mthumb")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${MCU_FLAGS} -g -Wall -O0")

# Use our custom linker script and don't use standard startup files
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MCU_FLAGS} -T ${LINKER_SCRIPT} -nostartfiles -Wl,--gc-sections")

# --- 4. SOURCES & OUTPUT ---
file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(${PROJECT_NAME}.elf ${SOURCES})

# Convert .elf to .hex and .bin for flashing
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND arm-none-eabi-objcopy -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND arm-none-eabi-objcopy -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Building HEX and BIN files..."
)