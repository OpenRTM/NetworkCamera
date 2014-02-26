
#include <string>

#include "gtest/gtest.h"

#include "SonyNetworkCamera.h"

// テストフィクスチャ
class SonyNetworkCameraTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::sony::SonyNetworkCamera client;
};


// 以下、SonyNetworkCameraTestクラスのテスト
//
// テストケースはポート番号（テスト番号）を用いて区別する
//
// ポート番号 | 確認項目
// 1          | パン左, デフォルト引数, 認証指定なし, サーバー指定あり, 前回呼び出し結果（成功）
// 2-4        | パン左, 数値3パターン
// 5          | パン右, デフォルト引数, 認証指定あり, レスポンス正常（204）
// 6-8        | パン右, 数値3パターン
// 9          | チルト上, デフォルト引数
// 10-12      | チルト上, 数値3パターン
// 13         | チルト下, デフォルト引数
// 14-16      | チルト下, 数値3パターン
// 17         | ズームイン, デフォルト引数
// 18-20      | ズームイン, 数値3パターン
// 21         | ズームアウト, デフォルト引数
// 22-24      | ズームアウト, 数値3パターン
// 25-27      | フォーカス, 3パターン
// 28-31      | ホワイトバランス, 4パターン
// 32         | 明るさ, デフォルト引数
// 33-35      | 明るさ, 数値3パターン
// 36,37      | 設置タイプ, 2パターン
// 38         | ホームポジション復帰
// 39         | サイズ  160x120, レスポンス正常（image/jpeg）
// 40         | サイズ  320x240
// 41         | サイズ  640x480
// 42         | 画質, デフォルト
// 43-45      | 画質, 数値3パターン
//
// 46         | 引数異常 サイズ
// 47,48      | 引数異常 画質, 2パターン
// 49         | 引数異常 フォーカス
// 50         | 引数異常 ホワイトバランス
// 51,52      | 引数異常 明るさ, 2パターン
// 53         | 引数異常 設置タイプ
// 54,55      | 引数異常 パン左, 2パターン
// 56,57      | 引数異常 パン右, 2パターン
// 58,59      | 引数異常 チルト上, 2パターン
// 60,61      | 引数異常 チルト下, 2パターン
// 62,63      | 引数異常 ズームイン, 2パターン
// 64,65      | 引数異常 ズームアウト, 2パターン
//
// 66         | レスポンス異常, 前回呼び出し結果（失敗）, statuscode: 401
// 67         | レスポンス異常, 前回呼び出し結果（失敗）, statuscode: -1

// パン
TEST_F(SonyNetworkCameraTest, panLeftDefaultTest) {
  client.setCamera("127.0.0.1", "1");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(true, client.isLastApiSuccess());
}
TEST_F(SonyNetworkCameraTest, panLeftLowTest) {
  client.setCamera("127.0.0.1", "2");
  client.movePanLeft(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, panLeftTest) {
  client.setCamera("127.0.0.1", "3");
  client.movePanLeft(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, panLeftHighTest) {
  client.setCamera("127.0.0.1", "4");
  client.movePanLeft(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, panRightDefaultTest) {
  client.setCamera("127.0.0.1", "5");
  client.setAuthenticateUser("user", "password");
  client.movePanRight();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, panRightLowTest) {
  client.setCamera("127.0.0.1", "6");
  client.movePanRight(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, panRightTest) {
  client.setCamera("127.0.0.1", "7");
  client.movePanRight(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, panRightHighTest) {
  client.setCamera("127.0.0.1", "8");
  client.movePanRight(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// チルト
TEST_F(SonyNetworkCameraTest, tiltUpDefaultTest) {
  client.setCamera("127.0.0.1", "9");
  client.moveTiltUp();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltUpLowTest) {
  client.setCamera("127.0.0.1", "10");
  client.moveTiltUp(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltUpTest) {
  client.setCamera("127.0.0.1", "11");
  client.moveTiltUp(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltUpHighTest) {
  client.setCamera("127.0.0.1", "12");
  client.moveTiltUp(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltDownDefaultTest) {
  client.setCamera("127.0.0.1", "13");
  client.moveTiltDown();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltDownLowTest) {
  client.setCamera("127.0.0.1", "14");
  client.moveTiltDown(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltDownTest) {
  client.setCamera("127.0.0.1", "15");
  client.moveTiltDown(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, tiltDownHighTest) {
  client.setCamera("127.0.0.1", "16");
  client.moveTiltDown(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ズーム
TEST_F(SonyNetworkCameraTest, zoomInDefaultTest) {
  client.setCamera("127.0.0.1", "17");
  client.zoomTele();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomInLowTest) {
  client.setCamera("127.0.0.1", "18");
  client.zoomTele(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomInTest) {
  client.setCamera("127.0.0.1", "19");
  client.zoomTele(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomInHighTest) {
  client.setCamera("127.0.0.1", "20");
  client.zoomTele(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomOutDefaultTest) {
  client.setCamera("127.0.0.1", "21");
  client.zoomWide();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomOutLowTest) {
  client.setCamera("127.0.0.1", "22");
  client.zoomWide(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomOutTest) {
  client.setCamera("127.0.0.1", "23");
  client.zoomWide(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, zoomOutHighTest) {
  client.setCamera("127.0.0.1", "24");
  client.zoomWide(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// フォーカス
TEST_F(SonyNetworkCameraTest, focusNearTest) {
  client.setCamera("127.0.0.1", "25");
  client.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::Near);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, focusFarTest) {
  client.setCamera("127.0.0.1", "26");
  client.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::Far);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, focusOnepushTest) {
  client.setCamera("127.0.0.1", "27");
  client.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::OnePushFocus);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ホワイトバランス
TEST_F(SonyNetworkCameraTest, whitebalanceAutoTest) {
  client.setCamera("127.0.0.1", "28");
  client.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::AutoWB);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, whitebalanceIndoorTest) {
  client.setCamera("127.0.0.1", "29");
  client.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::Indoor);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, whitebalanceOutdoorTest) {
  client.setCamera("127.0.0.1", "30");
  client.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::Outdoor);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, whitebalanceOnepushTest) {
  client.setCamera("127.0.0.1", "31");
  client.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::OnePushWB);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 明るさ
TEST_F(SonyNetworkCameraTest, brightnessDefaultTest) {
  client.setCamera("127.0.0.1", "32");
  client.adjustBrightness();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, brightnessLowTest) {
  client.setCamera("127.0.0.1", "33");
  client.adjustBrightness(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, brightnessTest) {
  client.setCamera("127.0.0.1", "34");
  client.adjustBrightness(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, brightnessHighTest) {
  client.setCamera("127.0.0.1", "35");
  client.adjustBrightness(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 設置場所
TEST_F(SonyNetworkCameraTest, setupTypeCeilingTest) {
  client.setCamera("127.0.0.1", "36");
  client.setSetupType(openrtm_network_camera::sony::SonyNetworkCamera::Ceiling);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, setupTypeDesktopTest) {
  client.setCamera("127.0.0.1", "37");
  client.setSetupType(openrtm_network_camera::sony::SonyNetworkCamera::Desktop);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ホームポジション
TEST_F(SonyNetworkCameraTest, homepositionTest) {
  client.setCamera("127.0.0.1", "38");
  client.moveToHomePosition();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 画像取得
TEST_F(SonyNetworkCameraTest, getImage160x120Test) {
  client.setCamera("127.0.0.1", "39");
  int length;
  const char* p = client.getImage(openrtm_network_camera::sony::SonyNetworkCamera::w160x120, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(28, length);
  ASSERT_STREQ("there is a image contents.\r\n", p);
}
TEST_F(SonyNetworkCameraTest, getImage320x240Test) {
  client.setCamera("127.0.0.1", "40");
  int length;
  client.getImage(openrtm_network_camera::sony::SonyNetworkCamera::w320x240, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, getImage640x480Test) {
  client.setCamera("127.0.0.1", "41");
  int length;
  client.getImage(openrtm_network_camera::sony::SonyNetworkCamera::w640x480, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// 画質
TEST_F(SonyNetworkCameraTest, imageQualityDefaultTest) {
  client.setCamera("127.0.0.1", "42");
  client.setQuality();
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, imageQualityLowTest) {
  client.setCamera("127.0.0.1", "43");
  client.setQuality(1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, imageQualityTest) {
  client.setCamera("127.0.0.1", "44");
  client.setQuality(3);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, imageQualityHighTest) {
  client.setCamera("127.0.0.1", "45");
  client.setQuality(10);
  if (HasFatalFailure()) {
    FAIL();
  }
}


// 引数異常 サイズ
TEST_F(SonyNetworkCameraTest, invalidImageSizeTest) {
  client.setCamera("127.0.0.1", "46");
  int length;
  client.getImage(openrtm_network_camera::sony::SonyNetworkCamera::Resolution(10), &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 画質
TEST_F(SonyNetworkCameraTest, invalidImageQualityLowTest) {
  client.setCamera("127.0.0.1", "47");
  client.setQuality(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidImageQualityHighTest) {
  client.setCamera("127.0.0.1", "48");
  client.setQuality(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 フォーカス
TEST_F(SonyNetworkCameraTest, invalidFocusTest) {
  client.setCamera("127.0.0.1", "49");
  client.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::FocusType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 ホワイトバランス
TEST_F(SonyNetworkCameraTest, invalidWhiteBalanceTest) {
  client.setCamera("127.0.0.1", "50");
  client.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::WhiteBalance(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 明るさ
TEST_F(SonyNetworkCameraTest, invalidBrightnessLowTest) {
  client.setCamera("127.0.0.1", "51");
  client.adjustBrightness(-1);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidBrightnessHightTest) {
  client.setCamera("127.0.0.1", "52");
  client.adjustBrightness(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 設置タイプ
TEST_F(SonyNetworkCameraTest, invalidSetupTypeTest) {
  client.setCamera("127.0.0.1", "53");
  client.setSetupType(openrtm_network_camera::sony::SonyNetworkCamera::SetupType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 パン左
TEST_F(SonyNetworkCameraTest, invalidPanLeftLowTest) {
  client.setCamera("127.0.0.1", "54");
  client.movePanLeft(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidPanLeftHighTest) {
  client.setCamera("127.0.0.1", "55");
  client.movePanLeft(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 パン右
TEST_F(SonyNetworkCameraTest, invalidPanRightLowTest) {
  client.setCamera("127.0.0.1", "56");
  client.movePanRight(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidPanRightHighTest) {
  client.setCamera("127.0.0.1", "57");
  client.movePanRight(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 チルト上
TEST_F(SonyNetworkCameraTest, invalidTiltUpLowTest) {
  client.setCamera("127.0.0.1", "58");
  client.moveTiltUp(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidTiltUpHighTest) {
  client.setCamera("127.0.0.1", "59");
  client.moveTiltUp(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 チルト下
TEST_F(SonyNetworkCameraTest, invalidTiltDownLowTest) {
  client.setCamera("127.0.0.1", "60");
  client.moveTiltDown(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidTiltDownHighTest) {
  client.setCamera("127.0.0.1", "61");
  client.moveTiltDown(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 ズームイン
TEST_F(SonyNetworkCameraTest, invalidZoomInLowTest) {
  client.setCamera("127.0.0.1", "62");
  client.zoomTele(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidZoomInHighTest) {
  client.setCamera("127.0.0.1", "63");
  client.zoomTele(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// 引数異常 ズームアウト
TEST_F(SonyNetworkCameraTest, invalidZoomOutLowTest) {
  client.setCamera("127.0.0.1", "64");
  client.zoomWide(0);
  if (HasFatalFailure()) {
    FAIL();
  }
}
TEST_F(SonyNetworkCameraTest, invalidZoomOutHighTest) {
  client.setCamera("127.0.0.1", "65");
  client.zoomWide(11);
  if (HasFatalFailure()) {
    FAIL();
  }
}

// レスポンス異常, statuscode: 401
TEST_F(SonyNetworkCameraTest, responseError401Test) {
  client.setCamera("127.0.0.1", "66");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// レスポンス異常, statuscode: -1
TEST_F(SonyNetworkCameraTest, responseErrorStatusCodeNegativeTest) {
  client.setCamera("127.0.0.1", "67");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}

// カメラ指定なしでの呼び出し
TEST_F(SonyNetworkCameraTest, noCameraSettingTest) {
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
}


// 以下、formatDigitFill0Width2関数のテスト

// １桁の正の数字
TEST(formatDigitFill0Width2Test, positiveLessThan10Test) {
  ASSERT_EQ(std::string("02"), openrtm_network_camera::sony::formatDigitFill0Width2(2));
}
// 2桁の正の数字
TEST(formatDigitFill0Width2Test, positiveMoreThanEq10Test) {
  ASSERT_EQ(std::string("18"), openrtm_network_camera::sony::formatDigitFill0Width2(18));
}
// ゼロ
TEST(formatDigitFill0Width2Test, zeroTest) {
  ASSERT_EQ(std::string("00"), openrtm_network_camera::sony::formatDigitFill0Width2(0));
}
// 本関数の処理対象外
//
// 3桁の正の数字
TEST(formatDigitFill0Width2Test, positiveMoreThan100Test) {
  ASSERT_EQ(std::string("100"), openrtm_network_camera::sony::formatDigitFill0Width2(100));
}
// 負の数字
TEST(formatDigitFill0Width2Test, negativeNumberTest) {
  ASSERT_EQ(std::string("-1"), openrtm_network_camera::sony::formatDigitFill0Width2(-1));
}
