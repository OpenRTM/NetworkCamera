
#include <string>

#include "gtest/gtest.h"

#include "HttpClientConcrete.h"

// テストフィクスチャ
class HttpClientConcreteTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::utility::HttpClientConcrete client;
};

// 以下、HttpClientConcreteクラスのテスト
// TimeoutBlockingClient クラスのスタブ実装を使い、正しく応答していることを確認
//
// なお、本テストで用いているTimeoutBlockingClientのスタブ実装では、
// read_until呼び出し時に行われる、デリミタ以降のバッファへの先読みを模擬できていない。
// この部分については、結合テストにて画像データ等のサイズの大きなデータを問題なく受信
// できることで確認する。

// 一般のリクエスト
TEST_F(HttpClientConcreteTest, requestOkTest) {
  client.doGet("127.0.0.1", "/test", "80");
  if (HasFatalFailure()) {
    FAIL();
  }

  // レスポンスコード
  ASSERT_EQ(200, client.getStatusCode());

  // ヘッダ
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(1, headers.size());
  ASSERT_EQ(std::string("Content-type: text/plain"), headers[0]);

  // コンテンツタイプ
  ASSERT_EQ(std::string("text/plain"), client.getContentType());

  // コンテンツ長
  ASSERT_EQ(11, client.getContentLength());

  // コンテンツ
  const char * p = client.getContents();
  std::string str(p, p + client.getContentLength());
  ASSERT_EQ(std::string("Return: 0\r\n"), str);
}

// 認証指定あり
TEST_F(HttpClientConcreteTest, requestOkWithBasicAuthTest) {
  client.setBasicAuthenticationParameter("user", "password");
  client.doGet("127.0.0.2", "/test", "80");
  if (HasFatalFailure()) {
    FAIL();
  }

  // レスポンスコード
  ASSERT_EQ(200, client.getStatusCode());

  // ヘッダ
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(2, headers.size());
  ASSERT_EQ(std::string("Content-type: text/plain"), headers[0]);
  ASSERT_EQ(std::string("Content-length: 11"), headers[1]);

  // コンテンツタイプ
  ASSERT_EQ(std::string("text/plain"), client.getContentType());

  // コンテンツ長
  ASSERT_EQ(11, client.getContentLength());

  // コンテンツ
  const char * p = client.getContents();
  std::string str(p, p + client.getContentLength());
  ASSERT_EQ(std::string("Return: 0\r\n"), str);
}

// タイムアウト指定あり
TEST_F(HttpClientConcreteTest, requestokWithTimeoutTest) {
  client.setTimeout(10);
  client.doGet("127.0.0.3", "/test", "80");
  if (HasFatalFailure()) {
    FAIL();
  }

  // レスポンスコード
  ASSERT_EQ(200, client.getStatusCode());

  // ヘッダ
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(2, headers.size());
  ASSERT_EQ(std::string("Content-type: text/plain"), headers[0]);
  ASSERT_EQ(std::string("Content-length: 11"), headers[1]);

  // コンテンツタイプ
  ASSERT_EQ(std::string("text/plain"), client.getContentType());

  // コンテンツ長
  ASSERT_EQ(11, client.getContentLength());

  // コンテンツ
  const char * p = client.getContents();
  std::string str(p, p + client.getContentLength());
  ASSERT_EQ(std::string("Return: 0\r\n"), str);
}

// レスポンス204
TEST_F(HttpClientConcreteTest, request204NoContentTest) {
  client.doGet("127.0.0.4", "/test", "80");
  if (HasFatalFailure()) {
    FAIL();
  }

  // レスポンスコード
  ASSERT_EQ(204, client.getStatusCode());

  // ヘッダ
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(5, headers.size());
  ASSERT_EQ(std::string("Content-length: 0"), headers[0]);
  ASSERT_EQ(std::string("Date: Tue, 18 Feb 2014 08:28:14 GMT"), headers[1]);
  ASSERT_EQ(std::string("Server: Boa/0.94.14rc21"), headers[2]);
  ASSERT_EQ(std::string("Accept-Ranges: bytes"), headers[3]);
  ASSERT_EQ(std::string("Connection: Keep-Alive"), headers[4]);

  // コンテンツタイプ
  ASSERT_EQ(std::string(""), client.getContentType());

  // コンテンツ長
  ASSERT_EQ(0, client.getContentLength());

  // コンテンツ
  const char * p = client.getContents();
  ASSERT_EQ(NULL, p);
}

// レスポンス401
TEST_F(HttpClientConcreteTest, request401Test) {
  client.doGet("127.0.0.5", "/test", "80");
  if (HasFatalFailure()) {
    FAIL();
  }

  // レスポンスコード
  ASSERT_EQ(401, client.getStatusCode());
}

// 例外発生
TEST_F(HttpClientConcreteTest, exceptionTest) {
  client.doGet("127.0.0.6", "/test", "80");
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(-1, client.getStatusCode());
}
