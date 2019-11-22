/*
 * wmhttpserver.cpp
 *
 *  Created on: 2019年11月18日
 *      Author: lyd
 */
#include <base/StringUtil.h>
#include "wmhttpserver.h"
#include <evpp/http/http_server.h>
#include <evpp/http/service.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include "fileHandle.h"
#include "util.h"
void wmhttpserver::DefaultHandler(evpp::EventLoop* loop,
                    const evpp::http::ContextPtr& ctx,
                    const evpp::http::HTTPSendResponseCallback& cb) {
	    ctx->AddResponseHeader("Content-Type", "text/html");
	    ctx->AddResponseHeader("Access-Control-Allow-Origin", "*");
	    ctx->AddResponseHeader("Server", "evpp");
	    std::ifstream t("/tmp/index.html");
	    std::stringstream buffer;
	    buffer << t.rdbuf();
	    std::string contents(buffer.str());
	    cb(contents);
}

bool wmhttpserver::Start(evpp::EventLoop *loop, short port) {
	 maketmpdir();
    evpp::http::Server server(10);

    server.SetThreadDispatchPolicy(evpp::ThreadDispatchPolicy::kIPAddressHashing);
    server.RegisterDefaultHandler(std::bind(&wmhttpserver::DefaultHandler,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3));
    server.RegisterHandler("/getDefaultAvatar", httpHandler::getDefailtAvaterHandler);
    server.RegisterHandler("/fileupload", httpHandler::getDefailtFileUpload);
    server.RegisterHandler("/postwatermark", httpHandler::getWaterMark);
    server.RegisterHandler("/getfilecontent", httpHandler::getFileContent);
    server.Init(port);
    server.Start();

    return false;

}
void wmhttpserver::Loop() {
    loop_->Run();
}
bool wmhttpserver::maketmpdir() {

    std::string rootDir = "/tmp/output/";
    if (!ForceDirectory(rootDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string sourceDir = "/tmp/source/";
    if (!ForceDirectory(sourceDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string watermarkDir = "/tmp/watermark/";
    if (!ForceDirectory(watermarkDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string resourcekDir = "/tmp/resource/";
    if (!ForceDirectory(resourcekDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string logDir = "/tmp/log/";
    if (!ForceDirectory(logDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    return false;
}

bool wmhttpserver::makedir() {

    std::string rootDir = IncludeTrailingPathDelimiter(getHomePath())+"work/hgcode/webserver/output/";
    if (!ForceDirectory(rootDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string sourceDir = IncludeTrailingPathDelimiter(getHomePath())+"work/hgcode/webserver/source/";
    if (!ForceDirectory(sourceDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string watermarkDir = IncludeTrailingPathDelimiter(getHomePath())+"work/hgcode/webserver/watermark/";
    if (!ForceDirectory(watermarkDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string resourcekDir = IncludeTrailingPathDelimiter(getHomePath())+"work/hgcode/webserver/resource/";
    if (!ForceDirectory(resourcekDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    std::string logDir = IncludeTrailingPathDelimiter(getHomePath())+"work/hgcode/webserver/log/";
    if (!ForceDirectory(logDir)){
        LOG_ERROR<<"create rootDir fail";
        return false;
    }
    return false;
}

