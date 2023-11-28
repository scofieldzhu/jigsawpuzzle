# CMakeList.txt: JigsawPuzzle 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(proj_name "JigsawPuzzle")

project (${proj_name})

set(Qt5_DIR "E:/Qt/5.15.2/msvc2019_64/lib/cmake/Qt5")

# 设置 Qt 版本和组件
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia)

set(source_dir "src")

file(GLOB_RECURSE
	 UI_FILES
	 "${source_dir}/*.ui"
)

file(GLOB_RECURSE
	 SOURCE_FILES 
	 "${source_dir}/*.cpp"
	 "${source_dir}/*.h"
)

# 将源代码添加到此项目的可执行文件。
add_executable (${proj_name} ${SOURCE_FILES} ${UI_FILES})

target_link_directories(${proj_name} PRIVATE 
	"bin"
)

target_link_libraries(${proj_name} PRIVATE 
	Qt5::Core 
	Qt5::Widgets 
	Qt5::Gui
	Qt5::Multimedia
	pugixml-x64-d
	ratel.basic-x64-d
	ratel.filesys-x64-d
	ratel.kernel-x64-d
	sflogger.core-v150-x64-d
	sflogger.xmlconf-v150-x64-d
)

target_include_directories(${proj_name} PRIVATE 
	"include"
	"include/sflogger"
	"include/sflogger/xmlconf"
	"include/ratel/basic"
	"include/ratel/filesys"
	"include/ratel/kernel"
	"src"
	"src/ui"
	"src/logic" 
	"src/logic/mediator" 
	"src/global"
)

install(TARGETS ${proj_name} DESTINATION bin)
#install(FILES "${PROJECT_BINARY_DIR}/MyLibraryConfig.h" 
   #     DESTINATION include)

# TODO: 如有需要，请添加测试并安装目标。
