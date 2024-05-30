
#include "Server.hpp"

using namespace std;

int main(void)
{
	try
	{
		Server server(AF_INET,
					  SOCK_STREAM,
					  0,
					  INADDR_ANY,
					  8080,
					  10);

		server.launch();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}

	return (0);
}