#include	<stdio.h>
#include	<errno.h>
#include	<string.h>
#include	<unistd.h>
#include	<time.h>
#include	<stdlib.h>
#include	<sys/time.h>
#include	"MinHeap.h"


sem_t 			sem_name;



void remainingtime(char *TIME,char *now)
{
	char 		remT[100]; //remaining  time
	int 		year,day,hour,min,sec;
	int 		year1,day1,hour1,min1,sec1;
	int 		year2,day2,hour2,min2,sec2;

	if(sscanf(TIME,"%d/%d/%d/%d/%d",&year1,&day1,&hour1,&min1,&sec1) == 5 && sscanf(now,"%d/%d/%d/%d/%d",&year2,&day2,&hour2,&min2,&sec2)==5)
	{
		year  	= year1 - year2;if(year < 0){printf("Error Entered past value\n");}
		day 	= day1-day2;hour 	= hour1 - hour2;min 	= min1 	- min2;sec 	= sec1 	- sec2;
		sprintf(remT,"%d/%d/%d/%d/%d",year,day,hour,min,sec);

		printf("%s\n", remT);

	}
}
void updatetime(char *now)
{
	int 		year,day,hour,min,sec;
	if (sscanf(now,"%d/%d/%d/%d/%d",&year,&day,&hour,&min,&sec) == 5)
				{

					if(day == 365 && hour == 23 && min == 59 && sec == 59)
					{
						year = year + 1;
						day = 0;
						hour = 0;
						min = 0;
						sec = 0;
						sprintf(now ,"%d/%d/%d/%d/%d",year,day,hour,min,sec );


						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,day,hour,min,sec);
					}
					else if(min != 59 && sec == 59)
					{
						min = min + 1;
						sec = 0;
						sprintf(now, "%d/%d/%d/%d/%d",year,day,hour,min,sec );
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,day,hour,min,sec);
					}
					else if (day != 365 && hour == 23 && min == 59 && sec == 59)
					{
						day = day + 1;
						hour = 0;
						min = 0;
						sec = 0;
						sprintf(now, "%d/%d/%d/%d/%d",year,day,hour,min,sec );
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,day,hour,min,sec);
					}
					else if (hour != 23 && min == 59 && sec == 59)
					{
						hour = hour + 1;
						min = 0;
						sec = 0;
						sprintf(now, "%d/%d/%d/%d/%d",year,day,hour,min,sec );;
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,day,hour,min,sec);
					}
					else if (sec != 59)
					{
						sec = sec + 1;
						sprintf(now, "%d/%d/%d/%d/%d",year,day,hour,min,sec );
						//printf("%s\n",now );
					//	printf("%d/%d/%d/%d/%d\n", year,day,hour,min,sec);
					}
					else{}
				}
}

void check(char *timestamp)
{
	int 		year,day,hour,min,sec;
	if ((sscanf(timestamp,"%d/%d/%d/%d/%d",&year,&day,&hour,&min,&sec) != 5) || year < 1000 || year > 9999 || day < 0 ||
											day > 365 || hour < 0 || hour > 23 ||min < 0 || min > 59 ||sec < 0 || sec > 59 )
	//Error - If enter more than 5 numbers still give correct answer	//CHECKING IF THE ARGUMENT IS CORRECT OR NOT
	{
		fprintf(stderr,"\x1b[1;31mEnter a valid timestamp or type 'quit'\x1b[0m\n");
		scanf("%s",timestamp);
		if(strcmp(timestamp,"quit") == 0){exit(0);}
		check(timestamp);
	}
}
