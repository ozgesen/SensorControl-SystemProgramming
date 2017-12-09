CC=gcc
LINK=gcc
LDFLAGS=-lpthread
CFLAGS=-c -g -Wall -I.
OBJECT_FILES= SensorVeriSetFunctions.o SensorVeriGetFunctions.o GPIOControl.o sunucu.o

.SUFFIXES: .c .o

.c .o:
	$(CC) $^ -o $@ $<


sunucu: $(OBJECT_FILES)
	$(LINK) $(OBJECT_FILES) -o $@ $(LDFLAGS)


#Dependances
SensorVeriSetFunctions.o: SensorVeriSetFunctions.h SensorVeriSetFunctions.c SensorVeri.h
SensorVeriGetFunctions.o : SensorVeriGetFunctions.h SensorVeriGetFunctions.c SensorVeri.h
GPIOControl.o :GPIOControl.c GPIOControl.h
sunucu.o: sunucu.c SensorVeriGetFunctions.h SensorVeriGetFunctions.h SensorVeri.h
