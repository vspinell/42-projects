section .text
    global _ft_strlen

_ft_strlen:

mov rcx, -1

_increase:
inc rcx
cmp byte [rdi + rcx], 0
jne _increase

mov rax, rcx
ret