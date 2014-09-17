/**************************************************

file: main.c
purpose: simple demo that receives characters from
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

 **************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#include <string.h>
#include <strings.h>
#endif

#include "rs232.h"
#include "get_time.h"

extern char comports[30][16];

int findSerial (char *thePortName) {
	for (int i=0; i<30; i++) {
		if (strcasecmp (thePortName, comports[i]) == 0){
			return i;
		}
	}
	return -1;
}

int main(int argc, char **argv)
{
	int i, n, portNum;        /* /dev/ttyS0 (COM1 on windows) */
	int baudrate = 9600;       /* 9600 baud */
	if (argc < 2) {
		printf ("need arguments\n");
		return 1;
	}
	if (argc >= 2) {
		portNum = findSerial (argv[1]);	
		if (portNum < 0) {
			printf ("no this port\n");
			return 2;
		}
	}
	if (argc >= 3) {
		baudrate = atoi (argv[2]);
		if (baudrate <= 0) {
			printf ("error! no this baudrate\n");
			return 3;
		}
	}

	printf ("port=%s\n", argv[1]);
	printf ("portNum=%d\n", portNum);
	printf ("baud=%d\n", baudrate);

	unsigned char buf[4096];


	if(serialBegin (portNum, baudrate, 1))
	{
		printf("Can not open comport\n");

		return(0);
	}

	while(1)
	{
		n = serialRead (portNum, buf, 4095);
		if (n > 0) {
			unsigned long now_time = get_time ();
			while (get_time () - now_time < 5) {
				int t = serialRead (portNum, buf+n, 4095);
				if (t > 0) {
					n += t;
					now_time = get_time ();
				}

			}
			buf[n] = 0;   /* always put a "null" at the end of a string! */

			// for(i=0; i < n; i++)
			// {
			// 	if(buf[i] < 32)  /* replace unreadable control-codes by dots */
			// 	{
			// 		buf[i] = '.';
			// 	}
			// }

			//printf("received %i bytes: %s\n", n, (char *)buf);
			printf("%d:%s", n, (char *)buf);

#ifdef _WIN32
		Sleep(100);
#else
	//	usleep(50000);  /* sleep for 100 milliSeconds */
		//sleep(1);  /* sleep for 100 milliSeconds */

#endif
		}
	}

	return(0);
}
