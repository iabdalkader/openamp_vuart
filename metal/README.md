# libmetal

## Overview

Libmetal provides common user APIs to access devices, handle device interrupts
and request memory across the following operating environments:
  * Linux user space (based on UIO and VFIO support in the kernel)
  * RTOS (with and without virtual memory)
  * Bare-metal environments

For more details on the framework please refer to the
[OpenAMP Docs](https://openamp.readthedocs.io/en/latest/).

## About this repo

This is a fork of libmetal with minimal changes that allow it to be integrated
into a larger project, as a submodule.
