#include "Doctor.h"
#include <iostream> // Necesario para std::cout

Doctor::Doctor(int id, const std::string &nombre, const std::string &especialidad)
    : id(id), nombre(nombre), especialidad(especialidad) {}

void Doctor::mostrarInfo() const {
    std::cout << "ID Doctor: " << id << "\nNombre: " << nombre
              << "\nEspecialidad: " << especialidad << std::endl;
}
