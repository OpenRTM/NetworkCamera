/*!
 * @file  SonyNetworkCamera.h
 * @brief NetworkCamera access class for Sony camera.
 * @date  2014-02-09
 */
#ifndef SONY_NETWORK_CAMERA_H
#define SONY_NETWORK_CAMERA_H

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
 * @namespace sony
 * @brief Sony�J����
 *
 */
namespace sony {

/*!
 * @class SonyNetworkCamera
 * @brief SonyNetworkCamera �N���X
 * 
 * Sony���l�b�g���[�N�J�����փA�N�Z�X���邽�߂̃N���X�B
 * �N���X�̃C���X�^���X������A�ڑ����؂�ւ��\�Ƃ���B
 *
 * �J�����Ăяo���̌��ʂ������������ۂ������\�b�h�ɂ��擾�\�Ƃ���B
 * �ڍׂȃG���[���̓��O�֏o�͂���B
 */
class SonyNetworkCamera
{
public:

  /*!
   * @brief �摜�T�C�Y
   */
  enum Resolution {
    w160x120,    //!< 160x120
    w320x240,    //!< 320x240
    w640x480,    //!< 640x480
  };

  /*!
   * @brief �t�H�[�J�X
   */
  enum FocusType {
    Near,          //!< �߂�
    Far,           //!< ����
    OnePushFocus,  //!< �����v�b�V��
  };

  /*!
   * @brief �z���C�g�o�����X
   */
  enum WhiteBalance {
    AutoWB,            //!< ����
    Indoor,            //!< ����
    Outdoor,           //!< ���O
    OnePushWB,         //!< �����v�b�V��
  };

  /*!
   * @brief �ݒu�^�C�v
   */
  enum SetupType {
    Ceiling,  //!< �V��
    Desktop,  //!< ���
  };

	SonyNetworkCamera(void);
	~SonyNetworkCamera(void);

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
   * �Ăяo�����ɉ𑜓x���p�����[�^�Ƃ��ė^����B
   *
   * @caution �߂�l�͌Ăяo�����ō폜���Ȃ�
   * @caution ����API�Ăяo���i�摜�ȊO���܂ނ��ׂāj�ɂ��f�[�^�����������B
   * ���������āA���̌Ăяo���O�Ɂi�K�v������΁j�߂�l���R�s�[���邱��
   *
   * @parma resolution  �𑜓x
   * @param p_length    �f�[�^���i�o�́j
   * @return �摜�f�[�^�z��ւ̃|�C���^
   */
  const char* getImage(const Resolution resolution, int* p_length);

  /*!
   * @brief �掿�̐ݒ�
   *
   * �J�����摜�̉掿��ݒ肷��B
   *
   * @param quality  �掿
   */
  void setQuality(const int quality = DEFAULT_QUALITY);

  /*!
   * @brief �������փp��
   */
	void movePanLeft(const int displacement = DEFAULT_PAN);

  /*!
   * @brief �E�����փp��
   */
  void movePanRight(const int displacement = DEFAULT_PAN);

  /*!
   * @brief �`���g�A�b�v
   */
  void moveTiltUp(const int displacement = DEFAULT_TILT);

  /*!
   * @brief �`���g�_�E��
   */
  void moveTiltDown(const int displacement = DEFAULT_TILT);

  /*!
   * @brief �Y�[���C��
   */
  void zoomTele(const int displacement = DEFAULT_ZOOM);

  /*!
   * @brief �Y�[���A�E�g
   */
  void zoomWide(const int displacement = DEFAULT_ZOOM);

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
  void adjustBrightness(const int brightness = DEFAULT_BRIGHTNESS);

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
  void movePan(const std::string& parameter, const int displacement);

  /*!
   * @brief �`���g����
   *
   * @param parameter �㉺
   */
  void moveTilt(const std::string& parameter, const int displacement);

  /*!
   * @brief �Y�[������
   *
   * @param parameter �C���A�E�g
   */
  void moveZoom(const std::string& parameter, const int displacement);

  /*!
   * @brief �p���E�`���g�E�Y�[������
   *
   * @param parameter ����p�����[�^
   */
  void movePTZ(const std::string& parameter);

  /*!
   * @brief �t�H�[�J�X���s
   *
   * @param parameter ����p�����[�^
   */
  void doFocus(const std::string& parameter);

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



  utility::HttpClient* p_client_;  //!< HttpClient�C���X�^���X

  std::string host_;      //!< �z�X�g���܂���IP�A�h���X
  std::string port_;      //!< �|�[�g�ԍ�

  std::string user_;      //!< Basic�F�ؗp���[�U�[
  std::string password_;  //!< Basic�F�ؗp�p�X���[�h

  bool lastResult;        //!< ���O��API�̎��s����, false:�Ȃ�炩�̃G���[, true:����

  static const int DEFAULT_QUALITY    = 5;  //!< �掿�̃f�t�H���g�l
  static const int DEFAULT_PAN        = 5;  //!< �p������̃f�t�H���g�ړ���
  static const int DEFAULT_TILT       = 5;  //!< �`���g����̃f�t�H���g�ړ���
  static const int DEFAULT_ZOOM       = 5;  //!< �Y�[������̃f�t�H���g�ړ���
  static const int DEFAULT_BRIGHTNESS = 5;  //!< ���邳�̃f�t�H���g�l


  SonyNetworkCamera(const SonyNetworkCamera&);
  void operator=(const SonyNetworkCamera&);
};

/*!
 * @brief �������琮�`�ςݕ�����ւ̕ϊ�
 *
 * �����ŗ^����ꂽ�������A2���\�����A
 * �s������0�Ŗ��߂��`���̕�����ɕϊ�����B
 *
 * @parma val  ���`�Ώۂ̐��l
 * @return ���`��̕�����
 */
std::string formatDigitFill0Width2(const int val);

} // sony
} // openrtm_network_camera

#endif