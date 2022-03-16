OUTPUT_ARCH(arm)
MEMORY {
        rom     : ORIGIN = 0x08000000, LENGTH = 32M
}

SECTIONS {
        .text :
        ALIGN(4)
        {

                FILL (0xABCD)

                __text_start = . ;
                *(.init)
                *(.text)
                *(.text.*)
                *(.ctors)
                *(.dtors)
                *(.data)
                *(.fini)
                *(COMMON)
                __text_end  = . ;
        }

        lib_text :
        ALIGN(4)
        {
                __text_siirtc_start = . ;
                build/src/siirtc.o(.text);
                __text_siirtc_end  = . ;
        }

        .rodata :
        SUBALIGN(4)
        {
                __rodata_start  = . ;
                *(.rodata)
        }

        lib_rodata :
        SUBALIGN(4)
        {
                build/src/siirtc.o(.rodata);
                __rodata_end  = . ;

                __bss_start__ = . ;
                *(.bss .bss.*)
                __bss_end__ = . ;
        _end = __bss_end__ ;
        __end__ = __bss_end__ ;
        } >rom = 0xff
}
