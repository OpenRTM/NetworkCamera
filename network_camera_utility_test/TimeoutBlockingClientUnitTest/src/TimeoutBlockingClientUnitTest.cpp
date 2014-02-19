
#include <string>

#include "gtest/gtest.h"

#include "TimeoutBlockingClient.h"

// テストフィクスチャ
class TimeoutBlockingClientTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::utility::TimeoutBlockingClient client;
};

// 以下、TimeoutBlockingClientクラスのテスト
// Linux上でサーバーを立ててからテストを実行する
// また、サーバー側の応答処理を変更する必要があるので、テストケースは個別に実行すること

// 通常のリクエスト
// レスポンスデータが、read_until実行時にstreambufに先読みされるサイズ（バッファサイズ）
// に含まれる程度に小さいことを想定
//
// サーバー側の想定：cat response.txt | nc -l 8080
TEST_F(TimeoutBlockingClientTest, requestOkTest) {

  boost::posix_time::time_duration td = boost::posix_time::seconds(60);
  client.connect("192.168.0.28", "8080", td); // テストサーバーに応じて変更

  // 送信テスト
  // 標準出力で確認する
  const std::string send_str = "Test request\r\n"
                               "this is a dummy request to netcat(nc) command as a http server.\r\n"
                               "end\r\n";

  boost::asio::streambuf buf;
  std::ostream os(&buf);
  os << send_str;

  client.write(buf, td);
  std::cout << "send str:\n" << send_str << std::endl;

  // 受信テスト
  // 想定するテキストの受信を確認する
  size_t s = client.read_until("\r\n", td);
  ASSERT_EQ(17, s);

  boost::asio::streambuf& input_buf = client.getStreambuf();

  std::cout << "readed size:" << s << ", buffer size:" << input_buf.size() << std::endl;
  {
    std::string msg;
    std::istream is(&input_buf);
    std::getline(is, msg);
    ASSERT_EQ(std::string("HTTP/1.0 200 OK\r"), msg);
  }

  // ヘッダデータの確認
  s = client.read_until("\r\n\r\n", td);
  std::cout << "readed size:" << s << ", buffer size:" << input_buf.size() << std::endl;
  {
    std::string msg;
    std::istream is(&input_buf);
    std::getline(is, msg);
    ASSERT_EQ(std::string("Content-length: 11\r"), msg);

    std::getline(is, msg);
    ASSERT_EQ(std::string("Accept-Ranges: bytes\r"), msg);

    std::getline(is, msg);
    ASSERT_EQ(std::string("Connection: Keep-Alive\r"), msg);

    std::getline(is, msg);
    ASSERT_EQ(std::string("\r"), msg);
  }

  // コンテンツの確認
  std::string msg;
  s = input_buf.size();
  if (s > 0) {
    std::cout << "remained data size:" << s << std::endl;
    const char* st = boost::asio::buffer_cast<const char*>(input_buf.data());
    msg = std::string(st, st + input_buf.size());
    input_buf.consume(input_buf.size());
  }

  s = client.read(td);  // read で読み込みデータがない
  EXPECT_EQ(0, s);

  std::cout << "additional read data size:" << s << std::endl;
  std::string msg2;
  if (s > 0) {
    const char* st = boost::asio::buffer_cast<const char*>(input_buf.data());
    msg2 = std::string(st, st + input_buf.size());
    input_buf.consume(input_buf.size());
  }

  msg = msg + msg2;
  ASSERT_EQ(std::string("Return: 0\r\n"), msg);
}

// readメソッドの確認
// レスポンスデータが、read_until実行時にstreambufに先読みされるサイズ（バッファサイズ）
// よりも大きいことを想定
//
// サーバー側の想定：cat response_read_test.txt | nc -l 8080
TEST_F(TimeoutBlockingClientTest, readMethodTest) {

  boost::posix_time::time_duration td = boost::posix_time::seconds(60);
  client.connect("192.168.0.28", "8080", td); // テストサーバーに応じて変更

  // 送信テスト
  // 標準出力で確認する
  const std::string send_str = "Test requestfor read\r\n";

  boost::asio::streambuf buf;
  std::ostream os(&buf);
  os << send_str;

  client.write(buf, td);
  std::cout << "send str:\n" << send_str << std::endl;

  // 受信テスト
  // 想定するテキストの受信を確認する
  size_t s = client.read_until("\r\n", td);
  ASSERT_EQ(17, s);

  boost::asio::streambuf& input_buf = client.getStreambuf();

  std::cout << "readed size:" << s << ", buffer size:" << input_buf.size() << std::endl;
  {
    std::string msg;
    std::istream is(&input_buf);
    std::getline(is, msg);
    ASSERT_EQ(std::string("HTTP/1.0 200 OK\r"), msg);
  }

  // コンテンツの確認
  std::string msg;
  s = input_buf.size();
  if (s > 0) {
    std::cout << "remained data size:" << s << std::endl;
    const char* st = boost::asio::buffer_cast<const char*>(input_buf.data());
    msg = std::string(st, st + input_buf.size());
    input_buf.consume(input_buf.size());
  }

  s = client.read(td);  // read で読み込みデータがある
  EXPECT_LT(0, s);

  std::cout << "additional read data size:" << s << std::endl;
  std::string msg2;
  if (s > 0) {
    const char* st = boost::asio::buffer_cast<const char*>(input_buf.data());
    msg2 = std::string(st, st + input_buf.size());
    input_buf.consume(input_buf.size());
  }

  msg = msg + msg2;
  std::cout << msg;

  const std::string correct =
    "Content-length: 11\r\n"
    "Accept-Ranges: bytes\r\n"
    "Connection: Keep-Alive\r\n"
    "\r\n"
    "OpenRTM-aist official website\r\n"
    "\r\n"
    "openrtm.org is the official website of OpenRTM-aist, an open source robotic technology middleware which is developed and distributed by Japan's National Institute of Advanced Industrial Science and Technology.\r\n"
    "openrtm-1.1.0-download.png\r\n"
    "\r\n"
    "OpenRTM-aist Version 1.1.0 has been released\r\n"
    "\r\n"
    "The latest release version is OpenRTM-aist-1.1.0-RELEASE. Source and binary packages for Linux and Windows are available from here. Current versions for each language are:\r\n"
    "\r\n"
    "    C++: 1.1.0-RELEASE\r\n"
    "    Python: 1.0.0-RELEASE\r\n"
    "    Java: 1.0.0-RELEASE\r\n"
    "    tools: 1.0.0-RELEASE\r\n"
    "\r\n"
    "\r\n"
    "The Windows installer package available from the link to the right includes all of the libraries, dependencies and tools required to try the example components. Please see \"Let's start OpenRTM-aist in ten minutes\" after it downloads it. Have fun!\r\n";
  ASSERT_EQ(correct, msg);
}

// タイムアウト
// サーバー側の想定：nc -l 8080
TEST_F(TimeoutBlockingClientTest, requestTimeoutTest) {

  boost::posix_time::time_duration td = boost::posix_time::seconds(5);
  client.connect("192.168.0.28", "8080", td);

  const std::string send_str = "server not respond\r\n";
  boost::asio::streambuf buf;
  std::ostream os(&buf);
  os << send_str;

  client.write(buf, td);
  std::cout << "send str:\n" << send_str << std::endl;

  ASSERT_ANY_THROW(client.read_until("\r\n", td));
}
