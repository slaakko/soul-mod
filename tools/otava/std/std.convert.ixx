export module std.convert;

import std.type.fundamental;
import std.string;
import std.algorithm;

export namespace std {

string to_string(int val);
string to_string(unsigned val);
string to_string(long val);
string to_string(unsigned long val);
string to_string(long long val);
string to_string(unsigned long long val);

} // namespace std
