import std.core;
import test_cls;
import util;

int main()
{
    try
    {
        util::Init();
        ns::cls c;
        c.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\class.xml)");
        ns::cls d;
        d.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\class.xml)");
        ns::cls e;
        e.b0 = true;
        e.sb1 = -1;
        e.b2 = 10;
        e.s3 = 100;
        e.us4 = 1000;
        e.i5 = -100;
        e.ui6 = 0;
        e.l7 = 0;
        e.ul8 = 100000000000000000;
        e.f9 = -123.456f;
        e.d10 = 1234.5678;
        e.c11 = 'X';
        e.wc12 = 'Y';
        e.uc13 = 'Z';
        e.u14 = util::random_uuid();
        e.s15 = "Hello!";
        e.ws16 = u"Qwerty";
        e.us17 = U"FooBar";
        e.d18 = util::GetCurrentDate();
        e.d19 = util::GetCurrentDateTime();
        e.tp20 = std::chrono::steady_clock::now();
        e.du21 = std::chrono::steady_clock::now() - e.tp20;
        e.en22 = ns::enm::third;
        e.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\class_2.xml)");
        ns::cls f;
        f.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\class_2.xml)");
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}
