CC= gcc
FLAGS= -g -Wall

.PHONY: clean all

all: cmp copy encode decode stshell codecA codecB

cmp: cmp.o
	$(CC) $(FLAGS) -o $@ $^

copy: copy.o
	$(CC) $(FLAGS) -o $@ $^

encode: encode.o libcodecA.so libcodeB.so
	$(CC) $(FLAGS) -o $@ $< -ldl

decode: decode.o libcodecA.so libcodeB.so
	$(CC) $(FLAGS) -o $@ $< -ldl

stshell: stshell.o
	$(CC) $(FLAGS) -o $@ $^

libcodecA.so: codecA.o
	$(CC) $(FLAGS) -shared -o $@ $^
	
libcodecB.so: codecB.o
	$(CC) $(FLAGS) -shared -o $@ $^

codecA.o: codecA.c codec.h
	$(CC) $(FLAGS) -fPIC -c $^

codecB.o: codecB.c codec.h
	$(CC) $(FLAGS) -fPIC -c $^

%.o: %.c
	$(CC) $(FLAGS) -c $^

clean: 
	rm -f *.gch *.so *.o cmp copy encode decode stshell