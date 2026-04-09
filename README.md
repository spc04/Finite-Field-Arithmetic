# Finite-Field-Arithmetic
This holds the C implementation for Finite Field Arithmetic operations, along with the Elliptic Curve operations over a large prime field. These are the building blocks for the Finite Field and Elliptic Curve Diffie-Hellman Key Exchange Protocol, respectively.

C implementation of Field Arithmetic operations over GF(2^128) using Intel SIMD Intrinsic Instruction Sets. This project demonstrates efficient cryptographic operations including addition, subtraction, School-book and Karatsuba multiplication, and fast reduction modulo the polynomial (x^128 + x^7 + x^2 + x + 1).

## Overview

This repository contains C programs that leverage Intel's SIMD (Single Instruction, Multiple Data) intrinsics to perform high-performance finite field arithmetic operations. These operations are fundamental to modern cryptographic algorithms such as AES-GCM (Galois/Counter Mode) and other authenticated encryption schemes.

## Files

- **CpuCheck.c**: CPU feature detection utility that checks for support of various Intel instruction sets including AES, PCLMUL, SSE, MMX, and AMD-specific extensions.

- **pclMulDemo.c**: Demonstrates School-book multiplication of 128-bit polynomials using the PCLMUL (Carry-less Multiplication) instruction set.

- **pclMulDemo_KarRed.c**: Implements Karatsuba multiplication algorithm for faster polynomial multiplication and includes reduction modulo x^128 + x^7 + x^2 + x + 1.

- **xor.c**: Performance comparison between standard XOR operations and SSE-accelerated XOR for 128-bit blocks.

## Prerequisites

- GCC compiler with support for Intel intrinsics
- CPU supporting PCLMUL instruction set (Intel Westmere and later, AMD Bulldozer and later)
- Linux/Windows environment

## Compilation

### CpuCheck.c
```bash
gcc -o cpucheck CpuCheck.c
```

### pclMulDemo.c
```bash
gcc -o pclmul_demo -msse -mpclmul pclMulDemo.c
```

### pclMulDemo_KarRed.c
```bash
gcc -o karatsuba_demo -msse4.1 -mpclmul pclMulDemo_KarRed.c
```

### xor.c
```bash
gcc -o xor_demo -msse2 xor.c
```

## Usage

Run the compiled executables to see the demonstrations:

```bash
./cpucheck          # Check CPU instruction support
./pclmul_demo       # School-book multiplication demo
./karatsuba_demo    # Karatsuba multiplication and reduction demo
./xor_demo          # XOR performance comparison
```

## Mathematical Background

The implementations perform arithmetic in the finite field GF(2^128) with the irreducible polynomial:

p(x) = x^128 + x^7 + x^2 + x + 1

This polynomial is used in the GCM (Galois/Counter Mode) specification for AES-GCM authenticated encryption.

## Performance Notes

- PCLMUL instructions provide hardware-accelerated carry-less multiplication
- Karatsuba algorithm reduces multiplication complexity from O(n^2) to O(n^log2(3))
- SSE instructions enable parallel processing of 128-bit blocks
- These optimizations are crucial for high-performance cryptographic implementations

## References

- Intel Intrinsics Guide: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
- GCM Specification: NIST SP 800-38D
- Finite Field Arithmetic for Cryptography
