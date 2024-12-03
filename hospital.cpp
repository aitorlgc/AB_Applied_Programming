#include "Hospital.h"
#include <iostream>

void Hospital::agregarDoctor(int id, const std::string &nombre, const std::string &especialidad) {
    doctores.emplace_back(id, nombre, especialidad);
}

void Hospital::agregarPaciente(int id, const std::string &nombre, int edad, int idDoctor) {
    Doctor *doctor = encontrarDoctor(idDoctor);
    if (doctor) {
        pacientes.emplace_back(id, nombre, edad, doctor);
    } else {
        std::cout << "Doctor con ID " << idDoctor << " no encontrado." << std::endl;
    }
}

Doctor *Hospital::encontrarDoctor(int id) {
    for (auto &doctor : doctores) {
        if (doctor.id == id) return &doctor;
    }
    return nullptr;
}

Paciente *Hospital::encontrarPaciente(int id) {
    for (auto &paciente : pacientes) {
        if (paciente.id == id) return &paciente;
    }
    return nullptr;
}

void Hospital::mostrarDoctores() const {
    std::cout << "Lista de doctores:\n";
    for (const auto &doctor : doctores) {
        doctor.mostrarInfo();
        std::cout << std::endl;
    }
}

void Hospital::mostrarPacientes() const {
    std::cout << "Lista de pacientes:\n";
    for (const auto &paciente : pacientes) {
        paciente.mostrarInfo();
        std::cout << std::endl;
    }
}
