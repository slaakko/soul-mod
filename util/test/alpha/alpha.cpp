import std.core;
import util.unicode;

int main()
{
    std::string alpha = "alpha";
    std::u32string alphau32 = util::ToUtf32(alpha);
    return 0;
}
