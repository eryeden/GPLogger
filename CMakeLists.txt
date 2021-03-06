# OUT-OF-SOURCEバージョンのCMakeLits.txt
# GPLogger
# シリアルポートから入ってきたデータを何かしらのデータ形式で保存する
# シリアル通信のライブラリは

PROJECT(GPLogger)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#For auto-complete
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Serial port library configuration
SET(LIB_SERIAL_PREFIX ${PROJECT_SOURCE_DIR}/lib/serial)
SET(LIB_SERIAL_INCLUDE ${LIB_SERIAL_PREFIX}/include)
SET(LIB_SERIAL_SRCDIR ${LIB_SERIAL_PREFIX}/src)

SET(LIB_SERIAL_SRCS
  ${LIB_SERIAL_SRCDIR}/serial.cc
  ${LIB_SERIAL_SRCDIR}/impl/unix.cc
  ${LIB_SERIAL_SRCDIR}/impl/list_ports/list_ports_linux.cc
  )

#--specs=nosys.specsを入れないとレファレンス出る。
set(COMPILEOPTIONS "-g -Wall")
set(COMPILEOPTIONSXX "-std=c++11")
set(LINKOPTIONS "-g")

MESSAGE("###########PROJECT ROOT DIRECTORY SOURCE##############")
MESSAGE(${PROJECT_SOURCE_DIR})
MESSAGE("###########PROJECT DIRECTORY BINARY##############")
MESSAGE(${PROJECT_BINARY_DIR})

SET(DIR_SOURCE "${PROJECT_SOURCE_DIR}/src")
SET(DIR_INCLUDE "${PROJECT_SOURCE_DIR}/include")
SET(DIR_BIN "${PROJECT_SOURCE_DIR}/bin")


#############################################################################

#ここでリンクする、使用する、Boostのエレメントが決まる。ここに乗ってないのを使用してコンパイルするとリンクエラーが出るので注意
find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}
  ${DIR_INCLUDE}
  ${LIB_SERIAL_INCLUDE}
  ${Boost_INCLUDE_DIR}
  )


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMPILEOPTIONS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMAKE_C_FLAGS} ${COMPILEOPTIONSXX}")

message("##C_FLAGS##")
message(${CMAKE_C_FLAGS})
message("##CXX_FLAGS##")
message(${CMAKE_CXX_FLAGS})

message("##LD_FLAGS##")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LINKOPTIONS}")

message(${CMAKE_EXE_LINKER_FLAGS})

SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS)
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS)

set(SRCS
  ${DIR_SOURCE}/main.cpp
  ${LIB_SERIAL_SRCS}
  )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(${CMAKE_PROJECT_NAME} ${SRCS})
#Boostをリンク
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES})



set(TARGET ${CMAKE_PROJECT_NAME})

#ALLを入れてないと自動実行
#入れいていない時は
#make ${CMAKE_PROJECT_NAME}.hex
#のようにコマンドを打てば実行可能
# ADD_CUSTOM_TARGET(${TARGET}.hex
#   ALL
#   DEPENDS ${TARGET}
#   COMMAND ${CMAKE_OBJCOPY} -Oihex ${CMAKE_BINARY_DIR}/bin/${TARGET} ${CMAKE_BINARY_DIR}/bin/${TARGET}.hex)
# ADD_CUSTOM_TARGET(${TARGET}.bin
#   ALL
#   DEPENDS ${TARGET}
#   COMMAND ${CMAKE_OBJCOPY} -Obinary ${CMAKE_BINARY_DIR}/bin/${TARGET} ${CMAKE_BINARY_DIR}/bin/${TARGET}.bin)

SET(COMPILE_COMMANDS "compile_commands.json")
ADD_CUSTOM_TARGET(${COMPILE_COMMANDS}
  ALL
  DEPENDS ${COMPILE_COMMANDS}
  COMMAND cp ${COMPILE_COMMANDS} ${PROJECT_SOURCE_DIR}/${COMPILE_COMMANDS})
