#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t r{ 0 };
	while( !ifs.eof() )
	{
		std::string s;
		std::getline( ifs, s );

		auto const is_digit = []( char const c ) -> bool
		{
			return std::isdigit( c );
		};

		r += ( ( *std::find_if( s.begin(), s.end(), is_digit ) ) - '0' ) * 10
			+ ( ( *std::find_if( s.rbegin(), s.rend(), is_digit ) ) - '0' );
	}

	std::cout << "result = " << r << std::endl;

	return 0;
}