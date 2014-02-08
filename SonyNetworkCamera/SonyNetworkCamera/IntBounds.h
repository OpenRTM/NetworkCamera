/*!
 * @file  IntBounds.h
 * @brief bounds for int.
 * @date  2014-02-09
 */
#ifndef INT_BOUNDS_H
#define INT_BOUNDS_H

/*!
 * @namespace openrtm_network_camera
 * @brief OpenRTM NetworkCamera�p�R���|�[�l���g
 *
 */
namespace openrtm_network_camera {

/*!
 * @namespace sony
 * @brief Sony�J����
 *
 */
namespace sony {

/*!
 * @brief int�^�̋��E�N���X
 *
 * int�^�����ɑ΂��鋫�E��\���N���X
 * �e���v���[�g�p�����[�^�Ŏ������͈͂𒴂��鐔�l�́A�f�t�H���g�l��
 * �u��������B
 */
template<int lower, int upper, int defaultValue>
class IntBounds {
public:
  IntBounds() {
    if ((lower > upper) || (defaultValue < lower) || (upper < defaultValue)) {
      throw std::exception();
    }
  }
  ~IntBounds() {}
  int operator()(const int val) {
    if (val < lower) return defaultValue;
    if (val > upper) return defaultValue;
    return val;
  }
};

} // sony
} // openrtm_network_camera

#endif
