# README of the RZ/G2L DDR Tools

<Div Align="right">
Renesas Electronics Corporation

Jul-25-2025
</Div>

DDR Tools are essential utilities provided by Renesas to assist developers in configuring, tuning, and verifying the operation of DDR memory (DDR3L/DDR4) on the RZ/G2L MPU. 

## 1. Overview

This document explains about RZ/G2L DDR Tools sample software for Renesas RZ/G2L Group MPUs.

The RZ/G2L DDR Tools is downloaded from the Host PC via SCIF by boot ROM.

And the RZ/G2L DDR Tools loads the DDR parameters from the Host PC via SCIF and provides functions such as logging training messages, checking DQ margins, and running stress tests.

[Chapter 2](#2-operating-environment) describes the operating environment.

[Chapter 3](#3-software) describes the software.

[Chapter 4](#4-how-to-build-the-rzg2-flash-writer) explains example of how to build the RZ/G2L DDR Tools.

[Chapter 5](#5-how-to-run-the-rzg2-flash-writer) explains example of how to perform the RZ/G2L DDR Tools.

[Chapter 6](#6-error-case-to-handle) explains how to handle error case.

[Chapter 7](#7-revision-history) explains revision history.

## 1.2. License

BSD-3-Clause (please see file [LICENSE.md](LICENSE.md) for the details)

## 1.3. Notice

The RZ/G2L DDR Tools is distributed as a sample software from Renesas without any warranty or support.

## 1.4. Contributing

To contribute to this layer, you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## 1.5. References

The following table shows the document related to this function.

### Related Document

| Number | Issuer  | Title                                                       | Edition           |
| ------ | ------- | ----------------------------------------------------------- | ----------------- |
| 1      | JEDEC   | Embedded Multi-Media Card (eMMC) Electrical Standard (5.01) | JESD84-B50.1      |
| 2      | Renesas | Release Note for Verified Linux Package for 64bit kernel    | Rev.1.01 or later |
| 3      | Renesas | RZ/G2L Yocto recipe Start-Up Guide                          | Rev.1.01 or later |
| 4      | Renesas | RZ/G2L Reference Boards Start-up Guide                      | Rev.1.01 or later |

## 2. Operating Environment

### 2.1. Hardware Environment

The following table lists the hardware needed to use this function.

#### Hardware environment

| Name         | Note                                              |
| ------------ | ------------------------------------------------- |
| Target board | RZ/G2L SMARC PMIC Evaluation Kit(RZ/G2L PMIC EVK) |
| Host PC      | Ubuntu Desktop 20.04(64bit) or later              |

## 2.2. Software Environment

The following table lists the software required to use this sample software.

### Software environment

| Name                             | Note                                                    |
| -------------------------------- | ------------------------------------------------------- |
| ARM64 Cross-compile Toolchain    | ARM64 Cross-compile Toolchain Release GCC v10.2         |

## 3. Software

### 3.1. Function

This package has the following functions.

- Loading DDR parameters
- Step-by-Step Training Message Log
- DQ Margin Checker
- Stress Checker
- Change the SCIF baud rate setting.
- Display the command help.

### 3.2. Option setting

The RZ/G2L DDR Tools support the following build options.

#### 3.2.1. BOARD

| BOARD            | BOARD setting                                                 |
| ---------------- | ------------------------------------------------------------- |
| RZG2L_SMARC_PMIC | Generate binary that works on RZ/G2L PMIC EVK board           |
### 3.3. Command specification

The following table shows the command list.

#### Command list

| Command                              | Description                                                            |
| ------------------------------------ | ---------------------------------------------------------------------- |
| DDRP                                 | Store DDR parameters into internal SRAM.                                |
| DDR_S [sadr] [eadr] {loop}           | Simple write-then-read checking of DDR.                                 |
| DDR_RB [sadr] [eadr] {loop}          | Random data write-then-read checking of DDR.                            |
| DDR_FB [sadr] [eadr] [data] {loop}   | Fixed data write-then-read checking of DDR.                             |
| DQ                                   | DQ to DQS timing margin check.                                          |
| SUP                                  | Change the SCIF baud rate setting.                                     |
| SUD                                  | Change the SCIF baud rate setting.                                     |
| RESET                                | Perform RESET of the CPU.                                              |
| H                                    | Display the command help.                                              |

#### 3.3.1. Store DDR parameters into internal SRAM

This command stores DDR parameters into internal SRAM

The following shows the procedure of this command.

Use "DDRP" command to load DDR parameters from PC.

```text
>DDRP
Please Input File size(byte) : H'  
```
Input file size with 0xEC0 = 3,776 bytes

```text
>DDRP
Please Input File size(byte) : H'EC0
Please send ! (binary)
```
Send DDR parameter file (binary) from PC. You can use this sample file "DDR_Parameters_Normal.bin".

```text
>DDRP
Please Input File size(byte) : H'EC0
Please send ! (binary)
DDR parameters loaded
DDR Setup v.1.0.0
Step1 - Step11 completed
Step12 completed
Step13 completed
Step14 completed
Step15 completed
Step16 completed
Step17 completed
Step18 completed
Step19 completed
Step20 completed
Step21 completed
Step22 completed
Step23 completed
Step24 completed
Step25 completed
Step26 completed
Step27 completed
Step28 completed
Step29 completed
Step30 completed
Step31 is skipped because ECC is unused
Step32 completed
DDR init completed
>
```
If all init steps are successful, it will print "DDR init completed"

#### 3.3.2. Simple write-then-read checking of DDR

This command writes fixed patterns to DDR and verifies them.

sadr and eadr are hexadecimal values that represent the start address, and end address respectively.
loop is a decimal value that specifies how many times the test should be repeated. If loop is not provided, the default value is 1.

DDR_S command allows users to perform tests on custom memory ranges specified by start and end addresses within the valid range of 0x40000040 to 0x13FFFFFFF, as 0x40000000 to 0x4000003F is a reserved area for training.

The following shows the procedure of this command.

Example

```text  
>ddr_s 42000000 43ffffff
== RAM CHECK (Byte Access) ===
- Marching Data Check --------
 [ Write H'00               ]
 [ Check H'00 -> Write H'55 ]
 [ Check H'55 -> Write H'AA ]
 [ Check H'AA -> Write H'FF ]
 [ Check H'FF               ]
- Decoder Pattern Check ------
 [ Write H'00,H'01,H'02 ... ]
 [ Check H'00,H'01,H'02 ... ]
CHECK RESULT ---->OK
1 command executions successful
```

#### 3.3.3. Random data write-then-read checking of DDR

This command writes random data from SRAM to DDR, then reads it back and verifies the result.

sadr and eadr are hexadecimal values that represent the start address, and end address respectively.
loop is a decimal value that specifies how many times the test should be repeated. If loop is not provided, the default value is 1.

DDR_RB command allows users to perform tests on custom memory ranges specified by start and end addresses within the valid range of 0x40000040 to 0x13FFFFFFF, as 0x40000000 to 0x4000003F is a reserved area for training.

The following shows the procedure of this command.

Example

```text
>ddr_rb 41000000 42ffffff 
== RAM CHECK RAMDOM (Byte Access) ===
##
CHECK RESULT ---->OK
1 command executions successful  
```

#### 3.3.4. Fixed data write-then-read checking of DDR

This command writes a fixed value (e.g., 0xA5) to DDR memory, then reads it back and verifies the result.

sadr, eadr, and data are hexadecimal values that represent the start address, end address, and fixed data respectively.
loop is a decimal value that specifies how many times the test should be repeated. If loop is not provided, the default value is 1.

DDR_FB command allows users to perform tests on custom memory ranges specified by start and end addresses within the valid range of 0x40000040 to 0x13FFFFFFF, as 0x40000000 to 0x4000003F is a reserved area for training.

The following shows the procedure of this command.

Example

```text  
>ddr_fb 40000040 4100003f a5 
== RAM CHECK FIXED DATA (Byte Access) ===
 [ Write H'A5               ]
 [ Check H'A5               ]
CHECK RESULT ---->OK
1 command executions successful
```

#### 3.3.5. DQ to DQS timing margin check

This command perform margin checking between DQ and DQS signals.

The following shows the procedure of this command.

```text
>DQ
***********************************
******** DQ Margin Checker ********
***********************************
V2.0.0 June 8th, 2022.
DRAM Initialization was skipped. It has already done.
[Write]
1                                                            100                                                                       
################################################################
RANK[0]
DQ# vs Delay (-31 to 32 [tap])
DQ[00]: XXXXXXXXXXXXXXXXXXXX...........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[01]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[02]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[03]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[04]: XXXXXXXXXXXXXXXXXXXXXX.........||...........XXXXXXXXXXXXXXXXXXXX
DQ[05]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[06]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[07]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[08]: XXXXXXXXXXXXXXXXXXXXXX.........||........XXXXXXXXXXXXXXXXXXXXXXX
DQ[09]: XXXXXXXXXXXXXXXXXXXXXX.........||........XXXXXXXXXXXXXXXXXXXXXXX
DQ[10]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[11]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[12]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[13]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[14]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[15]: XXXXXXXXXXXXXXXXXXXXXX.........||...........XXXXXXXXXXXXXXXXXXXX
[Read]
1                                                            100
################################################################
RANK[0]
DQ# vs Delay (-31 to 32 [tap])
DQ[00]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[01]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[02]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[03]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[04]: XXXXXXXXXXXXXXXXXXXXXX.........||...........XXXXXXXXXXXXXXXXXXXX
DQ[05]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[06]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[07]: XXXXXXXXXXXXXXXXXXXXX..........||..........XXXXXXXXXXXXXXXXXXXXX
DQ[08]: XXXXXXXXXXXXXXXXXXXXXX.........||........XXXXXXXXXXXXXXXXXXXXXXX
DQ[09]: XXXXXXXXXXXXXXXXXXXXXX.........||........XXXXXXXXXXXXXXXXXXXXXXX
DQ[10]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[11]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[12]: XXXXXXXXXXXXXXXXXXXXXX.........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[13]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[14]: XXXXXXXXXXXXXXXXXXXXX..........||.........XXXXXXXXXXXXXXXXXXXXXX
DQ[15]: XXXXXXXXXXXXXXXXXXXXXX.........||...........XXXXXXXXXXXXXXXXXXXX
FINISH!

```

#### 3.3.6. Change the SCIF baud rate setting

This command will change the baud rate of the SCIF.

Baud rate depends on the MPU and the SCIF clock setting on the board.

##### Baud rate settings after command execution

| Command | Baud rate at After command execution |
|---------|-------------------------------------:|
| SUP     | 921600bps                            |
| SUD     | 115200bps                            |

*Note) The baud rate that has been changed in this command cannot be undone until the power is turned off.*

The following shows the procedure of this command.

```text
>SUP
Scif speed UP
Please change to 921.6Kbps baud rate setting of the terminal.
```

```text
>SUD
Scif speed DOWN
Please change to 115.2Kbps baud rate setting of the terminal.
```

#### 3.3.7. Display the command help

Displays a description of the commands.

The following shows the procedure of this command.

```text
       Load DDR parameters
DDRP           Store DDR parameters into internal SRAM

       Stress checker command
DDR_S  [sadr] [eadr] {loop}        Simple write-then-read checking of DDR
DDR_RB [sadr] [eadr] {loop}        Random data write-then-read checking of DDR
DDR_FB [sadr] [eadr] [data] {loop} Fixed data write-then-read checking of DDR

       DQ margin checker command
DQ             DQ to DQS timing margin check

 SUP            Scif speed UP (Change to speed up baud rate setting)
 SUD            Scif speed DOWN (Change to speed down baud rate setting)
 RESET          Perform RESET of the CPU
 H              help
 D  {sadr {eadr}}          memory dump  (DM sets dump size)
 DM {B|W|L|X}              set&disp dump mode
 M  [adr]                  set memory(BYTE)
 MW [adr]                  set memory(WORD)
 ML [adr]                  set memory(LONG)
 MX [adr]                  set memory(LONG LONG)
 F  [sadr] [eadr] [data]   fill memory
 FL [sadr] [eadr] [data]   fill memory(LONG)
 FX [sadr] [eadr] [data]   fill memory(LONG LONG)
>
```

## 4. How to build the RZ/G2L DDR Tools

This chapter is described how to build the RZ/G2L DDR Tools.

### 4.1. Prepare the source code

```text
$ mkdir ~/DDR_Tools
$ cd ~/DDR_Tools
$ git clone https://github.com/renesas-rz/rz_tool_flash_writer.git
$ cd rz_tool_flash_writer/
$ git checkout v1.0 
```

### 4.2. Prepare the compiler

ARM toolchain:

```text  
$ cd ~/DDR_Tools
$ wget https://developer.arm.com/-/media/Files/downloads/gnu-a/10.2-2020.11/binrel/gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf.tar.xz
$ tar xvf gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf.tar.xz
```

### 4.3. Build the RZ/G2L DDR Tools

S-record file will be built by the following command.

```text  
$ cd ~/DDR_Tools/rz_tool_flash_writer/
$ export ARCH=arm64
$ export CROSS_COMPILE=../gcc-arm-10.2-2020.11-x86_64-aarch64-none-elf/bin/aarch64-none-elf-
$ export CC=${CROSS_COMPILE}gcc
$ export AS=${CROSS_COMPILE}as
$ export LD=${CROSS_COMPILE}ld
$ export AR=${CROSS_COMPILE}ar
$ export OBJDUMP=${CROSS_COMPILE}objdump
$ export OBJCOPY=${CROSS_COMPILE}objcopy
$ make clean
$ make EMMC=DISABLE SERIAL_FLASH=DISABLE BOARD=RZG2L_SMARC_PMIC
```

Output image will be available in the following directory.

* ~/DDR_Tools/rz_tool_flash_writer/AArch64_output/DDR_Tool_SCIF_RZG2L_SMARC_PMIC_DDR4.mot

## 5. How to run the RZ/G2L DDR Tools

### 5.1. Prepare for run DDR Tools

Start the target in the SCIF download mode and run the RZ/G2L DDR Tools sample code.

Regarding the DIP switch configuration on the board, refer to [Related Document](#related-document) No.4.

The following table shows the setting of terminal software.

#### Terminal software configuration

| Baud rate | Data bit length | Parity check | Stop bits | Flow control |
| --------: | --------------- | ------------ | --------- | ------------ |
| 115200bps | 8bits           | none         | 1bit      | none         |

Terminal software outputs the following log at power ON the target.

```text
SCIF Download mode
 (C) Renesas Electronics Corp.

 -- Load Program to SystemRAM ---------------
 please send !
```

Transfer S-record file after the log output.

S-record file:

- AArch64_output/DDR_Tool_SCIF_RZG2L_SMARC_PMIC_DDR4.mot

After the transfer has succeeded, the following log will be shown.

```text
Flash writer for RZ/G2 Series V1.08 Jul.25,2025
Product Code : RZ/G2L
> 
```

Please enter the any key from the console to continue.

## 6. Error case to handle

TBD 

## 7. Revision history

Describe the revision history of RZ/G2L DDR Tools.

### 7.1. v1.00

- First release.
- Support RZ/G2L PMIC EVK board.