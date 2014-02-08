
#include <iostream>
#include <sstream>
#include <fstream>

#include "SonyNetworkCamera.h"

int main(int argc, char* argv[])
{
  try {

    if (argc < 3) {
      std::cout << "Usage: exe <host> <port> [user] [password]\n";
      return 1;
    }

    openrtm_network_camera::sony::SonyNetworkCamera cam;

    cam.setCamera(argv[1], argv[2]);
    if(argc == 5) {
      cam.setAuthenticateUser(argv[3], argv[4]);
    }

    // “®ìƒTƒ“ƒvƒ‹
    std::cout << "pan left\n";
    cam.movePanLeft();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "pan right\n";
    cam.movePanRight();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "tilt down\n";
    cam.moveTiltDown();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "tilt up\n";
    cam.moveTiltUp();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "zoom tele\n";
    cam.zoomTele();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "zoom wide\n";
    cam.zoomWide();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "focus near\n";
    cam.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::Near);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "focus far\n";
    cam.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::Far);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "focus onepush\n";
    cam.adjustFocus(openrtm_network_camera::sony::SonyNetworkCamera::OnePushFocus);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "whitebalance inddor\n";
    cam.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::Indoor);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "whitebalance auto\n";
    cam.setWhiteBalance(openrtm_network_camera::sony::SonyNetworkCamera::AutoWB);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "brightness darker\n";
    cam.adjustBrightness(0);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "brightness darker\n";
    cam.adjustBrightness(2);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "brightness brighter\n";
    cam.adjustBrightness(10);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "brightness default\n";
    cam.adjustBrightness();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "setuptype ceiling\n";
    cam.setSetupType(openrtm_network_camera::sony::SonyNetworkCamera::Ceiling);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "setuptype desktop\n";
    cam.setSetupType(openrtm_network_camera::sony::SonyNetworkCamera::Desktop);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "set resolution\n";
    cam.setResolution(openrtm_network_camera::sony::SonyNetworkCamera::w160x120);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "get image\n";
    int length;
    const char* img = cam.getImage(&length);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::ofstream outfile("test.jpg", std::ios::out|std::ios::binary|std::ios::trunc);
    outfile.write(img, length);

    std::cout << "set resolution\n";
    cam.setResolution(openrtm_network_camera::sony::SonyNetworkCamera::w640x480);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }
    std::cout << "set quality\n";
    cam.setQuality(1);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::cout << "get image\n";
    const char* img2 = cam.getImage(&length);
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

    std::ofstream outfile2("test2.jpg", std::ios::out|std::ios::binary|std::ios::trunc);
    outfile2.write(img2, length);

    std::cout << "homeposition\n";
    cam.moveToHomePosition();
    if (!cam.isLastApiSuccess()) {
      std::cout << "error occured!\n";
    }

  } catch(...) {
    std::cout << "exception occured\n";
    return 1;
  }

	return 0;
}

