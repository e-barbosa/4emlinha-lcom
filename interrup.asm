CPU 686
BITS 32

%define EOI 20h ; define EOI como valendo 0x20
%define PIC1_CMD 20h
global _time_tick
global _sec_tick
global _t0_isr ; o handler tamb�m deve ser global, para ser instalado

section .data ; .data � a zona de dados inicializados
_time_tick dd 0
_sec_tick dd 0
freq: dd 1000

section .text ; .text � a zona de c�digo
_t0_isr: ; deve ser global para ser acedida em m�dulos escritos em C
		push eax ; todos os registos utilizados na rotina
		inc dword[_time_tick] ; instru��es da rotina
		dec dword[freq]
		
		jnz fim
		inc dword[_sec_tick]
		mov dword[freq], 1000
		
fim:
		mov al, EOI ; sinaliza EOI para o PIC-1
		out PIC1_CMD, al
		pop eax ; todos os registos guardados
		iretd
END ; fim de c�digo fonte assembly