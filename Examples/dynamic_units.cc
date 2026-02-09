#include <iostream>
#include <string>
#include <uconv.H>
#include <all_units.H> // Incluye todas las definiciones

UnitsInstancer init;


int main() {
    std::cout << "=== Ejemplo 2: Unidades Dinámicas (VtlQuantity) ===" << std::endl;
    std::cout << "Este ejemplo simula el manejo de unidades seleccionadas por el usuario en tiempo de ejecución." << std::endl;

    try {
        // Supongamos que estos strings vienen de una interfaz de usuario o archivo de config
        std::string unidad_entrada = "psia";
        double valor_entrada = 30.0;

        std::string unidad_salida = "bar";

        // Crear cantidad dinámicamente
        VtlQuantity presion(unidad_entrada, valor_entrada);
        std::cout << "\nEntrada: " << presion << std::endl;

        // Convertir dinámicamente
        VtlQuantity resultado(unidad_salida, presion);
        std::cout << "Convertido a " << unidad_salida << ": " << resultado << std::endl;

        // Operaciones mixtas
        VtlQuantity extra("Pa", 5000.0);
        std::cout << "Sumando " << extra << "..." << std::endl;

        // El resultado mantiene la unidad del operando izquierdo (psi)
        VtlQuantity total = presion + extra;
        std::cout << "Total: " << total << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
