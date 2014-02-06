/**
 *
 */
#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "utility_dll_defs.h"

namespace openrtm_network_camera {
namespace utility {

//// クラスが内部にSTLを持ち、dllエクスポートする場合に必要
//// これらがないと warning C4251 が出る
//// @see http://support.microsoft.com/default.aspx?scid=kb;ja-jp;168958
//template class NETWORKCAMERAUTILITY_API std::allocator<char>;
//template class NETWORKCAMERAUTILITY_API std::allocator<std::string>;
//template class NETWORKCAMERAUTILITY_API std::basic_string<char>;
//template class NETWORKCAMERAUTILITY_API std::vector<std::string>;

// 実際のhttpクライアントの前方宣言
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

  // 呼び出し側で開放しない
  const char* const* getHeaders(int* p_size);

  // 呼び出し側で開放しない
  const char* getContents() const;

  // 呼び出し側で開放しない
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