# uconv

A C++20 units and physical-quantities conversion library with:

- Strongly typed quantities at compile time (`Quantity<Unit>`)
- Runtime quantities (`VtlQuantity`)
- A Ruby DSL to define physical quantities, units, and conversions
- Strong DSL validation (duplicates, missing references, conversion coverage)
- Automatic C++ code generation and Doxygen documentation

## Contents

1. [Project Status](#project-status)
2. [Repository Layout](#repository-layout)
3. [Requirements](#requirements)
4. [Quick Start](#quick-start)
5. [Build Targets](#build-targets)
6. [Running Tests](#running-tests)
7. [Running Utilities](#running-utilities)
8. [Examples](#examples)
9. [Defining New Units and Conversions](#defining-new-units-and-conversions)
10. [DSL Validation Rules](#dsl-validation-rules)
11. [Documentation (Doxygen)](#documentation-doxygen)
12. [CI Workflows](#ci-workflows)
13. [Troubleshooting](#troubleshooting)
14. [License](#license)

## Project Status

The project is currently organized around the DSL pipeline:

- Source of truth for units DSL: `lib/unit-defs.rb` + `lib/unit-defs/*.rb`
- Generated C++ headers: `<build-dir>/generated/units/*.H`
- Core runtime API: `include/uconv.H`
- Unit tests (GoogleTest + `ctest`): `Tests/`
- CLI utilities (manual checks/tools): `utils/`

Generated headers are build artifacts and are not versioned in Git.

## Repository Layout

- `include/`: public headers (`uconv.H`, helper headers)
- `lib/`: core implementation and DSL definitions
- `bin/gen-units`: Ruby generator + DSL validator
- `Tests/`: automated unit tests
- `utils/`: manual CLI utilities
- `Examples/`: usage examples
- `docs/`: human-facing technical documentation (included in Doxygen)
- `cmake/Doxyfile.in`: Doxygen configuration template

## Requirements

### Required

- C++20 compiler (`g++` or `clang++`)
- CMake >= 3.10
- Ruby (to run `bin/gen-units`)
- `Aleph-w` headers + library
- `nlohmann/json` include path
- GoogleTest (for `Tests/`)

### Optional

- Doxygen + Graphviz (for docs)

## Quick Start

### 1. Set dependencies

You can provide dependencies as environment variables or CMake variables.

Using environment variables:

```bash
export ALEPHW=/path/to/Aleph-w
export JSON=/path/to/json
```

Or pass them explicitly to CMake:

```bash
cmake -S . -B cmake-build-debug -DALEPHW=/path/to/Aleph-w -DJSON_PATH=/path/to/json
```

### 2. Configure

```bash
cmake -S . -B cmake-build-debug -DALEPHW=/path/to/Aleph-w -DJSON_PATH=/path/to/json
```

### 3. Build

```bash
cmake --build cmake-build-debug -j
```

This build automatically regenerates `<build-dir>/generated/units/*.H` from the DSL when needed.

## Build Targets

Common targets:

- Default build: `cmake --build cmake-build-debug`
- Unit tests binaries: included via `Tests/`
- Utilities binaries: included via `utils/`
- Examples binaries: included via `Examples/`
- Docs site: `cmake --build cmake-build-debug --target docs`

CMake options:

- `-DENABLE_SANITIZERS=ON|OFF` (default `ON`)
- `-DBUILD_DOCS=ON|OFF` (default `ON`)

## Running Tests

Automated unit tests are in `Tests/` and are registered with `ctest`.

Run all:

```bash
ctest --test-dir cmake-build-debug --output-on-failure
```

If ASAN leak detection interferes in your environment, use:

```bash
ASAN_OPTIONS=detect_leaks=0 ctest --test-dir cmake-build-debug --output-on-failure
```

## Running Utilities

Manual utilities are built under `utils/`:

- `util-convert`: convert scalar values between units
- `util-vector-convert`: convert value vectors
- `util-all-units`: validate/range-check by physical quantity
- `util-unit-table`: inspect registered units table

Example:

```bash
./cmake-build-debug/utils/util-convert --help
```

## Examples

Examples are built under `Examples/`:

- `basic_conversion`
- `dynamic_units`
- `physics`

Example:

```bash
./cmake-build-debug/Examples/basic_conversion
```

## Defining New Units and Conversions

### 1. Add or edit DSL files

- Root DSL entrypoint: `lib/unit-defs.rb`
- Per-domain DSL files: `lib/unit-defs/*.rb`

If you add a new DSL file, import it in `lib/unit-defs.rb`.

### 2. Use DSL primitives

- `physical_quantity :Name do ... end`
- `unit :UnitName do ... end`
- `conversion :FromUnit, :ToUnit do |v| "...#{v}..." end`

Required metadata:

- Physical quantity: `symbol`, `latex`, `description`
- Unit: `symbol`, `latex`, `description`, `quantity`, `range`
- Conversion: `from`, `to`, formula block

### 3. Regenerate headers

```bash
ruby bin/gen-units lib/unit-defs.rb <build-dir>/generated/units
```

### 4. Build and test

```bash
cmake --build cmake-build-debug -j
ctest --test-dir cmake-build-debug --output-on-failure
```

## DSL Validation Rules

`bin/gen-units` enforces structural checks before generating C++:

- Missing fields (`symbol`, `latex`, `description`, `quantity`, `range`, formula)
- Invalid ranges (`min > max`, non-numeric range)
- Duplicates (quantity names/symbols, unit names/symbols, conversion pairs)
- Unknown references (unit -> quantity, conversion endpoints)
- Cross-quantity conversions (forbidden)
- Conversion coverage (directed full coverage within each quantity family)
- Explicit self-conversions (forbidden)

If validation fails, generation aborts with a detailed error list.

## Documentation (Doxygen)

### Generate docs

```bash
cmake --build cmake-build-debug --target docs
```

Output:

- HTML index: `cmake-build-debug/docs/doxygen/html/index.html`
- Warnings log: `cmake-build-debug/docs/doxygen/warnings.log`

### What is documented

- Full public API in `include/uconv.H`
- Generated units headers (`<build-dir>/generated/units/*.H`)
- DSL source files (`lib/unit-defs.rb`, `lib/unit-defs/*.rb`)
- Markdown docs in `docs/`

### Automatic docs for future units/conversions

When you define new units or conversions in the DSL:

1. `bin/gen-units` regenerates headers with Doxygen blocks per quantity/unit/conversion.
2. `docs` target runs Doxygen over generated headers and DSL docs.

So new DSL definitions appear in Doxygen automatically after:

```bash
cmake --build cmake-build-debug --target docs
```

## CI Workflows

Current workflows (`.github/workflows/`):

- `ci.yml`: matrix build/test + sanitizers (`gcc` and `clang`, Debug) + docs warnings gate
- `docs.yml`: build and publish Doxygen site to GitHub Pages
- `full_analysis.yml`: scheduled deeper analysis (build/test/cppcheck/docs)

## Troubleshooting

### `ALEPHW is not defined`

Set `ALEPHW` or pass `-DALEPHW=...`.

### `JSON_PATH is not defined`

Set `JSON` env var or pass `-DJSON_PATH=...`.

### DSL generation fails

Run directly to see validation errors:

```bash
ruby bin/gen-units lib/unit-defs.rb <build-dir>/generated/units
```

### Docs target not available

Install Doxygen and reconfigure:

```bash
sudo apt-get install doxygen graphviz
cmake -S . -B cmake-build-debug
```

## License

`uconv` is licensed under GNU GPL v3.
See `LICENSE`.
