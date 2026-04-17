types
{
        $T0 = type [4 x void*]
        $T3 = type { void*, long, $T3*, $T3*, $T3*, int } !1 // std::rb_node_base
        $T6 = type { byte*, long, long } !2 // std::basic_string<char>
        $T7 = type { long, $T6 } !3 // std::pair<const long long int, std::basic_string<char>>
        $T8 = type { $T3, $T7 } !4 // std::rb_node<std::pair<const long long int, std::basic_string<char>>>
        $T9 = type function void($T8*)
        $T10 = type function void($T7*)
        $T11 = type function void($T6*)
        $T12 = type function void($T3*)
        $T14 = type { $T8* } !7 // std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>
        $T15 = type function void($T14*)
        $T18 = type function void(void*)
        $T19 = type function bool($T14*)
        $T20 = type function $T8*($T14*)
        $T23 = type { byte } !12 // std::less<long long int>
        $T26 = type { $T14, long, $T23, $T23 } !13 // std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>
        $T27 = type function $T8*($T26*)
        $T28 = type function $T3*($T3*)
        $T29 = type function void($T26*, $T8*)
        $T30 = type function void($T3*, $T3*)
        $T36 = type function void($T26*)
}

data
{
        $T0 vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1 = [ void* conv(ulong 3047680653978019648), void* conv(ulong 6129356644785471800), void* conv($T9 @dtor_rb_node_925E56FE1A34C0E965945384C4491C176D1B96FB), void* conv(long 0) ]
}

// std::rb_node<std::pair<const long long int, std::basic_string<char>>>::@destructor() override

function $T9* dtor_rb_node_925E56FE1A34C0E965945384C4491C176D1B96FB !6
{
@0      $T8*    $0 = param
        $T8**   $1 = local $T8*
        store   $T8* $0, $T8** $1
        $T8*    $2 = load $T8** $1
        $T3*    $3 = bitcast $T8* $2
        void**  $4 = elemaddr $T3* $3, long 0
        void*   $5 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1
        store   void* $5, void** $4
        long*   $6 = elemaddr $T3* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T8*    $8 = load $T8** $1
        $T7*    $9 = elemaddr $T8* $8, long 1
        arg     $T7* $9
        call    $T10 @dtor_pair_697D2347BC872D6747FC4C19239B7A650C517C59
        $T8*    $10 = load $T8** $1
        $T3*    $11 = bitcast $T8* $10
        arg     $T3* $11
        call    $T12 @dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        $T8*    $12 = load $T8** $1
        $T3*    $13 = bitcast $T8* $12
        void**  $14 = elemaddr $T3* $13, long 0
        void*   $15 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_25138DAC82ED24AA7C96A39B1EBCFCEA9FC0D0B1
        store   void* $15, void** $14
        long*   $16 = elemaddr $T3* $13, long 1
        long*   $17 = bitcast long* $16
        store   long 0, long* $17
        ret     void
}

// std::pair<const long long int, std::basic_string<char>>::@destructor()

function $T10* dtor_pair_697D2347BC872D6747FC4C19239B7A650C517C59 !5
{
@0      $T7*    $0 = param
        $T7**   $1 = local $T7*
        store   $T7* $0, $T7** $1
        $T7*    $2 = load $T7** $1
        $T6*    $3 = elemaddr $T7* $2, long 1
        arg     $T6* $3
        call    $T11 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     void
}

extern function $T11* dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2

extern function $T12* dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE

// std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::~unique_ptr()

function $T15* dtor_514E355E78AD434A2F4603AA6B9B30F02490A858 !8
{
@0      $T14*   $0 = param
        $T14**  $1 = local $T14*
        store   $T14* $0, $T14** $1
        $T14*   $2 = load $T14** $1
        $T8**   $3 = elemaddr $T14* $2, long 0
        $T8*    $4 = load $T8** $3
        bool    $5 = equal $T8* $4, $T8* null
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      $T14*   $7 = load $T14** $1
        $T8**   $8 = elemaddr $T14* $7, long 0
        $T8*    $9 = load $T8** $8
        $T3*    $10 = bitcast $T8* $9
        void**  $11 = elemaddr $T3* $10, long 0
        void*   $12 = load void** $11
        $T0*    $13 = bitcast void* $12
        long*   $14 = elemaddr $T3* $10, long 1
        long*   $15 = bitcast long* $14
        long    $16 = load long* $15
        byte*   $17 = bitcast $T3* $10
        byte*   $18 = ptroffset byte* $17, long $16
        $T3*    $19 = bitcast byte* $18
        void**  $20 = elemaddr $T0* $13, long 2
        void*   $21 = load void** $20
        $T9*    $22 = bitcast void* $21
        void**  $23 = elemaddr $T0* $13, long 3
        long*   $24 = bitcast void** $23
        long    $25 = load long* $24
        byte*   $26 = bitcast $T3* $19
        byte*   $27 = ptroffset byte* $26, long $25
        $T3*    $28 = bitcast byte* $27
        arg     $T3* $28
        call    $T9* $22
        $T14*   $29 = load $T14** $1
        $T8**   $30 = elemaddr $T14* $29, long 0
        $T8*    $31 = load $T8** $30
        $T3*    $32 = bitcast $T8* $31
        void**  $33 = elemaddr $T3* $32, long 0
        void*   $34 = load void** $33
        $T0*    $35 = bitcast void* $34
        long*   $36 = elemaddr $T3* $32, long 1
        long*   $37 = bitcast long* $36
        long    $38 = load long* $37
        byte*   $39 = bitcast $T3* $32
        byte*   $40 = ptroffset byte* $39, long $38
        $T3*    $41 = bitcast byte* $40
        arg     $T3* $41
        call    $T18 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      ret     void
}

extern function $T18* op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4

// std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::operator_bool() const

function $T19* mfn_unique_ptr_operator_bool_089E3C7A9B28DC7BC31C9E85AA89F10258EFB60B !9
{
@0      $T14*   $0 = param
        $T14**  $1 = local $T14*
        store   $T14* $0, $T14** $1
        $T14*   $2 = load $T14** $1
        $T8**   $3 = elemaddr $T14* $2, long 0
        $T8*    $4 = load $T8** $3
        $T8*    $5 = bitcast void* null
        bool    $6 = equal $T8* $4, $T8* $5
        bool    $7 = not bool $6
        ret     bool $7
}

// std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::operator->() const

function $T20* op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE !10
{
@0      $T14*   $0 = param
        $T14**  $1 = local $T14*
        store   $T14* $0, $T14** $1
        $T14*   $2 = load $T14** $1
        $T8**   $3 = elemaddr $T14* $2, long 0
        $T8*    $4 = load $T8** $3
        ret     $T8* $4
}

// std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::root()

function $T27* mfn_rb_tree_root_DBDAF1BE82C6FC0021DBE1C80EF0A312A5293B86 !14
{
@0      $T26*   $0 = param
        $T26**  $1 = local $T26*
        store   $T26* $0, $T26** $1
        $T26*   $2 = load $T26** $1
        $T14*   $3 = elemaddr $T26* $2, long 0
        arg     $T14* $3
        $T8*    $4 = call $T20 @op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        $T3*    $5 = bitcast $T8* $4
        arg     $T3* $5
        $T3*    $6 = call $T28 @mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        $T8*    $7 = bitcast $T3* $6
        ret     $T8* $7
}

extern function $T28* mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5

// std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::set_root(std::rb_node<std::pair<const long long int, std::basic_string<char>>>*)

function $T29* mfn_rb_tree_set_root_1FC6BC4EABF32C49920CB3105FD631AC45819FFA !15
{
@0      $T26*   $0 = param
        $T8*    $1 = param
        $T26**  $2 = local $T26*
        $T8**   $3 = local $T8*
        store   $T26* $0, $T26** $2
        store   $T8* $1, $T8** $3
        $T26*   $4 = load $T26** $2
        $T14*   $5 = elemaddr $T26* $4, long 0
        arg     $T14* $5
        $T8*    $6 = call $T20 @op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        $T3*    $7 = bitcast $T8* $6
        $T8*    $8 = load $T8** $3
        $T3*    $9 = bitcast $T8* $8
        arg     $T3* $7
        arg     $T3* $9
        call    $T30 @mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
        ret     void
}

extern function $T30* mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12

// std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::get() const

function $T20* mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7 !16
{
@0      $T14*   $0 = param
        $T14**  $1 = local $T14*
        store   $T14* $0, $T14** $1
        $T14*   $2 = load $T14** $1
        $T8**   $3 = elemaddr $T14* $2, long 0
        $T8*    $4 = load $T8** $3
        ret     $T8* $4
}

// std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::set_leftmost(std::rb_node<std::pair<const long long int, std::basic_string<char>>>*)

function $T29* mfn_rb_tree_set_leftmost_A95E5B5E9265A34533DC129866550985214D96CD !17
{
@0      $T26*   $0 = param
        $T8*    $1 = param
        $T26**  $2 = local $T26*
        $T8**   $3 = local $T8*
        store   $T26* $0, $T26** $2
        store   $T8* $1, $T8** $3
        $T26*   $4 = load $T26** $2
        $T14*   $5 = elemaddr $T26* $4, long 0
        arg     $T14* $5
        $T8*    $6 = call $T20 @op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        $T3*    $7 = bitcast $T8* $6
        $T8*    $8 = load $T8** $3
        $T3*    $9 = bitcast $T8* $8
        arg     $T3* $7
        arg     $T3* $9
        call    $T30 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        ret     void
}

extern function $T30* mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F

// std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::set_rightmost(std::rb_node<std::pair<const long long int, std::basic_string<char>>>*)

function $T29* mfn_rb_tree_set_rightmost_416131C48D4FDCD92A6A6D22E1B26542FBF68DAA !18
{
@0      $T26*   $0 = param
        $T8*    $1 = param
        $T26**  $2 = local $T26*
        $T8**   $3 = local $T8*
        store   $T26* $0, $T26** $2
        store   $T8* $1, $T8** $3
        $T26*   $4 = load $T26** $2
        $T14*   $5 = elemaddr $T26* $4, long 0
        arg     $T14* $5
        $T8*    $6 = call $T20 @op_arrow_unique_ptr_008E469A400F6F440912282508A4BA9D235F24DE
        $T3*    $7 = bitcast $T8* $6
        $T8*    $8 = load $T8** $3
        $T3*    $9 = bitcast $T8* $8
        arg     $T3* $7
        arg     $T3* $9
        call    $T30 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        ret     void
}

extern function $T30* mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7

// std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::clear()

function $T36* mfn_rb_tree_clear_970EA955EBD079AE045A66B9F7798CC2F28AE0F5 !19
{
@0      $T26*   $0 = param
        $T26**  $1 = local $T26*
        $T8**   $2 = local $T8*
        store   $T26* $0, $T26** $1
        $T26*   $3 = load $T26** $1
        $T14*   $4 = elemaddr $T26* $3, long 0
        arg     $T14* $4
        bool    $5 = call $T19 @mfn_unique_ptr_operator_bool_089E3C7A9B28DC7BC31C9E85AA89F10258EFB60B
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      ret     void

@2      $T26*   $7 = load $T26** $1
        arg     $T26* $7
        $T8*    $8 = call $T27 @mfn_rb_tree_root_DBDAF1BE82C6FC0021DBE1C80EF0A312A5293B86
        store   $T8* $8, $T8** $2
        $T8*    $9 = load $T8** $2
        bool    $10 = equal $T8* $9, $T8* null
        bool    $11 = not bool $10
        branch  bool $11, @4, @5

@4      $T8*    $12 = load $T8** $2
        $T3*    $13 = bitcast $T8* $12
        void**  $14 = elemaddr $T3* $13, long 0
        void*   $15 = load void** $14
        $T0*    $16 = bitcast void* $15
        long*   $17 = elemaddr $T3* $13, long 1
        long*   $18 = bitcast long* $17
        long    $19 = load long* $18
        byte*   $20 = bitcast $T3* $13
        byte*   $21 = ptroffset byte* $20, long $19
        $T3*    $22 = bitcast byte* $21
        void**  $23 = elemaddr $T0* $16, long 2
        void*   $24 = load void** $23
        $T9*    $25 = bitcast void* $24
        void**  $26 = elemaddr $T0* $16, long 3
        long*   $27 = bitcast void** $26
        long    $28 = load long* $27
        byte*   $29 = bitcast $T3* $22
        byte*   $30 = ptroffset byte* $29, long $28
        $T3*    $31 = bitcast byte* $30
        arg     $T3* $31
        call    $T9* $25
        $T8*    $32 = load $T8** $2
        $T3*    $33 = bitcast $T8* $32
        void**  $34 = elemaddr $T3* $33, long 0
        void*   $35 = load void** $34
        $T0*    $36 = bitcast void* $35
        long*   $37 = elemaddr $T3* $33, long 1
        long*   $38 = bitcast long* $37
        long    $39 = load long* $38
        byte*   $40 = bitcast $T3* $33
        byte*   $41 = ptroffset byte* $40, long $39
        $T3*    $42 = bitcast byte* $41
        arg     $T3* $42
        call    $T18 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        $T26*   $43 = load $T26** $1
        $T8*    $44 = bitcast void* null
        arg     $T26* $43
        arg     $T8* $44
        call    $T29 @mfn_rb_tree_set_root_1FC6BC4EABF32C49920CB3105FD631AC45819FFA
        jmp     @5

@5      $T26*   $45 = load $T26** $1
        $T26*   $46 = load $T26** $1
        $T14*   $47 = elemaddr $T26* $46, long 0
        arg     $T14* $47
        $T8*    $48 = call $T20 @mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7
        arg     $T26* $45
        arg     $T8* $48
        call    $T29 @mfn_rb_tree_set_leftmost_A95E5B5E9265A34533DC129866550985214D96CD
        $T26*   $49 = load $T26** $1
        $T26*   $50 = load $T26** $1
        $T14*   $51 = elemaddr $T26* $50, long 0
        arg     $T14* $51
        $T8*    $52 = call $T20 @mfn_unique_ptr_get_4386B8F9AE681CE4735BFC70DC4ED372C8D426C7
        arg     $T26* $49
        arg     $T8* $52
        call    $T29 @mfn_rb_tree_set_rightmost_416131C48D4FDCD92A6A6D22E1B26542FBF68DAA
        long    $53 = signextend int 0
        $T26*   $54 = load $T26** $1
        long*   $55 = elemaddr $T26* $54, long 1
        store   long $53, long* $55
        ret     void
}

// std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::~rb_tree()

function $T36* dtor_522BCFF06A57BB278B6664D1BF5A64112E50A915 !20
{
@0      $T26*   $0 = param
        $T26**  $1 = local $T26*
        store   $T26* $0, $T26** $1
        $T26*   $2 = load $T26** $1
        arg     $T26* $2
        call    $T36 @mfn_rb_tree_clear_970EA955EBD079AE045A66B9F7798CC2F28AE0F5
        $T26*   $3 = load $T26** $1
        $T14*   $4 = elemaddr $T26* $3, long 0
        arg     $T14* $4
        call    $T15 @dtor_514E355E78AD434A2F4603AA6B9B30F02490A858
        ret     void
}

metadata
{
        !0 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/string_parser/string_parser_rules.cppm"}
        !1 = {fullName: "std::rb_node_base"}
        !2 = {fullName: "std::basic_string<char>"}
        !3 = {fullName: "std::pair<const long long int, std::basic_string<char>>"}
        !4 = {fullName: "std::rb_node<std::pair<const long long int, std::basic_string<char>>>"}
        !5 = {fullName: "std::pair<const long long int, std::basic_string<char>>::@destructor()", nodeType: 1}
        !6 = {fullName: "std::rb_node<std::pair<const long long int, std::basic_string<char>>>::@destructor() override", nodeType: 1}
        !7 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>"}
        !8 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::~unique_ptr()", nodeType: 1}
        !9 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::operator_bool() const", nodeType: 1}
        !10 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::operator->() const", nodeType: 1}
        !11 = {fullName: "std::select_first<const long long int, std::basic_string<char>>"}
        !12 = {fullName: "std::less<long long int>"}
        !13 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>"}
        !14 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::root()", nodeType: 1}
        !15 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::set_root(std::rb_node<std::pair<const long long int, std::basic_string<char>>>*)", nodeType: 1}
        !16 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const long long int, std::basic_string<char>>>>::get() const", nodeType: 1}
        !17 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::set_leftmost(std::rb_node<std::pair<const long long int, std::basic_string<char>>>*)", nodeType: 1}
        !18 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::set_rightmost(std::rb_node<std::pair<const long long int, std::basic_string<char>>>*)", nodeType: 1}
        !19 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::clear()", nodeType: 1}
        !20 = {fullName: "std::rb_tree<long long int, std::pair<const long long int, std::basic_string<char>>, std::select_first<const long long int, std::basic_string<char>>, std::less<long long int>>::~rb_tree()", nodeType: 1}
}
