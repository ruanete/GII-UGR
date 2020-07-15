.section .data
			 .macro linea
			 		# .int 1,1,1,1,1,1,1,1
					# .int 2,2,2,2,2,2,2,2
					# .int 1,2,3,4,1,2,3,4
					 .int 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
					# .int 0x08000000, 0x08000000, 0x08000000, 0x08000000
					# .int 0x10000000, 0x20000000, 0x30000000, 0x40000000
			 		# .int 0x10000000, 0x10000000, 0x10000000, 0x10000000
					# .int 0x0fffffff, 0x0fffffff, 0x0fffffff, 0x0fffffff
			 .endm
lista: .irpc i,1234
					linea
			 .endr
longlista:	.int   (.-lista)/4
resultado:	.quad   0
  formato: 	.asciz	"suma = %lu = 0x%lx hex\n"

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
