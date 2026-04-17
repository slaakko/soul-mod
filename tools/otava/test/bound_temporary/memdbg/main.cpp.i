types
{
        $T0 = type [6 x void*]
        $T4 = type { void*, long, int } !1 // std::ios_base
        $T5 = type { $T4 } !2 // std::basic_ios<char>
        $T6 = type { $T5, int } !3 // std::basic_ostream<char>
        $T7 = type function void($T6*)
        $T8 = type function void($T6*, byte*)
        $T9 = type [4 x void*]
        $T10 = type function void($T5*)
        $T12 = type { byte*, long, long } !4 // std::basic_string<char>
        $T13 = type function void($T12*)
        $T14 = type function void($T12*, byte*)
        $T15 = type function $T6*($T6*, $T12*)
        $T16 = type function void($T6*, $T12*)
        $T17 = type function $T6*($T6*, byte*)
        $T19 = type function void(void*)
        $T22 = type function int()
        $T23 = type function void($T4*)
        $T25 = type function void($T19*, $T19*, void*)
}

data
{
        $T0 vtab_class_basic_ostream_593FABF644ED49E7CDB1C64A39F756C4EAC0BCD5_8349A546AE8A12F97573B4E6492F3AE563BC8C7C = [ void* conv(ulong 12164968375907051723), void* conv(ulong 11109897516647986643), void* conv($T7 @dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3), void* conv(long 0), void* conv($T8 @mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0), void* conv(long 0) ]
        $T9 vtab_class_basic_ios_827A979AF3C805EA40D8AB412FA5FDC92FAA9E41_8349A546AE8A12F97573B4E6492F3AE563BC8C7C = [ void* conv(ulong 15383186997497895682), void* conv(ulong 4564523079047796995), void* conv($T10 @dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91), void* conv(long 0) ]
        byte string_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51 = "foo\00"
        $T6 variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40;
        byte string_1_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51 = "\0A\00"
        byte string_2_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51 = "abc\00"
}

extern function $T7* dtor_basic_ostream_032EAEA7F490E4FCA6679FC5E03956D7691E8FA3

extern function $T8* mfn_basic_ostream_write_55249620288160611A92FEA4F1211B021CE364B0

extern function $T10* dtor_basic_ios_A0A3B6F3ED9C1DD26632E88149912025ED293B91

// ::foo()

function $T13* fn_foo_F97C8F71C78EFEFCC863033F9AF286DFC355CC16 !5
{
@0      $T12*   $0 = param
        $T12**  $1 = local $T12*
        store   $T12* $0, $T12** $1
        $T12*   $2 = load $T12** $1
        arg     $T12* $2
        arg     byte* string_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
        call    $T14 @ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        ret     void
}

extern function $T14* ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF

// std::operator<<(std::basic_ostream<char>&, const std::string&)

function $T15* op_shift_left_9EB1D9660978D0826A659045ADFD694CF02666AC !6
{
@0      $T6*    $0 = param
        $T12*   $1 = param
        $T6**   $2 = local $T6*
        $T12**  $3 = local $T12*
        store   $T6* $0, $T6** $2
        store   $T12* $1, $T12** $3
        $T6*    $4 = load $T6** $2
        $T12*   $5 = load $T12** $3
        arg     $T6* $4
        arg     $T12* $5
        call    $T16 @mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE
        $T6*    $6 = load $T6** $2
        ret     $T6* $6
}

extern function $T16* mfn_basic_ostream_write_181FEA666828459989FEEDD38C86F9267896CBCE

// std::operator<<(std::basic_ostream<char>&, const char*)

function $T17* op_shift_left_DB559511639BB1719947D97B2A3D8178474C7C78 !7
{
@0      $T6*    $0 = param
        byte*   $1 = param
        $T6**   $2 = local $T6*
        byte**  $3 = local byte*
        store   $T6* $0, $T6** $2
        store   byte* $1, byte** $3
        $T6*    $4 = load $T6** $2
        $T4*    $5 = bitcast $T6* $4
        void**  $6 = elemaddr $T4* $5, long 0
        void*   $7 = load void** $6
        $T0*    $8 = bitcast void* $7
        long*   $9 = elemaddr $T4* $5, long 1
        long*   $10 = bitcast long* $9
        long    $11 = load long* $10
        byte*   $12 = bitcast $T4* $5
        byte*   $13 = ptroffset byte* $12, long $11
        $T4*    $14 = bitcast byte* $13
        void**  $15 = elemaddr $T0* $8, long 4
        void*   $16 = load void** $15
        $T8*    $17 = bitcast void* $16
        void**  $18 = elemaddr $T0* $8, long 5
        long*   $19 = bitcast void** $18
        long    $20 = load long* $19
        byte*   $21 = bitcast $T4* $14
        byte*   $22 = ptroffset byte* $21, long $20
        $T4*    $23 = bitcast byte* $22
        byte*   $24 = load byte** $3
        arg     $T4* $23
        arg     byte* $24
        call    $T8* $17
        $T6*    $25 = load $T6** $2
        ret     $T6* $25
}

// ::invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51(void*), parentFn=::main()

child function $T19* fn_invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_B344C7A7992C62A9519B3D37A5DFFF4522A5BE94 !8
{
@0      void*   $0 = param
        $T12*   $1 = plocal $T12, 0
        $T12*   $2 = plocal $T12, 0
        $T6**   $3 = plocal $T6*, 0
        void**  $4 = local void*
        store   void* $0, void** $4
        arg     $T12* $2
        call    $T13 @fn_foo_F97C8F71C78EFEFCC863033F9AF286DFC355CC16
        arg     $T6* variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        arg     $T12* $2
        $T6*    $5 = call $T15 @op_shift_left_9EB1D9660978D0826A659045ADFD694CF02666AC
        arg     $T6* $5
        arg     byte* string_1_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
        $T6*    $6 = call $T17 @op_shift_left_DB559511639BB1719947D97B2A3D8178474C7C78
        store   $T6* $6, $T6** $3
        arg     $T12* $2
        call    $T13 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     void
}

extern function $T13* dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2

// ::cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51(void*), parentFn=::main()

child function $T19* fn_cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_C9B7651690D9426DD426F44AE5BEEA58A3201014 !9
{
@0      void*   $0 = param
        $T12*   $1 = plocal $T12, 0
        $T12*   $2 = plocal $T12, 0
        $T6**   $3 = plocal $T6*, 0
        void**  $4 = local void*
        store   void* $0, void** $4
        arg     $T12* $1
        call    $T13 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     void
}

// ::main()

function $T22* fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D !10
{
@0      $T12*   $0 = local $T12
        $T12*   $1 = local $T12
        $T6**   $2 = local $T6*
        arg     $T12* $0
        arg     byte* string_2_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51
        call    $T14 @ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        $T4*    $3 = bitcast $T6* variable_cout_3E3E78378BB358BBF644B3033FE8F2A2A3E30E40
        arg     $T4* $3
        call    $T23 @mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250
        void*   $4 = getrbp
        arg     $T19 @fn_invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_B344C7A7992C62A9519B3D37A5DFFF4522A5BE94
        arg     $T19 @fn_cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51_C9B7651690D9426DD426F44AE5BEEA58A3201014
        arg     void* $4
        call    $T25 @ort_invoke
        $T6*    $5 = load $T6** $2
        arg     $T12* $0
        call    $T13 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     int 0
}

extern function $T23* mfn_ios_base_init_713928C50B451E6B7CA0BD4709EE931FB4A6E250

extern function $T25* ort_invoke

metadata
{
        !0 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/bound_temporary/main.cpp"}
        !1 = {fullName: "std::ios_base"}
        !2 = {fullName: "std::basic_ios<char>"}
        !3 = {fullName: "std::basic_ostream<char>"}
        !4 = {fullName: "std::basic_string<char>"}
        !5 = {fullName: "::foo()", nodeType: 1}
        !6 = {fullName: "std::operator<<(std::basic_ostream<char>&, const std::string&)", nodeType: 1}
        !7 = {fullName: "std::operator<<(std::basic_ostream<char>&, const char*)", nodeType: 1}
        !8 = {fullName: "::invoke_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51(void*)", nodeType: 1, parentName: "::main()"}
        !9 = {fullName: "::cleanup_0_compile_unit_CED9663DFD85CE1D7E8D9A43993929CA53E69C51(void*)", nodeType: 1, parentName: "::main()"}
        !10 = {fullName: "::main()", nodeType: 1}
}
