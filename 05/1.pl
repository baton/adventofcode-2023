#

use strict;

my @a = (), my @b = ();
while( <> )
{
	chomp;
	if( m/^seeds: (.*)/ )
	{
		@a = split ' ', $1;
		next;
	}
	if( !m/^\d/ )
	{
		@b = @a;
		next;
	}

	my( $t, $s, $d ) = split ' ';

	for( my $i = 0; $i != $#b + 1; ++$i )
	{
		if( ( $b[ $i ] >= $s ) && ( $b[ $i ] < ( $s + $d ) ) )
		{
			$a[ $i ] = $b[ $i ] - $s + $t;
			$b[ $i ] = -1;
		}
	}
}

@a = sort{ $a <=> $b } @a;
print "result = " . ( shift @a ) . "\n";