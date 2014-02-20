
#include <string>

#include "gtest/gtest.h"

#include "PanasonicNetworkCamera.h"

// �e�X�g�t�B�N�X�`��
class PanasonicNetworkCameraTest : public ::testing::Test {
public:
  virtual void SetUp() {
  }
  openrtm_network_camera::panasonic::PanasonicNetworkCamera client;
};


// �ȉ��APanasonicNetworkCameraTest�N���X�̃e�X�g
// ���ۂ̏����N���X HttpClientConcrete �𐳂����Ăяo���Ă��邱�Ƃ��m�F

// �e�X�g�P�[�X�̓|�[�g�ԍ���p���ċ�ʂ���
// �X�^�u���ł́A�|�[�g�ԍ�-80 �Ƃ����e�X�g�ԍ��Ŋm�F�����ƃ��X�|���X��
// �؂�ւ��Ă���
//
// �|�[�g�ԍ�   | �m�F����
// 81  | �p����, �F�؎w��Ȃ�, �T�[�o�[�w�肠��, �O��Ăяo�����ʁi�����j
// 82  | �p���E, �F�؎w�肠��, ���X�|���X����iReturn: 0�j
// 83  | �`���g��
// 84  | �`���g��
// 85  | �Y�[���C��
// 86  | �Y�[���A�E�g
// 87-89  | �t�H�[�J�X, 3�p�^�[��
// 90-95  | �z���C�g�o�����X, 6�p�^�[��
// 96-98  | ���邳, 3�p�^�[��
// 99-100 | �ݒu�^�C�v, 2�p�^�[��
// 101 | �z�[���|�W�V�������A, ���X�|���X����iReturn: home�j
// 102 | �T�C�Y  192x144, �掿Motion, ���X�|���X����iimage/jpeg�j
// 103 | �T�C�Y  320x240, �掿Clarity
// 104 | �T�C�Y  640x480, �掿Standard
// 105 | �T�C�Y 1280x960, �掿Standard
// 106 | �T�C�Y1280x1024, �掿Standard
// 107 | �����ُ� �T�C�Y
// 108 | �����ُ� �掿
// 109 | �����ُ� �t�H�[�J�X
// 110 | �����ُ� �z���C�g�o�����X
// 111 | �����ُ� ���邳
// 112 | �����ُ� �ݒu�^�C�v
// 113 | ���X�|���X�ُ�, �O��Ăяo�����ʁi���s�j, Return: -1
// 114 | ���X�|���X�ُ�, �O��Ăяo�����ʁi���s�j, statuscode: 401
// 115 | ���X�|���X�ُ�, �O��Ăяo�����ʁi���s�j, statuscode: -1

// �p��
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

// �`���g
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

// �Y�[��
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

// �t�H�[�J�X
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

// �z���C�g�o�����X
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

// ���邳
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

// �ݒu�ꏊ
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

// �z�[���|�W�V����
TEST_F(PanasonicNetworkCameraTest, homepositionTest) {
  client.setCamera("127.0.0.1", "101");
  client.moveToHomePosition();
  if (HasFatalFailure()) {
    FAIL();
  }
}

// �摜�擾
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


// �����ُ� �T�C�Y
TEST_F(PanasonicNetworkCameraTest, invalidImageSizeTest) {
  client.setCamera("127.0.0.1", "107");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Resolution(10), openrtm_network_camera::panasonic::PanasonicNetworkCamera::Motion, &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// �����ُ� �掿
TEST_F(PanasonicNetworkCameraTest, invalidImageQualityTest) {
  client.setCamera("127.0.0.1", "108");
  int length;
  client.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w320x240, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Quality(10), &length);
  if (HasFatalFailure()) {
    FAIL();
  }
}
// �����ُ� �t�H�[�J�X
TEST_F(PanasonicNetworkCameraTest, invalidFocusTest) {
  client.setCamera("127.0.0.1", "109");
  client.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::FocusType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// �����ُ� �z���C�g�o�����X
TEST_F(PanasonicNetworkCameraTest, invalidWhiteBalanceTest) {
  client.setCamera("127.0.0.1", "110");
  client.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::WhiteBalance(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// �����ُ� ���邳
TEST_F(PanasonicNetworkCameraTest, invalidBrightnessTest) {
  client.setCamera("127.0.0.1", "111");
  client.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::BrightnessType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}
// �����ُ� �ݒu�^�C�v
TEST_F(PanasonicNetworkCameraTest, invalidSetupTypeTest) {
  client.setCamera("127.0.0.1", "112");
  client.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::SetupType(10));
  if (HasFatalFailure()) {
    FAIL();
  }
}

// ���X�|���X�ُ�, Return: -1
TEST_F(PanasonicNetworkCameraTest, responseErrorReturnNegativeTest) {
  client.setCamera("127.0.0.1", "113");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// ���X�|���X�ُ�, statuscode: 401
TEST_F(PanasonicNetworkCameraTest, responseError401Test) {
  client.setCamera("127.0.0.1", "114");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}
// ���X�|���X�ُ�, statuscode: -1
TEST_F(PanasonicNetworkCameraTest, responseErrorStatusCodeNegativeTest) {
  client.setCamera("127.0.0.1", "115");
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
  ASSERT_EQ(false, client.isLastApiSuccess());
}

// �J�����w��Ȃ��ł̌Ăяo��
TEST_F(PanasonicNetworkCameraTest, noCameraSettingTest) {
  client.movePanLeft();
  if (HasFatalFailure()) {
    FAIL();
  }
}
