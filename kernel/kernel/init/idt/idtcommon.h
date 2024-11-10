#ifndef IDTCOMMON_H
#define IDTCOMMON_H

#include <stdint.h>

typedef struct
{
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, useless_esp, ebx, edx, ecx, eax;
	uint32_t int_num, err_code;
	uint32_t eip, cs, eflags, useresp, ss;
} __attribute__((packed)) stack_frame_t;
typedef void (*isr_t)(stack_frame_t*);

#endif