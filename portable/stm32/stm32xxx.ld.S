/*
 * This file is part of the OpenAMP Virtual UART Example.
 * Copyright (c) 2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 */

#include "port_config.h"

/* Entry Point */
ENTRY(g_pfnVectors)

_Min_Heap_Size = 0x2000;
_Min_Stack_Size = 0x2000;

/* Memories definition */
MEMORY
{
  SHM (rx)  : ORIGIN = SHM_ORIGIN, LENGTH = SHM_LENGTH 
  RAM (rx)  : ORIGIN = RAM_ORIGIN, LENGTH = RAM_LENGTH 
  ROM (rx)  : ORIGIN = ROM_ORIGIN, LENGTH = ROM_LENGTH 
}

#if RAM_IMAGE
REGION_ALIAS("REGION_ROM", RAM);
#else
REGION_ALIAS("REGION_ROM", ROM);
#endif
REGION_ALIAS("REGION_RAM", RAM);

 /* Symbols needed for OpenAMP to enable rpmsg */
_openamp_shm_region_start = ORIGIN(SHM);
_openamp_shm_region_end = ORIGIN(SHM)+LENGTH(SHM);

/* Sections */
SECTIONS
{
  /* The program code and other data into ROM memory */
  .text :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector))/* ISR table */
    . = ALIGN(4);
    *(.text)            /* .text sections (code)*/
    . = ALIGN(4);
    *(.text*)           /* .text* sections (code)*/
    . = ALIGN(4);
    *(.rodata)          /* .rodata sections (constants, strings, etc.)*/
    . = ALIGN(4);
    *(.rodata*)         /* .rodata* sections (constants, strings, etc.)*/
    . = ALIGN(4);
    _etext = .;         /* define a global symbols at end of code*/
  } >REGION_ROM

  .ARM.extab   : { 
  	. = ALIGN(4);
  	*(.ARM.extab* .gnu.linkonce.armextab.*)
  	. = ALIGN(4);
  } > REGION_ROM
  
  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } > REGION_ROM

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } > REGION_ROM
  
  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } > REGION_ROM
  
  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } > REGION_ROM

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    . = ALIGN(4);
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */
    . = ALIGN(4);
    _edata = .;
  } > REGION_RAM AT> REGION_ROM

  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } > REGION_RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
    _estack = .;
  } > REGION_RAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }

}
