/*
 * httpHandler.cpp
 *
 *  Created on: 2019年11月18日
 *      Author: lyd
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include "httpHandler.h"
#include "util.h"

unsigned char ToHex(unsigned char x) {
	return x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x) {
	unsigned char y;
	if (x >= 'A' && x <= 'Z')
		y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z')
		y = x - 'a' + 10;
	else if (x >= '0' && x <= '9')
		y = x - '0';
	else
		assert(0);
	return y;
}
//application/x-www.form-url编码
std::string UrlEncode(const std::string &str) {
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++) {
		if (isalnum((unsigned char) str[i]) || (str[i] == '-')
				|| (str[i] == '_') || (str[i] == '.') || (str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else {
			strTemp += '%';
			strTemp += ToHex((unsigned char) str[i] >> 4);
			strTemp += ToHex((unsigned char) str[i] % 16);
		}
	}
	return strTemp;
}
//application/x-www.form-url解码
std::string UrlDecode(const std::string &str) {
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++) {
		if (str[i] == '+')
			strTemp += ' ';
		else if (str[i] == '%') {
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char) str[++i]);
			unsigned char low = FromHex((unsigned char) str[++i]);
			strTemp += high * 16 + low;
		} else
			strTemp += str[i];
	}
	return strTemp;
}

void SaveFile(const std::string &file_path, const std::string &file_content) {
	std::ifstream infile(file_path);
	if (infile) {
		infile.close();
		LOG(WARNING) << "file : " << file_path << " already exist";
		return;
	}
	infile.close();

	std::ofstream outfile;
	outfile.open(file_path);
	if (outfile.is_open()) {
		outfile << file_content;
		LOG(INFO) << "Save file " << file_path << " success";
	} else
		LOG(WARNING) << "Save file " << file_path << " fail";
	outfile.close();
}

void FormatBody(const std::string &body) {
	LOG(INFO) << body;
	//g++4.8 do not support regex very well, so we can not use it.
	std::string file_name_pat = "filename=\"";
	size_t start_pos = body.find(file_name_pat);
	if (start_pos == std::string::npos) {
		LOG(WARNING) << "Cannot find 'filename' key in body";
		return;
	}
	//start_pos is the pos of 'f', so we should add to the character after '"'
	start_pos += file_name_pat.size();

	size_t end_pos = body.find("\"", start_pos);
	if (end_pos == std::string::npos) {
		LOG(WARNING) << "Do not have '\"' in the end of filename";
		return;
	}
	std::string file_name = body.substr(start_pos, end_pos - start_pos);
	LOG(INFO) << "filename : " << file_name;

	std::string content_type_pat = "Content-Type:";
	start_pos = body.find("\r\n", end_pos + content_type_pat.size());
	if (start_pos == std::string::npos) {
		LOG(WARNING) << "Find character after Content-Type fail";
		return;
	}
	//skip the next empty row '\r\n', so there is two of '\r\n'
	start_pos += 4;

	end_pos = body.rfind("\r\n---");
	if (end_pos == std::string::npos && end_pos > start_pos) {
		LOG(WARNING) << "Find last '---' fail";
		return;
	}
	std::string file_content = body.substr(start_pos, end_pos - start_pos);
	LOG(INFO) << "file content : " << file_content;

	std::string file_path = "/tmp/source/" + file_name;
	SaveFile(file_path, file_content);
}
void httpHandler::getDefailtAvaterHandler(evpp::EventLoop* loop,
                    const evpp::http::ContextPtr& ctx,
                    const evpp::http::HTTPSendResponseCallback& cb) {

	    cb("getDefailtAvaterHandler");
}
void httpHandler::getDefailtFileUpload(evpp::EventLoop* loop,
                    const evpp::http::ContextPtr& ctx,
                    const evpp::http::HTTPSendResponseCallback& cb) {
    std::string head1 = ctx->FindRequestHeader("Content-Type");
  //  std::string headlength = ctx->FindRequestHeader("Content-Length");

    FormatBody(ctx->body().ToString());
   //  cb(headlength);
    cb("file upload success");
}
void httpHandler::getWaterMark(evpp::EventLoop* loop,
                    const evpp::http::ContextPtr& ctx,
                    const evpp::http::HTTPSendResponseCallback& cb) {

	 embedWatermark("/tmp/source/ce.pdf","/tmp/output/ce.pdf","11101010011110110000111101010011");
    cb("water success");
}

void httpHandler::getFileContent(evpp::EventLoop* loop,
                    const evpp::http::ContextPtr& ctx,
                    const evpp::http::HTTPSendResponseCallback& cb) {

	 std::string uri1 = ctx->original_uri();
	 std::string urivalue1 = ctx->FindQueryFromURI(uri1,"filename");

	 std::ifstream t("/tmp/output/cc.pdf");

	 ctx->AddResponseHeader("Content-Type", "application/pdf");
	 ctx->AddResponseHeader("Server", "evpp");
    std::stringstream buffer;
	 buffer << t.rdbuf();
	 std::string contents(buffer.str());
	 cb(contents);

}


