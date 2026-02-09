# DSL Reference

The units DSL is defined and interpreted by `bin/gen-units`.

## Entry Point

- Root file: `lib/unit-defs.rb`
- It imports domain files from `lib/unit-defs/*.rb`

Example:

```ruby
import "lib/unit-defs/length.rb"
import "lib/unit-defs/pressure.rb"
```

## Core Declarations

### `physical_quantity`

```ruby
physical_quantity :Length do
  symbol "L"
  latex "L"
  description "Measurement of distance"
end
```

Required attributes:

- `symbol`
- `latex`
- `description`

### `unit`

```ruby
unit :meter do
  symbol "m"
  latex "m"
  description "Length in meters"
  quantity :Length
  range 0..30000
end
```

Required attributes:

- `symbol`
- `latex`
- `description`
- `quantity`
- `range`

### `conversion`

```ruby
conversion :meter, :foot do |v| "3.28083989501 * #{v}" end
```

Required fields:

- `from` unit
- `to` unit
- formula block

The block must return a C++ expression string.

## Validation Rules

The generator enforces the following before producing C++:

- Presence checks for all required fields
- Range checks:
  - range must exist
  - bounds must be numeric
  - `min <= max`
- Duplicate checks:
  - physical quantity names/symbols
  - unit names/symbols
  - conversion pairs (`from->to`)
  - type-name collisions (quantity name == unit name)
- Reference checks:
  - unit quantity must exist
  - conversion endpoints must exist
  - conversions across different quantities are forbidden
- Coverage checks:
  - for each quantity with more than one unit, directed full coverage is required
  - i.e., every `src -> tgt` must exist for `src != tgt`
- Explicit self-conversions are forbidden (`A -> A`)

## Practical Conventions

- Keep one domain per file under `lib/unit-defs/`
- Keep `lib/unit-defs.rb` as the single import list
- Prefer clear and stable unit class names
- Keep formulas explicit and readable

## Generation Command

```bash
ruby bin/gen-units lib/unit-defs.rb <build-dir>/generated/units
```

Generated files include Doxygen comments and should not be edited manually.
