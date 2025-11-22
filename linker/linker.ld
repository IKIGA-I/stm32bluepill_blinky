ENTRY(Reset_Handler)

MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 64K
    /* Change RAM to 20K (standard) or 10K (safe for clones) */
    RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {
        /* CRITICAL FIX: Added KEEP() so the garbage collector doesn't delete this! */
        KEEP(*(.isr_vector))
        *(.text)
        *(.rodata)
        . = ALIGN(4);
        _etext = .;
    } > FLASH

    /* Rest of the file stays the same... */
    .data :
    {
        _sdata = .;
        *(.data)
        . = ALIGN(4);
        _edata = .;
    } > RAM AT > FLASH

    .bss :
    {
        _sbss = .;
        *(.bss)
        . = ALIGN(4);
        _ebss = .;
    } > RAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}