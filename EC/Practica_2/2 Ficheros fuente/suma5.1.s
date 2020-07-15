.section .data
#ifndef TEST
#define TEST 9
#endif
			.macro linea
 		#if TEST==1
			.int 1,1,1,1
		#elif TEST==2
			.int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
		#elif TEST==3
			.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
		#elif TEST==4
			.int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
		#elif TEST==5
			.int -1,-1,-1,-1
		#elif TEST==6
			.int 200000000,200000000,200000000,200000000
		#elif TEST==7
			.int 300000000,300000000,300000000,300000000
		#elif TEST==8
			.int 5000000000,5000000000,5000000000,5000000000
		#else
			.error "Definir TEST entre 1..8"
		#endif
			.endm
lista: .irpc i,1234
					linea
			 .endr
longlista:	.int   (.-lista)/4
resultado:	.quad   0
formato: .ascii "resultado \t = %18lu (uns)\n"
				 .ascii "\t\t = 0x%18lx (hex)\n"
				 .asciz "\t\t = 0x %08x %08x \n"

.section .text
main: .global  main
	mov     $lista, %ebx		# Guardamos posición de la lista
	mov  longlista, %ecx		# Guardamos el tamaño de la lista
	call suma								# Llamada a la función suma

	mov  %eax, resultado		# Metemos los resultado de suma en resultado para luego mostrarlo
	mov  %edx, resultado+4

	mov   $formato, %rdi
	mov   resultado,%rsi
	mov   resultado,%rdx
	mov          $0,%eax	# varargin sin xmm
	call  printf		# == printf(formato, res, res);

	mov  resultado, %edi
	call _exit			# ==  exit(resultado)
	ret

suma:
	mov  $0, %eax
	mov  $0, %edx
	mov  $0, %esi

bucle:
	add   (%ebx,%esi,4), %eax
	jnc   no_acarreo
	inc   %edx

no_acarreo:
	inc 	%esi
	cmp   %esi,%ecx
	jne   bucle
	ret
