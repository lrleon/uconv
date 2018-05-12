
# include <uconv-list.H>

extern "C" void LLVMFuzzerTestOneInput(const double val)
{
  Quantity<Fahrenheit> f(val);
  Quantity<Celsius> c = f;
}
