/*!
 * @file  PanasonicNetworkCamera.cpp
 * @brief NetworkCamera access class for Panasonic camera.
 * @date  2014-02-07
 */

#include "PanasonicNetworkCamera.h"

#include <iostream>
#include <string>

#include <boost/regex.hpp>

#include <rtm/SystemLogger.h>

#include "HttpClient.h"

/*!
 * @namespace openrtm_network_camera
 * @brief OpenRTM NetworkCamera�p�R���|�[�l���g
 *
 */
namespace openrtm_network_camera {

/*!
 * @namespace panasonic
 * @brief Panasonic�J����
 *
 */
namespace panasonic {

namespace {
const char* CONTENTS_TYPE_IMAGE       = "image";
const char* CONTENTS_TYPE_TEXT        = "text";
const char* CONTENTS_TYPE_TEXT_PLAIN  = "text/plain";

const int STATUS_OK = 200;
const int STATUS_NO_CONTENT = 204;
const int STATUS_UNAUTHORIZED = 401;
}

PanasonicNetworkCamera::PanasonicNetworkCamera()
    : p_client_(new utility::HttpClient()),
      host_(""),
      port_(""),
      user_(""),
      password_(""),
      lastResult(false) {
  rtclog.setName("PanasonicNetworkCamera");
  RTC_DEBUG_STR("PanasonicNetworkCamera ctor");
}

PanasonicNetworkCamera::~PanasonicNetworkCamera() {
  if (NULL != p_client_) {
    delete p_client_;
    p_client_ = NULL;
  }
}

void PanasonicNetworkCamera::setCamera(const std::string& host, const std::string& port) {
  host_ = host;
  port_ = port;
}

void PanasonicNetworkCamera::setAuthenticateUser(const std::string& user, const std::string password) {
  user_ = user;
  password_ = password;
}

/*!
 * @brief �摜�̎擾
 *
 * @caution �p�����[�^���s���̏ꍇ�́A640x480, Standard �Ń��N�G�X�g���s���B
 */
const char* PanasonicNetworkCamera::getImage(const Resolution resolution, const Quality quality, int* p_length) {
  const char* API_PATH = "/SnapshotJPEG?Resolution=";
  const char* QUALITY = "&Quality=";

  std::string path(API_PATH);

  switch(resolution) {
  case w192x144:
    path += "192x144";
    break;
  case w320x240:
    path += "320x240";
    break;
  case w640x480:
    path += "640x480";
    break;
  case w1280x960:
    path += "1280x960";
    break;
  case w1280x1024:
    path += "1280x1024";
    break;
  default:
    RTC_WARN_STR("getImage: invalid resolution. try 640x480 value.");
    path += "640x480";
    break;
  }

  path += QUALITY;

  switch(quality) {
  case Motion:
    path += "Motion";
    break;
  case Standard:
    path += "Standard";
    break;
  case Clarity:
    path += "Clarity";
    break;
  default:
    RTC_WARN_STR("getImage: invalid quality. try Standard value.");
    path += "Standard";
    break;
  }

  const char* buf = doRequest(path, p_length);
  if (false == isValidContentsType(CONTENTS_TYPE_IMAGE)) {
    return NULL;
  }
  analyzeContents(buf, *p_length);
  return buf;
}

void PanasonicNetworkCamera::movePanLeft() {
  movePan("4");
}
void PanasonicNetworkCamera::movePanRight() {
  movePan("6");
}

void PanasonicNetworkCamera::moveTiltUp() {
  moveTilt("8");
}

void PanasonicNetworkCamera::moveTiltDown() {
  moveTilt("2");
}

void PanasonicNetworkCamera::zoomTele() {
  moveZoom("4");
}
void PanasonicNetworkCamera::zoomWide() {
  moveZoom("6");
}

/*!
 * @brief �t�H�[�J�X�̒���
 *
 * @caution �p�����[�^���s���̏ꍇ�́Aauto�Ń��N�G�X�g���s���B
 */
void PanasonicNetworkCamera::adjustFocus(const FocusType type) {
  const char* API_PATH = "/Set?Func=Focus&Kind=0&FocusMode=";

  std::string path(API_PATH);
  switch(type) {
  case Near:
    path += "4";
    break;
  case AutoFocus:
    path += "5";
    break;
  case Far:
    path += "6";
    break;
  default:
    RTC_WARN_STR("adjustFocus: invalid focus type. try auto value.");
    path += "5";
    break;
  }

  callTextTypeAPI(path);
}

/*!
 * @brief �z���C�g�o�����X�̐ݒ�
 *
 * @caution �p�����[�^���s���̏ꍇ�́Ahold�Ń��N�G�X�g���s���B
 */
void PanasonicNetworkCamera::setWhiteBalance(const WhiteBalance type) {
  const char* API_PATH = "/Set?Func=CameraWB&Kind=1&Data=";

  std::string path(API_PATH);
  switch(type) {
  case AutoWB:
    path += "0";
    break;
  case Indoor:
    path += "32";
    break;
  case Fluorescent_White:
    path += "48";
    break;
  case Fluorescent_Day:
    path += "64";
    break;
  case Outdoor:
    path += "80";
    break;
  case Hold:
    path += "16";
    break;
  default:
    RTC_WARN_STR("setWhiteBalance: invalid white balance type. try hold value. (hold means keep current while balance.)");
    path += "16";
    break;
  }

  callTextTypeAPI(path);
}

/*!
 * @brief ���邳�̒���
 *
 * @caution �p�����[�^���s���̏ꍇ�́ADefaultBrightness�Ń��N�G�X�g���s���B
 */
void PanasonicNetworkCamera::adjustBrightness(const BrightnessType type) {
  const char* API_PATH = "/nphControlCamera?Direction=";

  std::string path(API_PATH);
  switch(type) {
  case Darker:
    path += "Darker";
    break;
  case DefaultBrightness:
    path += "DefaultBrightness";
    break;
  case Brighter:
    path += "Brighter";
    break;
  default:
    RTC_WARN_STR("adjustBrightness: invalid brightness type. try default brightness value.");
    path += "DefaultBrightness";
    break;
  }

  callTextTypeAPI(path);
}

void PanasonicNetworkCamera::moveToHomePosition() {
  const char* API_PATH = "/Set?Func=PresetCnt&Kind=0";

  callTextTypeAPI(API_PATH);
}

/*!
 * @brief �ݒu�ꏊ�̐ݒ�
 *
 * @caution �p�����[�^���s���̏ꍇ�́ACeiling�Ń��N�G�X�g���s���B
 */
void PanasonicNetworkCamera::setSetupType(const SetupType type) {
  const char* API_PATH = "/Set?Func=Tilt&Kind=1&SetupType=";

  std::string path(API_PATH);
  switch(type) {
  case Ceiling:
    path += "0";
    break;
  case Desktop:
    path += "1";
    break;
  default:
    RTC_WARN_STR("setSetupType: invalid setuptype value. try ceiling value.");
    path += "0";
    break;
  }

  callTextTypeAPI(path);
}

void PanasonicNetworkCamera::movePan(const std::string& parameter) {
  const char* API_PAN  = "/Set?Func=Pan&Kind=0&DegMode=";
  movePTZ(API_PAN, parameter);
}
void PanasonicNetworkCamera::moveTilt(const std::string& parameter) {
  const char* API_TILT = "/Set?Func=Tilt&Kind=0&DegMode=";
  movePTZ(API_TILT, parameter);
}
void PanasonicNetworkCamera::moveZoom(const std::string& parameter) {
  const char* API_ZOOM = "/Set?Func=Zoom&Kind=0&ZoomMode=";
  movePTZ(API_ZOOM, parameter);
}
void PanasonicNetworkCamera::movePTZ(const std::string& path, const std::string& parameter) {
  callTextTypeAPI(path + parameter);
}

/*!
 * @brief ���X�|���X��Content-Type���e�L�X�g�ł���API�Ăяo��
 *
 * http���N�G�X�g�̔��s�A�z�肵���R���e���c�^�C�v�̊m�F�A�R���e���c�̉��
 * ���܂Ƃ߂Ď��s���邽�߂̃��\�b�h�B
 *
 * @param path API�̃p�X
 */
void PanasonicNetworkCamera::callTextTypeAPI(const std::string& path) {
  int length;
  const char* buf = doRequest(path, &length);
  if (false == isValidContentsType(CONTENTS_TYPE_TEXT)) {
    return;
  }
  analyzeContents(buf, length);
}

/*!
 * @brief ���N�G�X�g�̎��s
 *
 * PanasonicNetworkCamera::setCamera �Őݒ肵���J�����ɁA
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
const char* PanasonicNetworkCamera::doRequest(const std::string& path, int* p_length) {
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
    RTC_WARN_STR("401 error. not permitted for this api. Please check your authenticate information.");
    return NULL;
    break;
  case -1:
    RTC_WARN_STR("Failed to comunicate to a network camera. Please check host name and port number for a target network camera.");
    return NULL;
    break;
  default:
    std::stringstream ss;
    ss << status;
    RTC_WARN_STR("unexpected http status code: " + ss.str());
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

bool PanasonicNetworkCamera::isValidContentsType(const std::string& target_type) {
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

/*!
 * @brief �R���e���c�̉��
 *
 * doRequest �Ăяo���̂��ƌĂ΂�邱�Ƃ�z��B
 * Panasonic�̃l�b�g���[�N�J�����̑�����API�̓R���e���c�Ɏ��s����
 * ���܂߂ĕԂ��B���̂��߁A�R���e���c����͂��ăG���[���܂܂��
 * ����΂��̏������O�֏o�͂���B
 * �{���\�b�h�ɂ��R���e���c����͂��ď�������B
 *
 * ���ۂ̏�����Content-Type��text/plain�̏ꍇ�̂ݍs����B
 * �G���[�R�[�h�����o���ꂽ�ꍇ�́AlastResult ��false�ɐݒ肷��B
 *
 * @param p_contents  �R���e���c�idoRequest�̖߂�l�j
 * @param length      �R���e���c��
 */
void PanasonicNetworkCamera::analyzeContents(const char* p_contents, int length) {
  if (NULL == p_contents) {
    return;
  }

  // text/plain �ł��邱�Ƃ̊m�F
  const std::string type = p_client_->getContentType();
  if (std::string::npos == type.find(CONTENTS_TYPE_TEXT_PLAIN)) {
    return;
  }

  // Return���ʂ�����A�G���[�i���̒l�j�Ȃ烍�O�֏o��
  const std::string target(p_contents, p_contents+length);

  static const boost::regex reg("^Return:\\s*(-?\\d+)"); // Return:0, Return:-10, Return: 10 etc
  boost::smatch result;
  if (boost::regex_search(target, result, reg)) {
    const int return_code = ::atoi(result.str(1).c_str());
    if (0 > return_code) {
      std::stringstream ss;
      ss << return_code;
      RTC_WARN_STR("error: return code is " + ss.str());
      RTC_WARN_STR("Check your setup parameters and your camera features.");
      lastResult = false;  // �G���[�����������̂ŁAfalse�ɕύX
    }
  }
}


} // panasonic
} // openrtm_network_camera