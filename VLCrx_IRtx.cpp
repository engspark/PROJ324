
#include <stdio.h>
#include <stdlib.h>
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
  
  char buffer_in[819200];
  int buffcount = 0;
  
  int blockcount = 0;
 
 
   // Open File for writing
  FILE *f_dst = fopen("fullpic.bmp", "ab");
  if(f_dst == NULL)
  {
    printf("ERROR - Failed to open file for writing\n");
    exit(1);
  }
  
  
  while(1)
  {
	  char dummy;
	
	  
      if(millis()-prev_millis > 1000){
	if (buffcount != 0){
	  printf("Buffer count is not zero\n");
	  for(int i = 0; i<buffcount; i++){
	  //printf("%d\r\n", buffcount);  			
	  printf ("%c", buffer_in[i]) ;
	  
	  fwrite (&buffer_in[i], 1, 1, f_dst);
	   
	  }
	  //printf("block count incremented\n");
	  //fwrite (buffer_in, 1, buffcount, f_dst);
	  blockcount++;
	}
	
    if (blockcount == 1){      



    // Close File
    fclose(f_dst);
    printf("File Recieved");
    return 0;
    //f_dst = NULL; 
    }
    buffcount = 0;
    
      }
	  

	  //receive character serially
	  while(serialDataAvail(VLC_rx) >0){
	  
	  buffer_in[buffcount] = serialGetchar(VLC_rx);
	  //dummy = serialGetchar(VLC_rx);
	  prev_millis = millis();
	  //printf("buffer count incremented\n");
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
