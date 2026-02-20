/**
* @file relojLinux.cpp
* @brief Implementación del reloj de alta resolución para sistemas Linux.
* * Utiliza std::chrono::steady_clock para garantizar la monoticidad, evitando
* desviaciones causadas por ajustes de hora del sistema (NTP).
*/

#include "plataforma/relojLinux.h"
#include <chrono>

namespace Plataforma {
        /**
        * @brief Captura el tiempo actual de CPU en microsegundos.
        * @return uint64_t Microsegundos transcurridos desde el arranque del reloj. 
        */
        uint64_t RelojLinux::obtener_ticks_micro() const noexcept {
            auto ahora = std::chrono::steady_clock::now();
            return
        std::chrono::duration_cast<std::chrono::microseconds>(
                ahora.time_since_epoch()
            ).count();
        }

        /**
        * @brief Devuelve la resolución del periodo del reloj steady de la librería estándar.
        * @return Resolución en microsegundos.
        */
        uint64_t RelojLinux::obtener_resolucion_micro() const noexcept {
            // En Linux moderno suele ser 1 nanosegundo, pero lo reportamos en micros.
            return 1;
        }
} // namespace Plataforma