# iopex
IO Port EXersizer

This small MSDOS program is intended to make debugging of ISA
bus hardware simpler. All it does is repeatedly read from
a range of IO ports to allow probing of address decoding
logic with an oscilloscope simpler.

This should be compiled using Borland C++ under MSDOS.

Usage
-----

Simply running the program will start reading from IO ports
0x340 to 0x34f (originally intended to help debugging the
Phillips CM153 clone card by Tech Tangents). Pressing any
key will abort and return you to dos.

It is possible to specify a new base address on the command
line (provided as a hexadecimal number) where it will start
reading the 16 IO ports starting from that address.
