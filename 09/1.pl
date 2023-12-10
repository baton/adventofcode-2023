#

use strict;

my $sum = 0;
while( <> )
{
	chomp;
	my @a = split ' ';
	while( scalar( grep { $_ != 0 } @a ) != 0 )
	{
		$sum += $a[ $#a ];
		my @b = ();
		for( my $i = 0; $i != $#a; ++$i )
		{
			push @b, $a[ $i + 1 ] - $a[ $i ];
		}
		@a = @b;
	}
}

print "result = $sum\n";