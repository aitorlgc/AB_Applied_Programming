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
        cout << "Historial clinico:\n";
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
            cout << "\nDoctor asociado: " << doctorAsociado->nombre << endl;
        }
        else
        {
            cout << "\nDoctor asociado: Ninguno\n";
        }
        mostrarHistorial();
    }
};

// Clase CitaMedica
class CitaMedica
{
public:
    int idCita;
    int idPaciente;
    int idDoctor;
    string fecha;
    string hora;

    CitaMedica(int idCita, int idPaciente, int idDoctor, const string &fecha, const string &hora)
        : idCita(idCita), idPaciente(idPaciente), idDoctor(idDoctor), fecha(fecha), hora(hora) {}

    void mostrarInfo() const
    {
        cout << "ID Cita: " << idCita << "\nID Paciente: " << idPaciente
             << "\nID Doctor: " << idDoctor << "\nFecha: " << fecha
             << "\nHora: " << hora << endl;
    }
};

// Clase Hospital
class Hospital
{
public:
    vector<Doctor> doctores;
    vector<Paciente> pacientes;
    vector<CitaMedica> citas;

    void cargarDatos()
    {
        cargarDoctores("doctores.txt");
        cargarPacientes("pacientes.txt");
        cargarCitas("citas.txt");
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

    void editarDoctor(int id, const string &nuevoNombre, const string &nuevaEspecialidad)
    {
        Doctor *doctor = encontrarDoctor(id);
        if (doctor)
        {
            doctor->nombre = nuevoNombre;
            doctor->especialidad = nuevaEspecialidad;
            guardarDoctores("doctores.txt");
            cout << "Doctor actualizado correctamente.\n";
        }
        else
        {
            cout << "Doctor con ID " << id << " no encontrado.\n";
        }
    }

    void eliminarDoctor(int id)
    {
        auto it = remove_if(doctores.begin(), doctores.end(), [id](const Doctor &d)
                            { return d.id == id; });
        if (it != doctores.end())
        {
            doctores.erase(it, doctores.end());
            guardarDoctores("doctores.txt");
            cout << "Doctor eliminado correctamente.\n";
        }
        else
        {
            cout << "Doctor con ID " << id << " no encontrado.\n";
        }
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

    void editarPaciente(int id, const string &nuevoNombre, int nuevaEdad, int nuevoIdDoctor)
    {
        Paciente *paciente = encontrarPaciente(id);
        if (paciente)
        {
            Doctor *nuevoDoctor = encontrarDoctor(nuevoIdDoctor);
            if (nuevoDoctor || nuevoIdDoctor == -1)
            {
                paciente->nombre = nuevoNombre;
                paciente->edad = nuevaEdad;
                paciente->doctorAsociado = nuevoDoctor;
                guardarPacientes("pacientes.txt");
                cout << "Paciente actualizado correctamente.\n";
            }
            else
            {
                cout << "Doctor con ID " << nuevoIdDoctor << " no encontrado.\n";
            }
        }
        else
        {
            cout << "Paciente con ID " << id << " no encontrado.\n";
        }
    }

    void eliminarPaciente(int id)
    {
        auto it = remove_if(pacientes.begin(), pacientes.end(), [id](const Paciente &p) { return p.id == id; });
        if (it != pacientes.end())
        {
            pacientes.erase(it, pacientes.end());
            guardarPacientes("pacientes.txt");
            cout << "Paciente eliminado correctamente.\n";
        }
        else
        {
            cout << "Paciente con ID " << id << " no encontrado.\n";
        }
    }

    void agregarCita(int idCita, int idPaciente, int idDoctor, const string &fecha, const string &hora)
    {
        if (encontrarCita(idCita))
        {
            cout << "Error: Ya existe una cita con el ID " << idCita << ".\n";
            return;
        }

        Paciente *paciente = encontrarPaciente(idPaciente);
        Doctor *doctor = encontrarDoctor(idDoctor);

        if (paciente && doctor)
        {
            citas.emplace_back(idCita, idPaciente, idDoctor, fecha, hora);
            guardarCitas("citas.txt");
            cout << "Cita agendada correctamente.\n";
        }
        else
        {
            cout << "Error: Paciente o doctor no encontrado.\n";
        }
    }

    void mostrarCitas() const
    {
        cout << "Lista de citas:\n";
        for (const auto &cita : citas)
        {
            cita.mostrarInfo();
            cout << endl;
        }
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

    CitaMedica *encontrarCita(int idCita)
    {
        for (auto &cita : citas)
        {
            if (cita.idCita == idCita)
                return &cita;
        }
        return nullptr;
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

    void guardarCitas(const string &archivo) const
    {
        ofstream salida(archivo);
        for (const auto &cita : citas)
        {
            salida << cita.idCita << "," << cita.idPaciente << "," << cita.idDoctor
                   << "," << cita.fecha << "," << cita.hora << "\n";
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

    void cargarCitas(const string &archivo)
    {
        ifstream entrada(archivo);
        if (!entrada)
            return;
        string linea;
        while (getline(entrada, linea))
        {
            stringstream ss(linea);
            int idCita, idPaciente, idDoctor;
            string fecha, hora;
            getline(ss, linea, ',');
            idCita = stoi(linea);
            getline(ss, linea, ',');
            idPaciente = stoi(linea);
            getline(ss, linea, ',');
            idDoctor = stoi(linea);
            getline(ss, fecha, ',');
            getline(ss, hora, ',');
            citas.emplace_back(idCita, idPaciente, idDoctor, fecha, hora);
        }
    }

    void agregarHistorialClinico(int idPaciente, const string &nota)
    {
        Paciente *paciente = encontrarPaciente(idPaciente);
        if (paciente)
        {
            paciente->agregarHistorial(nota);
            guardarPacientes("pacientes.txt");
            cout << "Nota agregada al historial clinico del paciente.\n";
        }
        else
        {
            cout << "Paciente con ID " << idPaciente << " no encontrado.\n";
        }
    }

    void mostrarDoctores() const
    {
        cout << "Lista de doctores:\n";
        for (const auto &doctor : doctores)
        {
            doctor.mostrarInfo();
            cout << endl;
        }
    }

    void mostrarPacientes() const
    {
        cout << "Lista de pacientes:\n";
        for (const auto &paciente : pacientes)
        {
            paciente.mostrarInfo();
            cout << endl;
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
        cout << "2. Editar doctor\n";
        cout << "3. Eliminar doctor\n";
        cout << "4. Agregar paciente\n";
        cout << "5. Editar paciente\n";
        cout << "6. Eliminar paciente\n";
        cout << "7. Agregar cita medica\n";
        cout << "8. Mostrar citas medicas\n";
        cout << "9. Mostrar doctores\n";
        cout << "10. Mostrar pacientes\n";
        cout << "11. Agregar historial clinico a un paciente\n";
        cout << "0. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int id;
            string nombre, especialidad;
            cout << "ID del doctor: ";
            cin >> id;
            cin.ignore();
            cout << "Nombre del doctor: ";
            getline(cin, nombre);
            cout << "Especialidad del doctor: ";
            getline(cin, especialidad);
            hospital.agregarDoctor(id, nombre, especialidad);
            break;
        }
        case 2:
        {
            int id;
            string nuevoNombre, nuevaEspecialidad;
            cout << "ID del doctor a editar: ";
            cin >> id;
            cin.ignore();
            cout << "Nuevo nombre del doctor: ";
            getline(cin, nuevoNombre);
            cout << "Nueva especialidad del doctor: ";
            getline(cin, nuevaEspecialidad);
            hospital.editarDoctor(id, nuevoNombre, nuevaEspecialidad);
            break;
        }
        case 3:
        {
            int id;
            cout << "ID del doctor a eliminar: ";
            cin >> id;
            hospital.eliminarDoctor(id);
            break;
        }
        case 4:
        {
            int id, idDoctor, edad;
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
        case 5:
        {
            int id, nuevaEdad, nuevoIdDoctor;
            string nuevoNombre;
            cout << "ID del paciente a editar: ";
            cin >> id;
            cin.ignore();
            cout << "Nuevo nombre del paciente: ";
            getline(cin, nuevoNombre);
            cout << "Nueva edad del paciente: ";
            cin >> nuevaEdad;
            cout << "Nuevo ID del doctor asociado (-1 para ninguno): ";
            cin >> nuevoIdDoctor;
            hospital.editarPaciente(id, nuevoNombre, nuevaEdad, nuevoIdDoctor);
            break;
        }
        case 6:
        {
            int id;
            cout << "ID del paciente a eliminar: ";
            cin >> id;
            hospital.eliminarPaciente(id);
            break;
        }
        case 7:
        {
            int idCita, idPaciente, idDoctor;
            string fecha, hora;
            cout << "ID de la cita medica: ";
            cin >> idCita;
            cout << "ID del paciente: ";
            cin >> idPaciente;
            cout << "ID del doctor: ";
            cin >> idDoctor;
            cin.ignore();
            cout << "Fecha de la cita (DD/MM/AAAA): ";
            getline(cin, fecha);
            cout << "Hora de la cita (HH:MM): ";
            getline(cin, hora);
            hospital.agregarCita(idCita, idPaciente, idDoctor, fecha, hora);
            break;
        }
        case 8:
        {
            hospital.mostrarCitas();
            break;
        }
        case 9:
        {
            hospital.mostrarDoctores();
            break;
        }
        case 10:
        {
            hospital.mostrarPacientes();
            break;
        }
        case 11:
        {
            int idPaciente;
            string nota;
            cout << "ID del paciente: ";
            cin >> idPaciente;
            cin.ignore();
            cout << "Nota para agregar al historial clinico: ";
            getline(cin, nota);
            hospital.agregarHistorialClinico(idPaciente, nota);
            break;
        }
        case 0:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opción invalida. Intente nuevamente.\n";
            break;
        }

    } while (opcion != 0);

    return 0;
}
