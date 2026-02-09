
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
    general_units.cc
    error_paths.cc
    uconv_api.cc
    numeric_robustness.cc
    api_ops_legacy.cc
    coverage_drivers.cc
)

foreach(test_src ${TEST_SOURCES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(Test_${test_name} ${test_src})
    add_dependencies(Test_${test_name} uconv)
    target_link_libraries(Test_${test_name} uconv ${ALEPH_LIB} ${GSL_LIB} ${GSLCBLAS_LIB} ${M_LIB} GTest::GTest GTest::Main Threads::Threads)
    add_test(NAME ${test_name} COMMAND Test_${test_name})
endforeach()

# DSL negative tests: ensure the generator rejects invalid fixtures.
set(GEN_UNITS ${CMAKE_SOURCE_DIR}/bin/gen-units)
set(DSL_INVALID_DIR ${CMAKE_SOURCE_DIR}/Tests/dsl-invalid)
set(DSL_INVALID_OUT ${CMAKE_BINARY_DIR}/dsl-invalid)
set(DSL_NEGATIVE_RUNNER ${CMAKE_SOURCE_DIR}/Tests/run_dsl_negative_case.sh)

function(add_dsl_negative_test test_name fixture_file expected_message)
    add_test(
        NAME ${test_name}
        COMMAND bash ${DSL_NEGATIVE_RUNNER}
                ${GEN_UNITS}
                ${DSL_INVALID_DIR}/${fixture_file}
                ${DSL_INVALID_OUT}/${test_name}
                ${expected_message}
    )
endfunction()

add_dsl_negative_test(dsl_invalid_missing_symbol missing_symbol.rb "Missing symbol for")
add_dsl_negative_test(dsl_invalid_unknown_quantity unknown_quantity.rb "Unknown physical quantity")
add_dsl_negative_test(dsl_invalid_cross_quantity_conversion cross_quantity_conversion.rb "Cross-quantity conversion")
add_dsl_negative_test(dsl_invalid_missing_coverage missing_coverage.rb "Missing conversion coverage")
add_dsl_negative_test(dsl_invalid_missing_latex missing_latex.rb "Missing latex for")
add_dsl_negative_test(dsl_invalid_missing_description missing_description.rb "Missing description for")
add_dsl_negative_test(dsl_invalid_missing_range missing_range.rb "Missing range for")
add_dsl_negative_test(dsl_invalid_invalid_range invalid_range.rb "Invalid range (min > max)")
add_dsl_negative_test(dsl_invalid_duplicate_unit_symbol duplicate_unit_symbol.rb "Duplicated unit symbol")
add_dsl_negative_test(dsl_invalid_duplicate_unit_name duplicate_unit_name.rb "Duplicated unit name")
add_dsl_negative_test(dsl_invalid_duplicate_pq_name duplicate_pq_name.rb "Duplicated physical quantity name")
add_dsl_negative_test(dsl_invalid_duplicate_pq_symbol duplicate_pq_symbol.rb "Duplicated physical quantity symbol")
add_dsl_negative_test(dsl_invalid_duplicate_conversion_pair duplicate_conversion_pair.rb "Duplicated conversion pair")
add_dsl_negative_test(dsl_invalid_type_name_collision type_name_collision.rb "Type name collision")
add_dsl_negative_test(dsl_invalid_self_conversion self_conversion.rb "Explicit self-conversion is not allowed")
add_dsl_negative_test(dsl_invalid_unknown_source_unit unknown_source_unit.rb "Unknown source unit")
add_dsl_negative_test(dsl_invalid_unknown_target_unit unknown_target_unit.rb "Unknown target unit")
add_dsl_negative_test(dsl_invalid_missing_formula missing_formula.rb "Missing conversion formula block")
add_dsl_negative_test(dsl_invalid_missing_quantity_reference missing_quantity_reference.rb "Missing quantity reference for")
add_dsl_negative_test(dsl_invalid_non_numeric_range non_numeric_range.rb "Range values must be numeric")
add_dsl_negative_test(dsl_invalid_parse_error parse_error.rb "syntax error")
