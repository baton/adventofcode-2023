#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


size_t matches( std::string s, std::vector< int > v )
{
	if( s.empty() )
		return v.empty() ? 1ULL : 0ULL;

	switch( s[ 0 ] )
	{
		case '.':
			return matches( s.substr( 1 ), v );

		case '#':
			if( v.empty() )
				return 0;

			if( s.length() < v[ 0 ] )
				return 0;

			for( int i( 0 ); i != v[ 0 ]; ++i )
				if( s[ i ] == '.' )
					return 0;

			s = s.substr( v[ 0 ] );
			v.erase( v.begin() );

			if( !s.empty() )
			{
				if( s[ 0 ] == '#' )
					return 0;
				if( s[ 0 ] == '?' )
					s[ 0 ] = '.';
			}

			return matches( s, v );

		case '?':
			size_t m{ 0 };
			s[ 0 ] = '.';
			m += matches( s, v );
			s[ 0 ] = '#';
			m += matches( s, v );
			return m;
	}

	return 0;
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	size_t sum{ 0 };
	while( !ifs.eof() )
	{
		std::string s;
		ifs >> s;

		std::vector< int > v;
		{
			std::string m;
			ifs >> m;

			std::istringstream ss( m );
			for( std::string t; std::getline( ss, t, ',' ); )
				v.push_back( std::stoi( t ) );
		}

		sum += matches( s, v );
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}