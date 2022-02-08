;prototipe :
;           char    *ft_strdup(const char *s1);
;
;   1st argument : s1 -> rdi
;
;   return : char *newline->rax

    global _ft_strdup
    extern _malloc
    extern _ft_strlen
    extern _ft_strcpy
    extern ___error
    section .text
_ft_strdup:
            push rdi
            call _ft_strlen
            mov rdi, rax
            inc rdi
            call _malloc
            jc exit
            pop rsi
            mov rdi, rax
            call _ft_strcpy
            ret
exit:
            push rax
            call ___error
            pop  qword[rax]
            mov rax, -1
            ret