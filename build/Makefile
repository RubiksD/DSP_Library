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
OUTPUT2 = Butterworth
INCLUDE = -I ../include

SRC_PATH_FREQ_RESP = $(SRC_PATH)/Frequency_Response
SRC_PATH_FILTER_DSG = $(SRC_PATH)/Filter_Dsg
SRC_FREQ_RESP = $(SRC_PATH_FREQ_RESP)/FIR_Freq_Res.c\
								$(SRC_PATH_FREQ_RESP)/IIR_Freq_Res.c\
								$(SRC_PATH)/main.c

SRC_FITER_DSG = $(SRC_PATH)/main.c\
								$(SRC_PATH_FILTER_DSG)/Filter_Dsg.c\
								$(SRC_PATH_FILTER_DSG)/Butterworth_Filter.c\
								$(SRC_PATH_FREQ_RESP)/FIR_Freq_Res.c\
								$(SRC_PATH_FREQ_RESP)/IIR_Freq_Res.c

FLAGS += $(INCLUDE) $(PRE_COMPILATION_FLAGS)

freq_res:	clean
	$(CC) $(FLAGS) $(SRC_FREQ_RESP) -o $(OUTPUT1).out $(POST_COMPILATION_FLAGS)
	$(NM) -n $(OUTPUT1).out > $(OUTPUT1).map
	$(OD) -S $(OUTPUT1).out > $(OUTPUT1).asm

butterworth:	clean
	$(CC) $(FLAGS) $(SRC_FITER_DSG) -o $(OUTPUT2).out $(POST_COMPILATION_FLAGS)
	$(NM) -n $(OUTPUT2).out > $(OUTPUT2).map
	$(OD) -S $(OUTPUT2).out > $(OUTPUT2).asm

clean:
	rm -f *.map
	rm -f *.out
	rm -f *.asm
	rm -f *.a
	rm -f *.o
