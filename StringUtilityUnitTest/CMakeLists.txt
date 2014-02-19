cmake_minimum_required (VERSION 2.8)

# プロジェクト名
#   VS2010の場合ソリューション名に使われる
project(StringUtilityUnitTest)

# テスト対象プロジェクトの場所
set(NETWORK_CAMERA_TMP "${PROJECT_SOURCE_DIR}/../../network_camera_utility")
get_filename_component(NETWORK_CAMERA_DIR ${NETWORK_CAMERA_TMP} ABSOLUTE)

# ソースファイル指定
set(SRC ${PROJECT_SOURCE_DIR}/src)
set(TARGET_SORCES
  ${NETWORK_CAMERA_DIR}/src/string_utility.cpp
  ${SRC}/string_utility_unittest.cpp
)

# マクロ定義
# Windowsバージョン, XP以上を指定
if (WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif(WIN32)

# Boost検索
#
# ライブラリが見つけられない場合のヒント
set(BOOST_ROOT       "C:/Program Files (x86)/boost/boost_1_55_0/")
set(BOOST_INCLUDEDIR "C:/Program Files (x86)/boost/boost_1_55_0/")
set(BOOST_LIBRARYDIR "C:/Program Files (x86)/boost/boost_1_55_0/lib32-msvc-10.0")
#
# リンク対象のライブラリを指定しないと、ライブラリサーチパスが設定されない
#find_package(Boost 1.55.0 REQUIRED)
find_package(Boost 1.55.0 REQUIRED COMPONENTS serialization system)

# Google C++ Test
set(GTEST_ROOT_TMP "${PROJECT_SOURCE_DIR}/../../../gtest-1.7.0")
get_filename_component(GTEST_ROOT ${GTEST_ROOT_TMP} ABSOLUTE)
set(GTEST_LIBRARIES gtest.lib gtest_main.lib)

# インクルードパス
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${NETWORK_CAMERA_DIR}/include)
include_directories(${GTEST_ROOT}/include)


# ライブラリサーチパス
link_directories(${Boost_LIBRARY_DIRS})
link_directories(${GTEST_ROOT}/build/)


# テストプロジェクトの生成
add_executable(${PROJECT_NAME}  ${TARGET_SORCES})

# ライブラリの指定
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})

