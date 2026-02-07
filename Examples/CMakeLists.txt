# Examples configuration

# Find dependencies (same as in Tests)
find_library(ALEPH_LIB Aleph PATHS ${ALEPHW} NO_DEFAULT_PATH)
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)
find_library(M_LIB m)

set(EXAMPLES
    basic_conversion
    dynamic_units
    physics
)

foreach(ex ${EXAMPLES})
    add_executable(${ex} ${ex}.cc)
    target_link_libraries(${ex} uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB})
endforeach()
