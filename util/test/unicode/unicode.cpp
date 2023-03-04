import std.core;
import util.unicode;

int main()
{
	std::string s = "öhkömömmö";
	std::cout << s << std::endl;
	std::string t = util::ToUpper(s);
	std::cout << t << std::endl;
	return 0;
}
