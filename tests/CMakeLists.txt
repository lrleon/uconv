# Required system libraries
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)
find_library(M_LIB m)

# Aleph library (assuming it is in ALEPHW)
find_library(ALEPH_LIB Aleph PATHS ${ALEPHW} NO_DEFAULT_PATH)

set(LINK_LIBS uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB})

# Test executables
add_executable(convert convert.cc)
target_link_libraries(convert ${LINK_LIBS})

add_executable(vector-convert vector-convert.cc)
target_link_libraries(vector-convert ${LINK_LIBS})

add_executable(test-all-units test-all-units.cc)
target_link_libraries(test-all-units ${LINK_LIBS})

add_executable(test-unit-table test-unit-table.cc)
target_link_libraries(test-unit-table ${LINK_LIBS})
