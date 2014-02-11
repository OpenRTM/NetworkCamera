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
 *
 * �J�����Ăяo���̌��ʂ������������ۂ������\�b�h�ɂ��擾�\�Ƃ���B
 * �ڍׂȃG���[���̓��O�֏o�͂���B
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
   *
   * @param host  �z�X�g���܂���IP�A�h���X
   * @param port  �|�[�g�ԍ�
   */
  void setCamera(const std::string& host, const std::string& port);

  /*!
   * @brief �F�؃��[�U�[�̐ݒ�
   *
   * Basic�F�ؗp�̃��[�U�[���ƃp�X���[�h��ݒ肷��B
   * �ݒ莞�́A��ɔF�؏��𑗐M����B
   * �󕶎����ݒ肷��΁A�w�肪���������B
   *
   * @param user      ���[�U�[��
   * @param password  �p�X���[�h
   */
  void setAuthenticateUser(const std::string& user, const std::string password);

  /*!
   * @brief �摜�̎擾
   *
   * �J��������̉摜���擾����B�t�H�[�}�b�g��JPEG�B
   * �Ăяo�����ɉ𑜓x�Ɖ掿���p�����[�^�Ƃ��ė^����B
   * ���ݐݒ蒆�̉𑜓x�Ɖ掿�ȊO���w�肷��ꍇ�A�ύX�������K�v�B
   * �𑜓x����щ掿�̎w��l���A�J���������Ή����Ă��Ȃ��ꍇ�̋����̓J�����Ɉˑ�����B
   *
   * @caution �߂�l�͌Ăяo�����ō폜���Ȃ�
   * @caution ����API�Ăяo���i�摜�ȊO���܂ނ��ׂāj�ɂ��f�[�^�����������B
   * ���������āA���̌Ăяo���O�Ɂi�K�v������΁j�߂�l���R�s�[���邱��
   *
   * @parma resolution  �𑜓x
   * @param quality     �掿
   * @param p_length    �f�[�^���i�o�́j
   * @return �摜�f�[�^�z��ւ̃|�C���^
   */
  const char* getImage(const Resolution resolution, const Quality quality, int* p_length);

  /*!
   * @brief �������փp��
   */
	void movePanLeft();

  /*!
   * @brief �E�����փp��
   */
  void movePanRight();

  /*!
   * @brief �`���g�A�b�v
   */
  void moveTiltUp();

  /*!
   * @brief �`���g�_�E��
   */
  void moveTiltDown();

  /*!
   * @brief �Y�[���C��
   */
  void zoomTele();

  /*!
   * @brief �Y�[���A�E�g
   */
  void zoomWide();

  /*!
   * @brief �t�H�[�J�X����
   *
   * @param type  �t�H�[�J�X�����^�C�v
   */
  void adjustFocus(const FocusType type);

  /*!
   * @brief �z���C�g�o�����X�ݒ�
   *
   * @param type  �z���C�g�o�����X�^�C�v
   */
  void setWhiteBalance(const WhiteBalance type);

  /*!
   * @brief ���邳����
   *
   * @param type  ���邳�����^�C�v
   */
  void adjustBrightness(const BrightnessType type);

  /*!
   * @brief �z�[���|�W�V�������A
   */
  void moveToHomePosition();

  /*!
   * @brief �ݒu�ꏊ�̐ݒ�
   *
   * @param type  �ݒu�ꏊ�^�C�v
   */
  void setSetupType(const SetupType type);

  /*!
   * @brief ���sAPI�̐���
   *
   * �O��Ăяo����API�������������ۂ��𒲂ׂ�B
   *
   * @return true : �O��Ăяo��������
   *         false: �O��Ăяo�������s
   */
  bool isLastApiSuccess() const { return lastResult; }

protected:
private:
  /*!
   * @brief �p������
   *
   * @param parameter ���E
   */
  void movePan(const std::string& parameter);

  /*!
   * @brief �`���g����
   *
   * @param parameter �㉺
   */
  void moveTilt(const std::string& parameter);

  /*!
   * @brief �Y�[������
   *
   * @param parameter �C���A�E�g
   */
  void moveZoom(const std::string& parameter);

  /*!
   * @brief �p���E�`���g�E�Y�[������
   *
   * @param path      API�̃p�X
   * @param parameter ����p�����[�^
   */
  void movePTZ(const std::string& path, const std::string& parameter);

  /*!
   * @brief ���X�|���X��Content-Type���e�L�X�g�ł���API�Ăяo��
   *
   * @param path API�̃p�X
   */
  void callTextTypeAPI(const std::string& path);

  /*!
   * @brief ���N�G�X�g�̎��s
   *
   * �l�b�g���[�N�J�����ւ�API���N�G�X�g���s���B
   * �Ăяo�����ʂɉ����āA�O��̎��s���ʂ�ݒ肷��B
   *
   * @caution �߂�l�͌Ăяo�����ō폜���Ȃ�
   * @caution ����API�Ăяo���ɂ�背�X�|���X�{�f�B�����������B
   *
   * @param path  API�̃p�X
   * @param p_length  ���X�|���X�f�[�^���i�o�́j
   * @return �R���e���c�i���X�|���X�{�f�B�j�ւ̃|�C���^
   */
  const char* doRequest(const std::string& path, int* p_length);

  /*!
   * @brief �z�肵���R���e���c���ۂ�
   *
   * ���N�G�X�g�őz�肵���R���e���c���ۂ��𔻒肷��B
   * ����́AContents-Type�w�b�_�̏��Ɋ�Â��B
   *
   * @param target_type �z�肵�Ă���R���e���c�^�C�v�iMIME�\�L�ŗ^����j
   * @return true : ���X�|���X�͑z�肵���R���e���c �܂���Contents-Type�w�b�_���Ȃ�
   *         false: ���X�|���X�͑z�肵���R���e���c�ƈقȂ�
   */
  bool isValidContentsType(const std::string& target_type);

  /*!
   * @brief �R���e���c�̉��
   *
   * Panasonic�̃l�b�g���[�N�J�����̑�����API�̓R���e���c�Ɏ��s����
   * ���܂߂ĕԂ��B���̂��߁A�R���e���c����͂��ăG���[���܂܂��
   * ����΂��̏������O�֏o�͂���B
   *
   * �G���[�R�[�h�����o���ꂽ�ꍇ�͑O��̎��s���ʂ����s�ɐݒ肷��B
   *
   * @param p_contents  �R���e���c�idoRequest�̖߂�l�j
   * @param length      �R���e���c��
   */
  void analyzeContents(const char* p_contents, int length);


  utility::HttpClient* p_client_;  //!< HttpClient�C���X�^���X

  std::string host_;      //!< �z�X�g���܂���IP�A�h���X
  std::string port_;      //!< �|�[�g�ԍ�

  std::string user_;      //!< Basic�F�ؗp���[�U�[
  std::string password_;  //!< Basic�F�ؗp�p�X���[�h

  bool lastResult;        //!< ���O��API�̎��s����, false:�Ȃ�炩�̃G���[, true:����


  PanasonicNetworkCamera(const PanasonicNetworkCamera&);
  void operator=(const PanasonicNetworkCamera&);
};

} // panasonic
} // openrtm_network_camera

#endif