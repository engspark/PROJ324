
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <wiringPi.h>
#include <wiringSerial.h>


int main ()
{
  int serial_port ;
  char dat[6] = "hello";
  
  
  
  // open serial port
  if ((serial_port = serialOpen("/dev/ttyUSB0", 150)) < 0)	
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }
  // initializes wiringPi setup
  if (wiringPiSetup () == -1)					
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(1)
  {
	  
	//if(serialDataAvail (serial_port) )
	//{ 
	  // receive character serially
	  //dat = serialGetchar (serial_port);			
	  printf ("%s", dat) ;

	  //fflush (stdout) ;
	  // transmit character serially on port
	  serialPrintf(serial_port, dat);		
	//}
	delay(100);
  }

}
