#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>


std::string const digits[]{ "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
std::string const nums[]{ "1", "2", "3", "4", "5", "6", "7", "8", "9" };


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

		{
			std::string::const_iterator a{ std::find_if( s.begin(), s.end(), is_digit ) };
			uint64_t n{ 0 };
			for( size_t x{ 0 }; x != _countof( digits ); ++x )
			{	
				std::string const & d{ digits[ x ] };
				std::string::const_iterator i{ std::search( s.begin(), s.end(), d.begin(), d.end() ) };
				if( ( i != s.end() ) && ( i < a ) )
				{
					a = i;
					n = x + 1;
				}
			}
			r += ( is_digit( *a ) ? ( *a - '0' ) : n ) * 10;
		}

		{
			std::string::const_iterator a{ s.begin() };
			for( std::string const & n : nums )
			{
				std::string::const_iterator i{ std::find_end( s.begin(), s.end(), n.begin(), n.end() ) };
				if( ( i != s.end() ) && ( a < i ) )
					a = i;
			}
			uint64_t n{ 0 };
			for( size_t x{ 0 }; x != _countof( digits ); ++x )
			{	
				std::string const & d{ digits[ x ] };
				std::string::const_iterator i{ std::find_end( s.begin(), s.end(), d.begin(), d.end() ) };
				if( ( i != s.end() ) && ( a < i ) )
				{
					a = i;
					n = x + 1;
				}
			}
			r += ( is_digit( *a ) ? ( *a - '0' ) : n );
		}
	}

	std::cout << "result = " << r << std::endl;

	return 0;
}