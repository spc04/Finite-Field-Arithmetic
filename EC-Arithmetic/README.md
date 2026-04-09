# EC-Arithmetic Module

This module implements elliptic curve operations over the finite field F_p.

## Elliptic Curve

The curve is defined by the equation:
```
y² = x³ + ax + b
```

Where a and b are fixed curve parameters, and operations are performed modulo p.

## Point Representation

Points on the curve are represented using the `point` structure:
```c
typedef struct {
    uint32_t x[9];
    uint32_t y[9];
} point;
```

Both x and y coordinates are field elements in 30-bit limb representation.

## Files

- `ecc_base.h/c`: Basic elliptic curve operations (addition, doubling, inverse)
- `ecc_scal_mult.h/c`: Scalar multiplication algorithms

## Key Functions

### Basic Operations (`ecc_base.h`)
- `point addition(point P, point Q)`: Point addition on the elliptic curve
- `point doubling(point P)`: Point doubling operation
- `void inv(uint32_t *a, uint32_t *a1)`: Modular inverse computation
- `int isEqual(uint32_t *a, uint32_t *b)`: Check if two field elements are equal
- `void printPoint(point P)`: Print a point's coordinates

### Scalar Multiplication (`ecc_scal_mult.h`)
- `point ECC_L2R_mult(point P, uint8_t *n)`: Left-to-right scalar multiplication
- `point ECC_R2L_mult(point P, uint8_t *n)`: Right-to-left scalar multiplication
- `point ECC_montgomeryLadder_mult(point P, uint8_t *n)`: Montgomery ladder scalar multiplication

## Usage

Include the headers and compile the source files. Points should be initialized with valid coordinates on the curve. The Montgomery ladder method is recommended for cryptographic applications due to its resistance to timing attacks.

