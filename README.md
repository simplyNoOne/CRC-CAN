# CRC-CAN Calculator

A high-performance CRC (Cyclic Redundancy Check) calculator for CAN (Controller Area Network) protocols, written in C.

## Overview

This project implements a CAN CRC calculator that computes the 16-bit CRC polynomial used in CAN bus communications. The implementation is optimized for performance and can handle up to 96 bits of input data.

## Building

### Prerequisites

- CMake 3.20 or later
- C compiler (GCC, Clang, or MSVC)

### Build Instructions

1. Navigate to the project directory:
   ```bash
   cd CRC-CAN
   ```

2. Create a build directory (if not already present):
   ```bash
   mkdir -p build
   cd build
   ```

3. Configure and build:
   ```bash
   cmake ..
   cmake --build . --config Release
   ```

4. Run the application:
   ```bash
   ./crc_app      # Linux/macOS
   crc_app.exe    # Windows
   ```

## Usage

1. **Enter bit sequence**: Input a sequence of binary digits (0s and 1s), up to 96 bits. Spaces are ignored.
   ```
   Example: 10101010 11110000 or 1010101011110000
   ```

2. **Enter repetitions**: Specify how many times to calculate the CRC (1 to 1,000,000,000).

3. **View results**: The program displays:
   - CRC result (16-bit hexadecimal value)
   - Calculation time in milliseconds
   - Number of repetitions performed

## Technical Details

### CRC Algorithm

The CRC calculation uses the CAN CRC polynomial (0x4599) with:
- 16-bit register size
- Bit-by-bit computation
- XOR with 0x4599 when the feedback bit is 1

### Optimization

The project is built with:
- Release mode for production performance
- Link-Time Optimization (LTO)
- Native architecture optimization (-march=native)
- Aggressive compiler flags (-O3, loop unrolling, frame pointer omission)

## Input Constraints

- Minimum bit length: 1 bit
- Maximum bit length: 96 bits
- Allowed characters: '0', '1', and spaces
- Maximum repetitions: 1,000,000,000
