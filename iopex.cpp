/* IOPEX - IO Port EXerciser

Copyright 2022 Majenko Technologies

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, 
   this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, 
   this list of conditions and the following disclaimer in the documentation 
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors 
   may be used to endorse or promote products derived from this software 
   without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

Usage:

iopex
iopex <base port>
iopex <start>-<end>
iopex <start>+<num>

If the base port is omitted a default value (0x340) is used. The port should
be specified as a hexadecimal value.

You can specify a start and end port number, separated by a -, or a start
port and the number of ports to scan separated by a +.

For example the default value can be represented as either 340-34f or as
340+10 - note all values are hexadecimal, and a leading 0x is optional.

This program will read from the block of 16 IO ports starting at the
specified base port repeatedly until a key is pressed to terminate the
program.

*/


#include <dos.h>
#include <bios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parse_range(char *in, int *start, int *end) {
	char *minus = strstr(in, "-");
	char *plus = strstr(in, "+");

	if (minus != NULL) {
		char *right = minus + 1;
		*minus = 0;
		*start = strtoul(in, NULL, 16);
		*end = strtoul(right, NULL, 16);
		return;
	}

	if (plus != NULL) {
		char *right = plus + 1;
		*plus = 0;
		*start = strtoul(in, NULL, 16);
		*end = *start + strtoul(right, NULL, 16) - 1;
		return;
	}

	*start = 0x340;
	*end = 0x34f;
}

int main(int argc, char **argv) {
        int start = 0x340;
		int end = 0x34f;
        if (argc == 2) {
			parse_range(argv[1], &start, &end);
        }

        printf("Twiddling IO ports in the range 0x%03x - 0x%03x\n",
                start, end);
        printf("Press any key to stop\n");
        while (bioskey(1) == 0) {
                for (int i = start; i <= end; i++) {
                        inportb(i);
                }
        }
        bioskey(0);
        
        printf("Thank you - have a nice day.\n");
        return 0;
}
