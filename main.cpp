#include <iostream>
#include <string>
#include <vector>
// No se utiliza wiondows.h para que sea multisistema, por lo que el texto agregado no muestra tildes ni ciertos simbolos
using namespace std;

// Clase Doctor
class Doctor {
public:
    int id;
    string nombre;
    string especialidad;

    Doctor(int id, const string& nombre, const string& especialidad)
        : id(id), nombre(nombre), especialidad(especialidad) {}

    void mostrarInfo() const {
        cout << "ID Doctor: " << id << "\nNombre: " << nombre
             << "\nEspecialidad: " << especialidad << endl;
    }
};

// Clase Paciente
class Paciente {
public:
    int id;
    string nombre;
    int edad;
    Doctor* doctorAsociado;
    vector<string> historialClinico;

    Paciente(int id, const string& nombre, int edad, Doctor* doctorAsociado)
        : id(id), nombre(nombre), edad(edad), doctorAsociado(doctorAsociado) {}

    void agregarHistorial(const string& entrada) {
        historialClinico.push_back(entrada);
    }

    void mostrarHistorial() const {
        cout << "Historial clinico de " << nombre << ":\n";
        for (const string& entrada : historialClinico) {
            cout << "- " << entrada << endl;
        }
    }

    void mostrarInfo() const {
        cout << "ID Paciente: " << id << "\nNombre: " << nombre
             << "\nEdad: " << edad << "\nDoctor Asociado: " << doctorAsociado->nombre << endl;
    }
};

// Clase Hospital
class Hospital {
public:
    vector<Doctor> doctores;
    vector<Paciente> pacientes;

    void agregarDoctor(int id, const string& nombre, const string& especialidad) {
        doctores.emplace_back(id, nombre, especialidad);
    }

    void agregarPaciente(int id, const string& nombre, int edad, int idDoctor) {
        Doctor* doctor = encontrarDoctor(idDoctor);
        if (doctor) {
            pacientes.emplace_back(id, nombre, edad, doctor);
        } else {
            cout << "Doctor con ID " << idDoctor << " no encontrado." << endl;
        }
    }

    Doctor* encontrarDoctor(int id) {
        for (auto& doctor : doctores) {
            if (doctor.id == id) return &doctor;
        }
        return nullptr;
    }

    Paciente* encontrarPaciente(int id) {
        for (auto& paciente : pacientes) {
            if (paciente.id == id) return &paciente;
        }
        return nullptr;
    }

    void mostrarDoctores() const {
        cout << "Lista de doctores:\n";
        for (const auto& doctor : doctores) {
            doctor.mostrarInfo();
            cout << endl;
        }
    }

    void mostrarPacientes() const {
        cout << "Lista de pacientes:\n";
        for (const auto& paciente : pacientes) {
            paciente.mostrarInfo();
            cout << endl;
        }
    }
};

// Funcion principal
int main() {
    Hospital hospital;
    int opcion;

    do {
        cout << "\nMenu del hospital:\n";
        cout << "1. Agregar doctor\n";
        cout << "2. Agregar paciente\n";
        cout << "3. Mostrar doctores\n";
        cout << "4. Mostrar pacientes\n";
        cout << "5. Agregar historial clinico a un paciente\n";
        cout << "6. Mostrar historial clinico de un paciente\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int id;
            string nombre, especialidad;
            cout << "ID del doctor: ";
            cin >> id;
            cin.ignore();
            cout << "Nombre del doctor: ";
            getline(cin, nombre);
            cout << "Especialidad: ";
            getline(cin, especialidad);
            hospital.agregarDoctor(id, nombre, especialidad);
            break;
        }
        case 2: {
            int id, edad, idDoctor;
            string nombre;
            cout << "ID del paciente: ";
            cin >> id;
            cin.ignore();
            cout << "Nombre del paciente: ";
            getline(cin, nombre);
            cout << "Edad del paciente: ";
            cin >> edad;
            cout << "ID del doctor asociado: ";
            cin >> idDoctor;
            hospital.agregarPaciente(id, nombre, edad, idDoctor);
            break;
        }
        case 3:
            hospital.mostrarDoctores();
            break;
        case 4:
            hospital.mostrarPacientes();
            break;
        case 5: {
            int idPaciente;
            string entrada;
            cout << "ID del paciente: ";
            cin >> idPaciente;
            cin.ignore();
            cout << "Entrada para el historial clinico: ";
            getline(cin, entrada);
            Paciente* paciente = hospital.encontrarPaciente(idPaciente);
            if (paciente) {
                paciente->agregarHistorial(entrada);
                cout << "Historial actualizado.\n";
            } else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 6: {
            int idPaciente;
            cout << "ID del paciente: ";
            cin >> idPaciente;
            Paciente* paciente = hospital.encontrarPaciente(idPaciente);
            if (paciente) {
                paciente->mostrarHistorial();
            } else {
                cout << "Paciente no encontrado.\n";
            }
            break;
        }
        case 0:
            cout << "Saliendo del programa...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
        }
    } while (opcion != 0);

    return 0;
}