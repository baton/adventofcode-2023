#include <iostream>
#include <fstream>
#include <iterator>
#include <numeric>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>


using box_t = std::vector< std::pair< std::string, uint64_t > >;
using boxes_t = std::map< uint64_t, box_t >;


uint64_t hash( std::string const & s )
{
	return std::accumulate(
		s.begin(), s.end(),
		0ULL,
		[]( uint64_t const x, char const c ) -> uint64_t
		{
			return ( ( x + c ) * 17 ) % 256;
		}
	);
}

box_t::iterator find( box_t & box, std::string const & s )
{
	return std::find_if( box.begin(), box.end(),
		[ &s ]( box_t::value_type const & v ) -> bool
		{
			return v.first == s;
		}
	);
}


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	boxes_t boxes;
	for( std::string s; std::getline( ifs, s, ',' ); )
	{
		if( s.back() == '-' )
		{
			s.pop_back();
			boxes_t::iterator i{ boxes.find( hash( s ) ) };
			if( i != boxes.end() )
			{
				box_t & box{ i->second };

				box_t::iterator j{ find( box, s ) };
				if( j != box.end() )
					box.erase( j );

				if( box.empty() )
					boxes.erase( i );
			}
		}
		else
		{
			size_t p{ s.find( '=' ) };
			uint64_t const v{ std::stoull( s.substr( p + 1 ) ) };
			s.resize( p );

			box_t & box{ boxes[ hash( s ) ] };
			box_t::iterator j{ find( box, s ) };
			if( j != box.end() )
				j->second = v;
			else
				box.emplace_back( s, v );
		}
	}

	uint64_t const sum{
		std::transform_reduce(
			boxes.begin(), boxes.end(),
			0ULL,
			std::plus(),
			[]( auto const & box ) -> uint64_t
			{
				uint64_t s{ 0 };
				for( uint64_t i{ 0 }; i != box.second.size(); ++i )
					s += ( 1 + box.first ) * ( i + 1 ) * box.second[ i ].second;
				return s;
			}
		)
	};

	std::cout << "result = " << sum << std::endl;

	return 0;
}
