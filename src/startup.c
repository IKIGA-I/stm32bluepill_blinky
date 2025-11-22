#include <stdint.h>

/* These symbols come from the linker script (linker.ld). 
   They are not variables, they are addresses! */
extern uint32_t _estack;
extern uint32_t _etext; // End of code in Flash
extern uint32_t _sdata; // Start of data in RAM
extern uint32_t _edata; // End of data in RAM
extern uint32_t _sbss;  // Start of bss in RAM
extern uint32_t _ebss;  // End of bss in RAM

/* We promise the compiler that main() exists somewhere else */
extern void main(void);

/* This function runs BEFORE main() */
void Reset_Handler(void)
{
    // 1. Pointer Setup
    uint32_t *pSrc = &_etext; // Point to end of code (start of data in Flash)
    uint32_t *pDest = &_sdata; // Point to start of data in RAM

    // 2. Copy initialized data from Flash to RAM
    // We iterate until the destination pointer reaches the end of the data section
    while (pDest < &_edata) {
        *pDest++ = *pSrc++;
    }

    // 3. Zero out the BSS section (uninitialized variables)
    pDest = &_sbss;
    while (pDest < &_ebss) {
        *pDest++ = 0;
    }

    // 4. Everything is ready. Call the application!
    main();
}

/* The CPU looks here at boot to know what to do.
   __attribute__((section(".isr_vector"))) tells the linker:
   "Don't put this in random code memory. Put this at the very start!" */
// ... (Top part stays the same) ...

/* Add __attribute__((used)) */
__attribute__((section(".isr_vector"), used))
const void *vector_table[] = {
    &_estack,        // Initial Stack Pointer
    Reset_Handler    // Reset Handler
};