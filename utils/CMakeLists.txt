# Required system libraries
find_library(GSL_LIB gsl)
find_library(GSLCBLAS_LIB gslcblas)
find_library(M_LIB m)

# Aleph library (assuming it is in ALEPHW)
find_library(ALEPH_LIB Aleph PATHS ${ALEPHW} NO_DEFAULT_PATH)

set(LINK_LIBS uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB})

# Utility executables
add_executable(util-convert convert.cc)
add_dependencies(util-convert uconv)
target_link_libraries(util-convert ${LINK_LIBS})

add_executable(util-vector-convert vector-convert.cc)
add_dependencies(util-vector-convert uconv)
target_link_libraries(util-vector-convert ${LINK_LIBS})

add_executable(util-all-units all-units.cc)
add_dependencies(util-all-units uconv)
target_link_libraries(util-all-units ${LINK_LIBS})

add_executable(util-unit-table unit-table.cc)
add_dependencies(util-unit-table uconv)
target_link_libraries(util-unit-table ${LINK_LIBS})
