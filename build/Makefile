CC = gcc
OD = objdump
LD = ld
NM = nm
AR = ar
RANLIB = ranlib

AR_FLAGS = rc

SRC_PATH = ../src
PRE_COMPILATION_FLAGS = -Wall -O3 -g
POST_COMPILATION_FLAGS = -lm
OUTPUT1 = Frequency_Response
INCLUDE = -I ../include

SRC_COMMON = 	$(SRC_PATH)/fft.c\
							$(SRC_PATH)/cordic.c

SRC_PATH_FREQ_RESP = $(SRC_PATH)/Frequency_Response
SRC_FREQ_RESP = $(SRC_PATH_FREQ_RESP)/FIR_Freq_Res.c\
								$(SRC_PATH)/main.c

FLAGS += $(INCLUDE) $(PRE_COMPILATION_FLAGS)

freq_res:	clean
	$(CC) $(FLAGS) $(SRC_FREQ_RESP) -o $(OUTPUT1).out $(POST_COMPILATION_FLAGS)


fft:	clean
	$(CC) $(FLAGS) $(SRC1) -o $(OUTPUT1).out $(POST_COMPILATION_FLAGS)
	$(NM) -n $(OUTPUT1).out > $(OUTPUT1).map
	$(OD) -S $(OUTPUT1).out > $(OUTPUT1).asm

sin_wave:	clean
	$(CC) $(FLAGS) $(SRC2) -o $(OUTPUT2).out $(POST_COMPILATION_FLAGS)
	$(NM) -n $(OUTPUT2).out > $(OUTPUT2).map
	$(OD) -S $(OUTPUT2).out > $(OUTPUT2).asm

library:	clean
	$(CC) $(SRC_COMMON) -c $(FLAGS)
	$(AR) $(AR_FLAGS) cordic_fft.a *.o
	$(RANLIB) cordic_fft.a
	cp -f cordic_fft.a ../lib

clean:
	rm -f *.map
	rm -f *.out
	rm -f *.asm
	rm -f *.a
	rm -f *.o
