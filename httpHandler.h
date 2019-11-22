/*
 * httpHandler.h
 *
 *  Created on: 2019年11月18日
 *      Author: lyd
 */

#ifndef HTTPHANDLER_H_
#define HTTPHANDLER_H_
#include "evpp/http/http_server.h"
#include "evpp/event_loop.h"

class httpHandler {
public:
    httpHandler() = default;
    ~httpHandler() = default;

public:
    static void getDefailtAvaterHandler(evpp::EventLoop* loop,\
                      const evpp::http::ContextPtr& ctx,\
                      const evpp::http::HTTPSendResponseCallback& cb);
    static void getDefailtFileUpload(evpp::EventLoop* loop,\
                      const evpp::http::ContextPtr& ctx,\
                      const evpp::http::HTTPSendResponseCallback& cb);
    static void getWaterMark(evpp::EventLoop* loop,
                        const evpp::http::ContextPtr& ctx,
                        const evpp::http::HTTPSendResponseCallback& cb);
    static void getFileContent(evpp::EventLoop* loop,
                        const evpp::http::ContextPtr& ctx,
                        const evpp::http::HTTPSendResponseCallback& cb);
};


#endif /* HTTPHANDLER_H_ */
