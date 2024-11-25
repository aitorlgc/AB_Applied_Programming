#include <iostream> // Biblioteca necesaria para poder entrar y sacar datos
#include <string> // Biblioteca de manipulacion de texto
#include <vector> // Biblioteca para manipulacion de listas
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
    Doctor* doctorAsociado;  // Puntero al doctor asociado
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

    // Agregar doctores al hospital
    hospital.agregarDoctor(1, "Dr. Lopez", "Cardiologia");
    hospital.agregarDoctor(2, "Dra. Garcia", "Pediatria");

    // Agregar pacientes al hospital
    hospital.agregarPaciente(101, "Juan Perez", 45, 1);
    hospital.agregarPaciente(102, "Ana Martinez", 12, 2);

    // Agregar historial clínico a un paciente
    Paciente* paciente = hospital.encontrarPaciente(101);
    if (paciente) {
        paciente->agregarHistorial("Consulta inicial: dolor en el pecho.");
        paciente->agregarHistorial("Diagnostico: arritmia cardiaca.");
    }

    // Mostrar informacion
    hospital.mostrarDoctores();
    hospital.mostrarPacientes();

    // Mostrar historial clinico del paciente
    if (paciente) {
        paciente->mostrarHistorial();
    }

    return 0;
}