PUBLIC vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1
PUBLIC dtor_rb_node_925E56FE1A34C0E965945384C4491C176D1B96FB
PUBLIC dtor_pair_697D2347BC872D6747FC4C19239B7A650C517C59
EXTRN dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2:PROC
EXTRN dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE:PROC
PUBLIC dtor_514E355E78AD434A2F4603AA6B9B30F02490A858
EXTRN op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4:PROC
PUBLIC mfn_unique_ptr_operator_bool_089E3C7A9B28DC7BC31C9E85AA89F10258EFB60B
PUBLIC op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
PUBLIC mfn_rb_tree_root_DBDAF1BE82C6FC0021DBE1C80EF0A312A5293B86
EXTRN mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5:PROC
PUBLIC mfn_rb_tree_set_root_1FC6BC4EABF32C49920CB3105FD631AC45819FFA
EXTRN mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12:PROC
PUBLIC mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7
PUBLIC mfn_rb_tree_set_leftmost_A95E5B5E9265A34533DC129866550985214D96CD
EXTRN mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F:PROC
PUBLIC mfn_rb_tree_set_rightmost_416131C48D4FDCD92A6A6D22E1B26542FBF68DAA
EXTRN mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7:PROC
PUBLIC mfn_rb_tree_clear_970EA955EBD079AE045A66B9F7798CC2F28AE0F5
PUBLIC dtor_522BCFF06A57BB278B6664D1BF5A64112E50A915

.DATA

vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1 DQ              2A4B89685130A740H
DQ              550FD964CA1E4138H
DQ              dtor_rb_node_925E56FE1A34C0E965945384C4491C176D1B96FB
DQ              0000000000000000H

.CODE

; std::rb_node<std::pair<const long long int, std::basic_string<char>>>::@destructor() override

dtor_rb_node_925E56FE1A34C0E965945384C4491C176D1B96FB PROC FRAME
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
        mov             rdi, rsi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        lea             rax, vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1
        mov             r12, rax
        mov             qword ptr [rsi], r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             rdi, rsi
        mov             rax, 0000000000000000H
        mov             qword ptr [rdi], rax
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000030H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            dtor_pair_697D2347BC872D6747FC4C19239B7A650C517C59
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, rsi
        mov             rcx, rdi
        call            dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, rsi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        lea             rax, vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1
        mov             r12, rax
        mov             qword ptr [rsi], r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             rdi, rsi
        mov             rax, 0000000000000000H
        mov             qword ptr [rdi], rax
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
dtor_rb_node_925E56FE1A34C0E965945384C4491C176D1B96FB ENDP

; std::pair<const long long int, std::basic_string<char>>::@destructor()

dtor_pair_697D2347BC872D6747FC4C19239B7A650C517C59 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
dtor_pair_697D2347BC872D6747FC4C19239B7A650C517C59 ENDP

; std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::~unique_ptr()

dtor_514E355E78AD434A2F4603AA6B9B30F02490A858 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rsi, qword ptr [rdi]
        mov             rdx, 0000000000000000H
        cmp             rsi, rdx
        sete            dil
        mov             sil, dil
        xor             sil, 01H
        or              sil, sil
        jnz             @1
        jmp             @2
@1:     mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rsi, qword ptr [rdi]
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
        mov             rbx, 0000000000000002H
        mov             rax, 0000000000000008H
        mul             rbx
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rax+rcx]
        mov             r13, qword ptr [rdi]
        mov             rdi, r13
        mov             rbx, 0000000000000003H
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
        mov             rcx, rsi
        call            rdi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rsi, qword ptr [rdi]
        mov             rdi, rsi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             r12, qword ptr [rsi]
        mov             rsi, r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             r12, rsi
        mov             rsi, qword ptr [r12]
        mov             r12, rdi
        mov             rax, 0000000000000001H
        mul             rsi
        lea             rdi, qword ptr [rax+r12]
        mov             rsi, rdi
        mov             rcx, rsi
        call            op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp             @2
@2:     jmp             @3
@3:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rbx
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
dtor_514E355E78AD434A2F4603AA6B9B30F02490A858 ENDP

; std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::operator_bool() const

mfn_unique_ptr_operator_bool_089E3C7A9B28DC7BC31C9E85AA89F10258EFB60B PROC FRAME
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
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rsi, qword ptr [rdi]
        mov             rax, 0000000000000000H
        mov             rdi, rax
        cmp             rsi, rdi
        sete            r12b
        mov             sil, r12b
        xor             sil, 01H
        mov             al, sil
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
mfn_unique_ptr_operator_bool_089E3C7A9B28DC7BC31C9E85AA89F10258EFB60B ENDP

; std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::operator->() const

op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rsi, qword ptr [rdi]
        mov             rax, rsi
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE ENDP

; std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int,
;  std::basic_string<char>>, std::less<long long int>>::root()

mfn_rb_tree_root_DBDAF1BE82C6FC0021DBE1C80EF0A312A5293B86 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        mov             rsi, rax
        mov             rdi, rsi
        mov             rcx, rdi
        call            mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        mov             rsi, rax
        mov             rdi, rsi
        mov             rax, rdi
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
mfn_rb_tree_root_DBDAF1BE82C6FC0021DBE1C80EF0A312A5293B86 ENDP

; std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int,
;  std::basic_string<char>>, std::less<long long int>>::set_root(std::rb_node<std::pair<const long long int, std::basic_string
; <char>>>*)

mfn_rb_tree_set_root_1FC6BC4EABF32C49920CB3105FD631AC45819FFA PROC FRAME
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
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        mov             rsi, rax
        mov             rdi, rsi
        mov             rsi, qword ptr [rbp+0000000000000010H]
        mov             r12, rsi
        mov             rdx, r12
        mov             rcx, rdi
        call            mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
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
mfn_rb_tree_set_root_1FC6BC4EABF32C49920CB3105FD631AC45819FFA ENDP

; std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::get() const

mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rsi, qword ptr [rdi]
        mov             rax, rsi
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7 ENDP

; std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int,
;  std::basic_string<char>>, std::less<long long int>>::set_leftmost(std::rb_node<std::pair<const long long int, std::basic
; _string<char>>>*)

mfn_rb_tree_set_leftmost_A95E5B5E9265A34533DC129866550985214D96CD PROC FRAME
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
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        mov             rsi, rax
        mov             rdi, rsi
        mov             rsi, qword ptr [rbp+0000000000000010H]
        mov             r12, rsi
        mov             rdx, r12
        mov             rcx, rdi
        call            mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
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
mfn_rb_tree_set_leftmost_A95E5B5E9265A34533DC129866550985214D96CD ENDP

; std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int,
;  std::basic_string<char>>, std::less<long long int>>::set_rightmost(std::rb_node<std::pair<const long long int, std::basic
; _string<char>>>*)

mfn_rb_tree_set_rightmost_416131C48D4FDCD92A6A6D22E1B26542FBF68DAA PROC FRAME
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
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        mov             rsi, rax
        mov             rdi, rsi
        mov             rsi, qword ptr [rbp+0000000000000010H]
        mov             r12, rsi
        mov             rdx, r12
        mov             rcx, rdi
        call            mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
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
mfn_rb_tree_set_rightmost_416131C48D4FDCD92A6A6D22E1B26542FBF68DAA ENDP

; std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int,
;  std::basic_string<char>>, std::less<long long int>>::clear()

mfn_rb_tree_clear_970EA955EBD079AE045A66B9F7798CC2F28AE0F5 PROC FRAME
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
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            mfn_unique_ptr_operator_bool_089E3C7A9B28DC7BC31C9E85AA89F10258EFB60B
        mov             rsi, rax
        mov             dil, sil
        xor             dil, 01H
        or              dil, dil
        jnz             @1
        jmp             @2
@1:     jmp             @6
@2:     mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rcx, rsi
        call            mfn_rb_tree_root_DBDAF1BE82C6FC0021DBE1C80EF0A312A5293B86
        mov             rdi, rax
        mov             qword ptr [rbp+0000000000000010H], rdi
        mov             rsi, qword ptr [rbp+0000000000000010H]
        mov             rdx, 0000000000000000H
        cmp             rsi, rdx
        sete            dil
        mov             sil, dil
        xor             sil, 01H
        or              sil, sil
        jnz             @4
        jmp             @5
@4:     mov             rsi, qword ptr [rbp+0000000000000010H]
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
        mov             rbx, 0000000000000002H
        mov             rax, 0000000000000008H
        mul             rbx
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rax+rcx]
        mov             r13, qword ptr [rdi]
        mov             rdi, r13
        mov             rbx, 0000000000000003H
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
        mov             rcx, rsi
        call            rdi
        mov             rsi, qword ptr [rbp+0000000000000010H]
        mov             rdi, rsi
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             r12, qword ptr [rsi]
        mov             rsi, r12
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rdi]
        lea             rsi, qword ptr [rbx+rcx]
        mov             r12, rsi
        mov             rsi, qword ptr [r12]
        mov             r12, rdi
        mov             rax, 0000000000000001H
        mul             rsi
        lea             rdi, qword ptr [rax+r12]
        mov             rsi, rdi
        mov             rcx, rsi
        call            op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rax, 0000000000000000H
        mov             rdi, rax
        mov             rdx, rdi
        mov             rcx, rsi
        call            mfn_rb_tree_set_root_1FC6BC4EABF32C49920CB3105FD631AC45819FFA
        jmp             @5
@5:     mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             r12, qword ptr [rbx+rcx]
        mov             rcx, r12
        call            mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7
        mov             rdi, rax
        mov             rdx, rdi
        mov             rcx, rsi
        call            mfn_rb_tree_set_leftmost_A95E5B5E9265A34533DC129866550985214D96CD
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rdi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rdi]
        lea             r12, qword ptr [rbx+rcx]
        mov             rcx, r12
        call            mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7
        mov             rdi, rax
        mov             rdx, rdi
        mov             rcx, rsi
        call            mfn_rb_tree_set_rightmost_416131C48D4FDCD92A6A6D22E1B26542FBF68DAA
        mov             eax, 00000000H
        movsxd          rsi, eax
        mov             rdi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000008H
        lea             rcx, qword ptr [rdi]
        lea             r12, qword ptr [rbx+rcx]
        mov             qword ptr [r12], rsi
        jmp             @6
@6:     lea             rsp, qword ptr [rbp+0000000000000020H]
        pop             rbx
        pop             rbx
        pop             r13
        pop             r12
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
mfn_rb_tree_clear_970EA955EBD079AE045A66B9F7798CC2F28AE0F5 ENDP

; std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int,
;  std::basic_string<char>>, std::less<long long int>>::~rb_tree()

dtor_522BCFF06A57BB278B6664D1BF5A64112E50A915 PROC FRAME
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
        sub             rsp, 0000000000000030H
        .allocstack     0000000000000030H
        lea             rbp, qword ptr [rsp+0000000000000020H]
        .setframe       rbp, 0000000000000020H
        .endprolog      
@0:     mov             rsi, rcx
        mov             qword ptr [rbp+0000000000000008H], rsi
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rcx, rsi
        call            mfn_rb_tree_clear_970EA955EBD079AE045A66B9F7798CC2F28AE0F5
        mov             rsi, qword ptr [rbp+0000000000000008H]
        mov             rbx, 0000000000000000H
        lea             rcx, qword ptr [rsi]
        lea             rdi, qword ptr [rbx+rcx]
        mov             rcx, rdi
        call            dtor_514E355E78AD434A2F4603AA6B9B30F02490A858
        jmp             @1
@1:     lea             rsp, qword ptr [rbp+0000000000000010H]
        pop             rbx
        pop             rbx
        pop             rdi
        pop             rsi
        pop             rbp
        ret             00H
dtor_522BCFF06A57BB278B6664D1BF5A64112E50A915 ENDP

END
