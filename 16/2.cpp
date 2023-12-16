#include <iostream>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <memory>
#include <algorithm>


using point_t = std::pair< int, int >;
using beam_t = std::pair< point_t, int >;


int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	std::vector< std::string > const field{ std::istream_iterator< std::string >( ifs ), std::istream_iterator< std::string >() };

	auto calc_nrg = [ &field ]( beam_t const b0 ) -> int
	{
		std::set< beam_t > done;
		std::list< beam_t > front;
		front.push_back( b0 );

		while( !front.empty() )
		{
			beam_t b{ front.front() };
			front.pop_front();

			switch( b.second )
			{
				case 0: ++b.first.first; break;
				case 1: ++b.first.second; break;
				case 2: --b.first.first; break;
				case 3: --b.first.second; break;
				default: break;
			}
			if( b.first.first < 0 )
				continue;
			if( b.first.second < 0 )
				continue;
			if( b.first.first == field.size() )
				continue;
			if( b.first.second == field.front().size() )
				continue;
		
			if( !done.insert( b ).second )
				continue;

			char const p{ field[ b.first.second ][ b.first.first ] };

			if( p == '/' )
			{
				constexpr int bb[ 4 ]{ 3, 2, 1, 0 };
				b.second = bb[ b.second ];
			}
			else if( p == '\\' )
			{
				constexpr int bb[ 4 ]{ 1, 0, 3, 2 };
				b.second = bb[ b.second ];
			}
			else if( ( ( p == '|' ) && ( ( b.second % 2 ) == 0 ) )
				|| ( ( p == '-' ) && ( ( b.second % 2 ) == 1 ) ) )
			{
				front.emplace_back( b.first, ( b.second + 1 ) % 4 );
				front.emplace_back( b.first, ( b.second + 3 ) % 4 );
				continue;
			}
			front.push_back( b );
		}
	
		std::set< point_t > nrg;
		std::for_each( done.begin(), done.end(),
			[ &nrg ]( auto const & b )
			{
				nrg.insert( b.first );
			}
		);
	
		return nrg.size();
	};

	size_t mnrg{ 0 };
	for( int i{ 0 }; i != field.size(); ++i )
	{
		int const na{ calc_nrg( { { -1, i }, 0 } ) };
		if( mnrg < na )
			mnrg = na;

		int const nb{ calc_nrg( { { field.front().size(), i }, 2 } ) };
		if( mnrg < nb )
			mnrg = nb;
	}
	for( int i{ 0 }; i != field.front().size(); ++i )
	{
		int const na{ calc_nrg( { { i, -1 }, 1 } ) };
		if( mnrg < na )
			mnrg = na;

		int const nb{ calc_nrg( { { field.size(), i }, 3 } ) };
		if( mnrg < nb )
			mnrg = nb;
	}

	std::cout << "result = " << mnrg << std::endl;

	return 0;
}
