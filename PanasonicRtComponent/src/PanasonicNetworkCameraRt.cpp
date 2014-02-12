// -*- C++ -*-
/*!
 * @file  PanasonicNetworkCameraRt.cpp
 * @brief Network camera component for Panasonic
 * @date $Date$
 *
 * $Id$
 */

#include <rtm/SystemLogger.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "PanasonicNetworkCameraRt.h"

// Module specification
// <rtc-template block="module_spec">
static const char* panasonicnetworkcamerart_spec[] =
  {
    "implementation_id", "PanasonicNetworkCameraRt",
    "type_name",         "PanasonicNetworkCameraRt",
    "description",       "Network camera component for Panasonic",
    "version",           "1.0.0",
    "vendor",            "aist",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "0",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.cameraHost", "127.0.0.1",
    "conf.default.cameraPort", "80",
    "conf.default.user", "user",
    "conf.default.password", "password",
    "conf.default.imageFormat", "JPEG",
    "conf.default.imageQuality", "Standard",
    "conf.default.imageSize", "w640",
    "conf.default.whiteBalance", "auto",
    "conf.default.setupType", "desktop",
    // Widget
    "conf.__widget__.cameraHost", "text",
    "conf.__widget__.cameraPort", "text",
    "conf.__widget__.user", "text",
    "conf.__widget__.password", "text",
    "conf.__widget__.imageFormat", "radio",
    "conf.__widget__.imageQuality", "radio",
    "conf.__widget__.imageSize", "radio",
    "conf.__widget__.whiteBalance", "radio",
    "conf.__widget__.setupType", "radio",
    // Constraints
    "conf.__constraints__.imageFormat", "(JPEG, RAW)",
    "conf.__constraints__.imageQuality", "(Motion, Standard, Clarity)",
    "conf.__constraints__.imageSize", "(w192, w320, w640, w1280_43, w1280_54)",
    "conf.__constraints__.whiteBalance", "(auto, indoor, fluorescent_white, fluorescent_day, outdoor, hold)",
    "conf.__constraints__.setupType", "(ceiling, desktop)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
PanasonicNetworkCameraRt::PanasonicNetworkCameraRt(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ptzIn("ptz", m_ptz),
    m_focusIn("focus", m_focus),
    m_brightnessIn("brightness", m_brightness),
    m_imageOut("image", m_image)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
PanasonicNetworkCameraRt::~PanasonicNetworkCameraRt()
{
}



RTC::ReturnCode_t PanasonicNetworkCameraRt::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("ptz", m_ptzIn);
  addInPort("focus", m_focusIn);
  addInPort("brightness", m_brightnessIn);
  
  // Set OutPort buffer
  addOutPort("image", m_imageOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("cameraHost", m_cameraHost, "127.0.0.1");
  bindParameter("cameraPort", m_cameraPort, "80");
  bindParameter("user", m_user, "user");
  bindParameter("password", m_password, "password");
  bindParameter("imageFormat", m_imageFormat, "JPEG");
  bindParameter("imageQuality", m_imageQuality, "Standard");
  bindParameter("imageSize", m_imageSize, "w640");
  bindParameter("whiteBalance", m_whiteBalance, "auto");
  bindParameter("setupType", m_setupType, "desktop");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t PanasonicNetworkCameraRt::onActivated(RTC::UniqueId ec_id)
{
  // �����ݒ�
  setupCamera();
  setupAuthenticate();
  setupWhiteBalance();
  setupSetupType();

  // �ȑO�̃R���t�B�M�����[�V�����l��������
  m_lastConfig.cameraHost = m_cameraHost;
  m_lastConfig.cameraPort = m_cameraPort;
  m_lastConfig.user       = m_user;
  m_lastConfig.password   = m_password;
  m_lastConfig.whiteBalance = m_whiteBalance;
  m_lastConfig.setupType    = m_setupType;

  return RTC::RTC_OK;
}


RTC::ReturnCode_t PanasonicNetworkCameraRt::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PanasonicNetworkCameraRt::onExecute(RTC::UniqueId ec_id)
{
  // �R���t�B�M�����[�V�����m�F
  setupByConfigurations();

  // �f�[�^�|�[�g���͂̊m�F
  procPtz();
  procFocus();
  procBrightness();

  // �摜�擾����
  procImage();

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t PanasonicNetworkCameraRt::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*!
 * @brief �摜�擾����
 *
 * ��ɁA�R�̃X�e�b�v�ŏ������s���B
 * 1. http��p�����摜�̎擾
 * 2. �擾�����摜�̃t�H�[�}�b�g�ϊ�
 * 3. �o�͉摜�t�H�[�}�b�g�ɉ������摜��OutPort�֏�������
 *
 * @caution
 * �o�͉摜�t�H�[�}�b�g�ɂ�����炸�AJPEG�摜�͈�x
 * �G���R�[�h�����B
 */
void PanasonicNetworkCameraRt::procImage() {

  int length;
  const char* p_image = getCameraImage(&length);
  if ((false == m_camera.isLastApiSuccess()) || (NULL == p_image) || (0 == length)) {
    RTC_WARN_STR("failed image got.");
    return;
  }

  // �t�H�[�}�b�g�m�F
  bool isJpeg;
  if ("JPEG" == m_imageFormat) {
    isJpeg = true;
  } else if ("RAW" == m_imageFormat) {
    isJpeg = false;
  } else {
    RTC_WARN_STR("invalid format string, " + m_imageFormat + ". use JPEG value");
    isJpeg = true;
  }

  // �摜�T�C�Y���擾���邽�߂ɁA�t�H�[�}�b�g�ϊ����Ăяo��
  // ����
  //   �o�͉摜�t�H�[�}�b�g��JPEG�̏ꍇ����x�͕ϊ������
  std::vector<unsigned char> data;
  data.reserve(length);
  for (int i = 0; i < length; ++i) {
    data.push_back(p_image[i]);
  }

  cv::Mat converted = cv::imdecode(cv::Mat(data), 1);


  // �o�̓f�[�^�̐ݒ�

  m_image.width = converted.cols;
  m_image.height = converted.rows;

  // �o�̓t�H�[�}�b�g�ɉ����ď�����ς���
  if (isJpeg) {
    m_image.format = "JPEG";

    m_image.pixels.length(length);
    memcpy((void*)&(m_image.pixels[0]), p_image, length);

  } else {
    m_image.format = "RAW";

    const int l = converted.channels() * m_image.width * m_image.height;
    m_image.pixels.length(l);
    memcpy((void*)&(m_image.pixels[0]), converted.data, l);
  }

  // OutPort�֏�������
  m_imageOut.write();
}
const char* PanasonicNetworkCameraRt::getCameraImage(int* p_length) {

  // �摜�̎擾
  using openrtm_network_camera::panasonic::PanasonicNetworkCamera;

  PanasonicNetworkCamera::Resolution resolution;
  if ("192x144" == m_imageSize) {
    resolution = PanasonicNetworkCamera::w192x144;
  } else if ("320x240" == m_imageSize) {
    resolution = PanasonicNetworkCamera::w320x240;
  } else if ("640x480" == m_imageSize) {
    resolution = PanasonicNetworkCamera::w640x480;
  } else if ("1280x960" == m_imageSize) {
    resolution = PanasonicNetworkCamera::w1280x960;
  } else if ("1280x1024" == m_imageSize) {
    resolution = PanasonicNetworkCamera::w1280x1024;
  } else {
    RTC_WARN_STR("imageSize in configuration is invalid, " + m_imageSize + ". use 640x480 value.");
    resolution = PanasonicNetworkCamera::w640x480;
  }

  PanasonicNetworkCamera::Quality quality;
  if ("Motion" == m_imageQuality) {
    quality = PanasonicNetworkCamera::Motion;
  } else if ("Standard" == m_imageQuality) {
    quality = PanasonicNetworkCamera::Standard;
  } else if ("Clarity" == m_imageQuality) {
    quality = PanasonicNetworkCamera::Clarity;
  } else {
    RTC_WARN_STR("imageQuality in configuration is invalid, " + m_imageQuality + ". use Standard value.");
    quality = PanasonicNetworkCamera::Standard;
  }

  return m_camera.getImage(resolution, quality, p_length);
}

void PanasonicNetworkCameraRt::procPtz() {
  if (false == m_ptzIn.isNew()) {
    return;
  }
  m_ptz.data = m_ptzIn.read();

  if (3 != m_ptz.data.length()) {
    RTC_WARN_STR("data from ptz InPort is invalid. TimedShortSeq must be length 3, but not.");
    return;
  }

  // �p��
  const int data_pan = m_ptz.data[0];
  if (0 > data_pan) {
    m_camera.movePanRight();
  } else if (0 < data_pan) {
    m_camera.movePanLeft();
  }

  // �`���g
  const int data_tilt = m_ptz.data[1];
  if (0 > data_tilt) {
    m_camera.moveTiltUp();
  } else if (0 < data_tilt) {
    m_camera.moveTiltDown();
  }

  // �Y�[��
  const int data_zoom = m_ptz.data[2];
  if (0 > data_zoom) {
    m_camera.zoomTele();
  } else if (0 < data_zoom) {
    m_camera.zoomWide();
  }

  // �z�[���|�W�V�������A
  if (0 == data_pan && 0 == data_tilt && 0 == data_zoom) {
    m_camera.moveToHomePosition();
  }
}
void PanasonicNetworkCameraRt::procFocus() {
  if (false == m_focusIn.isNew()) {
    return;
  }
  m_focus.data = m_focusIn.read();

  if (0 > m_focus.data) {
    m_camera.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Near);
  } else if (0 < m_focus.data) {
    m_camera.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Far);
  } else {
    m_camera.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoFocus);
  }
}
void PanasonicNetworkCameraRt::procBrightness() {
  if (false == m_brightnessIn.isNew()) {
    return;
  }
  m_brightness.data = m_brightnessIn.read();

  if (0 > m_brightness.data) {
    m_camera.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Darker);
  } else if (0 < m_brightness.data) {
    m_camera.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Brighter);
  } else {
    m_camera.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::DefaultBrightness);
  }
}

/*!
 * @brief �R���t�B�M�����[�V������p�����ݒ�
 *
 * �ȑO�̐ݒ�l�ƈقȂ�ꍇ�ɁA�ݒ�pAPI���Ăяo��
 */
void PanasonicNetworkCameraRt::setupByConfigurations() {

  // �J�����ݒ�
  if ((m_lastConfig.cameraHost != m_cameraHost) || (m_lastConfig.cameraPort != m_cameraPort)) {
    setupCamera();
    m_lastConfig.cameraHost = m_cameraHost;
    m_lastConfig.cameraPort = m_cameraPort;
  }

  // �F�؏��
  if ((m_lastConfig.user != m_user) || (m_lastConfig.password != m_password)) {
    setupAuthenticate();
    m_lastConfig.user       = m_user;
    m_lastConfig.password   = m_password;
  }

  // �z���C�g�o�����X
  if (m_lastConfig.whiteBalance != m_whiteBalance) {
    setupWhiteBalance();
    m_lastConfig.whiteBalance = m_whiteBalance;
  }

  // �ݒu�ꏊ
  if (m_lastConfig.setupType != m_setupType) {
    setupSetupType();
    m_lastConfig.setupType    = m_setupType;
  }
}

void PanasonicNetworkCameraRt::setupCamera() {
  int port = m_cameraPort;
  if ((0 > m_cameraPort) || (65535 < m_cameraPort)) {
    std::stringstream ss;
    ss << m_cameraPort;
    RTC_WARN_STR("invalid configuration parameter, m_cameraPort:" + ss.str() + ". use \"80\" instead.");
    port = 80;
  }

  std::stringstream ss;
  ss << port;
  m_camera.setCamera(m_cameraHost, ss.str());
}
void PanasonicNetworkCameraRt::setupAuthenticate() {
  m_camera.setAuthenticateUser(m_user, m_password);
}
void PanasonicNetworkCameraRt::setupWhiteBalance() {
  using openrtm_network_camera::panasonic::PanasonicNetworkCamera;

  PanasonicNetworkCamera::WhiteBalance wb;
  if ("auto" == m_whiteBalance) {
    wb = PanasonicNetworkCamera::AutoWB;
  } else if ("indoor" == m_whiteBalance) {
    wb = PanasonicNetworkCamera::Indoor;
  } else if ("fluorescent_white" == m_whiteBalance) {
    wb = PanasonicNetworkCamera::Fluorescent_White;
  } else if ("fluorescent_day" == m_whiteBalance) {
    wb = PanasonicNetworkCamera::Fluorescent_Day;
  } else if ("outdoor" == m_whiteBalance) {
    wb = PanasonicNetworkCamera::Outdoor;
  } else if ("hold" == m_whiteBalance) {
    wb = PanasonicNetworkCamera::Hold;
  } else {
    RTC_WARN_STR("invalid configuration parameter, whilteBalance:" + m_whiteBalance + ". use \"auto\" instead.");
    wb = PanasonicNetworkCamera::AutoWB;
  }
  m_camera.setWhiteBalance(wb);
}
void PanasonicNetworkCameraRt::setupSetupType() {
  using openrtm_network_camera::panasonic::PanasonicNetworkCamera;

  PanasonicNetworkCamera::SetupType st;
  if ("ceiling" == m_setupType) {
    st = PanasonicNetworkCamera::Ceiling;
  } if ("desktop" == m_setupType) {
    st = PanasonicNetworkCamera::Desktop;
  } else {
    RTC_WARN_STR("invalid configuration parameter, setupType:" + m_setupType + ". use \"desktop\" instead.");
    st = PanasonicNetworkCamera::Desktop;
  }
  m_camera.setSetupType(st);
}



extern "C"
{
 
  void PanasonicNetworkCameraRtInit(RTC::Manager* manager)
  {
    coil::Properties profile(panasonicnetworkcamerart_spec);
    manager->registerFactory(profile,
                             RTC::Create<PanasonicNetworkCameraRt>,
                             RTC::Delete<PanasonicNetworkCameraRt>);
  }
  
};


