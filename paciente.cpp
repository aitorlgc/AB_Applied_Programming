#include "Paciente.h"
#include <iostream>

Paciente::Paciente(int id, const std::string &nombre, int edad, Doctor *doctorAsociado)
    : id(id), nombre(nombre), edad(edad), doctorAsociado(doctorAsociado) {}

void Paciente::agregarHistorial(const std::string &entrada) {
    historialClinico.push_back(entrada);
}

void Paciente::mostrarHistorial() const {
    std::cout << "Historial clinico de " << nombre << ":\n";
    for (const auto &entrada : historialClinico) {
        std::cout << "- " << entrada << std::endl;
    }
}

void Paciente::mostrarInfo() const {
    std::cout << "ID Paciente: " << id << "\nNombre: " << nombre
              << "\nEdad: " << edad << "\nDoctor Asociado: " << doctorAsociado->nombre << std::endl;
}
