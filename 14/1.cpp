#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>


using point_t = std::pair< int, int >;


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > rocks{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	for( int i{ 1 }; i != rocks.size(); ++i )
		for( int j{ 0 }; j != rocks[ i ].length(); ++j )
			if( rocks[ i ][ j ] == 'O' )
				for( int k{ i - 1 }; ( k != -1 ) && ( rocks[ k ][ j ] == '.' ); --k )
				{
					rocks[ k ][ j ] = 'O';
					rocks[ k + 1 ][ j ] = '.';
				}

	size_t sum{ 0 }, x{ 0 };
	for( std::string const & s : rocks )
		sum += x += std::count( s.begin(), s.end(), 'O' );

	std::cout << "result = " << sum << std::endl;

	return 0;
}