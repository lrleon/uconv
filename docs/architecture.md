# Architecture Overview

This document explains how `uconv` is structured and how data flows from DSL definitions to runtime conversion behavior.

## High-Level Components

- DSL definitions: `lib/unit-defs.rb` + `lib/unit-defs/*.rb`
- Generator/validator: `bin/gen-units`
- Generated headers: `<build-dir>/generated/units/*.H`
- Runtime core: `include/uconv.H` + `lib/uconv.cc`
- Unit tests: `Tests/`
- Utilities: `utils/`

Generated headers are build artifacts and are not tracked in Git.

## Build-Time Flow

1. CMake config loads `lib/CMakeLists.txt`.
2. Custom command runs:

```bash
ruby bin/gen-units lib/unit-defs.rb <build-dir>/generated/units
```

3. Generator validates DSL and emits headers under `<build-dir>/generated/units`.
4. Library target `uconv` is built and links with Aleph/GSL dependencies.
5. Tests, utilities, and examples link against `uconv`.

## Runtime Model

The core model uses three principal concepts:

- `PhysicalQuantity`: category/family (e.g., Length, Pressure)
- `Unit`: unit metadata + range constraints
- Quantities:
  - `Quantity<Unit>`: compile-time unit type
  - `VtlQuantity`: runtime unit selection

Conversions are registered as function pointers in lookup tables during static initialization.

## Compound Units

Compound units are separated by operation:

- Product (`u1 * u2`), e.g. area-like composition
- Ratio (`u1 / u2`), e.g. velocity-like composition

This is represented in the compound unit table with operation-aware keys and lookup paths.

## Safety and Validation Layers

- DSL structural validation in `bin/gen-units`
- Unit value range checks at runtime (`Unit` min/max + epsilon)
- Type-level conversion checks in templates (`Quantity<Unit>`)
- Runtime checks in `VtlQuantity` (unit compatibility, conversion existence)

## Documentation Pipeline

`cmake --build ... --target docs`:

1. Builds `uconv` (ensures generated headers are up to date).
2. Runs Doxygen with `cmake/Doxyfile.in`.
3. Includes API headers, DSL files, and `docs/*.md` pages.

So code and docs evolve together from the same DSL source.
