.section .data
#ifndef TEST
#define TEST 19
#endif
			.macro linea
 		#if TEST==1
			.int 1,2,1,2
		#elif TEST==2
			.int -1,-2,-1,-2
		#elif TEST==3
			.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
		#elif TEST==4
			.int 0x80000000,0x80000000,0x80000000,0x80000000
		#elif TEST==5
			.int 0xffffffff,0xffffffff,0xffffffff,0xffffffff
		#elif TEST==6
			.int 2000000000,2000000000,2000000000,2000000000
		#elif TEST==7
			.int 3000000000,3000000000,3000000000,3000000000
		#elif TEST==8
			.int -2000000000,-2000000000,-2000000000,-2000000000
    #elif TEST==9
			.int -3000000000,-3000000000,-3000000000,-3000000000
    #elif TEST==10
			.int 0,2,1,1,1,1
    #elif TEST==11
			.int 1,2,1,1,1,1
  	#elif TEST==12
			.int 8,2,1,1,1,1
    #elif TEST==13
			.int 15,2,1,1,1,1
    #elif TEST==14
			.int 16,2,1,1,1,1
    #elif TEST==15
			.int 0,-2,-1,-1,-1,-1
    #elif TEST==16
			.int -1,-2,-1,-1,-1,-1
  	#elif TEST==17
			.int -8,-2,-1,-1,-1,-1
    #elif TEST==18
			.int -15,-2,-1,-1,-1,-1
    #elif TEST==19
			.int -16,-2,-1,-1,-1,-1
		#else
			.error "Definir TEST entre 1..19"
		#endif
			.endm
lista: .irpc i,1234
			  linea
			 .endr

longlista: .int (.-lista)/4
media: .quad 0
resto: .quad 0

formato: .ascii "media \t = %11d \t resto \t = %11d \n"
				 .asciz "\t = 0x %08x \t \t = 0x %08x\n"

.section .text
main: .global  main
	mov     $lista, %ebx		# Guardamos posición de la lista
	mov  longlista, %ecx		# Guardamos el tamaño de la lista
	call suma								# Llamada a la función suma

	mov  %rax, media		# Metemos los resultado de suma en resultado para luego mostrarlo
	mov  %rdx, resto

	mov   $formato, %rdi
	mov   media,%rsi
	mov   resto,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);

	mov  media, %rdi
	call _exit			# ==  exit(resultado)
	ret

suma:
	mov $0, %rdi
	mov $0, %ebp
	mov $0, %rsi

bucle:
	mov (%ebx, %ebp,4), %rax
	cqo

	add %rax, %rdi
	adc %rdx, %rsi

	inc %ebp
	cmp %ebp, %ecx
	jne bucle

	mov %rdi, %rax
	mov %rsi, %rdx

	idiv %rcx

	ret
