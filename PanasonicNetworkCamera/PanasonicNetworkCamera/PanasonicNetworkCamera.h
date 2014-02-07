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
 * @brief OpenRTM NetworkCamera�p�R���|�[�l���g
 *
 */
namespace openrtm_network_camera {

/*!
 * @namespace utility
 * @brief ���ʏ���
 *
 */
namespace utility {
  class HttpClient; // �O���錾
}

/*!
 * @namespace panasonic
 * @brief Panasonic�J����
 *
 */
namespace panasonic {

/*!
 * @class PanasonicNetworkCamera
 * @brief PanasonicNetworkCamera �N���X
 * 
 * Panasonic���l�b�g���[�N�J�����փA�N�Z�X���邽�߂̃N���X�B
 * �N���X�̃C���X�^���X������A�ڑ����؂�ւ��\�Ƃ���B
 */
class PanasonicNetworkCamera
{
public:

  /*!
   * @brief �摜�T�C�Y
   */
  enum Resolution {
    w192x144,    //!< 192x144
    w320x240,    //!< 320x240
    w640x480,    //!< 640x480
    w1280x960,   //!< 1280x960
    w1280x1024,  //!< 1280x1024
  };

  /*!
   * @brief �掿
   */
  enum Quality {
    Motion ,  //!< �����D��
    Standard, //!< �ʏ�
    Clarity,  //!< �掿�D��
  };

  /*!
   * @brief �t�H�[�J�X
   */
  enum FocusType {
    Near,       //!< �߂�
    AutoFocus,  //!< ����
    Far,        //!< ����
  };

  /*!
   * @brief �z���C�g�o�����X
   */
  enum WhiteBalance {
    AutoWB,            //!< ����
    Indoor,            //!< ����
    Fluorescent_White, //!< �u�����i���F�j
    Fluorescent_Day,   //!< �u�����i�����F�j
    Outdoor,           //!< ���O
    Hold,              //!< �z�[���h
  };

  /*!
   * @brief ���邳
   */
  enum BrightnessType {
    Darker,             //!< �Â�
    DefaultBrightness,  //!< �f�t�H���g�̖��邳
    Brighter,           //!< ���邭
  };

  /*!
   * @brief �ݒu�^�C�v
   */
  enum SetupType {
    Ceiling,  //!< �V��
    Desktop,  //!< ���
  };

	PanasonicNetworkCamera(void);
	~PanasonicNetworkCamera(void);

  /*!
   * @brief �J�����̐ݒ�
   */
  void setCamera(const std::string& host, const std::string& port);

  /*!
   * @brief �F�؃��[�U�[�̐ݒ�
   *
   * �󕶎����ݒ肷��΁A�w�肪���������B
   */
  void setAuthenticateUser(const std::string& user, const std::string password);

  /*!
   * @brief �摜�̎擾
   *
   * @caution �߂�l�͌Ăяo�����ō폜���Ȃ�
   * @caution ����API�Ăяo���i�摜�ȊO���܂ނ��ׂāj�ɂ��f�[�^�����������B
   * ���������āA���̌Ăяo���O�Ɂi�K�v������΁j�߂�l���R�s�[���邱��
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
   * @brief ���N�G�X�g�̎��s
   *
   * @caution �߂�l�͎��̌Ăяo�����ɍ폜�����
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