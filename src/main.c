#include <stdint.h>

/* --- REGISTER ADDRESSES (From STM32F103 Datasheet) --- */

/* RCC (Reset and Clock Control) Base Address: 0x40021000 */
/* This is the "Fuse Box" of the microcontroller. Everything is OFF by default. */
#define RCC_BASE        0x40021000
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18)) // Offset 0x18

/* GPIO Port C Base Address: 0x40011000 */
/* The Blue Pill LED is usually on PC13 */
#define GPIOC_BASE      0x40011000
#define GPIOC_CRH       (*(volatile uint32_t *)(GPIOC_BASE + 0x04)) // Control Reg High
#define GPIOC_ODR       (*(volatile uint32_t *)(GPIOC_BASE + 0x0C)) // Output Data Reg

int main(void)
{
    /* STEP 1: Enable the Clock */
    /* You cannot write to GPIOC registers until you turn on its clock.
       Bit 4 of APB2ENR controls GPIOC. 
       (1 << 4) creates binary 00010000 */
    RCC_APB2ENR |= (1 << 4);

    /* STEP 2: Configure Pin PC13 */
    /* PC13 settings are in CRH (Control Register High).
       PC13 uses bits 20, 21, 22, 23.
       We want Output Push-Pull, 2MHz speed. 
       This corresponds to bits: 0010 (binary) or 0x2 (hex). */
    
    GPIOC_CRH &= ~(0xF << 20); // Clear the 4 bits for PC13 (Reset state)
    GPIOC_CRH |=  (0x2 << 20); // Write 2 into the bits for PC13

    while (1)
    {
        /* STEP 3: Blink */
        /* ODR (Output Data Register) controls the voltage.
           Bit 13 corresponds to Pin 13. */
           
        // Toggle Bit 13 using XOR (^)
        GPIOC_ODR ^= (1 << 13);

        // Lazy Delay Loop (Not accurate, but good enough for now)
        for (volatile int i = 0; i < 100000; i++);
    }
}