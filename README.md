# README of the RZ/G3E DDR Tools

<Div Align="right">
Renesas Electronics Corporation

Oct-15-2025
</Div>

The RZ/G3E DDR Tools are essential utilities provided by Renesas to assist developers in configuring, tuning, and verifying the operation of DDR memory (LPDDR4) on the RZ/G3E MPU. 

## 1. Overview

This document explains about RZ/G3E DDR Tools sample software for Renesas RZ/G3E Group MPUs.

The RZ/G3E DDR Tools is downloaded from the Host PC via SCIF by boot ROM.
It loads the DDR parameters from the Host PC via SCIF and provides functions such as logging training messages, Eye Opening Tool, and stress tests.

And the RZ/G3E DDR Tools downloads the some of the raw images from Host PC via SCIF, and writes the raw images to the Serial NOR Flash (hereafter referred to as “Serial Flash”).

[Chapter 2](#2-operating-environment) describes the operating environment.

[Chapter 3](#3-software) describes the software.

[Chapter 4](#4-how-to-build-the-rzg2-flash-writer) explains example of how to build the RZ/G3E DDR Tools.

[Chapter 5](#5-how-to-run-the-rzg2-flash-writer) explains example of how to perform the RZ/G3E DDR Tools.

[Chapter 6](#6-error-case-to-handle) explains how to handle error case.

[Chapter 7](#7-revision-history) explains revision history.

*Note) This sample software does not support the file system. Therefore, can be write the raw image to the Serial NOR Flash.*

## 1.2. License

BSD-3-Clause (please see file [LICENSE.md](LICENSE.md) for the details)

## 1.3. Notice

The RZ/G3E DDR Tools is distributed as a sample software from Renesas without any warranty or support.

## 1.4. Contributing

To contribute to this layer, you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

## 1.5. References

The following table shows the document related to this function.

### Related Document

| Number | Issuer  | Title                                                       | Edition           |
| ------ | ------- | ----------------------------------------------------------- | ----------------- |
| 1      | JEDEC   | Embedded Multi-Media Card (eMMC) Electrical Standard (5.01) | JESD84-B50.1      |
| 2      | Renesas | Release Note for Verified Linux Package for 64bit kernel    | Rev.1.00 or later |
| 3      | Renesas | RZ/G3E Reference Boards Start-up Guide                      | Rev.1.00 or later |

## 2. Operating Environment

### 2.1. Hardware Environment

The following table lists the hardware needed to use this function.

#### Hardware environment

| Name         | Note                                              |
| ------------ | ------------------------------------------------- |
| Target board | RZ/G3E SMARC Evaluation Kit (RZ/G3E EVK)          |
| Host PC      | Ubuntu Desktop 20.04(64bit) or later              |

The following table shows Serial Flash and eMMC support for RZ/G3E EVK MPU.

##### Serial Flash / eMMC support status of RZ/G3E EVK MPU

| Read/Write the Serial Flash | Boot from the Serial Flash | Read/Write the eMMC | Boot from the eMMC |
| --------------------------- | -------------------------- | ------------------- | ------------------ |
| Support                     | Support                    | Support             | Support            |

### 2.2. Software Environment

The following table lists the software required to use this sample software.

### Software environment

| Name                             | Note                                                    |
| -------------------------------- | ------------------------------------------------------- |
| ARM64 Cross-compile Toolchain    | ARM64 Cross-compile Toolchain Release GCC v10.3         |

## 3. Software

### 3.1. Function

This package has the following functions.

- Write to the images to the Serial Flash.
- Erase the Serial Flash.
- Display the CID/CSD/EXT_CSD registers of an eMMC.
- Modify the EXT_CSD registers of an eMMC.
- Write binary images to the boot partition of an eMMC.
- Write binary images to the user data area of an eMMC.
- Erase the boot partition of an eMMC.
- Erase the user data area of an eMMC.
- Load DDR parameters.
- Run the Eye Opening Tool.
- Display training message.
- Run the stress checker.
- Change the SCIF baud rate setting.
- Display the command help.

### 3.2. Option setting

The RZ/G3E DDR Tools support the following build options.

#### 3.2.1. BOARD

| BOARD            | BOARD setting                                                 |
| ---------------- | ------------------------------------------------------------- |
| RZG3E_SMARC      | Generate binary that works on RZ/G3E EVK board. (default)     |

#### 3.2.2. SERIAL_FLASH

Select from the following table according to the Serial Flash writing function.

If this option is not selected, the default value is ENABLE.

##### Association table for the SERIAL_FLASH value and valid Serial Flash writing function settings

| SERIAL_FLASH | Serial Flash writing setting                          |
| ------------ | ----------------------------------------------------- |
| ENABLE       | Serial Flash writing function is available. (default) |
| DISABLE      | Serial Flash writing function is not available.       |

#### 3.2.3 eMMC

Select from the following table according to the eMMC writing function.

If this option is not selected, the default value is ENABLE.

##### Association table for the eMMC value and valid eMMC writing function settings

| EMMC    | eMMC writing setting                                        |
|---------|-------------------------------------------------------------|
| ENABLE  | eMMC writing function is available. (default)               |
| DISABLE | eMMC writing function is not available.                     |

### 3.3. Command specification

The following table shows the command list.

#### Command list

| Command                              | Description                                                                                        |
| ------------------------------------ | -------------------------------------------------------------------------------------------------- |
| XLS2                                 | Write the S-record format images to the Serial Flash(SREC format).                                 |
| XLS3                                 | Write the S-record format images to the Serial Flash(BIN format).                                  |
| XCS                                  | Erase the Serial Flash.                                                                            |
| EM_DCID                              | Display the CID registers of eMMC.                                                                 |
| EM_DCSD                              | Display the CSD registers of eMMC.                                                                 |
| EM_DECSD                             | Display the EXT_CSD registers of eMMC.                                                             |
| EM_SECSD                             | Modify the EXT_CSD registers of eMMC.                                                              |
| EM_W                                 | Write to the S-record format images to the user data area of eMMC, and the boot partition of eMMC. |
| EM_WB                                | Write to the raw binary images to the user data area of eMMC, and the boot partition of eMMC.      |
| EM_E                                 | Erase the user data area of eMMC, and the boot partition of eMMC.                                  |
| DDRP                                 | Store DDR parameters into internal SRAM and run Eye Opening Tool.                                   |
| DDR_S [sadr] [eadr] {loop}           | Simple write-then-read checking of DDR.                                                            |
| DDR_RB [sadr] [eadr] {loop}          | Random data write-then-read checking of DDR.                                                       |
| DDR_FB [sadr] [eadr] [data] {loop}   | Fixed data write-then-read checking of DDR.                                                        |
| SUP                                  | Change the SCIF baud rate setting.                                                                 |
| SUD                                  | Change the SCIF baud rate setting.                                                                 |
| RESET                                | Perform RESET of the CPU.                                                                          |
| H                                    | Display the command help.                                                                          |

#### 3.3.1. Write to the S-record format images to the Serial Flash

This command writes the S-record format image to Serial Flash.

##### Example of writing data for the Serial Flash boot

| Filename                    | Program Top Address | Flash Save Address | Description                                 |
| --------------------------- | ------------------- | ------------------ | ------------------------------------------- |
| bl2_bp_spi-smarc-rzG3E.srec | H'8003600           | H'00000            | Loader                                      |
| fip-smarc-rzG3E.srec        | H'00000             | H'60000            | ARM Trusted Firmware and U-boot in FIP file |

The following shows the procedure of this command.

```text
>XLS2
===== Qspi writing of RZ/G3E Board Command =============
Load Program to Spiflash
Writes to any of SPI address.
 Dialog : AT25QL128A
Program Top Address & Qspi Save Address
===== Please Input Program Top Address ============
  Please Input : H'
```

Please enter the program top address of the write image in hexadecimal.

```text
>XLS2
===== Qspi writing of RZ/G3E Board Command =============
Load Program to Spiflash
Writes to any of SPI address.
 Dialog : AT25QL128A
Program Top Address & Qspi Save Address
===== Please Input Program Top Address ============
  Please Input : H'8003600

===== Please Input Qspi Save Address ===
  Please Input : H'
```

Please enter the flash save address in hexadecimal.

```text
>XLS2
===== Qspi writing of RZ/G3E Board Command =============
Load Program to Spiflash
Writes to any of SPI address.
 Dialog : AT25QL128A
Program Top Address & Qspi Save Address
===== Please Input Program Top Address ============
  Please Input : H'8003600

===== Please Input Qspi Save Address ===
  Please Input : H'0
please send ! ('.' & CR stop load)
```

Please download the write image in S-record format.

```text
>XLS2
===== Qspi writing of RZ/G3E Board Command =============
Load Program to Spiflash
Writes to any of SPI address.
 Dialog : AT25QL128A
Program Top Address & Qspi Save Address
===== Please Input Program Top Address ============
  Please Input : H'8003600

===== Please Input Qspi Save Address ===
  Please Input : H'0
please send ! ('.' & CR stop load)
Erase SPI Flash memory...
Erase Completed
Write to SPI Flash memory.
======= Qspi  Save Information  =================
 SpiFlashMemory Stat Address : H'00000000
 SpiFlashMemory End Address  : H'00021170
===========================================================

```

Image writing has been completed.

```text
SPI Data Clear(H'FF) Check : H'00000000-0000FFFF,Clear OK?(y/n)
```
In case a message to prompt to clear data like above, please enter “y”.


#### 3.3.2. Erase the Serial NOR Flash

This command erases all sectors of Serial Flash.

The following shows the procedure of this command.

```text
>XCS
ALL ERASE SpiFlash memory
Clear OK?(y/n)
```

Please enter the 'y' key.

```text
>XCS
ALL ERASE SpiFlash memory
 Dialog : AT25QL128A
 ERASE QSPI-FLASH (60sec[typ]).... complete!
>
```

Selected Serial Flash has been erased.

#### 3.3.3. Display the CID registers command

This command displays the contents of the CID registers of the eMMC.

The following shows the procedure of this command.

```text
>EM_DCID

[CID Field Data]
[127:120]  MID  0x13
[113:112]  CBX  0x01
[111:104]  OID  0x4E
[103: 56]  PNM  0x30494D323046
[ 55: 48]  PRV  0x10
[ 47: 16]  PSN  0x31893BAF
[ 15:  8]  MDT  0x5B
[  7:  1]  CRC  0x00
```

#### 3.3.4. Display the CSD registers command

This command displays the contents of the CSD registers of eMMC.

The following shows the procedure of this command.

```text
>EM_DCSD

[CSD Field Data]
[127:126]  CSD_STRUCTURE       0x03
[125:122]  SPEC_VERS           0x04
[119:112]  TAAC                0x7F
...
[ 11: 10]  FILE_FORMAT         0x00
[  9:  8]  ECC                 0x00
[  7:  1]  CRC                 0x00
```

#### 3.3.5. Display the EXT_CSD registers command

This command displays the contents of the EXT_CSD registers of the eMMC.

The following shows the procedure of this command.

```text
>EM_DECSD

[EXT_CSD Field Data]
[505:505]  EXT_SECURITY_ERR                           0x00
[504:504]  S_CMD_SET                                  0x01
[503:503]  HPI_FEATURES                               0x01
...
[142:140]  ENH_SIZE_MULT                              0x000000
[139:136]  ENH_START_ADDR                             0x00000000
[134:134]  SEC_BAD_BLK_MGMNT                          0x00
```

#### 3.3.6. Modify the EXT_CSD registers of eMMC command

This command modifies the contents of the EXT_CSD registers in the eMMC.

The values must be entered as **hexadecimal**.

Example:

```text
>EM_SECSD
  Please Input EXT_CSD Index(H'00 - H'1FF) :b1
  EXT_CSD[B1] = 0x00
  Please Input Value(H'00 - H'FF) :2
  EXT_CSD[B1] = 0x02
```

#### eMMC Boot Settings

Please note that for eMMC booting, the following EXT_CSD registers need to be modified:
 - EXT_CSD[**B1**] = **0x02**
 - EXT_CSD[**B3**] = **0x08**

#### 3.3.7. Write to the S-record format images to the eMMC

This command writes the S-record format image to any partition of the eMMC.

##### Example of writing data for the eMMC boot

| Filename                       | eMMC Save Partition | eMMC Save Sectors | Program Top Address | Description                                 |
|--------------------------------|---------------------|-------------------|---------------------|---------------------------------------------|
| bl2_bp_emmc-smarc-rzG3E.srec   | boot partition1     | H'00000001        | H'8003600           | Loader                                      |
| fip-smarc-rzG3E.srec           | boot partition1     | H'00000300        | H'00000             | ARM Trusted Firmware and U-boot in FIP file |

The following shows the procedure of this command.
The values must be entered as **hexadecimal**.
Please enter the start sector number of the write image in hexadecimal. Sector size is 512 bytes.
Please enter the program top address of the write image in hexadecimal.
Please download the write image in S-record format.

```text
>EM_W
EM_W Start --------------
---------------------------------------------------------
Please select,eMMC Partition Area.
 0:User Partition Area   : 62160896 KBytes
  eMMC Sector Cnt : H'0 - H'0768FFFF
 1:Boot Partition 1      : 32256 KBytes
  eMMC Sector Cnt : H'0 - H'0000FBFF
 2:Boot Partition 2      : 32256 KBytes
  eMMC Sector Cnt : H'0 - H'0000FBFF
---------------------------------------------------------
  Select area(0-2)>1                                        <<<< Enter "1" here
-- Boot Partition 1 Program -----------------------------
Please Input Start Address in sector :1                     <<<< Enter "1" here
Please Input Program Start Address : 8003600                <<<< Enter "8003600" here
Work RAM (H'40000000-H'4FFFFFFF) Clear....
please send ! ('.' & CR stop load)
SAVE -FLASH.......
EM_W Complete!
```

Image writing has been completed.

#### 3.3.8. Erase the eMMC

This command erases any partition of the eMMC.

The following shows the procedure of this command.

```text
>EM_E
EM_E Start --------------
---------------------------------------------------------
Please select,eMMC Partition Area.
 0:User Partition Area   : 62160896 KBytes
  eMMC Sector Cnt : H'0 - H'0768FFFF
 1:Boot Partition 1      : 32256 KBytes
  eMMC Sector Cnt : H'0 - H'0000FBFF
 2:Boot Partition 2      : 32256 KBytes
  eMMC Sector Cnt : H'0 - H'0000FBFF
---------------------------------------------------------
  Select area(0-2)>0                                       <<<< Enter "0" here
-- User Partition Area Program --------------------------
EM_E Complete!
```

Selected partition has been erased.

#### 3.3.9. Store DDR parameters into internal SRAM and run Eye Opening Tool

This command stores DDR parameters into internal SRAM and runs Eye Opening Tool

The following shows the procedure of this command.

Use "DDRP" command to load DDR parameters from PC.

```text
>DDRP
Please Input File size(byte) : H'  
```
Input file size with 0x11E58 = 73,304 bytes

```text
>DDRP
Please Input File size(byte) : H'11E58
Please send ! (binary)
```
Send DDR parameter file (binary) from PC. You can use this sample file "DDR_Parameters_Normal.bin". After the DDR parameters are loaded, Eye Opening Tool runs automatically. The raw test result like below is output on the terminal.

```text
>DDRP
Please Input File size(byte) : H'11E58
Please send ! (binary)
DDR parameters loaded

start DDR Setup
DDR: Setup (Rev. 02.01)
cpg_ddr_part1
setup_mc
cpg_ddr_part2
phyinit_c
phyinit_d2h_1d
00000007
phyinit_d2h_2d
00000007
phyinit_mc
save_retcsr
phyinit_i
phyinit_j
phyinit_d2h_1d
```

#### 3.3.10. Simple write-then-read checking of DDR

This command writes fixed patterns to DDR and verifies them.

sadr and eadr are hexadecimal values that represent the start address, and end address respectively.
loop is a decimal value that specifies how many times the test should be repeated. If loop is not provided, the default value is 1.

DDR_S command allows users to perform tests on custom memory ranges specified by start and end addresses within the valid range of 0x40000000 to 0x23FFFFFFF.

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

#### 3.3.11. Random data write-then-read checking of DDR

This command writes random data from SRAM to DDR, then reads it back and verifies the result.

sadr and eadr are hexadecimal values that represent the start address, and end address respectively.
loop is a decimal value that specifies how many times the test should be repeated. If loop is not provided, the default value is 1.

DDR_RB command allows users to perform tests on custom memory ranges specified by start and end addresses within the valid range of 0x40000000 to 0x23FFFFFFF.

The following shows the procedure of this command.

Example

```text
>ddr_rb 41000000 42ffffff 
== RAM CHECK RAMDOM (Byte Access) ===
##
CHECK RESULT ---->OK
1 command executions successful  
```

#### 3.3.12. Fixed data write-then-read checking of DDR

This command writes a fixed value (e.g., 0xA5) to DDR memory, then reads it back and verifies the result.

sadr, eadr, and data are hexadecimal values that represent the start address, end address, and fixed data respectively.
loop is a decimal value that specifies how many times the test should be repeated. If loop is not provided, the default value is 1.

DDR_FB command allows users to perform tests on custom memory ranges specified by start and end addresses within the valid range of 0x40000000 to 0x23FFFFFFF.

The following shows the procedure of this command.

Example

```text  
>ddr_fb 40000000 4100003f a5 
== RAM CHECK FIXED DATA (Byte Access) ===
 [ Write H'A5               ]
 [ Check H'A5               ]
CHECK RESULT ---->OK
1 command executions successful
```

#### 3.3.13. Change the SCIF baud rate setting

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

#### 3.3.14. Display the command help

Displays a description of the commands.

The following shows the procedure of this command.

```text
>H
        SPI Flash write command
 XCS            erase program to SPI Flash
 XLS2           write program to SPI Flash
 XLS3           write program to SPI Flash(Binary)

        eMMC write command
 EM_DCID        display register CID
 EM_DCSD        display register CSD
 EM_DECSD       display register EXT_CSD
 EM_SECSD       change register EXT_CSD byte
 EM_W           write program to eMMC
 EM_WB          write program to eMMC (Binary)
 EM_E           erase program to eMMC

        Load DDR parameters
 DDRP           Store DDR parameters into internal SRAM

        Stress checker command
 DDR_S  [sadr] [eadr] {loop}        Simple write-then-read checking of DDR
 DDR_RB [sadr] [eadr] {loop}        Random data write-then-read checking of DDR
 DDR_FB [sadr] [eadr] [data] {loop} Fixed data write-then-read checking of DDR

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

## 4. How to build the RZ/G3E DDR Tools

This chapter is described how to build the RZ/G3E DDR Tools.

### 4.1. Prepare the source code

```text
$ mkdir ~/DDR_Tools
$ cd ~/DDR_Tools
$ git clone https://github.com/renesas-rz/rz_tool_flash_writer.git
$ cd rz_tool_flash_writer/
$ git checkout rz_g3e
```

### 4.2. Prepare the compiler

ARM toolchain:

```text  
$ cd ~/DDR_Tools
$ wget https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar.xz
$ tar xvf gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar.xz
```

### 4.3. Build the RZ/G3E DDR Tools

S-record file will be built by the following command.

```text  
$ cd ~/DDR_Tools/rz_tool_flash_writer
$ export ARCH=arm64
$ export CROSS_COMPILE= ../gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf/bin/aarch64-none-elf-
$ export CC=${CROSS_COMPILE}gcc
$ export AS=${CROSS_COMPILE}as
$ export LD=${CROSS_COMPILE}ld
$ export AR=${CROSS_COMPILE}ar
$ export OBJDUMP=${CROSS_COMPILE}objdump
$ export OBJCOPY=${CROSS_COMPILE}objcopy
$ make -f makefile-g3e.gcc-arm clean
$ make -f makefile-g3e.gcc-arm BOARD=RZG3E_SMARC
```

Output image will be available in the following directory.

* ~/DDR_Tools/rz_tool_flash_writer/AArch64_output/Flash_Writer_SCIF_RZG3E_SMARC_LPDDR4X.mot

## 5. How to run the RZ/G3E DDR Tools

### 5.1. Prepare for run DDR Tools

Start the target in the SCIF download mode and run the RZ/G3E DDR Tools sample code.

Regarding the DIP switch configuration on the board, refer to [Related Document](#related-document) No.3.

The following table shows the setting of terminal software.

#### Terminal software configuration

| Baud rate | Data bit length | Parity check | Stop bits | Flow control |
| --------: | --------------- | ------------ | --------- | ------------ |
| 115200bps | 8bits           | none         | 1bit      | none         |

Terminal software outputs the following log at power ON the target.

```text
>SCI Download mode (Normal SCI boot)
-- Load Program to SRAM ---------------
```

Transfer S-record file after the log output.

S-record file:

- AArch64_output/Flash_Writer_SCIF_RZG3E_SMARC_LPDDR4X.mot

After the transfer has succeeded, the following log will be shown.

```text
Flash writer for RZ/G3E Series V0.92 Aug.07,2025
 Product Code : RZ/G3E
>
```

Please enter the any key from the console to continue.

### 5.2. Prepare for boot from the Serial Flash and eMMC

To boot from the eMMC, need to change the DIP switch setting.

Regarding the DIP switch configuration on the board, refer to [Related Document](#related-document) No.3.


## 6. Error case to handle

TBD 

## 7. Revision history

Describe the revision history of RZ/G3E DDR Tools.

### 7.1. v1.00

- First release.
- Support RZ/G3E EVK board.