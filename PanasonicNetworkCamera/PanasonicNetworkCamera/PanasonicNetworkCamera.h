/*!
 * @file  PanasonicNetworkCamera.h
 * @brief NetworkCamera access class for Panasonic camera.
 * @date  2014-02-07
 */
#ifndef PANASONIC_NETWORK_CAMERA_H
#define PANASONIC_NETWORK_CAMERA_H

#include <string>

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
  class HttpClient; // 前方宣言
}

/*!
 * @namespace panasonic
 * @brief Panasonicカメラ
 *
 */
namespace panasonic {

/*!
 * @class PanasonicNetworkCamera
 * @brief PanasonicNetworkCamera クラス
 * 
 * Panasonic製ネットワークカメラへアクセスするためのクラス。
 * クラスのインスタンス化後も、接続先を切り替え可能とする。
 */
class PanasonicNetworkCamera
{
public:

  /*!
   * @brief 画像サイズ
   */
  enum Resolution {
    w192x144,    //!< 192x144
    w320x240,    //!< 320x240
    w640x480,    //!< 640x480
    w1280x960,   //!< 1280x960
    w1280x1024,  //!< 1280x1024
  };

  /*!
   * @brief 画質
   */
  enum Quality {
    Motion ,  //!< 動き優先
    Standard, //!< 通常
    Clarity,  //!< 画質優先
  };

  /*!
   * @brief フォーカス
   */
  enum FocusType {
    Near,       //!< 近く
    AutoFocus,  //!< 自動
    Far,        //!< 遠く
  };

  /*!
   * @brief ホワイトバランス
   */
  enum WhiteBalance {
    AutoWB,            //!< 自動
    Indoor,            //!< 屋内
    Fluorescent_White, //!< 蛍光灯（白色）
    Fluorescent_Day,   //!< 蛍光灯（昼白色）
    Outdoor,           //!< 屋外
    Hold,              //!< ホールド
  };

  /*!
   * @brief 明るさ
   */
  enum BrightnessType {
    Darker,             //!< 暗く
    DefaultBrightness,  //!< デフォルトの明るさ
    Brighter,           //!< 明るく
  };

  /*!
   * @brief 設置タイプ
   */
  enum SetupType {
    Ceiling,  //!< 天井
    Desktop,  //!< 卓上
  };

	PanasonicNetworkCamera(void);
	~PanasonicNetworkCamera(void);

  /*!
   * @brief カメラの設定
   */
  void setCamera(const std::string& host, const std::string& port);

  /*!
   * @brief 認証ユーザーの設定
   *
   * 空文字列を設定すれば、指定が解除される。
   */
  void setAuthenticateUser(const std::string& user, const std::string password);

  /*!
   * @brief 画像の取得
   *
   * @caution 戻り値は呼び出し側で削除しない
   * @caution 次のAPI呼び出し（画像以外も含むすべて）によりデータが消去される。
   * したがって、次の呼び出し前に（必要があれば）戻り値をコピーすること
   *
   */
  const unsigned char* getImage(const Resolution resolution, const Quality quality, int* p_length);

	void movePanLeft();

  void movePanRight();

  void moveTiltUp();

  void moveTiltDown();

  void zoomTele();

  void zoomWide();

  void adjustFocus(const FocusType type);

  void setWhiteBalance(const WhiteBalance type);

  void adjustBrightness(const BrightnessType type);

  void moveToHomePosition();

  void setSetupType(const SetupType type);

protected:
private:

  /*!
   * @brief リクエストの実行
   *
   * @caution 戻り値は次の呼び出し時に削除される
   */
  const unsigned char* doRequest(const std::string& path, int* p_length);
  const unsigned char* processContents(const unsigned char* p_contents, int length);


  utility::HttpClient* p_client_;

  std::string host_;
  std::string port_;

  std::string user_;
  std::string password_;


  PanasonicNetworkCamera(const PanasonicNetworkCamera&);
  void operator=(const PanasonicNetworkCamera&);
};

} // panasonic
} // openrtm_network_camera

#endif