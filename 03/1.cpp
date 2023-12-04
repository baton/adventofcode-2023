#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>


bool is_symbol( int const x, int const y, std::vector< std::string > const & lines )
{
	if( ( x < 0 ) || ( y < 0 ) )
		return false;
	if( ( y == lines.size() ) || ( x == lines[ y ].size() ) )
		return false;

	char const c{ lines[ y ][ x ] };
	return ( c != '.' ) && !std::isdigit( c );
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const lines{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	size_t sum{ 0 };
	for( int y{ 0 }; y != lines.size(); ++y )
	{
		std::string const & s{ lines[ y ] };

		int x{ 0 };
		while( x != s.length() )
		{
			while( !std::isdigit( s[ x ] ) && ( x != s.length() ) )
				++x;

			if( x == s.length() )
				break;

			size_t n( s[ x ] - '0' );
			int const x0( x++ );
			while( std::isdigit( s[ x ] ) && ( x != s.length() ) )
				n = n * 10 + s[ x++ ] - '0';

			bool has_symbol{ false };
			for( int i( x0 - 1 ); i != x + 1; ++i )
				for( int j( y - 1 ); j != y + 2; ++j )
					has_symbol |= is_symbol( i, j, lines );

			if( has_symbol )
				sum += n;
		}
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}