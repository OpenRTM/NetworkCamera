
#include <string>

#include "gtest/gtest.h"

#include "IntBounds.h"

// 以下、IntBoundsテンプレートクラスのテスト

// 制限適用
TEST(InteBoundsTest, boundPositiveRangeTest) {
  using openrtm_network_camera::sony::IntBounds;

  IntBounds<1, 10, 5> bound;

  ASSERT_EQ(1, bound(1));
  ASSERT_EQ(3, bound(3));
  ASSERT_EQ(5, bound(5));
  ASSERT_EQ(9, bound(9));
  ASSERT_EQ(10, bound(10));
  // 制限適用
  ASSERT_EQ(5, bound(-1));
  ASSERT_EQ(5, bound(11));
}
TEST(InteBoundsTest, boundNegativerangeTest) {
  using openrtm_network_camera::sony::IntBounds;

  IntBounds<-10, 1, -2> bound;

  ASSERT_EQ(-10, bound(-10));
  ASSERT_EQ(0, bound(0));
  ASSERT_EQ(1, bound(1));
  // 制限適用
  ASSERT_EQ(-2, bound(-11));
  ASSERT_EQ(-2, bound(2));

}

void construct1() {
  openrtm_network_camera::sony::IntBounds<10, 1, 5> bound;
  std::cout << bound(3);
}
TEST(InteBoundsTest, invalidTemplateArgumentMinMaxTest) {
  ASSERT_ANY_THROW(construct1());
}

void construct2() {
  openrtm_network_camera::sony::IntBounds<1, 10, 0> bound;
  std::cout << bound(3);
}
TEST(InteBoundsTest, invalidTemplateArgumentTooSmallDefaultValueTest) {
  ASSERT_ANY_THROW(construct2());
}

void construct3() {
  openrtm_network_camera::sony::IntBounds<1, 10, 11> bound;
  std::cout << bound(3);
}
TEST(InteBoundsTest, invalidTemplateArgumentTooLargeDefaultValueTest) {
  ASSERT_ANY_THROW(construct3());
}

void construct4() {
  openrtm_network_camera::sony::IntBounds<1, 10, 1> bound;
  std::cout << bound(3);
  ASSERT_EQ(1, bound(0));
}
TEST(InteBoundsTest, checkTemplateArgumentDefault1Test) {
  ASSERT_NO_THROW(construct4());
}

void construct5() {
  openrtm_network_camera::sony::IntBounds<1, 10, 10> bound;
  std::cout << bound(3);
  ASSERT_EQ(10, bound(0));
}
TEST(InteBoundsTest, checkTemplateArgumentDefault2Test) {
  ASSERT_NO_THROW(construct5());
}
