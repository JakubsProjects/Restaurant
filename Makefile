main: main1.o main2.o main3.o
	gcc -o main main1.o main2.o main3.o

main1.o: main1.c main.h
	gcc -c main1.c

main2.o: main2.c main.h
	gcc -c main2.c

main3.o: main3.c main.h
	gcc -c main3.c

clean:
	rm main1.o main2.o main3.o main
