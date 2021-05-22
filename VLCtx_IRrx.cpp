
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include <wiringPi.h>
#include <wiringSerial.h>


int main ()
{
  int IR_rx;
  int VLC_tx;
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
  IR_rx = serialOpen("/dev/ttyUSB0", 9600);
  VLC_tx = serialOpen("/dev/ttyS0", 230400);
  
  while(1)
  {
	  
	//if(serialDataAvail (serial_port) )
	//{ 
	  // receive character serially
	  while(serialDataAvail(IR_rx) >0){
	  dat3 = serialGetchar (IR_rx);			
	  printf ("%c", dat3) ;
	  }
	  //fflush (stdout) ;
	  serialPrintf(VLC_tx, dat);
	  //fflush (stdout) ;
	  //serialPrintf(serial_port, dat);
	  //fflush (stdout) ;
	  delay (15);
	  // transmit character serially on port

	  		
	//}
	//delay(1);
  }

}
