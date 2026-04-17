PUBLIC string_0_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F
PUBLIC string_1_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F
PUBLIC fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D
EXTRN op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44:PROC
EXTRN ort_debug_operator_new:PROC

.DATA

string_0_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F DB              '::main()'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
string_1_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F DB              'D:/work/soul-mod/tools/otava/test/new_int/main.cp'
DB              'p'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H

.CODE

; ::main()

fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D PROC FRAME
        push            rbp
        .pushreg        rbp
        push            rsi
        .pushreg        rsi
        push            rdi
        .pushreg        rdi
        push            r12
        .pushreg        r12
        push            r13
        .pushreg        r13
        push            r14
        .pushreg        r14
        push            rbx
        .pushreg        rbx
        sub             rsp, 0000000000000040H
        .allocstack     0000000000000040H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rax, 0000000000000004H
        mov             rsi, rax
        mov             rcx, rsi
        call            op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44
        mov             rdi, rax
        mov             eax, 00000001H
        mov             r9d, eax
        lea             rax, string_1_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F
        mov             r8, rax
        lea             rax, string_0_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F
        mov             rdx, rax
        mov             rcx, rdi
        call            ort_debug_operator_new
        mov             rsi, rax
        mov             rdi, rsi
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             rsi, qword ptr [rbp+0000000000000010H]
        mov             eax, 00000001H
        mov             dword ptr [rsi], eax
        mov             qword ptr [rbp+0000000000000008H], rdi
        mov             ebx, 00000000H
        mov             eax, ebx
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000020H]
        pop             rbx
        pop             r14
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D ENDP

END
