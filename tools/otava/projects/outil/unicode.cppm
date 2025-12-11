// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module util.unicode;

import util.binary.stream.writer;
import util.binary.stream.reader;
import std;

export namespace util {

std::string SoulVersionStr();
std::expected<std::string, int> SoulRoot();
std::expected<std::string, int> SoulUcdFilePath();

std::unexpected<int> InvalidUtf8Sequence();
std::unexpected<int> UnicodeError(const std::string& message_);

std::expected<std::u32string, int> ToUtf32(const std::string& utf8Str);
std::expected<std::u32string, int> ToUtf32(const std::u16string& utf16Str);
std::expected<std::u32string, int> ToUtf32(const std::u32string& utf32Str);
std::expected<std::u16string, int> ToUtf16(const std::u32string& utf32Str);
std::expected<std::u16string, int> ToUtf16(const std::u16string& utf16Str);
std::expected<std::u16string, int> ToUtf16(const std::string& u8str);
std::expected<std::string, int> ToUtf8(const std::u32string& utf32Str);
std::expected<std::string, int> ToUtf8(const std::u16string& utf16Str);
std::expected<std::string, int> ToUtf8(const std::string& utf8Str);

class Utf8ToUtf32Engine
{
public:
    Utf8ToUtf32Engine();
    std::expected<bool, int> Put(std::uint8_t x);
    inline bool ResultReady() const { return resultReady; }
    inline char32_t Result() const { return result; }
private:
    int state;
    bool resultReady;
    char32_t result;
    std::vector<std::uint8_t> bytes;
};

std::expected<std::u32string, int> ToUpper(const std::u32string& s);
std::expected<std::u16string, int> ToUpper(const std::u16string& s);
std::expected<std::string, int> ToUpper(const std::string& s);
std::expected<std::u32string, int> ToLower(const std::u32string& s);
std::expected<std::u16string, int> ToLower(const std::u16string& s);
std::expected<std::string, int> ToLower(const std::string& s);
std::string MakeCanonicalPropertyName(const std::string& s);

enum class BinaryPropertyId : std::uint8_t
{
    asciiHexDigit,
    alphabetic,
    bidiControl,
    bidiMirrored,
    cased,
    compositionExclusion,
    caseIgnorable,
    fullCompositionExclusion,
    changesWhenCasefolded,
    changesWhenCaseMapped,
    changesWhenNFKCCasefolded,
    changesWhenLowercased,
    changesWhenTitlecased,
    changesWhenUppercased,
    dash,
    deprecated,
    defaultIgnorableCodePoint,
    diacritic,
    extender,
    graphemeBase,
    graphemeExtend,
    graphemeLink,
    hexDigit,
    hyphen,
    idContinue,
    ideographic,
    idStart,
    idsBinaryOperator,
    idsTrinaryOperator,
    joinControl,
    logicalOrderException,
    lowercase,
    math,
    noncharacterCodePoint,
    otherAlphabetic,
    otherDefaultIgnorableCodePoint,
    otherGraphemeExtend,
    otherIdContinue,
    otherIdStart,
    otherLowercase,
    otherMath,
    otherUppercase,
    patternSyntax,
    patternWhiteSpace,
    prependedConcatenationMark,
    quotationMark,
    radical,
    softDotted,
    sentenceterminal,
    terminalPunctuation,
    unifiedIdeograph,
    uppercase,
    variationSelector,
    whiteSpace,
    xidContinue,
    xidStart,
    expandsOnNFC,
    expandsOnNFD,
    expandsOnNFKC,
    expandsOnNFKD
};

class BinaryProperty
{
public:
    BinaryProperty(BinaryPropertyId id_, const std::string& shortName_, const std::string& longName_);
    inline BinaryPropertyId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
private:
    BinaryPropertyId id;
    std::string shortName;
    std::string longName;
};

class BinaryPropertyTable
{
public:
    static BinaryPropertyTable& Instance();
    std::expected<const BinaryProperty*, int> GetBinaryProperty(BinaryPropertyId binaryPropertyId) const;
    bool IsBinaryProperty(const std::string& shortName) const;
    std::expected<const BinaryProperty*, int> GetBinaryPropertyByShortName(const std::string& shortName) const;
    std::expected<const BinaryProperty*, int> GetBinaryPropertyByLongName(const std::string& longName) const;
    const std::vector<BinaryProperty>& BinaryProperties() const { return binaryProperties; }
private:
    BinaryPropertyTable();
    std::map<BinaryPropertyId, const BinaryProperty*> binaryPropertyIdMap;
    std::map<std::string, const BinaryProperty*> shortNameMap;
    std::map<std::string, const BinaryProperty*> longNameMap;
    std::vector<BinaryProperty> binaryProperties;
};

inline std::expected<const BinaryProperty*, int> GetBinaryProperty(BinaryPropertyId id)
{
    std::expected<const BinaryProperty*, int> s = BinaryPropertyTable::Instance().GetBinaryProperty(id);
    return s;
}

inline std::expected<const BinaryProperty*, int> GetBinaryPropertyByShortName(const std::string& shortName)
{
    return BinaryPropertyTable::Instance().GetBinaryPropertyByShortName(shortName);
}

inline std::expected<const BinaryProperty*, int> GetBinaryPropertyByLongName(const std::string& longName)
{
    return BinaryPropertyTable::Instance().GetBinaryPropertyByLongName(longName);
}

enum class BlockId : std::uint16_t
{
    none = 0,
    adlam, aegeanNumbers, ahom, alchemical, alphabeticPf, anatolianHieroglyphs, ancientGreekMusic, ancientGreekNumbers, ancientSymbols,
    arabic, arabicExtA, arabicMath, arabicPfA, arabicPfB, arabicSup, armenian, arrows, ascii, avestan,
    balinese, bamum, bamumSup, bassaVah, batak, bengali, bhaisuki, blockElements, bopomofo, bopomofoExt, boxDrawing,
    brahmi, braille, buginese, buhid, byzantineMusic,
    carian, caucasianAlbanian, chakma, cham, cherokee, cherokeeSup, chessSymbols,
    cjk, cjkCompat, cjkCompatForms, cjkCompatIdeographs, cjkCompatIdeographsSup, cjkExtA, cjkExtB, cjkExtC, cjkExtD, cjkExtE, cjkExtF,
    cjkRadicalsSup, cjkStrokes, cjkSymbols, compatJamo, controlPictures, coptic, copticEpactNumbers, countingRod, cuneiform,
    cuneiformNumbers, currencySymbols, cypriotSyllabary, cyrillic, cyrillicExtA, cyrillicExtB, cyrillicExtC, cyrillicSup,
    deseret, devanagari, devanagariExt, diacriticals, diariticalsForSymbols, diacriticalsSup, diacriticalsExt, dingbats, dogra, domino, duployan,
    earlyDynasticCuneiform, egyptianHieroglyphs, egyptianHieroglyphFormatControls, elbasan, elymaic, emoticons, enclosedAlphanum, enclosedAlphanumSup, enclosedCjk, enclosedIdeographicSup,
    ethiopic, ethiopicExt, ethiopicExtA, ethiopicSup,
    geometricShapes, geometricShapesExt, georgian, georgianExt, georgianSup, glagolitic, glagoliticSup, gothic, grantha, greek, greekExt, gujarati, gunjalaGondi, gurmukhi,
    halfAndFullForms, halfMarks, hangul, hanifiRohingya, hanunoo, hatran, hebrew, highPuSurrogates, highSurrogates, hiragana,
    idc, ideographicSymbols, imperialAramaic, indicNumberForms, inscriptionalPahlavi, inscriptionalParthian, ipaExt, indicSiyaqNumbers,
    jamo, jamoExtA, jamoExtB, javanese, kaithi, kanaExtA, smallKanaExt, kanaSup, kanbun, kangxi, kannada, katakana, katakanaExt, kayahLi, kharoshthi, khmer, khmerSymbols, khojki, khudawadi,
    lao, latin1Sup, latinExtA, latinExtAdditional, latinExtB, latinExtC, latinExtD, latinExtE, lepcha, letterlikeSymbols, limbu,
    linearA, linearBIdeograms, linearBSyllabary, lisu, lowSurrogates, lycian, lydian,
    mahajani, mahjong, makasar, malayalam, mandaic, manichean, marchen, masaramGondi, mathAlphanum, mathOperators, mayanNumerals, medefaidrin, meeteiMayek, meeteiMayekExt, mendeKikakui, meroiticCursive, meroiticHieroglyphs,
    miao, miscArrows, miscMathSymbolsA, miscMathSymbolsB, miscPictographs, miscSymbols, miscTechnical, modi, modifierLetters, modifierToneLetters, mongolian, mongolianSup,
    mro, music, multani, myanmar, myanmarExtA, myanmarExtB,
    nabataean, nb, nandinagari, newTaiLue, newa, nko, numberForms, nushu, nyiakengPuachueHmong,
    ocr, ogham, olChiki, oldHungarian, oldItalic, oldNorthArabian, oldPermic, oldPersian, oldSogdian, oldSouthArabian, oldTurkic, oriya, ornamentalDingbats, osage, osmanya, ottomanSiyaqNumbers,
    pahawhHmong, palmyrene, pauCinHau, phagsPa, phaistos, phoenician, phoneticExt, phoneticExtSup, playingCards, psalterPahlavi, pua, punctuation,
    rejang, rumi, runic,
    samaritan, saurashtra, sharada, shavian, shorthandFormatControls, siddham, sinhala, sinhalaArchaicNumbers, smallForms, sogdian, soraSompeng, soyombo, specials, sundanese, sundaneseSup,
    supArrowsA, supArrowsB, supArrowsC, supMathOperators, supPuaA, supPuaB, supPunctuation, supSymbolsAndPictographs, superAndSub, suttonSignWriting, sylotiNagri, symbolsAndPictographsExtA, syriac,
    syriacSup,
    tagalog, tagbanwa, tags, taiLe, taiTham, taiViet, taiXuanJing, takri, tamil, tamilSup, tangut, tangutComponents, telugu, thaana, thai, tibetan, tifinagh, tirhuta, transportAndMap,
    ucas, ucasExt, ugaritic, vai, vedicExt, verticalForms, vs, vsSup, wancho, warangCiti, yiRadicals, yiSyllables, yijing, zanabazarSquare
};

class Block
{
public:
    Block(BlockId id_, const std::string& shortName_, const std::string& longName_, char32_t start, char32_t end_);
    inline BlockId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
    inline char32_t Start() const { return start; }
    inline char32_t End() const { return end; }
private:
    BlockId id;
    std::string shortName;
    std::string longName;
    char32_t start;
    char32_t end;
};

class BlockTable
{
public:
    static BlockTable& Instance();
    std::expected<const Block*, int> GetBlock(BlockId blockId) const;
    std::expected<const Block*, int> GetBlockByShortName(const std::string& shortName) const;
    std::expected<const Block*, int> GetBlockByLongName(const std::string& longName) const;
    const std::vector<Block>& Blocks() const { return blocks; }
private:
    BlockTable();
    std::map<BlockId, const Block*> blockIdMap;
    std::map<std::string, const Block*> shortNameMap;
    std::map<std::string, const Block*> longNameMap;
    std::vector<Block> blocks;
};

inline std::expected<const Block*, int> GetBlock(BlockId blockId)
{
    return BlockTable::Instance().GetBlock(blockId);
}

inline std::expected<const Block*, int>  GetBlockByShortName(const std::string& shortName)
{
    return BlockTable::Instance().GetBlockByShortName(shortName);
}

inline std::expected<const Block*, int>  GetBlockByLongName(const std::string& longName)
{
    return BlockTable::Instance().GetBlockByLongName(longName);
}

enum class GeneralCategoryId : std::int32_t
{
    none = 0,
    Lu = 1 << 0, Ll = 1 << 1, Lt = 1 << 2, Lm = 1 << 3, Lo = 1 << 4,
    LC = Lu | Ll | Lt,
    L = Lu | Ll | Lt | Lm | Lo,
    Mn = 1 << 5, Mc = 1 << 6, Me = 1 << 7,
    M = Mn | Mc | Me,
    Nd = 1 << 8, Nl = 1 << 9, No = 1 << 10,
    N = Nd | Nl | No,
    Pc = 1 << 11, Pd = 1 << 12, Ps = 1 << 13, Pe = 1 << 14, Pi = 1 << 15, Pf = 1 << 16, Po = 1 << 17,
    P = Pc | Pd | Ps | Pe | Pi | Pf | Po,
    Sm = 1 << 18, Sc = 1 << 19, Sk = 1 << 20, So = 1 << 21,
    S = Sm | Sc | Sk | So,
    Zs = 1 << 22, Zl = 1 << 23, Zp = 1 << 24,
    Z = Zs | Zl | Zp,
    Cc = 1 << 25, Cf = 1 << 26, Cs = 1 << 27, Co = 1 << 28, Cn = 1 << 29,
    C = Cc | Cf | Cs | Co | Cn,
    G = L | M | N | P | S | Zs,
    B = L | N | P | S | Zs
};

inline GeneralCategoryId operator&(GeneralCategoryId left, GeneralCategoryId right)
{
    return GeneralCategoryId(std::int32_t(left) & std::int32_t(right));
}

inline GeneralCategoryId operator|(GeneralCategoryId left, GeneralCategoryId right)
{
    return GeneralCategoryId(std::int32_t(left) | std::int32_t(right));
}

class GeneralCategory
{
public:
    GeneralCategory(GeneralCategoryId id_, const std::string& shortName_, const std::string& longName_);
    inline GeneralCategoryId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
private:
    GeneralCategoryId id;
    std::string shortName;
    std::string longName;
};

class GeneralCategoryTable
{
public:
    static GeneralCategoryTable& Instance();
    std::expected<const GeneralCategory*, int> GetGeneralCategory(GeneralCategoryId generalCategoryId) const;
    std::expected<const GeneralCategory*, int> GetGeneralCategoryByShortName(const std::string& shortName) const;
    std::expected<const GeneralCategory*, int> GetGeneralCategoryByLongName(const std::string& shortName) const;
    const std::vector<GeneralCategory>& GeneralCategories() const { return generalCategories; }
private:
    GeneralCategoryTable();
    std::map<GeneralCategoryId, const GeneralCategory*> generalCategoryIdMap;
    std::map<std::string, const GeneralCategory*> shortNameMap;
    std::map<std::string, const GeneralCategory*> longNameMap;
    std::vector<GeneralCategory> generalCategories;
};

inline std::expected<const GeneralCategory*, int> GetGeneralCategory(GeneralCategoryId id)
{
    return GeneralCategoryTable::Instance().GetGeneralCategory(id);
}

inline std::expected<const GeneralCategory*, int> GetGeneralCategoryByShortName(const std::string& shortName)
{
    return GeneralCategoryTable::Instance().GetGeneralCategoryByShortName(shortName);
}

inline std::expected<const GeneralCategory*, int> GetGeneralCategoryByLongName(const std::string& longName)
{
    return GeneralCategoryTable::Instance().GetGeneralCategoryByLongName(longName);
}

enum class AgeId : std::uint8_t
{
    age_unassigned = 0,
    age_1_1,
    age_2_0, age_2_1,
    age_3_0, age_3_1, age_3_2,
    age_4_0, age_4_1,
    age_5_0, age_5_1, age_5_2,
    age_6_0, age_6_1, age_6_2, age_6_3,
    age_7_0,
    age_8_0,
    age_9_0,
    age_10_0,
    age_11_0,
    age_12_0, age_12_1
};

class Age
{
public:
    Age(AgeId id_, const std::string& version_);
    AgeId Id() const { return id; }
    const std::string& Version() const { return version; }
private:
    AgeId id;
    std::string version;
};

class AgeTable
{
public:
    static AgeTable& Instance();
    std::expected<const Age*, int> GetAge(AgeId id) const;
    std::expected<const Age*, int> GetAge(const std::string& version) const;
    inline const std::vector<Age>& Ages() const { return ages; }
private:
    AgeTable();
    std::map<AgeId, const Age*> ageIdMap;
    std::map<std::string, const Age*> versionMap;
    std::vector<Age> ages;
};

inline std::expected<const Age*, int> GetAge(AgeId id)
{
    return AgeTable::Instance().GetAge(id);
}

inline std::expected<const Age*, int> GetAge(const std::string& version)
{
    return AgeTable::Instance().GetAge(version);
}

enum class ScriptId : std::uint8_t
{
    none = 0,
    adlm, aghb, ahom, arab, armi, armn, avst,
    bali, bamu, bass, batk, beng, bhks, bopo, brah, brai, bugi, buhd,
    cakm, cans, cari, cham, cher, copt, cprt, cyrl,
    deva, dogr, dsrt, dupl,
    elba, elym, egyp, ethi,
    geor, glag, gong, gonm, goth, gran, grek, gujr, guru,
    hang, hani, hano, hatr, hebr, hira, hluw, hmng, hmnp, hrkt, hung,
    ital,
    java,
    kali, kana, khar, khmr, khoj, knda, kthi,
    lana, laoo, latn, lepc, limb, lina, linb, lisu, lyci, lydi,
    mahj, maka, mand, mani, marc, medf, mend, merc, mero, mlym, modi, mong, mroo, mtei, mult, mymr,
    nand, narb, nbat, newa, nkoo, nshu,
    ogam, olck, orkh, orya, osge, osma,
    palm, pauc, perm, phag, phli, phlp, phnx, plrd, prti,
    qaai,
    rjng, rohg, runr,
    samr, sarb, saur, sgnw, shaw, shrd, sidd, sind, sinh, sogd, sogo, sora, soyo, sund, sylo, syrc,
    tagb, takr, tale, talu, taml, tang, tavt, telu, tfng, tglg, thaa, thai, tibt, tirh,
    ugar,
    vaii,
    wara,
    wcho,
    xpeo, xsux,
    yiii, zanb,
    zinh, zyyy, zzzz
};

class Script
{
public:
    Script(ScriptId id_, const std::string& shortName_, const std::string& longName_);
    inline ScriptId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
private:
    ScriptId id;
    std::string shortName;
    std::string longName;
};

class ScriptTable
{
public:
    static ScriptTable& Instance();
    std::expected<const Script*, int> GetScript(ScriptId id) const;
    std::expected<const Script*, int> GetScriptByShortName(const std::string& shortName) const;
    std::expected<const Script*, int> GetScriptByLongName(const std::string& longName) const;
    inline const std::vector<Script>& Scripts() const { return scripts; }
private:
    ScriptTable();
    std::vector<Script> scripts;
    std::map<ScriptId, const Script*> scriptIdMap;
    std::map<std::string, const Script*> shortNameMap;
    std::map<std::string, const Script*> longNameMap;
};

inline std::expected<const Script*, int> GetScript(ScriptId id)
{
    return ScriptTable::Instance().GetScript(id);
}

inline std::expected<const Script*, int> GetScriptByShortName(const std::string& shortName)
{
    return ScriptTable::Instance().GetScriptByShortName(shortName);
}

inline std::expected<const Script*, int> GetScriptByLongName(const std::string& longName)
{
    return ScriptTable::Instance().GetScriptByLongName(longName);
}

class CharacterInfo
{
public:
    CharacterInfo();
    bool GetBinaryProperty(BinaryPropertyId binaryPropertyId) const
    {
        std::uint64_t mask = static_cast<std::uint64_t>(1) << static_cast<std::uint64_t>(static_cast<std::uint8_t>(binaryPropertyId));
        return (binaryProperties & mask) != 0;
    }
    void SetBinaryPropery(BinaryPropertyId binaryPropertyId, bool value)
    {
        std::uint64_t bit = static_cast<std::uint64_t>(1) << static_cast<std::uint64_t>(static_cast<std::uint8_t>(binaryPropertyId));
        if (value)
        {
            binaryProperties = binaryProperties | bit;
        }
        else
        {
            binaryProperties = binaryProperties & ~bit;
        }
    }
    inline GeneralCategoryId GetGeneralCategory() const
    {
        return generalCategory;
    }
    inline bool HasGeneralCategory(GeneralCategoryId generalCategory_) const
    {
        return (generalCategory & generalCategory_) != GeneralCategoryId::none;
    }
    inline void SetGeneralCategory(GeneralCategoryId generalCategory_)
    {
        generalCategory = generalCategory_;
    }
    inline char32_t Upper() const
    {
        return upper;
    }
    inline void SetUpper(char32_t upper_)
    {
        upper = upper_;
    }
    inline char32_t Lower() const
    {
        return lower;
    }
    inline void SetLower(char32_t lower_)
    {
        lower = lower_;
    }
    inline char32_t Title() const
    {
        return title;
    }
    inline void SetTitle(char32_t title_)
    {
        title = title_;
    }
    inline char32_t Folding() const
    {
        return folding;
    }
    inline void SetFolding(char32_t folding_)
    {
        folding = folding_;
    }
    inline BlockId GetBlock() const
    {
        return block;
    }
    inline void SetBlock(BlockId block_)
    {
        block = block_;
    }
    inline AgeId GetAge() const
    {
        return age;
    }
    inline void SetAge(AgeId age_)
    {
        age = age_;
    }
    inline ScriptId GetScript() const
    {
        return script;
    }
    inline void SetScript(ScriptId script_)
    {
        script = script_;
    }
    std::expected<bool, int> Write(BinaryStreamWriter& writer);
    std::expected<bool, int> Read(BinaryStreamReader& reader);
private:
    std::uint64_t binaryProperties;
    GeneralCategoryId generalCategory;
    char32_t upper;
    char32_t lower;
    char32_t title;
    char32_t folding;
    BlockId block;
    AgeId age;
    ScriptId script;
};

constexpr int numInfosInPage = 128;
constexpr size_t characterInfoSize = sizeof(std::uint64_t) + sizeof(BlockId) + sizeof(GeneralCategoryId) + sizeof(AgeId) + sizeof(std::uint32_t) + sizeof(std::uint32_t) + sizeof(std::uint32_t) +
sizeof(std::uint32_t) + sizeof(ScriptId);
constexpr size_t characterInfoPageSize = numInfosInPage * characterInfoSize;

enum class NumericTypeId : std::uint8_t
{
    none = 0,
    de, di, nu
};

class NumericType
{
public:
    NumericType(NumericTypeId id_, const std::string& shortName_, const std::string& longName_);
    inline NumericTypeId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
private:
    NumericTypeId id;
    std::string shortName;
    std::string longName;
};

class NumericTypeTable
{
public:
    static NumericTypeTable& Instance();
    std::expected<const NumericType*, int> GetNumericType(NumericTypeId id) const;
    std::expected<const NumericType*, int> GetNumericTypeByShortName(const std::string& shortName) const;
    std::expected<const NumericType*, int> GetNumericTypeByLongName(const std::string& longName) const;
    inline const std::vector<NumericType>& NumericTypes() const { return numericTypes; }
private:
    NumericTypeTable();
    std::vector<NumericType> numericTypes;
    std::map<NumericTypeId, const NumericType*> numericTypeMap;
    std::map<std::string, const NumericType*> shortNameMap;
    std::map<std::string, const NumericType*> longNameMap;
};

inline std::expected<const NumericType*, int> GetNumericType(NumericTypeId id)
{
    return NumericTypeTable::Instance().GetNumericType(id);
}

inline std::expected<const NumericType*, int> GetNumericTypeByShortName(const std::string& shortName)
{
    return NumericTypeTable::Instance().GetNumericTypeByShortName(shortName);
}

inline std::expected<const NumericType*, int> GetNumericTypeByLongName(const std::string& longName)
{
    return NumericTypeTable::Instance().GetNumericTypeByLongName(longName);
}

enum class BidiClassId : std::uint8_t
{
    none = 0,
    al, an, b, bn, cs, en, es, et, fsi, l, lre, lri, lro, nsm, on, pdf, pdi, r, rle, rli, rlo, s, ws
};

class BidiClass
{
public:
    BidiClass(BidiClassId id_, const std::string& shortName_, const std::string& longName_);
    inline BidiClassId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
private:
    BidiClassId id;
    std::string shortName;
    std::string longName;
};

class BidiClassTable
{
public:
    static BidiClassTable& Instance();
    std::expected<const BidiClass*, int> GetBidiClass(BidiClassId id) const;
    std::expected<const BidiClass*, int> GetBidiClassByShortName(const std::string& shortName) const;
    std::expected<const BidiClass*, int> GetBidiClassByLongName(const std::string& longName) const;
    inline const std::vector<BidiClass>& BidiClasses() const { return bidiClasses; }
private:
    BidiClassTable();
    std::vector<BidiClass> bidiClasses;
    std::map<BidiClassId, const BidiClass*> bidiClassMap;
    std::map<std::string, const BidiClass*> shortNameMap;
    std::map<std::string, const BidiClass*> longNameMap;
};

inline std::expected<const BidiClass*, int> GetBidiClass(BidiClassId id)
{
    return BidiClassTable::Instance().GetBidiClass(id);
}

inline std::expected<const BidiClass*, int> GetBidiClassByShortName(const std::string& shortName)
{
    return BidiClassTable::Instance().GetBidiClassByShortName(shortName);
}

inline std::expected<const BidiClass*, int> GetBidiClassByLongName(const std::string& longtName)
{
    return BidiClassTable::Instance().GetBidiClassByLongName(longtName);
}

enum class BidiPairedBracketTypeId : std::uint8_t
{
    none = 0,
    o, c
};

class BidiPairedBracketType
{
public:
    BidiPairedBracketType(BidiPairedBracketTypeId id_, const std::string& shortName_, const std::string& longName_);
    inline BidiPairedBracketTypeId Id() const { return id; }
    inline const std::string& ShortName() const { return shortName; }
    inline const std::string& LongName() const { return longName; }
private:
    BidiPairedBracketTypeId id;
    std::string shortName;
    std::string longName;
};

class BidiPairedBracketTypeTable
{
public:
    static BidiPairedBracketTypeTable& Instance();
    std::expected<const BidiPairedBracketType*, int> GetBidiPairedBracketType(BidiPairedBracketTypeId id) const;
    std::expected<const BidiPairedBracketType*, int> GetBidiPairedBracketTypeByShortName(const std::string& shortName) const;
    std::expected<const BidiPairedBracketType*, int> GetBidiPairedBracketTypeByLongName(const std::string& longName) const;
    inline const std::vector<BidiPairedBracketType>& BidiPairedBracketTypes() const { return bidiPairedBracketTypes; }
private:
    BidiPairedBracketTypeTable();
    std::vector<BidiPairedBracketType> bidiPairedBracketTypes;
    std::map<BidiPairedBracketTypeId, const BidiPairedBracketType*> typeMap;
    std::map<std::string, const BidiPairedBracketType*> shortNameMap;
    std::map<std::string, const BidiPairedBracketType*> longNameMap;
};

inline std::expected<const BidiPairedBracketType*, int> GetBidiPairedBracketType(BidiPairedBracketTypeId id)
{
    return BidiPairedBracketTypeTable::Instance().GetBidiPairedBracketType(id);
}

inline std::expected<const BidiPairedBracketType*, int> GetBidiPairedBracketTypeByShortName(const std::string& shortName)
{
    return BidiPairedBracketTypeTable::Instance().GetBidiPairedBracketTypeByShortName(shortName);
}

inline std::expected<const BidiPairedBracketType*, int> GetBidiPairedBracketTypeByLongName(const std::string& longName)
{
    return BidiPairedBracketTypeTable::Instance().GetBidiPairedBracketTypeByLongName(longName);
}

enum class AliasTypeId : std::uint8_t
{
    none = 0,
    correction, control, alternate, figment, abbreviation
};

class AliasType
{
public:
    AliasType(AliasTypeId id_, const std::string& name_);
    inline AliasTypeId Id() const { return id; }
    inline const std::string& Name() const { return name; }
private:
    AliasTypeId id;
    std::string name;
};

class AliasTypeTable
{
public:
    static AliasTypeTable& Instance();
    std::expected<const AliasType*, int> GetAliasType(AliasTypeId id) const;
    std::expected<const AliasType*, int> GetAliasType(const std::string& typeName) const;
    inline const std::vector<AliasType>& AliasTypes() const { return aliasTypes; }
private:
    AliasTypeTable();
    std::vector<AliasType> aliasTypes;
    std::map<AliasTypeId, const AliasType*> aliasTypeMap;
    std::map<std::string, const AliasType*> typeNameMap;
};

inline std::expected<const AliasType*, int> GetAliasType(AliasTypeId id)
{
    return AliasTypeTable::Instance().GetAliasType(id);
}

inline std::expected<const AliasType*, int> GetAliasType(const std::string& typeName)
{
    return AliasTypeTable::Instance().GetAliasType(typeName);
}

class Alias
{
public:
    Alias();
    Alias(AliasTypeId typeId_, const std::string& name_);
    inline AliasTypeId TypeId() const { return typeId; }
    inline const std::string& Name() const { return name; }
    std::expected<bool, int> Write(BinaryStreamWriter& writer);
    std::expected<bool, int> Read(BinaryStreamReader& reader);
private:
    AliasTypeId typeId;
    std::string name;
};

class ExtendedCharacterInfo
{
public:
    ExtendedCharacterInfo();
    inline const std::string& CharacterName() const
    {
        return characterName;
    }
    void SetCharacterName(const std::string& characterName_);
    inline const std::string& Unicode1Name() const
    {
        return unicode1Name;
    }
    void SetUnicode1Name(const std::string& unicode1Name_);
    inline std::uint8_t GetCanonicalCombiningClass() const
    {
        return canonicalCombiningClass;
    }
    inline void SetCanonicalCombiningClass(std::uint8_t canonicalCombiningClass_)
    {
        canonicalCombiningClass = canonicalCombiningClass_;
    }
    inline const std::u32string& FullUpper() const
    {
        return fullUpper;
    }
    inline std::u32string& FullUpper()
    {
        return fullUpper;
    }
    inline const std::u32string& FullLower() const
    {
        return fullLower;
    }
    inline std::u32string& FullLower()
    {
        return fullLower;
    }
    inline const std::u32string& FullTitle() const
    {
        return fullTitle;
    }
    inline std::u32string& FullTitle()
    {
        return fullTitle;
    }
    inline const std::u32string& FullFolding() const
    {
        return fullFolding;
    }
    inline std::u32string& FullFolding()
    {
        return fullFolding;
    }
    inline BidiClassId GetBidiClass() const
    {
        return bidiClass;
    }
    inline void SetBidiClass(BidiClassId bidiClass_)
    {
        bidiClass = bidiClass_;
    }
    inline NumericTypeId GetNumericType() const
    {
        return numericType;
    }
    inline void SetNumericType(NumericTypeId numericType_)
    {
        numericType = numericType_;
    }
    inline const std::string& GetNumericValue() const
    {
        return numericValue;
    }
    inline void SetNumericValue(const std::string& numericValue_)
    {
        numericValue = numericValue_;
    }
    inline const std::vector<Alias>& Aliases() const
    {
        return aliases;
    }
    inline std::vector<Alias>& Aliases()
    {
        return aliases;
    }
    inline char32_t GetBidiMirroringGlyph() const
    {
        return bidiMirroringGlyph;
    }
    inline void SetBidiMirroringGlyph(char32_t bidiMirroringGlyph_)
    {
        bidiMirroringGlyph = bidiMirroringGlyph_;
    }
    inline BidiPairedBracketTypeId GetBidiPairedBracketType() const
    {
        return bidiPairedBracketType;
    }
    inline void SetBidiPairedBracketType(BidiPairedBracketTypeId bidiPairedBracketType_)
    {
        bidiPairedBracketType = bidiPairedBracketType_;
    }
    inline char32_t GetBidiPairedBracket() const
    {
        return bidiPairedBracket;
    }
    inline void SetBidiPairedBracket(char32_t bidiPairedBracket_)
    {
        bidiPairedBracket = bidiPairedBracket_;
    }
    std::expected<bool, int> Write(BinaryStreamWriter& writer);
    std::expected<bool, int> Read(BinaryStreamReader& reader);
private:
    std::string characterName;
    std::string unicode1Name;
    std::uint8_t canonicalCombiningClass;
    std::u32string fullUpper;
    std::u32string fullLower;
    std::u32string fullTitle;
    std::u32string fullFolding;
    BidiClassId bidiClass;
    NumericTypeId numericType;
    std::string numericValue;
    std::vector<Alias> aliases;
    char32_t bidiMirroringGlyph;
    BidiPairedBracketTypeId bidiPairedBracketType;
    char32_t bidiPairedBracket;
};

class CharacterInfoPage
{
public:
    CharacterInfoPage();
    CharacterInfoPage(const CharacterInfoPage&) = delete;
    CharacterInfoPage& operator=(const CharacterInfoPage&) = delete;
    std::expected<const CharacterInfo*, int> GetCharacterInfo(int index) const;
    std::expected<CharacterInfo*, int> GetCharacterInfo(int index);
    std::expected<bool, int> Write(BinaryStreamWriter& writer);
    std::expected<bool, int> Read(BinaryStreamReader& reader);
private:
    std::vector<CharacterInfo> characterInfos;
};

class ExtendedCharacterInfoPage
{
public:
    ExtendedCharacterInfoPage();
    ExtendedCharacterInfoPage(const ExtendedCharacterInfoPage&) = delete;
    ExtendedCharacterInfoPage& operator=(const ExtendedCharacterInfoPage&) = delete;
    std::expected<const ExtendedCharacterInfo*, int> GetExtendedCharacterInfo(int index) const;
    std::expected<ExtendedCharacterInfo*, int> GetExtendedCharacterInfo(int index);
    std::expected<bool, int> Write(BinaryStreamWriter& writer);
    std::expected<bool, int> Read(BinaryStreamReader& reader);
private:
    std::vector<ExtendedCharacterInfo> extendedCharacterInfos;
};

class ExtendedCharacterInfoHeader
{
public:
    void AllocatePages(int numExtendedPages);
    std::expected<bool, int> Write(BinaryStreamWriter& writer);
    std::expected<bool, int> Read(BinaryStreamReader& reader);
    std::expected<std::uint32_t, int> GetPageStart(int pageIndex) const;
    std::expected<bool, int> SetPageStart(int pageIndex, std::uint32_t extendedPageStart);
private:
    std::vector<std::uint32_t> extendedPageStarts;
};

const int soul_ucd_version_1 = 1;
const int soul_ucd_version_2 = 2;
const int soul_ucd_version_3 = 3;
const int soul_ucd_version_4 = 4;
const int current_soul_ucd_version = soul_ucd_version_4;

enum class CharacterTableDataSource
{
    file, memory
};

class CharacterTable
{
public:
    CharacterTable(const CharacterTable&) = delete;
    CharacterTable& operator=(const CharacterTable&) = delete;
    static CharacterTable& Instance();
    std::expected<std::string, int> FilePath() const;
    std::expected<std::string, int> DeflateFilePath() const;
    std::expected<std::int64_t, int> GetUncompressedFileSize() const;
    std::expected<const CharacterInfo*, int> GetCharacterInfo(char32_t codePoint) const;
    std::expected<CharacterInfo*, int> CreateCharacterInfo(char32_t codePoint);
    std::expected<const ExtendedCharacterInfo*, int> GetExtendedCharacterInfo(char32_t codePoint) const;
    std::expected<ExtendedCharacterInfo*, int> CreateExtendedCharacterInfo(char32_t codePoint);
    std::expected<bool, int> Write();
    std::expected<bool, int> WriteDeflate();
    void SetData(std::uint8_t* data_, std::int64_t size_);
    void SetDeflateData(std::uint8_t* deflateData, std::int64_t deflateSize, std::int64_t uncompressedSize);
private:
    CharacterTable();
    std::expected<Streams, int> GetReadStreams();
    std::expected<bool, int> WriteHeader(BinaryStreamWriter& writer);
    std::expected<bool, int> ReadHeader(BinaryStreamReader& reader);
    std::expected<bool, int> ReadExtendedHeader(BinaryStreamReader& reader);
    CharacterTableDataSource dataSource;
    std::uint8_t* data;
    std::int64_t size;
    std::vector<std::uint8_t> memory;
    bool headerRead;
    std::vector<std::unique_ptr<CharacterInfoPage>> pages;
    std::uint32_t extendedHeaderStart;
    std::uint32_t extendedHeaderEnd;
    bool extendedHeaderRead;
    ExtendedCharacterInfoHeader extendedHeader;
    std::vector<std::unique_ptr<ExtendedCharacterInfoPage>> extendedPages;
    size_t headerSize;
};

inline std::expected<const CharacterInfo*, int> GetCharacterInfo(char32_t codePoint) { return CharacterTable::Instance().GetCharacterInfo(codePoint); }
inline std::expected<CharacterInfo*, int> CreateCharacterInfo(char32_t codePoint) { return CharacterTable::Instance().CreateCharacterInfo(codePoint); }
inline std::expected<const ExtendedCharacterInfo*, int> GetExtendedCharacterInfo(char32_t codePoint)
{ 
    const CharacterTable* table = &CharacterTable::Instance();
    return table->GetExtendedCharacterInfo(codePoint);
}
inline std::expected<ExtendedCharacterInfo*, int> CreateExtendedCharacterInfo(char32_t codePoint) { return CharacterTable::Instance().CreateExtendedCharacterInfo(codePoint); }

std::expected<GeneralCategoryId, int> GetGeneralCategory(char32_t c);
std::expected<bool, int> HasGeneralCategory(char32_t c, GeneralCategoryId generalCategory);
std::expected<bool, int> IsUpperLetter(char32_t c);
std::expected<bool, int> IsLowerLetter(char32_t c);
std::expected<bool, int> IsTitleLetter(char32_t c);
std::expected<bool, int> IsModifierLetter(char32_t c);
std::expected<bool, int> IsOtherLetter(char32_t c);
inline std::expected<bool, int> IsCasedLetter(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::LC);
}
inline std::expected<bool, int> IsLetter(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::L);
}
std::expected<bool, int> IsNonspacingMark(char32_t c);
std::expected<bool, int> IsSpacingMark(char32_t c);
std::expected<bool, int> IsEnclosingMark(char32_t c);
inline std::expected<bool, int> IsMark(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::M);
}
std::expected<bool, int> IsDecimalNumber(char32_t c);
std::expected<bool, int> IsLetterNumber(char32_t c);
std::expected<bool, int> IsOtherNumber(char32_t c);
inline std::expected<bool, int> IsNumber(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::N);
}
std::expected<bool, int> IsConnectorPunctuation(char32_t c);
std::expected<bool, int> IsDashPunctuation(char32_t c);
std::expected<bool, int> IsOpenPunctuation(char32_t c);
std::expected<bool, int> IsClosePunctuation(char32_t c);
std::expected<bool, int> IsInitialPunctuation(char32_t c);
std::expected<bool, int> IsFinalPunctuation(char32_t c);
std::expected<bool, int> IsOtherPunctuation(char32_t c);
inline std::expected<bool, int> IsPunctuation(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::P);
}
std::expected<bool, int> IsMathSymbol(char32_t c);
std::expected<bool, int> IsCurrencySymbol(char32_t c);
std::expected<bool, int> IsModifierSymbol(char32_t c);
std::expected<bool, int> IsOtherSymbol(char32_t c);
inline std::expected<bool, int> IsSymbol(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::S);
}
std::expected<bool, int> IsSpaceSeparator(char32_t c);
std::expected<bool, int> IsLineSeparator(char32_t c);
std::expected<bool, int> IsParagraphSeparator(char32_t c);
inline std::expected<bool, int> IsSeparator(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::Z);
}
std::expected<bool, int> IsControl(char32_t c);
std::expected<bool, int> IsFormat(char32_t c);
std::expected<bool, int> IsSurrogate(char32_t c);
std::expected<bool, int> IsPrivateUse(char32_t c);
std::expected<bool, int> IsUnassigned(char32_t c);
inline std::expected<bool, int> IsOther(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::C);
}
inline std::expected<bool, int> IsGraphic(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::G);
}
inline std::expected<bool, int> IsBase(char32_t c)
{
    return HasGeneralCategory(c, GeneralCategoryId::B);
}
inline std::expected<bool, int> IsCombining(char32_t c)
{
    return IsMark(c);
}
std::expected<char32_t, int> ToUpper(char32_t c);
std::expected<char32_t, int> ToLower(char32_t c);
std::expected<char32_t, int> ToTitle(char32_t c);
std::expected<char32_t, int> ToFolding(char32_t c);
std::expected<std::u32string, int> FullUpper(char32_t c);
std::expected<std::u32string, int> FullLower(char32_t c);
std::expected<std::u32string, int> FullTitle(char32_t c);
std::expected<std::u32string, int> FullFolding(char32_t c);
std::expected<bool, int> IsWhiteSpace(char32_t c);
std::expected<bool, int> IsAlphabetic(char32_t c);
std::expected<bool, int> IsAsciiHexDigit(char32_t c);
bool IsAsciiDigit(char32_t c);
std::expected<bool, int> IsUppercase(char32_t c);
std::expected<bool, int> IsLowercase(char32_t c);
std::expected<bool, int> IsIdStart(char32_t c);
std::expected<bool, int> IsIdCont(char32_t c);
std::expected<bool, int> IsGraphemeBase(char32_t c);
std::expected<bool, int> IsGraphemeExtender(char32_t c);
std::expected<bool, int> IsOtherLower(char32_t c);
std::expected<bool, int> IsOtherUpper(char32_t c);
std::expected<std::string, int> GetCharacterName(char32_t c);
std::expected<std::string, int> GetUnicode1Name(char32_t c);
std::expected<NumericTypeId, int> GetNumericType(char32_t c);
std::expected<std::string, int> GetNumericValue(char32_t c);
std::expected<bool, int> IsBidiMirrored(char32_t c);
std::expected<bool, int> IsBidiControl(char32_t c);
std::expected<char32_t, int> GetBidiMirroringGlyph(char32_t c);
std::expected<BidiPairedBracketTypeId, int> GetBidiPairedBracketType(char32_t c);
std::expected<char32_t, int> GetBidiPairedBracket(char32_t c);
std::expected<std::vector<Alias>, int> Aliases(char32_t c);

} // util
