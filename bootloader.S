	.code16
	.global _start

_start:
	movb $0x0e, %ah             # set BIOS mode to tty # %ah <- 0x0e

	movw $0x00, %bx             # i <- 0
loop:
	movb hello_msg(%bx), %al    # %al <- hello_msg[i]
	                            # we need to use the linker arguments so the
	                            # binary is correctly located at memory and
	                            # offsets are correctly calculated (-Ttext=)
	cmp $0x00, %al              # if (%al == 0) # message is null-terminated
	je halt                     #     goto halt
	int $0x10                   # call BIOS video service
	add $0x01, %bx              # i <- i + 1
	jmp loop

halt:
	hlt                         # interruptions can awake the processor
	jmp halt                    # so we make it go to halt again

hello_msg:
	.string "Hello x86 bare-metal + assembly world!" # GAS makes it null-terminated

padding:
	.fill 510 - (. - _start), 1, 0 # 510 = 512 - 2 bytes from signature

signature:
	.word 0xaa55                # BIOS boot signature
