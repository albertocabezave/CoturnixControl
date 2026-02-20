/**
* @file relojLinux.h
* @brief Declaración de implementación del reloj para sistemas Linux.
*/

#pragma once
#include "plataforma/reloj.h"

namespace Plataforma {
    class RelojLinux : public Reloj {
        public:
        virtual ~RelojLinux() = default; // Asegura la consistencia del vtable.

        uint64_t obtener_ticks_micro() const noexcept override;
        uint64_t obtener_resolucion_micro() const noexcept override;
    };
}