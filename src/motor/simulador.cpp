/**
* @file simulador.cpp
* @brief Implementación de la logica de acumulación para la estabilidad del sistema.
* * Separado de la cabecera para mantener la integridad del código y evitar
* redeclaraciones durante el enlazado.
*/

#include "motor/simulador.h"

namespace Motor {

    Simulador::Simulador(Plataforma::Reloj& r, uint32_t hz)
    :_reloj(r),
    _tiempo_acumulado(0),
    _paso_fijo_us(1000000 / hz) {}

    bool Simulador::debe_actualizar(uint64_t dt_micro) {
        _tiempo_acumulado += dt_micro;

        if(_tiempo_acumulado >= _paso_fijo_us) {
            _tiempo_acumulado -= _paso_fijo_us;
            return true;
        }
        return false;
    }

    double Simulador::obtener_paso_segundos() const noexcept {
        return Plataforma::Reloj::ticks_a_segundos(_paso_fijo_us);
    }
} // namespace Motor