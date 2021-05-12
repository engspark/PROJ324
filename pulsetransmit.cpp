
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>


int main ()
{
  int serial_port ;
  int serial_port1 ;
  char dat[6] = "hello";
  char dat1[8] = "goodbye";
  

  // open serial port
  /*if ((serial_port = serialOpen("/dev/ttyS0", 150)) < 0)	
  {
    
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }
  */
  // initializes wiringPi setup
  if (wiringPiSetup () == -1)					
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }
  serial_port1 = serialOpen("/dev/ttyUSB0", 230400);
  serial_port = serialOpen("/dev/ttyS0", 9600);
  
  while(1)
  {
	  
	//if(serialDataAvail (serial_port) )
	//{ 
	  // receive character serially
	  //dat = serialGetchar (serial_port);			
	  //printf ("%s", dat) ;
	  serialPrintf(serial_port1, dat1);
	  fflush (stdout) ;
	  serialPrintf(serial_port, dat);
	  fflush (stdout) ;
	  delay (5);
	  // transmit character serially on port

	  		
	//}
	//delay(1);
  }

}
