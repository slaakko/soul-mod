types
{
        $T2 = type { void*, long } !0 // std::exception
        $T3 = type { $T2 } !1 // std::bad_alloc
        $T4 = type function void()
        $T5 = type function void*(ulong)
        $T6 = type function void*(void*, byte*, byte*, int)
        $T7 = type function void($T3*)
        $T8 = type function void(void*, ulong, ulong)
        $T15 = type function void*()
        $T16 = type [6 x void*]
        $T18 = type function void(void*)
        $T19 = type function int(int, byte**)
        $T21 = type function int()
}

data
{
        byte string_0_ = "::__main_wrapper__(int, const char**)\00"
        byte string_1_ = "D:/work/soul-mod/tools/otava/test/if_temporary/__main__.cpp\00"
}

// ::__global_init__()

function $T4* __global_init__ !2
{
@0      $T3**   $0 = local $T3*
        ulong   $1 = bitcast long 16
        arg     ulong $1
        void*   $2 = call $T5 @op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44
        arg     void* $2
        arg     byte* string_0_
        arg     byte* string_1_
        arg     int 0
        void*   $3 = call $T6 @ort_debug_operator_new
        $T3*    $4 = bitcast void* $3
        store   $T3* $4, $T3** $0
        $T3*    $5 = load $T3** $0
        arg     $T3* $5
        call    $T7 @default_ctor_AF25A380FFB5E1D3D906D613C4B5D31B93E12B90
        void*   $6 = bitcast $T3* $4
        arg     void* $6
        arg     ulong 13822261819723092137
        arg     ulong 5711937791238266219
        call    $T8 @ort_set_bad_alloc
        call    $T4 @fn___dynamic_init__compile_unit_84DEC0F7E818042650E66C07AE1A45F9365DA9F9_7CD94554958218325ECA90097BE8CEC0A2147FCB
        call    $T4 @fn___dynamic_init__compile_unit_7275B3F43E1B6C49FBA7613C55EAB5C1EF1FBD06_60D0C2082F064AB0E80C1C4615F149895D0FAC08
        call    $T4 @fn___dynamic_init__compile_unit_3CAE5CCE46FBE978DC59D230EA95889E441EA158_B913E0E6F8C849FBD2C1236B017FD914A3461FDB
        call    $T4 @fn___dynamic_init__compile_unit_7434ED6B99D8BE329DCA42E600CB1F406A229502_A873A0CFA4000598FD35C2EC945CDFF9F75D6DFB
        ret     void
}

extern function $T5* op_new_5B6923745977D1C32781F9B20BA918D28BB3DF44

extern function $T6* ort_debug_operator_new

extern function $T7* default_ctor_AF25A380FFB5E1D3D906D613C4B5D31B93E12B90

extern function $T8* ort_set_bad_alloc

extern function $T4* fn___dynamic_init__compile_unit_84DEC0F7E818042650E66C07AE1A45F9365DA9F9_7CD94554958218325ECA90097BE8CEC0A2147FCB

extern function $T4* fn___dynamic_init__compile_unit_7275B3F43E1B6C49FBA7613C55EAB5C1EF1FBD06_60D0C2082F064AB0E80C1C4615F149895D0FAC08

extern function $T4* fn___dynamic_init__compile_unit_3CAE5CCE46FBE978DC59D230EA95889E441EA158_B913E0E6F8C849FBD2C1236B017FD914A3461FDB

extern function $T4* fn___dynamic_init__compile_unit_7434ED6B99D8BE329DCA42E600CB1F406A229502_A873A0CFA4000598FD35C2EC945CDFF9F75D6DFB

// ::__global_done__()

function $T4* __global_done__ !3
{
@0      void*   $0 = call $T15 @ort_get_bad_alloc
        $T3*    $1 = bitcast void* $0
        $T2*    $2 = bitcast $T3* $1
        void**  $3 = elemaddr $T2* $2, long 0
        void*   $4 = load void** $3
        $T16*   $5 = bitcast void* $4
        long*   $6 = elemaddr $T2* $2, long 1
        long*   $7 = bitcast long* $6
        long    $8 = load long* $7
        byte*   $9 = bitcast $T2* $2
        byte*   $10 = ptroffset byte* $9, long $8
        $T2*    $11 = bitcast byte* $10
        void**  $12 = elemaddr $T16* $5, long 2
        void*   $13 = load void** $12
        $T7*    $14 = bitcast void* $13
        void**  $15 = elemaddr $T16* $5, long 3
        long*   $16 = bitcast void** $15
        long    $17 = load long* $16
        byte*   $18 = bitcast $T2* $11
        byte*   $19 = ptroffset byte* $18, long $17
        $T2*    $20 = bitcast byte* $19
        arg     $T2* $20
        call    $T7* $14
        void*   $21 = call $T15 @ort_get_bad_alloc
        $T3*    $22 = bitcast void* $21
        $T2*    $23 = bitcast $T3* $22
        void**  $24 = elemaddr $T2* $23, long 0
        void*   $25 = load void** $24
        $T16*   $26 = bitcast void* $25
        long*   $27 = elemaddr $T2* $23, long 1
        long*   $28 = bitcast long* $27
        long    $29 = load long* $28
        byte*   $30 = bitcast $T2* $23
        byte*   $31 = ptroffset byte* $30, long $29
        $T2*    $32 = bitcast byte* $31
        arg     $T2* $32
        call    $T18 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        ret     void
}

extern function $T15* ort_get_bad_alloc

extern function $T18* op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4

// ::__main_wrapper__(int, const char**)

function $T19* fn___main_wrapper___6AD707E323E364CC721579A108E141F517AB5EF3 !5
{
@0      int     $0 = param
        byte**  $1 = param
        int*    $2 = local int
        byte*** $3 = local byte**
        int*    $4 = local int
        store   int $0, int* $2
        store   byte** $1, byte*** $3
        call    $T4 @__global_init__
        int     $5 = call $T21 @fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D
        store   int $5, int* $4
        call    $T4 @fn_run_at_exits_E93D88F8DBABD96E599F01AFA804D3BB619FDE8F
        call    $T4 @__global_done__
        int     $6 = load int* $4
        ret     int $6
}

extern function $T21* fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D

extern function $T4* fn_run_at_exits_E93D88F8DBABD96E599F01AFA804D3BB619FDE8F

metadata
{
        !0 = {fullName: "std::exception"}
        !1 = {fullName: "std::bad_alloc"}
        !2 = {fullName: "::__global_init__()", nodeType: 1}
        !3 = {fullName: "::__global_done__()", nodeType: 1}
        !4 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/if_temporary/__main__.cpp"}
        !5 = {fullName: "::__main_wrapper__(int, const char**)", nodeType: 1}
}
