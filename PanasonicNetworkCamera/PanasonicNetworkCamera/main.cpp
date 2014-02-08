
#include <iostream>
#include <sstream>
#include <fstream>

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

    // “®ìƒTƒ“ƒvƒ‹
    std::cout << "pan left\n";
    pana_cam.movePanLeft();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "pan right\n";
    pana_cam.movePanRight();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "tilt down\n";
    pana_cam.moveTiltDown();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "tilt up\n";
    pana_cam.moveTiltUp();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "zoom tele\n";
    pana_cam.zoomTele();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "zoom wide\n";
    pana_cam.zoomWide();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "focus near\n";
    pana_cam.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Near);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "focus far\n";
    pana_cam.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Far);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "focus auto\n";
    pana_cam.adjustFocus(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoFocus);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "whitebalance inddor\n";
    pana_cam.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Indoor);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "whitebalance auto\n";
    pana_cam.setWhiteBalance(openrtm_network_camera::panasonic::PanasonicNetworkCamera::AutoWB);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "brightness darker\n";
    pana_cam.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Darker);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "brightness darker\n";
    pana_cam.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Darker);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "brightness brighter\n";
    pana_cam.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Brighter);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "brightness default\n";
    pana_cam.adjustBrightness(openrtm_network_camera::panasonic::PanasonicNetworkCamera::DefaultBrightness);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "setuptype ceiling\n";
    pana_cam.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Ceiling);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "setuptype desktop\n";
    pana_cam.setSetupType(openrtm_network_camera::panasonic::PanasonicNetworkCamera::Desktop);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "get image\n";
    int length;
    const char* img = pana_cam.getImage(openrtm_network_camera::panasonic::PanasonicNetworkCamera::w640x480, openrtm_network_camera::panasonic::PanasonicNetworkCamera::Standard, &length);
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::ofstream outfile("test.jpg", std::ios::out|std::ios::binary|std::ios::trunc);
    outfile.write(img, length);

    std::cout << "homeposition\n";
    pana_cam.moveToHomePosition();
    if (!pana_cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

  } catch(...) {
    std::cout << "exception occured\n";
    return 1;
  }

	return 0;
}

