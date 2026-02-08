# Generation of units headers
# We use bin/gen-units to generate C++ headers in the build tree from the Ruby DSL

set(GEN_UNITS ${CMAKE_SOURCE_DIR}/bin/gen-units)
set(UNITS_DSL ${CMAKE_SOURCE_DIR}/lib/unit-defs.rb)
set(UNITS_DSL_DIR ${CMAKE_SOURCE_DIR}/lib/unit-defs)
if(NOT DEFINED UCONV_GENERATED_UNITS_DIR)
    set(UCONV_GENERATED_UNITS_DIR ${CMAKE_BINARY_DIR}/generated/units)
endif()
if(NOT DEFINED UCONV_GENERATED_DIR)
    set(UCONV_GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
endif()
set(UNITS_OUTPUT_DIR ${UCONV_GENERATED_UNITS_DIR})
set(ALL_UNITS_H ${UNITS_OUTPUT_DIR}/all_units.H)
set(UNITS_CATALOG_MD ${UNITS_OUTPUT_DIR}/units_catalog.md)
set(UCONV_CC ${CMAKE_CURRENT_SOURCE_DIR}/uconv.cc)

# List all DSL files for dependency tracking
file(GLOB DSL_FILES "${UNITS_DSL_DIR}/*.rb")

# Custom command to generate headers
add_custom_command(
    OUTPUT ${ALL_UNITS_H} ${UNITS_CATALOG_MD}
    COMMAND ruby ${GEN_UNITS} ${UNITS_DSL} ${UNITS_OUTPUT_DIR}
    DEPENDS ${GEN_UNITS} ${UNITS_DSL} ${DSL_FILES}
    COMMENT "Generating C++ units headers from Ruby DSL"
)

# Ensure generated headers and catalog are always materialized before build/docs.
add_custom_target(uconv_units_generated DEPENDS ${ALL_UNITS_H} ${UNITS_CATALOG_MD})

# Create the static library uconv
# We include ALL_UNITS_H in sources to ensure the custom command runs
# uconv.cc now includes all_units.H directly
add_library(uconv STATIC ${UCONV_CC} ${ALL_UNITS_H})
add_dependencies(uconv uconv_units_generated)

# Include directories for the library
target_include_directories(uconv PUBLIC
    ${UCONV_GENERATED_DIR}
    ${UNITS_OUTPUT_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${ALEPHW}
    ${JSON_PATH}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)
