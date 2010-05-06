CPU 686
BITS 32

%define EOI 20h ; define EOI como valendo 0x20
%define PIC1_CMD 20h
global _time_tick
global _sec_tick
global _programa

section .data ; .data é a zona de dados inicializados
_time_tick dd 0
_sec_tick dd 0
freq dd 1000

section .text ; .text é a zona de código
_programa:
	push eax;
	inc DWORD[_time_tick]
	dec DWORD[freq]
	jnz fim
	
	inc DWORD[_sec_tick]
	mov DWORD[freq], 1000
	
fim:  
	mov al, EOI ; sinaliza EOI para o PIC-1
	out PIC1_CMD, al
	
	pop eax
	iretd
END	; fim de código fonte assembly

