# Adding New Units

This is the recommended workflow to add or modify units and keep code + docs in sync.

## 1. Create or edit DSL file

Add content in `lib/unit-defs/your-domain.rb`.

If the file is new, import it in `lib/unit-defs.rb`:

```ruby
import "lib/unit-defs/your-domain.rb"
```

## 2. Define quantity, units, and conversions

Minimal skeleton:

```ruby
physical_quantity :YourQuantity do
  symbol "Q"
  latex "Q"
  description "Describe this physical quantity"
end

unit :your_unit_a do
  symbol "ua"
  latex "ua"
  description "Unit A"
  quantity :YourQuantity
  range 0..100
end

unit :your_unit_b do
  symbol "ub"
  latex "ub"
  description "Unit B"
  quantity :YourQuantity
  range 0..100
end

conversion :your_unit_a, :your_unit_b do |v| "2.0 * #{v}" end
conversion :your_unit_b, :your_unit_a do |v| "#{v} / 2.0" end
```

## 3. Regenerate headers

```bash
ruby bin/gen-units lib/unit-defs.rb <build-dir>/generated/units
```

If validation fails, fix all reported issues.

## 4. Build and test

```bash
cmake --build cmake-build-debug -j
ctest --test-dir cmake-build-debug --output-on-failure
```

## 5. Regenerate docs

```bash
cmake --build cmake-build-debug --target docs
```

## Why this auto-documents new units

`bin/gen-units` emits Doxygen blocks for:

- physical quantity structs
- unit structs
- conversion specializations

Since Doxygen scans generated headers under `<build-dir>/generated/units/`, newly added DSL entities are included automatically in the docs site.

## Common Failure Modes

- Missing one direction of conversion (`A -> B` exists, `B -> A` missing)
- Duplicate unit symbol
- Unit linked to unknown quantity
- Range omitted or invalid
- Conversion between units from different quantities
