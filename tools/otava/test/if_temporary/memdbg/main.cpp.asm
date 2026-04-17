PUBLIC string_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
PUBLIC string_1_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
PUBLIC string_2_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
PUBLIC fn_TypesEqual_0A6755C2E3D1E8E832B053E7596792EA01CDF275
PUBLIC fn_move_0327402166CAFF8AE1BE1FFDAAC2CF4FCCD50FE6
PUBLIC fn_invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_F43C493D0B43CB2040D56EBAB7844295B56EF727
EXTRN mfn_basic_string_append_2FC34573E365F5FCC5D8778E922A455E268A3849:PROC
PUBLIC fn_cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_C03E7148CE3BAA3DB10510782DCF03D351331848
EXTRN dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2:PROC
PUBLIC op_plus_5E72E32E84B1A92AC824CD5F0870E5FDDA418A8E
EXTRN ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF:PROC
EXTRN ort_invoke:PROC
EXTRN move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2:PROC
PUBLIC op_eq_412E617E1C20532FC09418C15B14860BE69CEFBF
EXTRN mfn_basic_string_length_6C8324D4F961C8E82865E765304795502F200142:PROC
EXTRN op_subscript_basic_string_6EFBC7FFD0854E40E648ED405083C6E719D74EA4:PROC
PUBLIC fn_foo_68565C58C2BE8F1AEACBA092C9167B7CB3B886B9
PUBLIC fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D

.DATA

string_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844 DB              '~'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
string_1_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844 DB              'abc'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
string_2_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844 DB              'def'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H

.CODE

; ::TypesEqual(int, int)

fn_TypesEqual_0A6755C2E3D1E8E832B053E7596792EA01CDF275 PROC FRAME
        push            rbp
        .pushreg        rbp
        push            rsi
        .pushreg        rsi
        push            rdi
        .pushreg        rdi
        push            r12
        .pushreg        r12
        push            rbx
        .pushreg        rbx
        sub             rsp, 0000000000000040H
        .allocstack     0000000000000040H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             esi, ecx
        mov             edi, edx
        mov             dword ptr [rbp+0000000000000008H], esi
        mov             dword ptr [rbp+0000000000000010H], edi
        mov             esi, dword ptr [rbp+0000000000000008H]
        mov             edi, dword ptr [rbp+0000000000000010H]
        cmp             esi, edi
        sete            r12b
        mov             al, r12b
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000020H]
        pop             rbx
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_TypesEqual_0A6755C2E3D1E8E832B053E7596792EA01CDF275 ENDP

; std::move(std::basic_string<char>&&)

fn_move_0327402166CAFF8AE1BE1FFDAAC2CF4FCCD50FE6 PROC FRAME
        push            rbp
        .pushreg        rbp
        push            rsi
        .pushreg        rsi
        push            rbx
        .pushreg        rbx
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rax, rsi
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rsi
        pop             rbp
        ret             00H
fn_move_0327402166CAFF8AE1BE1FFDAAC2CF4FCCD50FE6 ENDP

; ::invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844(void*), parentFn=std::operator+(const char*, const std::basic
; _string<char>&)

fn_invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_F43C493D0B43CB2040D56EBAB7844295B56EF727 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rdi, rcx
        mov             qword ptr [rbp+0000000000000008H], rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, qword ptr [rsi+0000000000000010H]
        mov             rdx, rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             r13, byte ptr [rsi+0000000000000020H]
        mov             rcx, r13
        call            mfn_basic_string_append_2FC34573E365F5FCC5D8778E922A455E268A3849
        mov             r12, rax
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             qword ptr [rsi+0000000000000038H], r12
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_F43C493D0B43CB2040D56EBAB7844295B56EF727 ENDP

; ::cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844(void*), parentFn=std::operator+(const char*, const std:
; :basic_string<char>&)

fn_cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_C03E7148CE3BAA3DB10510782DCF03D351331848 PROC FRAME
        push            rbp
        .pushreg        rbp
        push            rsi
        .pushreg        rsi
        push            rdi
        .pushreg        rdi
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rdi, rcx
        mov             qword ptr [rbp+0000000000000008H], rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             rdi, byte ptr [rsi+0000000000000020H]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_C03E7148CE3BAA3DB10510782DCF03D351331848 ENDP

; std::operator+(const char*, const std::basic_string<char>&)

op_plus_5E72E32E84B1A92AC824CD5F0870E5FDDA418A8E PROC FRAME
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
        sub             rsp, 0000000000000060H
        .allocstack     0000000000000060H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             rdi, rdx
        mov             r12, r8
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             qword ptr [rbp+0000000000000018H], r12
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdx, rsi
        lea             r12, byte ptr [rbp+0000000000000020H]
        mov             rcx, r12
        call            ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        mov             rsi, rbp
        mov             r8, rsi
        mov             rax, fn_cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_C03E7148CE3BAA3DB10510782DCF03D351331848
        mov             rdx, rax
        mov             rax, fn_invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_F43C493D0B43CB2040D56EBAB7844295B56EF727
        mov             rcx, rax
        call            ort_invoke
        mov             rsi, qword ptr [rbp+0000000000000038H]
        mov             rsi, qword ptr [rbp+0000000000000018H]
        lea             rdi, byte ptr [rbp+0000000000000020H]
        mov             rcx, rdi
        call            fn_move_0327402166CAFF8AE1BE1FFDAAC2CF4FCCD50FE6
        mov             rdi, rax
        mov             rdx, rdi
        mov             rcx, rsi
        call            move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2
        jmp             @1
@1:     lea             rsi, byte ptr [rbp+0000000000000020H]
        mov             rcx, rsi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp             @2
@2:     lea             rsp, qword ptr [rbp+0000000000000040H]
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
op_plus_5E72E32E84B1A92AC824CD5F0870E5FDDA418A8E ENDP

; std::operator==(const std::basic_string<char>&, const std::basic_string<char>&)

op_eq_412E617E1C20532FC09418C15B14860BE69CEFBF PROC FRAME
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
        sub             rsp, 0000000000000050H
        .allocstack     0000000000000050H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             rdi, rdx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rcx, rsi
        call            mfn_basic_string_length_6C8324D4F961C8E82865E765304795502F200142
        mov             rdi, rax
        mov             qword ptr [rbp+0000000000000018H], rdi
        mov             rsi, qword ptr [rbp+0000000000000018H]
        mov             rdi, qword ptr [rbp+0000000000000010H]
        mov             rcx, rdi
        call            mfn_basic_string_length_6C8324D4F961C8E82865E765304795502F200142
        mov             r12, rax
        cmp             rsi, r12
        sete            dil
        mov             sil, dil
        xor             sil, 01H
        or              sil, sil
        jnz             @1
        jmp             @2
@1:     mov             bl, 00H
        mov             al, bl
        jmp             @10
@2:     mov             eax, 00000000H
        movsxd          rsi, eax
        mov             qword ptr [rbp+0000000000000020H], rsi
        jmp             @4
@4:     mov             rsi, qword ptr [rbp+0000000000000020H]
        mov             rdi, qword ptr [rbp+0000000000000018H]
        cmp             rsi, rdi
        setl            r12b
        or              r12b, r12b
        jnz             @5
        jmp             @7
@5:     mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, qword ptr [rbp+0000000000000020H]
        mov             rdx, rdi
        mov             rcx, rsi
        call            op_subscript_basic_string_6EFBC7FFD0854E40E648ED405083C6E719D74EA4
        mov             r12, rax
        mov             sil, byte ptr [r12]
        mov             rdi, qword ptr [rbp+0000000000000010H]
        mov             r12, qword ptr [rbp+0000000000000020H]
        mov             rdx, r12
        mov             rcx, rdi
        call            op_subscript_basic_string_6EFBC7FFD0854E40E648ED405083C6E719D74EA4
        mov             r13, rax
        mov             dil, byte ptr [r13]
        cmp             sil, dil
        sete            r12b
        mov             sil, r12b
        xor             sil, 01H
        or              sil, sil
        jnz             @8
        jmp             @9
@6:     mov             rsi, qword ptr [rbp+0000000000000020H]
        mov             eax, 00000001H
        movsxd          rdi, eax
        add             rsi, rdi
        mov             r12, rsi
        mov             qword ptr [rbp+0000000000000020H], r12
        jmp             @4
@7:     mov             bl, 01H
        mov             al, bl
        jmp             @10
@8:     mov             bl, 00H
        mov             al, bl
        jmp             @10
@9:     jmp             @6
@10:    lea             rsp, qword ptr [rbp+0000000000000030H]
        pop             rbx
        pop             r14
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
op_eq_412E617E1C20532FC09418C15B14860BE69CEFBF ENDP

; ::foo(const std::string&, const std::string&)

fn_foo_68565C58C2BE8F1AEACBA092C9167B7CB3B886B9 PROC FRAME
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
        sub             rsp, 0000000000000080H
        .allocstack     0000000000000080H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             rdi, rdx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             eax, 00000000H
        mov             dword ptr [rbp+0000000000000018H], eax
        mov             eax, 00000000H
        mov             dword ptr [rbp+0000000000000020H], eax
        mov             eax, 00000001H
        mov             dword ptr [rbp+0000000000000028H], eax
        mov             esi, dword ptr [rbp+0000000000000028H]
        mov             edx, 00000001H
        cmp             esi, edx
        sete            dil
        or              dil, dil
        jnz             @4
        jmp             @2
@1:     mov             ebx, 00000001H
        mov             eax, ebx
        jmp             @5
@2:     mov             ebx, 00000000H
        mov             eax, ebx
        jmp             @5
@3:     mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, qword ptr [rbp+0000000000000010H]
        lea             r12, byte ptr [rbp+0000000000000038H]
        mov             r8, r12
        mov             rdx, rdi
        lea             rax, string_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
        mov             rcx, rax
        call            op_plus_5E72E32E84B1A92AC824CD5F0870E5FDDA418A8E
        lea             rdi, byte ptr [rbp+0000000000000038H]
        mov             rdx, rdi
        mov             rcx, rsi
        call            op_eq_412E617E1C20532FC09418C15B14860BE69CEFBF
        mov             rdi, rax
        lea             rsi, byte ptr [rbp+0000000000000038H]
        mov             rcx, rsi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        or              dil, dil
        jnz             @1
        jmp             @2
@4:     mov             esi, dword ptr [rbp+0000000000000018H]
        mov             edi, dword ptr [rbp+0000000000000020H]
        mov             edx, edi
        mov             ecx, esi
        call            fn_TypesEqual_0A6755C2E3D1E8E832B053E7596792EA01CDF275
        mov             r12, rax
        or              r12b, r12b
        jnz             @3
        jmp             @2
@5:     lea             rsp, qword ptr [rbp+0000000000000060H]
        pop             rbx
        pop             r14
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_foo_68565C58C2BE8F1AEACBA092C9167B7CB3B886B9 ENDP

; ::main()

fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D PROC FRAME
        push            rbp
        .pushreg        rbp
        push            rsi
        .pushreg        rsi
        push            rdi
        .pushreg        rdi
        push            rbx
        .pushreg        rbx
        push            rbx
        .pushreg        rbx
        sub             rsp, 0000000000000060H
        .allocstack     0000000000000060H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     lea             rax, string_1_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
        mov             rdx, rax
        lea             rdi, byte ptr [rbp+0000000000000010H]
        mov             rcx, rdi
        call            ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        lea             rax, string_2_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
        mov             rdx, rax
        lea             rdi, byte ptr [rbp+0000000000000028H]
        mov             rcx, rdi
        call            ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        lea             rsi, byte ptr [rbp+0000000000000028H]
        mov             rdx, rsi
        lea             rdi, byte ptr [rbp+0000000000000010H]
        mov             rcx, rdi
        call            fn_foo_68565C58C2BE8F1AEACBA092C9167B7CB3B886B9
        mov             rsi, rax
        lea             rdi, byte ptr [rbp+0000000000000010H]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        lea             rdi, byte ptr [rbp+0000000000000028H]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        mov             dword ptr [rbp+0000000000000008H], esi
        mov             ebx, 00000000H
        mov             eax, ebx
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000040H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D ENDP

END
