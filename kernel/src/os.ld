OUTPUT_ARCH("riscv")

ENTRY( _entry )

SECTIONS
{
    . = 0x80000000;
    PROVIDE(_begin = .);
    .text : {
        *(.text .text.*)
    . = ALIGN(0x1000);
    PROVIDE(_text = .)
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
    . = ALIGN(0x1000);
    PROVIDE(_end = .);
    
}
