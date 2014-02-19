
#include "HttpClientConcrete.h"

#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace openrtm_network_camera {
namespace utility {

HttpClientConcrete::HttpClientConcrete(void)
{
}

HttpClientConcrete::~HttpClientConcrete(void)
{
}

void HttpClientConcrete::doGet(const std::string& host_name, const std::string& path_name, const std::string& port) {
  ASSERT_EQ(std::string("127.0.0.1"), host_name);
  ASSERT_EQ(std::string("/test"), path_name);
  ASSERT_EQ(std::string("80"), port);

  status_code_ = 200;

  headers_.push_back(std::string("test 1"));
  headers_.push_back(std::string("test 2"));
  headers_.push_back(std::string("test 3"));

  content_type_ = "text/plain";
  content_length_ = 123;

  contents_ = "this is a test";
}

void HttpClientConcrete::setBasicAuthenticationParameter(const std::string& user, const std::string& password) {
  ASSERT_EQ(std::string("user"), user);
  ASSERT_EQ(std::string("password"), password);
}
void HttpClientConcrete::setTimeout(const long timeout) {
  ASSERT_EQ(10L, timeout);
}

} // utility
} // openrtm_network_camera
