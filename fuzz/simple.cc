
# include <uconv-list.H>
# include <iostream>

extern "C" void LLVMFuzzerTestOneInput(const double val)
{
  Quantity<Fahrenheit> f(val);
  Quantity<Celsius> c = f;
}

#ifndef __clang__
int main() {
  double val;
  while (std::cin >> val) {
    LLVMFuzzerTestOneInput(val);
  }
  return 0;
}
#endif
