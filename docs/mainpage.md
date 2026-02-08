# uconv Documentation

Welcome to the technical documentation for `uconv`.

## Read This First

- Repository guide: [README.md](../README.md)
- Core API: [include/uconv.H](../include/uconv.H)
- DSL root: [lib/unit-defs.rb](../lib/unit-defs.rb)

## Documentation Map

- [Architecture Overview](architecture.md)
- [DSL Reference](dsl-reference.md)
- [Adding New Units](adding-units.md)

## Documentation Generation

Build docs with:

```bash
cmake --build cmake-build-debug --target docs
```

Generated site:

- `cmake-build-debug/docs/doxygen/html/index.html`
- Generated units headers: `cmake-build-debug/generated/units/*.H`

## Auto-documentation Guarantee for New Units

If you add new units/conversions in the DSL:

1. `bin/gen-units` validates and regenerates C++ unit headers.
2. Generated headers include Doxygen comments for quantities, units, and conversions.
3. Running the `docs` target updates Doxygen with the new definitions.

No manual Doxygen edits are required for regular unit/conversion additions.
