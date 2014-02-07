/*!
 * @file  string_utility.h
 * @brief some string utility functions.
 * @date  2014-02-06
 */
#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

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

/*!
 * @brief ��������������ɕϊ�����B
 *
 * @param target  �����Ώە�����
 * @return �������ɕϊ�����������
 */
std::string convertToLower(const std::string& target);

/*!
 * @brief ������̑O����󔒂��폜����B
 *
 * @param target  �����Ώە�����
 * @param trimCharacters �폜�Ώۂ̋󔒕���
 * @return �󔒍폜��̕�����
 */
std::string trim(const std::string& target, const char* trimCharacters = " \t\v\r\n");

/*!
 * @brief base64�G���R�[�h��̕�������擾����B
 *
 * @param target  �����Ώە�����
 * @return base64�G���R�[�h��̕�����
 */
std::string base64encode(const std::string& target);

} // utility
} // openrtm_network_camera

#endif // STRING_UTILITY_H
