#include <iostream>
#include <uconv.H>
#include <units/velocity.H>
#include <units/length.H>
#include <units/time.H>

UnitsInstancer init;

using namespace std;

int main() {
    cout << "=== Ejemplo 3: Cálculos Físicos ===" << endl;

    // Definir velocidad y tiempo
    Quantity<Meter_S> velocidad = 25.0; // 25 m/s
    Quantity<second> tiempo = 10.0;     // 10 segundos

    cout << "Velocidad: " << velocidad << endl;
    cout << "Tiempo: " << tiempo << endl;

    // Calcular distancia
    // Como no hemos definido explícitamente la unidad compuesta (m/s * s = m),
    // operamos con los valores crudos (raw) y asignamos a la unidad resultante esperada.
    double distancia_val = velocidad.raw() * tiempo.raw();
    Quantity<meter> distancia = distancia_val;

    cout << "Distancia recorrida: " << distancia << endl;

    // Conversión a otras unidades de longitud
    cout << "En pies: " << Quantity<foot>(distancia) << endl;
    cout << "En yardas: " << Quantity<yard>(distancia) << endl;

    return 0;
}
