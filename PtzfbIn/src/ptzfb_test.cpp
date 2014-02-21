// -*- C++ -*-
/*!
 * @file  ptzfb_test.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "ptzfb_test.h"

// Module specification
// <rtc-template block="module_spec">
static const char* ptzfb_test_spec[] =
  {
    "implementation_id", "ptzfb_test",
    "type_name",         "ptzfb_test",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ptzfb_test::ptzfb_test(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ptzOut("ptz", m_ptz),
    m_focusOut("focus", m_focus),
    m_brightnessOut("brightness", m_brightness)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ptzfb_test::~ptzfb_test()
{
}



RTC::ReturnCode_t ptzfb_test::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer
  addOutPort("ptz", m_ptzOut);
  addOutPort("focus", m_focusOut);
  addOutPort("brightness", m_brightnessOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ptzfb_test::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ptzfb_test::onExecute(RTC::UniqueId ec_id)
{
  std::cout << "please input command: <command><number> [<command><number> ...]\n";
  std::cout << "  command :p, t, z, f, b\n";

  std::string order;
  std::getline(std::cin, order);

  std::cout << "order is: " << order << std::endl;

  if (1 > order.size()) {
    std::cout << "invalid command\n";
    return RTC::RTC_OK;
  };

  // 空白で分割
  std::vector<std::string> commands;

  std::istringstream iss(order);
  std::string c;
  while(iss >> c) {
    if (c.size() > 0) {
      commands.push_back(c);
      std::cout << "command: " << commands.at(commands.size()-1) << std::endl;
    }
  }

  if (0 == commands.size()) {
    std::cout << "no commands\n";
    return RTC::RTC_OK;;
  } else {
    std::cout << "number of commands: " << commands.size() << std::endl;
  }

  // p, t, z, f, b に対応
  bool isOrdered[5] = {false, false, false, false, false};
  int commandsVal[5] = {0, 0, 0, 0, 0};

  for (size_t i = 0; i < commands.size(); ++i) {
    std::string c = commands.at(i);
    // 数値がないのは正しいコマンドではない
    if (1 >= c.size()) {
      std::cout << "invalid commands: " << c << std::endl;
      continue;
    }

    if ('p' == c[0]) {
      isOrdered[0] = true;
      commandsVal[0] = getVal(c);
    } else if ('t' == c[0]) {
      isOrdered[1] = true;
      commandsVal[1] = getVal(c);
    } else if ('z' == c[0]) {
      isOrdered[2] = true;
      commandsVal[2] = getVal(c);
    } else if ('f' == c[0]) {
      isOrdered[3] = true;
      commandsVal[3] = getVal(c);
    } else if ('b' == c[0]) {
      isOrdered[4] = true;
      commandsVal[4] = getVal(c);
    } else {
      std::cout << "invalid commands: " << c << std::endl;
      continue;
    }
  }

  for (size_t i = 0; i < 5; ++i) {
    std::cout << "order [" << i << "]: " << isOrdered[i] << ", val: " << commandsVal[i] << std::endl;
  }

  // OutPort へ書き込み

  // パン・チルト・ズーム
  m_ptz.data.length(3);
  for (size_t i = 0; i < 3; ++i) {
    if (isOrdered[i]) {
      m_ptz.data[i] = static_cast<short>(commandsVal[i]);
    } else {
      m_ptz.data[i] = 0;
    }
  }
  // ホームポジション復帰は特別扱い
  if (0 == m_ptz.data[0] && 0 == m_ptz.data[1] && 0 == m_ptz.data[2]) {
    if (isOrdered[0] && isOrdered[1] && isOrdered[2]) {
      m_ptzOut.write();
      std::cout << "ptz command send\n";
    }
  } else {
    if (isOrdered[0] || isOrdered[1] || isOrdered[2]) {
      m_ptzOut.write();
      std::cout << "ptz command send\n";
    }
  }

  // フォーカス
  if (isOrdered[3]) {
    m_focus.data = commandsVal[3];
    m_focusOut.write();
    std::cout << "focus command send\n";
  }
  // 明るさ
  if (isOrdered[4]) {
    m_brightness.data = commandsVal[4];
    m_brightnessOut.write();
    std::cout << "focus command send\n";
  }

  return RTC::RTC_OK;
}

int ptzfb_test::getVal(const std::string& str) {
  int v = 0;
  std::istringstream is(str.substr(1, str.size()-1));
  is >> v;
  return v;
}

/*
RTC::ReturnCode_t ptzfb_test::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ptzfb_test::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ptzfb_testInit(RTC::Manager* manager)
  {
    coil::Properties profile(ptzfb_test_spec);
    manager->registerFactory(profile,
                             RTC::Create<ptzfb_test>,
                             RTC::Delete<ptzfb_test>);
  }
  
};


