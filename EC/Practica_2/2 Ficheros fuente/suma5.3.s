.section .data
#ifndef TEST
#define TEST 19
#endif
			.macro linea
 		#if TEST==1
			.int -1,-1,-1,-1
		#elif TEST==2
			.int 0x04000000, 0x04000000, 0x04000000, 0x04000000
		#elif TEST==3
			.int 0x08000000, 0x08000000, 0x08000000, 0x08000000
		#elif TEST==4
			.int 0x10000000, 0x10000000, 0x10000000, 0x10000000
		#elif TEST==5
			.int 0x7fffffff,0x7fffffff,0x7fffffff,0x7fffffff
		#elif TEST==6
			.int 0x80000000,0x80000000,0x80000000,0x80000000
		#elif TEST==7
			.int 0xf0000000,0xf0000000,0xf0000000,0xf0000000
		#elif TEST==8
			.int 0xf8000000,0xf8000000,0xf8000000,0xf8000000
    #elif TEST==9
  		.int 0xf7ffffff,0xf7ffffff,0xf7ffffff,0xf7ffffff
    #elif TEST==10
      .int 100000000,100000000,100000000,100000000
    #elif TEST==11
  		.int 200000000,200000000,200000000,200000000
  	#elif TEST==12
  		.int 300000000,300000000,300000000,300000000
    #elif TEST==13
    	.int 2000000000,2000000000,2000000000,2000000000
    #elif TEST==14
      .int 3000000000,3000000000,3000000000,3000000000
    #elif TEST==15
      .int -100000000,-100000000,-100000000,-100000000
    #elif TEST==16
  		.int -200000000,-200000000,-200000000,-200000000
  	#elif TEST==17
  		.int -300000000,-300000000,-300000000,-300000000
    #elif TEST==18
    	.int -2000000000,-2000000000,-2000000000,-2000000000
    #elif TEST==19
      .int -3000000000,-3000000000,-3000000000,-3000000000
		#else
			.error "Definir TEST entre 1..19"
		#endif
			.endm
lista: .irpc i,1234
					linea
			 .endr
longlista:	.int   (.-lista)/4
resultado:	.quad   0
formato: .ascii "resultado \t = %18ld (uns)\n"
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
	mov  $0, %edi
	mov  $0, %esi
	mov  $0, %ebp

bucle:
	mov	 (%ebx, %ebp,4), %eax
  cdq

  add  %eax, %esi
	adc	 %edx, %edi

	inc  %ebp
	cmp  %ebp,%ecx
	jne	 bucle

  mov  %edi, %edx
  mov  %esi, %eax

  ret
