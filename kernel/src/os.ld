OUTPUT_ARCH("riscv")

ENTRY( _entry )

SECTIONS
{
    . = 0x80000000;
    PROVIDE(_begin = .);
    .text : {
        *(.text .text.*)

    }
    .rodata : {
        
        *(.rodata .rodata.*)	
    }
    .data : {
        . = ALIGN(16);
        *(.data .data.*)
        *(.sdata .sdata.*)
    }
    .bss : {
        *(.bss .bss.*)
        *(.sbss .sbss.*)
        *(COMMON)
    }

    PROVIDE(_end = .);
    
}
