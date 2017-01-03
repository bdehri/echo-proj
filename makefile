
CC=g++ -std=c++0x
INCLUDES=-I ~/beast/
LİB=-lboost_system -pthread


program: client.cpp 
	$(CC) client.cpp $(INCLUDES) $(LİB) -o client
 

