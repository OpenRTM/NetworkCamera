
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
  std::stringstream ss(port);
  ss >> test_type;
  std::cout << "test type:" << test_type << std::endl;

  // テスト番号に応じてAPIパスを検証
  switch(test_type) {
  case 1:
  case 54:
  case 55:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0405", p_path_name);
    break;
  case 2:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0401", p_path_name);
    break;
  case 3:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0403", p_path_name);
    break;
  case 4:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0410", p_path_name);
    break;
  case 5:
  case 56:
  case 57:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0605", p_path_name);
    break;
  case 6:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0601", p_path_name);
    break;
  case 7:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0603", p_path_name);
    break;
  case 8:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0610", p_path_name);
    break;
  case 9:
  case 58:
  case 59:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0805", p_path_name);
    break;
  case 10:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0801", p_path_name);
    break;
  case 11:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0803", p_path_name);
    break;
  case 12:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0810", p_path_name);
    break;
  case 13:
  case 60:
  case 61:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0205", p_path_name);
    break;
  case 14:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0201", p_path_name);
    break;
  case 15:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0203", p_path_name);
    break;
  case 16:
    ASSERT_STREQ("/command/ptzf.cgi?relative=0210", p_path_name);
    break;
  case 17:
  case 62:
  case 63:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1105", p_path_name);
    break;
  case 18:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1101", p_path_name);
    break;
  case 19:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1103", p_path_name);
    break;
  case 20:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1110", p_path_name);
    break;
  case 21:
  case 64:
  case 65:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1005", p_path_name);
    break;
  case 22:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1001", p_path_name);
    break;
  case 23:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1003", p_path_name);
    break;
  case 24:
    ASSERT_STREQ("/command/ptzf.cgi?relative=1010", p_path_name);
    break;
  case 25:
    {
      // 一回のテスト中の呼び出し回数, フォーカス制御の場合２回呼ぶため
      static int request = 0;
      if (0 == request) {
        ASSERT_STREQ("/command/ptzf.cgi?move=near,1", p_path_name);
      } else if (1 == request) {
        ASSERT_STREQ("/command/ptzf.cgi?move=stop,focus", p_path_name);
      } else {
        FAIL();
      }
      ++request;
    }
    break;
  case 26:
    {
      // 一回のテスト中の呼び出し回数, フォーカス制御の場合２回呼ぶため
      static int request = 0;
      if (0 == request) {
        ASSERT_STREQ("/command/ptzf.cgi?move=far,1", p_path_name);
      } else if (1 == request) {
        ASSERT_STREQ("/command/ptzf.cgi?move=stop,focus", p_path_name);
      } else {
        FAIL();
      }
      ++request;
    }
    break;
  case 27:
    {
      // 一回のテスト中の呼び出し回数, フォーカス制御の場合２回呼ぶため
      static int request = 0;
      if (0 == request) {
        ASSERT_STREQ("/command/ptzf.cgi?move=onepushaf,1", p_path_name);
      } else {
        FAIL();
      }
      ++request;
    }
    break;
  case 28:
  case 50:
    ASSERT_STREQ("/command/camera.cgi?wbmode=auto", p_path_name);
    break;
  case 29:
    ASSERT_STREQ("/command/camera.cgi?wbmode=indoor", p_path_name);
    break;
  case 30:
    ASSERT_STREQ("/command/camera.cgi?wbmode=outdoor", p_path_name);
    break;
  case 31:
    ASSERT_STREQ("/command/camera.cgi?wbmode=onepushwb", p_path_name);
    break;
  case 32:
  case 51:
  case 52:
    ASSERT_STREQ("/command/camera.cgi?brightness=5", p_path_name);
    break;
  case 33:
    ASSERT_STREQ("/command/camera.cgi?brightness=0", p_path_name);
    break;
  case 34:
    ASSERT_STREQ("/command/camera.cgi?brightness=3", p_path_name);
    break;
  case 35:
    ASSERT_STREQ("/command/camera.cgi?brightness=10", p_path_name);
    break;
  case 36:
  case 53:
    ASSERT_STREQ("/command/camera.cgi?eflip=off", p_path_name);
    break;
  case 37:
    ASSERT_STREQ("/command/camera.cgi?eflip=on", p_path_name);
    break;
  case 38:
    ASSERT_STREQ("/command/presetposition.cgi?homepos=ptz-recall", p_path_name);
    break;
  case 39:
    ASSERT_STREQ("/jpeg/qqvga.jpg", p_path_name);
    break;
  case 40:
    ASSERT_STREQ("/jpeg/qvga.jpg", p_path_name);
    break;
  case 41:
  case 46:
    ASSERT_STREQ("/jpeg/vga.jpg", p_path_name);
    break;
  case 42:
  case 47:
  case 48:
    ASSERT_STREQ("/command/camera.cgi?jpquality=5", p_path_name);
    break;
  case 43:
    ASSERT_STREQ("/command/camera.cgi?jpquality=1", p_path_name);
    break;
  case 44:
    ASSERT_STREQ("/command/camera.cgi?jpquality=3", p_path_name);
    break;
  case 45:
    ASSERT_STREQ("/command/camera.cgi?jpquality=10", p_path_name);
    break;
  case 49:
    // case 27 と検証対象は同じだが、呼び出し回数を記録する必要があるのでケースを分ける
    {
      // 一回のテスト中の呼び出し回数, フォーカス制御の場合２回呼ぶため
      static int request = 0;
      if (0 == request) {
        ASSERT_STREQ("/command/ptzf.cgi?move=onepushaf,1", p_path_name);
      } else {
        FAIL();
      }
      ++request;
    }
    break;
  case 66:
  case 67:
    break;
  default:
    FAIL();
  }

  // 認証周り
  if (5 == test_type) {
    ASSERT_EQ(std::string("user"), user);
    ASSERT_EQ(std::string("password"), password);
  } else {
    ASSERT_EQ(std::string(""), user);
    ASSERT_EQ(std::string(""), password);
  }

}

int HttpClient::getStatusCode() const {
  if ((39 <= test_type && test_type <= 41) || (46 == test_type)) {
    return 200;
  } else if (66 == test_type) {
    return 401;
  } else if (67 == test_type) {
    return -1;
  }
  return 204;
}

const char* const* HttpClient::getHeaders(int* p_size) {
  return NULL;
}

const char* HttpClient::getContents() const {
  if ((39 <= test_type && test_type <= 41) || (46 == test_type)) {
    return "there is a image contents.\r\n";
  }
  return NULL;
}

const char* HttpClient::getContentType() const {
  if ((39 <= test_type && test_type <= 41) || (46 == test_type)) {
    return "image/jpeg";
  }
  return "";
}

size_t HttpClient::getContentLength() const {
  if ((39 <= test_type && test_type <= 41) || (46 == test_type)) {
    return 28;
  }
  return 0;
}

void HttpClient::setBasicAuthenticationParameter(const char* p_user, const char* p_password) {
  user = p_user;
  password = p_password;
}

void HttpClient::setTimeout(const long timeout) {
}

} // utility
} // openrtm_network_camera
