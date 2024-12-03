#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>
#include <iostream>

class Doctor {
public:
    int id;
    std::string nombre;
    std::string especialidad;

    Doctor(int id, const std::string &nombre, const std::string &especialidad);

    void mostrarInfo() const;
};

#endif
