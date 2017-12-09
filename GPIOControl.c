#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#define LOW  0

#define HIGH 1
#define bool int
#define true 1
#define false 0
#define SENSOR1 17
#define SENSOR2 18
#define RELAY  27

static int GPIORead(int pin){
    char path[28];
    char value_str[3];
    int fd;
    snprintf(path,30,"/sys/class/gpio%d/value",pin);
    fd=open(path,O_RDONLY);
    if(-1 ==fd){
        fprintf(stderr,"Failed");
        return(-1);
        
    }
    if(-1 ==read(fd,value_str,3)){
        fprintf(stderr,"Failed");
        return(-1);
    }
    close(fd);
    return(atoi(value_str));
    
    
    
}


static int GPIOWrite(int pin,int value){
    static const char s_values_str[]="01";
    char path[30];
    int fd;
    snprintf(path,30,"/sys/class/gpio/gpio%d/value",RELAY);
    fd = open(path,O_WRONLY);
    if(-1 == fd ){
        fprintf(stderr,"Failed");
        return(-1);
    }
    if(1!=write(fd,&s_values_str[LOW == value? 0:1],1)){
        fprintf(stderr,"Failed");
        return(-1);
    }
    close(fd);
    return(0);
    
        
    
}


int getSensor(int id){
        if(id==0)
	{return GPIORead(SENSOR1);}

        else if(id==1)
	{return GPIORead(SENSOR2);}

        else if(id==3)
	{//return GPIORead(SENSOR3);
         return 0;
	}

        else if(id==4)
	{//return GPIORead(SENSOR4);
        return 0;
	}

        else if(id==5)
	{//return GPIORead(SENSOR5);
	return 0;
	}

        else if(id==6)
	{//return GPIORead(SENSOR6);
	return 0;
	}

        else if(id==7)
	{//return GPIORead(SENSOR7);
        return 0;
	}
	
	else{return 0;}
}



void setSurucu(bool hedef){
         if(hedef ==true )
	 {GPIOWrite(RELAY,HIGH);}
         else
         {GPIOWrite(RELAY,LOW);}
         

}




