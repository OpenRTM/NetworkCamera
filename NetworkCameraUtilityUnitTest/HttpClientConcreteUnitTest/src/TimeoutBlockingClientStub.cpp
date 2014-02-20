
#include "TimeoutBlockingClient.h"

#include <boost/asio.hpp>

#include "gtest/gtest.h"

namespace openrtm_network_camera {
namespace utility {

namespace {
  int test_type = 0;

  // テスト1, Content-Lengthヘッダなし
  const std::string response1 = "HTTP/1.0 200 OK\r\n"
                                "Content-type: text/plain\r\n"
                                "\r\n"
                                "Return: 0\r\n";

  // テスト2, 正しいヘッダ
  const std::string response2 = "HTTP/1.0 200 OK\r\n"
                                "Content-Type: text/plain\r\n"
                                "Content-Length: 11\r\n"
                                "\r\n"
                                "Return: 0\r\n";
  // テスト3, ヘッダ名が小文字
  const std::string response3 = "HTTP/1.0 200 OK\r\n"
                                "Content-type: text/plain\r\n"
                                "Content-length: 11\r\n"
                                "\r\n"
                                "Return: 0\r\n";

  //const std::string response4 = "";

  // テスト5, Content-Length < 実際のコンテンツサイズ
  const std::string response5 = "HTTP/1.0 200 OK\r\n"
                                "Content-type: text/plain\r\n"
                                "Content-length: 4\r\n"
                                "\r\n"
                                "Return: 0\r\n";
  // テスト6, Content-Length > 実際のコンテンツサイズ
  const std::string response6 = "HTTP/1.0 200 OK\r\n"
                                "Content-type: text/plain\r\n"
                                "Content-length: 20\r\n"
                                "\r\n"
                                "Return: 0\r\n";
  // テスト7, status code 204
  const std::string response7 = "HTTP/1.0 204 No Content\r\n"
                                "Content-length: 0\r\n"
                                "Date: Tue, 18 Feb 2014 08:28:14 GMT\r\n"
                                "Server: Boa/0.94.14rc21\r\n"
                                "Accept-Ranges: bytes\r\n"
                                "Connection: Keep-Alive\r\n"
                                "\r\n";
  // テスト8, status code 401
  const std::string response8 = "HTTP/1.0 401 Unauthorized\r\n"
                                "\r\n";

  std::string response;
}

TimeoutBlockingClient::TimeoutBlockingClient()
    : io_service_(),
      socket_(io_service_),
      deadline_(io_service_),
      input_buffer_() {
}
TimeoutBlockingClient::~TimeoutBlockingClient() {
}

void TimeoutBlockingClient::connect(const std::string& host, const std::string& service, boost::posix_time::time_duration timeout) {
  ASSERT_EQ(std::string("127.0.0.1"), host);

  // ポート番号よりテスト番号を取得する
  std::stringstream ss(service);
  ss >> test_type;

  switch(test_type) {
  case 1:
  case 2:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
    ASSERT_EQ(60, timeout.total_seconds());
    break;
  case 3:
    ASSERT_EQ(10, timeout.total_seconds());
    break;
  case 9:
    std::cout << "exception throws from stub.\n";
    throw std::exception("exception throws from stub connect");
    break;
  default:
    FAIL();
  }
}

size_t TimeoutBlockingClient::read(boost::posix_time::time_duration timeout) {

  // タイムアウト時間の確認
  //   戻り値があるので省略
  // http://opencv.jp/googletestdocs/FAQ.html#void-value-not-ignored-as-it-ought-to-be

  std::ostream os(&input_buffer_);

  size_t s = response.size();

  std::cout << "debug read: response size:" << s << std::endl;
  std::cout << "debug read: response:" << response << "(end of response)\n";

  os << response;
  response = "";
  return s;
}

size_t TimeoutBlockingClient::read_until(const std::string& delimiter, boost::posix_time::time_duration timeout) {

  // タイムアウト時間の確認
  //   戻り値があるので省略
  // http://opencv.jp/googletestdocs/FAQ.html#void-value-not-ignored-as-it-ought-to-be

  std::ostream os(&input_buffer_);

  size_t pos;
  size_t s;
  if (std::string::npos != (pos = response.find(delimiter))) {
    s = pos + delimiter.size();

    std::cout << "debug read_until: response size:" << response.size() << std::endl;
    std::cout << "debug read_until: delimilter pos:" << pos << ", end of substr pos:" << s << std::endl;
    std::cout << "debug read_until: substr:" << response.substr(0, s) << std::endl;

    os << response.substr(0, s);
    response = response.substr(s);
  } else {
    std::cout << "unexpected condition\n";
    throw std::exception();
  }
  std::cout << "debug read_until: new response:" << response << "(end of response)\n";
  return pos;
}

void TimeoutBlockingClient::write(boost::asio::streambuf& buf, boost::posix_time::time_duration timeout) {
  // streambuf の中身をチェック
  std::istream is(&buf);

  std::string request;
  std::getline(is, request);
  ASSERT_EQ(std::string("GET /test HTTP/1.0\r"), request);

  std::ostringstream os;
  os << test_type;
  std::getline(is, request);
  ASSERT_EQ(std::string("Host: 127.0.0.1:" + os.str() + "\r"), request);

  std::getline(is, request);
  ASSERT_EQ(std::string("Accept: */*\r"), request);

  std::getline(is, request);
  ASSERT_EQ(std::string("User-Agent: OpenRTM-NetworkCamera-HttpClient\r"), request);

  if (2 == test_type) {
    std::getline(is, request);
    ASSERT_EQ(std::string("Authorization: Basic dXNlcjpwYXNzd29yZA==\r"), request); // user:passwordのbase64エンコーディング
  }

  std::getline(is, request);
  ASSERT_EQ(std::string("Connection: close\r"), request);

  // タイムアウト時間の確認
  if (3 == test_type) {
    ASSERT_EQ(10, timeout.total_seconds());
  } else {
    ASSERT_EQ(60, timeout.total_seconds());
  }

  // 応答データを設定する
  input_buffer_.consume(input_buffer_.size());

  switch(test_type) {
  case 1:
    response = response1;
    break;
  case 2:
    response = response2;
    break;
  case 3:
    response = response3;
    break;
  case 4:
    //response = response4;
    break;
  case 5:
    response = response5;
    break;
  case 6:
    response = response6;
    break;
  case 7:
    response = response7;
    break;
  case 8:
    response = response8;
    break;
  default:
    FAIL();
  }

}

} // utility
} // openrtm_network_camera