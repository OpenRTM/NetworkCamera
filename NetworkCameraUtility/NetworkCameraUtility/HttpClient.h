//
// http_client.h
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
// Boost.Asio のサンプルを元に記述 http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp03/http/client/sync_client.cpp
//

#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "utility_dll_defs.h"

namespace openrtm_network_camera {
namespace utility {

//// クラスが内部にSTLを持ち、dllエクスポートする場合に必要
//// これらがないと warning C4251 が出る
//// @see http://support.microsoft.com/default.aspx?scid=kb;ja-jp;168958
//template class NETWORKCAMERAUTILITY_API std::allocator<char>;
//template class NETWORKCAMERAUTILITY_API std::allocator<std::string>;
//template class NETWORKCAMERAUTILITY_API std::basic_string<char>;
//template class NETWORKCAMERAUTILITY_API std::vector<std::string>;


/**
 *
 */
class NETWORKCAMERAUTILITY_API HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);

	void doGet(const std::string& host_name, const std::string& path_name);

  int getStatusCode() const { return status_code_; }

  std::vector<std::string> getHeaders() const { return headers_; }

  // 呼び出し側で開放しない
  const char* getContents() const { return contents_; }

  std::string getContentType() const { return content_type_; }

  size_t getContentLength() const { return content_length_; }

  void setBasicAuthenticationParameter(const std::string& user, const std::string& password);

protected:
private:
  void response_member_init();
  void processHeaders(boost::asio::ip::tcp::socket* p_socket, boost::asio::streambuf* p_response);
  void setContentType();
  void setContentLength();
  void processContents(boost::asio::ip::tcp::socket* p_socket, boost::asio::streambuf* p_response);

  std::string getHeaderValue(const std::string& target);

  const static int ERROR_CODE = -1;

  // リクエスト
  std::string user_;
  std::string password_;

  // レスポンス
	int status_code_; // HTTP問い合わせの戻り値、エラー発生時は-1とする
	std::vector<std::string> headers_;
  std::string content_type_;
  size_t content_length_;
  char* contents_;

	HttpClient(const HttpClient&);
	void operator=(const HttpClient&);
};

} // utility
} // openrtm_network_camera

#endif