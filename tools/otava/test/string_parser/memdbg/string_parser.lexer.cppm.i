types
{
        $T0 = type [4 x void*]
        $T3 = type { void*, long } !1 // soul::lexer::Variables
        $T4 = type { $T3 } !2 // string_parser::lexer::string_lexer_Variables
        $T5 = type function void($T4*)
        $T9 = type { void*, long, $T9*, $T9*, $T9*, int } !3 // std::rb_node_base
        $T12 = type { byte*, byte* } !7 // soul::lexer::Lexeme<char8_t>
        $T13 = type { $T12, long } !8 // std::pair<const soul::lexer::Lexeme<char8_t>, long long int>
        $T14 = type { $T9, $T13 } !9 // std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>
        $T15 = type function void($T14*)
        $T28 = type { ushort*, ushort* } !10 // soul::lexer::Lexeme<char16_t>
        $T29 = type { $T28, long } !11 // std::pair<const soul::lexer::Lexeme<char16_t>, long long int>
        $T30 = type { $T9, $T29 } !12 // std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>
        $T31 = type function void($T30*)
        $T36 = type { uint*, uint* } !13 // soul::lexer::Lexeme<char32_t>
        $T37 = type { $T36, long } !14 // std::pair<const soul::lexer::Lexeme<char32_t>, long long int>
        $T38 = type { $T9, $T37 } !15 // std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>
        $T39 = type function void($T38*)
        $T40 = type function void($T3*)
        $T41 = type function void($T9*)
        $T43 = type { $T14* } !33 // std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>
        $T44 = type function void($T43*)
        $T47 = type function void(void*)
        $T48 = type function bool($T43*)
        $T49 = type function $T14*($T43*)
        $T52 = type { byte } !68 // soul::lexer::LexemeCompare<char32_t>
        $T55 = type { $T43, long, $T52, $T52 } !39 // std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>
        $T56 = type function $T14*($T55*)
        $T57 = type function $T9*($T9*)
        $T58 = type function void($T55*, $T14*)
        $T59 = type function void($T9*, $T9*)
        $T65 = type function void($T55*)
        $T92 = type { $T30* } !48 // std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>
        $T93 = type function void($T92*)
        $T96 = type function bool($T92*)
        $T97 = type function $T30*($T92*)
        $T103 = type { $T92, long, $T52, $T52 } !54 // std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>
        $T104 = type function $T30*($T103*)
        $T105 = type function void($T103*, $T30*)
        $T109 = type function void($T103*)
        $T114 = type { $T38* } !63 // std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>
        $T115 = type function void($T114*)
        $T118 = type function bool($T114*)
        $T119 = type function $T38*($T114*)
        $T125 = type { $T114, long, $T52, $T52 } !69 // std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>
        $T126 = type function $T38*($T125*)
        $T127 = type function void($T125*, $T38*)
        $T131 = type function void($T125*)
        $T137 = type { void* } !77 // std::mutex
        $T138 = type { $T137* } !78 // std::lock_guard<std::mutex>
        $T139 = type function void($T138*)
        $T140 = type function void($T137*)
}

data
{
        $T0 vtab_class_string_lexer_Variables_1B4D3078068174095E5FD7DF00CA56780DD58D56 = [ void* conv(ulong 9498701024064912482), void* conv(ulong 17618984378669473267), void* conv($T5 @dtor_string_lexer_Variables_FD7DF7BDE46CDC02C53D751A3D36570116233A4D), void* conv(long 0) ]
        $T0 vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_A653C07AE8DB0C024170FE6B8C425A253D2DD2B3 = [ void* conv(ulong 1016823463432123720), void* conv(ulong 1762217049037039213), void* conv($T15 @dtor_rb_node_222FF99EDE2B5988988BBF94A1D4D7DAD9A80D74), void* conv(long 0) ]
        $T0 vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_C88D9D950A7788920AABBA52843341D3FB51E61B = [ void* conv(ulong 12162539585982467714), void* conv(ulong 17912111165963626442), void* conv($T15 @dtor_rb_node_64A77A560098E1550C433F0237F81C4DB7D7D504), void* conv(long 0) ]
        $T0 vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_B749CA01BA26D6B7F9D8FBCB06F6898BCB4F8A4E = [ void* conv(ulong 6692883211110291269), void* conv(ulong 6911140328006258559), void* conv($T31 @dtor_rb_node_98008DB2C7CC6645150AA70BD08DD55112EC8C9A), void* conv(long 0) ]
        $T0 vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_9060ACBE41CD2B617E0A0C6277587318D9B025DB = [ void* conv(ulong 12596826753034481012), void* conv(ulong 1643487711971426304), void* conv($T39 @dtor_rb_node_762E6B7D10D1BA47140A9B95179F56F1D8137C47), void* conv(long 0) ]
}

// string_parser::lexer::string_lexer_Variables::@destructor() override

function $T5* dtor_string_lexer_Variables_FD7DF7BDE46CDC02C53D751A3D36570116233A4D !16
{
@0      $T4*    $0 = param
        $T4**   $1 = local $T4*
        store   $T4* $0, $T4** $1
        $T4*    $2 = load $T4** $1
        $T3*    $3 = bitcast $T4* $2
        void**  $4 = elemaddr $T3* $3, long 0
        void*   $5 = bitcast $T0* vtab_class_string_lexer_Variables_1B4D3078068174095E5FD7DF00CA56780DD58D56
        store   void* $5, void** $4
        long*   $6 = elemaddr $T3* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T4*    $8 = load $T4** $1
        $T3*    $9 = bitcast $T4* $8
        arg     $T3* $9
        call    $T40 @dtor_F71D4EE14A6516A134FD84CAA1CC079C49086D30
        $T4*    $10 = load $T4** $1
        $T3*    $11 = bitcast $T4* $10
        void**  $12 = elemaddr $T3* $11, long 0
        void*   $13 = bitcast $T0* vtab_class_string_lexer_Variables_1B4D3078068174095E5FD7DF00CA56780DD58D56
        store   void* $13, void** $12
        long*   $14 = elemaddr $T3* $11, long 1
        long*   $15 = bitcast long* $14
        store   long 0, long* $15
        ret     void
}

// std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>::@destructor() override

function $T15* dtor_rb_node_222FF99EDE2B5988988BBF94A1D4D7DAD9A80D74 !17
{
@0      $T14*   $0 = param
        $T14**  $1 = local $T14*
        store   $T14* $0, $T14** $1
        $T14*   $2 = load $T14** $1
        $T9*    $3 = bitcast $T14* $2
        void**  $4 = elemaddr $T9* $3, long 0
        void*   $5 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_A653C07AE8DB0C024170FE6B8C425A253D2DD2B3
        store   void* $5, void** $4
        long*   $6 = elemaddr $T9* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T14*   $8 = load $T14** $1
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $9
        call    $T41 @dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        $T14*   $10 = load $T14** $1
        $T9*    $11 = bitcast $T14* $10
        void**  $12 = elemaddr $T9* $11, long 0
        void*   $13 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_A653C07AE8DB0C024170FE6B8C425A253D2DD2B3
        store   void* $13, void** $12
        long*   $14 = elemaddr $T9* $11, long 1
        long*   $15 = bitcast long* $14
        store   long 0, long* $15
        ret     void
}

// std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>::@destructor() override

function $T15* dtor_rb_node_64A77A560098E1550C433F0237F81C4DB7D7D504 !32
{
@0      $T14*   $0 = param
        $T14**  $1 = local $T14*
        store   $T14* $0, $T14** $1
        $T14*   $2 = load $T14** $1
        $T9*    $3 = bitcast $T14* $2
        void**  $4 = elemaddr $T9* $3, long 0
        void*   $5 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_C88D9D950A7788920AABBA52843341D3FB51E61B
        store   void* $5, void** $4
        long*   $6 = elemaddr $T9* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T14*   $8 = load $T14** $1
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $9
        call    $T41 @dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        $T14*   $10 = load $T14** $1
        $T9*    $11 = bitcast $T14* $10
        void**  $12 = elemaddr $T9* $11, long 0
        void*   $13 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_C88D9D950A7788920AABBA52843341D3FB51E61B
        store   void* $13, void** $12
        long*   $14 = elemaddr $T9* $11, long 1
        long*   $15 = bitcast long* $14
        store   long 0, long* $15
        ret     void
}

// std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>::@destructor() override

function $T31* dtor_rb_node_98008DB2C7CC6645150AA70BD08DD55112EC8C9A !47
{
@0      $T30*   $0 = param
        $T30**  $1 = local $T30*
        store   $T30* $0, $T30** $1
        $T30*   $2 = load $T30** $1
        $T9*    $3 = bitcast $T30* $2
        void**  $4 = elemaddr $T9* $3, long 0
        void*   $5 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_B749CA01BA26D6B7F9D8FBCB06F6898BCB4F8A4E
        store   void* $5, void** $4
        long*   $6 = elemaddr $T9* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T30*   $8 = load $T30** $1
        $T9*    $9 = bitcast $T30* $8
        arg     $T9* $9
        call    $T41 @dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        $T30*   $10 = load $T30** $1
        $T9*    $11 = bitcast $T30* $10
        void**  $12 = elemaddr $T9* $11, long 0
        void*   $13 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_B749CA01BA26D6B7F9D8FBCB06F6898BCB4F8A4E
        store   void* $13, void** $12
        long*   $14 = elemaddr $T9* $11, long 1
        long*   $15 = bitcast long* $14
        store   long 0, long* $15
        ret     void
}

// std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>::@destructor() override

function $T39* dtor_rb_node_762E6B7D10D1BA47140A9B95179F56F1D8137C47 !62
{
@0      $T38*   $0 = param
        $T38**  $1 = local $T38*
        store   $T38* $0, $T38** $1
        $T38*   $2 = load $T38** $1
        $T9*    $3 = bitcast $T38* $2
        void**  $4 = elemaddr $T9* $3, long 0
        void*   $5 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_9060ACBE41CD2B617E0A0C6277587318D9B025DB
        store   void* $5, void** $4
        long*   $6 = elemaddr $T9* $3, long 1
        long*   $7 = bitcast long* $6
        store   long 0, long* $7
        $T38*   $8 = load $T38** $1
        $T9*    $9 = bitcast $T38* $8
        arg     $T9* $9
        call    $T41 @dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE
        $T38*   $10 = load $T38** $1
        $T9*    $11 = bitcast $T38* $10
        void**  $12 = elemaddr $T9* $11, long 0
        void*   $13 = bitcast $T0* vtab_class_rb_node_1A230528F6B961082F6B1F0CD4CFC22EA4AF3BA4_9060ACBE41CD2B617E0A0C6277587318D9B025DB
        store   void* $13, void** $12
        long*   $14 = elemaddr $T9* $11, long 1
        long*   $15 = bitcast long* $14
        store   long 0, long* $15
        ret     void
}

extern function $T40* dtor_F71D4EE14A6516A134FD84CAA1CC079C49086D30

extern function $T41* dtor_1860085DFFC51E877DCD21B82AEDC6B6DCBE29FE

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::~unique_ptr()

function $T44* dtor_3F8862B23805CE9B1D0EDA53C2871F2B36F9DCCB !19
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        bool    $5 = equal $T14* $4, $T14* null
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      $T43*   $7 = load $T43** $1
        $T14**  $8 = elemaddr $T43* $7, long 0
        $T14*   $9 = load $T14** $8
        $T9*    $10 = bitcast $T14* $9
        void**  $11 = elemaddr $T9* $10, long 0
        void*   $12 = load void** $11
        $T0*    $13 = bitcast void* $12
        long*   $14 = elemaddr $T9* $10, long 1
        long*   $15 = bitcast long* $14
        long    $16 = load long* $15
        byte*   $17 = bitcast $T9* $10
        byte*   $18 = ptroffset byte* $17, long $16
        $T9*    $19 = bitcast byte* $18
        void**  $20 = elemaddr $T0* $13, long 2
        void*   $21 = load void** $20
        $T15*   $22 = bitcast void* $21
        void**  $23 = elemaddr $T0* $13, long 3
        long*   $24 = bitcast void** $23
        long    $25 = load long* $24
        byte*   $26 = bitcast $T9* $19
        byte*   $27 = ptroffset byte* $26, long $25
        $T9*    $28 = bitcast byte* $27
        arg     $T9* $28
        call    $T15* $22
        $T43*   $29 = load $T43** $1
        $T14**  $30 = elemaddr $T43* $29, long 0
        $T14*   $31 = load $T14** $30
        $T9*    $32 = bitcast $T14* $31
        void**  $33 = elemaddr $T9* $32, long 0
        void*   $34 = load void** $33
        $T0*    $35 = bitcast void* $34
        long*   $36 = elemaddr $T9* $32, long 1
        long*   $37 = bitcast long* $36
        long    $38 = load long* $37
        byte*   $39 = bitcast $T9* $32
        byte*   $40 = ptroffset byte* $39, long $38
        $T9*    $41 = bitcast byte* $40
        arg     $T9* $41
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      ret     void
}

extern function $T47* op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::operator_bool() const

function $T48* mfn_unique_ptr_operator_bool_C054C1D60CC011AAE53830E70593E13180AE3323 !20
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        $T14*   $5 = bitcast void* null
        bool    $6 = equal $T14* $4, $T14* $5
        bool    $7 = not bool $6
        ret     bool $7
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::operator->() const

function $T49* op_arrow_unique_ptr_1065D70F5197B43CB465D07EE540A1F374264A11 !21
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        ret     $T14* $4
}

// std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::root()

function $T56* mfn_rb_tree_root_B98918B789C78D0CA0E28AC7936AEDEADF091327 !25
{
@0      $T55*   $0 = param
        $T55**  $1 = local $T55*
        store   $T55* $0, $T55** $1
        $T55*   $2 = load $T55** $1
        $T43*   $3 = elemaddr $T55* $2, long 0
        arg     $T43* $3
        $T14*   $4 = call $T49 @op_arrow_unique_ptr_1065D70F5197B43CB465D07EE540A1F374264A11
        $T9*    $5 = bitcast $T14* $4
        arg     $T9* $5
        $T9*    $6 = call $T57 @mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        $T14*   $7 = bitcast $T9* $6
        ret     $T14* $7
}

extern function $T57* mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5

// std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>*)

function $T58* mfn_rb_tree_set_root_742954C1BAD474956F41C2C672439CC31C598ED6 !26
{
@0      $T55*   $0 = param
        $T14*   $1 = param
        $T55**  $2 = local $T55*
        $T14**  $3 = local $T14*
        store   $T55* $0, $T55** $2
        store   $T14* $1, $T14** $3
        $T55*   $4 = load $T55** $2
        $T43*   $5 = elemaddr $T55* $4, long 0
        arg     $T43* $5
        $T14*   $6 = call $T49 @op_arrow_unique_ptr_1065D70F5197B43CB465D07EE540A1F374264A11
        $T9*    $7 = bitcast $T14* $6
        $T14*   $8 = load $T14** $3
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
        ret     void
}

extern function $T59* mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::get() const

function $T49* mfn_unique_ptr_get_65C0768D101350553800F65A662359E362E9FE16 !27
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        ret     $T14* $4
}

// std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>*)

function $T58* mfn_rb_tree_set_leftmost_392E8E6D5A58424EDC6905784F4B6426A8C01818 !28
{
@0      $T55*   $0 = param
        $T14*   $1 = param
        $T55**  $2 = local $T55*
        $T14**  $3 = local $T14*
        store   $T55* $0, $T55** $2
        store   $T14* $1, $T14** $3
        $T55*   $4 = load $T55** $2
        $T43*   $5 = elemaddr $T55* $4, long 0
        arg     $T43* $5
        $T14*   $6 = call $T49 @op_arrow_unique_ptr_1065D70F5197B43CB465D07EE540A1F374264A11
        $T9*    $7 = bitcast $T14* $6
        $T14*   $8 = load $T14** $3
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        ret     void
}

extern function $T59* mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F

// std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>*)

function $T58* mfn_rb_tree_set_rightmost_E278B97BCC3B6A369B9A8C4ED5206388E53AD23A !29
{
@0      $T55*   $0 = param
        $T14*   $1 = param
        $T55**  $2 = local $T55*
        $T14**  $3 = local $T14*
        store   $T55* $0, $T55** $2
        store   $T14* $1, $T14** $3
        $T55*   $4 = load $T55** $2
        $T43*   $5 = elemaddr $T55* $4, long 0
        arg     $T43* $5
        $T14*   $6 = call $T49 @op_arrow_unique_ptr_1065D70F5197B43CB465D07EE540A1F374264A11
        $T9*    $7 = bitcast $T14* $6
        $T14*   $8 = load $T14** $3
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        ret     void
}

extern function $T59* mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7

// std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::clear()

function $T65* mfn_rb_tree_clear_86D500900D6AC584F0E5FDEF9437E02D885F9896 !30
{
@0      $T55*   $0 = param
        $T55**  $1 = local $T55*
        $T14**  $2 = local $T14*
        store   $T55* $0, $T55** $1
        $T55*   $3 = load $T55** $1
        $T43*   $4 = elemaddr $T55* $3, long 0
        arg     $T43* $4
        bool    $5 = call $T48 @mfn_unique_ptr_operator_bool_C054C1D60CC011AAE53830E70593E13180AE3323
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      ret     void

@2      $T55*   $7 = load $T55** $1
        arg     $T55* $7
        $T14*   $8 = call $T56 @mfn_rb_tree_root_B98918B789C78D0CA0E28AC7936AEDEADF091327
        store   $T14* $8, $T14** $2
        $T14*   $9 = load $T14** $2
        bool    $10 = equal $T14* $9, $T14* null
        bool    $11 = not bool $10
        branch  bool $11, @4, @5

@4      $T14*   $12 = load $T14** $2
        $T9*    $13 = bitcast $T14* $12
        void**  $14 = elemaddr $T9* $13, long 0
        void*   $15 = load void** $14
        $T0*    $16 = bitcast void* $15
        long*   $17 = elemaddr $T9* $13, long 1
        long*   $18 = bitcast long* $17
        long    $19 = load long* $18
        byte*   $20 = bitcast $T9* $13
        byte*   $21 = ptroffset byte* $20, long $19
        $T9*    $22 = bitcast byte* $21
        void**  $23 = elemaddr $T0* $16, long 2
        void*   $24 = load void** $23
        $T15*   $25 = bitcast void* $24
        void**  $26 = elemaddr $T0* $16, long 3
        long*   $27 = bitcast void** $26
        long    $28 = load long* $27
        byte*   $29 = bitcast $T9* $22
        byte*   $30 = ptroffset byte* $29, long $28
        $T9*    $31 = bitcast byte* $30
        arg     $T9* $31
        call    $T15* $25
        $T14*   $32 = load $T14** $2
        $T9*    $33 = bitcast $T14* $32
        void**  $34 = elemaddr $T9* $33, long 0
        void*   $35 = load void** $34
        $T0*    $36 = bitcast void* $35
        long*   $37 = elemaddr $T9* $33, long 1
        long*   $38 = bitcast long* $37
        long    $39 = load long* $38
        byte*   $40 = bitcast $T9* $33
        byte*   $41 = ptroffset byte* $40, long $39
        $T9*    $42 = bitcast byte* $41
        arg     $T9* $42
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        $T55*   $43 = load $T55** $1
        $T14*   $44 = bitcast void* null
        arg     $T55* $43
        arg     $T14* $44
        call    $T58 @mfn_rb_tree_set_root_742954C1BAD474956F41C2C672439CC31C598ED6
        jmp     @5

@5      $T55*   $45 = load $T55** $1
        $T55*   $46 = load $T55** $1
        $T43*   $47 = elemaddr $T55* $46, long 0
        arg     $T43* $47
        $T14*   $48 = call $T49 @mfn_unique_ptr_get_65C0768D101350553800F65A662359E362E9FE16
        arg     $T55* $45
        arg     $T14* $48
        call    $T58 @mfn_rb_tree_set_leftmost_392E8E6D5A58424EDC6905784F4B6426A8C01818
        $T55*   $49 = load $T55** $1
        $T55*   $50 = load $T55** $1
        $T43*   $51 = elemaddr $T55* $50, long 0
        arg     $T43* $51
        $T14*   $52 = call $T49 @mfn_unique_ptr_get_65C0768D101350553800F65A662359E362E9FE16
        arg     $T55* $49
        arg     $T14* $52
        call    $T58 @mfn_rb_tree_set_rightmost_E278B97BCC3B6A369B9A8C4ED5206388E53AD23A
        long    $53 = signextend int 0
        $T55*   $54 = load $T55** $1
        long*   $55 = elemaddr $T55* $54, long 1
        store   long $53, long* $55
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::~rb_tree()

function $T65* dtor_F0FEF5EF8D25C67995B4B02ED2E72FAAAAF5A4C9 !31
{
@0      $T55*   $0 = param
        $T55**  $1 = local $T55*
        store   $T55* $0, $T55** $1
        $T55*   $2 = load $T55** $1
        arg     $T55* $2
        call    $T65 @mfn_rb_tree_clear_86D500900D6AC584F0E5FDEF9437E02D885F9896
        $T55*   $3 = load $T55** $1
        $T43*   $4 = elemaddr $T55* $3, long 0
        arg     $T43* $4
        call    $T44 @dtor_3F8862B23805CE9B1D0EDA53C2871F2B36F9DCCB
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::~unique_ptr()

function $T44* dtor_5644F90192BEF6C5B741C9F75CC41263AA0A0EF9 !34
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        bool    $5 = equal $T14* $4, $T14* null
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      $T43*   $7 = load $T43** $1
        $T14**  $8 = elemaddr $T43* $7, long 0
        $T14*   $9 = load $T14** $8
        $T9*    $10 = bitcast $T14* $9
        void**  $11 = elemaddr $T9* $10, long 0
        void*   $12 = load void** $11
        $T0*    $13 = bitcast void* $12
        long*   $14 = elemaddr $T9* $10, long 1
        long*   $15 = bitcast long* $14
        long    $16 = load long* $15
        byte*   $17 = bitcast $T9* $10
        byte*   $18 = ptroffset byte* $17, long $16
        $T9*    $19 = bitcast byte* $18
        void**  $20 = elemaddr $T0* $13, long 2
        void*   $21 = load void** $20
        $T15*   $22 = bitcast void* $21
        void**  $23 = elemaddr $T0* $13, long 3
        long*   $24 = bitcast void** $23
        long    $25 = load long* $24
        byte*   $26 = bitcast $T9* $19
        byte*   $27 = ptroffset byte* $26, long $25
        $T9*    $28 = bitcast byte* $27
        arg     $T9* $28
        call    $T15* $22
        $T43*   $29 = load $T43** $1
        $T14**  $30 = elemaddr $T43* $29, long 0
        $T14*   $31 = load $T14** $30
        $T9*    $32 = bitcast $T14* $31
        void**  $33 = elemaddr $T9* $32, long 0
        void*   $34 = load void** $33
        $T0*    $35 = bitcast void* $34
        long*   $36 = elemaddr $T9* $32, long 1
        long*   $37 = bitcast long* $36
        long    $38 = load long* $37
        byte*   $39 = bitcast $T9* $32
        byte*   $40 = ptroffset byte* $39, long $38
        $T9*    $41 = bitcast byte* $40
        arg     $T9* $41
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::operator_bool() const

function $T48* mfn_unique_ptr_operator_bool_B1CF3130E6EB7995CBA9FCB7C78B0F4FE1CA213A !35
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        $T14*   $5 = bitcast void* null
        bool    $6 = equal $T14* $4, $T14* $5
        bool    $7 = not bool $6
        ret     bool $7
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::operator->() const

function $T49* op_arrow_unique_ptr_0CE66D931BC441B2B2DBB6580FE7F7989157C039 !36
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        ret     $T14* $4
}

// std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::root()

function $T56* mfn_rb_tree_root_790C53A895A35F714C60E23CA0D33A0C73A349C7 !40
{
@0      $T55*   $0 = param
        $T55**  $1 = local $T55*
        store   $T55* $0, $T55** $1
        $T55*   $2 = load $T55** $1
        $T43*   $3 = elemaddr $T55* $2, long 0
        arg     $T43* $3
        $T14*   $4 = call $T49 @op_arrow_unique_ptr_0CE66D931BC441B2B2DBB6580FE7F7989157C039
        $T9*    $5 = bitcast $T14* $4
        arg     $T9* $5
        $T9*    $6 = call $T57 @mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        $T14*   $7 = bitcast $T9* $6
        ret     $T14* $7
}

// std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>*)

function $T58* mfn_rb_tree_set_root_813818AC0E4C7136C7D316D433C1BBDE723DF974 !41
{
@0      $T55*   $0 = param
        $T14*   $1 = param
        $T55**  $2 = local $T55*
        $T14**  $3 = local $T14*
        store   $T55* $0, $T55** $2
        store   $T14* $1, $T14** $3
        $T55*   $4 = load $T55** $2
        $T43*   $5 = elemaddr $T55* $4, long 0
        arg     $T43* $5
        $T14*   $6 = call $T49 @op_arrow_unique_ptr_0CE66D931BC441B2B2DBB6580FE7F7989157C039
        $T9*    $7 = bitcast $T14* $6
        $T14*   $8 = load $T14** $3
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::get() const

function $T49* mfn_unique_ptr_get_E9EF99EABC17D2551C52360EC42D235932A19CE3 !42
{
@0      $T43*   $0 = param
        $T43**  $1 = local $T43*
        store   $T43* $0, $T43** $1
        $T43*   $2 = load $T43** $1
        $T14**  $3 = elemaddr $T43* $2, long 0
        $T14*   $4 = load $T14** $3
        ret     $T14* $4
}

// std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>*)

function $T58* mfn_rb_tree_set_leftmost_85DCA9B9D9971804A9DE569D7E6F001D1AA506A5 !43
{
@0      $T55*   $0 = param
        $T14*   $1 = param
        $T55**  $2 = local $T55*
        $T14**  $3 = local $T14*
        store   $T55* $0, $T55** $2
        store   $T14* $1, $T14** $3
        $T55*   $4 = load $T55** $2
        $T43*   $5 = elemaddr $T55* $4, long 0
        arg     $T43* $5
        $T14*   $6 = call $T49 @op_arrow_unique_ptr_0CE66D931BC441B2B2DBB6580FE7F7989157C039
        $T9*    $7 = bitcast $T14* $6
        $T14*   $8 = load $T14** $3
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>*)

function $T58* mfn_rb_tree_set_rightmost_96ED8F8745E7DCA35BD00AF010B6639771927CE3 !44
{
@0      $T55*   $0 = param
        $T14*   $1 = param
        $T55**  $2 = local $T55*
        $T14**  $3 = local $T14*
        store   $T55* $0, $T55** $2
        store   $T14* $1, $T14** $3
        $T55*   $4 = load $T55** $2
        $T43*   $5 = elemaddr $T55* $4, long 0
        arg     $T43* $5
        $T14*   $6 = call $T49 @op_arrow_unique_ptr_0CE66D931BC441B2B2DBB6580FE7F7989157C039
        $T9*    $7 = bitcast $T14* $6
        $T14*   $8 = load $T14** $3
        $T9*    $9 = bitcast $T14* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::clear()

function $T65* mfn_rb_tree_clear_68571BD8E879805E0DF53F3F2518712038CCC1F3 !45
{
@0      $T55*   $0 = param
        $T55**  $1 = local $T55*
        $T14**  $2 = local $T14*
        store   $T55* $0, $T55** $1
        $T55*   $3 = load $T55** $1
        $T43*   $4 = elemaddr $T55* $3, long 0
        arg     $T43* $4
        bool    $5 = call $T48 @mfn_unique_ptr_operator_bool_B1CF3130E6EB7995CBA9FCB7C78B0F4FE1CA213A
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      ret     void

@2      $T55*   $7 = load $T55** $1
        arg     $T55* $7
        $T14*   $8 = call $T56 @mfn_rb_tree_root_790C53A895A35F714C60E23CA0D33A0C73A349C7
        store   $T14* $8, $T14** $2
        $T14*   $9 = load $T14** $2
        bool    $10 = equal $T14* $9, $T14* null
        bool    $11 = not bool $10
        branch  bool $11, @4, @5

@4      $T14*   $12 = load $T14** $2
        $T9*    $13 = bitcast $T14* $12
        void**  $14 = elemaddr $T9* $13, long 0
        void*   $15 = load void** $14
        $T0*    $16 = bitcast void* $15
        long*   $17 = elemaddr $T9* $13, long 1
        long*   $18 = bitcast long* $17
        long    $19 = load long* $18
        byte*   $20 = bitcast $T9* $13
        byte*   $21 = ptroffset byte* $20, long $19
        $T9*    $22 = bitcast byte* $21
        void**  $23 = elemaddr $T0* $16, long 2
        void*   $24 = load void** $23
        $T15*   $25 = bitcast void* $24
        void**  $26 = elemaddr $T0* $16, long 3
        long*   $27 = bitcast void** $26
        long    $28 = load long* $27
        byte*   $29 = bitcast $T9* $22
        byte*   $30 = ptroffset byte* $29, long $28
        $T9*    $31 = bitcast byte* $30
        arg     $T9* $31
        call    $T15* $25
        $T14*   $32 = load $T14** $2
        $T9*    $33 = bitcast $T14* $32
        void**  $34 = elemaddr $T9* $33, long 0
        void*   $35 = load void** $34
        $T0*    $36 = bitcast void* $35
        long*   $37 = elemaddr $T9* $33, long 1
        long*   $38 = bitcast long* $37
        long    $39 = load long* $38
        byte*   $40 = bitcast $T9* $33
        byte*   $41 = ptroffset byte* $40, long $39
        $T9*    $42 = bitcast byte* $41
        arg     $T9* $42
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        $T55*   $43 = load $T55** $1
        $T14*   $44 = bitcast void* null
        arg     $T55* $43
        arg     $T14* $44
        call    $T58 @mfn_rb_tree_set_root_813818AC0E4C7136C7D316D433C1BBDE723DF974
        jmp     @5

@5      $T55*   $45 = load $T55** $1
        $T55*   $46 = load $T55** $1
        $T43*   $47 = elemaddr $T55* $46, long 0
        arg     $T43* $47
        $T14*   $48 = call $T49 @mfn_unique_ptr_get_E9EF99EABC17D2551C52360EC42D235932A19CE3
        arg     $T55* $45
        arg     $T14* $48
        call    $T58 @mfn_rb_tree_set_leftmost_85DCA9B9D9971804A9DE569D7E6F001D1AA506A5
        $T55*   $49 = load $T55** $1
        $T55*   $50 = load $T55** $1
        $T43*   $51 = elemaddr $T55* $50, long 0
        arg     $T43* $51
        $T14*   $52 = call $T49 @mfn_unique_ptr_get_E9EF99EABC17D2551C52360EC42D235932A19CE3
        arg     $T55* $49
        arg     $T14* $52
        call    $T58 @mfn_rb_tree_set_rightmost_96ED8F8745E7DCA35BD00AF010B6639771927CE3
        long    $53 = signextend int 0
        $T55*   $54 = load $T55** $1
        long*   $55 = elemaddr $T55* $54, long 1
        store   long $53, long* $55
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::~rb_tree()

function $T65* dtor_8FE329A5D253B1BD51F83DC8A8798A53A32EDE14 !46
{
@0      $T55*   $0 = param
        $T55**  $1 = local $T55*
        store   $T55* $0, $T55** $1
        $T55*   $2 = load $T55** $1
        arg     $T55* $2
        call    $T65 @mfn_rb_tree_clear_68571BD8E879805E0DF53F3F2518712038CCC1F3
        $T55*   $3 = load $T55** $1
        $T43*   $4 = elemaddr $T55* $3, long 0
        arg     $T43* $4
        call    $T44 @dtor_5644F90192BEF6C5B741C9F75CC41263AA0A0EF9
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::~unique_ptr()

function $T93* dtor_2CD82CDF4916D3295B27F1792B594126F325F564 !49
{
@0      $T92*   $0 = param
        $T92**  $1 = local $T92*
        store   $T92* $0, $T92** $1
        $T92*   $2 = load $T92** $1
        $T30**  $3 = elemaddr $T92* $2, long 0
        $T30*   $4 = load $T30** $3
        bool    $5 = equal $T30* $4, $T30* null
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      $T92*   $7 = load $T92** $1
        $T30**  $8 = elemaddr $T92* $7, long 0
        $T30*   $9 = load $T30** $8
        $T9*    $10 = bitcast $T30* $9
        void**  $11 = elemaddr $T9* $10, long 0
        void*   $12 = load void** $11
        $T0*    $13 = bitcast void* $12
        long*   $14 = elemaddr $T9* $10, long 1
        long*   $15 = bitcast long* $14
        long    $16 = load long* $15
        byte*   $17 = bitcast $T9* $10
        byte*   $18 = ptroffset byte* $17, long $16
        $T9*    $19 = bitcast byte* $18
        void**  $20 = elemaddr $T0* $13, long 2
        void*   $21 = load void** $20
        $T31*   $22 = bitcast void* $21
        void**  $23 = elemaddr $T0* $13, long 3
        long*   $24 = bitcast void** $23
        long    $25 = load long* $24
        byte*   $26 = bitcast $T9* $19
        byte*   $27 = ptroffset byte* $26, long $25
        $T9*    $28 = bitcast byte* $27
        arg     $T9* $28
        call    $T31* $22
        $T92*   $29 = load $T92** $1
        $T30**  $30 = elemaddr $T92* $29, long 0
        $T30*   $31 = load $T30** $30
        $T9*    $32 = bitcast $T30* $31
        void**  $33 = elemaddr $T9* $32, long 0
        void*   $34 = load void** $33
        $T0*    $35 = bitcast void* $34
        long*   $36 = elemaddr $T9* $32, long 1
        long*   $37 = bitcast long* $36
        long    $38 = load long* $37
        byte*   $39 = bitcast $T9* $32
        byte*   $40 = ptroffset byte* $39, long $38
        $T9*    $41 = bitcast byte* $40
        arg     $T9* $41
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::operator_bool() const

function $T96* mfn_unique_ptr_operator_bool_382ED7EED1CA706E5CA32FF323B2839101567060 !50
{
@0      $T92*   $0 = param
        $T92**  $1 = local $T92*
        store   $T92* $0, $T92** $1
        $T92*   $2 = load $T92** $1
        $T30**  $3 = elemaddr $T92* $2, long 0
        $T30*   $4 = load $T30** $3
        $T30*   $5 = bitcast void* null
        bool    $6 = equal $T30* $4, $T30* $5
        bool    $7 = not bool $6
        ret     bool $7
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::operator->() const

function $T97* op_arrow_unique_ptr_CCAB16721FBDB274452156180ADB1D1AE35C4E4E !51
{
@0      $T92*   $0 = param
        $T92**  $1 = local $T92*
        store   $T92* $0, $T92** $1
        $T92*   $2 = load $T92** $1
        $T30**  $3 = elemaddr $T92* $2, long 0
        $T30*   $4 = load $T30** $3
        ret     $T30* $4
}

// std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::root()

function $T104* mfn_rb_tree_root_EF12D171A25DA6D3FEC466BDBC872B3C506039E1 !55
{
@0      $T103*  $0 = param
        $T103** $1 = local $T103*
        store   $T103* $0, $T103** $1
        $T103*  $2 = load $T103** $1
        $T92*   $3 = elemaddr $T103* $2, long 0
        arg     $T92* $3
        $T30*   $4 = call $T97 @op_arrow_unique_ptr_CCAB16721FBDB274452156180ADB1D1AE35C4E4E
        $T9*    $5 = bitcast $T30* $4
        arg     $T9* $5
        $T9*    $6 = call $T57 @mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        $T30*   $7 = bitcast $T9* $6
        ret     $T30* $7
}

// std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>*)

function $T105* mfn_rb_tree_set_root_D273EF7EA4653954A30267FEE5E193292E41001D !56
{
@0      $T103*  $0 = param
        $T30*   $1 = param
        $T103** $2 = local $T103*
        $T30**  $3 = local $T30*
        store   $T103* $0, $T103** $2
        store   $T30* $1, $T30** $3
        $T103*  $4 = load $T103** $2
        $T92*   $5 = elemaddr $T103* $4, long 0
        arg     $T92* $5
        $T30*   $6 = call $T97 @op_arrow_unique_ptr_CCAB16721FBDB274452156180ADB1D1AE35C4E4E
        $T9*    $7 = bitcast $T30* $6
        $T30*   $8 = load $T30** $3
        $T9*    $9 = bitcast $T30* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::get() const

function $T97* mfn_unique_ptr_get_1EBECF15CB90C7F55E982D7F01E11E8EDBCE6AD6 !57
{
@0      $T92*   $0 = param
        $T92**  $1 = local $T92*
        store   $T92* $0, $T92** $1
        $T92*   $2 = load $T92** $1
        $T30**  $3 = elemaddr $T92* $2, long 0
        $T30*   $4 = load $T30** $3
        ret     $T30* $4
}

// std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>*)

function $T105* mfn_rb_tree_set_leftmost_B6A429AC90D6C2298406EBAFF7E825FE7DF0D038 !58
{
@0      $T103*  $0 = param
        $T30*   $1 = param
        $T103** $2 = local $T103*
        $T30**  $3 = local $T30*
        store   $T103* $0, $T103** $2
        store   $T30* $1, $T30** $3
        $T103*  $4 = load $T103** $2
        $T92*   $5 = elemaddr $T103* $4, long 0
        arg     $T92* $5
        $T30*   $6 = call $T97 @op_arrow_unique_ptr_CCAB16721FBDB274452156180ADB1D1AE35C4E4E
        $T9*    $7 = bitcast $T30* $6
        $T30*   $8 = load $T30** $3
        $T9*    $9 = bitcast $T30* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>*)

function $T105* mfn_rb_tree_set_rightmost_951F22FB6E380CDF3328807BD67C864BD0371570 !59
{
@0      $T103*  $0 = param
        $T30*   $1 = param
        $T103** $2 = local $T103*
        $T30**  $3 = local $T30*
        store   $T103* $0, $T103** $2
        store   $T30* $1, $T30** $3
        $T103*  $4 = load $T103** $2
        $T92*   $5 = elemaddr $T103* $4, long 0
        arg     $T92* $5
        $T30*   $6 = call $T97 @op_arrow_unique_ptr_CCAB16721FBDB274452156180ADB1D1AE35C4E4E
        $T9*    $7 = bitcast $T30* $6
        $T30*   $8 = load $T30** $3
        $T9*    $9 = bitcast $T30* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::clear()

function $T109* mfn_rb_tree_clear_505C084436AE564CA4140E5B8ABF1CB0AED16F91 !60
{
@0      $T103*  $0 = param
        $T103** $1 = local $T103*
        $T30**  $2 = local $T30*
        store   $T103* $0, $T103** $1
        $T103*  $3 = load $T103** $1
        $T92*   $4 = elemaddr $T103* $3, long 0
        arg     $T92* $4
        bool    $5 = call $T96 @mfn_unique_ptr_operator_bool_382ED7EED1CA706E5CA32FF323B2839101567060
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      ret     void

@2      $T103*  $7 = load $T103** $1
        arg     $T103* $7
        $T30*   $8 = call $T104 @mfn_rb_tree_root_EF12D171A25DA6D3FEC466BDBC872B3C506039E1
        store   $T30* $8, $T30** $2
        $T30*   $9 = load $T30** $2
        bool    $10 = equal $T30* $9, $T30* null
        bool    $11 = not bool $10
        branch  bool $11, @4, @5

@4      $T30*   $12 = load $T30** $2
        $T9*    $13 = bitcast $T30* $12
        void**  $14 = elemaddr $T9* $13, long 0
        void*   $15 = load void** $14
        $T0*    $16 = bitcast void* $15
        long*   $17 = elemaddr $T9* $13, long 1
        long*   $18 = bitcast long* $17
        long    $19 = load long* $18
        byte*   $20 = bitcast $T9* $13
        byte*   $21 = ptroffset byte* $20, long $19
        $T9*    $22 = bitcast byte* $21
        void**  $23 = elemaddr $T0* $16, long 2
        void*   $24 = load void** $23
        $T31*   $25 = bitcast void* $24
        void**  $26 = elemaddr $T0* $16, long 3
        long*   $27 = bitcast void** $26
        long    $28 = load long* $27
        byte*   $29 = bitcast $T9* $22
        byte*   $30 = ptroffset byte* $29, long $28
        $T9*    $31 = bitcast byte* $30
        arg     $T9* $31
        call    $T31* $25
        $T30*   $32 = load $T30** $2
        $T9*    $33 = bitcast $T30* $32
        void**  $34 = elemaddr $T9* $33, long 0
        void*   $35 = load void** $34
        $T0*    $36 = bitcast void* $35
        long*   $37 = elemaddr $T9* $33, long 1
        long*   $38 = bitcast long* $37
        long    $39 = load long* $38
        byte*   $40 = bitcast $T9* $33
        byte*   $41 = ptroffset byte* $40, long $39
        $T9*    $42 = bitcast byte* $41
        arg     $T9* $42
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        $T103*  $43 = load $T103** $1
        $T30*   $44 = bitcast void* null
        arg     $T103* $43
        arg     $T30* $44
        call    $T105 @mfn_rb_tree_set_root_D273EF7EA4653954A30267FEE5E193292E41001D
        jmp     @5

@5      $T103*  $45 = load $T103** $1
        $T103*  $46 = load $T103** $1
        $T92*   $47 = elemaddr $T103* $46, long 0
        arg     $T92* $47
        $T30*   $48 = call $T97 @mfn_unique_ptr_get_1EBECF15CB90C7F55E982D7F01E11E8EDBCE6AD6
        arg     $T103* $45
        arg     $T30* $48
        call    $T105 @mfn_rb_tree_set_leftmost_B6A429AC90D6C2298406EBAFF7E825FE7DF0D038
        $T103*  $49 = load $T103** $1
        $T103*  $50 = load $T103** $1
        $T92*   $51 = elemaddr $T103* $50, long 0
        arg     $T92* $51
        $T30*   $52 = call $T97 @mfn_unique_ptr_get_1EBECF15CB90C7F55E982D7F01E11E8EDBCE6AD6
        arg     $T103* $49
        arg     $T30* $52
        call    $T105 @mfn_rb_tree_set_rightmost_951F22FB6E380CDF3328807BD67C864BD0371570
        long    $53 = signextend int 0
        $T103*  $54 = load $T103** $1
        long*   $55 = elemaddr $T103* $54, long 1
        store   long $53, long* $55
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::~rb_tree()

function $T109* dtor_3CF5D35A03ED1D2308E0A1636A9095DAF31B1E5D !61
{
@0      $T103*  $0 = param
        $T103** $1 = local $T103*
        store   $T103* $0, $T103** $1
        $T103*  $2 = load $T103** $1
        arg     $T103* $2
        call    $T109 @mfn_rb_tree_clear_505C084436AE564CA4140E5B8ABF1CB0AED16F91
        $T103*  $3 = load $T103** $1
        $T92*   $4 = elemaddr $T103* $3, long 0
        arg     $T92* $4
        call    $T93 @dtor_2CD82CDF4916D3295B27F1792B594126F325F564
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::~unique_ptr()

function $T115* dtor_FDB80B49F4DE7F087BAE8AEE2B713CAEF38C434F !64
{
@0      $T114*  $0 = param
        $T114** $1 = local $T114*
        store   $T114* $0, $T114** $1
        $T114*  $2 = load $T114** $1
        $T38**  $3 = elemaddr $T114* $2, long 0
        $T38*   $4 = load $T38** $3
        bool    $5 = equal $T38* $4, $T38* null
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      $T114*  $7 = load $T114** $1
        $T38**  $8 = elemaddr $T114* $7, long 0
        $T38*   $9 = load $T38** $8
        $T9*    $10 = bitcast $T38* $9
        void**  $11 = elemaddr $T9* $10, long 0
        void*   $12 = load void** $11
        $T0*    $13 = bitcast void* $12
        long*   $14 = elemaddr $T9* $10, long 1
        long*   $15 = bitcast long* $14
        long    $16 = load long* $15
        byte*   $17 = bitcast $T9* $10
        byte*   $18 = ptroffset byte* $17, long $16
        $T9*    $19 = bitcast byte* $18
        void**  $20 = elemaddr $T0* $13, long 2
        void*   $21 = load void** $20
        $T39*   $22 = bitcast void* $21
        void**  $23 = elemaddr $T0* $13, long 3
        long*   $24 = bitcast void** $23
        long    $25 = load long* $24
        byte*   $26 = bitcast $T9* $19
        byte*   $27 = ptroffset byte* $26, long $25
        $T9*    $28 = bitcast byte* $27
        arg     $T9* $28
        call    $T39* $22
        $T114*  $29 = load $T114** $1
        $T38**  $30 = elemaddr $T114* $29, long 0
        $T38*   $31 = load $T38** $30
        $T9*    $32 = bitcast $T38* $31
        void**  $33 = elemaddr $T9* $32, long 0
        void*   $34 = load void** $33
        $T0*    $35 = bitcast void* $34
        long*   $36 = elemaddr $T9* $32, long 1
        long*   $37 = bitcast long* $36
        long    $38 = load long* $37
        byte*   $39 = bitcast $T9* $32
        byte*   $40 = ptroffset byte* $39, long $38
        $T9*    $41 = bitcast byte* $40
        arg     $T9* $41
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        jmp     @2

@2      ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::operator_bool() const

function $T118* mfn_unique_ptr_operator_bool_28C4F810054E5503CD6A7939A49FF08447AB4E6C !65
{
@0      $T114*  $0 = param
        $T114** $1 = local $T114*
        store   $T114* $0, $T114** $1
        $T114*  $2 = load $T114** $1
        $T38**  $3 = elemaddr $T114* $2, long 0
        $T38*   $4 = load $T38** $3
        $T38*   $5 = bitcast void* null
        bool    $6 = equal $T38* $4, $T38* $5
        bool    $7 = not bool $6
        ret     bool $7
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::operator->() const

function $T119* op_arrow_unique_ptr_DA436D4F36E2B19A371D203091867ABB497854F6 !66
{
@0      $T114*  $0 = param
        $T114** $1 = local $T114*
        store   $T114* $0, $T114** $1
        $T114*  $2 = load $T114** $1
        $T38**  $3 = elemaddr $T114* $2, long 0
        $T38*   $4 = load $T38** $3
        ret     $T38* $4
}

// std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::root()

function $T126* mfn_rb_tree_root_D4BB45A937BDCA13D582ABF1939F45CC9C13C9A2 !70
{
@0      $T125*  $0 = param
        $T125** $1 = local $T125*
        store   $T125* $0, $T125** $1
        $T125*  $2 = load $T125** $1
        $T114*  $3 = elemaddr $T125* $2, long 0
        arg     $T114* $3
        $T38*   $4 = call $T119 @op_arrow_unique_ptr_DA436D4F36E2B19A371D203091867ABB497854F6
        $T9*    $5 = bitcast $T38* $4
        arg     $T9* $5
        $T9*    $6 = call $T57 @mfn_rb_node_base_get_parent_5D359D4EEF0AE25B6633747B48E50D691D5795A5
        $T38*   $7 = bitcast $T9* $6
        ret     $T38* $7
}

// std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>*)

function $T127* mfn_rb_tree_set_root_9E57F04C2A7D7A22138A4D2C4E3AC4F53C4C7EFE !71
{
@0      $T125*  $0 = param
        $T38*   $1 = param
        $T125** $2 = local $T125*
        $T38**  $3 = local $T38*
        store   $T125* $0, $T125** $2
        store   $T38* $1, $T38** $3
        $T125*  $4 = load $T125** $2
        $T114*  $5 = elemaddr $T125* $4, long 0
        arg     $T114* $5
        $T38*   $6 = call $T119 @op_arrow_unique_ptr_DA436D4F36E2B19A371D203091867ABB497854F6
        $T9*    $7 = bitcast $T38* $6
        $T38*   $8 = load $T38** $3
        $T9*    $9 = bitcast $T38* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_parent_5A08BDF9027C2D65AD98B7ECD332AD49712B4B12
        ret     void
}

// std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::get() const

function $T119* mfn_unique_ptr_get_83672DE774561F1D6161230BDD8A9EBB0522F65C !72
{
@0      $T114*  $0 = param
        $T114** $1 = local $T114*
        store   $T114* $0, $T114** $1
        $T114*  $2 = load $T114** $1
        $T38**  $3 = elemaddr $T114* $2, long 0
        $T38*   $4 = load $T38** $3
        ret     $T38* $4
}

// std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>*)

function $T127* mfn_rb_tree_set_leftmost_3745AA61FAB04FEFA56E00F013BDD867215EFDD8 !73
{
@0      $T125*  $0 = param
        $T38*   $1 = param
        $T125** $2 = local $T125*
        $T38**  $3 = local $T38*
        store   $T125* $0, $T125** $2
        store   $T38* $1, $T38** $3
        $T125*  $4 = load $T125** $2
        $T114*  $5 = elemaddr $T125* $4, long 0
        arg     $T114* $5
        $T38*   $6 = call $T119 @op_arrow_unique_ptr_DA436D4F36E2B19A371D203091867ABB497854F6
        $T9*    $7 = bitcast $T38* $6
        $T38*   $8 = load $T38** $3
        $T9*    $9 = bitcast $T38* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_left_AA7CA21FBFF06BDBD82E291F946E50574693388F
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>*)

function $T127* mfn_rb_tree_set_rightmost_817F9581C8CE924FB6367A087EBF5ACC0087781E !74
{
@0      $T125*  $0 = param
        $T38*   $1 = param
        $T125** $2 = local $T125*
        $T38**  $3 = local $T38*
        store   $T125* $0, $T125** $2
        store   $T38* $1, $T38** $3
        $T125*  $4 = load $T125** $2
        $T114*  $5 = elemaddr $T125* $4, long 0
        arg     $T114* $5
        $T38*   $6 = call $T119 @op_arrow_unique_ptr_DA436D4F36E2B19A371D203091867ABB497854F6
        $T9*    $7 = bitcast $T38* $6
        $T38*   $8 = load $T38** $3
        $T9*    $9 = bitcast $T38* $8
        arg     $T9* $7
        arg     $T9* $9
        call    $T59 @mfn_rb_node_base_set_right_37BBC55B6C0F71EB870F5843151B172B9BFE1BE7
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::clear()

function $T131* mfn_rb_tree_clear_45055374FBA02ABDCDB59B3AE066113910B5C99F !75
{
@0      $T125*  $0 = param
        $T125** $1 = local $T125*
        $T38**  $2 = local $T38*
        store   $T125* $0, $T125** $1
        $T125*  $3 = load $T125** $1
        $T114*  $4 = elemaddr $T125* $3, long 0
        arg     $T114* $4
        bool    $5 = call $T118 @mfn_unique_ptr_operator_bool_28C4F810054E5503CD6A7939A49FF08447AB4E6C
        bool    $6 = not bool $5
        branch  bool $6, @1, @2

@1      ret     void

@2      $T125*  $7 = load $T125** $1
        arg     $T125* $7
        $T38*   $8 = call $T126 @mfn_rb_tree_root_D4BB45A937BDCA13D582ABF1939F45CC9C13C9A2
        store   $T38* $8, $T38** $2
        $T38*   $9 = load $T38** $2
        bool    $10 = equal $T38* $9, $T38* null
        bool    $11 = not bool $10
        branch  bool $11, @4, @5

@4      $T38*   $12 = load $T38** $2
        $T9*    $13 = bitcast $T38* $12
        void**  $14 = elemaddr $T9* $13, long 0
        void*   $15 = load void** $14
        $T0*    $16 = bitcast void* $15
        long*   $17 = elemaddr $T9* $13, long 1
        long*   $18 = bitcast long* $17
        long    $19 = load long* $18
        byte*   $20 = bitcast $T9* $13
        byte*   $21 = ptroffset byte* $20, long $19
        $T9*    $22 = bitcast byte* $21
        void**  $23 = elemaddr $T0* $16, long 2
        void*   $24 = load void** $23
        $T39*   $25 = bitcast void* $24
        void**  $26 = elemaddr $T0* $16, long 3
        long*   $27 = bitcast void** $26
        long    $28 = load long* $27
        byte*   $29 = bitcast $T9* $22
        byte*   $30 = ptroffset byte* $29, long $28
        $T9*    $31 = bitcast byte* $30
        arg     $T9* $31
        call    $T39* $25
        $T38*   $32 = load $T38** $2
        $T9*    $33 = bitcast $T38* $32
        void**  $34 = elemaddr $T9* $33, long 0
        void*   $35 = load void** $34
        $T0*    $36 = bitcast void* $35
        long*   $37 = elemaddr $T9* $33, long 1
        long*   $38 = bitcast long* $37
        long    $39 = load long* $38
        byte*   $40 = bitcast $T9* $33
        byte*   $41 = ptroffset byte* $40, long $39
        $T9*    $42 = bitcast byte* $41
        arg     $T9* $42
        call    $T47 @op_delete_167D47FA77C24384DD9C13AC7477DB25384C82B4
        $T125*  $43 = load $T125** $1
        $T38*   $44 = bitcast void* null
        arg     $T125* $43
        arg     $T38* $44
        call    $T127 @mfn_rb_tree_set_root_9E57F04C2A7D7A22138A4D2C4E3AC4F53C4C7EFE
        jmp     @5

@5      $T125*  $45 = load $T125** $1
        $T125*  $46 = load $T125** $1
        $T114*  $47 = elemaddr $T125* $46, long 0
        arg     $T114* $47
        $T38*   $48 = call $T119 @mfn_unique_ptr_get_83672DE774561F1D6161230BDD8A9EBB0522F65C
        arg     $T125* $45
        arg     $T38* $48
        call    $T127 @mfn_rb_tree_set_leftmost_3745AA61FAB04FEFA56E00F013BDD867215EFDD8
        $T125*  $49 = load $T125** $1
        $T125*  $50 = load $T125** $1
        $T114*  $51 = elemaddr $T125* $50, long 0
        arg     $T114* $51
        $T38*   $52 = call $T119 @mfn_unique_ptr_get_83672DE774561F1D6161230BDD8A9EBB0522F65C
        arg     $T125* $49
        arg     $T38* $52
        call    $T127 @mfn_rb_tree_set_rightmost_817F9581C8CE924FB6367A087EBF5ACC0087781E
        long    $53 = signextend int 0
        $T125*  $54 = load $T125** $1
        long*   $55 = elemaddr $T125* $54, long 1
        store   long $53, long* $55
        ret     void
}

// std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::~rb_tree()

function $T131* dtor_84D2C01550FD7C046EA90DF8014DB0E17CC77A2C !76
{
@0      $T125*  $0 = param
        $T125** $1 = local $T125*
        store   $T125* $0, $T125** $1
        $T125*  $2 = load $T125** $1
        arg     $T125* $2
        call    $T131 @mfn_rb_tree_clear_45055374FBA02ABDCDB59B3AE066113910B5C99F
        $T125*  $3 = load $T125** $1
        $T114*  $4 = elemaddr $T125* $3, long 0
        arg     $T114* $4
        call    $T115 @dtor_FDB80B49F4DE7F087BAE8AEE2B713CAEF38C434F
        ret     void
}

// std::lock_guard<std::mutex>::~lock_guard()

function $T139* dtor_40FE4AD4D223145D8479C41BF21522F32B8C91A5 !79
{
@0      $T138*  $0 = param
        $T138** $1 = local $T138*
        store   $T138* $0, $T138** $1
        $T138*  $2 = load $T138** $1
        $T137** $3 = elemaddr $T138* $2, long 0
        $T137*  $4 = load $T137** $3
        arg     $T137* $4
        call    $T140 @mfn_mutex_unlock_933B4583FEEAA19A271E1E6FD10B10D69B30368E
        ret     void
}

extern function $T140* mfn_mutex_unlock_933B4583FEEAA19A271E1E6FD10B10D69B30368E

metadata
{
        !0 = {nodeType: 0, sourceFileName: "D:/work/soul-mod/tools/otava/test/string_parser/string_parser.lexer.cppm"}
        !1 = {fullName: "soul::lexer::Variables"}
        !2 = {fullName: "string_parser::lexer::string_lexer_Variables"}
        !3 = {fullName: "std::rb_node_base"}
        !4 = {fullName: "soul::lexer::Lexeme<char>"}
        !5 = {fullName: "std::pair<const soul::lexer::Lexeme<char>, long long int>"}
        !6 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>"}
        !7 = {fullName: "soul::lexer::Lexeme<char8_t>"}
        !8 = {fullName: "std::pair<const soul::lexer::Lexeme<char8_t>, long long int>"}
        !9 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>"}
        !10 = {fullName: "soul::lexer::Lexeme<char16_t>"}
        !11 = {fullName: "std::pair<const soul::lexer::Lexeme<char16_t>, long long int>"}
        !12 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>"}
        !13 = {fullName: "soul::lexer::Lexeme<char32_t>"}
        !14 = {fullName: "std::pair<const soul::lexer::Lexeme<char32_t>, long long int>"}
        !15 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>"}
        !16 = {fullName: "string_parser::lexer::string_lexer_Variables::@destructor() override", nodeType: 1}
        !17 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>::@destructor() override", nodeType: 1}
        !18 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>"}
        !19 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::~unique_ptr()", nodeType: 1}
        !20 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::operator_bool() const", nodeType: 1}
        !21 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::operator->() const", nodeType: 1}
        !22 = {fullName: "std::select_first<const soul::lexer::Lexeme<char>, long long int>"}
        !23 = {fullName: "soul::lexer::LexemeCompare<char>"}
        !24 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>"}
        !25 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::root()", nodeType: 1}
        !26 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>*)", nodeType: 1}
        !27 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>>::get() const", nodeType: 1}
        !28 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>*)", nodeType: 1}
        !29 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char>, long long int>>*)", nodeType: 1}
        !30 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::clear()", nodeType: 1}
        !31 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char>, std::pair<const soul::lexer::Lexeme<char>, long long int>, std::select_first<const soul::lexer::Lexeme<char>, long long int>, soul::lexer::LexemeCompare<char>>::~rb_tree()", nodeType: 1}
        !32 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>::@destructor() override", nodeType: 1}
        !33 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>"}
        !34 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::~unique_ptr()", nodeType: 1}
        !35 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::operator_bool() const", nodeType: 1}
        !36 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::operator->() const", nodeType: 1}
        !37 = {fullName: "std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>"}
        !38 = {fullName: "soul::lexer::LexemeCompare<char8_t>"}
        !39 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>"}
        !40 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::root()", nodeType: 1}
        !41 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>*)", nodeType: 1}
        !42 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>>::get() const", nodeType: 1}
        !43 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>*)", nodeType: 1}
        !44 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char8_t>, long long int>>*)", nodeType: 1}
        !45 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::clear()", nodeType: 1}
        !46 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char8_t>, std::pair<const soul::lexer::Lexeme<char8_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char8_t>, long long int>, soul::lexer::LexemeCompare<char8_t>>::~rb_tree()", nodeType: 1}
        !47 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>::@destructor() override", nodeType: 1}
        !48 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>"}
        !49 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::~unique_ptr()", nodeType: 1}
        !50 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::operator_bool() const", nodeType: 1}
        !51 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::operator->() const", nodeType: 1}
        !52 = {fullName: "std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>"}
        !53 = {fullName: "soul::lexer::LexemeCompare<char16_t>"}
        !54 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>"}
        !55 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::root()", nodeType: 1}
        !56 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>*)", nodeType: 1}
        !57 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>>::get() const", nodeType: 1}
        !58 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>*)", nodeType: 1}
        !59 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char16_t>, long long int>>*)", nodeType: 1}
        !60 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::clear()", nodeType: 1}
        !61 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char16_t>, std::pair<const soul::lexer::Lexeme<char16_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char16_t>, long long int>, soul::lexer::LexemeCompare<char16_t>>::~rb_tree()", nodeType: 1}
        !62 = {fullName: "std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>::@destructor() override", nodeType: 1}
        !63 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>"}
        !64 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::~unique_ptr()", nodeType: 1}
        !65 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::operator_bool() const", nodeType: 1}
        !66 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::operator->() const", nodeType: 1}
        !67 = {fullName: "std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>"}
        !68 = {fullName: "soul::lexer::LexemeCompare<char32_t>"}
        !69 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>"}
        !70 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::root()", nodeType: 1}
        !71 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::set_root(std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>*)", nodeType: 1}
        !72 = {fullName: "std::unique_ptr<std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>>::get() const", nodeType: 1}
        !73 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::set_leftmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>*)", nodeType: 1}
        !74 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::set_rightmost(std::rb_node<std::pair<const soul::lexer::Lexeme<char32_t>, long long int>>*)", nodeType: 1}
        !75 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::clear()", nodeType: 1}
        !76 = {fullName: "std::rb_tree<soul::lexer::Lexeme<char32_t>, std::pair<const soul::lexer::Lexeme<char32_t>, long long int>, std::select_first<const soul::lexer::Lexeme<char32_t>, long long int>, soul::lexer::LexemeCompare<char32_t>>::~rb_tree()", nodeType: 1}
        !77 = {fullName: "std::mutex"}
        !78 = {fullName: "std::lock_guard<std::mutex>"}
        !79 = {fullName: "std::lock_guard<std::mutex>::~lock_guard()", nodeType: 1}
}
