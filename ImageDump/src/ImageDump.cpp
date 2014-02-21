// -*- C++ -*-
/*!
 * @file  ImageDump.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "ImageDump.h"

// Module specification
// <rtc-template block="module_spec">
static const char* imagedump_spec[] =
  {
    "implementation_id", "ImageDump",
    "type_name",         "ImageDump",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.base_filename", "image_",
    // Widget
    "conf.__widget__.base_filename", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ImageDump::ImageDump(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_imageIn("image", m_image)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ImageDump::~ImageDump()
{
}



RTC::ReturnCode_t ImageDump::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("image", m_imageIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("base_filename", m_base_filename, "image_");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ImageDump::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ImageDump::onExecute(RTC::UniqueId ec_id)
{
  std::string outFilename(m_base_filename);

  if (m_imageIn.isNew()) {
    m_imageIn.read();

    // 取得画像フォーマットの確認
    const std::string format(m_image.format);
    if ("RAW" == format) {
      std::cout << "RAW data format\n";
      outFilename += "Raw.raw";

    } else if ("JPEG" == format) {
      std::cout << "JPEG data format\n";
      outFilename += "Jpeg.jpg";

    } else {
      std::cout << "invalid data format\n";
      return RTC::RTC_OK;
    }

    // 画像をファイルへダンプ
    size_t len = m_image.pixels.length();
    if (0 < outFilename.size() && 0 < len) {
      std::basic_ofstream<unsigned char> outfile(outFilename, std::ios::out|std::ios::binary|std::ios::trunc);
      outfile.write(&(m_image.pixels[0]), len);
    }
  }
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ImageDump::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ImageDump::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ImageDumpInit(RTC::Manager* manager)
  {
    coil::Properties profile(imagedump_spec);
    manager->registerFactory(profile,
                             RTC::Create<ImageDump>,
                             RTC::Delete<ImageDump>);
  }
  
};


