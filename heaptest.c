#include	"MinHeap.h"
#include	<stdio.h>
#include	<string.h>

static int
intCompare( const void * p1, const void * p2 )
{
	const int *		p01 = p1;
	const int *		p02 = p2;

	if ( *p01 == *p02 )	return 0;
	else if ( *p01 < *p02 )	return -1;
	else			return 1;
}

static void
printHeap( MinHeap * minHeap )
{
	unsigned int	i, limit;
	int		x;

	limit = minHeap->elemcount;
	printf( "[ " );
	for ( i = 0 ; i < limit ; i++ )
	{
		x = *((int *)(minHeap->block + i * sizeof(int)));
		printf( "%d ", x );
	}
	printf( "]\n" );
}

int
main()
{
	int		x;
	char		directive[20];
	MinHeap		minHeap;
	int *		p;

	initializeMinHeap( &minHeap, intCompare, sizeof(int) );
	while ( printf( "enter directive>" ), scanf( " %s", directive ) > 0 )
	{
		if ( strcmp( directive, "add" ) == 0 )
		{
			scanf( " %d", &x );
			addElement( &minHeap, &x );
			printHeap( &minHeap );
		}
		else if ( strcmp( directive, "rem" ) == 0 )
		{
			if ( removeMin( &minHeap, &x ) == 0 )
				printf( "MinHeap is empty\n" );
			else
				printf( "%d  ", x );
			printHeap( &minHeap );
		}
		else
		{
			printf( "\x1b[1;31mBogus directive: %s\x1b[0m\n", directive );
		}
	}
	printf( "Normal end.\n" );
}
