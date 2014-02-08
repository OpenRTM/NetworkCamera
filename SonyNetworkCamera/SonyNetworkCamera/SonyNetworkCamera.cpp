/*!
 * @file  SonyNetworkCamera.cpp
 * @brief NetworkCamera access class for Sony camera.
 * @date  2014-02-09
 */

#include "SonyNetworkCamera.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

#include "IntBounds.h"
#include "HttpClient.h"

/*!
 * @namespace openrtm_network_camera
 * @brief OpenRTM NetworkCamera�p�R���|�[�l���g
 *
 */
namespace openrtm_network_camera {

/*!
 * @namespace sony
 * @brief Sony�J����
 *
 */
namespace sony {

namespace {
const char* CONTENTS_TYPE_IMAGE = "image";
const char* CONTENTS_TYPE_TEXT  = "text";

const int STATUS_OK = 200;
const int STATUS_NO_CONTENT = 204;
const int STATUS_UNAUTHORIZED = 401;
}

SonyNetworkCamera::SonyNetworkCamera()
    : p_client_(new utility::HttpClient()),
      host_(""),
      port_(""),
      user_(""),
      password_(""),
      lastResult(false) {
}

SonyNetworkCamera::~SonyNetworkCamera() {
  if (NULL != p_client_) {
    delete p_client_;
    p_client_ = NULL;
  }
}

void SonyNetworkCamera::setCamera(const std::string& host, const std::string& port) {
  host_ = host;
  port_ = port;
}

void SonyNetworkCamera::setAuthenticateUser(const std::string& user, const std::string password) {
  user_ = user;
  password_ = password;
}

/*!
 * @brief �摜�̎擾
 *
 * @caution �摜�̎擾�ɂ́A/oneshotimage.jpg ���g���A�𑜓x�́Acamera.cgi?jpimagesize
 * �ŕύX������@������B�������A���̕��@�̏ꍇ�A�𑜓x�ύX�������ɔ��f���ꂸ�A
 * �擾�����摜�̃T�C�Y���w��O�̂��̂ɂȂ�ꍇ���������B
 * ���̂��߁A/jpeg��API���g�����ƂƂ����B
 *
 * @parma resolution  �𑜓x
 * @param p_length    �f�[�^���i�o�́j
 * @return �摜�f�[�^�z��ւ̃|�C���^
 */
const char* SonyNetworkCamera::getImage(const Resolution resolution, int* p_length) {
  const char* API_PATH = "/jpeg/";
  const char* POST_STR = ".jpg";

  std::string path(API_PATH);

  switch(resolution) {
  case w160x120:
    path += "qqvga";
    break;
  case w320x240:
    path += "qvga";
    break;
  case w640x480:
    path += "vga";
    break;
  default:
    std::cout << "getImage: invalid resolution. try 640x480 value.\n";
    path += "vga";
    break;
  }
  path += POST_STR;

  const char* buf = doRequest(path, p_length);
  if (false == isValidContentsType(CONTENTS_TYPE_IMAGE)) {
    return NULL;
  }
  return buf;
}

void SonyNetworkCamera::setQuality(const int quality) {
  const char* API_PATH = "/command/camera.cgi?jpquality=";

  IntBounds<1, 10, DEFAULT_QUALITY> bounds;
  std::stringstream ss;
  ss << bounds(quality);
  
  std::string path(API_PATH);
  path += ss.str();

  callTextTypeAPI(path);
}

void SonyNetworkCamera::movePanLeft(const int displacement) {
  movePan("04", displacement);
}
void SonyNetworkCamera::movePanRight(const int displacement) {
  movePan("06", displacement);
}
void SonyNetworkCamera::moveTiltUp(const int displacement) {
  moveTilt("08", displacement);
}
void SonyNetworkCamera::moveTiltDown(const int displacement) {
  moveTilt("02", displacement);
}
void SonyNetworkCamera::zoomTele(const int displacement) {
  moveZoom("11", displacement);
}
void SonyNetworkCamera::zoomWide(const int displacement) {
  moveZoom("10", displacement);
}

/*!
 * @brief �t�H�[�J�X�̒���
 *
 * �t�H�[�J�X������Ăяo���Bonepush�ȊO�̏ꍇ�́A
 * �A�����ăt�H�[�J�X��~������Ăяo���B
 *
 * @caution �p�����[�^���s���̏ꍇ�́Aonepush�Ń��N�G�X�g���s���B
 */
void SonyNetworkCamera::adjustFocus(const FocusType type) {
  const char* SPEED = ",1"; // [1,2,...,8] �����A�P�Œ�Ƃ���

  bool needStop = false;
  std::string type_str;
  switch(type) {
  case Near:
    type_str = "near";
    needStop = true;
    break;
  case Far:
    type_str = "far";
    needStop = true;
    break;
  case OnePushFocus:
    type_str = "onepushaf";
    break;
  default:
    std::cout << "adjustFocus: invalid focus type. try onepush value.\n";
    type_str = "onepushaf";
    break;
  }

  // �t�H�[�J�X���s
  doFocus(type_str + SPEED);

  // �t�H�[�J�X�����~
  if (needStop) {
    doFocus("stop,focus");
  }
}

/*!
 * @brief �z���C�g�o�����X�̐ݒ�
 *
 * @caution �p�����[�^���s���̏ꍇ�́Aauto�Ń��N�G�X�g���s���B
 */
void SonyNetworkCamera::setWhiteBalance(const WhiteBalance type) {
  const char* API_PATH = "/command/camera.cgi?wbmode=";

  std::string path(API_PATH);
  switch(type) {
  case AutoWB:
    path += "auto";
    break;
  case Indoor:
    path += "indoor";
    break;
  case Outdoor:
    path += "outdoor";
    break;
  case OnePushWB:
    path += "onepushwb";
    break;
  default:
    std::cout << "setWhiteBalance: invalid white balance type. try auto value.\n";
    path += "auto";
    break;
  }

  callTextTypeAPI(path);
}

/*!
 * @brief ���邳�̒���
 *
 * @caution �p�����[�^���s���̏ꍇ�́ADefaultBrightness�Ń��N�G�X�g���s���B
 */
void SonyNetworkCamera::adjustBrightness(const int brightness) {
  const char* API_PATH = "/command/camera.cgi?brightness=";

  IntBounds<0, 10, DEFAULT_BRIGHTNESS> bounds;
  std::stringstream ss;
  ss << bounds(brightness);

  std::string path(API_PATH);
  path += ss.str();

  callTextTypeAPI(path);
}

void SonyNetworkCamera::moveToHomePosition() {
  const char* API_PATH = "/command/presetposition.cgi?homepos=ptz-recall";
  callTextTypeAPI(API_PATH);
}

/*!
 * @brief �ݒu�ꏊ�̐ݒ�
 *
 * @caution �p�����[�^���s���̏ꍇ�́ACeiling�Ń��N�G�X�g���s���B
 */
void SonyNetworkCamera::setSetupType(const SetupType type) {
  const char* API_PATH = "/command/camera.cgi?eflip=";

  std::string path(API_PATH);
  switch(type) {
  case Ceiling:
    path += "off";
    break;
  case Desktop:
    path += "on";
    break;
  default:
    std::cout << "setSetupType: invalid setuptype value. try ceiling value.\n";
    path += "off";
    break;
  }

  callTextTypeAPI(path);
}


void SonyNetworkCamera::movePan(const std::string& parameter, const int displacement) {
  IntBounds<1, 10, DEFAULT_PAN> bounds;
  movePTZ(parameter + formatDigitFill0Width2(bounds(displacement)));
}
void SonyNetworkCamera::moveTilt(const std::string& parameter, const int displacement) {
  IntBounds<1, 10, DEFAULT_TILT> bounds;
  movePTZ(parameter + formatDigitFill0Width2(bounds(displacement)));
}
void SonyNetworkCamera::moveZoom(const std::string& parameter, const int displacement) {
  IntBounds<1, 10, DEFAULT_ZOOM> bounds;
  movePTZ(parameter + formatDigitFill0Width2(bounds(displacement)));
}
void SonyNetworkCamera::movePTZ(const std::string& parameter) {
  const char* API_PTZ  = "/command/ptzf.cgi?relative=";
  callTextTypeAPI(API_PTZ + parameter);
}

void SonyNetworkCamera::doFocus(const std::string& parameter) {
  const char* API_PATH = "/command/ptzf.cgi?move=";
  callTextTypeAPI(API_PATH + parameter);
}

/*!
 * @brief ���X�|���X��Content-Type���e�L�X�g�ł���API�Ăяo��
 *
 * http���N�G�X�g�̔��s�A�z�肵���R���e���c�^�C�v�̊m�F�A�R���e���c�̉��
 * ���܂Ƃ߂Ď��s���邽�߂̃��\�b�h�B
 *
 * @param path API�̃p�X
 */
void SonyNetworkCamera::callTextTypeAPI(const std::string& path) {
  int length;
  const char* buf = doRequest(path, &length);
  isValidContentsType(CONTENTS_TYPE_TEXT);
}

/*!
 * @brief ���N�G�X�g�̎��s
 *
 * SonyNetworkCamera::setCamera �Őݒ肵���J�����ɁA
 * �����Ŏw�肳�ꂽAPI���N�G�X�g�𓊂���B
 * ���s���͏�ɁABasic�F�ؕt���B
 *
 * @caution �߂�l�͌Ăяo�����ō폜���Ȃ�
 * @caution ����API�Ăяo���ɂ�背�X�|���X�{�f�B�����������B
 *
 * @param path  API�̃p�X
 * @param p_length  ���X�|���X�f�[�^���i�o�́j
 * @return �R���e���c�i���X�|���X�{�f�B�j�ւ̃|�C���^
 */
const char* SonyNetworkCamera::doRequest(const std::string& path, int* p_length) {
  lastResult = false;

  // Basic�F�ؕt�����N�G�X�g
  p_client_->setBasicAuthenticationParameter(user_.c_str(), password_.c_str());
  p_client_->doGet(host_.c_str(), path.c_str(), port_.c_str());

  // ���ʏ���

  // �X�e�[�^�X�R�[�h
  *p_length = 0;
  const int status = p_client_->getStatusCode();
  switch(status) {
  case STATUS_OK:
  case STATUS_NO_CONTENT:
    break;
  case STATUS_UNAUTHORIZED:
    std::cout << "401�G���[�BAPI���쌠��������܂���B�F�؏����������Ă��������B\n";
    return NULL;
    break;
  case -1:
    std::cout << "�J�����Ƃ̒ʐM�Ɏ��s���܂����B�z�X�g���E�|�[�g�ԍ��Ȃǂ��m�F���Ă��������B\n";
    return NULL;
    break;
  default:
    std::cout << "�����ȊO��http�X�e�[�^�X�R�[�h�F" << status << "\n";
    return NULL;
    break;
  }

  // http�X�e�[�^�X�R�[�h�ł̔��茋��
  lastResult = true;

  // �R���e���c���̊m�F
  *p_length = p_client_->getContentLength();
  if (0 == *p_length) {
    return NULL;
  }

  return p_client_->getContents();
}

bool SonyNetworkCamera::isValidContentsType(const std::string& target_type) {
  const std::string type = p_client_->getContentType();
  if (0 == type.size()) {
    // �R���e���c�^�C�v�w�b�_���Ȃ��ꍇ�͔���ł��Ȃ��̂�true�Ƃ���
    return true;
  }

  if (std::string::npos == type.find(target_type)) {
    lastResult = false;  // �z�肵���R���e���c�^�C�v�ƈقȂ�̂ŁAfalse�ɕύX
    return false;
  }
  return true;
}

std::string formatDigitFill0Width2(const int val) {
  std::ostringstream os;
  os << std::setw(2) << std::setfill('0') << val;
  return os.str();
}


} // sony
} // openrtm_network_camera