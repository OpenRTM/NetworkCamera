/*!
 * @file  HttpClientConcrete.cpp
 * @brief Http client using Boost.Asio
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * @date  2014-02-06
 */
#include "HttpClientConcrete.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <string>

#include <boost/asio.hpp>

#include "string_utility.h"


namespace openrtm_network_camera {
namespace utility {

// �萔��`
namespace {
  const char * CRLF = "\r\n";
  const char * CRLF2 = "\r\n\r\n";

  // �w�b�_���͏������ŏ�������
  const std::string ContentTypeHeader = "content-type";
  const std::string ContentLengthHeader = "content-length";
}

HttpClientConcrete::HttpClientConcrete(void)
    : user_(""),
      password_(""),
      status_code_(ERROR_CODE),
      headers_(),
      content_type_(""),
      content_length_(0),
      contents_(NULL) {
}

HttpClientConcrete::~HttpClientConcrete(void) {
  if (contents_ != NULL) {
    delete [] contents_;
    contents_ = NULL;
  }
}

void HttpClientConcrete::doGet(const std::string& host_name, const std::string& path_name, const std::string& port) {
  using boost::asio::ip::tcp;

  // ���X�|���X�p�̃����o�[�ϐ��̏�����
  response_member_init();

  try
  {
    boost::asio::io_service io_service;

    // Get a list of endpoints corresponding to the server name.
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(host_name, port);
    tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    // Try each endpoint until we successfully establish a connection.
    tcp::socket socket(io_service);
    boost::asio::connect(socket, endpoint_iterator);

    // Form the request. We specify the "Connection: close" header so that the
    // server will close the socket after transmitting the response. This will
    // allow us to treat all data up until the EOF as the content.
    boost::asio::streambuf request;
    std::ostream request_stream(&request);
    request_stream << "GET " << path_name << " HTTP/1.0" << CRLF;
    request_stream << "Host: " << host_name << ":" << port << CRLF;
    request_stream << "Accept: */*" << CRLF;
    request_stream << "User-Agent: " << "OpenRTM-NetworkCamera-HttpClient" << CRLF;

    // Basic�F��
    if (0 != user_.size() && 0 != password_.size()) {
      std::string auth = base64encode(user_ + ":" + password_);
      request_stream << "Authorization: Basic " << auth << CRLF;
    }

    request_stream << "Connection: close" << CRLF << CRLF;

    // TODO �^�C���A�E�g�͐ݒ�ł���H

    // Send the request.
    boost::asio::write(socket, request);

    // Read the response status line. The response streambuf will automatically
    // grow to accommodate the entire line. The growth may be limited by passing
    // a maximum size to the streambuf constructor.
    boost::asio::streambuf response;
    boost::asio::read_until(socket, response, CRLF);

    // Check that response is OK.
    std::istream response_stream(&response);
    std::string http_version;
    response_stream >> http_version;
    response_stream >> status_code_;
    std::string status_message;
    std::getline(response_stream, status_message);
    if (!response_stream || http_version.substr(0, 5) != "HTTP/")
    {
      std::cout << "Invalid response\n";
      status_code_ = ERROR_CODE;
      return;
    }
    if ((status_code_ != 200) && (status_code_ != 204))
    {
      std::cout << "Response returned with status code " << status_code_ << "\n";
      // �X�e�[�^�X�R�[�h OK�܂���No Content �ȊO�́A�w�b�_����͂��Ȃ�
      return;
    }

    // �w�b�_�̉��
    processHeaders(&socket, &response);

    setContentType();
    setContentLength();

    // �R���e���c�̎擾
    processContents(&socket, &response);
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
    status_code_ = ERROR_CODE;
  }
}

void HttpClientConcrete::setBasicAuthenticationParameter(const std::string& user, const std::string& password) {
  user_ = user;
  password_ = password;
}

void HttpClientConcrete::response_member_init() {
  status_code_ = ERROR_CODE;
  headers_.clear();
  content_type_.clear();
  content_length_ = 0;
  if (contents_ != NULL) {
    delete [] contents_;
    contents_ = NULL;
  }
}

void HttpClientConcrete::processHeaders(boost::asio::ip::tcp::socket* p_socket, boost::asio::streambuf* p_response) {
  headers_.clear();

  std::istream response_stream(p_response);

  // Read the response headers, which are terminated by a blank line.
  boost::asio::read_until(*p_socket, *p_response, CRLF2);

  // Process the response headers.
  std::string header;
  while (std::getline(response_stream, header) && header != "\r") {
    std::string h = header;

    std::string::size_type pos = h.find_last_of("\r");
    if (std::string::npos != pos) {
      h = h.substr(0, pos);
    }
    headers_.push_back(h);
  }
}

void HttpClientConcrete::setContentType() {
  content_type_.clear();

  // Content-Type �w�b�_�̎擾
  for(std::vector<std::string>::iterator iter = headers_.begin(); iter != headers_.end(); ++iter) {
    std::string t = convertToLower((*iter).substr(0, ContentTypeHeader.size()));
    if (t == ContentTypeHeader) {
      std::string type = (*iter).substr(ContentTypeHeader.size());

      content_type_ = getHeaderValue(type);
      break;
    }
  }
}

/*!
 * @brief �R���e���c����ݒ肷��B
 *
 * �w�b�_�� Content-Length �ɋL�ڂ̃R���e���c�����擾����B
 *
 * @caution
 * Content-Length 0�܂��͂Ȃ��ꍇ�ɂ�����炸�A�R���e���c�f�[�^������΁A
 * HttpClientConcrete#processContents �̏������ɐ������R���e���c�����ݒ肳���B
 * 
 * @return �R���e���c��
 */
void HttpClientConcrete::setContentLength() {
  content_length_ = 0;

  // Content-Length �w�b�_�̎擾
  for(std::vector<std::string>::iterator iter = headers_.begin(); iter != headers_.end(); ++iter) {
    std::string t = convertToLower((*iter).substr(0, ContentLengthHeader.size()));
    if (t == ContentLengthHeader) {
      std::string type = (*iter).substr(ContentLengthHeader.size());

      std::string tmp = getHeaderValue(type);
      content_length_ = ::atoi(tmp.c_str());
      break;
    }
  }
}

/*!
 * @breif �R���e���c�̏����B
 *
 * ���X�|���X�f�[�^���������āA�R���e���c�����o���B
 *
 * @caution
 * �R���e���c����0�̏ꍇ�ł��A���ۂ̃f�[�^������΂�����ɏ]���A
 * �R���e���c�����Đݒ肷��B
 *
 * @param p_socket    socket�ւ̃|�C���^
 * @param p_response  ���X�|���X�����p��streambuf
 */
void HttpClientConcrete::processContents(boost::asio::ip::tcp::socket* p_socket, boost::asio::streambuf* p_response) {
  if (contents_ != NULL) {
    delete [] contents_;
    contents_ = NULL;
  }

  // �R���e���c�T�C�Y�̊m�F
  const size_t length = getContentLength();
  if (0 == length) {
    std::cout << "Maybe no Content-Length header.\n";
  }

  // �ꎞ�o�b�t�@�ɓǂݍ��ݍς݃f�[�^���o��
  char * buf_pre = NULL;
  size_t pre_readed = p_response->size();
  if (pre_readed > 0) {
    buf_pre = new char [pre_readed];
    p_response->commit(pre_readed);
    memcpy(buf_pre, boost::asio::buffer_cast<const char*>(p_response->data()), pre_readed);
    p_response->consume(pre_readed);
  }

  // Read until EOF, writing data to output as we go.
  boost::system::error_code error;
  size_t bytes = boost::asio::read(*p_socket, *p_response, boost::asio::transfer_all(), error);
  if (error != boost::asio::error::eof) {
    if (NULL != buf_pre) {
      delete [] buf_pre;
      buf_pre = NULL;
    }

    status_code_ = ERROR_CODE;
    return;
  }

  // ���b�Z�[�W�{�f�B���̃`�F�b�N
  if (0 == length) {
    content_length_ = pre_readed + bytes;

    // ���b�Z�[�W�{�f�B�ɉ����Ȃ������ꍇ
    if (0 == content_length_) {
      std::cout << "Content Length is 0.\n";
      return;
    }

  } else if ((pre_readed + bytes) != length) {
    if (NULL != buf_pre) {
      delete [] buf_pre;
      buf_pre = NULL;
    }

    std::cout << "Content Length maybe invalid.\n";
    status_code_ = ERROR_CODE;
    return;
  }

  // �R���e���c�ۑ��̈�̊m��
  contents_ = new char [pre_readed + bytes];

  // �R���e���c�̕ۑ�
  if (NULL != buf_pre) {
    memcpy(contents_, buf_pre, pre_readed);
    delete [] buf_pre;
    buf_pre = NULL;
  }

  if (0 >= bytes) {
    return;
  }

  p_response->commit(bytes);
  memcpy(contents_ + pre_readed, boost::asio::buffer_cast<const char*>(p_response->data()), bytes);

}

std::string HttpClientConcrete::getHeaderValue(const std::string& target) {
  std::string::size_type pos = target.find(":");

  if (pos != std::string::npos) {
    return trim(target.substr(pos+1));
  }  
  return std::string(target);
}

} // utility
} // openrtm_network_camera
