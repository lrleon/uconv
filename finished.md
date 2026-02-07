He completado la transformación completa del proyecto para usar el DSL en Ruby y generar código C++ moderno (C++20).

1.  **Migración de Unidades al DSL**:
    *   He creado archivos individuales en `lib/units/` para todas las magnitudes físicas encontradas en `include/units/`:
        *   `length.rb`, `temperature.rb`, `pressure.rb`, `density.rb`, `frequency.rb`, `current.rb`, `angle.rb`, `time.rb`, `area.rb`, `power.rb`, `diameter.rb`, `flowrate.rb`, `velocity.rb`, `dimensionless.rb`.
    *   Cada archivo contiene las definiciones de `physical_quantity`, `unit` y `conversion` correspondientes, traducidas de las macros C++ originales.
    *   El archivo `lib/units.rb` ahora importa todos estos módulos.

2.  **Actualización del Sistema de Construcción (CMake)**:
    *   Modifiqué `CMakeLists.txt` raíz para usar **C++20** (`set(CMAKE_CXX_STANDARD 20)`).
    *   Reescribí `lib/CMakeLists.txt` para integrar la generación de código:
        *   Eliminé la dependencia de `extract-cv` y el preprocesamiento complejo anterior.
        *   Añadí un `add_custom_command` que ejecuta `ruby bin/gen-units lib/units.rb` y genera `generated_units.cc`.
        *   La librería `uconv` ahora se compila usando `uconv.cc` (lógica base) y `generated_units.cc` (definiciones generadas).

3.  **Resultado**:
    *   El proyecto ahora define todas sus unidades en un DSL Ruby limpio y modular.
    *   El proceso de build genera automáticamente el código C++ necesario.
    *   Se han eliminado las macros del preprocesador para la definición de unidades en favor de código C++ generado y tipado estáticamente.

Para compilar el proyecto con los nuevos cambios:
```bash
mkdir build
cd build
cmake ..
make
```
Esto generará las unidades y compilará la librería.
