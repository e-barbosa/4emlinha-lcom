#include "ints.h"

/** Installs the ASM written function 'irq_func' as the interrupt
 * handler associated with interrupt 'irq', updating the 'old_irq'
 * structure with the current interrupt handler.  Returns 0 on success
 * or -1 on error, in which case the original interrupt handler
 * remains installed.
 * 
 * See reinstall_asm_irq_handler() to reinstall the original handler.
 */
int install_asm_irq_handler(int irq, void (*irq_func)(void), _go32_dpmi_seginfo *old_irq){
				
	int vector = IRQ_VECTOR(irq);
	_go32_dpmi_seginfo new_irq;
	
	if (_go32_dpmi_get_protected_mode_interrupt_vector(vector, old_irq))
		return -1;
	
	new_irq.pm_selector = _go32_my_cs();
	new_irq.pm_offset = (unsigned long)irq_func;
	
	if(_go32_dpmi_set_protected_mode_interrupt_vector(vector, &new_irq)) 
		return -1;
	
	return 0;
}


void reinstall_asm_irq_handler(int irq, _go32_dpmi_seginfo *old_irq){
	int vector = IRQ_VECTOR(irq);
	_go32_dpmi_set_protected_mode_interrupt_vector(vector, old_irq);
}



void enable_irq(int irq)
{
	unsigned char in;
	
	if (irq < 8)
	{
		in = inportb(PIC1_MASK);
		outportb(PIC1_MASK, in & ~ IRQ_MASK_BIT(irq) );
	}
	else
	{
		in = inportb(PIC2_MASK);
		outportb(PIC2_MASK, in & ~ IRQ_MASK_BIT(irq) );
	}

}

int disable_irq(int irq)
{
	unsigned char in;
	
	if (irq < 8)
	{
		in = inportb(PIC1_MASK);
		outportb(PIC1_MASK, in |  IRQ_MASK_BIT(irq) );
	}
	else
	{
		in = inportb(PIC2_MASK);
		outportb(PIC2_MASK, in | IRQ_MASK_BIT(irq) );
	}
	
	return in;
}
