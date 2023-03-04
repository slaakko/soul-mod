import std.core;
import std.filesystem;
import util.unicode;
import util.file.stream;
import util.binary.stream.writer;
import util.buffered.stream;

void write_test_file(util::BinaryStreamWriter& writer)
{
    bool x0 = false;
    writer.Write(x0);
    bool x1 = true;
    writer.Write(x1);
    uint8_t x3 = 0;
    writer.Write(x3);
    uint16_t x5 = 2;
    writer.Write(x5);
    int16_t x6 = -1;
    writer.Write(x6);
    uint32_t x7 = 3;
    writer.Write(x7);
    int32_t x8 = 4;
    writer.Write(x8);
    uint64_t x9 = 5;
    writer.Write(x9);
    int64_t x10 = 6;
    writer.Write(x10);
    char8_t x11 = '@';
    writer.Write(x11);
    char16_t x12 = 'a';
    writer.Write(x12);
    char32_t x13 = 'x';
    writer.Write(x13);
    std::string x14 = "alpha";
    writer.Write(x14);
    std::u16string x15 = util::ToUtf16("beta");
    writer.Write(x15);
    std::u32string x16 = util::ToUtf32("gamma");
    writer.Write(x16);
    uint32_t x17 = 7;
    writer.WriteULEB128UInt(x17);
    uint64_t x18 = 8;
    writer.WriteULEB128ULong(x18);
    int32_t x19 = 9;
    writer.WriteSLEB128Int(x19);
    int64_t x20 = 10;
    writer.WriteSLEB128Long(x20);
    util::uuid x21 = util::uuid::random();
    writer.Write(x21);
}

void Check(bool assert, int number)
{
    if (!assert)
    {
        std::string msg = "assertion ";
        msg.append(std::to_string(number));
        msg.append(" failed");
        throw std::runtime_error(msg);
    }
}

void read_test_file(util::BinaryStreamReader& reader)
{
    bool x0 = reader.ReadBool();
    Check(x0 == false, 0);
    bool x1 = reader.ReadBool();
    Check(x1 == true, 1);
    uint8_t x3 = reader.ReadByte();
    Check(x3 == 0, 3);
    uint16_t x5 = reader.ReadUShort();
    Check(x5 == 2, 5);
    int16_t x6 = reader.ReadShort();
    Check(x6 == -1, 6);
    uint32_t x7 = reader.ReadUInt();
    Check(x7 == 3, 7);
    int32_t x8 = reader.ReadInt(); 
    Check(x8 == 4, 8);
    uint64_t x9 = reader.ReadULong();
    Check(x9 == 5, 9);
    int64_t x10 = reader.ReadLong();
    Check(x10 == 6, 10);
    char8_t x11 = reader.ReadChar8();
    Check(x11 == '@', 11);
    char16_t x12 = reader.ReadWChar();
    Check(x12 == 'a', 12);
    char32_t x13 = reader.ReadUChar();
    Check(x13 == 'x', 13);
    std::string x14 = reader.ReadUtf8String();
    Check(x14 == "alpha", 14);
    std::u16string x15 = reader.ReadUtf16String();
    Check(x15 == util::ToUtf16("beta"), 15);
    std::u32string x16 = reader.ReadUtf32String();
    Check(x16 == util::ToUtf32("gamma"), 16);
    uint32_t x17 = reader.ReadULEB128UInt();
    Check(x17 == 7, 17);
    uint64_t x18 = reader.ReadULEB128ULong();
    Check(x18 == 8, 18);
    int32_t x19 = reader.ReadSLEB128Int();
    Check(x19 == 9, 19);
    int64_t x20 = reader.ReadSLEB128Long();
    Check(x20 == 10, 20);
    util::uuid x21;
    reader.ReadUuid(x21);
}

void write_test_file(const std::string& testFilePath)
{
    util::OpenMode mode = util::OpenMode::write | util::OpenMode::binary;
    util::FileStream outputFile(testFilePath, mode);
    util::BufferedStream outputFileBufStream(outputFile);
    util::BinaryStreamWriter writer(outputFileBufStream);
    write_test_file(writer);
}

void read_test_file(const std::string& testFilePath)
{
    util::OpenMode mode = util::OpenMode::read | util::OpenMode::binary;
    util::FileStream inputFile(testFilePath, mode);
    util::BufferedStream inputFileBufStream(inputFile);
    util::BinaryStreamReader reader(inputFileBufStream);
    read_test_file(reader);
}

int main()
{
    try
    {
        std::filesystem::path f = util::SoulRoot();
        f /= "util";
        f /= "test";
        f /= "binary_stream_reader_writer";
        f /= "test.bin";
        std::string filePath = f.generic_string();
        std::cout << "==> " << filePath << "\n";
        write_test_file(filePath);
        read_test_file(filePath);
        std::cout << "success" << "\n";
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
