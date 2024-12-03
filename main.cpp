#include <iostream>
#include "Hospital.h"

int main()
{
    Hospital hospital;
    int opcion;

    do
    {
        std::cout << "\nMenu del hospital:\n";
        std::cout << "1. Agregar doctor\n";
        std::cout << "2. Agregar paciente\n";
        std::cout << "3. Mostrar doctores\n";
        std::cout << "4. Mostrar pacientes\n";
        std::cout << "5. Agregar historial clinico a un paciente\n";
        std::cout << "6. Mostrar historial clinico de un paciente\n";
        std::cout << "0. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int id;
            std::string nombre, especialidad;
            std::cout << "ID del doctor: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Nombre del doctor: ";
            getline(std::cin, nombre);
            std::cout << "Especialidad: ";
            getline(std::cin, especialidad);
            hospital.agregarDoctor(id, nombre, especialidad);
            break;
        }
        case 2:
        {
            int id, edad, idDoctor;
            std::string nombre;
            std::cout << "ID del paciente: ";
            std::cin >> id;
            std::cin.ignore();
            std::cout << "Nombre del paciente: ";
            getline(std::cin, nombre);
            std::cout << "Edad del paciente: ";
            std::cin >> edad;
            std::cout << "ID del doctor asociado: ";
            std::cin >> idDoctor;
            hospital.agregarPaciente(id, nombre, edad, idDoctor);
            break;
        }
        case 3:
            hospital.mostrarDoctores();
            break;
        case 4:
            hospital.mostrarPacientes();
            break;
        case 5:
        {
            int idPaciente;
            std::string entrada;
            std::cout << "ID del paciente: ";
            std::cin >> idPaciente;
            std::cin.ignore();
            std::cout << "Entrada para el historial clinico: ";
            getline(std::cin, entrada);
            Paciente *paciente = hospital.encontrarPaciente(idPaciente);
            if (paciente)
            {
                paciente->agregarHistorial(entrada);
                std::cout << "Historial actualizado.\n";
            }
            else
            {
                std::cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 6:
        {
            int idPaciente;
            std::cout << "ID del paciente: ";
            std::cin >> idPaciente;
            Paciente *paciente = hospital.encontrarPaciente(idPaciente);
            if (paciente)
            {
                paciente->mostrarHistorial();
            }
            else
            {
                std::cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 0:
            std::cout << "Saliendo del programa...\n";
            break;
        default:
            std::cout << "Opcion no valida.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}
