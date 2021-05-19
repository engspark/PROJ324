
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include <wiringPi.h>
#include <wiringSerial.h>


int main ()
{
  int serial_port ;
  int serial_port1 ;
  char dat[8] = "hello\n";
  char dat1[10] = "goodbye\n";
  char dat3;
  

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
  serial_port1 = serialOpen("/dev/ttyUSB0", 9600);
  serial_port = serialOpen("/dev/ttyUSB1", 230400);
  
  while(1)
  {
	  
	//if(serialDataAvail (serial_port) )
	//{ 
	  // receive character serially
	  while(serialDataAvail(serial_port) >0){
	  dat3 = serialGetchar (serial_port);			
	  printf ("%c", dat3) ;
	  }
	  //fflush (stdout) ;
	  serialPrintf(serial_port1, dat1);
	  //fflush (stdout) ;
	  //serialPrintf(serial_port, dat);
	  //fflush (stdout) ;
	  delay (15);
	  // transmit character serially on port

	  		
	//}
	//delay(1);
  }

}
