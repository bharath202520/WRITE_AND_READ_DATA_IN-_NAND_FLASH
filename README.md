📌 Project Summary
==================
This project demonstrates how to interface the Micron MT29F1G01ABAFDWB 2Gb SPI NAND Flash chip with an Arduino Mega using the SPI interface. It includes features like:
Resetting the chip
Reading device ID
Checking and setting lock registers
Erasing blocks
Writing (programming) data
Reading data from pages
Checking status registers
It is designed for educational and testing purposes to help developers understand how to communicate with SPI NAND flash memory chips.

🛠️ Hardware Setup
==================
Component	Description
Microcontroller	Arduino Mega 2560 or anyone comtroller
Flash Chip	Micron MT29F1G01ABAFDWB (2Gb NAND)
Communication	SPI (Serial Peripheral Interface)
CS (Chip Select)	Pin 53 (defined in code as CS_PIN)

File Structure & Important Functions
====================================
✅ 1. reset()
Command: 0xFF
Purpose: Soft resets the NAND flash chip.
✅ 2. readDeviceID()
Command: 0x9F
Purpose: Reads the manufacturer and device ID.
✅ 3. to_check_lock_register()
Command: 0x0F (with address 0xA0)
Purpose: Reads the lock status register (check if blocks/pages are locked).
✅ 4. set_a_feacure_address()
Command: 0x1F (with address 0xA0)
Purpose: Unlocks blocks/pages by writing 0x00 to the block lock register.
✅ 5. erase_block(struct block_page d)
Command: 0x52
Purpose: Erases a 128KB block. Needed before writing.
✅ 6. write_enable()
Command: 0x06
Purpose: Sets the Write Enable Latch (WEL) bit. Required before any program or erase operations.
✅ 7. write_to_data(...)
Commands:
Load program data: 0x02
Execute program: 0x10
Purpose: Writes data into NAND flash memory.
✅ 8. readPage(...)
Commands:
Page Read: 0x13
Read from Cache: 0x03
Purpose: Reads data from a specific block and page.
✅ 9. printStatus(...)
Command: 0x0F with 0xC0
Purpose: Reads the status register and interprets key bits:
bit 0: OIP (Operation in progress)
bit 1: WEL (Write enable latch)
bit 2: E_FAIL (Erase fail)
bit 3: P_FAIL (Program fail)
| Bit | Name    | Meaning                         |
| --- | ------- | ------------------------------- |
| 0   | OIP     | 1 = Busy, 0 = Ready             |
| 1   | WEL     | 1 = Write enabled, 0 = Disabled |
| 2   | E\_FAIL | 1 = Erase failed                |
| 3   | P\_FAIL | 1 = Program failed              |

🔁 Known Issues & Debug Tips
============================
❗ Inconsistent Programming (Write Failures)
If P_FAIL (bit 3 of status register) is set:
Check if write_enable() was properly called before 0x02 and 0x10
Ensure the block was erased before writing
Avoid frequent repeated writes to the same page without erasing

❗ Status Register Returns 0x22
==============================
Means: 0x20 = P_FAIL, 0x02 = WEL
Indicates program failure after write was enabled
Check if you are trying to write to a non-erased page

💡 Future Improvements
======================
Add CRC or checksum verification after read
Implement bad block management
Add file system-style access (e.g., FAT-like layout)
