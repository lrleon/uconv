
# include <uconv-list.H>
# include <iostream>
# include <cstdint>
# include <cstring>
# include <cmath>

extern "C" int LLVMFuzzerTestOneInput(const std::uint8_t *data,
                                      const std::size_t size)
{
  if (size < sizeof(double))
    return 0;

  double val = 0.0;
  std::memcpy(&val, data, sizeof(double));
  if (not std::isfinite(val))
    return 0;

  // Most random inputs are outside of unit range. Ignore them and only
  // exercise conversion logic for values that are valid for Fahrenheit.
  if (not BaseQuantity::is_valid(val, Fahrenheit::get_instance()))
    return 0;

  Quantity<Fahrenheit> f(val);
  Quantity<Celsius> c = f;
  Quantity<Fahrenheit> back = c;
  (void) back;
  return 0;
}

#ifndef __clang__
int main() {
  double val;
  while (std::cin >> val) {
    LLVMFuzzerTestOneInput(reinterpret_cast<const std::uint8_t *>(&val),
                           sizeof(double));
  }
  return 0;
}
#endif
