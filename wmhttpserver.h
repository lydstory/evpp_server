/*
 * wmhttpserver.h
 *
 *  Created on: 2019年11月18日
 *      Author: lyd
 */

#ifndef WMHTTPSERVER_H_
#define WMHTTPSERVER_H_

#include "httpHandler.h"
using namespace std;
class wmhttpserver {
public:

   	 wmhttpserver() = default;
	    ~wmhttpserver() = default;

	    bool Start(evpp::EventLoop* loop, short port =8100);
	    void Loop();

	    void DefaultHandler(evpp::EventLoop* loop,\
	                    const evpp::http::ContextPtr& ctx,\
	                    const evpp::http::HTTPSendResponseCallback& cb);
private:
	    bool makedir();
	    bool maketmpdir();
private:
    std::shared_ptr<evpp::http::Server> httpServer_;
    evpp::EventLoop* loop_ = nullptr;
};

#endif /* WMHTTPSERVER_H_ */
