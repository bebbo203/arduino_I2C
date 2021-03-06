# AVR makefile stub

# to clean a folder
# from command line
#$> make clean

# to build the folder
#$> make 

# to upload a file
# from command line
# $> make <main_filename>.hex

#
# remember to give yourself the read/write permissions on the
# serial line
# $> sudo addgroup <your username> dialout
# logout/login



# !!!!!!!!!!!!!!!! MODIFY HERE !!!!!!!!!!!!!!!! 

# put here the file containing the main() routine
# to be uploaded on the avr
# you can add multiple files, they will be all generated

BINS=main_master.c main_slave.c main_serial.c

# put here the additional .o files you want to generate
# one .c file for each .o should be present
OBJS=avr_common/uart.o libs/misc_utils.c libs/queue.c libs/clock.c libs/write.c libs/read.c libs/signals.c libs/i2c.c

# put here the additional header files needed for compilation
HEADERS=avr_common/uart.h libs/queue.h libs/misc_utils.h libs/clock.h libs/write.h libs/read.h libs/signals.h libs/i2c.h


# the file below contains the actual rules

# !!!!!!!!!!!!!!!! MODIFY HERE !!!!!!!!!!!!!!!! 

include avr_common/avr.mk




