
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                               syscall.asm
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;                                                     Forrest Yu, 2005
; ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

%include "sconst.inc"

_NR_get_ticks       equ 0 ; 要跟 global.c 中 sys_call_table 的定义相对应！
_NR_disp_str        equ 1
_NR_process_sleep   equ 2
_NR_sem_p       equ 3
_NR_sem_v       equ 4
INT_VECTOR_SYS_CALL equ 0x90

; 导出符号
global	get_ticks
global	disp_str
global	process_sleep
global	sem_p
global	sem_v

bits 32
[section .text]

; ====================================================================
;                              get_ticks
; ====================================================================
get_ticks:
	mov ecx, [esp + 4]
	mov	eax, _NR_get_ticks
	int	INT_VECTOR_SYS_CALL
	ret

; ====================================================================
;                              disp_str
; ====================================================================
disp_str:
	mov ecx, [esp + 4]
	mov	eax, _NR_disp_str
	int	INT_VECTOR_SYS_CALL
	ret

; ====================================================================
;                              process_sleep
; ====================================================================
process_sleep:
	mov ecx, [esp + 4]
	mov	eax, _NR_process_sleep
	int	INT_VECTOR_SYS_CALL
	ret

; ====================================================================
;                              sem_p
; ====================================================================
sem_p:
	mov ecx, [esp + 4]
	mov	eax, _NR_sem_p
	int	INT_VECTOR_SYS_CALL
	ret

; ====================================================================
;                              sem_v
; ====================================================================
sem_v:
	mov ecx, [esp + 4]
	mov	eax, _NR_sem_v
	int	INT_VECTOR_SYS_CALL
	ret
