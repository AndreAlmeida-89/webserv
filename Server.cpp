#include "Server.hpp"

// Constructors
Server::Server()
{
	_domain = 0;
	_service = 0;
	_protocol = 0;
	_interface = 0;
	_port = 0;
	bzero(&_address, sizeof(_address));
	_backlog = 0;
	_socket = 0;
	std::cout << "\e[0;33mDefault Constructor called of Server\e[0m" << std::endl;
}

Server::Server(const Server &copy)
{
	_domain = copy.getDomain();
	_service = copy.getService();
	_protocol = copy.getProtocol();
	_interface = copy.getInterface();
	_port = copy.getPort();
	_address = copy.getAddress();
	_backlog = copy.getBacklog();
	std::cout << "\e[0;33mCopy Constructor called of Server\e[0m" << std::endl;
}

Server::Server(int domain,
			   int service,
			   int protocol,
			   u_int32_t interface,
			   int port,
			   int backlog)
{
	_domain = domain;
	_service = service;
	_protocol = protocol;
	_interface = interface;
	_port = port;
	_backlog = backlog;
	bzero(&_address, sizeof(_address));
	_address.sin_family = _domain;
	_address.sin_port = htons(_port);
	_address.sin_addr.s_addr = htonl(_interface);
	_socket = socket(_domain, _service, _protocol);

	if (_socket < 0)
		throw SockerError();
	if (bind(_socket, (struct sockaddr *)&_address, sizeof(_address)) < 0)
		throw BindError();
	if (listen(_socket, _backlog) < 0)
		throw ListenError();
}

// Destructor
Server::~Server()
{
	std::cout << "\e[0;31mDestructor called of Server\e[0m" << std::endl;
}

// Operators
Server &Server::operator=(const Server &assign)
{
	_domain = assign.getDomain();
	_service = assign.getService();
	_protocol = assign.getProtocol();
	_interface = assign.getInterface();
	_port = assign.getPort();
	_address = assign.getAddress();
	_backlog = assign.getBacklog();
	_socket = assign.getSocket();

	return *this;
}

// Getters / Setters
int Server::getDomain() const
{
	return _domain;
}
int Server::getService() const
{
	return _service;
}
int Server::getProtocol() const
{
	return _protocol;
}
u_int32_t Server::getInterface() const
{
	return _interface;
}
int Server::getPort() const
{
	return _port;
}
struct sockaddr_in Server::getAddress() const
{
	return _address;
}
int Server::getBacklog() const
{
	return _backlog;
}

int Server::getSocket() const
{
	return _socket;
}

void Server::launch()
{
	char buffer[2056];
	const char *http_response = "HTTP/1.1 200 OK\r\n"
								"Content-Length: 35\r\n"
								"Content-Type: text/html; charset=utf-8\r\n\r\n"
								"<html><h1>Hello, world!</h1></html>";
	bzero(&buffer, sizeof(buffer));

	while (1)
	{
		std::cout << "Waiting for a connection..." << std::endl;

		size_t len = sizeof(_address);
		int socket_fd = accept(_socket,
							   (sockaddr *)&_address,
							   (socklen_t *)&len);
		if (socket_fd < 0)
			throw SockerError();

		if (read(socket_fd, buffer, sizeof(buffer)) < 0)
			throw ReadError();

		std::cout << buffer;

		if (write(socket_fd, http_response, strlen(http_response)) < 0)
			throw WriteError();

		close(socket_fd);
	}
}

// Exceptions
const char *Server::SockerError::what() const throw()
{
	return "Error creating socket";
}

const char *Server::BindError::what() const throw()
{
	return "Error binding";
}

const char *Server::ListenError::what() const throw()
{
	return "Error listening";
}

const char *Server::ReadError::what() const throw()
{
	return "Error reading buffer";
}

const char *Server::WriteError::what() const throw()
{
	return "Error writing buffer";
}