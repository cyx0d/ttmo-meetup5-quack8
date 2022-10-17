// Compile With: gcc -o quack8 quack8.c
// For example use like this: echo -ne "\x01\x10\xff" | ./quack8

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <sys/mman.h>

#define LON	1
#define LOFF	0

#define M_REG	0
#define M_ARG1	455
#define M_ARG2	910

#define REG_A 	0x10
#define REG_B	0x20
#define REG_C	0x40
#define REG_D	0x80

#define CRASH_IP	"[!] The end ^^."
#define CRASH_OP	"[!] There's no such opcode for JIT."
#define CRASH_SET	"[!] Entered a missing number of bytes."
#define CRASH_REG	"[!] There's no such register for JIT."
#define CRASH_VAL	"[!] The number entered doesn't fit the range."

#define set_shit_nop(base) \
	((base ^ 0xF0) - (base & 0x0F))

#define set_shit_code4sda(base) \
	((((base & 0xF0) << 5) >> 4) + 6)

#define set_shit_code4add(base, set_number) \
	(!set_number) ? ((base & 0xF0) ^ 0x1F) + 1 : ((base & 0xF0) << 1)

#define set_shit_code4sub(base, set_number) \
	(!set_number) ? ((base & 0xF0) ^ 0x1F) + 1 : ((base & 0xF0) << 1) + (base & 0xB0)

#define set_shit_code4sdr(base, set_number) \
	(!set_number) ? ((base & 0xF0) ^ 0xF0) : ((base & 0xF0) ^ 0xD0)

#define set_shit_code4xor(base, set_number) \
	(!set_number) ? ((base & 0xF0) ^ 0xE0) : ((base & 0xF0) ^ 0x90)

#define set_shit_code4and(base, set_number) \
	(!set_number) ? ((base & 0xF0) ^ 0xE0) : ((base & 0xF0) ^ 0x80)

#define set_shit_code4or(base, set_number) \
	(!set_number) ? ((base & 0xF0) ^ 0xE0) : ((base & 0xF0) ^ 0xA0)

struct vm_memory {
	char inter_map[0x555];
	char *jit_code;
	size_t jit_code_size;
	size_t jit_code_count;

	struct vm_op {
		uint8_t op[0x555];
	} opc;

	struct vm_args {
		uint8_t arg1[0x555];
		uint8_t arg2[0x555];
	} arg;

	struct vm_regs {
		uint8_t ret[0x1c7];
		uint8_t a, b, c, d, i;
	} reg;

	struct vm_backup {
		uint8_t opc;
		uint8_t arg1, arg2;
		size_t count;
	} bak;
} vm;

void crash(char *dmsg)
{
	puts(dmsg);
	puts("[*] Goodbye!");
	exit(1337);
}

void check4sda(uint8_t reg[], uint8_t value[])
{
	for(size_t m = 0; m != vm.jit_code_size / 3; m++)
	{
		switch(reg[m])
		{
			case REG_A: vm.reg.ret[m] = 'a'; break;
			case REG_B: vm.reg.ret[m] = 'b'; break;
			case REG_C: vm.reg.ret[m] = 'c'; break;
			case REG_D: vm.reg.ret[m] = 'd'; break;
			default: crash(CRASH_REG); break;
		}

		if(!(value[m] >= 0 && value[m] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check4add(uint8_t reg[], uint8_t value[])
{
	for(size_t mm = 0; mm != vm.jit_code_size / 3; mm++)
	{
		switch(reg[mm])
		{
			case REG_A: vm.reg.ret[mm] = 'a'; break;
			case REG_B: vm.reg.ret[mm] = 'b'; break;
			case REG_C: vm.reg.ret[mm] = 'c'; break;
			case REG_D: vm.reg.ret[mm] = 'd'; break;
			default: crash(CRASH_REG); break;
		}
                                                  
		if(!(value[mm] >= 0 && value[mm] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check4sub(uint8_t reg[], uint8_t value[])
{
	for(size_t mmm = 0; mmm != vm.jit_code_size / 3; mmm++)
	{
		switch(reg[mmm])
		{
			case REG_A: vm.reg.ret[mmm] = 'a'; break;
			case REG_B: vm.reg.ret[mmm] = 'b'; break;
			case REG_C: vm.reg.ret[mmm] = 'c'; break;
			case REG_D: vm.reg.ret[mmm] = 'd'; break;
			default: crash(CRASH_REG); break;
		}
                                                  
		if(!(value[mmm] >= 0 && value[mmm] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check4sdr(uint8_t reg[], uint8_t value[])
{
	for(size_t mmmm = 0; mmmm != vm.jit_code_size / 3; mmmm++)
	{
		switch(reg[mmmm])
		{
			case REG_A: vm.reg.ret[mmmm] = 'a'; break;
			case REG_B: vm.reg.ret[mmmm] = 'b'; break;
			case REG_C: vm.reg.ret[mmmm] = 'c'; break;
			case REG_D: vm.reg.ret[mmmm] = 'd'; break;
			default: crash(CRASH_REG); break;
		}
		
		if(!(value[mmmm] >= 0 && value[mmmm] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check4xor(uint8_t reg[], uint8_t value[])
{
	for(size_t mmmmm = 0; mmmmm != vm.jit_code_size / 3; mmmmm++)
	{
		switch(reg[mmmmm])
		{
			case REG_A: vm.reg.ret[mmmmm] = 'a'; break;
			case REG_B: vm.reg.ret[mmmmm] = 'b'; break;
			case REG_C: vm.reg.ret[mmmmm] = 'c'; break;
			case REG_D: vm.reg.ret[mmmmm] = 'd'; break;
			default: crash(CRASH_REG); break;
		}
		
		if(!(value[mmmmm] >= 0 && value[mmmmm] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check4and(uint8_t reg[], uint8_t value[])
{
	for(size_t mmmmmm = 0; mmmmmm != vm.jit_code_size / 3; mmmmmm++)
	{
		switch(reg[mmmmmm])
		{
			case REG_A: vm.reg.ret[mmmmmm] = 'a'; break;
			case REG_B: vm.reg.ret[mmmmmm] = 'b'; break;
			case REG_C: vm.reg.ret[mmmmmm] = 'c'; break;
			case REG_D: vm.reg.ret[mmmmmm] = 'd'; break;
			default: crash(CRASH_REG); break;
		}
		
		if(!(value[mmmmmm] >= 0 && value[mmmmmm] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check4or(uint8_t reg[], uint8_t value[])
{
	for(size_t mmmmmmm = 0; mmmmmmm != vm.jit_code_size / 3; mmmmmmm++)
	{
		switch(reg[mmmmmmm])
		{
			case REG_A: vm.reg.ret[mmmmmmm] = 'a'; break;
			case REG_B: vm.reg.ret[mmmmmmm] = 'b'; break;
			case REG_C: vm.reg.ret[mmmmmmm] = 'c'; break;
			case REG_D: vm.reg.ret[mmmmmmm] = 'd'; break;
			default: crash(CRASH_REG); break;
		}
		
		if(!(value[mmmmmmm] >= 0 && value[mmmmmmm] <= 0xff))
			crash(CRASH_VAL);
	}
}

void check_code(uint8_t op_code[], uint8_t arg1[], uint8_t arg2[])
{
	for(size_t n = 0; n != vm.jit_code_size / 3; n++)
	{
		switch(op_code[n])
		{
			case 0x01: check4sda(arg1, arg2); break;
			case 0x02: check4add(arg1, arg2); break;
			case 0x04: check4sub(arg1, arg2); break;
			case 0x08: check4sdr(arg1, arg2); break;
			case 0x10: check4xor(arg1, arg2); break;
			case 0x20: check4and(arg1, arg2); break;
			case 0x40: check4or(arg1, arg2); break;
			default: crash(CRASH_OP); break;
		}
	}
}

void set_vm(char *byte_codes)
{
	if(!(vm.jit_code_size % 3))
	{
		for(size_t k = 0, l = 0 ; k != vm.jit_code_size ; k += 3, l++)
		{
			vm.opc.op[l]   = *(byte_codes + k + 0);
			vm.arg.arg1[l] = *(byte_codes + k + 1);
			vm.arg.arg2[l] = *(byte_codes + k + 2);
		}

		vm.reg.a = 0;
		vm.reg.b = 0;
		vm.reg.c = 0;
		vm.reg.d = 0;
		vm.reg.i = vm.bak.count + 1;
		vm.jit_code_count = 0;
		vm.bak.count = 0;
	}

	else crash(CRASH_SET);
}

void set_map(uint8_t v0, uint8_t v1, uint8_t v2)
{
	vm.inter_map[vm.bak.count +  M_REG] = v0;
	vm.inter_map[vm.bak.count + M_ARG1] = v1;
	vm.inter_map[vm.bak.count + M_ARG2] = v2;
}

void set_reg4sda(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a = value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b = value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c = value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d = value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4sda(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A: 
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sda(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = (op ^ op);
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sda(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = (op ^ op) + ((vm.reg.ret[ct] & 0xF0) >> 5);
			vm.jit_code[vm.jit_code_count++] = a2; 
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sda(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = (op ^ op) + (vm.reg.ret[ct] & 0x0D);
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sda(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = (op ^ op) + ((vm.reg.ret[ct] & 0x0F) >> 1);
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void set_reg4add(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a += value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b += value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c += value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d += value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4add(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A:
			vm.jit_code[vm.jit_code_count++] = set_shit_nop(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = ((vm.reg.ret[ct] & 0xF0) >> 5) + 0x01;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4add(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4add(vm.reg.ret[ct], 1) + 0x03;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4add(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4add(vm.reg.ret[ct], 1) + 0x01;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4add(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4add(vm.reg.ret[ct], 1) + 0x02;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void set_reg4sub(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a -= value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b -= value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c -= value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d -= value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4sub(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A:
			vm.jit_code[vm.jit_code_count++] = set_shit_nop(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = ((vm.reg.ret[ct] & 0xF0) >> 1) - 0x04;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sub(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sub(vm.reg.ret[ct], 1) + 0x0B;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sub(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sub(vm.reg.ret[ct], 1) + 0x09;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sub(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sub(vm.reg.ret[ct], 1) + 0x0A;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void set_reg4sdr(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a = value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b = value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c = value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d = value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4sdr(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A: 
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 1);
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 1) + 0x03;
			vm.jit_code[vm.jit_code_count++] = a2; 
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 1) + 0x01;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4sdr(vm.reg.ret[ct], 1) + 0x02;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void set_reg4xor(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a ^= value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b ^= value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c ^= value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d ^= value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4xor(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A:
			vm.jit_code[vm.jit_code_count++] = set_shit_nop(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = (set_shit_code4xor(vm.reg.ret[ct], 1) >> 2) & 0xF4;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4xor(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4xor(vm.reg.ret[ct], 1) + 0x03;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4xor(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4xor(vm.reg.ret[ct], 1) + 0x01;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4xor(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4xor(vm.reg.ret[ct], 1) + 0x02;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void set_reg4and(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a &= value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b &= value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c &= value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d &= value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4and(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A:
			vm.jit_code[vm.jit_code_count++] = set_shit_nop(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = ((set_shit_code4and(vm.reg.ret[ct], 1) >> 2) & 0xE0) + 0x04;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4and(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4and(vm.reg.ret[ct], 1) + 0x03;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4and(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4and(vm.reg.ret[ct], 1) + 0x01;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4and(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4and(vm.reg.ret[ct], 1) + 0x02;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void set_reg4or(uint8_t reg, uint8_t value)
{
	switch(reg)
	{
		case REG_A: vm.reg.a |= value; vm.reg.i = vm.bak.count; break;
		case REG_B: vm.reg.b |= value; vm.reg.i = vm.bak.count; break;
		case REG_C: vm.reg.c |= value; vm.reg.i = vm.bak.count; break;
		case REG_D: vm.reg.d |= value; vm.reg.i = vm.bak.count; break;
	}
}

void set_op4or(uint8_t op, uint8_t a1, uint8_t a2, size_t ct)
{
	switch(a1)
	{
		case REG_A:
			vm.jit_code[vm.jit_code_count++] = set_shit_nop(vm.reg.ret[ct]);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 1) >> 4;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_B:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 1) + 0x0B;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_C:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 1) + 0x09;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;

		case REG_D:
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 0);
			vm.jit_code[vm.jit_code_count++] = set_shit_code4or(vm.reg.ret[ct], 1) + 0x0A;
			vm.jit_code[vm.jit_code_count++] = a2;
			break;
	}
}

void jit_sda(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] SDA %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4sda(a1, a2);
	set_op4sda(op, a1, a2, ct);
}

void jit_add(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] ADD %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4add(a1, a2);
	set_op4add(op, a1, a2, ct);
}

void jit_sub(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] SUB %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4sub(a1, a2);
	set_op4sub(op, a1, a2, ct);
}

void jit_sdr(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] SDR %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4sdr(a1, a2);
	set_op4sdr(op, a1, a2, ct);
}

void jit_xor(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] XOR %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4xor(a1, a2);
	set_op4xor(op, a1, a2, ct);
}

void jit_and(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] AND %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4and(a1, a2);
	set_op4and(op, a1, a2, ct);
}

void jit_or(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf("[C] OR %c %#02x\n", vm.reg.ret[ct], a2);
	set_map(op, a1, a2);
	set_reg4or(a1, a2);
	set_op4or(op, a1, a2, ct);
}

void jit_instructions(uint8_t op, uint8_t a1, uint8_t a2, uint8_t ct)
{
	printf(
		"[R] a:%#x b:%#x c:%#x d:%#x i:%#x\n",
		vm.reg.a, vm.reg.b, vm.reg.c, vm.reg.d, ct
	);

	printf(
		"[I] op:%#x arg1:%#x arg2:%#x\n",
		op, a1, a2
	);

	if(op & 0x01)
		jit_sda(op, a1, a2, ct);

	if(op & 0x02)
		jit_add(op, a1, a2, ct);
	
	if(op & 0x04)
		jit_sub(op, a1, a2, ct);

	if(op & 0x08)
		jit_sdr(op, a1, a2, ct);

	if(op & 0x10)
		jit_xor(op, a1, a2, ct);

	if(op & 0x20)
		jit_and(op, a1, a2, ct);
	
	if(op & 0x40)
		jit_or(op, a1, a2, ct);
}

void jit_introduction(char *pure_code)
{
	set_vm(pure_code);
	check_code(vm.opc.op, vm.arg.arg1, vm.arg.arg2);

	while(vm.bak.count != (vm.jit_code_size / 3) + 1)
	{
		vm.bak.opc = vm.opc.op[vm.bak.count];
		vm.bak.arg1 = vm.arg.arg1[vm.bak.count];
		vm.bak.arg2 = vm.arg.arg2[vm.bak.count];

		jit_instructions(vm.bak.opc, vm.bak.arg1, vm.bak.arg2, vm.bak.count);
		
		vm.bak.count += 1;
	}
}

void main(int argc, char *argv[])
{
	puts("[+] This JIT is customized for TTMO. This we call \"Quack-8\".");
	puts("[+] To use this \"Quack-8\" you'll need to reverse binary.");
	puts("[+] Good luck!");

	vm.jit_code = mmap((void *)0x13370000, 0x1000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, 0, 0);
	memset(vm.jit_code, '\x90', 0x1000);
	vm.jit_code_size = read(0, vm.jit_code, 0x1000);
	
	jit_introduction(vm.jit_code);
	((void(*)())vm.jit_code)();
}
