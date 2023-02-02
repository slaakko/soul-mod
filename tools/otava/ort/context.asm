.CODE 

save_context PROC

    mov rax, qword ptr [rsp]
    mov qword ptr [rcx], rax
    add rcx, 8
    mov qword ptr [rcx], rbp
    add rcx, 8
    mov qword ptr [rcx], rsp
    add rcx, 8
    mov qword ptr [rcx], rbx
    add rcx, 8
    mov qword ptr [rcx], rdx
    add rcx, 8
    mov qword ptr [rcx], rsi
    add rcx, 8
    mov qword ptr [rcx], rdi
    add rcx, 8
    mov qword ptr [rcx], r8
    add rcx, 8
    mov qword ptr [rcx], r9
    add rcx, 8
    mov qword ptr [rcx], r10
    add rcx, 8
    mov qword ptr [rcx], r11
    add rcx, 8
    mov qword ptr [rcx], r12
    add rcx, 8
    mov qword ptr [rcx], r13
    add rcx, 8
    mov qword ptr [rcx], r14
    add rcx, 8
    mov qword ptr [rcx], r15
    xor eax, eax
    ret 00h

save_context ENDP

restore_context PROC

    mov eax, edx
    mov rdx, qword ptr [rcx]
    add rcx, 8
    mov rbp, qword ptr [rcx]
    add rcx, 8
    mov rsp, qword ptr [rcx]
    add rcx, 8
    mov qword ptr [rsp], rdx
    mov rbx, qword ptr [rcx]
    add rcx, 8
    mov rdx, qword ptr [rcx]
    add rcx, 8
    mov rsi, qword ptr [rcx]
    add rcx, 8
    mov rdi, qword ptr [rcx]
    add rcx, 8
    mov r8, qword ptr [rcx]
    add rcx, 8
    mov r9, qword ptr [rcx]
    add rcx, 8
    mov r10, qword ptr [rcx]
    add rcx, 8
    mov r11, qword ptr [rcx]
    add rcx, 8
    mov r12, qword ptr [rcx]
    add rcx, 8
    mov r13, qword ptr [rcx]
    add rcx, 8
    mov r14, qword ptr [rcx]
    add rcx, 8
    mov r15, qword ptr [rcx]
    ret 00h

restore_context ENDP

END
