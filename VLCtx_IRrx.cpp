
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


#include <wiringPi.h>
#include <wiringSerial.h>


int main ()
{
  int IR_rx;
  int VLC_tx;
  //char dat[8] = "hello\n";
  char dat[120] = "Hello there, my name is josh.\n Howre you doing today?\n Is everything ok?\n";
  char dat1[10] = "goodbye\n";
  char dat3;
  
    FILE * fileP;
    long size;
    char * buffer;
    size_t final;
    
    


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
  


    fileP= fopen ( "myfile.txt" , "rb" );
    if (fileP==NULL) {fputs ("File error",stderr); 
    exit (1);
    }

    // calculating file size
    fseek (fileP, 0 , SEEK_END);
    size = ftell (fileP);
    rewind (fileP);
    printf("%u" ,size);

    // allocating mem for file
    buffer = (char*) malloc (sizeof(char)*size);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copying file into buffer
    final = fread (buffer,1,size,fileP);
    if (final != size) 
    {
        fputs ("Reading error",stderr); 
        exit (3);
    }
    // the whole file is now loaded in the memory buffer. 

    fclose (fileP);
    
    
  
 while(1){

	  //char dumbo = 'j';
	  char dataloop[30] = "Hello there\n General Kenobi!\n";
	  delay(10000);
	  //while(scanf("%c", dumbo) <= 0){}

	//if(serialDataAvail (serial_port) )
	//{ 
	  // receive character serially
	  while(serialDataAvail(IR_rx) >0){
	  dat3 = serialGetchar(IR_rx);
	  printf ("%c", dat3);
	  }
	  
//	  serialPuts(VLC_tx, buffer);
//serialPuts (VLC_tx, "Hello there\n General Kenobi!\n");
	  //serial
	  
	  for(int i=0; i<size; i++){
	  serialPutchar(VLC_tx,buffer[i]);	  
	  
	  }
	  
	  delay(2000);
	  //delay (15);
	  //return 0;
	  
	  // transmit character serially on port
      //printf ("%c", *buffer) ;
	  		
	//}
	//delay(1);
  }
  //return 0;


}
