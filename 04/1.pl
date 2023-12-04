#

use strict;

my $sum = 0;
while( <> )
{
	chomp;
	s/^[^:]+:\s//;
	my( $a, $b ) = split ' \| ';
	my %n = map{ $_ => 1 } split ' ', $b;
	my $v = 0;
	foreach my $x ( split ' ', $a )
	{
		if( exists( $n{ $x } ) )
		{
			$v = !$v ? 1 : $v * 2;
		}
	}
	$sum += $v;
}

print "result = $sum\n";