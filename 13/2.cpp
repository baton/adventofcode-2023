#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <memory>


std::vector< std::pair< bool, size_t > > find_reflections( std::vector< std::string > const & pattern )
{
	std::vector< std::pair< bool, size_t > > r;

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
			r.emplace_back( true, x );
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
			r.emplace_back( false, n );
	}

	return r;
}



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

		std::vector< std::pair< bool, size_t > > const reflections( find_reflections( pattern ) );

		bool found{ false };

		for( std::string & s : pattern )
		{
			for( char & c : s )
			{
				c = ( c == '#' ) ? '.' : '#';

				std::vector< std::pair< bool, size_t > > const rs( find_reflections( pattern ) );
				for( std::pair< bool, size_t > const & r : rs )
				{
					if( found = ( r != reflections.front() ) )
					{
						sum += ( r.first ? 100 : 1 ) * r.second;

						break;
					}
				}

				c = ( c == '#' ) ? '.' : '#';

				if( found )
					break;
			}

			if( found )
				break;
		}
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}