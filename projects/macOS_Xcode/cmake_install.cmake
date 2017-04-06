# Install script for directory: /Users/jamesfolk/Dropbox/Developer/NJLI/Engine

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/generated")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/tests" TYPE FILE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/Tests.in/lua/njli_test.lua")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/data" TYPE FILE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/DoxyFiles.in/images/logo.png")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/thirdparty/macOS/10.12/Release" TYPE PROGRAM FILES
    "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/BUILD/lib/lua/macOS/10.12//Release/bin/lua"
    "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/BUILD/lib/lua/macOS/10.12//Release/bin/luac"
    "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/BUILD/lib/assimp/macOS/10.12//Release/bin/assimp"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/src/njli/platform/Game.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/data/swig/lua" TYPE FILE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/lnjli.xml")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/data/swig/lua" TYPE FILE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/lbullet.xml")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/" TYPE DIRECTORY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/ldoc")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/" TYPE DIRECTORY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/docbook")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/" TYPE DIRECTORY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/html")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/" TYPE DIRECTORY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/latex")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/" TYPE DIRECTORY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/rtf")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/doc/" TYPE DIRECTORY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/cmake.in/xml")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE STATIC_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/Debug/libnjli.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE STATIC_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/Release/libnjli.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE STATIC_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/MinSizeRel/libnjli.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE STATIC_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/RelWithDebInfo/libnjli.a")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
      execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.a")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE SHARED_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/Debug/libnjli.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE SHARED_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/Release/libnjli.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE SHARED_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/MinSizeRel/libnjli.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release" TYPE SHARED_LIBRARY FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/RelWithDebInfo/libnjli.dylib")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/macOS/10.12/Release/libnjli.dylib")
      endif()
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release" TYPE MODULE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/Debug/njli.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release" TYPE MODULE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/Release/njli.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release" TYPE MODULE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/MinSizeRel/njli.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release" TYPE MODULE FILES "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/RelWithDebInfo/njli.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/jamesfolk/Dropbox/Developer/NJLI/External/thirdparty/fmod/lib/macOS/10.12/Release"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/module/macOS/10.12/Release/njli.so")
      endif()
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/jamesfolk/Dropbox/Developer/NJLI/Engine/projects/macOS_Xcode/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
