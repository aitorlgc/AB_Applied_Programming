#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <vector>
#include "Doctor.h"

class Paciente {
public:
    int id;
    std::string nombre;
    int edad;
    Doctor *doctorAsociado;
    std::vector<std::string> historialClinico;

    Paciente(int id, const std::string &nombre, int edad, Doctor *doctorAsociado);

    void agregarHistorial(const std::string &entrada);
    void mostrarHistorial() const;
    void mostrarInfo() const;
};

#endif
