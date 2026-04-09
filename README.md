# Finite-Field-Arithmetic

This repository contains a C implementation for Finite Field Arithmetic operations and Elliptic Curve operations over a large prime field. These implementations serve as the building blocks for the Finite Field Diffie-Hellman (FFDH) and Elliptic Curve Diffie-Hellman (ECDH) Key Exchange Protocols.

## Overview

The project is organized into two main modules:

- **Field-Arithmetic**: Implements arithmetic operations in a finite field F_p, where p is a 256-bit prime number.
- **EC-Arithmetic**: Implements elliptic curve operations over the same finite field.

## Prime Field

The implementations operate over the finite field defined by the prime p:

```
p = 0xF9EFDF7F5B834C613A04EACEDEC0BE55917213BEC2A08A1C28306FAD40E9
```

This prime is represented in multiple formats throughout the code:
- As a byte array (32 bytes, big-endian)
- As 9 limbs in base 2^30 (30-bit words)

## Modules

### Field-Arithmetic

Located in the `Field-Arithmetic/` directory, this module provides:

- **Basic Operations**: Addition and subtraction of field elements
- **Multiplication**: Using Barrett reduction for modular multiplication
- **Exponentiation**: Left-to-right exponentiation (square-and-multiply)
- **Conversions**: Between byte arrays and 30-bit limb representations

Key files:
- `add_mul.h/c`: Addition and subtraction operations
- `barrett.h/c`: Barrett modular reduction and multiplication
- `convert.h/c`: Base conversion utilities
- `expo_mult.h/c`: Exponentiation algorithms

### EC-Arithmetic

Located in the `EC-Arithmetic/` directory, this module provides elliptic curve operations:

- **Curve Parameters**: The curve is defined as y² = x³ + ax + b over F_p
- **Point Operations**: Point addition and doubling
- **Scalar Multiplication**: Multiple algorithms including Montgomery ladder
- **Inverse Computation**: Modular inverse using Fermat's little theorem

Key files:
- `ecc_base.h/c`: Basic elliptic curve operations and point structure
- `ecc_scal_mult.h/c`: Scalar multiplication algorithms

## Usage

This is a header-only library with accompanying C source files. To use in your project:

1. Include the appropriate header files
2. Compile the corresponding C files
3. Link them into your application

Example compilation:
```bash
gcc -c Field-Arithmetic/*.c EC-Arithmetic/*.c
gcc your_program.c *.o -o your_program
```

## Dependencies

- Standard C libraries (stdint.h, stdio.h, stdlib.h)
- No external dependencies required

## Security Notes

- This implementation is for educational/research purposes
- Not intended for production cryptographic use without thorough security review
- Timing attacks and other side-channel vulnerabilities have not been addressed
