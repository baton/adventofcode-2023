#

use strict;

my %hands = ();
while( <> )
{
	chomp;
	my( $h, $s ) = split '\s+';
	$hands{ $h } = $s;
}

my $sum = 0;
my $r = 1;
$sum += $r++ * $hands{ $_ } foreach( sort handcmp keys %hands );

print "result = $sum\n";

sub handcmp
{
	my @aa = split '', $a;
	my @bb = split '', $b;

	my @ia = map { index( "J23456789TQKA", $_ ) } @aa;
	my @ib = map { index( "J23456789TQKA", $_ ) } @bb;

	my %ta = ();
	++$ta{ $_ } foreach( @aa );
	my @va = sort values %ta;
	my $tas = keys %ta;
	if( ( $tas != 1 ) && exists $ta{ 'J' } )
	{
		my $j = $ta{ 'J' };
		delete $ta{ 'J' };
		@va = sort values %ta;
		$tas = keys %ta;
		$va[ $#va ] += $j;
	}

	my %tb = ();
	++$tb{ $_ } foreach( @bb );
	my $tbs = keys %tb;
	my @vb = sort values %tb;
	if( ( $tbs != 1 ) && exists $tb{ 'J' } )
	{
		my $j = $tb{ 'J' };
		delete $tb{ 'J' };
		@vb = sort values %tb;
		$tbs = keys %tb;
		$vb[ $#vb ] += $j;  
	}

	if( $tas != $tbs )
	{
		return $tbs <=> $tas;
	}

	if( $tas == 2 )
	{
		return $va[ 1 ] <=> $vb[ 1 ] if( $va[ 1 ] != $vb[ 1 ] );
	}

	if( $tas == 3 )
	{
		return $va[ 2 ] <=> $vb[ 2 ] if( $va[ 2 ] != $vb[ 2 ] );
	}

	for( my $i = 0; $i != $#ia+1; ++$i )
	{
		return $ia[ $i ] <=> $ib[ $i ] if( $ia[ $i ] != $ib[ $i ] );
	}

	return 0;
}
