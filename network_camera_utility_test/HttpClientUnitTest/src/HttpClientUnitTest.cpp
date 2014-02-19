
#include <string>

#include "gtest/gtest.h"

#include "HttpClient.h"

// テストフィクスチャ
class HttpClientTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::utility::HttpClient client;
};

// 以下、HttpClientクラスのテスト
// 実際の処理クラス HttpClientConcrete を正しく呼び出していることを確認

TEST_F(HttpClientTest, doGetTest) {
  client.doGet("127.0.0.1", "/test", "80");
}

TEST_F(HttpClientTest, getStatusCodeTest) {
  client.doGet("127.0.0.1", "/test", "80");
  ASSERT_EQ(200, client.getStatusCode());
}

TEST_F(HttpClientTest, getHeadersTest) {
  client.doGet("127.0.0.1", "/test", "80");
  int length;
  const char* const* headers = client.getHeaders(&length);

  ASSERT_EQ(3, length);

  ASSERT_STREQ("test 1", headers[0]);
  ASSERT_STREQ("test 2", headers[1]);
  ASSERT_STREQ("test 3", headers[2]);
}

TEST_F(HttpClientTest, getContentTypeTest) {
  client.doGet("127.0.0.1", "/test", "80");
  ASSERT_STREQ("text/plain", client.getContentType());
}

TEST_F(HttpClientTest, getContentLengthTest) {
  client.doGet("127.0.0.1", "/test", "80");
  ASSERT_EQ(123, client.getContentLength());
}

TEST_F(HttpClientTest, getContentsTest) {
  client.doGet("127.0.0.1", "/test", "80");
  ASSERT_STREQ("this is a test", client.getContents());
}

TEST_F(HttpClientTest, setBasicAuthenticationParameterTest) {
  client.setBasicAuthenticationParameter("user", "password");
}

TEST_F(HttpClientTest, setTimeoutTest) {
  client.setTimeout(10);
}
