/**
* @file simulador.h
* @brief Motor de paso fijo con gestión interna de estado.
* * Esta versión automatiza el consumo de tiempo acumulado
* eliminado la necesidad de manipular variables externas de
* tiempo en el bucle principal.
*/

#pragma once
#include "plataforma/reloj.h"

namespace Motor {

    /**
    * @class Simulador
    * @brief Controlador de tiempo que gestiona su propio acumulador.
    */
    class Simulador {
        private:
        Plataforma::Reloj& _reloj; /**< Referencia del hardware de tiempo. */
        uint64_t _tiempo_acumulado; /**< Tiempo pendiente por procesar. */
        const uint64_t _paso_fijo_us; /**< Duración constante del tick. */

        public:
        /**
        * @brief Inicializa el simulador con una frecuncia específica.
        * @param r Referencia al reloj del sistema.
        * @param hz Ticks por segundo.
        */
        Simulador(Plataforma::Reloj& r, uint32_t hz);

        /**
        * @brief Alimenta el acumulador con el delta de tiempo real.
        * @param dt_micro Tiempo transcurrio desde el ultimo frame.
        */
        void actualizar_tiempo(uint64_t dt_micro);

        /**
        * @brief Intenta consumir un paso de simulación.
        * @return true si se consumió un tick (resta un paso del acumulador).
        * @return false si no hay suficiente tiempo acumulado.
        */
        bool intentar_tick();

        /**
        * @brief Retorna el valor del paso fijo en segundos.
        */
        double obtener_paso_segundos() const noexcept;
    };
} // namespace Motor