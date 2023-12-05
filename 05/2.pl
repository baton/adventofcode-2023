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
		foreach( @b )
		{
			push @a, $_ if defined $_;
		}
		@b = @a;
		@a = ();
		next;
	}

	my( $t, $s, $d ) = split ' ';

	for( my $i = 0; $i != $#b + 1; $i += 2 )
	{
		next if( !defined $b[ $i ] );
		next if( $b[ $i ] >= ( $s + $d ) );
		next if( ( $b[ $i ] + $b[ $i + 1 ] ) < $s );

		if( $b[ $i ] < $s )
		{
			push @a, $t;

			if( ( $b[ $i ] + $b[ $i + 1 ] ) <= ( $s + $d ) )
			{
				push @a, $b[ $i ] + $b[ $i + 1 ] - $s;
			}
			else
			{
				push @a, $d;

				push @b, ( ( $s + $d ), ( $b[ $i ] + $b[ $i + 1 ] ) - ( $s + $d ) );
			}

			$b[ $i + 1 ] = $s - $b[ $i ];
		}
		else
		{
			push @a, $b[ $i ] - $s + $t;

			if( ( $b[ $i ] + $b[ $i + 1 ] ) <= ( $s + $d ) )
			{
				push @a, $b[ $i + 1 ];

				undef $b[ $i ]; undef $b[ $i + 1 ];
			}
			else
			{
				push @a, ( $s + $d ) - $b[ $i ];

				$b[ $i + 1 ] = ( $b[ $i ] + $b[ $i + 1 ] ) - ( $s + $d );
				$b[ $i ] = $s + $d;
			}
		}
	}
}

foreach( @b )
{
	push @a, $_ if defined $_;
}
my $i = 0;
@a = grep { ++$i % 2 } @a;

print "result = " . min( @a ) . "\n";


sub min
{
	@_ = sort { $a <=> $b } @_;
	return shift;
}

sub max
{
	@_ = sort { $a <=> $b } @_;
	return pop;
}
