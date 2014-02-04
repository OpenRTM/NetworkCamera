
#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include <string>

namespace openrtm_network_camera {
namespace utility {

std::string convertToLower(const std::string& target);

std::string trim(const std::string& target, const char* trimCharacters = " \t\v\r\n");

std::string base64encode(const std::string& target);

} // utility
} // openrtm_network_camera

#endif // STRING_UTILITY_H
