/*
 * SPDX-FileCopyrightText: 2020 Efabless Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * SPDX-License-Identifier: Apache-2.0
 */

#include <defs.h>

void putchar_uart(char c)
{
	if (c == '\n')
		putchar_uart('\r');
    while (reg_uart_txfull == 1);
	reg_uart_data = c;
}

void print(const char *p)
{
	while (*p)
		putchar_uart(*(p++));
}

void print_hex(uint32_t v, int digits)
{
	for (int i = digits - 1; i >= 0; i--) {
		char c = "0123456789abcdef"[(v >> (4*i)) & 15];
		putchar_uart(c);
	}
}

void print_dec(uint32_t v)
{
	if (v >= 2000) {
		print("OVER");
		return;
	}
	else if (v >= 1000) { putchar_uart('1'); v -= 1000; }
	else putchar_uart(' ');

	if 	(v >= 900) { putchar_uart('9'); v -= 900; }
	else if	(v >= 800) { putchar_uart('8'); v -= 800; }
	else if	(v >= 700) { putchar_uart('7'); v -= 700; }
	else if	(v >= 600) { putchar_uart('6'); v -= 600; }
	else if	(v >= 500) { putchar_uart('5'); v -= 500; }
	else if	(v >= 400) { putchar_uart('4'); v -= 400; }
	else if	(v >= 300) { putchar_uart('3'); v -= 300; }
	else if	(v >= 200) { putchar_uart('2'); v -= 200; }
	else if	(v >= 100) { putchar_uart('1'); v -= 100; }
	else putchar_uart('0');

	if 	(v >= 90) { putchar_uart('9'); v -= 90; }
	else if	(v >= 80) { putchar_uart('8'); v -= 80; }
	else if	(v >= 70) { putchar_uart('7'); v -= 70; }
	else if	(v >= 60) { putchar_uart('6'); v -= 60; }
	else if	(v >= 50) { putchar_uart('5'); v -= 50; }
	else if	(v >= 40) { putchar_uart('4'); v -= 40; }
	else if	(v >= 30) { putchar_uart('3'); v -= 30; }
	else if	(v >= 20) { putchar_uart('2'); v -= 20; }
	else if	(v >= 10) { putchar_uart('1'); v -= 10; }
	else putchar_uart('0');

	if 	(v >= 9) { putchar_uart('9'); v -= 9; }
	else if	(v >= 8) { putchar_uart('8'); v -= 8; }
	else if	(v >= 7) { putchar_uart('7'); v -= 7; }
	else if	(v >= 6) { putchar_uart('6'); v -= 6; }
	else if	(v >= 5) { putchar_uart('5'); v -= 5; }
	else if	(v >= 4) { putchar_uart('4'); v -= 4; }
	else if	(v >= 3) { putchar_uart('3'); v -= 3; }
	else if	(v >= 2) { putchar_uart('2'); v -= 2; }
	else if	(v >= 1) { putchar_uart('1'); v -= 1; }
	else putchar_uart('0');
}

void print_digit(uint32_t v)
{
    v &= (uint32_t)0x000F;

    if (v == 9) { putchar_uart('9'); }
    else if (v == 8) { putchar_uart('8'); }
    else if (v == 7) { putchar_uart('7'); }
    else if (v == 6) { putchar_uart('6'); }
    else if (v == 5) { putchar_uart('5'); }
    else if (v == 4) { putchar_uart('4'); }
    else if (v == 3) { putchar_uart('3'); }
    else if (v == 2) { putchar_uart('2'); }
    else if (v == 1) { putchar_uart('1'); }
    else if (v == 0) { putchar_uart('0'); }
    else if (v == 10) { putchar_uart('a'); }
    else if (v == 11) { putchar_uart('b'); }
    else if (v == 12) { putchar_uart('c'); }
    else if (v == 13) { putchar_uart('d'); }
    else if (v == 14) { putchar_uart('e'); }
    else if (v == 15) { putchar_uart('f'); }
    else putchar_uart('*');
}
