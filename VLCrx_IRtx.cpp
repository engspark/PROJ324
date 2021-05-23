
#include <stdio.h>
#include <string.h>
#include <errno.h>


#include <wiringPi.h>
#include <wiringSerial.h>



unsigned long prev_millis = 0;

int main ()
{
  int VLC_rx ;
  int IR_tx ;
  char dat[8] = "hello\n";
//  char dat1[100] = "Hello there, my name is josh.\n Howre you doing today?\n Is everything ok?\n";

  //char dat1[120] = "Hello there, my name is josh.\n Howre you doing today?\n Is everything ok?\n";
  char dat3;
  
    //FILE * fileP;
    long size = 1024;
    char * buffer;
    size_t final;



    //// allocating mem for file
    buffer = (char*) malloc (sizeof(char)*size);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    //// copying file into buffer
    //final = fread (buffer,1,size,fileP);
    //if (final != size) 
    //{
        //fputs ("Reading error",stderr); 
        //exit (3);
    //}
    //// the whole file is now loaded in the memory buffer. 

    //fclose (fileP);

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
  IR_tx = serialOpen("/dev/ttyUSB0", 9600);
  VLC_rx = serialOpen("/dev/ttyUSB1", 230400);
  //serialPutchar( ,IR_tx)
  
  char buffer_in[300];
  int buffcount = 0;
  
  
  while(1)
  {
	  char dummy;
	  
      if(millis()-prev_millis > 1000){
	if (buffcount != 0){
	  for(int i = 0; i<buffcount; i++){
	  //printf("%d\r\n", buffcount);  			
	  printf ("%c", buffer_in[i]) ;
	  }
	}
      
	buffcount = 0;
      }
	  
	//if(serialDataAvail (VLC_rx) )
	//{ 
	  //receive character serially
	  if(serialDataAvail(VLC_rx) >0){
	  
	  buffer_in[buffcount] = serialGetchar(VLC_rx);
	  //dummy = serialGetchar(VLC_rx);
	  prev_millis = millis();
	  buffcount++;
	  }
	  //printf("%c", dummy);
	  for(int i = 0; i<buffcount; i++){			
	  //printf ("%c", buffer_in[i]) ;
	  }
	  
	  //buffcount = 0;
	  //fflush (stdout) ;
	 // delay(1000);
	  //serialPuts(IR_tx, "Make thing thing long\n much better now\n");
	  serialPuts(IR_tx, dat);
	  //fflush (stdout) ;
	  //serialPrintf(serial_port, dat);
	  //fflush (stdout) ;
	  //delay (50);
	  // transmit character serially on port
	//return 0;
	  		
	//}

  }
  serialClose(IR_tx);

}
