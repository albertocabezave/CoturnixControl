/**
* @file simulador.h
* @brief Motor de paso fijo para la sincronización del gemelo digital.
* * Esta clase implementa el algoritmo de acumulación de tiempo para
* garantizar que los sensores virtuales y la lógica de negocio se 
* ejecuten a una frecuencia constante, independientemente de la carga
* del CPU.
*/

#pragma once
#include "plataforma/reloj.h"

namespace Motor {
    /**
    * @class Simulador
    * @brief Controlador de tiempo determinista para la simulación.
    */
    class Simulador {
        private:
        Plataforma::Reloj& _reloj; /**< Referencia al hardware de tiempo. */
        uint64_t _tiempo_acumulado; /**< Microsegundos pendiente de procesar. */
    
        const uint64_t _paso_fijo_us; /**< Intervalo objetivo por tick. */

        public:
        /** 
        * @brief Verifica si el acumulador tiene suficiente tiempo para un tick físico.
        * @param dt_micro Delta de tiempo real capturado desde el ultimo frame.
        * @return true si debe ejecutar un paso de simulación, false en caso contrario.
        * * Éste método es la base de la integridad del sistema bajo estrés.
        */
        bool debe_actualizar(uint64_t dt_micro) {
            _tiempo_acumulado += dt_micro;

            if(_tiempo_acumulado >= _paso_fijo_us) {
                _tiempo_acumulado -= _paso_fijo_us;
                return true;
            }
            return false;
        }

        /**
        * @brief Retorna el valor del paso fijo en segundos para cálculos físicos.
        * @return double Valor constante (ej. 0.01666 para 60Hz).
        */
        double obtener_paso_segundos() cosnt noexcept {
            return Plataforma::Reloj::ticks_a_segundos(_paso_fijo_us);
        }
    };
}