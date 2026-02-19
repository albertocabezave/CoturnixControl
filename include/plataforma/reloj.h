/**
* @file reloj.h
* @brief Interfáz abstracta para la gestión del tiempo de alta precisión.
* * Define las operaciones necesarias para obtener ticks de hardware sin errores de coma
* flotante, garantizano el determinismo en sistemas de control.
*/
#pragma once
#include <cstdint> // Para usar uint64_t y poder usar numeros enteros
// en lugar de double, asi evitamos errores en el calculo de la fisica y desfase de tiempo.

namespace Plataforma {
    /** 
    * @brief Destructor virtual para asegurar la limpieza de clases derivadas
    */
    class Reloj {
        public:
        virtual ~Reloj() = default;

        /**
        * @brief Obtiene el conteo de microsegundos desde un punto de inicio fijo.
        * @return uint64_t en microsegundos (exactitud absoluta).
        * @note Marcada como noexcept porque la obtención del tiempo no debe fallar.
        */
        virtual uint64_t obtener_ticks_micro() const noexcept = 0;

        /**
        * @brief Obtiene la resolucion mínima detectable por el hardware.
        * @return uint64_t Intervalo minimo en microsegundos.
        */
        virtual uint64_t obtener_resolucion_micro() const noexcept = 0;

        /**
        * @brief Utilidad estática para convertir ticks exactos a segundos decimales.
        * @param ticks Cantidad de microsegundos a convertir.
        * @return double Representación en segundos para cálculos físicos.
        * No altera el estado del reloj, solo traduce unidades.
        */
        static double ticks_a_segundos(uint64_t ticks) noexcept {
            return static_cast<double>(ticks) / 1000000.0;
        }
    };
}// namespace Plataforma