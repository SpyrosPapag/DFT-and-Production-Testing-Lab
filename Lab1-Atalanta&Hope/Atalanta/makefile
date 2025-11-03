#
# Makefile of atalanta
#
CFLAGS = -O
GDATA =	parameter.h define.h macro.h
CC=gcc
#
# for atpg
#
SRCS =	error.c hash.c help.c read_cct.c structure.c io.c pio.c \
	stem.c define_fault_list.c testability.c fan.c \
	learn.c ppsfp.c truth.c lsim.c fsim.c random.c print.c sim.c atalanta.c
OBJS =	error.o hash.o help.o read_cct.o structure.o io.o pio.o \
	stem.o define_fault_list.o testability.o fan.o \
	learn.o ppsfp.o truth.o lsim.o fsim.o random.o print.o sim.o atalanta.o




#SRCS =	error.c hash.c help.c read_cct.c structure.c io.c pio.c \
#	stem.c define_fault_list.c testability.c fan.c help_fsim.c \
#	learn.c ppsfp.c truth.c lsim.c fsim.c random.c print.c sim.c main_fsim.c
#OBJS =	error.o hash.o help.o read_cct.o structure.o io.o pio.o \
#	stem.o define_fault_list.o testability.o fan.o help_fsim.o \
#	learn.o ppsfp.o truth.o lsim.o fsim.o random.o print.o sim.o main_fsim.o

#
# for fault simulator
#
OBJSF =	error.o hash.o help_fsim.o read_cct.o structure.o io.o pio.o \
	define_fault_list.o ppsfp.o random.o print.o main_fsim.o

atalanta:	$(OBJS) $(GDATA)
	gcc $(CFLAGS) $(OBJS) -o atalanta

fsim:	$(OBJSF) $(GDATA)
	gcc $(CFLAGS) $(OBJSF) -o fsim

atalanta.o:	atalanta.c $(GDATA) truthtable.h global.d
	gcc $(CFLAGS) -c atalanta.c

main_fsim.o:	main_fsim.c $(GDATA) truthtable.h global.d
	gcc $(CFLAGS) -c main_fsim.c

io.o:	io.c $(GDATA)
	gcc $(CFLAGS) -c io.c

print.o:	print.c $(GDATA)
	gcc $(CFLAGS) -c print.c

pio.o:	pio.c $(GDATA)
	gcc $(CFLAGS) -c pio.c

stem.o:	stem.c $(GDATA)
	gcc $(CFLAGS) -c stem.c

define_fault_list.o:	define_fault_list.c $(GDATA)
	gcc $(CFLAGS) -c define_fault_list.c

testability.o:	testability.c $(GDATA)
	gcc $(CFLAGS) -c testability.c

fan.o:	fan.c $(GDATA)
	gcc $(CFLAGS) -c fan.c

learn.o:	learn.c $(GDATA)
	gcc $(CFLAGS) -c learn.c

ppsfp.o:	ppsfp.c $(GDATA)
	gcc $(CFLAGS) -c ppsfp.c

truth.o:	truth.c $(GDATA)
	gcc $(CFLAGS) -c truth.c

lsim.o:	lsim.c $(GDATA)
	gcc $(CFLAGS) -c lsim.c

fsim.o:	fsim.c $(GDATA)
	gcc $(CFLAGS) -c fsim.c

random.o:	random.c
	gcc $(CFLAGS) -c random.c

hash.o:	hash.c $(GDATA)
	gcc $(CFLAGS) -c hash.c

error.o:	error.c $(GDATA)
	gcc $(CFLAGS) -c error.c

help.o:	help.c $(GDATA)
	gcc $(CFLAGS) -c help.c

help_fsim.o:	help_fsim.c $(GDATA)
	gcc $(CFLAGS) -c help_fsim.c

read_cct.o:	read_cct.c $(GDATA)
	gcc $(CFLAGS) -c read_cct.c

structure.o:	structure.c $(GDATA)
	gcc $(CFLAGS) -c structure.c

sim.o:	sim.c $(GDATA)
	gcc $(CFLAGS) -c sim.c

lint:
	lint $(SRCS)

clear:
	rm -f *.o

