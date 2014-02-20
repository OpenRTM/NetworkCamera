
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
// スタブ側では、ポート番号-80 としたテスト番号で確認処理とレスポンスを
// 切り替えている
//
// ポート番号   | 確認項目
// 81  | パン左, 認証指定なし, サーバー指定あり, 前回呼び出し結果（成功）
// 82  | パン右, 認証指定あり, レスポンス正常（Return: 0）
// 83  | チルト上
// 84  | チルト下
// 85  | ズームイン
// 86  | ズームアウト
// 87-89  | フォーカス, 3パターン
// 90-95  | ホワイトバランス, 6パターン
// 96-98  | 明るさ, 3パターン
// 99-100 | 設置タイプ, 2パターン
// 101 | ホームポジション復帰, レスポンス正常（Return: home）
// 102 | サイズ  192x144, 画質Motion, レスポンス正常（image/jpeg）
// 103 | サイズ  320x240, 画質Clarity
// 104 | サイズ  640x480, 画質Standard
// 105 | サイズ 1280x960, 画質Standard
// 106 | サイズ1280x1024, 画質Standard
// 107 | 引数異常 サイズ
// 108 | 引数異常 画質
// 109 | 引数異常 フォーカス
// 110 | 引数異常 ホワイトバランス
// 111 | 引数異常 明るさ
// 112 | 引数異常 設置タイプ
// 113 | レスポンス異常, 前回呼び出し結果（失敗）, Return: -1
// 114 | レスポンス異常, 前回呼び出し結果（失敗）, statuscode: 401
// 115 | レスポンス異常, 前回呼び出し結果（失敗）, statuscode: -1

// パン
TEST_F(PanasonicNetworkCameraTest, panLeftTest) {
  client.setCamera("127.0.0.1", "81");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(true, client.isLastApiSuccess());
}
TEST_F(PanasonicNetworkCameraTest, panRightTest) {
  client.setCamera("127.0.0.1", "82");
  client.setAuthenticateUser("user", "password");
  client.movePanRight();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// チルト
TEST_F(PanasonicNetworkCameraTest, tiltUpTest) {
  client.setCamera("127.0.0.1", "83");
  client.moveTiltUp();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, tiltDownTest) {
  client.setCamera("127.0.0.1", "84");
  client.moveTiltDown();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ズーム
TEST_F(PanasonicNetworkCameraTest, zoomInTest) {
  client.setCamera("127.0.0.1", "85");
  client.zoomTele();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, zoomOutTest) {
  client.setCamera("127.0.0.1", "86");
  client.zoomWide();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// フォーカス
TEST_F(PanasonicNetworkCameraTest, focusNearTest) {
  client.setCamera("127.0.0.1", "87");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Near);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, focusFarTest) {
  client.setCamera("127.0.0.1", "88");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Far);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, focusAutoTest) {
  client.setCamera("127.0.0.1", "89");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoFocus);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ホワイトバランス
TEST_F(PanasonicNetworkCameraTest, whitebalanceAutoTest) {
  client.setCamera("127.0.0.1", "90");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoWB);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceIndoorTest) {
  client.setCamera("127.0.0.1", "91");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Indoor);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceFluorescentWhiteTest) {
  client.setCamera("127.0.0.1", "92");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Fluorescent_White);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceFluorescentDayTest) {
  client.setCamera("127.0.0.1", "93");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Fluorescent_Day);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceOutdoorTest) {
  client.setCamera("127.0.0.1", "94");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Outdoor);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, whitebalanceHoldTest) {
  client.setCamera("127.0.0.1", "95");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Hold);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 明るさ
TEST_F(PanasonicNetworkCameraTest, brightnessDarkerTest) {
  client.setCamera("127.0.0.1", "96");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Darker);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, brightnessBrighterTest) {
  client.setCamera("127.0.0.1", "97");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Brighter);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, brightnessDefaultTest) {
  client.setCamera("127.0.0.1", "98");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::DefaultBrightness);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 設置場所
TEST_F(PanasonicNetworkCameraTest, setupTypeCeilingTest) {
  client.setCamera("127.0.0.1", "99");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Ceiling);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, setupTypeDesktopTest) {
  client.setCamera("127.0.0.1", "100");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Desktop);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ホームポジション
TEST_F(PanasonicNetworkCameraTest, homepositionTest) {
  client.setCamera("127.0.0.1", "101");
  client.moveToHomePosition();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 画像取得
TEST_F(PanasonicNetworkCameraTest, getImage192x144Test) {
  client.setCamera("127.0.0.1", "102");
  int length;
  const char* p = client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w192x144, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Motion, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(28, length);
  ASSERT_STREQ("there is a image contents.\r\n", p);
}
TEST_F(PanasonicNetworkCameraTest, getImage320x240Test) {
  client.setCamera("127.0.0.1", "103");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w320x240, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Clarity, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, getImage640x480Test) {
  client.setCamera("127.0.0.1", "104");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w640x480, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, getImage1280x960Test) {
  client.setCamera("127.0.0.1", "105");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w1280x960, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(PanasonicNetworkCameraTest, getImage1280x1024Test) {
  client.setCamera("127.0.0.1", "106");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w1280x1024, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}


// 引数異常 サイズ
TEST_F(PanasonicNetworkCameraTest, invalidImageSizeTest) {
  client.setCamera("127.0.0.1", "107");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Resolution(10), openrtm_network_camera::panasonic::PanasonicNetworkCamera::Motion, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 画質
TEST_F(PanasonicNetworkCameraTest, invalidImageQualityTest) {
  client.setCamera("127.0.0.1", "108");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w320x240, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Quality(10), &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 フォーカス
TEST_F(PanasonicNetworkCameraTest, invalidFocusTest) {
  client.setCamera("127.0.0.1", "109");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::FocusType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 ホワイトバランス
TEST_F(PanasonicNetworkCameraTest, invalidWhiteBalanceTest) {
  client.setCamera("127.0.0.1", "110");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::WhiteBalance(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 明るさ
TEST_F(PanasonicNetworkCameraTest, invalidBrightnessTest) {
  client.setCamera("127.0.0.1", "111");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::BrightnessType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 設置タイプ
TEST_F(PanasonicNetworkCameraTest, invalidSetupTypeTest) {
  client.setCamera("127.0.0.1", "112");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::SetupType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}

// レスポンス異常, Return: -1
TEST_F(PanasonicNetworkCameraTest, responseErrorReturnNegativeTest) {
  client.setCamera("127.0.0.1", "113");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// レスポンス異常, statuscode: 401
TEST_F(PanasonicNetworkCameraTest, responseError401Test) {
  client.setCamera("127.0.0.1", "114");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// レスポンス異常, statuscode: -1
TEST_F(PanasonicNetworkCameraTest, responseErrorStatusCodeNegativeTest) {
  client.setCamera("127.0.0.1", "115");
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
