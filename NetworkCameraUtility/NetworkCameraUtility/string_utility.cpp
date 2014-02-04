
#include "string_utility.h"

//#include <ctype.h>

#include <algorithm>
#include <string>
#include <sstream>

#include <boost/serialization/pfto.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

namespace openrtm_network_camera {
namespace utility {

std::string convertToLower(const std::string& target) {
  std::string t = target;
  std::transform(t.begin(), t.end(), t.begin(), ::tolower);
  return t;
}

std::string trim(const std::string& target, const char* trimCharacters) {
  std::string result("");

  // �����̋󔒈ȊO�̕����ʒu
  std::string::size_type left = target.find_first_not_of(trimCharacters);

  if (std::string::npos != left) {
    // �E���̋󔒈ȊO�̕����ʒu
    std::string::size_type right = target.find_last_not_of(trimCharacters);

    result = target.substr(left, right - left + 1);
  }
  return result;
}

namespace {
  const std::string base64_padding[] = {"", "==", "="};
}
// Base64�G���R�[�f�B���O�ɂ���
// @see http://ja.wikipedia.org/wiki/Base64
// Boost�ł�Base64�G���R�[�f�B���O�������@�ɂ���
// @see http://stackoverflow.com/questions/7053538/how-do-i-encode-a-string-to-base64-using-only-boost
// @see http://d.hatena.ne.jp/amachang/20090325/1237960531
// @see http://www.boost.org/doc/libs/1_55_0/libs/serialization/doc/dataflow.html
std::string base64encode(const std::string& target) {
  using boost::archive::iterators::base64_from_binary;
  using boost::archive::iterators::transform_width;

  typedef base64_from_binary<transform_width<const char *, 6, 8> > base64_encorder;

  std::stringstream ss;
  std::copy(
    base64_encorder(BOOST_MAKE_PFTO_WRAPPER(target.c_str())),
    base64_encorder(BOOST_MAKE_PFTO_WRAPPER(target.c_str() + target.size())),
    std::ostream_iterator<char>(ss)
    );

  // Base64�R�[�f�B���O�ɂ��킹�ĂS�����P�ʂɂȂ�悤�Ƀp�f�B���O���s��
  // �p�f�B���O�������̌��ߕ��͉��L�̂Ƃ���l����΂悢
  //
  // �Ώە�����̕�������n�Ƃ����
  //   8n/6 = 4n/3    : 6bit�P�ʂɕ��������ۂ̕������i�v�؂�グ�j
  //   (4n/3)/4 = n/3 : 4�����P�ʂɂ܂Ƃ߂��O���[�v�̐��i�v�؂�グ�j
  //   4*1/3 = 1.33.. : �O���[�v���̗]�肪�P�̏ꍇ�̕������i�v�؂�グ�A�����Q�����j
  //   4*2/3 = 2.66.. : �O���[�v���̗]�肪�Q�̏ꍇ�̕������i�v�؂�グ�A�����P�����j
  ss << base64_padding[target.size() % 3];

  return ss.str();
}

} // utility
} // openrtm_network_camera
