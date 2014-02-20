
#include "HttpClient.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace openrtm_network_camera {
namespace utility {

// ポート番号でテストを区別し、検証する内容を切り替える
namespace {
  int test_type = 0;

  std::string user;
  std::string password;
}

HttpClient::HttpClient(void)
{
}

HttpClient::~HttpClient(void)
{
}

// リクエストURLを検証する
void HttpClient::doGet(const char* p_host_name, const char* p_path_name, const char* p_port) {
  const std::string host = p_host_name;
  const std::string port = p_port;
  if (host == ""){
    ASSERT_EQ(std::string(""), port);
    return;
  }

  ASSERT_EQ(std::string("127.0.0.1"), host);

  // ポート番号からテスト番号を取得
  // テスト番号＝ポート番号－８０
  std::stringstream ss(port);
  ss >> test_type;
  test_type -= 80;
  ASSERT_LE(1, test_type);
  ASSERT_GE(115, test_type);

  std::cout << "test type:" << test_type << std::endl;

  // テスト番号に応じてAPIパスを検証
  switch(test_type) {
  case 1:
    ASSERT_STREQ("/Set?Func=Pan&Kind=0&DegMode=4", p_path_name);
    break;
  case 2:
    ASSERT_STREQ("/Set?Func=Pan&Kind=0&DegMode=6", p_path_name);
    break;
  case 3:
    ASSERT_STREQ("/Set?Func=Tilt&Kind=0&DegMode=8", p_path_name);
    break;
  case 4:
    ASSERT_STREQ("/Set?Func=Tilt&Kind=0&DegMode=2", p_path_name);
    break;
  case 5:
    ASSERT_STREQ("/Set?Func=Zoom&Kind=0&ZoomMode=4", p_path_name);
    break;
  case 6:
    ASSERT_STREQ("/Set?Func=Zoom&Kind=0&ZoomMode=6", p_path_name);
    break;
  case 7:
    ASSERT_STREQ("/Set?Func=Focus&Kind=0&FocusMode=4", p_path_name);
    break;
  case 8:
    ASSERT_STREQ("/Set?Func=Focus&Kind=0&FocusMode=6", p_path_name);
    break;
  case 9:
    ASSERT_STREQ("/Set?Func=Focus&Kind=0&FocusMode=5", p_path_name);
    break;
  case 10:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=0", p_path_name);
    break;
  case 11:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=32", p_path_name);
    break;
  case 12:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=48", p_path_name);
    break;
  case 13:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=64", p_path_name);
    break;
  case 14:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=80", p_path_name);
    break;
  case 15:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=16", p_path_name);
    break;
  case 16:
    ASSERT_STREQ("/nphControlCamera?Direction=Darker", p_path_name);
    break;
  case 17:
    ASSERT_STREQ("/nphControlCamera?Direction=Brighter", p_path_name);
    break;
  case 18:
    ASSERT_STREQ("/nphControlCamera?Direction=DefaultBrightness", p_path_name);
    break;
  case 19:
    ASSERT_STREQ("/Set?Func=Tilt&Kind=1&SetupType=0", p_path_name);
    break;
  case 20:
    ASSERT_STREQ("/Set?Func=Tilt&Kind=1&SetupType=1", p_path_name);
    break;
  case 21:
    ASSERT_STREQ("/Set?Func=PresetCnt&Kind=0", p_path_name);
    break;
  case 22:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=192x144&Quality=Motion", p_path_name);
    break;
  case 23:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=320x240&Quality=Clarity", p_path_name);
    break;
  case 24:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=640x480&Quality=Standard", p_path_name);
    break;
  case 25:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=1280x960&Quality=Standard", p_path_name);
    break;
  case 26:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=1280x1024&Quality=Standard", p_path_name);
    break;
  case 27:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=640x480&Quality=Motion", p_path_name);
    break;
  case 28:
    ASSERT_STREQ("/SnapshotJPEG?Resolution=320x240&Quality=Standard", p_path_name);
    break;
  case 29:
    ASSERT_STREQ("/Set?Func=Focus&Kind=0&FocusMode=5", p_path_name);
    break;
  case 30:
    ASSERT_STREQ("/Set?Func=CameraWB&Kind=1&Data=16", p_path_name);
    break;
  case 31:
    ASSERT_STREQ("/nphControlCamera?Direction=DefaultBrightness", p_path_name);
    break;
  case 32:
    ASSERT_STREQ("/Set?Func=Tilt&Kind=1&SetupType=0", p_path_name);
    break;
  case 33:
  case 34:
  case 35:
    break;
  default:
    FAIL();
  }

  // 認証周り
  if (2 == test_type) {
    ASSERT_EQ(std::string("user"), user);
    ASSERT_EQ(std::string("password"), password);
  } else {
    ASSERT_EQ(std::string(""), user);
    ASSERT_EQ(std::string(""), password);
  }

}

int HttpClient::getStatusCode() const {
  if (34 == test_type) {
    return 401;
  } else if (35 == test_type) {
    return -1;
  }
  return 200;
}

const char* const* HttpClient::getHeaders(int* p_size) {
  return NULL;
}

const char* HttpClient::getContents() const {
  if (21 == test_type) {
    return "Return: home\r\n";
  } else if (22 <= test_type && test_type < 28) {
    return "there is a image contents.\r\n";
  } else if (33 == test_type) {
    return "Return: -1\r\n";
  }
  return "Return: 0\r\n";
}

const char* HttpClient::getContentType() const {
  if ((16 <= test_type && test_type <= 18) || (31 == test_type)){
    return "text/html";
  } else if (22 <= test_type && test_type <= 28) {
    return "image/jpeg";
  }
  return "text/plain";
}

size_t HttpClient::getContentLength() const {
  if (21 == test_type) {
    return 14;
  } else if (22 <= test_type && test_type < 28) {
    return 28;
  } else if (33 == test_type) {
    return 12;
  }
  return 11;
}

void HttpClient::setBasicAuthenticationParameter(const char* p_user, const char* p_password) {
  user = p_user;
  password = p_password;
}

void HttpClient::setTimeout(const long timeout) {
}

} // utility
} // openrtm_network_camera
