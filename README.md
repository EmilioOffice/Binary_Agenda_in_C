# Binary Agenda in C

This repository is part of my formative years as a Software Engineering student. It showcases the implementation of problem-solving techniques, analytical thinking, and the business logic behind a **binary-based agenda** (contact management system) in C. The primary goal of this project is **educational practice** and **skill acquisition**—it is **not** intended to be a fully polished product.

> **Disclaimer**: This code is provided “as is” for learning purposes. The author(s) bear no responsibility for any misuse or damages resulting from its use.

---

## Overview

- **Project Purpose**: Demonstrate how to build a basic agenda (contact manager) in C using binary file storage.  
- **Key Topics**:  
  - C language fundamentals (structs, pointers, file I/O)  
  - Binary file operations (`fwrite`, `fread`, etc.)  
  - Simple CLI menu and user interaction  
  - Memory allocation and array management

---

## Authors' Rights

All code in this repository is protected under the rights of the author(s). If you wish to reuse or modify this code beyond personal learning or demonstration, please **contact the author** for permission. Any unauthorized commercial use is strictly prohibited. Emilio Marquez <emiliomrqzoff@gmail.com>

---

## Recommended Compiler and Environment

- **GCC (MinGW-w64)** on Windows, or **GCC/Clang** on Linux/Mac.  
- You can also use other C compilers, but **MinGW-w64** on Windows is commonly recommended for ease of setup.  
- The code may not run properly on certain IDEs if not configured for correct paths (e.g., CLion) without additional setup.

---

## How to Compile and Run

1. **Clone or Copy the Repository**  
   - You can copy and paste the code directly into your environment, or clone the repository if multiple files exist.
    ```bash
    git clone https://github.com/EmilioOffice/Binary_Agenda_in_C.git

2. **Open a Terminal/Command Prompt**  
   - Ensure you have a C compiler (e.g., GCC) installed.
   ```bash
   gcc --version

3. **Compile the Program** (example with GCC):
   - You can name the .exe file how you prefer for simplicity it is stated as "binary_agenda"
   ```bash
   gcc Binary_Agenda.c -o binary_agenda

4. **Execute the Program** :
   - Run your .exe file that was just compiled in this example "binary_agenda.exe"
   ```bash
   /Binary_Agenda_in_C/binary_agenda.exe
