CPU 686
BITS 32

%define DATA_REG 0x60
%define EOI 0x20
%define PIC1_CMD 0x20


section .data

global _kbd_isr

extern _keys_queue
extern _queuePut


section .text

_kbd_isr:
	push eax
	
	xor eax, eax
	in al, DATA_REG

	push eax
	push _keys_queue
	call _queuePut
	add esp, 8
	
;fim:
	mov al, EOI
	out PIC1_CMD, al

	pop eax
	iretd
END