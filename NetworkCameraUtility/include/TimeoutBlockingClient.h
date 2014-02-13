/*!
 * @file  TimoutBlockingClient.h
 * @brief Network access client using Boost.Asio
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * @date  2014-02-06
 */
#ifndef TIMEOUT_BLOCKING_CLIENT_H
#define TIMEOUT_BLOCKING_CLIENT_H

#include <string>

#include <boost/asio.hpp>

/*!
 * @namespace openrtm_network_camera
 * @brief OpenRTM NetworkCamera用コンポーネント
 *
 */
namespace openrtm_network_camera {

/*!
 * @namespace utility
 * @brief 共通処理
 *
 */
namespace utility {

/*!
 * @class TimeoutBlockingClient
 * @brief Boost.Asio を用いた タイムアウト付きのClient クラス
 * 
 * タイムアウトを備えた、ネットワークへアクセスするクライアントクラス。
 * 処理は、Boost.Asio を元に実装する。
 *
 * Boost.Asio のサンプルを元に記述
 * @see http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp03/timeouts/blocking_tcp_client.cpp
 */
class TimeoutBlockingClient
{
public:
  TimeoutBlockingClient();
  ~TimeoutBlockingClient();

  void connect(const std::string& host, const std::string& service, boost::posix_time::time_duration timeout);

  size_t read(boost::posix_time::time_duration timeout);
  size_t read_until(const std::string& delimiter, boost::posix_time::time_duration timeout);

  void write(boost::asio::streambuf& buf, boost::posix_time::time_duration timeout);

  /*!
   * @brief 読み込み結果を保持するstreambufへの参照を取得
   *
   * 呼び出し側では、戻り値を参照で受けて必要な処理を行う
   */
  boost::asio::streambuf& getStreambuf() { return input_buffer_; }

private:
  void check_deadline();

  boost::asio::io_service io_service_;
  boost::asio::ip::tcp::socket socket_;
  boost::asio::deadline_timer deadline_;
  boost::asio::streambuf input_buffer_;


  TimeoutBlockingClient(const TimeoutBlockingClient&);
  void operator=(const TimeoutBlockingClient&);
};

} // utility
} // openrtm_network_camera

#endif