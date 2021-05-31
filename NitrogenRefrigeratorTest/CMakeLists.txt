cmake_minimum_required(VERSION 3.5)

project(NitrogenRefrigeratorTest LANGUAGES CXX)


add_definitions(-DGTEST_LANGUAGE_CXX11)

find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT "C:/Users/chochheim/Documents/Privat/CppProjects/googletest" STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "C:/Users/chochheim/Documents/Privat/CppProjects/googletest")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})

set(FILES_TO_TEST ../NitrogenRefrigerator/CellContainer/cellcontainer.h
  ../NitrogenRefrigerator/CellContainer/cellcontainer.cpp
  ../NitrogenRefrigerator/CellContainer/jsonStorage.h
  ../NitrogenRefrigerator/CellContainer/jsonStorage.cpp)

set(TEST_FILES CellContainerTest/cellContainerTest.h)
set(TEST_FILES CellContainerTest/jsonStorageTest.h)

add_executable(NitrogenRefrigeratorTest main.cpp tst_NitrogenRefrigeratorTest.h
  ${TEST_FILES}
  ${FILES_TO_TEST}
  ${GTestFiles})

add_test(NAME NitrogenRefrigeratorTest COMMAND NitrogenRefrigeratorTest)
target_link_libraries(NitrogenRefrigeratorTest PRIVATE Threads::Threads)

