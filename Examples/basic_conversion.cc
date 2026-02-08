#include <iostream>
#include <uconv.H>
#include <units/length.H>
#include <units/temperature.H>

// Instantiate the units system (required once in the program)
UnitsInstancer init;

using namespace std;

int main() {
    cout << "=== Example 1: Basic Conversion ===" << endl;

    // Definition of quantities with strong types
    Quantity<meter> length = 10.0;
    Quantity<foot> width = 50.0;

    cout << "Initial length: " << length << endl;
    cout << "Initial width: " << width << endl;

    // Arithmetic operations: automatic conversion
    // 'width' is converted to 'meter' before adding
    Quantity<meter> total = length + width;

    cout << "Total (length + width) in meters: " << total << endl;

    // Explicit conversion to another unit
    Quantity<yard> total_yards = total;
    cout << "Total in yards: " << total_yards << endl;

    // Example with temperature
    Quantity<Celsius> t_c = 100.0;
    Quantity<Fahrenheit> t_f = t_c;

    cout << "\nBoiling point temperature: " << t_c << " = " << t_f << endl;

    return 0;
}
