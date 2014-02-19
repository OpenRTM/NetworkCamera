
#include <string>

#include "gtest/gtest.h"

#include "string_utility.h"

// convertToLower
TEST(ConvertToLowerTest, StringToLowerTest) {
  ASSERT_EQ(std::string("test"), openrtm_network_camera::utility::convertToLower("Test"));
  ASSERT_EQ(std::string("host name"), openrtm_network_camera::utility::convertToLower("Host Name"));
  ASSERT_EQ(std::string(" ## caution!! this is a 1st test ## "), openrtm_network_camera::utility::convertToLower(" ## CAUTION!! THIS IS A 1st TEST ## "));
}
TEST(ConvertToLowerTest, EmptyStringTest) {
  ASSERT_EQ(std::string(""), openrtm_network_camera::utility::convertToLower(""));
}

// trim
TEST(TrimTest, PostTrimTest) {
  ASSERT_EQ(std::string("Test"), openrtm_network_camera::utility::trim("Test "));
  ASSERT_EQ(std::string("Test2"), openrtm_network_camera::utility::trim("Test2   "));
}
TEST(TrimTest, PreTrimTest) {
  ASSERT_EQ(std::string("Host Name"), openrtm_network_camera::utility::trim(" Host Name"));
  ASSERT_EQ(std::string("Host Name2"), openrtm_network_camera::utility::trim("  Host Name2"));
}
TEST(TrimTest, BothTrimTest) {
  ASSERT_EQ(std::string("dummy test"), openrtm_network_camera::utility::trim(" dummy test "));
  ASSERT_EQ(std::string("dummy test"), openrtm_network_camera::utility::trim("  dummy test  "));
  ASSERT_EQ(std::string("Today is chilly."), openrtm_network_camera::utility::trim(" Today is chilly.\t "));
  ASSERT_EQ(std::string("There are much snow."), openrtm_network_camera::utility::trim(" \n There are much snow.\r \n \r\n"));
}
TEST(TrimTest, EmptyStringTest) {
  ASSERT_EQ(std::string(""), openrtm_network_camera::utility::trim("     "));
  ASSERT_EQ(std::string(""), openrtm_network_camera::utility::trim("  \n   "));
}

// base64encode
// エンコード後も文字列は、下記のコマンドで求めた
//   echo -n ABC | base64
TEST(Base64EncodeTest, Encode6bitTest) {
  ASSERT_EQ(std::string("QUJD"), openrtm_network_camera::utility::base64encode("ABC"));      // 6bit分割で余りなし
  ASSERT_EQ(std::string("QUJDRA=="), openrtm_network_camera::utility::base64encode("ABCD")); // 6bit分割で余りあり
}
TEST(Base64EncodeTest, Encode4charactersTest) {
  ASSERT_EQ(std::string("QUJD"), openrtm_network_camera::utility::base64encode("ABC"));       // 4文字変換で余りなし
  ASSERT_EQ(std::string("QUJDRA=="), openrtm_network_camera::utility::base64encode("ABCD"));  // 4文字変換で余り2
  ASSERT_EQ(std::string("QUJDREU="), openrtm_network_camera::utility::base64encode("ABCDE")); // 4文字変換で余り1
}
TEST(Base64EncodeTest, EmptyStringTest) {
  ASSERT_EQ(std::string(""), openrtm_network_camera::utility::base64encode(""));
}
