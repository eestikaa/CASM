; ----------------------------------------------------
; random.asm
; @brief        Generates a random 32-bit integer and returns it to the C function.
; Time-stamp counter used as the seed multiplier for EXTRA RANDOMNESS. Formula R(n+1) = (a*Rn + c) mod(m)
; r0 is the seed, a, c and m are magical constants and rn .... rn+whatever are the random numbers.
; @author   Rainer
; @date         17.01.15
; ----------------------------------------------------
 
%include "macros.inc"

section .data

; The values are directly ripped from http://rosettacode.org/wiki/Linear_congruential_generator#C
        randomConst dd 0x00003039 ; Magical constant 1
        multConst dd 0x41C64E6D ; Multiplication constant 1103515245 - apparently this is tried and true for 32-bit integers.
		maskConst dd 0x7FFFFFFF ; Integer mask for 32-bit application.
 
section .text
 
 
globalfunc _arand, seed:dword
	prologue
	
	push EBX
	push ESI
	
	rdtsc ; First we get read the time-stamp counter (rdtsc saves it in EDX and EAX registers)
	mov ebx, .seed ; Put the seed value into ebx register
	xor eax, ebx ; Even if the seed is 0x0H, then it won't break anything.. Hopefully
	and eax, [maskConst] ; Eliminate some leading ones...
	;Since multiply multiplies EAX with the given registry, we'll leave our seed in EAX.
	
	mov esi, [multConst]
	mul esi ; Multiply the seed with the constant.
	add eax, [randomConst] ; Add the random magical constant
	and eax, [maskConst]
	
	pop ESI
	pop EBX
	
	epilogue

globalfunc _astartswith, inpstr:dword, with:dword
	prologue
	push EBX
	push ESI
	
	mov ebx, .inpstr
	mov esi, .with
	mov bl, byte[ebx]
	mov bh, byte[esi]
	.if bl==bh
		mov eax, 1
	.elseif bl!=bh
		mov eax, 0
	.endif
	
	pop ESI
	pop EBX
	epilogue

	
	