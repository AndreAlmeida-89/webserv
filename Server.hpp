#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server
{
public:
	// Constructors
	Server(int domain,
		   int service,
		   int protocol,
		   u_int32_t interface,
		   int port,
		   int backlog);

	// Destructor
	~Server();

	// Getters / Setters
	int getDomain() const;
	int getService() const;
	int getProtocol() const;
	u_int32_t getInterface() const;
	int getPort() const;
	struct sockaddr_in getAddress() const;
	int getBacklog() const;
	int getSocket() const;

	// Exceptions
	class SockerError : public std::exception
	{
		virtual const char *what() const throw();
	};

	class BindError : public std::exception
	{
		virtual const char *what() const throw();
	};

	class ListenError : public std::exception
	{
		virtual const char *what() const throw();
	};

	class ReadError : public std::exception
	{
		virtual const char *what() const throw();
	};

	class WriteError : public std::exception
	{
		virtual const char *what() const throw();
	};

	void launch();

private:
	// Constructors
	Server();
	Server(const Server &copy);

	// Operators
	Server &operator=(const Server &assign);

	int _domain;
	int _service;
	int _protocol;
	u_int32_t _interface;
	int _port;
	struct sockaddr_in _address;
	int _backlog;
	int _socket;
};

#endif