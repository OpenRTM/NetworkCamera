
#include <string>

#include "gtest/gtest.h"

#include "HttpClientConcrete.h"

// �e�X�g�t�B�N�X�`��
class HttpClientConcreteTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::utility::HttpClientConcrete client;
};

// �ȉ��AHttpClientConcrete�N���X�̃e�X�g
// TimeoutBlockingClient �N���X�̃X�^�u�������g���A�������������Ă��邱�Ƃ��m�F
//
// �Ȃ��A�{�e�X�g�ŗp���Ă���TimeoutBlockingClient�̃X�^�u�����ł́A
// read_until�Ăяo�����ɍs����A�f���~�^�ȍ~�̃o�b�t�@�ւ̐�ǂ݂�͋[�ł��Ă��Ȃ��B
// ���̕����ɂ��ẮA�����e�X�g�ɂĉ摜�f�[�^���̃T�C�Y�̑傫�ȃf�[�^����Ȃ���M
// �ł��邱�ƂŊm�F����B

// ��ʂ̃��N�G�X�g
TEST_F(HttpClientConcreteTest, requestOkTest) {
  client.doGet("127.0.0.1", "/test", "80");

  // ���X�|���X�R�[�h
  ASSERT_EQ(200, client.getStatusCode());

  // �w�b�_
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(1, headers.size());
  ASSERT_EQ(std::string("Content-type: text/plain"), headers[0]);

  // �R���e���c�^�C�v
  ASSERT_EQ(std::string("text/plain"), client.getContentType());

  // �R���e���c��
  ASSERT_EQ(11, client.getContentLength());

  // �R���e���c
  const char * p = client.getContents();
  std::string str(p, p + client.getContentLength());
  ASSERT_EQ(std::string("Return: 0\r\n"), str);
}

// �F�؎w�肠��
TEST_F(HttpClientConcreteTest, requestOkWithBasicAuthTest) {
  client.setBasicAuthenticationParameter("user", "password");
  client.doGet("127.0.0.2", "/test", "80");

  // ���X�|���X�R�[�h
  ASSERT_EQ(200, client.getStatusCode());

  // �w�b�_
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(2, headers.size());
  ASSERT_EQ(std::string("Content-type: text/plain"), headers[0]);
  ASSERT_EQ(std::string("Content-length: 11"), headers[1]);

  // �R���e���c�^�C�v
  ASSERT_EQ(std::string("text/plain"), client.getContentType());

  // �R���e���c��
  ASSERT_EQ(11, client.getContentLength());

  // �R���e���c
  const char * p = client.getContents();
  std::string str(p, p + client.getContentLength());
  ASSERT_EQ(std::string("Return: 0\r\n"), str);
}

// �^�C���A�E�g�w�肠��
TEST_F(HttpClientConcreteTest, requestokWithTimeoutTest) {
  client.setTimeout(10);
  client.doGet("127.0.0.3", "/test", "80");

  // ���X�|���X�R�[�h
  ASSERT_EQ(200, client.getStatusCode());

  // �w�b�_
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(2, headers.size());
  ASSERT_EQ(std::string("Content-type: text/plain"), headers[0]);
  ASSERT_EQ(std::string("Content-length: 11"), headers[1]);

  // �R���e���c�^�C�v
  ASSERT_EQ(std::string("text/plain"), client.getContentType());

  // �R���e���c��
  ASSERT_EQ(11, client.getContentLength());

  // �R���e���c
  const char * p = client.getContents();
  std::string str(p, p + client.getContentLength());
  ASSERT_EQ(std::string("Return: 0\r\n"), str);
}

// ���X�|���X204
TEST_F(HttpClientConcreteTest, request204NoContentTest) {
  client.doGet("127.0.0.4", "/test", "80");

  // ���X�|���X�R�[�h
  ASSERT_EQ(204, client.getStatusCode());

  // �w�b�_
  std::vector<std::string> headers = client.getHeaders();
  ASSERT_EQ(5, headers.size());
  ASSERT_EQ(std::string("Content-length: 0"), headers[0]);
  ASSERT_EQ(std::string("Date: Tue, 18 Feb 2014 08:28:14 GMT"), headers[1]);
  ASSERT_EQ(std::string("Server: Boa/0.94.14rc21"), headers[2]);
  ASSERT_EQ(std::string("Accept-Ranges: bytes"), headers[3]);
  ASSERT_EQ(std::string("Connection: Keep-Alive"), headers[4]);

  // �R���e���c�^�C�v
  ASSERT_EQ(std::string(""), client.getContentType());

  // �R���e���c��
  ASSERT_EQ(0, client.getContentLength());

  // �R���e���c
  const char * p = client.getContents();
  ASSERT_EQ(NULL, p);
}

// ���X�|���X401
TEST_F(HttpClientConcreteTest, request401Test) {
  client.doGet("127.0.0.5", "/test", "80");

  // ���X�|���X�R�[�h
  ASSERT_EQ(401, client.getStatusCode());
}

// ��O����
TEST_F(HttpClientConcreteTest, exceptionTest) {
  client.doGet("127.0.0.6", "/test", "80");
  ASSERT_EQ(-1, client.getStatusCode());
}
