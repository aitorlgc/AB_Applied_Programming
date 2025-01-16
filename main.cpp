#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Hospital {
public:
    struct Doctor {
        int id;
        string nombre;
        string especialidad;
    };

    struct Paciente {
    int id;
    string nombre;
    int edad;
    int idDoctor;
    string fechaIngreso; // Cambiar int a string
};


    struct Cita {
        int idCita;
        int idPaciente;
        int idDoctor;
        string fecha;
        string hora;
    };

    vector<Doctor> doctores;
    vector<Paciente> pacientes;
    vector<Cita> citas;

    // Funciones de gestión
   void agregarDoctor(int id, const string& nombre, const string& especialidad) {
    doctores.push_back({id, nombre, especialidad});
    cout << "Doctor " << nombre << " agregado correctamente.\n";
    guardarBackup(); // Guardar cambios automáticamente
}

void agregarPaciente(int id, const string& nombre, int edad, int idDoctor, const string& fechaIngreso) {
    pacientes.push_back({id, nombre, edad, idDoctor, fechaIngreso});
    cout << "Paciente " << nombre << " agregado correctamente.\n";
    guardarBackup(); // Guardar cambios automáticamente
}

void agregarCita(int idCita, int idPaciente, int idDoctor, const string& fecha, const string& hora) {
    citas.push_back({idCita, idPaciente, idDoctor, fecha, hora});
    cout << "Cita registrada correctamente.\n";
    guardarBackup(); // Guardar cambios automáticamente
}

void modificarDoctor(int id, const string& nombre, const string& especialidad) {
    for (auto& doctor : doctores) {
        if (doctor.id == id) {
            doctor.nombre = nombre;
            doctor.especialidad = especialidad;
            cout << "Doctor modificado correctamente.\n";
            guardarBackup(); // Guardar cambios automáticamente
            return;
        }
    }
    cout << "Doctor no encontrado.\n";
}

void modificarPaciente(int id, const string& nombre, int edad, int idDoctor, const string& fechaIngreso) {
    for (auto& paciente : pacientes) {
        if (paciente.id == id) {
            paciente.nombre = nombre;
            paciente.edad = edad;
            paciente.idDoctor = idDoctor;
            paciente.fechaIngreso = fechaIngreso;
            cout << "Paciente modificado correctamente.\n";
            guardarBackup(); // Guardar cambios automáticamente
            return;
        }
    }
    cout << "Paciente no encontrado.\n";
}

void modificarCita(int idCita, int idPaciente, int idDoctor, const string& fecha, const string& hora) {
    for (auto& cita : citas) {
        if (cita.idCita == idCita) {
            cita.idPaciente = idPaciente;
            cita.idDoctor = idDoctor;
            cita.fecha = fecha;
            cita.hora = hora;
            cout << "Cita modificada correctamente.\n";
            guardarBackup(); // Guardar cambios automáticamente
            return;
        }
    }
    cout << "Cita no encontrada.\n";
}

void eliminarDoctor(int id) {
    auto it = remove_if(doctores.begin(), doctores.end(), [id](const Doctor& d) { return d.id == id; });
    if (it != doctores.end()) {
        doctores.erase(it, doctores.end());
        cout << "Doctor eliminado correctamente.\n";
        guardarBackup(); // Guardar cambios automáticamente
    } else {
        cout << "Doctor no encontrado.\n";
    }
}

void eliminarPaciente(int id) {
    auto it = remove_if(pacientes.begin(), pacientes.end(), [id](const Paciente& p) { return p.id == id; });
    if (it != pacientes.end()) {
        pacientes.erase(it, pacientes.end());
        cout << "Paciente eliminado correctamente.\n";
        guardarBackup(); // Guardar cambios automáticamente
    } else {
        cout << "Paciente no encontrado.\n";
    }
}

void eliminarCita(int idCita) {
    auto it = remove_if(citas.begin(), citas.end(), [idCita](const Cita& c) { return c.idCita == idCita; });
    if (it != citas.end()) {
        citas.erase(it, citas.end());
        cout << "Cita eliminada correctamente.\n";
        guardarBackup(); // Guardar cambios automáticamente
    } else {
        cout << "Cita no encontrada.\n";
    }
}


    // Funciones de backup
    void guardarBackup() {
        ofstream archivoDoctores("doctores_backup.txt");
        for (const auto& doctor : doctores) {
            archivoDoctores << doctor.id << "," << doctor.nombre << "," << doctor.especialidad << "\n";
        }

        ofstream archivoPacientes("pacientes_backup.txt");
        for (const auto& paciente : pacientes) {
            archivoPacientes << paciente.id << "," << paciente.nombre << "," << paciente.edad << "," << paciente.idDoctor << "," << paciente.fechaIngreso << "\n";
        }

        ofstream archivoCitas("citas_backup.txt");
        for (const auto& cita : citas) {
            archivoCitas << cita.idCita << "," << cita.idPaciente << "," << cita.idDoctor << "," << cita.fecha << "," << cita.hora << "\n";
        }

        cout << "Backup guardado correctamente.\n";
    }

    // Funciones de búsqueda
    void buscarDoctor(const string& nombre) {
        bool encontrado = false;
        for (const auto& doctor : doctores) {
            if (doctor.nombre.find(nombre) != string::npos) {
                cout << "ID: " << doctor.id << ", Nombre: " << doctor.nombre << ", Especialidad: " << doctor.especialidad << endl;
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No se ha encontrado ningun doctor con ese nombre.\n";
        }
    }

    void buscarPaciente(const string& nombre) {
        bool encontrado = false;
        for (const auto& paciente : pacientes) {
            if (paciente.nombre.find(nombre) != string::npos) {
                cout << "ID: " << paciente.id << ", Nombre: " << paciente.nombre << ", Edad: " << paciente.edad << ", ID Doctor: " << paciente.idDoctor << ", Fecha de ingreso: " << paciente.fechaIngreso << endl;
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No se ha encontrado ningun paciente.\n";
        }
    }

    void buscarCita(int idCita) {
        bool encontrado = false;
        for (const auto& cita : citas) {
            if (cita.idCita == idCita) {
                cout << "Cita ID: " << cita.idCita << ", Paciente ID: " << cita.idPaciente << ", Doctor ID: " << cita.idDoctor << ", Fecha: " << cita.fecha << ", Hora: " << cita.hora << endl;
                encontrado = true;
            }
        }
        if (!encontrado) {
            cout << "No se encontró ninguna cita con ese ID.\n";
        }
    }

    // Funciones para mostrar todos los elementos
   // Función para cargar datos desde el archivo de doctores
void cargarDoctores() {
    ifstream archivoDoctores("doctores_backup.txt");
    doctores.clear();
    if (archivoDoctores.is_open()) {
        string linea;
        while (getline(archivoDoctores, linea)) {
            int id;
            string nombre, especialidad;
            size_t pos1 = linea.find(',');
            size_t pos2 = linea.rfind(',');

            id = stoi(linea.substr(0, pos1));
            nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            especialidad = linea.substr(pos2 + 1);

            doctores.push_back({id, nombre, especialidad});
        }
        archivoDoctores.close();
    } else {
        cout << "No se pudo abrir el archivo de doctores.\n";
    }
}

// Función para cargar datos desde el archivo de pacientes
void cargarPacientes() {
    ifstream archivoPacientes("pacientes_backup.txt");
    pacientes.clear();
    if (archivoPacientes.is_open()) {
        string linea;
        while (getline(archivoPacientes, linea)) {
            int id, edad, idDoctor;
            string nombre, fechaIngreso;

            size_t pos1 = linea.find(',');
            size_t pos2 = linea.find(',', pos1 + 1);
            size_t pos3 = linea.find(',', pos2 + 1);
            size_t pos4 = linea.rfind(',');

            id = stoi(linea.substr(0, pos1));
            nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            edad = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            idDoctor = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
            fechaIngreso = linea.substr(pos4 + 1);

            pacientes.push_back({id, nombre, edad, idDoctor, fechaIngreso});
        }
        archivoPacientes.close();
    } else {
        cout << "No se pudo abrir el archivo de pacientes.\n";
    }
}

// Función para cargar datos desde el archivo de citas
void cargarCitas() {
    ifstream archivoCitas("citas_backup.txt");
    citas.clear();
    if (archivoCitas.is_open()) {
        string linea;
        while (getline(archivoCitas, linea)) {
            int idCita, idPaciente, idDoctor;
            string fecha, hora;

            size_t pos1 = linea.find(',');
            size_t pos2 = linea.find(',', pos1 + 1);
            size_t pos3 = linea.find(',', pos2 + 1);
            size_t pos4 = linea.rfind(',');

            idCita = stoi(linea.substr(0, pos1));
            idPaciente = stoi(linea.substr(pos1 + 1, pos2 - pos1 - 1));
            idDoctor = stoi(linea.substr(pos2 + 1, pos3 - pos2 - 1));
            fecha = linea.substr(pos3 + 1, pos4 - pos3 - 1);
            hora = linea.substr(pos4 + 1);

            citas.push_back({idCita, idPaciente, idDoctor, fecha, hora});
        }
        archivoCitas.close();
    } else {
        cout << "No se pudo abrir el archivo de citas.\n";
    }
}

// Modificar las funciones de mostrar para cargar datos antes de mostrarlos
void mostrarDoctores() {
    cargarDoctores();
    for (const auto& doctor : doctores) {
        cout << "ID: " << doctor.id << ", Nombre: " << doctor.nombre << ", Especialidad: " << doctor.especialidad << endl;
    }
}

void mostrarPacientes() {
    cargarPacientes();
    for (const auto& paciente : pacientes) {
        cout << "ID: " << paciente.id << ", Nombre: " << paciente.nombre << ", Edad: " << paciente.edad
             << ", ID Doctor: " << paciente.idDoctor << ", Fecha de ingreso: " << paciente.fechaIngreso << endl;
    }
}

void mostrarCitas() {
    cargarCitas();
    for (const auto& cita : citas) {
        cout << "Cita ID: " << cita.idCita << ", Paciente ID: " << cita.idPaciente
             << ", Doctor ID: " << cita.idDoctor << ", Fecha: " << cita.fecha << ", Hora: " << cita.hora << endl;
    }
}
};

int main() {
    Hospital hospital;

    int opcion;
    do {
        cout << "\nMenu:\n";
        cout << "1. Agregar Doctor\n";
        cout << "2. Agregar Paciente\n";
        cout << "3. Agregar Cita\n";
        cout << "4. Modificar Doctor\n";
        cout << "5. Modificar Paciente\n";
        cout << "6. Modificar Cita\n";
        cout << "7. Eliminar Doctor\n";
        cout << "8. Eliminar Paciente\n";
        cout << "9. Eliminar Cita\n";
        cout << "10. Buscar Doctor\n";
        cout << "11. Buscar Paciente\n";
        cout << "12. Buscar Cita\n";
        cout << "13. Mostrar Todos los Doctores\n";
        cout << "14. Mostrar Todos los Pacientes\n";
        cout << "15. Mostrar Todas las Citas\n";
        cout << "16. Realizar Backup\n";
        cout << "17. Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                int id;
                string nombre, especialidad;
                cout << "Ingrese el ID del doctor: ";
                cin >> id;
                cout << "Ingrese el nombre del doctor: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la especialidad del doctor: ";
                getline(cin, especialidad);
                hospital.agregarDoctor(id, nombre, especialidad);
                break;
            }
            case 2: {
                int id, edad, idDoctor;
                string nombre, fechaIngreso;
                cout << "Ingrese el ID del paciente: ";
                cin >> id;
                cout << "Ingrese el nombre del paciente: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la edad del paciente: ";
                cin >> edad;
                cout << "Ingrese el ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese la fecha de ingreso (dd-mm-yyyy): ";
                cin.ignore();
                getline(cin, fechaIngreso);
                hospital.agregarPaciente(id, nombre, edad, idDoctor, fechaIngreso);
                break;
            }

            case 3: {
                int idCita, idPaciente, idDoctor;
                string fecha, hora;
                cout << "Ingrese el ID de la cita: ";
                cin >> idCita;
                cout << "Ingrese el ID del paciente: ";
                cin >> idPaciente;
                cout << "Ingrese el ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese la fecha de la cita (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fecha);
                cout << "Ingrese la hora de la cita (HH:MM): ";
                getline(cin, hora);
                hospital.agregarCita(idCita, idPaciente, idDoctor, fecha, hora);
                break;
            }
            case 4: {
                int id;
                string nombre, especialidad;
                cout << "Ingrese el ID del doctor a modificar: ";
                cin >> id;
                cout << "Ingrese el nuevo nombre del doctor: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la nueva especialidad del doctor: ";
                getline(cin, especialidad);
                hospital.modificarDoctor(id, nombre, especialidad);
                break;
            }
            case 5: {
                int id, edad, idDoctor;
                string nombre, fechaIngreso;
                cout << "Ingrese el ID del paciente a modificar: ";
                cin >> id;
                cout << "Ingrese el nuevo nombre del paciente: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la nueva edad del paciente: ";
                cin >> edad;
                cout << "Ingrese el nuevo ID del doctor: ";
                cin >> idDoctor;
                
                hospital.modificarPaciente(id, nombre, edad, idDoctor, fechaIngreso);
                break;
            }
            case 6: {
                int idCita, idPaciente, idDoctor;
                string fecha, hora;
                cout << "Ingrese el ID de la cita a modificar: ";
                cin >> idCita;
                cout << "Ingrese el nuevo ID del paciente: ";
                cin >> idPaciente;
                cout << "Ingrese el nuevo ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese la nueva fecha de la cita (YYYY-MM-DD): ";
                cin.ignore();
                getline(cin, fecha);
                cout << "Ingrese la nueva hora de la cita (HH:MM): ";
                getline(cin, hora);
                hospital.modificarCita(idCita, idPaciente, idDoctor, fecha, hora);
                break;
            }
            case 7: {
                int id;
                cout << "Ingrese el ID del doctor a eliminar: ";
                cin >> id;
                hospital.eliminarDoctor(id);
                break;
            }
            case 8: {
                int id;
                cout << "Ingrese el ID del paciente a eliminar: ";
                cin >> id;
                hospital.eliminarPaciente(id);
                break;
            }
            case 9: {
                int idCita;
                cout << "Ingrese el ID de la cita a eliminar: ";
                cin >> idCita;
                hospital.eliminarCita(idCita);
                break;
            }
            case 10: {
                string nombreDoctor;
                cout << "Ingrese el nombre del doctor a buscar: ";
                cin.ignore();
                getline(cin, nombreDoctor);
                hospital.buscarDoctor(nombreDoctor);
                break;
            }
            case 11: {
                string nombrePaciente;
                cout << "Ingrese el nombre del paciente a buscar: ";
                cin.ignore();
                getline(cin, nombrePaciente);
                hospital.buscarPaciente(nombrePaciente);
                break;
            }
            case 12: {
                int idCita;
                cout << "Ingrese el ID de la cita a buscar: ";
                cin >> idCita;
                hospital.buscarCita(idCita);
                break;
            }
            case 13: {
                hospital.mostrarDoctores();
                break;
            }
            case 14: {
                hospital.mostrarPacientes();
                break;
            }
            case 15: {
                hospital.mostrarCitas();
                break;
            }
            case 16:
                hospital.guardarBackup();
                break;
            case 17:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opción inválida, intente de nuevo.\n";
        }
    } while (opcion != 17);
    return 0;
}
