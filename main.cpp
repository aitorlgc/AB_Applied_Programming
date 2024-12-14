#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

// Clase Doctor
class Doctor
{
public:
    int id;
    string nombre;
    string especialidad;

    Doctor(int id, const string &nombre, const string &especialidad)
        : id(id), nombre(nombre), especialidad(especialidad) {}

    void mostrarInfo() const
    {
        cout << "ID Doctor: " << id << "\nNombre: " << nombre
             << "\nEspecialidad: " << especialidad << endl;
    }
};

// Clase Paciente
class Paciente
{
public:
    int id;
    string nombre;
    int edad;
    Doctor *doctorAsociado;
    vector<string> historialClinico;

    Paciente(int id, const string &nombre, int edad, Doctor *doctorAsociado)
        : id(id), nombre(nombre), edad(edad), doctorAsociado(doctorAsociado) {}

    void agregarHistorial(const string &nota)
    {
        historialClinico.push_back(nota);
    }

    void mostrarHistorial() const
    {
        cout << "Historial Clinico:\n";
        for (const auto &nota : historialClinico)
        {
            cout << "- " << nota << endl;
        }
    }

    void mostrarInfo() const
    {
        cout << "ID Paciente: " << id << "\nNombre: " << nombre
             << "\nEdad: " << edad;
        if (doctorAsociado)
        {
            cout << "\nDoctor Asociado: " << doctorAsociado->nombre << endl;
        }
        else
        {
            cout << "\nDoctor Asociado: Ninguno\n";
        }
        mostrarHistorial();
    }
};

// Clase Hospital
class Hospital
{
public:
    vector<Doctor> doctores;
    vector<Paciente> pacientes;

    void cargarDatos()
    {
        cargarDoctores("doctores.txt");
        cargarPacientes("pacientes.txt");
    }

    void agregarDoctor(int id, const string &nombre, const string &especialidad)
    {
        if (encontrarDoctor(id))
        {
            cout << "Error: Ya existe un doctor con el ID " << id << ".\n";
            return;
        }
        doctores.emplace_back(id, nombre, especialidad);
        guardarDoctores("doctores.txt");
    }

    void agregarPaciente(int id, const string &nombre, int edad, int idDoctor)
    {
        if (encontrarPaciente(id))
        {
            cout << "Error: Ya existe un paciente con el ID " << id << ".\n";
            return;
        }

        Doctor *doctor = encontrarDoctor(idDoctor);
        if (doctor)
        {
            pacientes.emplace_back(id, nombre, edad, doctor);
            guardarPacientes("pacientes.txt");
        }
        else
        {
            cout << "Doctor con ID " << idDoctor << " no encontrado." << endl;
        }
    }

    void agregarHistorialClinico(int idPaciente, const string &nota)
    {
        Paciente *paciente = encontrarPaciente(idPaciente);
        if (paciente)
        {
            paciente->agregarHistorial(nota);
            guardarPacientes("pacientes.txt");
            cout << "Nota agregada al historial clínico del paciente.\n";
        }
        else
        {
            cout << "Paciente con ID " << idPaciente << " no encontrado.\n";
        }
    }

    void modificarDoctor(int id, const string &nuevoNombre, const string &nuevaEspecialidad)
    {
        Doctor *doctor = encontrarDoctor(id);
        if (doctor)
        {
            doctor->nombre = nuevoNombre;
            doctor->especialidad = nuevaEspecialidad;
            guardarDoctores("doctores.txt");
            cout << "Datos del doctor actualizados correctamente.\n";
        }
        else
        {
            cout << "Doctor con ID " << id << " no encontrado.\n";
        }
    }

    void modificarPaciente(int id, const string &nuevoNombre, int nuevaEdad)
    {
        Paciente *paciente = encontrarPaciente(id);
        if (paciente)
        {
            paciente->nombre = nuevoNombre;
            paciente->edad = nuevaEdad;
            guardarPacientes("pacientes.txt");
            cout << "Datos del paciente actualizados correctamente.\n";
        }
        else
        {
            cout << "Paciente con ID " << id << " no encontrado.\n";
        }
    }

    void eliminarDoctor(int id)
    {
        doctores.erase(remove_if(doctores.begin(), doctores.end(),
                                 [id](const Doctor &d)
                                 { return d.id == id; }),
                       doctores.end());
        guardarDoctores("doctores.txt");
    }

    void eliminarPaciente(int id)
    {
        pacientes.erase(remove_if(pacientes.begin(), pacientes.end(),
                                  [id](const Paciente &p)
                                  { return p.id == id; }),
                        pacientes.end());
        guardarPacientes("pacientes.txt");
    }

    Doctor *encontrarDoctor(int id)
    {
        for (auto &doctor : doctores)
        {
            if (doctor.id == id)
                return &doctor;
        }
        return nullptr;
    }

    Paciente *encontrarPaciente(int id)
    {
        for (auto &paciente : pacientes)
        {
            if (paciente.id == id)
                return &paciente;
        }
        return nullptr;
    }

    void mostrarDoctores() const
    {
        cout << "Lista de Doctores:\n";
        for (const auto &doctor : doctores)
        {
            doctor.mostrarInfo();
            cout << endl;
        }
    }

    void mostrarPacientes() const
    {
        cout << "Lista de Pacientes:\n";
        for (const auto &paciente : pacientes)
        {
            paciente.mostrarInfo();
            cout << endl;
        }
    }

    void guardarDoctores(const string &archivo) const
    {
        ofstream salida(archivo);
        for (const auto &doctor : doctores)
        {
            salida << doctor.id << "," << doctor.nombre << "," << doctor.especialidad << "\n";
        }
    }

    void guardarPacientes(const string &archivo) const
    {
        ofstream salida(archivo);
        for (const auto &paciente : pacientes)
        {
            salida << paciente.id << "," << paciente.nombre << "," << paciente.edad << ","
                   << (paciente.doctorAsociado ? paciente.doctorAsociado->id : -1);
            for (const auto &nota : paciente.historialClinico)
            {
                salida << "," << nota;
            }
            salida << "\n";
        }
    }

    void cargarDoctores(const string &archivo)
    {
        ifstream entrada(archivo);
        if (!entrada)
            return;
        string linea;
        while (getline(entrada, linea))
        {
            stringstream ss(linea);
            string nombre, especialidad;
            int id;
            getline(ss, linea, ',');
            id = stoi(linea);
            getline(ss, nombre, ',');
            getline(ss, especialidad, ',');
            doctores.emplace_back(id, nombre, especialidad);
        }
    }

    void cargarPacientes(const string &archivo)
    {
        ifstream entrada(archivo);
        if (!entrada)
            return;
        string linea;
        while (getline(entrada, linea))
        {
            stringstream ss(linea);
            string nombre;
            int id, edad, idDoctor;
            getline(ss, linea, ',');
            id = stoi(linea);
            getline(ss, nombre, ',');
            getline(ss, linea, ',');
            edad = stoi(linea);
            getline(ss, linea, ',');
            idDoctor = stoi(linea);
            Doctor *doctor = encontrarDoctor(idDoctor);
            Paciente paciente(id, nombre, edad, doctor);

            while (getline(ss, linea, ','))
            {
                paciente.historialClinico.push_back(linea);
            }
            pacientes.push_back(paciente);
        }
    }
};

// Función principal
int main()
{
    Hospital hospital;
    hospital.cargarDatos();
    int opcion;

    do
    {
        cout << "\nMenu del hospital:\n";
        cout << "1. Agregar doctor\n";
        cout << "2. Agregar paciente\n";
        cout << "3. Mostrar doctores\n";
        cout << "4. Mostrar pacientes\n";
        cout << "5. Agregar historial clinico a paciente\n";
        cout << "6. Modificar doctor\n";
        cout << "7. Eliminar doctor\n";
        cout << "8. Modificar paciente\n";
        cout << "9. Eliminar paciente\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int id;
            string nombre, especialidad;
            cout << "Ingrese ID del doctor: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nombre del doctor: ";
            getline(cin, nombre);
            cout << "Ingrese especialidad del doctor: ";
            getline(cin, especialidad);
            hospital.agregarDoctor(id, nombre, especialidad);
            break;
        }
        case 2:
        {
            int id, edad, idDoctor;
            string nombre;
            cout << "Ingrese ID del paciente: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nombre del paciente: ";
            getline(cin, nombre);
            cout << "Ingrese edad del paciente: ";
            cin >> edad;
            cout << "Ingrese ID del doctor asociado: ";
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
        case 5:
        {
            int idPaciente;
            string nota;
            cout << "Ingrese ID del paciente: ";
            cin >> idPaciente;
            cin.ignore();
            cout << "Ingrese nota para el historial clinico: ";
            getline(cin, nota);
            hospital.agregarHistorialClinico(idPaciente, nota);
            break;
        }
        case 6:
        {
            int id;
            string nuevoNombre, nuevaEspecialidad;
            cout << "Ingrese ID del doctor a modificar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nuevo nombre del doctor: ";
            getline(cin, nuevoNombre);
            cout << "Ingrese nueva especialidad del doctor: ";
            getline(cin, nuevaEspecialidad);
            hospital.modificarDoctor(id, nuevoNombre, nuevaEspecialidad);
            break;
        }
        case 7:
        {
            int id;
            cout << "Ingrese ID del doctor a eliminar: ";
            cin >> id;
            hospital.eliminarDoctor(id);
            break;
        }
        case 8:
        {
            int id, nuevaEdad;
            string nuevoNombre;
            cout << "Ingrese ID del paciente a modificar: ";
            cin >> id;
            cin.ignore();
            cout << "Ingrese nuevo nombre del paciente: ";
            getline(cin, nuevoNombre);
            cout << "Ingrese nueva edad del paciente: ";
            cin >> nuevaEdad;
            hospital.modificarPaciente(id, nuevoNombre, nuevaEdad);
            break;
        }
        case 9:
        {
            int id;
            cout << "Ingrese ID del paciente a eliminar: ";
            cin >> id;
            hospital.eliminarPaciente(id);
            break;
        }
        case 0:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opción no válida, intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}
