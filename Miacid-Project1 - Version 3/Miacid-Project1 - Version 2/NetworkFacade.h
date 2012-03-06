#ifndef NETWORKFACADE_H
#define NETWORKFACADE_H

// Includes
#include "foundation.h"

class NetworkFacade{

	#define DEFAULT_BUFLEN 512
	#define DEFAULT_PORT "27015"

	private:
		int iResult;
		SOCKET ConnectSocket;
		char recvbuf[DEFAULT_BUFLEN];
		int recvbuflen;

	public:
		NetworkFacade();
		int awaitConnection();
		int connectTo();
		int sendMove(char*);
		int receiveMove();
		int endConnection();

};

#endif