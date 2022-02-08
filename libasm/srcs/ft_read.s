;prototipe :
;            ssize_t    read(int fildes, void *buf, size_t nbyte);
;
;   1st argument : fd                -> rdi
;   2nd argument : pointer to budder -> rsi
;   3rd argument : nbyte             -> rdx
;
;   return : char *newline->rax

    global _ft_read
    extern ___error
section .text

_ft_read:
        mov rax, 0x2000003
        syscall
        jc ret_error
        ret
ret_error:
        push rax
        call ___error
        pop qword[rax]
        mov rax, -1
        ret
