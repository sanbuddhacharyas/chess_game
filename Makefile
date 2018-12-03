#
CC=g++
CFLAGS = -c -Wall
all: hello
hello:main.o Blob.o opencv.o CBoard.o ai.o CMove.o CMoveList.o SerialPort.o SerialStream.o SerialStreamBuf.o serial.o
	$(CC) main.o Blob.o opencv.o  CBoard.o ai.o CMove.o CMoveList.o SerialPort.o SerialStream.o SerialStreamBuf.o serial.o -lsfml-audio -lsfml-window -lsfml-graphics -lsfml-system `pkg-config --cflags --libs opencv` -o san

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

Blob.o: Blob.cpp
	$(CC) $(CFLAGS) Blob.cpp

opencv.o:opencv.cpp
	$(CC) $(CFLAGS) opencv.cpp

CBoard.o:CBoard.cpp
	$(CC) $(CFLAGS) CBoard.cpp

ai.o: ai.cpp
	$(CC) $(CFLAGS) ai.cpp

CMove.o: CMove.cpp
	$(CC) $(CFLAGS) CMove.cpp

CMoveList.o: CMoveList.cpp
	$(CC) $(CFLAGS) CMoveList.cpp

SerialPort.o : SerialPort.cpp
	$(CC) $(CFLAGS) SerialPort.cpp

SerialStream.o : SerialStream.cpp
	$(CC) $(CFLAGS) SerialStream.cpp

SerialStreamBuf.o : SerialStreamBuf.cpp
	$(CC) $(CFLAGS) SerialStreamBuf.cpp
 
serial.o: serial.cpp 
	$(CC) $(CFLAGS) serial.cpp


clean:
	rm -rf *o san


