OBJS = parse.o main.o
main:	$(OBJS)
	g++ -pedantic  $(OBJS) -o a.out
parse.o:  parse.cpp
	g++ -c parse.cpp
main.o:	main.c
	g++ -c main.c 
clean:
	rm *.o
