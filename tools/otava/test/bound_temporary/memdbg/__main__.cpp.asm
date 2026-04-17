PUBLIC string_0_
PUBLIC string_1_
PUBLIC __global_init__
EXTRN op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44:PROC
EXTRN ort_debug_operator_new:PROC
EXTRN default_ctor_AF25A380FFB5E1D3D906D613C4B5D31B93E12B90:PROC
EXTRN ort_set_bad_alloc:PROC
EXTRN fn___dynamic_init__compile_unit_84DEC0F7E818042650E66C07AE1A45F9365DA9F9_7CD94554958218325ECA90097BE8CEC0A2147FCB:PROC
EXTRN fn___dynamic_init__compile_unit_7275B3F43E1B6C49FBA7613C55EAB5C1EF1FBD06_60D0C2082F064AB0E80C1C4615F149895D0FAC08:PROC
EXTRN fn___dynamic_init__compile_unit_3CAE5CCE46FBE978DC59D230EA95889E441EA158_B913E0E6F8C849FBD2C1236B017FD914A3461FDB:PROC
EXTRN fn___dynamic_init__compile_unit_7434ED6B99D8BE329DCA42E600CB1F406A229502_A873A0CFA4000598FD35C2EC945CDFF9F75D6DFB:PROC
PUBLIC __global_done__
EXTRN ort_get_bad_alloc:PROC
EXTRN op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4:PROC
PUBLIC fn___main_wrapper___6AD707E323E364CC721579A108E141F517AB5EF3
EXTRN fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D:PROC
EXTRN fn_run_at_exits_E93D88F8DBABD96E599F01AFA804D3BB619FDE8F:PROC

.DATA

string_0_ DB              '::__main_wrapper__(int, const char**)'
DB              00H
DB              00H
DB              00H
string_1_ DB              'D:/work/soul-mod/tools/otava/test/bound_temporary/__main__.cpp'
DB              00H
DB              00H

.CODE

; ::__global_init__()

__global_init__ PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rax, 0000000000000010H
        mov             rsi, rax
        mov             rcx, rsi
        call            op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44
        mov             rdi, rax
        mov             eax, 00000000H
        mov             r9d, eax
        lea             rax, string_1_
        mov             r8, rax
        lea             rax, string_0_
        mov             rdx, rax
        mov             rcx, rdi
        call            ort_debug_operator_new
        mov             rsi, rax
        mov             rdi, rsi
        mov             qword ptr [rbp+0000000000000008H], rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rcx, rsi
        call            default_ctor_AF25A380FFB5E1D3D906D613C4B5D31B93E12B90
        mov             rsi, rdi
        mov             rax, 1A9B1320B8A86B6EH
        mov             r8, rax
        mov             rax, 0C23C9D976CA3A171H
        mov             rdx, rax
        mov             rcx, rsi
        call            ort_set_bad_alloc
        call            fn___dynamic_init__compile_unit_84DEC0F7E818042650E66C07AE1A45F9365DA9F9_7CD94554958218325ECA90097BE8CEC0A2147FCB
        call            fn___dynamic_init__compile_unit_7275B3F43E1B6C49FBA7613C55EAB5C1EF1FBD06_60D0C2082F064AB0E80C1C4615F149895D0FAC08
        call            fn___dynamic_init__compile_unit_3CAE5CCE46FBE978DC59D230EA95889E441EA158_B913E0E6F8C849FBD2C1236B017FD914A3461FDB
        call            fn___dynamic_init__compile_unit_7434ED6B99D8BE329DCA42E600CB1F406A229502_A873A0CFA4000598FD35C2EC945CDFF9F75D6DFB
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             r14
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
__global_init__ ENDP

; ::__global_done__()

__global_done__ PROC FRAME
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
        sub             rsp, 0000000000000020H
        .allocstack     0000000000000020H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     call            ort_get_bad_alloc
        mov             rsi, rax
        mov             rdi, rsi
        mov             rsi, rdi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             r12, qword ptr [rdi]
        mov             rdi, r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rsi]
        lea             r12, qword ptr [rbx+rcx]
        mov             r13, r12
        mov             r12, qword ptr [r13]
        mov             r13, rsi
        mov             rax, 0000000000000001H
        mul             r12
        lea             rsi, qword ptr [rax+r13]
        mov             r12, rsi
        mov             rbx, 0000000000000002H
        mov             rax, 0000000000000008H
        mul             rbx
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rax+rcx]
        mov             r13, qword ptr [rsi]
        mov             rsi, r13
        mov             rbx, 0000000000000003H
        mov             rax, 0000000000000008H
        mul             rbx
        lea             rcx, qword ptr [rdi]
        lea             r13, qword ptr [rax+rcx]
        mov             rdi, r13
        mov             r13, qword ptr [rdi]
        mov             rdi, r12
        mov             rax, 0000000000000001H
        mul             r13
        lea             r12, qword ptr [rax+rdi]
        mov             rdi, r12
        mov             rcx, rdi
        call            rsi
        call            ort_get_bad_alloc
        mov             rsi, rax
        mov             rdi, rsi
        mov             rsi, rdi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             r12, qword ptr [rdi]
        mov             rdi, r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             r12, rdi
        mov             rdi, qword ptr [r12]
        mov             r12, rsi
        mov             rax, 0000000000000001H
        mul             rdi
        lea             rsi, qword ptr [rax+r12]
        mov             rdi, rsi
        mov             rcx, rdi
        call            op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000000H]
        pop             rbx
        pop             rbx
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
__global_done__ ENDP

; ::__main_wrapper__(int, const char**)

fn___main_wrapper___6AD707E323E364CC721579A108E141F517AB5EF3 PROC FRAME
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
        sub             rsp, 0000000000000040H
        .allocstack     0000000000000040H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             esi, ecx
        mov             rdi, rdx
        mov             dword ptr [rbp+0000000000000008H], esi
        mov             qword ptr [rbp+0000000000000010H], rdi
        call            __global_init__
        call            fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D
        mov             rsi, rax
        mov             dword ptr [rbp+0000000000000018H], esi
        call            fn_run_at_exits_E93D88F8DBABD96E599F01AFA804D3BB619FDE8F
        call            __global_done__
        mov             esi, dword ptr [rbp+0000000000000018H]
        mov             eax, esi
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000020H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
fn___main_wrapper___6AD707E323E364CC721579A108E141F517AB5EF3 ENDP

END
