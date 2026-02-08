
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

# Find Aleph and other dependencies
find_library(ALEPH_LIB Aleph PATHS ${ALEPHW} NO_DEFAULT_PATH)
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)
find_library(M_LIB m)

if(NOT ALEPH_LIB)
    message(FATAL_ERROR "Aleph library not found in ${ALEPHW}")
endif()

# Test sources
set(TEST_SOURCES
    quantity.cc
    unititem.cc
    line.cc
    compound.cc
)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(Test_${test_name} ${test_src})
    target_link_libraries(Test_${test_name} uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB} GTest::GTest GTest::Main Threads::Threads)
    add_test(NAME ${test_name} COMMAND Test_${test_name})
endforeach()
