export module std.utilities.ratio;

import std.type.fundamental;

export namespace std {

template<int64_t N, int64_t D = 1>
class ratio
{
public:
	static constexpr int64_t num;
	static constexpr int64_t den;
	// using type = ratio<num, den>;
};

using yocto = ratio<1, 1'000'000'000'000'000'000'000'000>;
using zepto = ratio<1, 	   1'000'000'000'000'000'000'000>;
using atto = ratio<1, 	       1'000'000'000'000'000'000>;
using femto = ratio<1, 	       	   1'000'000'000'000'000>;
using pico = ratio<1, 	       	   	   1'000'000'000'000>;
using nano = ratio<1, 	       	   	       1'000'000'000>;
using micro = ratio<1, 	       	   	           1'000'000>;
using milli = ratio<1, 	       	   	               1'000>;
using centi = ratio<1, 	       	   	                 100>;
using deci = ratio<1, 	       	   	                  10>;
using deca = ratio< 	       	   	               10, 1>;
using hecto = ratio< 	       	   	              100, 1>;
using kilo = ratio< 	       	   	            1'000, 1>;
using mega = ratio< 	       	   	        1'000'000, 1>;
using giga = ratio< 	       	   	    1'000'000'000, 1>;
using tera = ratio< 	       	    1'000'000'000'000, 1>;
using peta = ratio< 	  	    1'000'000'000'000'000, 1>;
using exa = ratio< 	  	    1'000'000'000'000'000'000, 1>;
using zetta = ratio< 	1'000'000'000'000'000'000'000, 1>;
using yotta = ratio<1'000'000'000'000'000'000'000'000, 1>;

} // namespace std
