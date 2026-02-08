#include <iostream>
#include <string>
#include <uconv.H>
#include <all_units.H> // Incluye todas las definiciones

UnitsInstancer init;

using namespace std;

int main() {
    cout << "=== Ejemplo 2: Unidades Dinámicas (VtlQuantity) ===" << endl;
    cout << "Este ejemplo simula el manejo de unidades seleccionadas por el usuario en tiempo de ejecución." << endl;

    try {
        // Supongamos que estos strings vienen de una interfaz de usuario o archivo de config
        string unidad_entrada = "psia";
        double valor_entrada = 30.0;

        string unidad_salida = "bar";

        // Crear cantidad dinámicamente
        VtlQuantity presion(unidad_entrada, valor_entrada);
        cout << "\nEntrada: " << presion << endl;

        // Convertir dinámicamente
        VtlQuantity resultado(unidad_salida, presion);
        cout << "Convertido a " << unidad_salida << ": " << resultado << endl;

        // Operaciones mixtas
        VtlQuantity extra("Pa", 5000.0);
        cout << "Sumando " << extra << "..." << endl;

        // El resultado mantiene la unidad del operando izquierdo (psi)
        VtlQuantity total = presion + extra;
        cout << "Total: " << total << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
