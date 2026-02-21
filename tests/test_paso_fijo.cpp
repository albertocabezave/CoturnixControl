/**
* @file test_paso_fijo.cpp
* @brief Test de validación para la lógica de auto-consumo del simulador.
*/

#include <iostream>
#include <unistd.h>
#include "plataforma/relojLinux.h"
#include "motor/simulador.h"

int main() {
    Plataforma::RelojLinux reloj;
    Motor::Simulador sim(reloj, 10); // 100ms por paso.

    std::cout << "--- TEST DE AUTO CONSUMO ---" << std::endl;

    uint64_t // Terminamos aqui, aqui lo dejamos....
}