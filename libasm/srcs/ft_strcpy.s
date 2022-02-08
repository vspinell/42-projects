;prototipe :
;           char    *ft_strcpy(char *dst, const char *src);
;
;   1st argument : dest->rdi
;   2nd argument : src->rsi
;
;   return : char *dest->rax

    global _ft_strcpy
section .text

_ft_strcpy:
            mov rax, rdi ; char *ret = &dest
            mov rcx, -1 ; inizializzo il contatore a -1
copy:
    inc rcx
    mov dl, byte[rsi + rcx]
    mov byte[rdi + rcx], dl
    cmp byte[rsi + rcx], 0
    jne copy
ret