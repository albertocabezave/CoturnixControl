/**
* @file test_reloj.cpp
* @brief Unidad de validación para el sistema de cronometría de alta precisión.
* * Este programa verifica la interidad del hardware y la implementación de RelojLinux,
* asegurando que el motor de tiempo sea apto para la simulación del Gemelo Digital.
*/

#include <iostream>
#include <cstdint>
#include <unistd.h>
#include "plataforma/reloj.h"
#include "plataforma/relojLinux.h"

/**
* @brief Función principal de diagnóstico del sistema de tiempo.
* * Realiza tres comprobaciones críticas: resolución de ticks, monotonicidad del contador
* y presición de la suspención del kernel.
* @return int 0 si el sistema es estable, 1 si detecta anomalías de hardware.
*/
int main() {
    /** @brief Instancia local de la implementación para linux. */
    Plataforma::RelojLinux reloj;

    std::cout << "--- INICIANDO DIAGNÓSTICO DE PRECISIÓN TEMPORAL ---" << std::endl;

    /** 1. Verificación de la resolución reportada por el hardware. */
    uint64_t resolucion = reloj.obtener_resolucion_micro();
    std::cout << "[INFO] Resolución detectada: " << resolucion << "us" << std::endl;

    /** 2. Test de monotonicidad: El tiempo debe ser una función creciente */
    uint64_t t_alfa = reloj.obtener_ticks_micro();
    uint64_t t_beta = reloj.obtener_ticks_micro();

    if (t_beta < t_alfa) {
        std::cerr << "[ERROR CRÍTICO] El reloj no es monotónico (Tiempo regresivo)." << std::endl;
        return 1;
    }
    std::cout << "[OK] Test de monotonicidad superado." << std::endl;

    /** 3. Test de deriva y latencia del sistema operativo. */
    const uint32_t pausa_objetivo_us = 100000; // 100 milisegundos.

    uint64_t inicio = reloj.obtener_ticks_micro();
    usleep(pausa_objetivo_us);
    uint64_t fin = reloj.obtener_ticks_micro();

    uint64_t delta = fin - inicio;
    double segundos = Plataforma::Reloj::ticks_a_segundos(delta);

    std::cout << "[RESULTADO] Tiempo real transcurrido: " << delta << "us(" << segundos <<
    " s" << std::endl;

    /** Validación de límites: Linux no es un sistema de tiempo real(RTOS), por lo
    * por lo que usleep puede tardar más, pero jamás menos del tiempo solicitado.
    */
    if (delta >= pausa_objetivo_us) {
        std::cout << "[OK] Comportamiento del sistema dentro de los parámetros nominales." <<
        std::endl;
    } else {
        std::cerr << "[ERROR] El reloj reportó menos tiempo del transcurrido físicamente." <<
        std::endl;
        return 1;
    }
    return 0;
}