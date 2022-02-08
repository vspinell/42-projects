
	global	_ft_write
	extern	___error
	
	section	.text

_ft_write:
			mov		rax, 0x2000004		; put 1 (syscall ID of write) into rax
			syscall
			jc		ret_error			; if ret < 0 then ret_error()
			ret							; return (ret)

ret_error:
	        push		rax			; memorizzo l'indirizzo contenuto in rax nella stack
	        call	___error            ; in rax verra' memorizzato l'indirizzo restituito dalla funzione error  
	        pop		qword[rax]      ; prende il valore di rax e lo esegue (esegue la funzione error)
            mov 	rax, -1 			; *ret = tmp (put return value into errno)
	        ret 						; return (ret)