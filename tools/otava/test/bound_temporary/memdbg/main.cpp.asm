PUBLIC vtab_class_basic_ostream_593FABF644ED49E7CDB1C64A39F756C4EAC0BCD5_8349A546AE8A12F97573B4E6492F3AE563BC8C7C
PUBLIC vtab_class_basic_ios_827A979AF3C805EA40D8AB412FA5FDC92FAA9E41_8349A546AE8A12F97573B4E6492F3AE563BC8C7C
PUBLIC string_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
EXTRN variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40:BYTE
PUBLIC string_1_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
PUBLIC string_2_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
EXTRN dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3:PROC
EXTRN mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0:PROC
EXTRN dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91:PROC
PUBLIC fn_foo_F97C8F71C78EFEFCC863033F9AF286DFC355CC16
EXTRN ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF:PROC
PUBLIC op_shift_left_9EB1D9660978D0826A659045ADFD694CF02666AC
EXTRN mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE:PROC
PUBLIC op_shift_left_DB559511639BB1719947D97B2A3D8178474C7C78
PUBLIC fn_invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_B344C7A7992C62A9519B3D37A5DFFF4522A5BE94
EXTRN dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2:PROC
PUBLIC fn_cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_C9B7651690D9426DD426F44AE5BEEA58A3201014
PUBLIC fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D
EXTRN mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250:PROC
EXTRN ort_invoke:PROC

.DATA

vtab_class_basic_ostream_593FABF644ED49E7CDB1C64A39F756C4EAC0BCD5_8349A546AE8A12F97573B4E6492F3AE563BC8C7C DQ              0A8D2A648FDCCE8CBH
DQ              9A2E48EDBACC35D3H
DQ              dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3
DQ              0000000000000000H
DQ              mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0
DQ              0000000000000000H
vtab_class_basic_ios_827A979AF3C805EA40D8AB412FA5FDC92FAA9E41_8349A546AE8A12F97573B4E6492F3AE563BC8C7C DQ              0D57C0F1213451B02H
DQ              3F58718E77B75903H
DQ              dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91
DQ              0000000000000000H
string_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51 DB              'foo'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
string_1_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51 DB              0AH
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
string_2_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51 DB              'abc'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H

.CODE

; ::foo()

fn_foo_F97C8F71C78EFEFCC863033F9AF286DFC355CC16 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             rax, string_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
        mov             rdx, rax
        mov             rcx, rsi
        call            ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_foo_F97C8F71C78EFEFCC863033F9AF286DFC355CC16 ENDP

; std::operator<<(std::basic_ostream<char>&, const std::string&)

op_shift_left_9EB1D9660978D0826A659045ADFD694CF02666AC PROC FRAME
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
        push            rbx
        .pushreg        rbx
        push            rbx
        .pushreg        rbx
        sub             rsp, 0000000000000040H
        .allocstack     0000000000000040H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             rdi, rdx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, qword ptr [rbp+0000000000000010H]
        mov             rdx, rdi
        mov             rcx, rsi
        call            mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rax, rsi
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000020H]
        pop             rbx
        pop             rbx
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
op_shift_left_9EB1D9660978D0826A659045ADFD694CF02666AC ENDP

; std::operator<<(std::basic_ostream<char>&, const char*)

op_shift_left_DB559511639BB1719947D97B2A3D8178474C7C78 PROC FRAME
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
@0:     mov             rsi, rcx
        mov             rdi, rdx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, rsi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             r12, qword ptr [rsi]
        mov             rsi, r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rdi]
        lea             r12, qword ptr [rbx+rcx]
        mov             r13, r12
        mov             r12, qword ptr [r13]
        mov             r13, rdi
        mov             rax, 0000000000000001H
        mul             r12
        lea             rdi, qword ptr [rax+r13]
        mov             r12, rdi
        mov             rbx, 0000000000000004H
        mov             rax, 0000000000000008H
        mul             rbx
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rax+rcx]
        mov             r13, qword ptr [rdi]
        mov             rdi, r13
        mov             rbx, 0000000000000005H
        mov             rax, 0000000000000008H
        mul             rbx
        lea             rcx, qword ptr [rsi]
        lea             r13, qword ptr [rax+rcx]
        mov             rsi, r13
        mov             r13, qword ptr [rsi]
        mov             rsi, r12
        mov             rax, 0000000000000001H
        mul             r13
        lea             r12, qword ptr [rax+rsi]
        mov             rsi, r12
        mov             r12, qword ptr [rbp+0000000000000010H]
        mov             rdx, r12
        mov             rcx, rsi
        call            rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rax, rsi
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
op_shift_left_DB559511639BB1719947D97B2A3D8178474C7C78 ENDP

; ::invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51(void*), parentFn=::main()

fn_invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_B344C7A7992C62A9519B3D37A5DFFF4522A5BE94 PROC FRAME
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
        lea             rdi, byte ptr [rsi+0000000000000020H]
        mov             rcx, rdi
        call            fn_foo_F97C8F71C78EFEFCC863033F9AF286DFC355CC16
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             rdi, byte ptr [rsi+0000000000000020H]
        mov             rdx, rdi
        lea             rax, variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        mov             rcx, rax
        call            op_shift_left_9EB1D9660978D0826A659045ADFD694CF02666AC
        mov             rdi, rax
        lea             rax, string_1_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
        mov             rdx, rax
        mov             rcx, rdi
        call            op_shift_left_DB559511639BB1719947D97B2A3D8178474C7C78
        mov             r12, rax
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             qword ptr [rsi+0000000000000038H], r12
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             rdi, byte ptr [rsi+0000000000000020H]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_B344C7A7992C62A9519B3D37A5DFFF4522A5BE94 ENDP

; ::cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51(void*), parentFn=::main()

fn_cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_C9B7651690D9426DD426F44AE5BEEA58A3201014 PROC FRAME
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
        lea             rdi, byte ptr [rsi+0000000000000008H]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_C9B7651690D9426DD426F44AE5BEEA58A3201014 ENDP

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
        push            rbx
        .pushreg        rbx
        push            rbx
        .pushreg        rbx
        sub             rsp, 0000000000000060H
        .allocstack     0000000000000060H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     lea             rax, string_2_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
        mov             rdx, rax
        lea             rdi, byte ptr [rbp+0000000000000008H]
        mov             rcx, rdi
        call            ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        lea             rax, variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        mov             rsi, rax
        mov             rcx, rsi
        call            mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250
        mov             rsi, rbp
        mov             r8, rsi
        mov             rax, fn_cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_C9B7651690D9426DD426F44AE5BEEA58A3201014
        mov             rdx, rax
        mov             rax, fn_invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_B344C7A7992C62A9519B3D37A5DFFF4522A5BE94
        mov             rcx, rax
        call            ort_invoke
        mov             rsi, qword ptr [rbp+0000000000000038H]
        lea             rsi, byte ptr [rbp+0000000000000008H]
        mov             rcx, rsi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        mov             ebx, 00000000H
        mov             eax, ebx
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000040H]
        pop             rbx
        pop             rbx
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D ENDP

END
