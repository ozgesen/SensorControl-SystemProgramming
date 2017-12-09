#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include "SensorVeri.h"
#include "SensorVeriGetFunctions.h"
#include "SensorVeriSetFunctions.h"
#include <fcntl.h> 
#include <unistd.h> 
#include "GPIOControl.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#define bool int
#define true 1
#define false 0
#define sensorsize 2
Sensor sen[sensorsize];
Surucu sur;

int baglantiIstegi; //baglantinin hanngi iletisim kanalından geldiği bilgisi
int bitti; //client-server iletisimi biterse UART'ı kesmek ici isaret 
int count;//Sensor count
char *ip="192.168.1.37";
int serverport=7778;
int server_fd,client_fd;


void alarmHandler ( )
{
  printf ("Suncu kapanıyor.\n") ;
  close(server_fd);
}
char durumPaketleme(){
  char sonuc;
  int i=0;
  unsigned int senid=0;
  int sendurum=0;
  uint8_t unsonuc;
  uint8_t toplam=0x0;
  Sensor *s;

  for(i=0;i<sensorsize;i++){
  s=&sen[i];
  
  senid=getSensorId(s);
  sendurum=getSensorDurum(s);

  if(sendurum==1)
  unsonuc=0x1;
  else
  unsonuc=0x0;

  unsonuc=unsonuc >> senid; 
  toplam = toplam | unsonuc;
  }
  sonuc=toplam;
  printf("Cikan char degeri \n %c \n ",sonuc);
  return sonuc;


}

void *uartControl() 
{    
/*

int uart0_filestream = -1;

uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);//Open in non blocking read/write mode
	if (uart0_filestream == -1)
	{

		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}


struct termios options;
tcgetattr(uart0_filestream, &options);
options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;//<Set baud rate
options.c_iflag = IGNPAR;
options.c_oflag = 0;
options.c_lflag = 0;
tcflush(uart0_filestream, TCIFLUSH);
tcsetattr(uart0_filestream, TCSANOW, &options);


while(true){
//----- RECEIVE BYTES -----
if (uart0_filestream != -1)
{
	// Read up to 255 characters from the port if they are there
	unsigned char rx_buffer[256];
	char packet[30];
        char *p;
        p=&packet[0];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);//Filestream, buffer to store in, number of bytes to read (max)
	if (rx_length < 0)
	{
	//An error occured (will occur if there are no bytes)
	printf("Read error\n");
	}
	else if (rx_length == 0)
	{
	//No data waiting
	printf("no data to readr\n");
	}
	else
	{
	//Bytes received
	rx_buffer[rx_length] = '\0';
	


                        int flag=0;
		        char alinanmesaj[10];
		        int veri;

			   
		       sscanf(rx_buffer,"%s %d", alinanmesaj, &veri);
	   		

		        	if(strncmp(rx_buffer, "sensorDurum:",11) ==0)
		                {
				 output = durumPaketleme();   
                                 sprintf(p,"sensorDurum %c:",output);               

		                }
		        	else if(strncmp(rx_buffer, "sensorSayi:",11) ==0)
		                {

		                 sprintf(p, "sensorSayi %d:", sensorsize);
	 

		                }
		        	else if(strncmp(rx_buffer, "sensorTip",8) ==0)
		                {
		                 
		                 sprintf(p, "sensorTip %s:", getSensorTip(&sen[veri]));  
	   
		                
		                }
		        	else if(strncmp(rx_buffer, "surucu",6) == 0 && strlen(alinanmesaj)<9)
		                {
		                 flag= setSurucuDurum(&sur,veri);
				
		                
		                 if(flag==1)
		                 { sprintf(p, "surucu ok:");  }
		                 else
		                 { sprintf(p, "surucu err:");  }
		               
		                 
		                }
		        	else if(strcmp(rx_buffer, "surucuDurum:") ==0)
		                {
		
                                 sprintf(p, "surucuDurum %d:",getSurucuDurum(&sur));  
		                 
		                }
		        	else if(strncmp(rx_buffer, "off",3) ==0)
		                { 
		                 break;                         
		                }
		                else{}

			
                               
	if (uart0_filestream != -1)
	{
		int count = write(uart0_filestream, &packet[0], strlen(p)); //Filestream, bytes to write, number of bytes to write
		if (count < 0)
		{
			printf("UART TX error\n");
		}
	}


}}

close(uart0_filestream);
*/
pthread_exit(0);



} 
void *sensorGuncelle(void *sen) 
{    int deger=0;
     Sensor *sens=(Sensor *)sen;
     setSensorId(sens,count);
     setSensorTip(sens,count);
     count++;
	while(1){
	 
             deger =getSensorId(sens);
             setSensorDurum(sens,deger);


	     if(bitti==0)
	     break;

          sleep(5);
	}
   pthread_exit(0);
     
} 

void *serverControl() 
{    


        char output;
	struct sockaddr_in caddr,saddr;
	char msg[30];
	char packet[30];
        char *p;
        p=&packet[0];
	int size;
     
	//Server Socket Address
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(serverport);

	saddr.sin_addr.s_addr=htonl(INADDR_ANY);

	//Create server socket
	server_fd=socket(PF_INET,SOCK_STREAM,0);
	if(server_fd == -1){
		printf("Error on socket creation [%s] \n",strerror(errno));
		return (0); 
	}

	//Bind the address to server socket
	if(bind(server_fd,(struct sockaddr *)&saddr, sizeof(struct sockaddr))==-1){
		printf("Error socket bind [%s] \n",strerror(errno));
		return (0); 
	}

	//Listen for a connection request
	if(listen(server_fd,1)){
		printf("Error socket listen [%s] \n",strerror(errno));
		return (0); 
	}


	//Accept connection request and connect
	socklen_t addrSize=sizeof(caddr);
      client_fd=accept(server_fd,(struct sockaddr*)&caddr,&addrSize);	
	if(client_fd==-1){
		printf("Error socket accept [%s] \n",strerror(errno));
		close(server_fd);
		return (0); 
	}
	printf("Server new connecton has been established [%s/%d]\n",inet_ntoa(caddr.sin_addr),caddr.sin_port);

        signal(SIGTSTP, alarmHandler) ; 

       while(true){
		//read and write maeesages
		if((size=read(client_fd,msg,sizeof(msg)))==-1){
		
			printf("Error reading [%s] \n",strerror(errno));
	 	}
		else{  
				
			printf("Read data [%s]\n",msg);

		        int flag=0;
		        char alinanmesaj[10];
		        int veri;

			   
		       sscanf(msg,"%s %d", alinanmesaj, &veri);
	   		

		        	if(strncmp(msg, "sensorDurum:",11) ==0)
		                {
				 output = durumPaketleme();   
                                 sprintf(p,"sensorDurum %c:",output);               

		                }
		        	else if(strncmp(msg, "sensorSayi:",11) ==0)
		                {

		                 sprintf(p, "sensorSayi %d:", sensorsize);
	 

		                }
		        	else if(strncmp(msg, "sensorTip",8) ==0)
		                {
		                 
		                 sprintf(p, "sensorTip %s:", getSensorTip(&sen[veri]));  
	   
		                
		                }
		        	else if(strncmp(msg, "surucu",6) == 0 && strlen(alinanmesaj)<9)
		                {
		                 flag= setSurucuDurum(&sur,veri);
				
		                
		                 if(flag==1)
		                 { sprintf(p, "surucu ok:");  }
		                 else
		                 { sprintf(p, "surucu err:");  }
		               
		                 
		                }
		        	else if(strcmp(msg, "surucuDurum:") ==0)
		                {
		
                                 sprintf(p, "surucuDurum %d:",getSurucuDurum(&sur));  
		                 
		                }
		        	else if(strncmp(msg, "off",3) ==0)
		                { 
		                 break;                         
		                }
		                else{}

				if(write(client_fd,packet,sizeof(packet))!=sizeof(packet)){
				printf("Error writing [%s] \n",strerror(errno));
				}
				else{
				printf("Sent data [%s] \n",packet);
				} 
			}
			
        }

	//Close connections
	close(server_fd);
    
	return 0;
} 
int main(){

    int i=0;

    pthread_t t1,t2;
    pthread_t t[sensorsize];
    count =0;
 
    printf("Sunucu ip : [%s] Sunucu port : [%d]\n",ip,serverport);

    pthread_create (&t1, NULL, uartControl, NULL) ; //UART beklemesi için
    pthread_create (&t2, NULL, serverControl, NULL);   //client-server baglantisi icin

    for(i=0;i<sensorsize;i++)
    {
       pthread_create (&t[i], NULL, sensorGuncelle, (void *)&sen[i]) ; //sensor durum guncelleme
    }

    pthread_join (t1, NULL) ;
    pthread_join (t2, NULL) ; 
 return 0;
}
