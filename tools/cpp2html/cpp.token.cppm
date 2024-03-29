
// this file has been automatically generated from 'C:/work/soul-mod/tools/cpp2html/cpp.token' using soul lexer generator version 4.0.0

export module cpp.token;

import std.core;

export namespace cpp::token {

constexpr int32_t tokenSetID = 992473601;

constexpr int64_t ALIGNAS = (static_cast<int64_t>(tokenSetID) << 32) | 1;
constexpr int64_t ALIGNOF = (static_cast<int64_t>(tokenSetID) << 32) | 2;
constexpr int64_t ASM = (static_cast<int64_t>(tokenSetID) << 32) | 3;
constexpr int64_t AUTO = (static_cast<int64_t>(tokenSetID) << 32) | 4;
constexpr int64_t BOOL = (static_cast<int64_t>(tokenSetID) << 32) | 5;
constexpr int64_t BREAK = (static_cast<int64_t>(tokenSetID) << 32) | 6;
constexpr int64_t CASE = (static_cast<int64_t>(tokenSetID) << 32) | 7;
constexpr int64_t CATCH = (static_cast<int64_t>(tokenSetID) << 32) | 8;
constexpr int64_t CHAR = (static_cast<int64_t>(tokenSetID) << 32) | 9;
constexpr int64_t CHAR8_T = (static_cast<int64_t>(tokenSetID) << 32) | 10;
constexpr int64_t CHAR16_T = (static_cast<int64_t>(tokenSetID) << 32) | 11;
constexpr int64_t CHAR32_T = (static_cast<int64_t>(tokenSetID) << 32) | 12;
constexpr int64_t CLASS = (static_cast<int64_t>(tokenSetID) << 32) | 13;
constexpr int64_t CONCEPT = (static_cast<int64_t>(tokenSetID) << 32) | 14;
constexpr int64_t CONST = (static_cast<int64_t>(tokenSetID) << 32) | 15;
constexpr int64_t CONSTEVAL = (static_cast<int64_t>(tokenSetID) << 32) | 16;
constexpr int64_t CONSTEXPR = (static_cast<int64_t>(tokenSetID) << 32) | 17;
constexpr int64_t CONSTINIT = (static_cast<int64_t>(tokenSetID) << 32) | 18;
constexpr int64_t CONST_CAST = (static_cast<int64_t>(tokenSetID) << 32) | 19;
constexpr int64_t CONTINUE = (static_cast<int64_t>(tokenSetID) << 32) | 20;
constexpr int64_t CO_AWAIT = (static_cast<int64_t>(tokenSetID) << 32) | 21;
constexpr int64_t CO_RETURN = (static_cast<int64_t>(tokenSetID) << 32) | 22;
constexpr int64_t CO_YIELD = (static_cast<int64_t>(tokenSetID) << 32) | 23;
constexpr int64_t DECLTYPE = (static_cast<int64_t>(tokenSetID) << 32) | 24;
constexpr int64_t DEFAULT = (static_cast<int64_t>(tokenSetID) << 32) | 25;
constexpr int64_t DELETE = (static_cast<int64_t>(tokenSetID) << 32) | 26;
constexpr int64_t DO = (static_cast<int64_t>(tokenSetID) << 32) | 27;
constexpr int64_t DOUBLE = (static_cast<int64_t>(tokenSetID) << 32) | 28;
constexpr int64_t DYNAMIC_CAST = (static_cast<int64_t>(tokenSetID) << 32) | 29;
constexpr int64_t ELSE = (static_cast<int64_t>(tokenSetID) << 32) | 30;
constexpr int64_t ENUM = (static_cast<int64_t>(tokenSetID) << 32) | 31;
constexpr int64_t EXPLICIT = (static_cast<int64_t>(tokenSetID) << 32) | 32;
constexpr int64_t EXPORT = (static_cast<int64_t>(tokenSetID) << 32) | 33;
constexpr int64_t EXTERN = (static_cast<int64_t>(tokenSetID) << 32) | 34;
constexpr int64_t FALSE = (static_cast<int64_t>(tokenSetID) << 32) | 35;
constexpr int64_t FLOAT = (static_cast<int64_t>(tokenSetID) << 32) | 36;
constexpr int64_t FOR = (static_cast<int64_t>(tokenSetID) << 32) | 37;
constexpr int64_t FRIEND = (static_cast<int64_t>(tokenSetID) << 32) | 38;
constexpr int64_t GOTO = (static_cast<int64_t>(tokenSetID) << 32) | 39;
constexpr int64_t IF = (static_cast<int64_t>(tokenSetID) << 32) | 40;
constexpr int64_t IMPORT = (static_cast<int64_t>(tokenSetID) << 32) | 41;
constexpr int64_t INLINE = (static_cast<int64_t>(tokenSetID) << 32) | 42;
constexpr int64_t INT = (static_cast<int64_t>(tokenSetID) << 32) | 43;
constexpr int64_t LONG = (static_cast<int64_t>(tokenSetID) << 32) | 44;
constexpr int64_t MUTABLE = (static_cast<int64_t>(tokenSetID) << 32) | 45;
constexpr int64_t NAMESPACE = (static_cast<int64_t>(tokenSetID) << 32) | 46;
constexpr int64_t NEW = (static_cast<int64_t>(tokenSetID) << 32) | 47;
constexpr int64_t NOEXCEPT = (static_cast<int64_t>(tokenSetID) << 32) | 48;
constexpr int64_t NULLPTR = (static_cast<int64_t>(tokenSetID) << 32) | 49;
constexpr int64_t OPERATOR = (static_cast<int64_t>(tokenSetID) << 32) | 50;
constexpr int64_t PRIVATE = (static_cast<int64_t>(tokenSetID) << 32) | 51;
constexpr int64_t MODULE = (static_cast<int64_t>(tokenSetID) << 32) | 52;
constexpr int64_t PROTECTED = (static_cast<int64_t>(tokenSetID) << 32) | 53;
constexpr int64_t PUBLIC = (static_cast<int64_t>(tokenSetID) << 32) | 54;
constexpr int64_t REGISTER = (static_cast<int64_t>(tokenSetID) << 32) | 55;
constexpr int64_t REINTERPRET_CAST = (static_cast<int64_t>(tokenSetID) << 32) | 56;
constexpr int64_t REQUIRES = (static_cast<int64_t>(tokenSetID) << 32) | 57;
constexpr int64_t RETURN = (static_cast<int64_t>(tokenSetID) << 32) | 58;
constexpr int64_t SHORT = (static_cast<int64_t>(tokenSetID) << 32) | 59;
constexpr int64_t SIGNED = (static_cast<int64_t>(tokenSetID) << 32) | 60;
constexpr int64_t SIZEOF = (static_cast<int64_t>(tokenSetID) << 32) | 61;
constexpr int64_t STATIC = (static_cast<int64_t>(tokenSetID) << 32) | 62;
constexpr int64_t STATIC_ASSERT = (static_cast<int64_t>(tokenSetID) << 32) | 63;
constexpr int64_t STATIC_CAST = (static_cast<int64_t>(tokenSetID) << 32) | 64;
constexpr int64_t STRUCT = (static_cast<int64_t>(tokenSetID) << 32) | 65;
constexpr int64_t SWITCH = (static_cast<int64_t>(tokenSetID) << 32) | 66;
constexpr int64_t TEMPLATE = (static_cast<int64_t>(tokenSetID) << 32) | 67;
constexpr int64_t THIS = (static_cast<int64_t>(tokenSetID) << 32) | 68;
constexpr int64_t THREAD_LOCAL = (static_cast<int64_t>(tokenSetID) << 32) | 69;
constexpr int64_t THROW = (static_cast<int64_t>(tokenSetID) << 32) | 70;
constexpr int64_t TRUE = (static_cast<int64_t>(tokenSetID) << 32) | 71;
constexpr int64_t TRY = (static_cast<int64_t>(tokenSetID) << 32) | 72;
constexpr int64_t TYPEDEF = (static_cast<int64_t>(tokenSetID) << 32) | 73;
constexpr int64_t TYPEID = (static_cast<int64_t>(tokenSetID) << 32) | 74;
constexpr int64_t TYPENAME = (static_cast<int64_t>(tokenSetID) << 32) | 75;
constexpr int64_t UNION = (static_cast<int64_t>(tokenSetID) << 32) | 76;
constexpr int64_t UNSIGNED = (static_cast<int64_t>(tokenSetID) << 32) | 77;
constexpr int64_t USING = (static_cast<int64_t>(tokenSetID) << 32) | 78;
constexpr int64_t VIRTUAL = (static_cast<int64_t>(tokenSetID) << 32) | 79;
constexpr int64_t VOID = (static_cast<int64_t>(tokenSetID) << 32) | 80;
constexpr int64_t VOLATILE = (static_cast<int64_t>(tokenSetID) << 32) | 81;
constexpr int64_t WCHAR_T = (static_cast<int64_t>(tokenSetID) << 32) | 82;
constexpr int64_t WHILE = (static_cast<int64_t>(tokenSetID) << 32) | 83;
constexpr int64_t FLOATLIT = (static_cast<int64_t>(tokenSetID) << 32) | 84;
constexpr int64_t INTLIT = (static_cast<int64_t>(tokenSetID) << 32) | 85;
constexpr int64_t CHARLIT = (static_cast<int64_t>(tokenSetID) << 32) | 86;
constexpr int64_t STRINGLIT = (static_cast<int64_t>(tokenSetID) << 32) | 87;
constexpr int64_t BEGINRAWSTRINGLIT = (static_cast<int64_t>(tokenSetID) << 32) | 88;
constexpr int64_t COLONCOLON = (static_cast<int64_t>(tokenSetID) << 32) | 89;
constexpr int64_t COMMA = (static_cast<int64_t>(tokenSetID) << 32) | 90;
constexpr int64_t ASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 91;
constexpr int64_t MULASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 92;
constexpr int64_t DIVASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 93;
constexpr int64_t REMASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 94;
constexpr int64_t ADDASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 95;
constexpr int64_t SUBASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 96;
constexpr int64_t SHIFTRIGHTASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 97;
constexpr int64_t SHIFTLEFTASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 98;
constexpr int64_t ANDASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 99;
constexpr int64_t XORASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 100;
constexpr int64_t ORASSIGN = (static_cast<int64_t>(tokenSetID) << 32) | 101;
constexpr int64_t QUEST = (static_cast<int64_t>(tokenSetID) << 32) | 102;
constexpr int64_t COLON = (static_cast<int64_t>(tokenSetID) << 32) | 103;
constexpr int64_t OROR = (static_cast<int64_t>(tokenSetID) << 32) | 104;
constexpr int64_t AMPAMP = (static_cast<int64_t>(tokenSetID) << 32) | 105;
constexpr int64_t OR = (static_cast<int64_t>(tokenSetID) << 32) | 106;
constexpr int64_t XOR = (static_cast<int64_t>(tokenSetID) << 32) | 107;
constexpr int64_t AMP = (static_cast<int64_t>(tokenSetID) << 32) | 108;
constexpr int64_t EQ = (static_cast<int64_t>(tokenSetID) << 32) | 109;
constexpr int64_t NEQ = (static_cast<int64_t>(tokenSetID) << 32) | 110;
constexpr int64_t LEQ = (static_cast<int64_t>(tokenSetID) << 32) | 111;
constexpr int64_t GEQ = (static_cast<int64_t>(tokenSetID) << 32) | 112;
constexpr int64_t SPACESHIP = (static_cast<int64_t>(tokenSetID) << 32) | 113;
constexpr int64_t LANGLE = (static_cast<int64_t>(tokenSetID) << 32) | 114;
constexpr int64_t RANGLE = (static_cast<int64_t>(tokenSetID) << 32) | 115;
constexpr int64_t SHIFTLEFT = (static_cast<int64_t>(tokenSetID) << 32) | 116;
constexpr int64_t SHIFTRIGHT = (static_cast<int64_t>(tokenSetID) << 32) | 117;
constexpr int64_t PLUS = (static_cast<int64_t>(tokenSetID) << 32) | 118;
constexpr int64_t MINUS = (static_cast<int64_t>(tokenSetID) << 32) | 119;
constexpr int64_t STAR = (static_cast<int64_t>(tokenSetID) << 32) | 120;
constexpr int64_t DIV = (static_cast<int64_t>(tokenSetID) << 32) | 121;
constexpr int64_t MOD = (static_cast<int64_t>(tokenSetID) << 32) | 122;
constexpr int64_t DOTSTAR = (static_cast<int64_t>(tokenSetID) << 32) | 123;
constexpr int64_t ARROWSTAR = (static_cast<int64_t>(tokenSetID) << 32) | 124;
constexpr int64_t LPAREN = (static_cast<int64_t>(tokenSetID) << 32) | 125;
constexpr int64_t RPAREN = (static_cast<int64_t>(tokenSetID) << 32) | 126;
constexpr int64_t PLUSPLUS = (static_cast<int64_t>(tokenSetID) << 32) | 127;
constexpr int64_t MINUSMINUS = (static_cast<int64_t>(tokenSetID) << 32) | 128;
constexpr int64_t EXCLAMATION = (static_cast<int64_t>(tokenSetID) << 32) | 129;
constexpr int64_t TILDE = (static_cast<int64_t>(tokenSetID) << 32) | 130;
constexpr int64_t LBRACKET = (static_cast<int64_t>(tokenSetID) << 32) | 131;
constexpr int64_t RBRACKET = (static_cast<int64_t>(tokenSetID) << 32) | 132;
constexpr int64_t LBRACE = (static_cast<int64_t>(tokenSetID) << 32) | 133;
constexpr int64_t RBRACE = (static_cast<int64_t>(tokenSetID) << 32) | 134;
constexpr int64_t DOT = (static_cast<int64_t>(tokenSetID) << 32) | 135;
constexpr int64_t ARROW = (static_cast<int64_t>(tokenSetID) << 32) | 136;
constexpr int64_t SEMICOLON = (static_cast<int64_t>(tokenSetID) << 32) | 137;
constexpr int64_t ELLIPSIS = (static_cast<int64_t>(tokenSetID) << 32) | 138;
constexpr int64_t WS = (static_cast<int64_t>(tokenSetID) << 32) | 139;
constexpr int64_t LINECOMMENT = (static_cast<int64_t>(tokenSetID) << 32) | 140;
constexpr int64_t BLOCKCOMMENT = (static_cast<int64_t>(tokenSetID) << 32) | 141;
constexpr int64_t BLOCKCOMMENTLINE = (static_cast<int64_t>(tokenSetID) << 32) | 142;
constexpr int64_t KEYWORD = (static_cast<int64_t>(tokenSetID) << 32) | 143;
constexpr int64_t ID = (static_cast<int64_t>(tokenSetID) << 32) | 144;
constexpr int64_t NUMBER = (static_cast<int64_t>(tokenSetID) << 32) | 145;
constexpr int64_t PP = (static_cast<int64_t>(tokenSetID) << 32) | 146;
constexpr int64_t OTHER = (static_cast<int64_t>(tokenSetID) << 32) | 147;
constexpr int64_t __THREAD = (static_cast<int64_t>(tokenSetID) << 32) | 148;
constexpr int64_t __DECLSPEC = (static_cast<int64_t>(tokenSetID) << 32) | 149;
constexpr int64_t __CDECL = (static_cast<int64_t>(tokenSetID) << 32) | 150;
constexpr int64_t __FASTCALL = (static_cast<int64_t>(tokenSetID) << 32) | 151;
constexpr int64_t __STDCALL = (static_cast<int64_t>(tokenSetID) << 32) | 152;
constexpr int64_t __THISCALL = (static_cast<int64_t>(tokenSetID) << 32) | 153;
constexpr int64_t __VECTORCALL = (static_cast<int64_t>(tokenSetID) << 32) | 154;
constexpr int64_t __INT64 = (static_cast<int64_t>(tokenSetID) << 32) | 155;
constexpr int64_t __INT32 = (static_cast<int64_t>(tokenSetID) << 32) | 156;
constexpr int64_t __INT16 = (static_cast<int64_t>(tokenSetID) << 32) | 157;
constexpr int64_t __INT8 = (static_cast<int64_t>(tokenSetID) << 32) | 158;
constexpr int64_t __UNALIGNED = (static_cast<int64_t>(tokenSetID) << 32) | 159;
constexpr int64_t __INLINE = (static_cast<int64_t>(tokenSetID) << 32) | 160;
constexpr int64_t __NULLPTR = (static_cast<int64_t>(tokenSetID) << 32) | 161;
constexpr int64_t __PRAGMA = (static_cast<int64_t>(tokenSetID) << 32) | 162;
constexpr int64_t MAX = (static_cast<int64_t>(tokenSetID) << 32) | 163;

} // cpp::token
