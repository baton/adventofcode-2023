#

use strict;

my $sum = 0;
while( <> )
{
	chomp;
	my @a = split ' ';
	my @x = ( $a[ 0 ] );
	while( scalar( grep { $_ != 0 } @a ) != 0 )
	{
		my @b = ();
		for( my $i = 0; $i != $#a; ++$i )
		{
			push @b, $a[ $i + 1 ] - $a[ $i ];
		}
		@a = @b;
		push @x, $a[ 0 ];
	}
	my $s = pop @x;
	$s = ( pop @x ) - $s while( @x );
	$sum += $s;
}

print "result = $sum\n";