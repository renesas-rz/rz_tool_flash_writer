#!/bin/sh
#
# Sample script to build the flash writer for RZ/G2L.
#

set -ue

export ARCH=arm64
export CROSS_COMPILE=`pwd`/../../gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin/aarch64-none-elf-
export CC=${CROSS_COMPILE}gcc
export AS=${CROSS_COMPILE}as
export LD=${CROSS_COMPILE}ld
export AR=${CROSS_COMPILE}ar
export OBJDUMP=${CROSS_COMPILE}objdump
export OBJCOPY=${CROSS_COMPILE}objcopy

cd ../
make clean
make EMMC=ENABLE SERIAL_FLASH=DISABLE BOARD=${1}
