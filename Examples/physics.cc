#include <iostream>
#include <uconv.H>
#include <units/velocity.H>
#include <units/length.H>
#include <units/time.H>

UnitsInstancer init;


int main() {
    std::cout << "=== Ejemplo 3: Cálculos Físicos ===" << std::endl;

    // Definir velocidad y tiempo
    Quantity<Meter_S> velocidad = 25.0; // 25 m/s
    Quantity<second> tiempo = 10.0;     // 10 segundos

    std::cout << "Velocidad: " << velocidad << std::endl;
    std::cout << "Tiempo: " << tiempo << std::endl;

    // Calcular distancia
    // Como no hemos definido explícitamente la unidad compuesta (m/s * s = m),
    // operamos con los valores crudos (raw) y asignamos a la unidad resultante esperada.
    double distancia_val = velocidad.raw() * tiempo.raw();
    Quantity<meter> distancia = distancia_val;

    std::cout << "Distancia recorrida: " << distancia << std::endl;

    // Conversión a otras unidades de longitud
    std::cout << "En pies: " << Quantity<foot>(distancia) << std::endl;
    std::cout << "En yardas: " << Quantity<yard>(distancia) << std::endl;

    return 0;
}
