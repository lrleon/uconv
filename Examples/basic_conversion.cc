#include <iostream>
#include <uconv.H>
#include <units/length.H>
#include <units/temperature.H>

// Instanciar el sistema de unidades (necesario una vez en el programa)
UnitsInstancer init;

using namespace std;

int main() {
    cout << "=== Ejemplo 1: Conversión Básica ===" << endl;

    // Definición de cantidades con tipos fuertes
    Quantity<meter> largo = 10.0;
    Quantity<foot> ancho = 50.0;

    cout << "Largo inicial: " << largo << endl;
    cout << "Ancho inicial: " << ancho << endl;

    // Operaciones aritméticas: conversión automática
    // 'ancho' se convierte a 'meter' antes de sumar
    Quantity<meter> total = largo + ancho;

    cout << "Total (largo + ancho) en metros: " << total << endl;

    // Conversión explícita a otra unidad
    Quantity<yard> total_yardas = total;
    cout << "Total en yardas: " << total_yardas << endl;

    // Ejemplo con temperatura
    Quantity<Celsius> t_c = 100.0;
    Quantity<Fahrenheit> t_f = t_c;

    cout << "\nTemperatura de ebullición: " << t_c << " = " << t_f << endl;

    return 0;
}
