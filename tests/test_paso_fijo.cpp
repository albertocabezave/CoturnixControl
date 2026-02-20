/**
* @file test_paso_fijo.cpp
* @brief Validación del acumulador de tiempo bajo condiciones de estrés.
* * Comprueba que el gemelo digital mantenga la precisión y no pierda ticks
* aunque la CPU de la Class mate sufra retrasos (lag).
*/

#include <iostream>
#include <unistd.h>
#include "plataforma/relojLinux.h"
#include "motor/simulador.h"

int main() {
    Plataforma::RelojLinux reloj;

    /**
    * @brief Configuramos el simulador a 10Hz.
    * Esto significa que debe ocurrir un tick cada 100.000 microsegundos
    */
    Motor::Simulador sim(reloj, 10);

    std::cout << "--- TEST DE ACUMULADOR Y PASO FIJO ---" << std::endl;

    std::cout << "Paso objetivo: " << sim.obtener_paso_segundos() <<
    " s" << std::endl;

    uint64_t t_anterior = reloj.obtener_ticks_micro();
    int ticks_totales = 0;

    /**
    * @brief Simulamos un escenario de estrés:
    * El programa se detiene 150ms (más de lo que dura un paso de 100ms).
    * El simulador DEBE detectar que se saltó un paso y ejecutarlo después.
    */
    for(int i = 1; i <= 3; ++i) {
        // Simulamos carga pesada o lag del sistema.
        usleep(150000);

        uint64_t t_actual = reloj.obtener_ticks_micro();
        uint64_t dt = t_actual - t_anterior;
        t_anterior = t_actual;

        std::cout << "\nIteración " << i << "Delta real: " << dt <<
        "us): " << std::endl;

        /**
        * @brief El bucle while es vital.
        * Si el tiempo acumulado es mucho, ejecutará varios ticks seguidos
        * para ponerse al día con el tiempo real.
        */
        while (sim.debe_actualizar(dt)) {
            ticks_totales++;
            std::cout << " [TICK] Ejecutando paso fijo # " << ticks_totales << std::endl;

            /**
            * @brief IMPORTANTE: Una vez que el simulador procesa el primer tick,
            * el "dt" restante ya fue absorbido por el acumulador interno.
            */
            dt = 0; // Esta trampa debe ser corregida en el simulador.h/cpp para evitar escribirlo de nuevo en todo while.
        }
    }

    std::cout << "\n--- RESULTADO FINAL ---" << std::endl;
    if (ticks_totales >= 4) {
        std::cout << "[OK] Test superado: El acumulador recuperó el tiempo perdido" <<
        std::endl;
    } else {
        std::cerr << "[FAIL] Error de integridad: Se perdieron pasos de simulación." <<
        std::endl;
        return 1;
    }

    return 0;
}