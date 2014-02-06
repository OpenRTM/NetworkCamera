/**
 *
 */
#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "utility_dll_defs.h"

namespace openrtm_network_camera {
namespace utility {

//// �N���X��������STL�������Adll�G�N�X�|�[�g����ꍇ�ɕK�v
//// ����炪�Ȃ��� warning C4251 ���o��
//// @see http://support.microsoft.com/default.aspx?scid=kb;ja-jp;168958
//template class NETWORKCAMERAUTILITY_API std::allocator<char>;
//template class NETWORKCAMERAUTILITY_API std::allocator<std::string>;
//template class NETWORKCAMERAUTILITY_API std::basic_string<char>;
//template class NETWORKCAMERAUTILITY_API std::vector<std::string>;

// ���ۂ�http�N���C�A���g�̑O���錾
class HttpClientConcrete;

/**
 *
 */
class NETWORKCAMERAUTILITY_API HttpClient
{
public:
	HttpClient(void);
	~HttpClient(void);

	void doGet(const char* p_host_name, const char* p_path_name, const char* p_port);

  int getStatusCode() const;

  // �Ăяo�����ŊJ�����Ȃ�
  const char* const* getHeaders(int* p_size);

  // �Ăяo�����ŊJ�����Ȃ�
  const char* getContents() const;

  // �Ăяo�����ŊJ�����Ȃ�
  const char* getContentType() const;

  size_t getContentLength() const;

  void setBasicAuthenticationParameter(const char* p_user, const char* p_password);

protected:
private:
  void deleteHeaderContainer();

  HttpClientConcrete* p_client_;
  const char** p_header_container_;

  HttpClient(const HttpClient&);
  void operator=(const HttpClient&);
};

} // utility
} // openrtm_network_camera

#endif