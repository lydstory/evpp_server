// netserver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>
#include <vector>
#include <list>
using namespace std;
#ifdef _WIN32
#include "winmain-inl.h"
#endif
std::vector<evpp::TCPConnPtr> conns;
std::vector<evpp::TCPConnPtr>::iterator iter;
void OnMessage(const evpp::TCPConnPtr& conn,
	evpp::Buffer* msg) {
	std::string s = msg->NextAllString();
	// LOG_INFO << "Received a message [" << s << "]";

	std::cout << conns.size() << std::endl;
	for (iter = conns.begin(); iter != conns.end(); iter++)
	{
		if (*iter != conn)
		{

			evpp::TCPConnPtr sconn;
			sconn = *iter;

			sconn->Send(s);
		}
		else
			continue;
	}

	if (s == "quit" || s == "exit") {
		conn->Close();
	}
}


void OnConnection(const evpp::TCPConnPtr& conn) {
	if (conn->IsConnected()) {
		std::cout << "Accept a new connection from " << conn->remote_addr();
		std::cout << conn->remote_addr() << std::endl;
		conns.push_back(conn);
	}
	else {
		std::cout << "Disconnected from " << conn->remote_addr();

		//  conns.pop(conn);
		conns.erase(remove(conns.begin(), conns.end(), conn), conns.end());

	}




}


int main(int argc, char* argv[]) {


	std::string port = "9099";

	conns.clear();
	
	std::string addr = std::string("0.0.0.0:") + port;
	evpp::EventLoop loop;
	evpp::TCPServer server(&loop, addr, "TCPEcho", 0);
	server.SetConnectionCallback(&OnConnection);
	server.SetMessageCallback(&OnMessage);

	server.Init();
	server.Start();
	loop.Run();
	return 0;
}
