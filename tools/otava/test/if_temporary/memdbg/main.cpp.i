types
{
        $T0 = type function bool(int, int)
        $T2 = type { byte*, long, long } !2 // std::basic_string<char>
        $T3 = type function $T2*($T2*)
        $T4 = type function void(void*)
        $T5 = type function $T2*($T2*, $T2*)
        $T7 = type function void($T2*)
        $T8 = type function void(byte*, $T2*, $T2*)
        $T9 = type function void($T2*, byte*)
        $T11 = type function void($T4*, $T4*, void*)
        $T12 = type function void($T2*, $T2*)
        $T13 = type function bool($T2*, $T2*)
        $T14 = type function long($T2*)
        $T15 = type function byte*($T2*, long)
        $T16 = type function int($T2*, $T2*)
        $T17 = type function int()
}

data
{
        byte string_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844 = "~\00"
        byte string_1_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844 = "abc\00"
        byte string_2_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844 = "def\00"
}

// ::TypesEqual(int, int)

function $T0* fn_TypesEqual_0A6755C2E3D1E8E832B053E7596792EA01CDF275 !1
{
@0      int     $0 = param
        int     $1 = param
        int*    $2 = local int
        int*    $3 = local int
        store   int $0, int* $2
        store   int $1, int* $3
        int     $4 = load int* $2
        int     $5 = load int* $3
        bool    $6 = equal int $4, int $5
        ret     bool $6
}

// std::move(std::basic_string<char>&&)

function $T3* fn_move_0327402166CAFF8AE1BE1FFDAAC2CF4FCCD50FE6 !3
{
@0      $T2*    $0 = param
        $T2**   $1 = local $T2*
        store   $T2* $0, $T2** $1
        $T2*    $2 = load $T2** $1
        ret     $T2* $2
}

// ::invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844(void*), parentFn=std::operator+(const char*, const std::basic_string<char>&)

child function $T4* fn_invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_F43C493D0B43CB2040D56EBAB7844295B56EF727 !4
{
@0      void*   $0 = param
        byte**  $1 = plocal byte*, 0
        $T2**   $2 = plocal $T2*, 0
        $T2**   $3 = plocal $T2*, 0
        $T2*    $4 = plocal $T2, 0
        $T2**   $5 = plocal $T2*, 0
        void**  $6 = local void*
        store   void* $0, void** $6
        $T2*    $7 = load $T2** $2
        arg     $T2* $4
        arg     $T2* $7
        $T2*    $8 = call $T5 @mfn_basic_string_append_2FC34573E365F5FCC5D8778E922A455E268A3849
        store   $T2* $8, $T2** $5
        ret     void
}

extern function $T5* mfn_basic_string_append_2FC34573E365F5FCC5D8778E922A455E268A3849

// ::cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844(void*), parentFn=std::operator+(const char*, const std::basic_string<char>&)

child function $T4* fn_cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_C03E7148CE3BAA3DB10510782DCF03D351331848 !5
{
@0      void*   $0 = param
        byte**  $1 = plocal byte*, 0
        $T2**   $2 = plocal $T2*, 0
        $T2**   $3 = plocal $T2*, 0
        $T2*    $4 = plocal $T2, 0
        $T2**   $5 = plocal $T2*, 0
        void**  $6 = local void*
        store   void* $0, void** $6
        arg     $T2* $4
        call    $T7 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     void
}

extern function $T7* dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2

// std::operator+(const char*, const std::basic_string<char>&)

function $T8* op_plus_5E72E32E84B1A92AC824CD5F0870E5FDDA418A8E !6
{
@0      byte*   $0 = param
        $T2*    $1 = param
        $T2*    $2 = param
        byte**  $3 = local byte*
        $T2**   $4 = local $T2*
        $T2**   $5 = local $T2*
        $T2*    $6 = local $T2
        $T2**   $7 = local $T2*
        store   byte* $0, byte** $3
        store   $T2* $1, $T2** $4
        store   $T2* $2, $T2** $5
        byte*   $8 = load byte** $3
        arg     $T2* $6
        arg     byte* $8
        call    $T9 @ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        void*   $9 = getrbp
        arg     $T4 @fn_invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_F43C493D0B43CB2040D56EBAB7844295B56EF727
        arg     $T4 @fn_cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844_C03E7148CE3BAA3DB10510782DCF03D351331848
        arg     void* $9
        call    $T11 @ort_invoke
        $T2*    $10 = load $T2** $7
        $T2*    $11 = load $T2** $5
        arg     $T2* $6
        $T2*    $12 = call $T3 @fn_move_0327402166CAFF8AE1BE1FFDAAC2CF4FCCD50FE6
        arg     $T2* $11
        arg     $T2* $12
        call    $T12 @move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2
        jmp     @1

@1      arg     $T2* $6
        call    $T7 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        ret     void
}

extern function $T9* ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF

extern function $T11* ort_invoke

extern function $T12* move_ctor_040807DE0E0AFF6EE7514668F669516ECC2463B2

// std::operator==(const std::basic_string<char>&, const std::basic_string<char>&)

function $T13* op_eq_412E617E1C20532FC09418C15B14860BE69CEFBF !7
{
@0      $T2*    $0 = param
        $T2*    $1 = param
        $T2**   $2 = local $T2*
        $T2**   $3 = local $T2*
        long*   $4 = local long
        long*   $5 = local long
        store   $T2* $0, $T2** $2
        store   $T2* $1, $T2** $3
        $T2*    $6 = load $T2** $2
        arg     $T2* $6
        long    $7 = call $T14 @mfn_basic_string_length_6C8324D4F961C8E82865E765304795502F200142
        store   long $7, long* $4
        long    $8 = load long* $4
        $T2*    $9 = load $T2** $3
        arg     $T2* $9
        long    $10 = call $T14 @mfn_basic_string_length_6C8324D4F961C8E82865E765304795502F200142
        bool    $11 = equal long $8, long $10
        bool    $12 = not bool $11
        branch  bool $12, @1, @2

@1      ret     bool false

@2      long    $13 = signextend int 0
        store   long $13, long* $5
        jmp     @4

@4      long    $14 = load long* $5
        long    $15 = load long* $4
        bool    $16 = less long $14, long $15
        branch  bool $16, @5, @7

@5      $T2*    $17 = load $T2** $2
        long    $18 = load long* $5
        arg     $T2* $17
        arg     long $18
        byte*   $19 = call $T15 @op_subscript_basic_string_6EFBC7FFD0854E40E648ED405083C6E719D74EA4
        byte    $20 = load byte* $19
        $T2*    $21 = load $T2** $3
        long    $22 = load long* $5
        arg     $T2* $21
        arg     long $22
        byte*   $23 = call $T15 @op_subscript_basic_string_6EFBC7FFD0854E40E648ED405083C6E719D74EA4
        byte    $24 = load byte* $23
        bool    $25 = equal byte $20, byte $24
        bool    $26 = not bool $25
        branch  bool $26, @8, @9

@6      long    $27 = load long* $5
        long    $28 = signextend int 1
        long    $29 = add long $27, long $28
        store   long $29, long* $5
        jmp     @4

@7      ret     bool true

@8      ret     bool false

@9      jmp     @6
}

extern function $T14* mfn_basic_string_length_6C8324D4F961C8E82865E765304795502F200142

extern function $T15* op_subscript_basic_string_6EFBC7FFD0854E40E648ED405083C6E719D74EA4

// ::foo(const std::string&, const std::string&)

function $T16* fn_foo_68565C58C2BE8F1AEACBA092C9167B7CB3B886B9 !8
{
@0      $T2*    $0 = param
        $T2*    $1 = param
        $T2**   $2 = local $T2*
        $T2**   $3 = local $T2*
        int*    $4 = local int
        int*    $5 = local int
        int*    $6 = local int
        bool*   $7 = local bool
        $T2*    $8 = local $T2
        bool*   $9 = local bool
        store   $T2* $0, $T2** $2
        store   $T2* $1, $T2** $3
        store   int 0, int* $4
        store   int 0, int* $5
        store   int 1, int* $6
        int     $10 = load int* $6
        bool    $11 = equal int $10, int 1
        branch  bool $11, @4, @2

@1      ret     int 1

@2      ret     int 0

@3      $T2*    $12 = load $T2** $2
        $T2*    $13 = load $T2** $3
        arg     byte* string_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
        arg     $T2* $13
        arg     $T2* $8
        call    $T8 @op_plus_5E72E32E84B1A92AC824CD5F0870E5FDDA418A8E
        arg     $T2* $12
        arg     $T2* $8
        bool    $14 = call $T13 @op_eq_412E617E1C20532FC09418C15B14860BE69CEFBF
        arg     $T2* $8
        call    $T7 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        branch  bool $14, @1, @2

@4      int     $15 = load int* $4
        int     $16 = load int* $5
        arg     int $15
        arg     int $16
        bool    $17 = call $T0 @fn_TypesEqual_0A6755C2E3D1E8E832B053E7596792EA01CDF275
        branch  bool $17, @3, @2
}

// ::main()

function $T17* fn_main_E38ADCEC68EC816A0C571F2AB26E3B2606FAD76D !9
{
@0      int*    $0 = local int
        $T2*    $1 = local $T2
        $T2*    $2 = local $T2
        arg     $T2* $1
        arg     byte* string_1_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
        call    $T9 @ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        arg     $T2* $2
        arg     byte* string_2_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844
        call    $T9 @ctor_basic_string_4FDCD111049E713777B900C3998248EFF2F572EF
        arg     $T2* $1
        arg     $T2* $2
        int     $3 = call $T16 @fn_foo_68565C58C2BE8F1AEACBA092C9167B7CB3B886B9
        arg     $T2* $1
        call    $T7 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        arg     $T2* $2
        call    $T7 @dtor_409F27B2D43347A8314F1FB387BFE59E59F7E0D2
        store   int $3, int* $0
        ret     int 0
}

metadata
{
        !0 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/if_temporary/main.cpp"}
        !1 = {fullName: "::TypesEqual(int, int)", nodeType: 1}
        !2 = {fullName: "std::basic_string<char>"}
        !3 = {fullName: "std::move(std::basic_string<char>&&)", nodeType: 1}
        !4 = {fullName: "::invoke_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844(void*)", nodeType: 1, parentName: "std::operator+(const char*, const std::basic_string<char>&)"}
        !5 = {fullName: "::cleanup_0_compile_unit_945CCC8B575E3EC050EB8C5C9891BDFB16F99844(void*)", nodeType: 1, parentName: "std::operator+(const char*, const std::basic_string<char>&)"}
        !6 = {fullName: "std::operator+(const char*, const std::basic_string<char>&)", nodeType: 1}
        !7 = {fullName: "std::operator==(const std::basic_string<char>&, const std::basic_string<char>&)", nodeType: 1}
        !8 = {fullName: "::foo(const std::string&, const std::string&)", nodeType: 1}
        !9 = {fullName: "::main()", nodeType: 1}
}
