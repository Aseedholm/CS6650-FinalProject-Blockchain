#ifndef __SERVERSOCKET_HPP__
#define __SERVERSOCKET_HPP__

#include <memory>

#include "Socket.hpp"

class ServerSocket: public Socket {
public:
	ServerSocket() {}
	~ServerSocket() {}

	ServerSocket(int fd, bool nagle_on = NAGLE_ON);

	bool Init(int port);
	std::unique_ptr<ServerSocket> Accept();
};


#endif // end of #ifndef __SERVERSOCKET_HPP__
