;prototipe :
;           char    *ft_strcmp(const char *s1, const char *s2);
;
;   1st argument : s1->rdi
;   2nd argument : s2->rsi
;
;   return : int diff (*dest - *src) -> rax

            global _ft_strcmp
section .text
_ft_strcmp:
            mov rcx, -1
            mov rax, 0
compare:
        inc rcx
        mov r8b, byte[rdi + rcx]
        mov r9b, byte[rsi + rcx]
        cmp r8b, r9b
        jne exit
        cmp r8b, 0
        je exit
        cmp r9b, 0
        je exit
        jmp compare

exit:
        sub r8b, r9b
        movsx rax, r8b
        ret
