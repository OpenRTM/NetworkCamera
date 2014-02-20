
#include <string>

#include "gtest/gtest.h"

#include "PanasonicNetworkCamera.h"

// テストフィクスチャ
class PanasonicNetworkCameraTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::panasonic::PanasonicNetworkCamera client;
};


// 以下、PanasonicNetworkCameraTestクラスのテスト
// 実際の処理クラス HttpClientConcrete を正しく呼び出していることを確認

// テストケースはポート番号を用いて区別する
// スタブ側では、ポート番号をテスト番号として扱う
//
// ポート番号 | 確認項目
// 1          | パン左, 認証指定なし, サーバー指定あり, 前回呼び出し結果（成功）
// 2          | パン右, 認証指定あり, レスポンス正常（Return: 0）
// 3          | チルト上
// 4          | チルト下
// 5          | ズームイン
// 6          | ズームアウト
// 7-9        | フォーカス, 3パターン
// 10-15      | ホワイトバランス, 6パターン
// 16-18      | 明るさ, 3パターン
// 19-20      | 設置タイプ, 2パターン
// 21         | ホームポジション復帰, レスポンス正常（Return: home）
// 22         | サイズ  192x144, 画質Motion, レスポンス正常（image/jpeg）
// 23         | サイズ  320x240, 画質Clarity
// 24         | サイズ  640x480, 画質Standard
// 25         | サイズ 1280x960, 画質Standard
// 26         | サイズ1280x1024, 画質Standard
//
// 27         | 引数異常 サイズ
// 28         | 引数異常 画質
// 29         | 引数異常 フォーカス
// 30         | 引数異常 ホワイトバランス
// 31         | 引数異常 明るさ
// 32         | 引数異常 設置タイプ
//
// 33         | レスポンス異常, 前回呼び出し結果（失敗）, Return: -1
// 34         | レスポンス異常, 前回呼び出し結果（失敗）, statuscode: 401
// 35         | レスポンス異常, 前回呼び出し結果（失敗）, statuscode: -1

// パン
TEST_F(PanasonicNetworkCameraTest, panLeftTest) {
  client.setCamera("127.0.0.1", "1");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(true, client.isLastApiSuccess());
}
TEST_F(PanasonicNetworkCameraTest, panRightTest) {
  client.setCamera("127.0.0.1", "2");
  client.setAuthenticateUser("user", "password");
  client.movePanRight();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// チルト
TEST_F(PanasonicNetworkCameraTest, tiltUpTest) {
  client.setCamera("127.0.0.1", "3");
  client.moveTiltUp();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, tiltDownTest) {
  client.setCamera("127.0.0.1", "4");
  client.moveTiltDown();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ズーム
TEST_F(PanasonicNetworkCameraTest, zoomInTest) {
  client.setCamera("127.0.0.1", "5");
  client.zoomTele();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, zoomOutTest) {
  client.setCamera("127.0.0.1", "6");
  client.zoomWide();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// フォーカス
TEST_F(PanasonicNetworkCameraTest, focusNearTest) {
  client.setCamera("127.0.0.1", "7");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Near);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, focusFarTest) {
  client.setCamera("127.0.0.1", "8");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Far);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, focusAutoTest) {
  client.setCamera("127.0.0.1", "9");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoFocus);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ホワイトバランス
TEST_F(PanasonicNetworkCameraTest, whitebalanceAutoTest) {
  client.setCamera("127.0.0.1", "10");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoWB);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceIndoorTest) {
  client.setCamera("127.0.0.1", "11");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Indoor);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceFluorescentWhiteTest) {
  client.setCamera("127.0.0.1", "12");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Fluorescent_White);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceFluorescentDayTest) {
  client.setCamera("127.0.0.1", "13");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Fluorescent_Day);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceOutdoorTest) {
  client.setCamera("127.0.0.1", "14");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Outdoor);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceHoldTest) {
  client.setCamera("127.0.0.1", "15");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Hold);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 明るさ
TEST_F(PanasonicNetworkCameraTest, brightnessDarkerTest) {
  client.setCamera("127.0.0.1", "16");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Darker);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, brightnessBrighterTest) {
  client.setCamera("127.0.0.1", "17");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Brighter);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, brightnessDefaultTest) {
  client.setCamera("127.0.0.1", "18");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::DefaultBrightness);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 設置場所
TEST_F(PanasonicNetworkCameraTest, setupTypeCeilingTest) {
  client.setCamera("127.0.0.1", "19");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Ceiling);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, setupTypeDesktopTest) {
  client.setCamera("127.0.0.1", "20");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Desktop);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ホームポジション
TEST_F(PanasonicNetworkCameraTest, homepositionTest) {
  client.setCamera("127.0.0.1", "21");
  client.moveToHomePosition();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 画像取得
TEST_F(PanasonicNetworkCameraTest, getImage192x144Test) {
  client.setCamera("127.0.0.1", "22");
  int length;
  const char* p = client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w192x144, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Motion, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(28, length);
  ASSERT_STREQ("there is a image contents.\r\n", p);
}
TEST_F(PanasonicNetworkCameraTest, getImage320x240Test) {
  client.setCamera("127.0.0.1", "23");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w320x240, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Clarity, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, getImage640x480Test) {
  client.setCamera("127.0.0.1", "24");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w640x480, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, getImage1280x960Test) {
  client.setCamera("127.0.0.1", "25");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w1280x960, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, getImage1280x1024Test) {
  client.setCamera("127.0.0.1", "26");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w1280x1024, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}


// 引数異常 サイズ
TEST_F(PanasonicNetworkCameraTest, invalidImageSizeTest) {
  client.setCamera("127.0.0.1", "27");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Resolution(10), openrtm_network_camera::panasonic::PanasonicNetworkCamera::Motion, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 画質
TEST_F(PanasonicNetworkCameraTest, invalidImageQualityTest) {
  client.setCamera("127.0.0.1", "28");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w320x240, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Quality(10), &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 フォーカス
TEST_F(PanasonicNetworkCameraTest, invalidFocusTest) {
  client.setCamera("127.0.0.1", "29");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::FocusType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 ホワイトバランス
TEST_F(PanasonicNetworkCameraTest, invalidWhiteBalanceTest) {
  client.setCamera("127.0.0.1", "30");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::WhiteBalance(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 明るさ
TEST_F(PanasonicNetworkCameraTest, invalidBrightnessTest) {
  client.setCamera("127.0.0.1", "31");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::BrightnessType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 設置タイプ
TEST_F(PanasonicNetworkCameraTest, invalidSetupTypeTest) {
  client.setCamera("127.0.0.1", "32");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::SetupType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}

// レスポンス異常, Return: -1
TEST_F(PanasonicNetworkCameraTest, responseErrorReturnNegativeTest) {
  client.setCamera("127.0.0.1", "33");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// レスポンス異常, statuscode: 401
TEST_F(PanasonicNetworkCameraTest, responseError401Test) {
  client.setCamera("127.0.0.1", "34");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// レスポンス異常, statuscode: -1
TEST_F(PanasonicNetworkCameraTest, responseErrorStatusCodeNegativeTest) {
  client.setCamera("127.0.0.1", "35");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}

// カメラ指定なしでの呼び出し
TEST_F(PanasonicNetworkCameraTest, noCameraSettingTest) {
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
}
