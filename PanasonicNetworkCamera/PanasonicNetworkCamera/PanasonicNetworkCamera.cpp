/*!
 * @file  PanasonicNetworkCamera.cpp
 * @brief NetworkCamera access class for Panasonic camera.
 * @date  2014-02-07
 */

#include "PanasonicNetworkCamera.h"

#include <iostream>
#include <string>

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

PanasonicNetworkCamera::PanasonicNetworkCamera()
    : p_client_(new utility::HttpClient()),
      host_(""),
      port_(""),
      user_(""),
      password_("") {
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
   * @caution �߂�l�͌Ăяo�����ō폜���Ȃ�
   * @caution ����API�Ăяo���i�摜�ȊO���܂ނ��ׂāj�ɂ��f�[�^�����������B
   * ���������āA���̌Ăяo���O�Ɂi�K�v������΁j�߂�l���R�s�[���邱��
   *
   */
const unsigned char* PanasonicNetworkCamera::getImage(const Resolution resolution, const Quality quality, int* p_length) {
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
    std::cout << "getImage: invalid resolution. try 640x480 value.\n";
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
    std::cout << "getImage: invalid quality. try Standard value.\n";
    path += "Standard";
    break;
  }

  const unsigned char* buf = doRequest(path, p_length);
  return processContents(buf, *p_length);
}

namespace {
const char* API_PAN  = "/Set?Func=Pan&Kind=0&DegMode=";
const char* API_TILT = "/Set?Func=Tilt&Kind=0&DegMode=";
const char* API_ZOOM = "/Set?Func=Zoom&Kind=0&ZoomMode=";
}

void PanasonicNetworkCamera::movePanLeft() {
  std::string path(API_PAN);
  path += "4";

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::movePanRight() {
  std::string path(API_PAN);
  path += "6";

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::moveTiltUp() {
  std::string path(API_TILT);
  path += "8";

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::moveTiltDown() {
  std::string path(API_TILT);
  path += "2";

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::zoomTele() {
  std::string path(API_ZOOM);
  path += "4";

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::zoomWide() {
  std::string path(API_ZOOM);
  path += "6";

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

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
    std::cout << "adjustFocus: invalid focus type. try auto value.\n";
    path += "5";
    break;
  }

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

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
    std::cout << "setWhiteBalance: invalid white balance type. try hold value. (hold means keep current while balance.)\n";
    path += "16";
    break;
  }

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::adjustBrightness(const BrightnessType type) {
  const char* API_PATH = "/Set?Func=CameraWB&Kind=1&Data=";

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
    std::cout << "adjustBrightness: invalid brightness type. try default brightness value.\n";
    path += "DefaultBrightness";
    break;
  }

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

void PanasonicNetworkCamera::moveToHomePosition() {
  const char* API_PATH = "/Set?Func=PresetCnt&Kind=0";

  int length;
  const unsigned char* buf = doRequest(API_PATH, &length);
  processContents(buf, length);
}

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
    std::cout << "setSetupType: invalid setuptype value. try ceiling value.\n";
    path += "0";
    break;
  }

  int length;
  const unsigned char* buf = doRequest(path, &length);
  processContents(buf, length);
}

namespace {
const int STATUS_OK = 200;
const int STATUS_NO_CONTENT = 204;
const int STATUS_UNAUTHORIZED = 401;
}

/*!
 * @brief �l�b�g���[�N�J������API�𑗐M
 *
 * PanasonicNetworkCamera::setCamera �Őݒ肵���J�����ɁA
 * �����Ŏw�肳�ꂽAPI���N�G�X�g�𓊂���B
 * ���s���͏�ɁABasic�F�ؕt���B
 *
 */
const unsigned char* PanasonicNetworkCamera::doRequest(const std::string& path, int* p_length) {
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
    std::cout << "�G���[����\n";
    return NULL;
    break;
  default:
    std::cout << "�s���ȃX�e�[�^�X�R�[�h�F" << status << "\n";
    return NULL;
    break;
  }

  // �R���e���c���̊m�F
  *p_length = p_client_->getContentLength();
  if (0 == *p_length) {
    return NULL;
  }

  return (unsigned char*)p_client_->getContents(); // TODO �߂�l���C��
}

/*!
 * @brief ���X�|���X���ʂ̏���
 *
 * Content-Type�ɉ����ď������s���B
 *   image/*    �F�擾�����f�[�^��߂�l�Ƃ��Ė߂��B
 *   text/plain �F���ʂ�W���o�͂֏o���i�G���[�R�[�h���܂܂�邽�߁j
 *   text/���̑��F�Ȃɂ����Ȃ�
 *   ���̑�     �F�Ȃɂ����Ȃ�
 */
const unsigned char* PanasonicNetworkCamera::processContents(const unsigned char* contents, int length) {
  if (NULL == contents) {
    return NULL;
  }

  const std::string type = p_client_->getContentType();

  // image/*     : �摜�f�[�^��߂�
  if (std::string::npos != type.find("image")) {
    return contents;
  }

  // text/plain  : ���ʂ��o��
  // text/���̑� : �Ȃɂ����Ȃ�
  // ���̑�      : �Ȃɂ����Ȃ�
  if (std::string::npos != type.find("text")) {
    if (std::string::npos != type.find("text/plain")) {
      // �{���́AReturn: �ȍ~�𒲂ׂăG���[�R�[�h�݂̂�\����������
      // �z�[���|�W�V�������A���̖߂�l�����̂̂��߁A���������G�ɂȂ�̂őΉ����Ȃ�
      std::cout << contents << "\n";
    }
  }
  return NULL;
}

} // panasonic
} // openrtm_network_camera