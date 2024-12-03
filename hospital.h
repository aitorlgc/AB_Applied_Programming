#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <vector>
#include "Doctor.h"
#include "Paciente.h"

class Hospital {
public:
    std::vector<Doctor> doctores;
    std::vector<Paciente> pacientes;

    void agregarDoctor(int id, const std::string &nombre, const std::string &especialidad);
    void agregarPaciente(int id, const std::string &nombre, int edad, int idDoctor);
    Doctor *encontrarDoctor(int id);
    Paciente *encontrarPaciente(int id);
    void mostrarDoctores() const;
    void mostrarPacientes() const;
};

#endif
