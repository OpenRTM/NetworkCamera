/*!
 * @file  HttpClient.h
 * @brief Http client for dll export
 * @date  2014-02-06
 */
#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "utility_dll_defs.h"

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

class HttpClientConcrete;

/*!
 * @class HttpClient
 * @brief HttpClient �N���X
 * 
 * Http��p���ăA�N�Z�X���邽�߂̃N���X�B
 * ���ۂ̏����́AHttpClientConcrete�N���X�ֈϏ�����B
 * DLL�쐬���ɃG�N�X�|�[�g����N���X������STL���g���Ă���ꍇ�A
 * ��肪���������̂ŁA�O���փG�N�X�|�[�g����N���X�i�{�N���X�j�ł�
 * STL����菜�����B
 *
 * @see http://support.microsoft.com/default.aspx?scid=kb;ja-jp;168958
 * @see http://stackoverflow.com/questions/8976617/when-exporting-stl-stdbasic-string-template-from-dll-i-get-a-lnk2005-error
 */
class NETWORKCAMERAUTILITY_API HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);

  /*!
   * @brief GET���N�G�X�g�̎��s
   *
   * �w��z�X�g�ɑ΂���GET���N�G�X�g�����s����B�����͓����ōs����B
   * ���N�G�X�g���ɁAHttpClient#setBasicAuthenticationParameter ���\�b�h�ɂ��F�؏��
   * ���^�����Ă���ꍇ�́ABasic�F�ؗp�̏��������{����B
   * Http���X�|���X�R�[�h���A200�A204�ȊO�͕s���ȃ��X�|���X�Ɣ��f���A
   * �K�v�ȃw�b�_��R���e���c��ݒ肵�Ȃ��B
   * �܂��A�G���[�������ɂ́A�X�e�[�^�X�R�[�h��-1��ݒ肷��B
   *
   * @param p_host_name  �z�X�g���iIP�A�h���X��OK�j
   * @param p_path_name  �ΏۂƂȂ��΃p�X��
   * @param p_port       �|�[�g�ԍ�
   */
	void doGet(const char* p_host_name, const char* p_path_name, const char* p_port);

  /*!
   * @brief http���X�|���X�̃X�e�[�^�X�R�[�h���擾����B
   *
   * http���N�G�X�g�ɑ΂���X�e�[�^�X�R�[�h��Ԃ��B
   *
   * @return �X�e�[�^�X�R�[�h
   *         -1:�G���[����
   */
  int getStatusCode() const;

  /*!
   * @brief http���X�|���X�̃w�b�_���擾����B
   *
   * http���N�G�X�g�ɑ΂���w�b�_�̔z����擾����B
   * �e�w�b�_�́@�w�b�_���F�p�����[�^�@�̌`���̕����񂪂��̂܂܊i�[����Ă���B
   *
   * @param p_size �w�b�_��
   * @return �w�b�_�̔z��ւ̃|�C���^
   * @caution �߂�l�͌Ăяo�����ŊJ�����Ȃ�
   */
  const char* const* getHeaders(int* p_size);

  /*!
   * @brief http���X�|���X�̃R���e���c���擾����B
   *
   * http���N�G�X�g�ɑ΂���R���e���c���擾����B
   * �X�e�[�^�X�R�[�h��204�iNo Contents�j�̏ꍇ��A200�iOK�j�̏ꍇ�ł��A
   * �R���e���c���܂܂�Ă��Ȃ��ꍇ������B
   * �R���e���c�̓e�L�X�g�̏ꍇ���o�C�i���f�[�^�̏ꍇ������̂ŁA
   * �擾�����f�[�^�́AgetContentType �� getContentLength �ɉ����ēK�؂�
   * �������s�����ƁB
   *
   * @return �R���e���c�f�[�^�ւ̃|�C���^
   * @caution �߂�l�͌Ăяo�����ŊJ�����Ȃ�
   */
  const char* getContents() const;

  /*!
   * @brief http���X�|���X�̃R���e���c�^�C�v���擾����B
   *
   * http���N�G�X�g�ɑ΂���R���e���c�^�C�v���擾����B
   *
   * @return �R���e���c�^�C�v������ւ̃|�C���^�A������\0
   * @caution �߂�l�͌Ăяo�����ŊJ�����Ȃ�
   */
  const char* getContentType() const;

  /*!
   * @brief http���X�|���X�̃R���e���c�����擾����B
   *
   * http���N�G�X�g�ɑ΂���R���e���c�����擾����B
   *
   * @return �R���e���c���A�f�[�^���Ȃ��ꍇ��0
   */
  size_t getContentLength() const;

  /*!
   * @brief http���N�G�X�g���̔F�؏���ݒ肷��B
   *
   * http���N�G�X�g����Basic�F�ؗp�̔F�؏���ݒ肷��B
   * �w�肳�ꂽ�ꍇ�́A��ɔF�؏���t�����ă��N�G�X�g���s���B
   *
   * @param p_user      ���[�U�[��
   * @param p_password  �p�X���[�h
   */
  void setBasicAuthenticationParameter(const char* p_user, const char* p_password);

protected:
private:
  /*!
   * @brief �w�b�_�i�[�p�R���e�i�̍폜
   */
  void deleteHeaderContainer();

  HttpClientConcrete* p_client_;     //!< ���ۂ�http�������s���N���X�̃C���X�^���X
  const char** p_header_container_;  //!< �w�b�_�i�[�p�R���e�i


  HttpClient(const HttpClient&);
  void operator=(const HttpClient&);
};

} // utility
} // openrtm_network_camera

#endif