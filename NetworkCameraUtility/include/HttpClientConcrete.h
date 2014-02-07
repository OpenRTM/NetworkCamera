/*!
 * @file  HttpClientConcrete.h
 * @brief Http client using Boost.Asio
 *
 * Distributed under the Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 * 
 * @date  2014-02-06
 */
#ifndef HTTP_CLIENT_CONCRETE_H
#define HTTP_CLIENT_CONCRETE_H

#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>

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

/*!
 * @class HttpClientConcrete
 * @brief Boost.Asio ��p���� HttpClient �N���X
 * 
 * Http��p���ăA�N�Z�X���邽�߂̃N���X�B
 * �����́ABoost.Asio �����Ɏ�������B
 *
 * Boost.Asio �̃T���v�������ɋL�q
 * @see http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/example/cpp03/http/client/sync_client.cpp
 */
class HttpClientConcrete
{
public:
	HttpClientConcrete(void);
	~HttpClientConcrete(void);

  /*!
   * @brief GET���N�G�X�g�̎��s
   *
   * �w��z�X�g�ɑ΂���GET���N�G�X�g�����s����B�����͓����ōs����B
   * ���N�G�X�g���ɁAHttpClientConcrete#setBasicAuthenticationParameter ���\�b�h�ɂ��F�؏��
   * ���^�����Ă���ꍇ�́ABasic�F�ؗp�̏��������{����B
   * Http���X�|���X�R�[�h���A200�A204�ȊO�͕s���ȃ��X�|���X�Ɣ��f���A
   * �K�v�ȃw�b�_��R���e���c��ݒ肵�Ȃ��B
   * �܂��A�G���[�������ɂ́A�X�e�[�^�X�R�[�h��-1��ݒ肷��B
   *
   * @param host_name  �z�X�g���iIP�A�h���X��OK�j
   * @param path_name  �ΏۂƂȂ��΃p�X��
   * @param port       �|�[�g�ԍ�
   */
	void doGet(const std::string& host_name, const std::string& path_name, const std::string& port);

  /*!
   * @brief http���X�|���X�̃X�e�[�^�X�R�[�h���擾����B
   *
   * http���N�G�X�g�ɑ΂���X�e�[�^�X�R�[�h��Ԃ��B
   *
   * @return �X�e�[�^�X�R�[�h
   *         -1:�G���[����
   */
  int getStatusCode() const { return status_code_; }

  /*!
   * @brief http���X�|���X�̃w�b�_���擾����B
   *
   * http���N�G�X�g�ɑ΂���w�b�_�̔z����擾����B
   * �e�w�b�_�́@�w�b�_���F�p�����[�^�@�̌`���̕����񂪂��̂܂܊i�[����Ă���B
   *
   * @return �w�b�_
   */
  const std::vector<std::string>& getHeaders() const { return headers_; }

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
  const char* getContents() const { return contents_; }

  /*!
   * @brief http���X�|���X�̃R���e���c�^�C�v���擾����B
   *
   * http���N�G�X�g�ɑ΂���R���e���c�^�C�v���擾����B
   *
   * @return �R���e���c�^�C�v
   */
  const std::string& getContentType() const { return content_type_; }

  /*!
   * @brief http���X�|���X�̃R���e���c�����擾����B
   *
   * http���N�G�X�g�ɑ΂���R���e���c�����擾����B
   *
   * @return �R���e���c���A�f�[�^���Ȃ��ꍇ��0
   */
  size_t getContentLength() const { return content_length_; }

  /*!
   * @brief http���N�G�X�g���̔F�؏���ݒ肷��B
   *
   * http���N�G�X�g����Basic�F�ؗp�̔F�؏���ݒ肷��B
   * �w�肳�ꂽ�ꍇ�́A��ɔF�؏���t�����ă��N�G�X�g���s���B
   *
   * @param p_user      ���[�U�[��
   * @param p_password  �p�X���[�h
   */
  void setBasicAuthenticationParameter(const std::string& user, const std::string& password);

protected:
private:
  /*!
   * @brief http���X�|���X�Ɋ֘A���郁���o�[�ϐ��̏�����
   */
  void response_member_init();

  /*!
   * @brief �w�b�_�̏���
   *
   * ���X�|���X�f�[�^���������āA�w�b�_�����o���B
   *
   * @param p_socket    socket�ւ̃|�C���^
   * @param p_response  ���X�|���X�����p��streambuf
   */
  void processHeaders(boost::asio::ip::tcp::socket* p_socket, boost::asio::streambuf* p_response);

  /*!
   * @breif �R���e���c�^�C�v��ݒ肷��B
   */
  void setContentType();

  /*!
   * @breif �R���e���c����ݒ肷��B
   */
  void setContentLength();

  /*!
   * @breif �R���e���c�̏����B
   *
   * ���X�|���X�f�[�^���������āA�R���e���c�����o���B
   *
   * @param p_socket    socket�ւ̃|�C���^
   * @param p_response  ���X�|���X�����p��streambuf
   */
  void processContents(boost::asio::ip::tcp::socket* p_socket, boost::asio::streambuf* p_response);

  /*!
   * @breif �w�b�_�l�̎擾�B
   *
   * �w�b�_���������͂��A���̒l�����o���B
   *
   * @param target �w�b�_������
   * @return �w�b�_�l�i�R�����ȍ~�̒l�j
   */
  std::string getHeaderValue(const std::string& target);


  const static int ERROR_CODE = -1; //!< �G���[�������̃X�e�[�^�X�R�[�h

  // ���N�G�X�g�p�ϐ�
  std::string user_;      //!< ���[�U�[��
  std::string password_;  //!< �p�X���[�h

  // ���X�|���X�p�ϐ�
	int status_code_;                   //!< HTTP�₢���킹�̖߂�l�A�G���[��������-1�Ƃ���
	std::vector<std::string> headers_;  //!< �w�b�_
  std::string content_type_;          //!< �R���e���c�^�C�v
  size_t content_length_;             //!< �R���e���c��
  char* contents_;                    //!< �R���e���c


	HttpClientConcrete(const HttpClientConcrete&);
	void operator=(const HttpClientConcrete&);
};

} // utility
} // openrtm_network_camera

#endif