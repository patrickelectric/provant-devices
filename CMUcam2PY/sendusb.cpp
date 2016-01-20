#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <string>
#include <iostream>

//rgb vector to threshold
int rgbv[]={30, 0, 176, 126, 255, 230};
char  temp;
int  i=0;
char byte[64];
char msg[9];
char *pch;

int main()
{

    int fd = open("/dev/ttyUSB0", O_RDWR);

	// restart camera
	sleep(1);
    write(fd, "RS \r", 4);
	sleep(1);
    read(fd, &byte[0], 64);
    printf("R => %s\n", byte);
	// ask camera to track
	sprintf(byte, "TC %d %d %d %d %d %d \r",255-rgbv[0],255-rgbv[1],255-rgbv[2],255-rgbv[3],255-rgbv[4],255-rgbv[5]);

	i=0;
	temp=0;
	while(temp!='\r')
		temp=byte[i++];
	write(fd, byte, i);

	// proccess data
	while(1)
	{
		i=0;
		temp=0;
		usleep(100);
		while(temp!='\r')
		{
			read(fd, &temp, 1);
			byte[i++]=temp;
			if(i>62)
			{
				printf("ERROR\n");
				printf("%s\n",byte);
			}
		}
		//printf("%s\n",byte );
		if(byte[0]=='T')
		{
			byte[i]='\0';

			pch = strtok(byte," ");
			i=0;
			while(pch != NULL)
		  	{
				msg[i++]=atoi(pch);
		    	//printf ("%d -> %d\n",i,msg[i]);
		    	pch = strtok(NULL, " ");
		  	}
			// Default Type T packet
			// T mx my x1 y1 x2 y2 pixels confidence
			if(msg[7]>0)
				printf("coord (%f \t %f)\t CM\n",(87.0/2.0-(float)(msg[1]))*5.0/21.0,(141.0/2.0-float(msg[2]))*5.0/17.0);
		}
	}

    return 0;
}
