cmake_minimum_required (VERSION 2.8)

# プロジェクト名
#   VS2010の場合ソリューション名に使われる
project(NetworkCameraUtility)

# ソースファイル指定
set(SRC ${PROJECT_SOURCE_DIR}/src)
set(TARGET_SORCES
  ${SRC}/string_utility.cpp
  ${SRC}/HttpClient.cpp
  ${SRC}/HttpClientConcrete.cpp
)

# マクロ定義
# Windowsバージョン, XP以上を指定
if (WIN32)
  add_definitions(-D_WIN32_WINNT=0x0501)
endif(WIN32)
#add_definitions(-DNETWORKCAMERAUTILITY_EXPORTS)

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

# インクルードパス
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR}/include)

# ライブラリサーチパス
link_directories(${Boost_LIBRARY_DIRS})

# DLL用のエクスポート設定ファイルを生成するモジュールのロード
include (GenerateExportHeader)

# 共有ライブラリの生成
add_library(NetworkCameraUtility SHARED ${TARGET_SORCES})

# エクスポート設定ファイルの生成
GENERATE_EXPORT_HEADER(NetworkCameraUtility
  BASE_NAME         NetworkCameraUtility
  EXPORT_MACRO_NAME NETWORKCAMERAUTILITY_API
  EXPORT_FILE_NAME  ${PROJECT_SOURCE_DIR}/include/utility_dll_defs.h
  STATIC_DEFINE     NetworkCameraUtility_BUILT_AS_STATIC)

# ライブラリの指定
#target_link_libraries(NetworkCameraUtility ${Boost_LIBRARIES})

