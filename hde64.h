/*
 * Hacker Disassembler Engine 64
 * Copyright (c) 2008-2009, Vyacheslav Patkov.
 * All rights reserved.
 *
 * hde64.h: C/C++ header file
 *
 */

// Extended from original hde64.h AVX support by Fyyre
// Further extended with complete EVEX/VEX/XOP and 3-byte opcode support

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
		uint8_t  opcode3;

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

		// VEX prefix fields (AVX/AVX2)
		uint8_t  vex_r;
		uint8_t  vex_x;
		uint8_t  vex_b;
		uint8_t  vex_mmmmm;      // Main opcode map select
		uint8_t  vex_w;          // Operand size / promotion bit
		uint8_t  vex_vvvv;       // Additional register operand
		uint8_t  vex_l;          // Vector length (0=128-bit, 1=256-bit)
		uint8_t  vex_pp;         // Implied prefix (00=none, 01=66h, 10=F3h, 11=F2h)

		// EVEX prefix fields (AVX-512)
		uint8_t  evex_r_prime;   // R' bit (high bit of R)
		uint8_t  evex_x;         // X bit (high bit of X)
		uint8_t  evex_b;         // B bit (high bit of B)
		uint8_t  evex_mmmmm;     // Main opcode map select
		uint8_t  evex_w;         // Operand size / promotion bit
		uint8_t  evex_vvvv;      // Additional register operand
		uint8_t  evex_pp;        // Implied prefix (00=none, 01=66h, 10=F3h, 11=F2h)
		uint8_t  evex_z;         // Zeroing/merging control
		uint8_t  evex_ll;        // Vector length (00=128, 01=256, 10=512, 11=reserved)
		uint8_t  evex_b_flag;    // Broadcast/rounding/suppress all exceptions flag
		uint8_t  evex_v_prime;   // V' bit (high bit of V)

		// XOP prefix fields (AMD)
		uint8_t  xop_r;
		uint8_t  xop_x;
		uint8_t  xop_b;
		uint8_t  xop_mmmmm;      // Main opcode map select
		uint8_t  xop_w;          // Operand size / promotion bit
		uint8_t  xop_vvvv;       // Additional register operand
		uint8_t  xop_l;          // Vector length
		uint8_t  xop_pp;         // Implied prefix

		uint32_t flags;
	} hde64s;

	// Flags
#define F_MODRM           0x00000001u
#define F_SIB             0x00000002u
#define F_IMM8            0x00000004u
#define F_IMM16           0x00000008u
#define F_IMM32           0x00000010u
#define F_IMM64           0x00000020u
#define F_DISP8           0x00000040u
#define F_DISP16          0x00000080u
#define F_DISP32          0x00000100u
#define F_RELATIVE        0x00000200u

#define F_ERROR           0x00001000u
#define F_ERROR_OPCODE    0x00002000u
#define F_ERROR_LENGTH    0x00004000u
#define F_ERROR_LOCK      0x00008000u
#define F_ERROR_OPERAND   0x00010000u

	// Instruction encoding format flags
#define F_VEX             0x00020000u  // VEX prefix (AVX/AVX2)
#define F_EVEX            0x00040000u  // EVEX prefix (AVX-512)
#define F_XOP             0x00080000u  // XOP prefix (AMD)
#define F_OPCODE2         0x00100000u  // 2-byte opcode (0F prefix)
#define F_OPCODE3_38      0x00200000u  // 3-byte opcode (0F 38 prefix)
#define F_OPCODE3_3A      0x00400000u  // 3-byte opcode (0F 3A prefix)

	unsigned int hde64_disasm(const void* code, hde64s* hs);

#ifdef __cplusplus
}
#endif