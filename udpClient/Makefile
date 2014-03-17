all: main.c
	g++ main.c -o udpClient.out -Wall

android:
	arm-linux-gnu-c++ main.c -o udpClient.android -Wall

clean:
	rm *.o udpClient.out
