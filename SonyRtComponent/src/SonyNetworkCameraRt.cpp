// -*- C++ -*-
/*!
 * @file  SonyNetworkCameraRt.cpp
 * @brief Network camera component for SONY
 * @date $Date$
 *
 * $Id$
 */

#include "SonyNetworkCameraRt.h"

// Module specification
// <rtc-template block="module_spec">
static const char* sonynetworkcamerart_spec[] =
  {
    "implementation_id", "SonyNetworkCameraRt",
    "type_name",         "SonyNetworkCameraRt",
    "description",       "Network camera component for SONY",
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
    "conf.default.imageSize", "640x480",
    "conf.default.imageQuality", "5",
    "conf.default.whiteBalance", "auto",
    "conf.default.setupType", "desktop",
    // Widget
    "conf.__widget__.cameraHost", "text",
    "conf.__widget__.cameraPort", "text",
    "conf.__widget__.user", "text",
    "conf.__widget__.password", "text",
    "conf.__widget__.imageFormat", "radio",
    "conf.__widget__.imageSize", "radio",
    "conf.__widget__.imageQuality", "slider.5",
    "conf.__widget__.whiteBalance", "radio",
    "conf.__widget__.setupType", "radio",
    // Constraints
    "conf.__constraints__.imageFormat", "(JPEG, RAW)",
    "conf.__constraints__.imageSize", "(160x120, 320x240, 640x480)",
    "conf.__constraints__.imageQuality", "1<=x<=10",
    "conf.__constraints__.whiteBalance", "(auto, indoor, outdoor, onepushwb)",
    "conf.__constraints__.setupType", "(ceiling, desktop)",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SonyNetworkCameraRt::SonyNetworkCameraRt(RTC::Manager* manager)
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
SonyNetworkCameraRt::~SonyNetworkCameraRt()
{
}



RTC::ReturnCode_t SonyNetworkCameraRt::onInitialize()
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
  bindParameter("imageSize", m_imageSize, "640x480");
  bindParameter("imageQuality", m_imageQuality, "5");
  bindParameter("whiteBalance", m_whiteBalance, "auto");
  bindParameter("setupType", m_setupType, "desktop");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SonyNetworkCameraRt::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SonyNetworkCameraRt::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SonyNetworkCameraRt::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SonyNetworkCameraRt::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SonyNetworkCameraRtInit(RTC::Manager* manager)
  {
    coil::Properties profile(sonynetworkcamerart_spec);
    manager->registerFactory(profile,
                             RTC::Create<SonyNetworkCameraRt>,
                             RTC::Delete<SonyNetworkCameraRt>);
  }
  
};


