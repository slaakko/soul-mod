types
{
        $T2 = type { void*, long, $T2*, $T2*, $T2*, int } !0 // std::rb_node_base
        $T4 = type { int, int } !1 // std::pair<const int, int>
        $T5 = type { $T2, $T4 } !2 // std::rb_node<std::pair<const int, int>>
        $T6 = type [4 x void*]
        $T7 = type function void($T5*)
        $T8 = type [6 x void*]
        $T12 = type { void*, long, int } !4 // std::ios_base
        $T13 = type { $T12 } !5 // std::basic_ios<char>
        $T14 = type { $T13, int } !6 // std::basic_ostream<char>
        $T15 = type function void($T14*)
        $T16 = type function void($T14*, byte*)
        $T18 = type function void($T13*)
        $T19 = type function void($T2*)
        $T21 = type { $T5* } !41 // std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>
        $T22 = type function void($T21*)
        $T25 = type function void(void*)
        $T26 = type function bool($T21*)
        $T27 = type function $T5*($T21*)
        $T30 = type { byte } !13 // std::less<int>
        $T33 = type { $T21, long, $T30, $T30 } !14 // std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>
        $T34 = type function $T5*($T33*)
        $T35 = type function $T2*($T2*)
        $T36 = type function void($T33*, $T5*)
        $T37 = type function void($T2*, $T2*)
        $T43 = type function void($T33*)
        $T48 = type function void($T30*)
        $T50 = type function void($T4*)
        $T51 = type function $T4*($T4*)
        $T52 = type function int*(int*)
        $T54 = type function void($T4*, $T4*)
        $T55 = type function void($T5*, $T4*, $T2*)
        $T57 = type function void($T21*, $T5*)
        $T61 = type function void*(ulong)
        $T62 = type function void*(void*, byte*, byte*, int)
        $T63 = type function void($T2*, int)
        $T66 = type { $T33 } !34 // std::map<int, int, std::less<int>>
        $T67 = type function void($T66*)
        $T69 = type function void($T4*, int*, int*)
        $T70 = type function int*($T30*, $T4*)
        $T71 = type function $T4*($T5*)
        $T72 = type function bool($T30*, int*, int*)
        $T76 = type function $T5**($T5**)
        $T77 = type function void($T21*, $T21*)
        $T78 = type function void($T33*, $T21*)
        $T83 = type function bool($T21*, $T21*)
        $T86 = type function $T2**($T33*)
        $T87 = type function $T2**($T2*)
        $T88 = type function void($T33*, $T5*, $T5*, $T4*, $T21*)
        $T89 = type function void($T2*, $T2**)
        $T92 = type { $T21, bool } !54 // std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>
        $T93 = type function void($T92*, $T21*, bool*)
        $T94 = type function $T92*($T92*)
        $T95 = type function $T21*($T21*)
        $T96 = type function bool*(bool*)
        $T97 = type function void($T92*, $T92*)
        $T98 = type function void($T21*, bool*, $T92*)
        $T100 = type function $T2*($T2*)
        $T101 = type function void($T33*, $T4*, $T92*)
        $T102 = type function void($T66*, $T4*, $T92*)
        $T104 = type function $T4*($T21*)
        $T105 = type function int*($T66*, int*)
        $T106 = type function bool($T33*)
        $T107 = type function void($T33*, int*, $T21*)
        $T108 = type function void($T66*, int*, $T21*)
        $T109 = type function void($T66*, $T21*)
        $T111 = type { byte*, long, long } !71 // std::basic_string<char>
        $T112 = type function $T14*($T14*, $T111*)
        $T113 = type function void($T14*, $T111*)
        $T114 = type function $T14*($T14*, byte*)
        $T119 = type function void(int, $T111*)
        $T120 = type function void($T111*, $T111*)
        $T121 = type function void($T111*)
        $T125 = type function int()
        $T127 = type function void($T25*, $T25*, void*)
        $T128 = type function void($T12*)
}

data
{
        $T6 vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_F7E5F150F29B2C52B2A4CD0F8B523E9E1E0AF606 = [ void* conv(ulong 1486899736768506772), void* conv(ulong 11511164791753316717), void* conv($T7 @dtor_rb_node_05AB035D823D8122BEF2B95AF9B07557929831C9), void* conv(long 0) ]
        $T8 vtab_class_basic_ostream_593FABF644ED49E7CDB1C64A39F756C4EAC0BCD5_9AFCA4640DB47DAFF5501CEB445F8FA0BF0FECAA = [ void* conv(ulong 12164968375907051723), void* conv(ulong 11109897516647986643), void* conv($T15 @dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3), void* conv(long 0), void* conv($T16 @mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0), void* conv(long 0) ]
        $T6 vtab_class_basic_ios_827A979AF3C805EA40D8AB412FA5FDC92FAA9E41_9AFCA4640DB47DAFF5501CEB445F8FA0BF0FECAA = [ void* conv(ulong 15383186997497895682), void* conv(ulong 4564523079047796995), void* conv($T18 @dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91), void* conv(long 0) ]
        byte string_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5 = "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::init()\00"
        byte string_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5 = "D:/work/soul-mod/tools/otava/test/map/map.cpp\00"
        byte string_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5 = "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::insert(std::rb_node<std::pair<const int, int>>*, std::rb_node<std::pair<const int, int>>*, std::pair<const int, int>&&)\00"
        $T14 variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40;
        byte string_3_compile_unit_2B96B93279757D013A42886094ED44C5626597A5 = "\0A\00"
}

// std::rb_node<std::pair<const int, int>>::@destructor() override

function $T7* dtor_rb_node_05AB035D823D8122BEF2B95AF9B07557929831C9 !7
{
@0      $T5*    $0 = param
        $T5**   $1 = local $T5*
        store   $T5* $0, $T5** $1
        $T5*    $2 = load $T5** $1
        $T2*    $3 = bitcast $T5* $2
        void**  $4 = elemaddr $T2* $3, long 0
        void*   $5 = bitcast $T6* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_F7E5F150F29B2C52B2A4CD0F8B523E9E1E0AF606
        store   void* $5, void** $4
        long*   $6 = elemaddr $T2* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T5*    $8 = load $T5** $1
        $T2*    $9 = bitcast $T5* $8
        arg     $T2* $9
        call    $T19 @dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        $T5*    $10 = load $T5** $1
        $T2*    $11 = bitcast $T5* $10
        void**  $12 = elemaddr $T2* $11, long 0
        void*   $13 = bitcast $T6* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_F7E5F150F29B2C52B2A4CD0F8B523E9E1E0AF606
        store   void* $13, void** $12
        long*   $14 = elemaddr $T2* $11, long 1
        long*   $15 = bitcast long* $14
        store   long 0, long* $15
        ret     void
}

extern function $T15* dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3

extern function $T16* mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0

extern function $T18* dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91

extern function $T19* dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE

// std::unique_ptr<std::rb_node<std::pair<const int, int>>>::~unique_ptr()

function $T22* dtor_A9ECFF635C643368C2C17A4E474FB177245EBF1E !9
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        bool    $5 = equal $T5* $4, $T5* null
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      $T21*   $7 = load $T21** $1
        $T5**   $8 = elemaddr $T21* $7, long 0
        $T5*    $9 = load $T5** $8
        $T2*    $10 = bitcast $T5* $9
        void**  $11 = elemaddr $T2* $10, long 0
        void*   $12 = load void** $11
        $T6*    $13 = bitcast void* $12
        long*   $14 = elemaddr $T2* $10, long 1
        long*   $15 = bitcast long* $14
        long    $16 = load long* $15
        byte*   $17 = bitcast $T2* $10
        byte*   $18 = ptroffset byte* $17, long $16
        $T2*    $19 = bitcast byte* $18
        void**  $20 = elemaddr $T6* $13, long 2
        void*   $21 = load void** $20
        $T7*    $22 = bitcast void* $21
        void**  $23 = elemaddr $T6* $13, long 3
        long*   $24 = bitcast void** $23
        long    $25 = load long* $24
        byte*   $26 = bitcast $T2* $19
        byte*   $27 = ptroffset byte* $26, long $25
        $T2*    $28 = bitcast byte* $27
        arg     $T2* $28
        call    $T7* $22
        $T21*   $29 = load $T21** $1
        $T5**   $30 = elemaddr $T21* $29, long 0
        $T5*    $31 = load $T5** $30
        $T2*    $32 = bitcast $T5* $31
        void**  $33 = elemaddr $T2* $32, long 0
        void*   $34 = load void** $33
        $T6*    $35 = bitcast void* $34
        long*   $36 = elemaddr $T2* $32, long 1
        long*   $37 = bitcast long* $36
        long    $38 = load long* $37
        byte*   $39 = bitcast $T2* $32
        byte*   $40 = ptroffset byte* $39, long $38
        $T2*    $41 = bitcast byte* $40
        arg     $T2* $41
        call    $T25 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      ret     void
}

extern function $T25* op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4

// std::unique_ptr<std::rb_node<std::pair<const int, int>>>::operator_bool() const

function $T26* mfn_unique_ptr_operator_bool_E85891987FDB288CBC2A747B5DF359219956E4AC !10
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        $T5*    $5 = bitcast void* null
        bool    $6 = equal $T5* $4, $T5* $5
        bool    $7 = not bool $6
        ret     bool $7
}

// std::unique_ptr<std::rb_node<std::pair<const int, int>>>::operator->() const

function $T27* op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE !11
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        ret     $T5* $4
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::root()

function $T34* mfn_rb_tree_root_1B3598BD7673997789F017438DD58AB432375423 !15
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        $T21*   $3 = elemaddr $T33* $2, long 0
        arg     $T21* $3
        $T5*    $4 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $5 = bitcast $T5* $4
        arg     $T2* $5
        $T2*    $6 = call $T35 @mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        $T5*    $7 = bitcast $T2* $6
        ret     $T5* $7
}

extern function $T35* mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::set_root(std::rb_node<std::pair<const int, int>>*)

function $T36* mfn_rb_tree_set_root_4230F81FC97D65C6336FB7754BE4A7A7C3D82FAA !16
{
@0      $T33*   $0 = param
        $T5*    $1 = param
        $T33**  $2 = local $T33*
        $T5**   $3 = local $T5*
        store   $T33* $0, $T33** $2
        store   $T5* $1, $T5** $3
        $T33*   $4 = load $T33** $2
        $T21*   $5 = elemaddr $T33* $4, long 0
        arg     $T21* $5
        $T5*    $6 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $7 = bitcast $T5* $6
        $T5*    $8 = load $T5** $3
        $T2*    $9 = bitcast $T5* $8
        arg     $T2* $7
        arg     $T2* $9
        call    $T37 @mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
        ret     void
}

extern function $T37* mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12

// std::unique_ptr<std::rb_node<std::pair<const int, int>>>::get() const

function $T27* mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3 !17
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        ret     $T5* $4
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::set_leftmost(std::rb_node<std::pair<const int, int>>*)

function $T36* mfn_rb_tree_set_leftmost_9FE6C4474EB47EEC05D4BAD7AB4A233FB2A63C6B !18
{
@0      $T33*   $0 = param
        $T5*    $1 = param
        $T33**  $2 = local $T33*
        $T5**   $3 = local $T5*
        store   $T33* $0, $T33** $2
        store   $T5* $1, $T5** $3
        $T33*   $4 = load $T33** $2
        $T21*   $5 = elemaddr $T33* $4, long 0
        arg     $T21* $5
        $T5*    $6 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $7 = bitcast $T5* $6
        $T5*    $8 = load $T5** $3
        $T2*    $9 = bitcast $T5* $8
        arg     $T2* $7
        arg     $T2* $9
        call    $T37 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        ret     void
}

extern function $T37* mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::set_rightmost(std::rb_node<std::pair<const int, int>>*)

function $T36* mfn_rb_tree_set_rightmost_C530ACBBD39A4FB08D60448A9EF6E54F6AF4436F !19
{
@0      $T33*   $0 = param
        $T5*    $1 = param
        $T33**  $2 = local $T33*
        $T5**   $3 = local $T5*
        store   $T33* $0, $T33** $2
        store   $T5* $1, $T5** $3
        $T33*   $4 = load $T33** $2
        $T21*   $5 = elemaddr $T33* $4, long 0
        arg     $T21* $5
        $T5*    $6 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $7 = bitcast $T5* $6
        $T5*    $8 = load $T5** $3
        $T2*    $9 = bitcast $T5* $8
        arg     $T2* $7
        arg     $T2* $9
        call    $T37 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        ret     void
}

extern function $T37* mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::clear()

function $T43* mfn_rb_tree_clear_88543FA34AA517A8BB1232A14DDCABAC8F67F0E7 !20
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        $T5**   $2 = local $T5*
        store   $T33* $0, $T33** $1
        $T33*   $3 = load $T33** $1
        $T21*   $4 = elemaddr $T33* $3, long 0
        arg     $T21* $4
        bool    $5 = call $T26 @mfn_unique_ptr_operator_bool_E85891987FDB288CBC2A747B5DF359219956E4AC
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      ret     void

@2      $T33*   $7 = load $T33** $1
        arg     $T33* $7
        $T5*    $8 = call $T34 @mfn_rb_tree_root_1B3598BD7673997789F017438DD58AB432375423
        store   $T5* $8, $T5** $2
        $T5*    $9 = load $T5** $2
        bool    $10 = equal $T5* $9, $T5* null
        bool    $11 = not bool $10
        branch  bool $11, @4, @5

@4      $T5*    $12 = load $T5** $2
        $T2*    $13 = bitcast $T5* $12
        void**  $14 = elemaddr $T2* $13, long 0
        void*   $15 = load void** $14
        $T6*    $16 = bitcast void* $15
        long*   $17 = elemaddr $T2* $13, long 1
        long*   $18 = bitcast long* $17
        long    $19 = load long* $18
        byte*   $20 = bitcast $T2* $13
        byte*   $21 = ptroffset byte* $20, long $19
        $T2*    $22 = bitcast byte* $21
        void**  $23 = elemaddr $T6* $16, long 2
        void*   $24 = load void** $23
        $T7*    $25 = bitcast void* $24
        void**  $26 = elemaddr $T6* $16, long 3
        long*   $27 = bitcast void** $26
        long    $28 = load long* $27
        byte*   $29 = bitcast $T2* $22
        byte*   $30 = ptroffset byte* $29, long $28
        $T2*    $31 = bitcast byte* $30
        arg     $T2* $31
        call    $T7* $25
        $T5*    $32 = load $T5** $2
        $T2*    $33 = bitcast $T5* $32
        void**  $34 = elemaddr $T2* $33, long 0
        void*   $35 = load void** $34
        $T6*    $36 = bitcast void* $35
        long*   $37 = elemaddr $T2* $33, long 1
        long*   $38 = bitcast long* $37
        long    $39 = load long* $38
        byte*   $40 = bitcast $T2* $33
        byte*   $41 = ptroffset byte* $40, long $39
        $T2*    $42 = bitcast byte* $41
        arg     $T2* $42
        call    $T25 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        $T33*   $43 = load $T33** $1
        $T5*    $44 = bitcast void* null
        arg     $T33* $43
        arg     $T5* $44
        call    $T36 @mfn_rb_tree_set_root_4230F81FC97D65C6336FB7754BE4A7A7C3D82FAA
        jmp     @5

@5      $T33*   $45 = load $T33** $1
        $T33*   $46 = load $T33** $1
        $T21*   $47 = elemaddr $T33* $46, long 0
        arg     $T21* $47
        $T5*    $48 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        arg     $T33* $45
        arg     $T5* $48
        call    $T36 @mfn_rb_tree_set_leftmost_9FE6C4474EB47EEC05D4BAD7AB4A233FB2A63C6B
        $T33*   $49 = load $T33** $1
        $T33*   $50 = load $T33** $1
        $T21*   $51 = elemaddr $T33* $50, long 0
        arg     $T21* $51
        $T5*    $52 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        arg     $T33* $49
        arg     $T5* $52
        call    $T36 @mfn_rb_tree_set_rightmost_C530ACBBD39A4FB08D60448A9EF6E54F6AF4436F
        long    $53 = signextend int 0
        $T33*   $54 = load $T33** $1
        long*   $55 = elemaddr $T33* $54, long 1
        store   long $53, long* $55
        ret     void
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::~rb_tree()

function $T43* dtor_EB08BB08642BCCD955254BBFBC95EAFC62A7D95F !21
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        arg     $T33* $2
        call    $T43 @mfn_rb_tree_clear_88543FA34AA517A8BB1232A14DDCABAC8F67F0E7
        $T33*   $3 = load $T33** $1
        $T21*   $4 = elemaddr $T33* $3, long 0
        arg     $T21* $4
        call    $T22 @dtor_A9ECFF635C643368C2C17A4E474FB177245EBF1E
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const int, int>>>::unique_ptr()

function $T22* default_ctor_F8F0156191733E9ADE9006DA908589A70ED91D5F !22
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T5*    $2 = bitcast void* null
        $T21*   $3 = load $T21** $1
        $T5**   $4 = elemaddr $T21* $3, long 0
        store   $T5* $2, $T5** $4
        ret     void
}

// std::select_first<const int, int>::@class_default_ctor()

function $T48* default_ctor_select_first_896C8370FC00157E17B61FE52EC4C71F451A07FF !23
{
@0      $T30*   $0 = param
        $T30**  $1 = local $T30*
        store   $T30* $0, $T30** $1
        ret     void
}

// std::less<int>::@class_default_ctor()

function $T48* default_ctor_less_EBC0FBE1C0A9EC389FB258046FA743992C5147B7 !24
{
@0      $T30*   $0 = param
        $T30**  $1 = local $T30*
        store   $T30* $0, $T30** $1
        ret     void
}

// std::pair<const int, int>::pair()

function $T50* default_ctor_31C5BC2EA178F8EBBBC7CFC3E5F3667415ABB7CA !25
{
@0      $T4*    $0 = param
        $T4**   $1 = local $T4*
        store   $T4* $0, $T4** $1
        $T4*    $2 = load $T4** $1
        int*    $3 = elemaddr $T4* $2, long 0
        store   int 0, int* $3
        $T4*    $4 = load $T4** $1
        int*    $5 = elemaddr $T4* $4, long 1
        store   int 0, int* $5
        ret     void
}

// std::move(std::pair<const int, int>&&)

function $T51* fn_move_8E306F2AEABEF643D992290CC7205728319CCF76 !26
{
@0      $T4*    $0 = param
        $T4**   $1 = local $T4*
        store   $T4* $0, $T4** $1
        $T4*    $2 = load $T4** $1
        ret     $T4* $2
}

// std::move(const int&&)

function $T52* fn_move_86EB287F2D50B47F1CFFD37A60ED46F29BD27516 !27
{
@0      int*    $0 = param
        int**   $1 = local int*
        store   int* $0, int** $1
        int*    $2 = load int** $1
        ret     int* $2
}

// std::move(int&&)

function $T52* fn_move_F0520FC15A4B7F76236EF1D46D94A08F95521DBC !28
{
@0      int*    $0 = param
        int**   $1 = local int*
        store   int* $0, int** $1
        int*    $2 = load int** $1
        ret     int* $2
}

// std::pair<const int, int>::pair(std::pair<const int, int>&&)

function $T54* move_ctor_2F5CF9F53F329B323B1C17DD2567F47913655C8C !29
{
@0      $T4*    $0 = param
        $T4*    $1 = param
        $T4**   $2 = local $T4*
        $T4**   $3 = local $T4*
        store   $T4* $0, $T4** $2
        store   $T4* $1, $T4** $3
        $T4*    $4 = load $T4** $3
        int*    $5 = elemaddr $T4* $4, long 0
        arg     int* $5
        int*    $6 = call $T52 @fn_move_86EB287F2D50B47F1CFFD37A60ED46F29BD27516
        int     $7 = load int* $6
        $T4*    $8 = load $T4** $2
        int*    $9 = elemaddr $T4* $8, long 0
        store   int $7, int* $9
        $T4*    $10 = load $T4** $3
        int*    $11 = elemaddr $T4* $10, long 1
        arg     int* $11
        int*    $12 = call $T52 @fn_move_F0520FC15A4B7F76236EF1D46D94A08F95521DBC
        int     $13 = load int* $12
        $T4*    $14 = load $T4** $2
        int*    $15 = elemaddr $T4* $14, long 1
        store   int $13, int* $15
        ret     void
}

// std::rb_node<std::pair<const int, int>>::rb_node(std::pair<const int, int>&&, std::rb_node_base*)

function $T55* ctor_rb_node_FBFD7FFCD5991DDC90CC194EB48CE60DF1E48803 !30
{
@0      $T5*    $0 = param
        $T4*    $1 = param
        $T2*    $2 = param
        $T5**   $3 = local $T5*
        $T4**   $4 = local $T4*
        $T2**   $5 = local $T2*
        store   $T5* $0, $T5** $3
        store   $T4* $1, $T4** $4
        store   $T2* $2, $T2** $5
        $T5*    $6 = load $T5** $3
        $T2*    $7 = bitcast $T5* $6
        $T2*    $8 = load $T2** $5
        arg     $T2* $7
        arg     $T2* $8
        call    $T37 @ctor_rb_node_base_AD0A66DB7ADEC4B6C13963BAA62ED115CFD4A086
        $T5*    $9 = load $T5** $3
        $T2*    $10 = bitcast $T5* $9
        void**  $11 = elemaddr $T2* $10, long 0
        void*   $12 = bitcast $T6* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_F7E5F150F29B2C52B2A4CD0F8B523E9E1E0AF606
        store   void* $12, void** $11
        long*   $13 = elemaddr $T2* $10, long 1
        long*   $14 = bitcast long* $13
        store   long 0, long* $14
        $T5*    $15 = load $T5** $3
        $T4*    $16 = elemaddr $T5* $15, long 1
        $T4*    $17 = load $T4** $4
        arg     $T4* $17
        $T4*    $18 = call $T51 @fn_move_8E306F2AEABEF643D992290CC7205728319CCF76
        arg     $T4* $16
        arg     $T4* $18
        call    $T54 @move_ctor_2F5CF9F53F329B323B1C17DD2567F47913655C8C
        ret     void
}

extern function $T37* ctor_rb_node_base_AD0A66DB7ADEC4B6C13963BAA62ED115CFD4A086

// std::unique_ptr<std::rb_node<std::pair<const int, int>>>::reset(std::rb_node<std::pair<const int, int>>*)

function $T57* mfn_unique_ptr_reset_D1A8A6A05245CF500A5EC24353A43A85A1B93371 !31
{
@0      $T21*   $0 = param
        $T5*    $1 = param
        $T21**  $2 = local $T21*
        $T5**   $3 = local $T5*
        store   $T21* $0, $T21** $2
        store   $T5* $1, $T5** $3
        $T21*   $4 = load $T21** $2
        $T5**   $5 = elemaddr $T21* $4, long 0
        $T5*    $6 = load $T5** $5
        bool    $7 = equal $T5* $6, $T5* null
        bool    $8 = not bool $7
        branch  bool $8, @1, @2

@1      $T21*   $9 = load $T21** $2
        $T5**   $10 = elemaddr $T21* $9, long 0
        $T5*    $11 = load $T5** $10
        $T2*    $12 = bitcast $T5* $11
        void**  $13 = elemaddr $T2* $12, long 0
        void*   $14 = load void** $13
        $T6*    $15 = bitcast void* $14
        long*   $16 = elemaddr $T2* $12, long 1
        long*   $17 = bitcast long* $16
        long    $18 = load long* $17
        byte*   $19 = bitcast $T2* $12
        byte*   $20 = ptroffset byte* $19, long $18
        $T2*    $21 = bitcast byte* $20
        void**  $22 = elemaddr $T6* $15, long 2
        void*   $23 = load void** $22
        $T7*    $24 = bitcast void* $23
        void**  $25 = elemaddr $T6* $15, long 3
        long*   $26 = bitcast void** $25
        long    $27 = load long* $26
        byte*   $28 = bitcast $T2* $21
        byte*   $29 = ptroffset byte* $28, long $27
        $T2*    $30 = bitcast byte* $29
        arg     $T2* $30
        call    $T7* $24
        $T21*   $31 = load $T21** $2
        $T5**   $32 = elemaddr $T21* $31, long 0
        $T5*    $33 = load $T5** $32
        $T2*    $34 = bitcast $T5* $33
        void**  $35 = elemaddr $T2* $34, long 0
        void*   $36 = load void** $35
        $T6*    $37 = bitcast void* $36
        long*   $38 = elemaddr $T2* $34, long 1
        long*   $39 = bitcast long* $38
        long    $40 = load long* $39
        byte*   $41 = bitcast $T2* $34
        byte*   $42 = ptroffset byte* $41, long $40
        $T2*    $43 = bitcast byte* $42
        arg     $T2* $43
        call    $T25 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      $T5*    $44 = load $T5** $3
        $T21*   $45 = load $T21** $2
        $T5**   $46 = elemaddr $T21* $45, long 0
        store   $T5* $44, $T5** $46
        ret     void
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::init()

function $T43* mfn_rb_tree_init_579B2C0966AEB8FA304099B38C9B45AB23DFA6AD !32
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        $T5**   $2 = local $T5*
        $T4*    $3 = local $T4
        store   $T33* $0, $T33** $1
        $T33*   $4 = load $T33** $1
        $T21*   $5 = elemaddr $T33* $4, long 0
        ulong   $6 = bitcast long 56
        arg     ulong $6
        void*   $7 = call $T61 @op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44
        arg     void* $7
        arg     byte* string_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5
        arg     byte* string_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5
        arg     int 1
        void*   $8 = call $T62 @ort_debug_operator_new
        $T5*    $9 = bitcast void* $8
        store   $T5* $9, $T5** $2
        $T5*    $10 = load $T5** $2
        arg     $T4* $3
        call    $T50 @default_ctor_31C5BC2EA178F8EBBBC7CFC3E5F3667415ABB7CA
        $T2*    $11 = bitcast void* null
        arg     $T5* $10
        arg     $T4* $3
        arg     $T2* $11
        call    $T55 @ctor_rb_node_FBFD7FFCD5991DDC90CC194EB48CE60DF1E48803
        arg     $T21* $5
        arg     $T5* $9
        call    $T57 @mfn_unique_ptr_reset_D1A8A6A05245CF500A5EC24353A43A85A1B93371
        $T33*   $12 = load $T33** $1
        $T21*   $13 = elemaddr $T33* $12, long 0
        arg     $T21* $13
        $T5*    $14 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $15 = bitcast $T5* $14
        arg     $T2* $15
        arg     int 0
        call    $T63 @mfn_rb_node_base_set_color_5CAC95F613E0886DD0B8E9819323C610E900E683
        $T33*   $16 = load $T33** $1
        $T33*   $17 = load $T33** $1
        $T21*   $18 = elemaddr $T33* $17, long 0
        arg     $T21* $18
        $T5*    $19 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        arg     $T33* $16
        arg     $T5* $19
        call    $T36 @mfn_rb_tree_set_leftmost_9FE6C4474EB47EEC05D4BAD7AB4A233FB2A63C6B
        $T33*   $20 = load $T33** $1
        $T33*   $21 = load $T33** $1
        $T21*   $22 = elemaddr $T33* $21, long 0
        arg     $T21* $22
        $T5*    $23 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        arg     $T33* $20
        arg     $T5* $23
        call    $T36 @mfn_rb_tree_set_rightmost_C530ACBBD39A4FB08D60448A9EF6E54F6AF4436F
        ret     void
}

extern function $T61* op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44

extern function $T62* ort_debug_operator_new

extern function $T63* mfn_rb_node_base_set_color_5CAC95F613E0886DD0B8E9819323C610E900E683

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::rb_tree()

function $T43* default_ctor_528047C2A0FC8B262568C8437EB70FD55B3A78A6 !33
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        $T21*   $3 = elemaddr $T33* $2, long 0
        arg     $T21* $3
        call    $T22 @default_ctor_F8F0156191733E9ADE9006DA908589A70ED91D5F
        long    $4 = signextend int 0
        $T33*   $5 = load $T33** $1
        long*   $6 = elemaddr $T33* $5, long 1
        store   long $4, long* $6
        $T33*   $7 = load $T33** $1
        $T30*   $8 = elemaddr $T33* $7, long 2
        arg     $T30* $8
        call    $T48 @default_ctor_select_first_896C8370FC00157E17B61FE52EC4C71F451A07FF
        $T33*   $9 = load $T33** $1
        $T30*   $10 = elemaddr $T33* $9, long 3
        arg     $T30* $10
        call    $T48 @default_ctor_less_EBC0FBE1C0A9EC389FB258046FA743992C5147B7
        $T33*   $11 = load $T33** $1
        arg     $T33* $11
        call    $T43 @mfn_rb_tree_init_579B2C0966AEB8FA304099B38C9B45AB23DFA6AD
        ret     void
}

// std::map<int, int, std::less<int>>::map()

function $T67* default_ctor_30B6EAC544BBBBF503E6BE8F202AF396FF25DF0B !35
{
@0      $T66*   $0 = param
        $T66**  $1 = local $T66*
        store   $T66* $0, $T66** $1
        $T66*   $2 = load $T66** $1
        $T33*   $3 = elemaddr $T66* $2, long 0
        arg     $T33* $3
        call    $T43 @default_ctor_528047C2A0FC8B262568C8437EB70FD55B3A78A6
        ret     void
}

// std::map<int, int, std::less<int>>::@destructor()

function $T67* dtor_map_D91D456389CE69CF7E40BBEE173765EB2BAD7067 !36
{
@0      $T66*   $0 = param
        $T66**  $1 = local $T66*
        store   $T66* $0, $T66** $1
        $T66*   $2 = load $T66** $1
        $T33*   $3 = elemaddr $T66* $2, long 0
        arg     $T33* $3
        call    $T43 @dtor_EB08BB08642BCCD955254BBFBC95EAFC62A7D95F
        ret     void
}

// std::pair<const int, int>::pair(const int&&, int&&)

function $T69* ctor_pair_CAC9203211522A5AD648016407EAC037DDFF9AAB !37
{
@0      $T4*    $0 = param
        int*    $1 = param
        int*    $2 = param
        $T4**   $3 = local $T4*
        int**   $4 = local int*
        int**   $5 = local int*
        store   $T4* $0, $T4** $3
        store   int* $1, int** $4
        store   int* $2, int** $5
        int*    $6 = load int** $4
        arg     int* $6
        int*    $7 = call $T52 @fn_move_86EB287F2D50B47F1CFFD37A60ED46F29BD27516
        int     $8 = load int* $7
        $T4*    $9 = load $T4** $3
        int*    $10 = elemaddr $T4* $9, long 0
        store   int $8, int* $10
        int*    $11 = load int** $5
        arg     int* $11
        int*    $12 = call $T52 @fn_move_F0520FC15A4B7F76236EF1D46D94A08F95521DBC
        int     $13 = load int* $12
        $T4*    $14 = load $T4** $3
        int*    $15 = elemaddr $T4* $14, long 1
        store   int $13, int* $15
        ret     void
}

// std::select_first<const int, int>::operator()(const std::pair<const int, int>&) const

function $T70* op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979 !38
{
@0      $T30*   $0 = param
        $T4*    $1 = param
        $T30**  $2 = local $T30*
        $T4**   $3 = local $T4*
        store   $T30* $0, $T30** $2
        store   $T4* $1, $T4** $3
        $T4*    $4 = load $T4** $3
        int*    $5 = elemaddr $T4* $4, long 0
        ret     int* $5
}

// std::rb_node<std::pair<const int, int>>::value()

function $T71* mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9 !39
{
@0      $T5*    $0 = param
        $T5**   $1 = local $T5*
        store   $T5* $0, $T5** $1
        $T5*    $2 = load $T5** $1
        $T4*    $3 = elemaddr $T5* $2, long 1
        ret     $T4* $3
}

// std::less<int>::operator()(const int&, const int&) const

function $T72* op_apply_less_2328D89C86144AD22E0B68798073E752D76F575A !40
{
@0      $T30*   $0 = param
        int*    $1 = param
        int*    $2 = param
        $T30**  $3 = local $T30*
        int**   $4 = local int*
        int**   $5 = local int*
        store   $T30* $0, $T30** $3
        store   int* $1, int** $4
        store   int* $2, int** $5
        int*    $6 = load int** $4
        int     $7 = load int* $6
        int*    $8 = load int** $5
        int     $9 = load int* $8
        bool    $10 = less int $7, int $9
        ret     bool $10
}

// std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::rb_node_iterator(std::rb_node<std::pair<const int, int>>*)

function $T57* ctor_rb_node_iterator_85AE9D8E08884A80A6EAD3D66F1A83F2141D5AAC !42
{
@0      $T21*   $0 = param
        $T5*    $1 = param
        $T21**  $2 = local $T21*
        $T5**   $3 = local $T5*
        store   $T21* $0, $T21** $2
        store   $T5* $1, $T5** $3
        $T5*    $4 = load $T5** $3
        $T21*   $5 = load $T21** $2
        $T5**   $6 = elemaddr $T21* $5, long 0
        store   $T5* $4, $T5** $6
        ret     void
}

// std::move(std::rb_node<std::pair<const int, int>>*&&)

function $T76* fn_move_6BD1B4A547DD84551748C0F66939D0D9BB6F9D86 !43
{
@0      $T5**   $0 = param
        $T5***  $1 = local $T5**
        store   $T5** $0, $T5*** $1
        $T5**   $2 = load $T5*** $1
        ret     $T5** $2
}

// std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::@class_move_ctor(std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&&)

function $T77* move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269 !44
{
@0      $T21*   $0 = param
        $T21*   $1 = param
        $T21**  $2 = local $T21*
        $T21**  $3 = local $T21*
        store   $T21* $0, $T21** $2
        store   $T21* $1, $T21** $3
        $T21*   $4 = load $T21** $3
        $T5**   $5 = elemaddr $T21* $4, long 0
        arg     $T5** $5
        $T5**   $6 = call $T76 @fn_move_6BD1B4A547DD84551748C0F66939D0D9BB6F9D86
        $T5*    $7 = load $T5** $6
        $T21*   $8 = load $T21** $2
        $T5**   $9 = elemaddr $T21* $8, long 0
        store   $T5* $7, $T5** $9
        ret     void
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::end()

function $T78* mfn_rb_tree_end_909487DDE486E2B1D633A24FA7E9BC53E9BFBA18 !45
{
@0      $T33*   $0 = param
        $T21*   $1 = param
        $T33**  $2 = local $T33*
        $T21**  $3 = local $T21*
        $T21*   $4 = local $T21
        store   $T33* $0, $T33** $2
        store   $T21* $1, $T21** $3
        $T21*   $5 = load $T21** $3
        $T33*   $6 = load $T33** $2
        $T21*   $7 = elemaddr $T33* $6, long 0
        arg     $T21* $7
        $T5*    $8 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        arg     $T21* $4
        arg     $T5* $8
        call    $T57 @ctor_rb_node_iterator_85AE9D8E08884A80A6EAD3D66F1A83F2141D5AAC
        arg     $T21* $5
        arg     $T21* $4
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::leftmost()

function $T34* mfn_rb_tree_leftmost_13E6F9A1BF4115858582124504FA0F2F6711A542 !46
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        $T21*   $3 = elemaddr $T33* $2, long 0
        arg     $T21* $3
        $T5*    $4 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $5 = bitcast $T5* $4
        arg     $T2* $5
        $T2*    $6 = call $T35 @mfn_rb_node_base_get_left_CA41E0268374885EDF0A2EC4AB70D66EB7DEE351
        $T5*    $7 = bitcast $T2* $6
        ret     $T5* $7
}

extern function $T35* mfn_rb_node_base_get_left_CA41E0268374885EDF0A2EC4AB70D66EB7DEE351

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::begin()

function $T78* mfn_rb_tree_begin_8CD40EC22D4E02BF277FE8DDB318770C42BB2072 !47
{
@0      $T33*   $0 = param
        $T21*   $1 = param
        $T33**  $2 = local $T33*
        $T21**  $3 = local $T21*
        $T21*   $4 = local $T21
        $T21*   $5 = local $T21
        store   $T33* $0, $T33** $2
        store   $T21* $1, $T21** $3
        $T33*   $6 = load $T33** $2
        $T21*   $7 = elemaddr $T33* $6, long 0
        arg     $T21* $7
        bool    $8 = call $T26 @mfn_unique_ptr_operator_bool_E85891987FDB288CBC2A747B5DF359219956E4AC
        bool    $9 = not bool $8
        branch  bool $9, @1, @2

@1      $T21*   $10 = load $T21** $3
        $T33*   $11 = load $T33** $2
        arg     $T33* $11
        arg     $T21* $4
        call    $T78 @mfn_rb_tree_end_909487DDE486E2B1D633A24FA7E9BC53E9BFBA18
        arg     $T21* $10
        arg     $T21* $4
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void

@2      $T21*   $12 = load $T21** $3
        $T33*   $13 = load $T33** $2
        arg     $T33* $13
        $T5*    $14 = call $T34 @mfn_rb_tree_leftmost_13E6F9A1BF4115858582124504FA0F2F6711A542
        arg     $T21* $5
        arg     $T5* $14
        call    $T57 @ctor_rb_node_iterator_85AE9D8E08884A80A6EAD3D66F1A83F2141D5AAC
        arg     $T21* $12
        arg     $T21* $5
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void
}

// std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::node() const

function $T27* mfn_rb_node_iterator_node_8F307AF5F8A594C187DE4B97A02B6A1AF61A476E !48
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        ret     $T5* $4
}

// std::operator==(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&, const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&)

function $T83* op_eq_200EB5C13C62E7A2B3C01FBD1E06D411A32737E9 !49
{
@0      $T21*   $0 = param
        $T21*   $1 = param
        $T21**  $2 = local $T21*
        $T21**  $3 = local $T21*
        store   $T21* $0, $T21** $2
        store   $T21* $1, $T21** $3
        $T21*   $4 = load $T21** $2
        arg     $T21* $4
        $T5*    $5 = call $T27 @mfn_rb_node_iterator_node_8F307AF5F8A594C187DE4B97A02B6A1AF61A476E
        $T21*   $6 = load $T21** $3
        arg     $T21* $6
        $T5*    $7 = call $T27 @mfn_rb_node_iterator_node_8F307AF5F8A594C187DE4B97A02B6A1AF61A476E
        bool    $8 = equal $T5* $5, $T5* $7
        ret     bool $8
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::rightmost()

function $T34* mfn_rb_tree_rightmost_A6EDB34C577C0AAF17FD47D14634C723CD65A9FA !50
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        $T21*   $3 = elemaddr $T33* $2, long 0
        arg     $T21* $3
        $T5*    $4 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $5 = bitcast $T5* $4
        arg     $T2* $5
        $T2*    $6 = call $T35 @mfn_rb_node_base_get_right_877D876415132D037A4918347CC0376C9CCECCD3
        $T5*    $7 = bitcast $T2* $6
        ret     $T5* $7
}

extern function $T35* mfn_rb_node_base_get_right_877D876415132D037A4918347CC0376C9CCECCD3

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::root_ptr()

function $T86* mfn_rb_tree_root_ptr_F03E369C47A6300E552239D9246EB5F7747CD303 !51
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        $T21*   $3 = elemaddr $T33* $2, long 0
        arg     $T21* $3
        $T5*    $4 = call $T27 @op_arrow_unique_ptr_1525E86DAA1BB5651346A54E79BD39B1507A16FE
        $T2*    $5 = bitcast $T5* $4
        arg     $T2* $5
        $T2**   $6 = call $T87 @mfn_rb_node_base_parent_ptr_25279F637CB7352ACFAA99E96636DFE6706527B4
        ret     $T2** $6
}

extern function $T87* mfn_rb_node_base_parent_ptr_25279F637CB7352ACFAA99E96636DFE6706527B4

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::insert(std::rb_node<std::pair<const int, int>>*, std::rb_node<std::pair<const int, int>>*, std::pair<const int, int>&&)

function $T88* mfn_rb_tree_insert_BB08DF87022A98BD1E798F497B24AA8751DBFABA !52
{
@0      $T33*   $0 = param
        $T5*    $1 = param
        $T5*    $2 = param
        $T4*    $3 = param
        $T21*   $4 = param
        $T33**  $5 = local $T33*
        $T5**   $6 = local $T5*
        $T5**   $7 = local $T5*
        $T4**   $8 = local $T4*
        $T21**  $9 = local $T21*
        $T5**   $10 = local $T5*
        $T5**   $11 = local $T5*
        bool*   $12 = local bool
        bool*   $13 = local bool
        $T21*   $14 = local $T21
        store   $T33* $0, $T33** $5
        store   $T5* $1, $T5** $6
        store   $T5* $2, $T5** $7
        store   $T4* $3, $T4** $8
        store   $T21* $4, $T21** $9
        $T33*   $15 = load $T33** $5
        $T21*   $16 = elemaddr $T33* $15, long 0
        arg     $T21* $16
        bool    $17 = call $T26 @mfn_unique_ptr_operator_bool_E85891987FDB288CBC2A747B5DF359219956E4AC
        bool    $18 = not bool $17
        branch  bool $18, @1, @2

@1      $T33*   $19 = load $T33** $5
        arg     $T33* $19
        call    $T43 @mfn_rb_tree_init_579B2C0966AEB8FA304099B38C9B45AB23DFA6AD
        jmp     @2

@2      ulong   $20 = bitcast long 56
        arg     ulong $20
        void*   $21 = call $T61 @op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44
        arg     void* $21
        arg     byte* string_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5
        arg     byte* string_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5
        arg     int 1
        void*   $22 = call $T62 @ort_debug_operator_new
        $T5*    $23 = bitcast void* $22
        store   $T5* $23, $T5** $11
        $T5*    $24 = load $T5** $11
        $T4*    $25 = load $T4** $8
        arg     $T4* $25
        $T4*    $26 = call $T51 @fn_move_8E306F2AEABEF643D992290CC7205728319CCF76
        $T5*    $27 = load $T5** $7
        $T2*    $28 = bitcast $T5* $27
        arg     $T5* $24
        arg     $T4* $26
        arg     $T2* $28
        call    $T55 @ctor_rb_node_FBFD7FFCD5991DDC90CC194EB48CE60DF1E48803
        store   $T5* $23, $T5** $10
        $T5*    $29 = load $T5** $7
        $T33*   $30 = load $T33** $5
        $T21*   $31 = elemaddr $T33* $30, long 0
        arg     $T21* $31
        $T5*    $32 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        bool    $33 = equal $T5* $29, $T5* $32
        branch  bool $33, @3, @7

@3      $T5*    $34 = load $T5** $7
        $T2*    $35 = bitcast $T5* $34
        $T5*    $36 = load $T5** $10
        $T2*    $37 = bitcast $T5* $36
        arg     $T2* $35
        arg     $T2* $37
        call    $T37 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        $T5*    $38 = load $T5** $7
        $T33*   $39 = load $T33** $5
        $T21*   $40 = elemaddr $T33* $39, long 0
        arg     $T21* $40
        $T5*    $41 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        bool    $42 = equal $T5* $38, $T5* $41
        branch  bool $42, @8, @10

@4      $T5*    $43 = load $T5** $10
        $T2*    $44 = bitcast $T5* $43
        $T33*   $45 = load $T33** $5
        arg     $T33* $45
        $T2**   $46 = call $T86 @mfn_rb_tree_root_ptr_F03E369C47A6300E552239D9246EB5F7747CD303
        arg     $T2* $44
        arg     $T2** $46
        call    $T89 @fn_rebalance_after_insert_1D2F472C99EF4D7F903B3E4F902B7BD0127A8B1A
        $T33*   $47 = load $T33** $5
        long*   $48 = elemaddr $T33* $47, long 1
        long    $49 = load long* $48
        long    $50 = signextend int 1
        long    $51 = add long $49, long $50
        $T33*   $52 = load $T33** $5
        long*   $53 = elemaddr $T33* $52, long 1
        store   long $51, long* $53
        $T21*   $54 = load $T21** $9
        $T5*    $55 = load $T5** $10
        arg     $T21* $14
        arg     $T5* $55
        call    $T57 @ctor_rb_node_iterator_85AE9D8E08884A80A6EAD3D66F1A83F2141D5AAC
        arg     $T21* $54
        arg     $T21* $14
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void

@5      $T5*    $56 = load $T5** $7
        $T2*    $57 = bitcast $T5* $56
        $T5*    $58 = load $T5** $10
        $T2*    $59 = bitcast $T5* $58
        arg     $T2* $57
        arg     $T2* $59
        call    $T37 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        $T5*    $60 = load $T5** $7
        $T33*   $61 = load $T33** $5
        arg     $T33* $61
        $T5*    $62 = call $T34 @mfn_rb_tree_rightmost_A6EDB34C577C0AAF17FD47D14634C723CD65A9FA
        bool    $63 = equal $T5* $60, $T5* $62
        branch  bool $63, @13, @14

@6      $T33*   $64 = load $T33** $5
        $T30*   $65 = elemaddr $T33* $64, long 3
        $T33*   $66 = load $T33** $5
        $T30*   $67 = elemaddr $T33* $66, long 2
        $T5*    $68 = load $T5** $10
        arg     $T5* $68
        $T4*    $69 = call $T71 @mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9
        arg     $T30* $67
        arg     $T4* $69
        int*    $70 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        $T33*   $71 = load $T33** $5
        $T30*   $72 = elemaddr $T33* $71, long 2
        $T5*    $73 = load $T5** $7
        arg     $T5* $73
        $T4*    $74 = call $T71 @mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9
        arg     $T30* $72
        arg     $T4* $74
        int*    $75 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        arg     $T30* $65
        arg     int* $70
        arg     int* $75
        bool    $76 = call $T72 @op_apply_less_2328D89C86144AD22E0B68798073E752D76F575A
        branch  bool $76, @3, @5

@7      $T5*    $77 = load $T5** $6
        $T5*    $78 = bitcast void* null
        bool    $79 = equal $T5* $77, $T5* $78
        bool    $80 = not bool $79
        branch  bool $80, @3, @6

@8      $T33*   $81 = load $T33** $5
        $T5*    $82 = load $T5** $10
        arg     $T33* $81
        arg     $T5* $82
        call    $T36 @mfn_rb_tree_set_root_4230F81FC97D65C6336FB7754BE4A7A7C3D82FAA
        $T33*   $83 = load $T33** $5
        $T5*    $84 = load $T5** $10
        arg     $T33* $83
        arg     $T5* $84
        call    $T36 @mfn_rb_tree_set_rightmost_C530ACBBD39A4FB08D60448A9EF6E54F6AF4436F
        jmp     @9

@9      jmp     @4

@10     $T5*    $85 = load $T5** $7
        $T33*   $86 = load $T33** $5
        arg     $T33* $86
        $T5*    $87 = call $T34 @mfn_rb_tree_leftmost_13E6F9A1BF4115858582124504FA0F2F6711A542
        bool    $88 = equal $T5* $85, $T5* $87
        branch  bool $88, @11, @12

@11     $T33*   $89 = load $T33** $5
        $T5*    $90 = load $T5** $10
        arg     $T33* $89
        arg     $T5* $90
        call    $T36 @mfn_rb_tree_set_leftmost_9FE6C4474EB47EEC05D4BAD7AB4A233FB2A63C6B
        jmp     @12

@12     jmp     @9

@13     $T33*   $91 = load $T33** $5
        $T5*    $92 = load $T5** $10
        arg     $T33* $91
        arg     $T5* $92
        call    $T36 @mfn_rb_tree_set_rightmost_C530ACBBD39A4FB08D60448A9EF6E54F6AF4436F
        jmp     @14

@14     jmp     @4
}

extern function $T89* fn_rebalance_after_insert_1D2F472C99EF4D7F903B3E4F902B7BD0127A8B1A

// std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::@class_copy_ctor(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&)

function $T77* copy_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269 !53
{
@0      $T21*   $0 = param
        $T21*   $1 = param
        $T21**  $2 = local $T21*
        $T21**  $3 = local $T21*
        store   $T21* $0, $T21** $2
        store   $T21* $1, $T21** $3
        $T21*   $4 = load $T21** $3
        $T5**   $5 = elemaddr $T21* $4, long 0
        $T5*    $6 = load $T5** $5
        $T21*   $7 = load $T21** $2
        $T5**   $8 = elemaddr $T21* $7, long 0
        store   $T5* $6, $T5** $8
        ret     void
}

// std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>::pair(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&, const bool&)

function $T93* ctor_pair_DA877013F1FA3DF433EE3194A1248FB785DACAC4 !55
{
@0      $T92*   $0 = param
        $T21*   $1 = param
        bool*   $2 = param
        $T92**  $3 = local $T92*
        $T21**  $4 = local $T21*
        bool**  $5 = local bool*
        store   $T92* $0, $T92** $3
        store   $T21* $1, $T21** $4
        store   bool* $2, bool** $5
        $T92*   $6 = load $T92** $3
        $T21*   $7 = elemaddr $T92* $6, long 0
        $T21*   $8 = load $T21** $4
        arg     $T21* $7
        arg     $T21* $8
        call    $T77 @copy_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        bool*   $9 = load bool** $5
        bool    $10 = load bool* $9
        $T92*   $11 = load $T92** $3
        bool*   $12 = elemaddr $T92* $11, long 1
        store   bool $10, bool* $12
        ret     void
}

// std::move(std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>&&)

function $T94* fn_move_D92954D71E1A2D52FF50BA2A5BD9649FC0A8C712 !56
{
@0      $T92*   $0 = param
        $T92**  $1 = local $T92*
        store   $T92* $0, $T92** $1
        $T92*   $2 = load $T92** $1
        ret     $T92* $2
}

// std::move(std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&&)

function $T95* fn_move_B3EF4CF8360663A1C9E8E55AEEC6B412713D65D3 !57
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        ret     $T21* $2
}

// std::move(bool&&)

function $T96* fn_move_6B12F56DB63C7B7EFB3FE712FE6863790B856E1D !58
{
@0      bool*   $0 = param
        bool**  $1 = local bool*
        store   bool* $0, bool** $1
        bool*   $2 = load bool** $1
        ret     bool* $2
}

// std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>::pair(std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>&&)

function $T97* move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83 !59
{
@0      $T92*   $0 = param
        $T92*   $1 = param
        $T92**  $2 = local $T92*
        $T92**  $3 = local $T92*
        store   $T92* $0, $T92** $2
        store   $T92* $1, $T92** $3
        $T92*   $4 = load $T92** $2
        $T21*   $5 = elemaddr $T92* $4, long 0
        $T92*   $6 = load $T92** $3
        $T21*   $7 = elemaddr $T92* $6, long 0
        arg     $T21* $7
        $T21*   $8 = call $T95 @fn_move_B3EF4CF8360663A1C9E8E55AEEC6B412713D65D3
        arg     $T21* $5
        arg     $T21* $8
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        $T92*   $9 = load $T92** $3
        bool*   $10 = elemaddr $T92* $9, long 1
        arg     bool* $10
        bool*   $11 = call $T96 @fn_move_6B12F56DB63C7B7EFB3FE712FE6863790B856E1D
        bool    $12 = load bool* $11
        $T92*   $13 = load $T92** $2
        bool*   $14 = elemaddr $T92* $13, long 1
        store   bool $12, bool* $14
        ret     void
}

// std::make_pair(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&, const bool&)

function $T98* fn_make_pair_0CFF03192AC8A7F5F95C67A8FEEF158723FD6C0F !60
{
@0      $T21*   $0 = param
        bool*   $1 = param
        $T92*   $2 = param
        $T21**  $3 = local $T21*
        bool**  $4 = local bool*
        $T92**  $5 = local $T92*
        $T92*   $6 = local $T92
        store   $T21* $0, $T21** $3
        store   bool* $1, bool** $4
        store   $T92* $2, $T92** $5
        $T21*   $7 = load $T21** $3
        bool*   $8 = load bool** $4
        arg     $T92* $6
        arg     $T21* $7
        arg     bool* $8
        call    $T93 @ctor_pair_DA877013F1FA3DF433EE3194A1248FB785DACAC4
        $T92*   $9 = load $T92** $5
        arg     $T92* $6
        $T92*   $10 = call $T94 @fn_move_D92954D71E1A2D52FF50BA2A5BD9649FC0A8C712
        arg     $T92* $9
        arg     $T92* $10
        call    $T97 @move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83
        ret     void
}

// std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::operator--()

function $T95* op_minus_minus_rb_node_iterator_869D433DA22C135B07E06B6085DF56CD51C53780 !61
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        $T2*    $5 = bitcast $T5* $4
        arg     $T2* $5
        $T2*    $6 = call $T100 @fn_get_prev_A6501809BB0AFCA16C8FAF0D16E33C5A36CEC338
        $T5*    $7 = bitcast $T2* $6
        $T21*   $8 = load $T21** $1
        $T5**   $9 = elemaddr $T21* $8, long 0
        store   $T5* $7, $T5** $9
        $T21*   $10 = load $T21** $1
        ret     $T21* $10
}

extern function $T100* fn_get_prev_A6501809BB0AFCA16C8FAF0D16E33C5A36CEC338

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::insert(std::pair<const int, int>&&)

function $T101* mfn_rb_tree_insert_5CAA050D711EE3A25D89F160BC91C1FF25D99714 !62
{
@0      $T33*   $0 = param
        $T4*    $1 = param
        $T92*   $2 = param
        $T33**  $3 = local $T33*
        $T4**   $4 = local $T4*
        $T92**  $5 = local $T92*
        $T5**   $6 = local $T5*
        $T5**   $7 = local $T5*
        bool*   $8 = local bool
        $T21*   $9 = local $T21
        $T21*   $10 = local $T21
        $T21*   $11 = local $T21
        $T21*   $12 = local $T21
        $T21*   $13 = local $T21
        bool*   $14 = local bool
        $T92*   $15 = local $T92
        $T21*   $16 = local $T21
        bool*   $17 = local bool
        $T92*   $18 = local $T92
        bool*   $19 = local bool
        $T92*   $20 = local $T92
        store   $T33* $0, $T33** $3
        store   $T4* $1, $T4** $4
        store   $T92* $2, $T92** $5
        $T33*   $21 = load $T33** $3
        $T21*   $22 = elemaddr $T33* $21, long 0
        arg     $T21* $22
        bool    $23 = call $T26 @mfn_unique_ptr_operator_bool_E85891987FDB288CBC2A747B5DF359219956E4AC
        bool    $24 = not bool $23
        branch  bool $24, @1, @2

@1      $T33*   $25 = load $T33** $3
        arg     $T33* $25
        call    $T43 @mfn_rb_tree_init_579B2C0966AEB8FA304099B38C9B45AB23DFA6AD
        jmp     @2

@2      $T33*   $26 = load $T33** $3
        arg     $T33* $26
        $T5*    $27 = call $T34 @mfn_rb_tree_root_1B3598BD7673997789F017438DD58AB432375423
        store   $T5* $27, $T5** $6
        $T33*   $28 = load $T33** $3
        $T21*   $29 = elemaddr $T33* $28, long 0
        arg     $T21* $29
        $T5*    $30 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        store   $T5* $30, $T5** $7
        store   bool true, bool* $8
        jmp     @5

@3      $T5*    $31 = load $T5** $6
        store   $T5* $31, $T5** $7
        $T33*   $32 = load $T33** $3
        $T30*   $33 = elemaddr $T33* $32, long 3
        $T33*   $34 = load $T33** $3
        $T30*   $35 = elemaddr $T33* $34, long 2
        $T4*    $36 = load $T4** $4
        arg     $T30* $35
        arg     $T4* $36
        int*    $37 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        $T33*   $38 = load $T33** $3
        $T30*   $39 = elemaddr $T33* $38, long 2
        $T5*    $40 = load $T5** $6
        arg     $T5* $40
        $T4*    $41 = call $T71 @mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9
        arg     $T30* $39
        arg     $T4* $41
        int*    $42 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        arg     $T30* $33
        arg     int* $37
        arg     int* $42
        bool    $43 = call $T72 @op_apply_less_2328D89C86144AD22E0B68798073E752D76F575A
        store   bool $43, bool* $8
        bool    $44 = load bool* $8
        branch  bool $44, @6, @8

@4      $T5*    $45 = load $T5** $7
        arg     $T21* $9
        arg     $T5* $45
        call    $T57 @ctor_rb_node_iterator_85AE9D8E08884A80A6EAD3D66F1A83F2141D5AAC
        bool    $46 = load bool* $8
        branch  bool $46, @9, @10

@5      $T5*    $47 = load $T5** $6
        bool    $48 = equal $T5* $47, $T5* null
        bool    $49 = not bool $48
        branch  bool $49, @3, @4

@6      $T5*    $50 = load $T5** $6
        $T2*    $51 = bitcast $T5* $50
        arg     $T2* $51
        $T2*    $52 = call $T35 @mfn_rb_node_base_get_left_CA41E0268374885EDF0A2EC4AB70D66EB7DEE351
        $T5*    $53 = bitcast $T2* $52
        store   $T5* $53, $T5** $6
        jmp     @7

@7      jmp     @5

@8      $T5*    $54 = load $T5** $6
        $T2*    $55 = bitcast $T5* $54
        arg     $T2* $55
        $T2*    $56 = call $T35 @mfn_rb_node_base_get_right_877D876415132D037A4918347CC0376C9CCECCD3
        $T5*    $57 = bitcast $T2* $56
        store   $T5* $57, $T5** $6
        jmp     @7

@9      $T33*   $58 = load $T33** $3
        arg     $T33* $58
        arg     $T21* $12
        call    $T78 @mfn_rb_tree_begin_8CD40EC22D4E02BF277FE8DDB318770C42BB2072
        arg     $T21* $9
        arg     $T21* $12
        bool    $59 = call $T83 @op_eq_200EB5C13C62E7A2B3C01FBD1E06D411A32737E9
        branch  bool $59, @11, @13

@10     $T33*   $60 = load $T33** $3
        $T30*   $61 = elemaddr $T33* $60, long 3
        $T33*   $62 = load $T33** $3
        $T30*   $63 = elemaddr $T33* $62, long 2
        arg     $T21* $9
        $T5*    $64 = call $T27 @mfn_rb_node_iterator_node_8F307AF5F8A594C187DE4B97A02B6A1AF61A476E
        arg     $T5* $64
        $T4*    $65 = call $T71 @mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9
        arg     $T30* $63
        arg     $T4* $65
        int*    $66 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        $T33*   $67 = load $T33** $3
        $T30*   $68 = elemaddr $T33* $67, long 2
        $T4*    $69 = load $T4** $4
        arg     $T30* $68
        arg     $T4* $69
        int*    $70 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        arg     $T30* $61
        arg     int* $66
        arg     int* $70
        bool    $71 = call $T72 @op_apply_less_2328D89C86144AD22E0B68798073E752D76F575A
        branch  bool $71, @15, @16

@11     $T33*   $72 = load $T33** $3
        $T5*    $73 = load $T5** $6
        $T5*    $74 = load $T5** $7
        $T4*    $75 = load $T4** $4
        arg     $T4* $75
        $T4*    $76 = call $T51 @fn_move_8E306F2AEABEF643D992290CC7205728319CCF76
        arg     $T33* $72
        arg     $T5* $73
        arg     $T5* $74
        arg     $T4* $76
        arg     $T21* $13
        call    $T88 @mfn_rb_tree_insert_BB08DF87022A98BD1E798F497B24AA8751DBFABA
        arg     $T21* $10
        arg     $T21* $13
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        $T92*   $77 = load $T92** $5
        store   bool true, bool* $14
        arg     $T21* $10
        arg     bool* $14
        arg     $T92* $15
        call    $T98 @fn_make_pair_0CFF03192AC8A7F5F95C67A8FEEF158723FD6C0F
        arg     $T92* $77
        arg     $T92* $15
        call    $T97 @move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83
        ret     void

@12     jmp     @10

@13     arg     $T21* $9
        $T21*   $78 = call $T95 @op_minus_minus_rb_node_iterator_869D433DA22C135B07E06B6085DF56CD51C53780
        jmp     @12

@15     $T33*   $79 = load $T33** $3
        $T5*    $80 = load $T5** $6
        $T5*    $81 = load $T5** $7
        $T4*    $82 = load $T4** $4
        arg     $T4* $82
        $T4*    $83 = call $T51 @fn_move_8E306F2AEABEF643D992290CC7205728319CCF76
        arg     $T33* $79
        arg     $T5* $80
        arg     $T5* $81
        arg     $T4* $83
        arg     $T21* $16
        call    $T88 @mfn_rb_tree_insert_BB08DF87022A98BD1E798F497B24AA8751DBFABA
        arg     $T21* $11
        arg     $T21* $16
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        $T92*   $84 = load $T92** $5
        store   bool true, bool* $17
        arg     $T21* $11
        arg     bool* $17
        arg     $T92* $18
        call    $T98 @fn_make_pair_0CFF03192AC8A7F5F95C67A8FEEF158723FD6C0F
        arg     $T92* $84
        arg     $T92* $18
        call    $T97 @move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83
        ret     void

@16     $T92*   $85 = load $T92** $5
        store   bool false, bool* $19
        arg     $T21* $9
        arg     bool* $19
        arg     $T92* $20
        call    $T98 @fn_make_pair_0CFF03192AC8A7F5F95C67A8FEEF158723FD6C0F
        arg     $T92* $85
        arg     $T92* $20
        call    $T97 @move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83
        ret     void
}

// std::map<int, int, std::less<int>>::insert(std::pair<const int, int>&&)

function $T102* mfn_map_insert_25EDB1D9C20F2017088E5193D61F8B1D6BB13775 !63
{
@0      $T66*   $0 = param
        $T4*    $1 = param
        $T92*   $2 = param
        $T66**  $3 = local $T66*
        $T4**   $4 = local $T4*
        $T92**  $5 = local $T92*
        $T92*   $6 = local $T92
        store   $T66* $0, $T66** $3
        store   $T4* $1, $T4** $4
        store   $T92* $2, $T92** $5
        $T92*   $7 = load $T92** $5
        $T66*   $8 = load $T66** $3
        $T33*   $9 = elemaddr $T66* $8, long 0
        $T4*    $10 = load $T4** $4
        arg     $T4* $10
        $T4*    $11 = call $T51 @fn_move_8E306F2AEABEF643D992290CC7205728319CCF76
        arg     $T33* $9
        arg     $T4* $11
        arg     $T92* $6
        call    $T101 @mfn_rb_tree_insert_5CAA050D711EE3A25D89F160BC91C1FF25D99714
        arg     $T92* $7
        arg     $T92* $6
        call    $T97 @move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83
        ret     void
}

// std::rb_node<std::pair<const int, int>>::value_ptr()

function $T71* mfn_rb_node_value_ptr_D6869136C8ABC7B8B59D4C7BC3EB2D366F33D431 !64
{
@0      $T5*    $0 = param
        $T5**   $1 = local $T5*
        store   $T5* $0, $T5** $1
        $T5*    $2 = load $T5** $1
        $T4*    $3 = elemaddr $T5* $2, long 1
        ret     $T4* $3
}

// std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::operator->()

function $T104* op_arrow_rb_node_iterator_570DCC10F0AFBA5270FC39CF8155F9B70FEB2B17 !65
{
@0      $T21*   $0 = param
        $T21**  $1 = local $T21*
        store   $T21* $0, $T21** $1
        $T21*   $2 = load $T21** $1
        $T5**   $3 = elemaddr $T21* $2, long 0
        $T5*    $4 = load $T5** $3
        arg     $T5* $4
        $T4*    $5 = call $T71 @mfn_rb_node_value_ptr_D6869136C8ABC7B8B59D4C7BC3EB2D366F33D431
        ret     $T4* $5
}

// std::map<int, int, std::less<int>>::operator[](const std::map<int, int, std::less<int>>::key_type&)

function $T105* op_subscript_map_EF3018F085D28307C99267A1E0AB9AE0BE535A02 !66
{
@0      $T66*   $0 = param
        int*    $1 = param
        $T66**  $2 = local $T66*
        int**   $3 = local int*
        int*    $4 = local int
        $T4*    $5 = local $T4
        $T92*   $6 = local $T92
        $T21*   $7 = local $T21
        int*    $8 = local int
        $T92*   $9 = local $T92
        store   $T66* $0, $T66** $2
        store   int* $1, int** $3
        int*    $10 = load int** $3
        int     $11 = load int* $10
        store   int $11, int* $4
        arg     int* $4
        int*    $12 = call $T52 @fn_move_F0520FC15A4B7F76236EF1D46D94A08F95521DBC
        store   int 0, int* $8
        arg     int* $8
        int*    $13 = call $T52 @fn_move_F0520FC15A4B7F76236EF1D46D94A08F95521DBC
        arg     $T4* $5
        arg     int* $12
        arg     int* $13
        call    $T69 @ctor_pair_CAC9203211522A5AD648016407EAC037DDFF9AAB
        $T66*   $14 = load $T66** $2
        arg     $T4* $5
        $T4*    $15 = call $T51 @fn_move_8E306F2AEABEF643D992290CC7205728319CCF76
        arg     $T66* $14
        arg     $T4* $15
        arg     $T92* $9
        call    $T102 @mfn_map_insert_25EDB1D9C20F2017088E5193D61F8B1D6BB13775
        arg     $T92* $6
        arg     $T92* $9
        call    $T97 @move_ctor_17DF2F2FCFEF9E89C2ED3E572E214412AC52CD83
        $T21*   $16 = elemaddr $T92* $6, long 0
        arg     $T21* $7
        arg     $T21* $16
        call    $T77 @copy_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        arg     $T21* $7
        $T4*    $17 = call $T104 @op_arrow_rb_node_iterator_570DCC10F0AFBA5270FC39CF8155F9B70FEB2B17
        int*    $18 = elemaddr $T4* $17, long 1
        ret     int* $18
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::empty() const

function $T106* mfn_rb_tree_empty_58DE4A2F70D6A8200F94FC2B04DE9272EFF25ED9 !67
{
@0      $T33*   $0 = param
        $T33**  $1 = local $T33*
        store   $T33* $0, $T33** $1
        $T33*   $2 = load $T33** $1
        long*   $3 = elemaddr $T33* $2, long 1
        long    $4 = load long* $3
        long    $5 = signextend int 0
        bool    $6 = equal long $4, long $5
        ret     bool $6
}

// std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::find(const std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::key_type&)

function $T107* mfn_rb_tree_find_D234FEC119FDF3B17059DB3D5F459224592AD119 !68
{
@0      $T33*   $0 = param
        int*    $1 = param
        $T21*   $2 = param
        $T33**  $3 = local $T33*
        int**   $4 = local int*
        $T21**  $5 = local $T21*
        $T5**   $6 = local $T5*
        $T5**   $7 = local $T5*
        $T21*   $8 = local $T21
        $T21*   $9 = local $T21
        $T21*   $10 = local $T21
        $T21*   $11 = local $T21
        bool*   $12 = local bool
        $T21*   $13 = local $T21
        store   $T33* $0, $T33** $3
        store   int* $1, int** $4
        store   $T21* $2, $T21** $5
        $T33*   $14 = load $T33** $3
        arg     $T33* $14
        bool    $15 = call $T106 @mfn_rb_tree_empty_58DE4A2F70D6A8200F94FC2B04DE9272EFF25ED9
        branch  bool $15, @1, @2

@1      $T21*   $16 = load $T21** $5
        $T33*   $17 = load $T33** $3
        arg     $T33* $17
        arg     $T21* $9
        call    $T78 @mfn_rb_tree_end_909487DDE486E2B1D633A24FA7E9BC53E9BFBA18
        arg     $T21* $16
        arg     $T21* $9
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void

@2      $T33*   $18 = load $T33** $3
        $T21*   $19 = elemaddr $T33* $18, long 0
        arg     $T21* $19
        $T5*    $20 = call $T27 @mfn_unique_ptr_get_283637895A534A47A11982DA8237DFD8C56030B3
        store   $T5* $20, $T5** $6
        $T33*   $21 = load $T33** $3
        arg     $T33* $21
        $T5*    $22 = call $T34 @mfn_rb_tree_root_1B3598BD7673997789F017438DD58AB432375423
        store   $T5* $22, $T5** $7
        jmp     @6

@4      $T33*   $23 = load $T33** $3
        $T30*   $24 = elemaddr $T33* $23, long 3
        $T33*   $25 = load $T33** $3
        $T30*   $26 = elemaddr $T33* $25, long 2
        $T5*    $27 = load $T5** $7
        arg     $T5* $27
        $T4*    $28 = call $T71 @mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9
        arg     $T30* $26
        arg     $T4* $28
        int*    $29 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        int*    $30 = load int** $4
        arg     $T30* $24
        arg     int* $29
        arg     int* $30
        bool    $31 = call $T72 @op_apply_less_2328D89C86144AD22E0B68798073E752D76F575A
        bool    $32 = not bool $31
        branch  bool $32, @7, @9

@5      $T5*    $33 = load $T5** $6
        arg     $T21* $10
        arg     $T5* $33
        call    $T57 @ctor_rb_node_iterator_85AE9D8E08884A80A6EAD3D66F1A83F2141D5AAC
        arg     $T21* $8
        arg     $T21* $10
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        $T33*   $34 = load $T33** $3
        arg     $T33* $34
        arg     $T21* $11
        call    $T78 @mfn_rb_tree_end_909487DDE486E2B1D633A24FA7E9BC53E9BFBA18
        arg     $T21* $8
        arg     $T21* $11
        bool    $35 = call $T83 @op_eq_200EB5C13C62E7A2B3C01FBD1E06D411A32737E9
        branch  bool $35, @10, @13

@6      $T5*    $36 = load $T5** $7
        bool    $37 = equal $T5* $36, $T5* null
        bool    $38 = not bool $37
        branch  bool $38, @4, @5

@7      $T5*    $39 = load $T5** $7
        store   $T5* $39, $T5** $6
        $T5*    $40 = load $T5** $7
        $T2*    $41 = bitcast $T5* $40
        arg     $T2* $41
        $T2*    $42 = call $T35 @mfn_rb_node_base_get_left_CA41E0268374885EDF0A2EC4AB70D66EB7DEE351
        $T5*    $43 = bitcast $T2* $42
        store   $T5* $43, $T5** $7
        jmp     @8

@8      jmp     @6

@9      $T5*    $44 = load $T5** $7
        $T2*    $45 = bitcast $T5* $44
        arg     $T2* $45
        $T2*    $46 = call $T35 @mfn_rb_node_base_get_right_877D876415132D037A4918347CC0376C9CCECCD3
        $T5*    $47 = bitcast $T2* $46
        store   $T5* $47, $T5** $7
        jmp     @8

@10     $T21*   $48 = load $T21** $5
        $T33*   $49 = load $T33** $3
        arg     $T33* $49
        arg     $T21* $13
        call    $T78 @mfn_rb_tree_end_909487DDE486E2B1D633A24FA7E9BC53E9BFBA18
        arg     $T21* $48
        arg     $T21* $13
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void

@11     ret     void

@12     $T21*   $50 = load $T21** $5
        arg     $T21* $8
        $T21*   $51 = call $T95 @fn_move_B3EF4CF8360663A1C9E8E55AEEC6B412713D65D3
        arg     $T21* $50
        arg     $T21* $51
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void

@13     $T33*   $52 = load $T33** $3
        $T30*   $53 = elemaddr $T33* $52, long 3
        int*    $54 = load int** $4
        $T33*   $55 = load $T33** $3
        $T30*   $56 = elemaddr $T33* $55, long 2
        arg     $T21* $8
        $T5*    $57 = call $T27 @mfn_rb_node_iterator_node_8F307AF5F8A594C187DE4B97A02B6A1AF61A476E
        arg     $T5* $57
        $T4*    $58 = call $T71 @mfn_rb_node_value_63999797887B48FA3BA429C5F4D79ACA4797F9F9
        arg     $T30* $56
        arg     $T4* $58
        int*    $59 = call $T70 @op_apply_select_first_E242149D1C4A7DE1EF8AFEA4165D03B12AE7B979
        arg     $T30* $53
        arg     int* $54
        arg     int* $59
        bool    $60 = call $T72 @op_apply_less_2328D89C86144AD22E0B68798073E752D76F575A
        branch  bool $60, @10, @12

@15     jmp     @11
}

// std::map<int, int, std::less<int>>::find(const std::map<int, int, std::less<int>>::key_type&)

function $T108* mfn_map_find_67110951612C4BA15AF43C2E0B3276FCD9584CF9 !69
{
@0      $T66*   $0 = param
        int*    $1 = param
        $T21*   $2 = param
        $T66**  $3 = local $T66*
        int**   $4 = local int*
        $T21**  $5 = local $T21*
        $T21*   $6 = local $T21
        store   $T66* $0, $T66** $3
        store   int* $1, int** $4
        store   $T21* $2, $T21** $5
        $T21*   $7 = load $T21** $5
        $T66*   $8 = load $T66** $3
        $T33*   $9 = elemaddr $T66* $8, long 0
        int*    $10 = load int** $4
        arg     $T33* $9
        arg     int* $10
        arg     $T21* $6
        call    $T107 @mfn_rb_tree_find_D234FEC119FDF3B17059DB3D5F459224592AD119
        arg     $T21* $7
        arg     $T21* $6
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void
}

// std::map<int, int, std::less<int>>::end()

function $T109* mfn_map_end_98D482E276F7F0BD4F2A89DF8F2EDF104E043AD3 !70
{
@0      $T66*   $0 = param
        $T21*   $1 = param
        $T66**  $2 = local $T66*
        $T21**  $3 = local $T21*
        $T21*   $4 = local $T21
        store   $T66* $0, $T66** $2
        store   $T21* $1, $T21** $3
        $T21*   $5 = load $T21** $3
        $T66*   $6 = load $T66** $2
        $T33*   $7 = elemaddr $T66* $6, long 0
        arg     $T33* $7
        arg     $T21* $4
        call    $T78 @mfn_rb_tree_end_909487DDE486E2B1D633A24FA7E9BC53E9BFBA18
        arg     $T21* $5
        arg     $T21* $4
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        ret     void
}

// std::operator<<(std::basic_ostream<char>&, const std::string&)

function $T112* op_shift_left_A47B5AF80881921DC010D065DEAA61BC11415DB0 !72
{
@0      $T14*   $0 = param
        $T111*  $1 = param
        $T14**  $2 = local $T14*
        $T111** $3 = local $T111*
        store   $T14* $0, $T14** $2
        store   $T111* $1, $T111** $3
        $T14*   $4 = load $T14** $2
        $T111*  $5 = load $T111** $3
        arg     $T14* $4
        arg     $T111* $5
        call    $T113 @mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE
        $T14*   $6 = load $T14** $2
        ret     $T14* $6
}

extern function $T113* mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE

// std::operator<<(std::basic_ostream<char>&, const char*)

function $T114* op_shift_left_DE924D2472D38FCEBDD89B348A558FD5FAA576F1 !73
{
@0      $T14*   $0 = param
        byte*   $1 = param
        $T14**  $2 = local $T14*
        byte**  $3 = local byte*
        store   $T14* $0, $T14** $2
        store   byte* $1, byte** $3
        $T14*   $4 = load $T14** $2
        $T12*   $5 = bitcast $T14* $4
        void**  $6 = elemaddr $T12* $5, long 0
        void*   $7 = load void** $6
        $T8*    $8 = bitcast void* $7
        long*   $9 = elemaddr $T12* $5, long 1
        long*   $10 = bitcast long* $9
        long    $11 = load long* $10
        byte*   $12 = bitcast $T12* $5
        byte*   $13 = ptroffset byte* $12, long $11
        $T12*   $14 = bitcast byte* $13
        void**  $15 = elemaddr $T8* $8, long 4
        void*   $16 = load void** $15
        $T16*   $17 = bitcast void* $16
        void**  $18 = elemaddr $T8* $8, long 5
        long*   $19 = bitcast void** $18
        long    $20 = load long* $19
        byte*   $21 = bitcast $T12* $14
        byte*   $22 = ptroffset byte* $21, long $20
        $T12*   $23 = bitcast byte* $22
        byte*   $24 = load byte** $3
        arg     $T12* $23
        arg     byte* $24
        call    $T16* $17
        $T14*   $25 = load $T14** $2
        ret     $T14* $25
}

// ::invoke_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*), parentFn=::main()

child function $T25* fn_invoke_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_CFC4D65E8CE78425401C31BCB18F2F8E5B633D93 !74
{
@0      void*   $0 = param
        $T66*   $1 = plocal $T66, 0
        $T21*   $2 = plocal $T21, 0
        $T111*  $3 = plocal $T111, 0
        int*    $4 = plocal int, 0
        int*    $5 = plocal int, 0
        $T21*   $6 = plocal $T21, 0
        $T21*   $7 = plocal $T21, 0
        $T111*  $8 = plocal $T111, 0
        int**   $9 = plocal int*, 0
        $T111*  $10 = plocal $T111, 0
        $T14**  $11 = plocal $T14*, 0
        void**  $12 = local void*
        int*    $13 = local int
        store   void* $0, void** $12
        store   int 1, int* $13
        arg     $T66* $1
        arg     int* $13
        int*    $14 = call $T105 @op_subscript_map_EF3018F085D28307C99267A1E0AB9AE0BE535A02
        store   int* $14, int** $9
        ret     void
}

// ::cleanup_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*), parentFn=::main()

child function $T25* fn_cleanup_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_881820708B66D769C05217C3AF32AB7D64382C82 !75
{
@0      void*   $0 = param
        $T66*   $1 = plocal $T66, 0
        $T21*   $2 = plocal $T21, 0
        $T111*  $3 = plocal $T111, 0
        int*    $4 = plocal int, 0
        int*    $5 = plocal int, 0
        $T21*   $6 = plocal $T21, 0
        $T21*   $7 = plocal $T21, 0
        $T111*  $8 = plocal $T111, 0
        int**   $9 = plocal int*, 0
        $T111*  $10 = plocal $T111, 0
        $T14**  $11 = plocal $T14*, 0
        void**  $12 = local void*
        store   void* $0, void** $12
        arg     $T66* $1
        call    $T67 @dtor_map_D91D456389CE69CF7E40BBEE173765EB2BAD7067
        ret     void
}

// ::invoke_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*), parentFn=::main()

child function $T25* fn_invoke_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_CACE0DCA66AF312423D4F2E55BC7AFDE501D42C1 !76
{
@0      void*   $0 = param
        $T66*   $1 = plocal $T66, 0
        $T21*   $2 = plocal $T21, 0
        $T111*  $3 = plocal $T111, 0
        int*    $4 = plocal int, 0
        int*    $5 = plocal int, 0
        $T21*   $6 = plocal $T21, 0
        $T21*   $7 = plocal $T21, 0
        $T111*  $8 = plocal $T111, 0
        int**   $9 = plocal int*, 0
        $T111*  $10 = plocal $T111, 0
        $T14**  $11 = plocal $T14*, 0
        void**  $12 = local void*
        store   void* $0, void** $12
        arg     $T21* $2
        $T4*    $13 = call $T104 @op_arrow_rb_node_iterator_570DCC10F0AFBA5270FC39CF8155F9B70FEB2B17
        int*    $14 = elemaddr $T4* $13, long 1
        int     $15 = load int* $14
        arg     int $15
        arg     $T111* $8
        call    $T119 @fn_to_string_8AE9B97F02FD9A59C3D292EF23DE031B355D8511
        arg     $T111* $10
        arg     $T111* $8
        call    $T120 @move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2
        arg     $T111* $8
        call    $T121 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     void
}

extern function $T119* fn_to_string_8AE9B97F02FD9A59C3D292EF23DE031B355D8511

extern function $T120* move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2

extern function $T121* dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2

// ::cleanup_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*), parentFn=::main()

child function $T25* fn_cleanup_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_FE226EE3E143DC0FF6B66C10487539CEFDC22CFA !77
{
@0      void*   $0 = param
        $T66*   $1 = plocal $T66, 0
        $T21*   $2 = plocal $T21, 0
        $T111*  $3 = plocal $T111, 0
        int*    $4 = plocal int, 0
        int*    $5 = plocal int, 0
        $T21*   $6 = plocal $T21, 0
        $T21*   $7 = plocal $T21, 0
        $T111*  $8 = plocal $T111, 0
        int**   $9 = plocal int*, 0
        $T111*  $10 = plocal $T111, 0
        $T14**  $11 = plocal $T14*, 0
        void**  $12 = local void*
        store   void* $0, void** $12
        arg     $T66* $1
        call    $T67 @dtor_map_D91D456389CE69CF7E40BBEE173765EB2BAD7067
        ret     void
}

// ::invoke_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*), parentFn=::main()

child function $T25* fn_invoke_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_985E3E80CC84DF35611645472E9FDE1C312C70A7 !78
{
@0      void*   $0 = param
        $T66*   $1 = plocal $T66, 0
        $T21*   $2 = plocal $T21, 0
        $T111*  $3 = plocal $T111, 0
        int*    $4 = plocal int, 0
        int*    $5 = plocal int, 0
        $T21*   $6 = plocal $T21, 0
        $T21*   $7 = plocal $T21, 0
        $T111*  $8 = plocal $T111, 0
        int**   $9 = plocal int*, 0
        $T111*  $10 = plocal $T111, 0
        $T14**  $11 = plocal $T14*, 0
        void**  $12 = local void*
        store   void* $0, void** $12
        arg     $T14* variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        arg     $T111* $3
        $T14*   $13 = call $T112 @op_shift_left_A47B5AF80881921DC010D065DEAA61BC11415DB0
        arg     $T14* $13
        arg     byte* string_3_compile_unit_2B96B93279757D013A42886094ED44C5626597A5
        $T14*   $14 = call $T114 @op_shift_left_DE924D2472D38FCEBDD89B348A558FD5FAA576F1
        store   $T14* $14, $T14** $11
        ret     void
}

// ::cleanup_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*), parentFn=::main()

child function $T25* fn_cleanup_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_094E1E53060878AE84540575EA29295565987C1E !79
{
@0      void*   $0 = param
        $T66*   $1 = plocal $T66, 0
        $T21*   $2 = plocal $T21, 0
        $T111*  $3 = plocal $T111, 0
        int*    $4 = plocal int, 0
        int*    $5 = plocal int, 0
        $T21*   $6 = plocal $T21, 0
        $T21*   $7 = plocal $T21, 0
        $T111*  $8 = plocal $T111, 0
        int**   $9 = plocal int*, 0
        $T111*  $10 = plocal $T111, 0
        $T14**  $11 = plocal $T14*, 0
        void**  $12 = local void*
        store   void* $0, void** $12
        arg     $T111* $3
        call    $T121 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        arg     $T66* $1
        call    $T67 @dtor_map_D91D456389CE69CF7E40BBEE173765EB2BAD7067
        ret     void
}

// ::main()

function $T125* fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D !80
{
@0      $T66*   $0 = local $T66
        $T21*   $1 = local $T21
        $T111*  $2 = local $T111
        int*    $3 = local int
        int*    $4 = local int
        $T21*   $5 = local $T21
        $T21*   $6 = local $T21
        $T111*  $7 = local $T111
        int**   $8 = local int*
        $T111*  $9 = local $T111
        $T14**  $10 = local $T14*
        arg     $T66* $0
        call    $T67 @default_ctor_30B6EAC544BBBBF503E6BE8F202AF396FF25DF0B
        void*   $11 = getrbp
        arg     $T25 @fn_invoke_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_CFC4D65E8CE78425401C31BCB18F2F8E5B633D93
        arg     $T25 @fn_cleanup_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_881820708B66D769C05217C3AF32AB7D64382C82
        arg     void* $11
        call    $T127 @ort_invoke
        int*    $12 = load int** $8
        store   int 2, int* $12
        store   int 1, int* $4
        arg     $T66* $0
        arg     int* $4
        arg     $T21* $5
        call    $T108 @mfn_map_find_67110951612C4BA15AF43C2E0B3276FCD9584CF9
        arg     $T21* $1
        arg     $T21* $5
        call    $T77 @move_ctor_rb_node_iterator_7F638D08966A049DF9F215AF55F4C651C95BA269
        arg     $T66* $0
        arg     $T21* $6
        call    $T109 @mfn_map_end_98D482E276F7F0BD4F2A89DF8F2EDF104E043AD3
        arg     $T21* $1
        arg     $T21* $6
        bool    $13 = call $T83 @op_eq_200EB5C13C62E7A2B3C01FBD1E06D411A32737E9
        bool    $14 = not bool $13
        branch  bool $14, @1, @2

@1      void*   $15 = getrbp
        arg     $T25 @fn_invoke_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_CACE0DCA66AF312423D4F2E55BC7AFDE501D42C1
        arg     $T25 @fn_cleanup_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_FE226EE3E143DC0FF6B66C10487539CEFDC22CFA
        arg     void* $15
        call    $T127 @ort_invoke
        arg     $T111* $2
        arg     $T111* $9
        call    $T120 @move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2
        $T12*   $16 = bitcast $T14* variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        arg     $T12* $16
        call    $T128 @mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250
        void*   $17 = getrbp
        arg     $T25 @fn_invoke_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_985E3E80CC84DF35611645472E9FDE1C312C70A7
        arg     $T25 @fn_cleanup_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5_094E1E53060878AE84540575EA29295565987C1E
        arg     void* $17
        call    $T127 @ort_invoke
        $T14*   $18 = load $T14** $10
        arg     $T111* $9
        call    $T121 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        arg     $T111* $2
        call    $T121 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        jmp     @2

@2      jmp     @3

@3      arg     $T66* $0
        call    $T67 @dtor_map_D91D456389CE69CF7E40BBEE173765EB2BAD7067
        ret     int 0
}

extern function $T127* ort_invoke

extern function $T128* mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250

metadata
{
        !0 = {fullName: "std::rb_node_base"}
        !1 = {fullName: "std::pair<const int, int>"}
        !2 = {fullName: "std::rb_node<std::pair<const int, int>>"}
        !3 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/map/map.cpp"}
        !4 = {fullName: "std::ios_base"}
        !5 = {fullName: "std::basic_ios<char>"}
        !6 = {fullName: "std::basic_ostream<char>"}
        !7 = {fullName: "std::rb_node<std::pair<const int, int>>::@destructor() override", nodeType: 1}
        !8 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>"}
        !9 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>::~unique_ptr()", nodeType: 1}
        !10 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>::operator_bool() const", nodeType: 1}
        !11 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>::operator->() const", nodeType: 1}
        !12 = {fullName: "std::select_first<const int, int>"}
        !13 = {fullName: "std::less<int>"}
        !14 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>"}
        !15 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::root()", nodeType: 1}
        !16 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::set_root(std::rb_node<std::pair<const int, int>>*)", nodeType: 1}
        !17 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>::get() const", nodeType: 1}
        !18 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::set_leftmost(std::rb_node<std::pair<const int, int>>*)", nodeType: 1}
        !19 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::set_rightmost(std::rb_node<std::pair<const int, int>>*)", nodeType: 1}
        !20 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::clear()", nodeType: 1}
        !21 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::~rb_tree()", nodeType: 1}
        !22 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>::unique_ptr()", nodeType: 1}
        !23 = {fullName: "std::select_first<const int, int>::@class_default_ctor()", nodeType: 1}
        !24 = {fullName: "std::less<int>::@class_default_ctor()", nodeType: 1}
        !25 = {fullName: "std::pair<const int, int>::pair()", nodeType: 1}
        !26 = {fullName: "std::move(std::pair<const int, int>&&)", nodeType: 1}
        !27 = {fullName: "std::move(const int&&)", nodeType: 1}
        !28 = {fullName: "std::move(int&&)", nodeType: 1}
        !29 = {fullName: "std::pair<const int, int>::pair(std::pair<const int, int>&&)", nodeType: 1}
        !30 = {fullName: "std::rb_node<std::pair<const int, int>>::rb_node(std::pair<const int, int>&&, std::rb_node_base*)", nodeType: 1}
        !31 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const int, int>>>::reset(std::rb_node<std::pair<const int, int>>*)", nodeType: 1}
        !32 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::init()", nodeType: 1}
        !33 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::rb_tree()", nodeType: 1}
        !34 = {fullName: "std::map<int, int, std::less<int>>"}
        !35 = {fullName: "std::map<int, int, std::less<int>>::map()", nodeType: 1}
        !36 = {fullName: "std::map<int, int, std::less<int>>::@destructor()", nodeType: 1}
        !37 = {fullName: "std::pair<const int, int>::pair(const int&&, int&&)", nodeType: 1}
        !38 = {fullName: "std::select_first<const int, int>::operator()(const std::pair<const int, int>&) const", nodeType: 1}
        !39 = {fullName: "std::rb_node<std::pair<const int, int>>::value()", nodeType: 1}
        !40 = {fullName: "std::less<int>::operator()(const int&, const int&) const", nodeType: 1}
        !41 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>"}
        !42 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::rb_node_iterator(std::rb_node<std::pair<const int, int>>*)", nodeType: 1}
        !43 = {fullName: "std::move(std::rb_node<std::pair<const int, int>>*&&)", nodeType: 1}
        !44 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::@class_move_ctor(std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&&)", nodeType: 1}
        !45 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::end()", nodeType: 1}
        !46 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::leftmost()", nodeType: 1}
        !47 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::begin()", nodeType: 1}
        !48 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::node() const", nodeType: 1}
        !49 = {fullName: "std::operator==(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&, const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&)", nodeType: 1}
        !50 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::rightmost()", nodeType: 1}
        !51 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::root_ptr()", nodeType: 1}
        !52 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::insert(std::rb_node<std::pair<const int, int>>*, std::rb_node<std::pair<const int, int>>*, std::pair<const int, int>&&)", nodeType: 1}
        !53 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::@class_copy_ctor(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&)", nodeType: 1}
        !54 = {fullName: "std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>"}
        !55 = {fullName: "std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>::pair(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&, const bool&)", nodeType: 1}
        !56 = {fullName: "std::move(std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>&&)", nodeType: 1}
        !57 = {fullName: "std::move(std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&&)", nodeType: 1}
        !58 = {fullName: "std::move(bool&&)", nodeType: 1}
        !59 = {fullName: "std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>::pair(std::pair<std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>, bool>&&)", nodeType: 1}
        !60 = {fullName: "std::make_pair(const std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>&, const bool&)", nodeType: 1}
        !61 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::operator--()", nodeType: 1}
        !62 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::insert(std::pair<const int, int>&&)", nodeType: 1}
        !63 = {fullName: "std::map<int, int, std::less<int>>::insert(std::pair<const int, int>&&)", nodeType: 1}
        !64 = {fullName: "std::rb_node<std::pair<const int, int>>::value_ptr()", nodeType: 1}
        !65 = {fullName: "std::rb_node_iterator<std::pair<const int, int>, std::pair<const int, int>&, std::pair<const int, int>*>::operator->()", nodeType: 1}
        !66 = {fullName: "std::map<int, int, std::less<int>>::operator[](const std::map<int, int, std::less<int>>::key_type&)", nodeType: 1}
        !67 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::empty() const", nodeType: 1}
        !68 = {fullName: "std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::find(const std::rb_tree<int, std::pair<const int, int>, std::select_first<const int, int>, std::less<int>>::key_type&)", nodeType: 1}
        !69 = {fullName: "std::map<int, int, std::less<int>>::find(const std::map<int, int, std::less<int>>::key_type&)", nodeType: 1}
        !70 = {fullName: "std::map<int, int, std::less<int>>::end()", nodeType: 1}
        !71 = {fullName: "std::basic_string<char>"}
        !72 = {fullName: "std::operator<<(std::basic_ostream<char>&, const std::string&)", nodeType: 1}
        !73 = {fullName: "std::operator<<(std::basic_ostream<char>&, const char*)", nodeType: 1}
        !74 = {fullName: "::invoke_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*)", nodeType: 1, parentName: "::main()"}
        !75 = {fullName: "::cleanup_0_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*)", nodeType: 1, parentName: "::main()"}
        !76 = {fullName: "::invoke_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*)", nodeType: 1, parentName: "::main()"}
        !77 = {fullName: "::cleanup_1_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*)", nodeType: 1, parentName: "::main()"}
        !78 = {fullName: "::invoke_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*)", nodeType: 1, parentName: "::main()"}
        !79 = {fullName: "::cleanup_2_compile_unit_2B96B93279757D013A42886094ED44C5626597A5(void*)", nodeType: 1, parentName: "::main()"}
        !80 = {fullName: "::main()", nodeType: 1}
}
