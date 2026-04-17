types
{
        $T0 = type function int()
        $T1 = type function void*(ulong)
        $T2 = type function void*(void*, byte*, byte*, int)
}

data
{
        byte string_0_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F = "::main()\00"
        byte string_1_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F = "D:/work/soul-mod/tools/otava/test/new_int/main.cpp\00"
}

// ::main()

function $T0* fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D !1
{
@0      int**   $0 = local int*
        int**   $1 = local int*
        ulong   $2 = bitcast long 4
        arg     ulong $2
        void*   $3 = call $T1 @op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44
        arg     void* $3
        arg     byte* string_0_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F
        arg     byte* string_1_compile_unit_630A9B1EBA2DC4A85D027F3F52F82CAABC2E139F
        arg     int 1
        void*   $4 = call $T2 @ort_debug_operator_new
        int*    $5 = bitcast void* $4
        store   int* $5, int** $1
        int*    $6 = load int** $1
        store   int 1, int* $6
        store   int* $5, int** $0
        ret     int 0
}

extern function $T1* op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44

extern function $T2* ort_debug_operator_new

metadata
{
        !0 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/new_int/main.cpp"}
        !1 = {fullName: "::main()", nodeType: 1}
}
