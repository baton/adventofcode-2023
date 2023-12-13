#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


uint64_t matches( std::string_view const & s, std::vector< int > const & v )
{
	std::vector< std::vector< uint64_t > > d( s.length() + 1, std::vector< uint64_t >( v.size() + 1, 0ULL ) );
	d[ 0 ][ 0 ] = 1;

	for( size_t i{ 0 }; i != s.length(); ++i )
	{
		for( size_t j{ 0 }; j != v.size(); ++j )
		{
			if( ( i + v[ j ] + 1 ) <= s.length() )
			{
				bool m{ true };
				for( size_t k{ 0 }; m && ( k != v[ j ] ); ++k )
					m &= s[ i + k ] != '.';
				m &= s[ i + v[ j ] ] != '#';

				if( m )
					d[ i + 1 + v[ j ] ][ j + 1 ] += d[ i ][ j ];
			}
		}

		if( s[ i ] != '#' )
		{
			for( size_t j{ 0 }; j != v.size() + 1; ++j )
				d[ i + 1 ][ j ] += d[ i ][ j ];
		}
	}

	return d[ s.length() ][ v.size() ];
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	uint64_t sum{ 0 };
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

		std::string s5( s );
		std::vector< int > v5( v );
		for( uint64_t i = 1; i != 5; ++i )
		{
			s5 += "?" + s;
			v5.insert( v5.end(), v.begin(), v.end() );
		}
		s5.push_back( '.' );

		sum += matches( s5, v5 );
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}