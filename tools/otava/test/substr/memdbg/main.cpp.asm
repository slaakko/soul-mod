PUBLIC vtab_class_basic_ostream_593FABF644ED49E7CDB1C64A39F756C4EAC0BCD5_D5C53B7CD6C584B60A0B0C0C83EB0D7A9A66A5E3
PUBLIC vtab_class_basic_ios_827A979AF3C805EA40D8AB412FA5FDC92FAA9E41_D5C53B7CD6C584B60A0B0C0C83EB0D7A9A66A5E3
EXTRN variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40:BYTE
PUBLIC variable_npos_1D89F5F5B2DA7FC4D6EB98889C4309EB8129A36A
PUBLIC string_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8
PUBLIC string_1_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8
EXTRN dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3:PROC
EXTRN mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0:PROC
EXTRN dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91:PROC
PUBLIC op_shift_left_A5F58ABAE9246DE735B14758755CED77A12AEF56
EXTRN mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE:PROC
PUBLIC op_shift_left_D1164804742A2A8A891F09439A29BBC1005FB42E
PUBLIC fn_invoke_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_4C3AE4FA67871C8C6046FA6A0175BA282F321FF3
EXTRN mfn_basic_string_substr_6C3C666998EAAD21FF1AED3163F3BB340C8812AB:PROC
EXTRN dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2:PROC
PUBLIC fn_cleanup_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_EE6E7E755EA1B8969C3C6D27005D63D2EE432611
PUBLIC fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D
EXTRN ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF:PROC
EXTRN mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250:PROC
EXTRN ort_invoke:PROC

.DATA

vtab_class_basic_ostream_593FABF644ED49E7CDB1C64A39F756C4EAC0BCD5_D5C53B7CD6C584B60A0B0C0C83EB0D7A9A66A5E3 DQ              0A8D2A648FDCCE8CBH
DQ              9A2E48EDBACC35D3H
DQ              dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3
DQ              0000000000000000H
DQ              mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0
DQ              0000000000000000H
vtab_class_basic_ios_827A979AF3C805EA40D8AB412FA5FDC92FAA9E41_D5C53B7CD6C584B60A0B0C0C83EB0D7A9A66A5E3 DQ              0D57C0F1213451B02H
DQ              3F58718E77B75903H
DQ              dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91
DQ              0000000000000000H
variable_npos_1D89F5F5B2DA7FC4D6EB98889C4309EB8129A36A DD              0FFFFFFFFH
DB              00H
DB              00H
DB              00H
DB              00H
string_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8 DB              0AH
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H
string_1_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8 DB              'abradacabra'
DB              00H
DB              00H
DB              00H
DB              00H
DB              00H

.CODE

; std::operator<<(std::basic_ostream<char>&, const std::string&)

op_shift_left_A5F58ABAE9246DE735B14758755CED77A12AEF56 PROC FRAME
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
op_shift_left_A5F58ABAE9246DE735B14758755CED77A12AEF56 ENDP

; std::operator<<(std::basic_ostream<char>&, const char*)

op_shift_left_D1164804742A2A8A891F09439A29BBC1005FB42E PROC FRAME
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
op_shift_left_D1164804742A2A8A891F09439A29BBC1005FB42E ENDP

; ::invoke_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8(void*), parentFn=::main()

fn_invoke_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_4C3AE4FA67871C8C6046FA6A0175BA282F321FF3 PROC FRAME
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
        push            r15
        .pushreg        r15
        sub             rsp, 0000000000000040H
        .allocstack     0000000000000040H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rdi, rcx
        mov             qword ptr [rbp+0000000000000008H], rdi
        mov             eax, 00000006H
        movsxd          rdi, eax
        lea             rdx, variable_npos_1D89F5F5B2DA7FC4D6EB98889C4309EB8129A36A
        mov             r12, qword ptr [rdx]
        mov             qword ptr [rbp+0000000000000010H], r12
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             r13, byte ptr [rsi+0000000000000020H]
        mov             r9, r13
        mov             r8, r12
        mov             rdx, rdi
        mov             qword ptr [rbp+0000000000000010H], r12
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             r12, byte ptr [rsi+0000000000000008H]
        mov             rcx, r12
        call            mfn_basic_string_substr_6C3C666998EAAD21FF1AED3163F3BB340C8812AB
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             rdi, byte ptr [rsi+0000000000000020H]
        mov             rdx, rdi
        lea             rax, variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        mov             rcx, rax
        call            op_shift_left_A5F58ABAE9246DE735B14758755CED77A12AEF56
        mov             rdi, rax
        lea             rax, string_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8
        mov             rdx, rax
        mov             rcx, rdi
        call            op_shift_left_D1164804742A2A8A891F09439A29BBC1005FB42E
        mov             r12, rax
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             qword ptr [rsi+0000000000000038H], r12
        mov             rsi, qword ptr [rbp+0000000000000008H]
        lea             rdi, byte ptr [rsi+0000000000000008H]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000020H]
        pop             r15
        pop             r14
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn_invoke_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_4C3AE4FA67871C8C6046FA6A0175BA282F321FF3 ENDP

; ::cleanup_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8(void*), parentFn=::main()

fn_cleanup_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_EE6E7E755EA1B8969C3C6D27005D63D2EE432611 PROC FRAME
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
fn_cleanup_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_EE6E7E755EA1B8969C3C6D27005D63D2EE432611 ENDP

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
@0:     lea             rax, string_1_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8
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
        mov             rax, fn_cleanup_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_EE6E7E755EA1B8969C3C6D27005D63D2EE432611
        mov             rdx, rax
        mov             rax, fn_invoke_0_compile_unit_C75DBC61544C4A85980CBCA74E8556EEC701C9A8_4C3AE4FA67871C8C6046FA6A0175BA282F321FF3
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
