// -*- C++ -*-
/*!
 * @file  PanasonicNetworkCameraRt.cpp
 * @brief Network camera component for Panasonic
 * @date $Date$
 *
 * $Id$
 */

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
    "conf.default.user", """",
    "conf.default.password", """",
    "conf.default.imageFormat", ""JPEG"",
    "conf.default.imageQuality", ""Standard"",
    "conf.default.imageSize", ""w640"",
    "conf.default.whiteBalance", ""auto"",
    "conf.default.setupType", ""desktop"",
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
    "conf.__constraints__.imageFormat", "("JPEG", "RAW")",
    "conf.__constraints__.imageQuality", "("Motion", "Standard", "Clarity")",
    "conf.__constraints__.imageSize", "(w192", "w320", "w640", "w1280_43", "w1280_54")",
    "conf.__constraints__.whiteBalance", "("auto", "indoor", "fluorescent_white", "fluorescent_day", "outdoor", "hold")",
    "conf.__constraints__.setupType", "("ceiling", "desktop")",
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
  bindParameter("user", m_user, """");
  bindParameter("password", m_password, """");
  bindParameter("imageFormat", m_imageFormat, ""JPEG"");
  bindParameter("imageQuality", m_imageQuality, ""Standard"");
  bindParameter("imageSize", m_imageSize, ""w640"");
  bindParameter("whiteBalance", m_whiteBalance, ""auto"");
  bindParameter("setupType", m_setupType, ""desktop"");
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
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PanasonicNetworkCameraRt::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t PanasonicNetworkCameraRt::onExecute(RTC::UniqueId ec_id)
{
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


