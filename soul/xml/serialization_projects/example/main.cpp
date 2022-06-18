import std.core;
import example;
import util;

int main()
{
    try
    {
        util::Init();

        example::ns::Data data;
        data.name = "data";
        data.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\data_1.xml)");
        example::ns::Data data_read;
        data_read.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\data_1.xml)");

        example::ns::Derived derived;
        derived.name = "derived";
        derived.derivedStr = "derived_str";
        derived.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\derived_1.xml)");
        example::ns::Derived derived_read;
        derived_read.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\derived_1.xml)");

        example::ns::Foo empty_foo;
        empty_foo.name = "foo";
        empty_foo.contained.name = "contained";
        empty_foo.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\empty_foo.xml)");
        example::ns::Foo empty_foo_read;
        empty_foo_read.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\empty_foo.xml)");

        example::ns::Foo foo_1;
        foo_1.name = "foo_1";
        foo_1.contained.name = "foo_1.contained";
        example::ns::Data* d1(new example::ns::Data());
        d1->name = "d1";
        foo_1.data.reset(d1);
        foo_1.strings.push_back("foo_1.str.1");
        example::ns::Data* d2(new example::ns::Data());
        d2->name = "d2";
        foo_1.datas.push_back(std::unique_ptr<example::ns::Data>(d2));
        foo_1.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\foo_1.xml)");
        example::ns::Foo foo_1_read;
        foo_1_read.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\foo_1.xml)");

        example::ns::Foo foo_2;
        foo_2.name = "foo_2";
        foo_2.contained.name = "foo_2.contained";
        example::ns::Derived* foo_2_derived(new example::ns::Derived());
        foo_2_derived->name = "foo_2_derived";
        foo_2_derived->derivedStr = "foo_2.derived_str";
        foo_2.data.reset(foo_2_derived);
        foo_2.strings.push_back("foo_2.string_1");
        foo_2.strings.push_back("foo_2.string_2");
        example::ns::Data* foo_2_data(new example::ns::Data());
        foo_2_data->name = "foo_2_data";
        foo_2.datas.push_back(std::unique_ptr<example::ns::Data>(foo_2_data));
        example::ns::Derived* foo_2_derived_2(new example::ns::Derived());
        foo_2_derived_2->name = "foo_2_derived_2";
        foo_2_derived_2->derivedStr = "foo_2_derived_2.str";
        foo_2.datas.push_back(std::unique_ptr<example::ns::Data>(foo_2_derived_2));
        foo_2.WriteToXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\foo_2.xml)");
        example::ns::Foo foo_2_read;
        foo_1_read.ReadFromXmlFile(R"(C:\work\soul-mod\soul\xml\serialization_test_data\foo_2.xml)");
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    util::Done();
    return 0;
}