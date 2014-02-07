
#include <iostream>

#include "PanasonicNetworkCamera.h"

int main(int argc, char* argv[])
{
  try {

    if (argc < 3) {
      std::cout << "Usage: exe <host> <port> [user] [password]\n";
      return 1;
    }

    openrtm_network_camera::panasonic::PanasonicNetworkCamera pana_cam;

    pana_cam.setCamera(argv[1], argv[2]);
    if(argc == 5) {
      pana_cam.setAuthenticateUser(argv[3], argv[4]);
    }

    // “®ìƒTƒ“ƒvƒ‹‘‚­


  } catch(...) {
    std::cout << "exception occured\n";
    return 1;
  }

	return 0;
}

