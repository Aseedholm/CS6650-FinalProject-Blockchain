#ifndef __CLIENTSOCKET_HPP__
#define __CLIENTSOCKET_HPP__

#include <string>

#include "Socket.hpp"


class ClientSocket: public Socket {
public:
	ClientSocket() {}
	~ClientSocket() {}

	int Init(std::string ip, int port);
};


#endif // end of #ifndef __CLIENTSOCKET_HPP__
