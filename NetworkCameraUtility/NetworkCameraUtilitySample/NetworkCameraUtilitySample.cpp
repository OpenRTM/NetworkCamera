//
// NetworkCameraUtilitySample.cpp
//
//
// sync_client.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "HttpClient.h"

#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 4)
    {
      std::cout << "Usage: sync_client <server> <port> <path> [id] [password]\n";
      std::cout << "Example:\n";
      std::cout << "  sync_client www.boost.org /LICENSE_1_0.txt user password\n";
      return 1;
    }

    openrtm_network_camera::utility::HttpClient client;

    // Basic”FØ‚ª•K—v‚Èê‡
    if (argc == 6) {
      client.setBasicAuthenticationParameter(argv[4], argv[5]);
    }

    client.doGet(argv[1], argv[3], argv[2]);

    std::cout << "Http response status:" << client.getStatusCode() << "\n\n";
    if (0 > client.getStatusCode()) {
      std::cout << "error occured\n";
      return 1;
    }
    if ((200 != client.getStatusCode()) && (204 != client.getStatusCode())) {
      std::cout << "invalid status code: " << client.getStatusCode() << "\n";
      return 1;
    }

    std::cout << "Headers\n";
    std::vector<std::string> headers = client.getHeaders();

    for(std::vector<std::string>::iterator iter = headers.begin(); iter != headers.end(); ++iter) {
      std::cout << *iter << std::endl;
    }

    std::cout << "\n";

    std::cout << "Content-Type\n";
    std::cout << client.getContentType() << "\n\n";

    std::cout << "Contents\n";
    const char* contents = client.getContents();

    if (0 >= client.getContentLength()) {
      std::cout << "(no contents)\n";
      return 0;
    }

    std::string type = client.getContentType();
    if (std::string::npos != type.find("text")) {
      std::string str(contents, contents + client.getContentLength());
      std::cout << str;
    } else if (std::string::npos != type.find("image")) {
      std::ofstream outfile("test.jpg", std::ios::out|std::ios::binary|std::ios::trunc);
      outfile.write(contents, client.getContentLength());
    }
  }
  catch (std::exception& e)
  {
    std::cout << "Exception: " << e.what() << "\n";
  }

  return 0;
}