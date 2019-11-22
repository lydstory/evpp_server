#include <stdio.h>
#include <evpp/http/http_server.h>
#include <evpp/http/service.h>

#include "wmhttpserver.h"
#include "util.h"
#include "config.h"


int main(int argc, char* argv[]) {

    conf.loadConfig("./wmsvc.conf");
	 initEmbedWatermark();
    init_pdf2svg();
	 evpp::EventLoop loop;
	 wmhttpserver server;
	 server.Start(&loop,9100);
	 server.Loop();
	 std::cout<<"hello,world"<<std::endl;

    return 0;
}
