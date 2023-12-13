#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	size_t sum{ 0 };
	while( !ifs.eof() )
	{
		std::vector< std::string > pattern;
		for( std::string s; std::getline( ifs, s ) && !s.empty(); )
			pattern.push_back( s );

		for( size_t x{ 1 }; x != pattern.size(); ++x )
		{
			bool m{ true };
			for( size_t i{ x }; m && ( i != pattern.size() ); ++i )
			{
				if( ( x - ( i - x ) ) < 1 )
					break;
				m &= pattern[ i ] == pattern[ x - ( i - x ) - 1 ];
			}

			if( m )
			{
				sum += x * 100;

				break;
			}
		}

		for( size_t n{ 1 }; n != pattern[ 0 ].size(); ++n )
		{
			bool m{ true };
			for( size_t i{ 0 }; m && ( i != pattern.size() ); ++i )
				for( size_t j{ n }; m && ( j != pattern[ i ].size() ); ++j )
				{
					if( ( n - ( j - n ) ) < 1 )
						break;
					m &= pattern[ i ][ j ] == pattern[ i ][ n - ( j - n ) - 1 ];
				}

			if( m )
			{
				sum += n;

				break;
			}
		}
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}