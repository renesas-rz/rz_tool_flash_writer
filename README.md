# README of the RZ/G2L DDR Tools

<Div Align="right">
Renesas Electronics Corporation

Jul-30-2026
</Div>

The RZ/G2L Flash Writer is sample software for Renesas RZ/G2L MPU. It downloads binary images from a host PC via SCIF or USB and writes those images to Serial NOR Flash or eMMC.

The RZ/G2L DDR Tools, based on the RZ/G2L Flash Writer, are essential utilities provided by Renesas to help developers configure, tune, and verify DDR3L/DDR4 memory operation on the RZ/G2L MPU.

## 1. Overview

This document explains the RZ/G2L DDR Tools for Renesas RZ/G2L MPU, which is based on the RZ/G2L Flash Writer.

The RZ/G2L DDR Tools is downloaded from the Host PC via SCIF by boot ROM.

And the RZ/G2L DDR Tools loads the DDR parameters from the Host PC via SCIF and provides functions such as logging training messages, checking DQ margins, and running stress tests.

[Chapter 2](#2-operating-environment) describes the operating environment.

[Chapter 3](#3-software) describes the software.

[Chapter 4](#4-how-to-build-the-rzg2l-ddr-tools) explains example of how to build the RZ/G2L DDR Tools.

[Chapter 5](#5-how-to-run-the-rzg2l-ddr-tools) explains example of how to perform the RZ/G2L DDR Tools.

[Chapter 6](#6-error-case-to-handle) explains how to handle error case.

[Chapter 7](#7-revision-history) explains revision history.

> [!NOTE]
>
> This sample software does not support the file system. Therefore, it can only write raw images to Serial NOR Flash.

### 1.1. License

BSD-3-Clause (please see file [LICENSE.md](LICENSE.md) for the details)

### 1.2. Notice

The RZ/G2L DDR Tools is distributed as a sample software from Renesas without any warranty or support.

### 1.3. Contributing

To contribute to this layer, you should email patches to renesas-rz@renesas.com. Please send .patch files as email attachments, not embedded in the email body.

### 1.4. References

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

| Name         | Note                                               |
| ------------ | -------------------------------------------------- |
| Target board | RZ/G2L SMARC PMIC Evaluation Kit (RZ/G2L PMIC EVK) |
| Host PC      | Ubuntu Desktop 22.04(64bit) or later               |

The following table shows Serial Flash and eMMC support for RZ/G2L PMIC EVK.

#### Serial Flash / eMMC support status of RZ/G2L PMIC EVK

| Read/Write the Serial Flash | Boot from the Serial Flash | Read/Write the eMMC | Boot from the eMMC |
| --------------------------- | -------------------------- | ------------------- | ------------------ |
| Not supported               | Not supported              | Supported           | Supported          |

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
- Step-by-Step Training Message Log.
- Run the DQ Margin Checker.
- Run the stress checker.
- Change the SCIF baud rate setting.
- Display the command help.

### 3.2. Option setting

The RZ/G2L DDR Tools support the following build options.

#### 3.2.1. BOARD

| BOARD            | BOARD setting                                                 |
| ---------------- | ------------------------------------------------------------- |
| RZG2L_SMARC_PMIC | Generate binary that works on RZ/G2L PMIC EVK board           |

#### 3.2.2. SERIAL_FLASH

Select from the following table according to the Serial Flash writing function.

If this option is not selected, the default value is ENABLE (In RZ/G2L DDR Tools, this option is disabled by a script).

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
| EM_DCID                              | Display the CID registers of eMMC.                                                                 |
| EM_DCSD                              | Display the CSD registers of eMMC.                                                                 |
| EM_DECSD                             | Display the EXT_CSD registers of eMMC.                                                             |
| EM_SECSD                             | Modify the EXT_CSD registers of eMMC.                                                              |
| EM_W                                 | Write to the S-record format images to the user data area of eMMC, and the boot partition of eMMC. |
| EM_WB                                | Write to the raw binary images to the user data area of eMMC, and the boot partition of eMMC.      |
| EM_E                                 | Erase the user data area of eMMC, and the boot partition of eMMC.                                  |
| DDRP                                 | Store DDR parameters into internal SRAM.                                                           |
| DDR_S [sadr] [eadr] {loop}           | Simple write-then-read checking of DDR.                                                            |
| DDR_RB [sadr] [eadr] {loop}          | Random data write-then-read checking of DDR.                                                       |
| DDR_FB [sadr] [eadr] [data] {loop}   | Fixed data write-then-read checking of DDR.                                                        |
| DQ                                   | DQ to DQS timing margin check.                                                                     |
| SUP                                  | Change the SCIF baud rate setting.                                                                 |
| SUD                                  | Change the SCIF baud rate setting.                                                                 |
| RESET                                | Perform RESET of the CPU.                                                                          |
| H                                    | Display the command help.                                                                          |

#### 3.3.1. Display the CID registers command

This command displays the contents of the CID registers of the eMMC.

The following shows the procedure of this command.

```text
>EM_DCID

[CID Field Data]
[127:120]  MID  0x13
[113:112]  CBX  0x01
[111:104]  OID  0x4E
[103: 56]  PNM  0x47314D31354D
[ 55: 48]  PRV  0x10
[ 47: 16]  PSN  0x1A5959BA
[ 15:  8]  MDT  0xC8
[  7:  1]  CRC  0x00
```

#### 3.3.2. Display the CSD registers command

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

#### 3.3.3. Display the EXT_CSD registers command

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

#### 3.3.4. Modify the EXT_CSD registers of eMMC command

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

#### 3.3.5. Write to the S-record format images to the eMMC

> [!NOTE]
>
> In case `DDR_PARAM_LOAD` is enabled (refer to [4.3. Build the RZ/G2L DDR Tools](#43-build-the-rzg2l-ddr-tools)). Please make sure the DDR parameters are loaded successfully (refer to [3.3.7. Store DDR parameters into internal SRAM](#337-store-ddr-parameters-into-internal-sram)).

This command writes the S-record format image to any partition of the eMMC.

##### Example of writing data for the eMMC boot

| Filename                         | eMMC Save Partition | eMMC Save Sectors | Program Top Address | Description                                 |
| -------------------------------- | ------------------- |-------------------|---------------------|---------------------------------------------|
| bl2_bp_mmc-smarc-rzg2l_pmic.srec | boot partition1     | H'00000001        | H'11E00             | Loader                                      |
| fip-smarc-rzg2l_pmic.srec        | boot partition1     | H'00000100        | H'00000             | ARM Trusted Firmware and U-boot in FIP file |

The following shows the procedure of this command.
The values must be entered as **hexadecimal**.
Please enter the start sector number of the write image in hexadecimal. Sector size is 512 bytes.
Please enter the program top address of the write image in hexadecimal.

```text
>EM_W
EM_W Start --------------
---------------------------------------------------------
Please select,eMMC Partition Area.
0:User Partition Area : 62160896 KBytes
eMMC Sector Cnt : H'0 - H'0768FFFF
1:Boot Partition 1 : 32256 KBytes
eMMC Sector Cnt : H'0 - H'0000FBFF
2:Boot Partition 2 : 32256 KBytes
eMMC Sector Cnt : H'0 - H'0000FBFF
---------------------------------------------------------
  Select area(0-2)>1                                        <<<< Enter "1" here
-- Boot Partition 1 Program -----------------------------
Please Input Start Address in sector :1                     <<<< Enter "1" here
Please Input Program Start Address : 11E00                  <<<< Enter "11E00" here
Work RAM(H'50000000-H'50FFFFFF) Clear....
please send ! ('.' & CR stop load)
```

Please download the write image in S-record format.

```text
SAVE -FLASH.......
EM_W Complete!
```

Image writing has been completed.

#### 3.3.6. Erase the eMMC

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

#### 3.3.7. Store DDR parameters into internal SRAM

> [!NOTE]
>
> To use this feature. Please enable `DDR_PARAM_LOAD` when building the RZ/G2L DDR Tools (refer to [4.3. Build the RZ/G2L DDR Tools](#43-build-the-rzg2l-ddr-tools)).

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
Send DDR parameter file (binary) from PC. You can use this sample file "DDR_Parameters_Normal.bin" (refer to [4.4. Generate DDR parameters (*.bin)](#44-generate-ddr-parameters-bin)). After the DDR parameters are loaded, Eye Opening Tool runs automatically. The raw test result like below is output on the terminal.

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

#### 3.3.8. Simple write-then-read checking of DDR

> [!NOTE]
>
> To use this feature. Please enable `DDR_PARAM_LOAD` when building the RZ/G2L DDR Tools (refer to [4.3. Build the RZ/G2L DDR Tools](#43-build-the-rzg2l-ddr-tools)) and make sure the DDR parameters are loaded successfully (refer to [3.3.7. Store DDR parameters into internal SRAM](#337-store-ddr-parameters-into-internal-sram)).

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

#### 3.3.9. Random data write-then-read checking of DDR

> [!NOTE]
>
> To use this feature. Please enable `DDR_PARAM_LOAD` when building the RZ/G2L DDR Tools (refer to [4.3. Build the RZ/G2L DDR Tools](#43-build-the-rzg2l-ddr-tools)) and make sure the DDR parameters are loaded successfully (refer to [3.3.7. Store DDR parameters into internal SRAM](#337-store-ddr-parameters-into-internal-sram)).

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

#### 3.3.10. Fixed data write-then-read checking of DDR

> [!NOTE]
>
> To use this feature. Please enable `DDR_PARAM_LOAD` when building the RZ/G2L DDR Tools (refer to [4.3. Build the RZ/G2L DDR Tools](#43-build-the-rzg2l-ddr-tools)) and make sure the DDR parameters are loaded successfully (refer to [3.3.7. Store DDR parameters into internal SRAM](#337-store-ddr-parameters-into-internal-sram)).

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

#### 3.3.11. DQ to DQS timing margin check

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

#### 3.3.12. Change the SCIF baud rate setting

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

#### 3.3.13. Display the command help

Displays a description of the commands.

The following shows the procedure of this command.

```text
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

```bash
$ export DDR_TOOLS_DIR=${PWD}/DDR_Tools
$ mkdir -pv ${DDR_TOOLS_DIR}
$ cd ${DDR_TOOLS_DIR}
$ git clone https://github.com/renesas-rz/rz_tool_flash_writer.git
$ cd rz_tool_flash_writer/
$ git checkout v1.2.0_RZ/G2L
```

### 4.2. Prepare the compiler

ARM toolchain:

```bash
$ cd ${DDR_TOOLS_DIR}
$ wget https://developer.arm.com/-/media/Files/downloads/gnu-a/10.3-2021.07/binrel/gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar.xz
$ tar xvf gcc-arm-10.3-2021.07-x86_64-aarch64-none-elf.tar.xz
```

### 4.3. Build the RZ/G2L DDR Tools

S-record file will be built by the following command.

```bash
$ cd ${DDR_TOOLS_DIR}/rz_tool_flash_writer/scripts/
$ ./build_flash_writer_g2l.sh RZG2L_SMARC_PMIC
```

> [!NOTE]
>
> DDR features and Training Message log are enabled by default in `build_flash_writer_g2l.sh`.
>
> To disable them, set `DDR_PARAM_LOAD=DISABLE` and `DDR_DEBUG=0` in the build script (`build_flash_writer_g2l.sh`), or remove these options before building the RZ/G2L DDR Tools.

Output image will be available in the following directory:

* ${DDR_TOOLS_DIR}/rz_tool_flash_writer/AArch64_output/Flash_Writer_SCIF_RZG2L_SMARC_PMIC_DDR4_2GB_1PCS.mot

### 4.4. Generate DDR parameters (*.bin)

Run the following command to convert the DDR parameters source code in the flash_writer repository (*.c files) into a binary file:

```bash
$ cd ${DDR_TOOLS_DIR}/rz_tool_flash_writer/scripts/
$ ./c2bin.sh ${DDR_TOOLS_DIR}/rz_tool_flash_writer/ddr/g2l/param_mc_C-011_D4-01-1.c ${DDR_TOOLS_DIR}/rz_tool_flash_writer/ddr/common/param_swizzle_T1bc.c
```

A binary file will be generated at the following path:
* ${DDR_TOOLS_DIR}/rz_tool_flash_writer/scripts/DDR_Parameters.bin

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

- AArch64_output/Flash_Writer_SCIF_RZG2L_SMARC_PMIC_DDR4_2GB_1PCS.mot

After the transfer has succeeded, the following log will be shown.

```text
Flash writer for RZ/G2 Series Vx.xx MMM.DD,YYYY
Product Code : RZ/G2L
> 
```

Please enter the any key from the console to continue.

### 5.2. Prepare for boot from the Serial Flash and eMMC

To boot from the eMMC, need to change the DIP switch setting.

Regarding the DIP switch configuration on the board, refer to [Related Document](#related-document) No.4.


## 6. Error case to handle

TBD 

## 7. Revision history

Describe the revision history of RZ/G2L DDR Tools.

| Revision | Date        |  Descriptions                                                                  |
| -------- | ----------- | ------------------------------------------------------------------------------ |
| v1.0.0   | Jul-25-2025 | - First release.<br>- Support RZ/G2L PMIC EVK board.                           |
| v1.1.0   | Mar-06-2026 | - Use a shared .mot file for both eMMC and DDR Tools.<br>- Add helper scripts. |
| v1.2.0   | Jul-30-2026 | - Add DDR_PARAM_LOAD and DDR_DEBUG options.                                    |
