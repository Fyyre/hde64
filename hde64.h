/*
 * Hacker Disassembler Engine 64
 * Copyright (c) 2008-2009, Vyacheslav Patkov.
 * All rights reserved.
 *
 * hde64.h: C/C++ header file
 *
 */

// Extended from original hde64.h AVX support by Fyyre

#pragma once

#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct {
		uint8_t  len;

		uint8_t  p_rep;
		uint8_t  p_lock;
		uint8_t  p_seg;
		uint8_t  p_66;
		uint8_t  p_67;
		uint8_t  rex;
		uint8_t  rex_w;
		uint8_t  rex_r;
		uint8_t  rex_x;
		uint8_t  rex_b;

		uint8_t  opcode;
		uint8_t  opcode2;

		uint8_t  modrm;
		uint8_t  modrm_mod;
		uint8_t  modrm_reg;
		uint8_t  modrm_rm;

		uint8_t  sib;
		uint8_t  sib_scale;
		uint8_t  sib_index;
		uint8_t  sib_base;

		union {
			uint8_t  imm8;
			uint16_t imm16;
			uint32_t imm32;
			uint64_t imm64;
		} imm;

		union {
			uint8_t  disp8;
			uint16_t disp16;
			uint32_t disp32;
		} disp;

		uint32_t flags;
	} hde64s;

	// Flags (unchanged)
#define F_MODRM         0x00000001u
#define F_SIB           0x00000002u
#define F_IMM8          0x00000004u
#define F_IMM16         0x00000008u
#define F_IMM32         0x00000010u
#define F_IMM64         0x00000020u
#define F_DISP8         0x00000040u
#define F_DISP16        0x00000080u
#define F_DISP32        0x00000100u
#define F_RELATIVE      0x00000200u

#define F_ERROR         0x00001000u
#define F_ERROR_OPCODE  0x00002000u
#define F_ERROR_LENGTH  0x00004000u
#define F_ERROR_LOCK    0x00008000u
#define F_ERROR_OPERAND 0x00010000u

	unsigned int hde64_disasm(const void* code, hde64s* hs);

#ifdef __cplusplus
}
#endif