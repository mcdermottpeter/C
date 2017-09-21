
#include	<stdio.h>
#include	<pthread.h>
#include	<errno.h>
#include	<string.h>
#include	<unistd.h>
#include	<time.h>
#include	<sys/time.h>
#include	<stdlib.h>
#include	<semaphore.h>
#include 	<locale.h>
#include	<signal.h>
#include	"function.h"
#include	"MinHeap.h"
#include	"MinHeap.c"

pthread_t 		pit1;
pthread_t 		pit2;
pthread_t 		pit3;
pthread_mutex_t lock;
MinHeap			minHeap;
sem_t 			sem_name;

static void
printHeap( MinHeap * minHeap )
{
	unsigned int	i, limit;
	char	*x;

	limit = minHeap->elemcount;
	printf( "[ " );
	for ( i = 0 ; i < limit ; i++ )
	{
		x = (char *)(minHeap->block + i * sizeof(char *));
		printf( "%s ", x );
	}
	printf( "]\n" );
}


static int
intCompare( const void * p1, const void * p2 )
{
	const char *		p01 = p1;
	const char *		p02 = p2;

	return strcmp(p01,p02);
}

void *ReaderT(void *now1)				//Thread 1 - Reader
{
	char *now;
	char *TIME;
	char timestamp[100];				   	//user timestamp
	char activity[100];						//user activity

	now = (char *)now1;

	while(printf("--->Enter Timestamp\n"),scanf("%s",timestamp))
	{
		char request[100];
		check(timestamp);
		printf("--->Enter activity to be performed at that time:\n");			//Entering Name of the activity
		scanf("%s",activity);

		sprintf(request,"%s %s",timestamp,activity);
		printf("--->Request of %s at %s added to the memory\n",timestamp,activity);
		addElement( &minHeap, &request );						//Adding element to the MinHeap
		//printHeap( &minHeap );									//Printing MinHeap
		TIME = (char *)getMin(&minHeap);						//Getting the MinHeap
	//	remainingtime(TIME,now);
	}
}

void *WorkerT(void *pit2)				//Thread 2 - Worker
{
int i = 0;
	while(1)
	{

	}
}

void *ClockT(void *now1)				//Thread 3 - Clock
{
	char *now;
	now = (char *)now1;
	while(1)
	{
		sleep(1);
		updatetime(now);
		//break;
	}
}

int main(int argc, char ** argv )
{
	char 		*now;
	int 		year,day,hour,min,sec;

	strcpy(now,argv[1]);
	//sscanf("%[^\n]",now);					//Ask Professor



	if ( argc > 2) 							//GREATER THAN 2 ARGUMENTS
		{
			fprintf(stderr,"\x1b[1;31mMust specify only 2 argument\nExiting........\x1b[0m\n");
			_exit( 1 );
		}
	else if (sscanf(now,"%d/%d/%d/%d/%d",&year,&day,&hour,&min,&sec) != 5  || year < 1000 || year > 9999 || day < 0 ||
											day > 365 || hour < 0 || hour > 23 ||min < 0 || min > 59 ||sec < 0 || sec > 59 ) 	//Error - If enter more than 5 numbers still give correct answer	//CHECKING IF THE ARGUMENT IS CORRECT OR NOT
		{
			fprintf(stderr,"\x1b[1;31mMust specify correct timestamp format\nExiting........\x1b[0m\n");
			exit(1);
		}
	else										//IF WORKING CORRECTLY THEN
		{
			pthread_mutex_init(&lock,NULL);							//Initializing Mutex
			sem_init(&sem_name,0,1);								//Initializing Semaphore
			initializeMinHeap( &minHeap, intCompare, 1000000); 		//Initialzing MinHeap
			pthread_create(&pit1, NULL, ReaderT,now );				//Initializing Thread 1 - Reader
			pthread_create(&pit2, NULL, WorkerT,NULL);				//Initializing Thread 2 - Worker
			pthread_create(&pit3, NULL, ClockT, now);				//Initializing Thread 3 - Clock
			pthread_join(pit1, NULL);
			pthread_join(pit2, NULL);
			pthread_join(pit3, NULL);
			pthread_exit(0);										//Exiting Threads
		}
	return 0;
}
