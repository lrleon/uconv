# Fuzzing specific configuration
# Note: The original Imakefile adds -fsanitize=fuzzer.
# This requires clang.

option(UCONV_ENABLE_FUZZ_SMOKE_TESTS "Enable bounded fuzz smoke tests in ctest" ON)

# Required system libraries (same as in tests)
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)
find_library(M_LIB m)
find_library(ALEPH_LIB Aleph PATHS ${ALEPHW} NO_DEFAULT_PATH)

set(LINK_LIBS uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB})

add_executable(simple simple.cc)
add_dependencies(simple uconv)
target_link_libraries(simple ${LINK_LIBS})

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(simple PRIVATE -fsanitize=fuzzer)
    target_link_options(simple PRIVATE -fsanitize=fuzzer)

    if(UCONV_ENABLE_FUZZ_SMOKE_TESTS)
        add_test(
            NAME fuzz_simple_smoke
            COMMAND simple
                    -runs=20000
                    -max_total_time=20
                    -rss_limit_mb=2048
                    -print_final_stats=1
                    -detect_leaks=0
        )
        set_tests_properties(fuzz_simple_smoke PROPERTIES TIMEOUT 40)
    endif()
endif()
