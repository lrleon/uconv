# Fuzzing specific configuration
# Note: The original Imakefile adds -fsanitize=fuzzer.
# This requires clang.

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-fsanitize=fuzzer)
    add_link_options(-fsanitize=fuzzer)
endif()

# Required system libraries (same as in tests)
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)
find_library(M_LIB m)
find_library(ALEPH_LIB Aleph PATHS ${ALEPHW} NO_DEFAULT_PATH)

set(LINK_LIBS uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB})

add_executable(simple simple.cc)
target_link_libraries(simple ${LINK_LIBS})
