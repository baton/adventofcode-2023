#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <string>
#include <list>
#include <map>
#include <memory>
#include <algorithm>


struct rule_t
{
	bool is_condition{ false };
	bool is_gt{ false };
	uint64_t cmp{ 0ULL };
	std::string in, out;
};
using workflow_t = std::list< rule_t >;
using workflows_t = std::map< std::string, workflow_t >;

using range_t = std::pair< uint64_t, uint64_t >;
using part_t = std::map< std::string, range_t >;

part_t xmas{
		{ "x", { 1ULL, 4000ULL } },
		{ "m", { 1ULL, 4000ULL } },
		{ "a", { 1ULL, 4000ULL } },
		{ "s", { 1ULL, 4000ULL } } };

int main( int argc, char * argv[] )
{
	if( argc < 2 )
		return 0;

	std::ifstream ifs( argv[ 1 ] );

	workflows_t workflows;
	for( std::string wfs; std::getline( ifs, wfs ) && !wfs.empty(); )
	{
		wfs.pop_back(); // '}'
		size_t const br{ wfs.find( '{' ) };

		workflow_t & wf{ workflows[ wfs.substr( 0, br ) ] };

		std::istringstream iss( wfs.substr( br + 1 ) );
		for( std::string s; std::getline( iss, s, ',' ); )
		{
			rule_t & r{ wf.emplace_back() };
			if( ( s.length() > 2 ) && ( ( s[ 1 ] == '>' ) || ( s[ 1 ] == '<' ) ) )
			{
				r.is_condition = true;
				r.in.push_back( s[ 0 ] );
				r.is_gt = ( s[ 1 ] == '>' );
				s = s.substr( 2 );
				size_t const sc{ s.find( ':' ) };
				r.cmp = std::stoi( s.substr( 0, sc ) );
				r.out = s.substr( sc + 1 );
			}
			else
			{
				r.out = s;
			}
		}
	}

	uint64_t sum{ 0ULL };

	std::list< std::pair< std::string, part_t > > front;
	front.emplace_back( "in", xmas );
	while( !front.empty() )
	{
		auto [ label, part ] = front.front();
		front.pop_front();

		if( label == "R" )
			continue;
		if( label == "A" )
		{
			uint64_t m{ 1 };
			for( auto const & [ k, v ] : part )
				m *= v.second - v.first + 1;
			sum += m;
			continue;
		}

		workflow_t const & w{ workflows[ label ] };
		for( rule_t const & r : w )
		{
			if( r.is_condition )
			{
				part_t a( part ), b( part );
				if( r.cmp < part[ r.in ].first )
					a[ r.in ] = { 0, 0 };
				else if( r.cmp > part[ r.in ].second )
					b[ r.in ] = { 0, 0 };
				else
				{
					if( r.is_gt )
					{
						a[ r.in ].second = r.cmp;
						b[ r.in ].first = r.cmp + 1;
					}
					else
					{
						a[ r.in ].second = r.cmp - 1;
						b[ r.in ].first = r.cmp;
					}
				}

				if( r.is_gt )
				{
					if( b[ r.in ].first != 0 )
						front.emplace_back( r.out, b );
					part = a;
				}
				else
				{
					if( a[ r.in ].first != 0 )
						front.emplace_back( r.out, a );
					part = b;
				}

				if( part[ r.in ].first == 0 )
					break;
			}
			else
			{
				front.emplace_back( r.out, part );
				break;
			}
		}
	}

	std::cout << "result = " << sum << std::endl;

	return 0;
}