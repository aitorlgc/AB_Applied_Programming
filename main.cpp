#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

class Hospital
{
public:
    struct Doctor
    {
        int id;
        string nombre;
        string especialidad;
    };

    struct HistorialClinico
    {
        int idHistorial;
        string fecha;
        string descripcion;
    };

    struct Paciente
    {
        int id;
        string nombre;
        int edad;
        int idDoctor;
        string fechaIngreso;
        vector<HistorialClinico> historiales;
    };

    struct Cita
    {
        int idCita;
        int idPaciente;
        int idDoctor;
        string fecha;
        string hora;
    };

    vector<Doctor> doctores;
    vector<Paciente> pacientes;
    vector<Cita> citas;
    vector<HistorialClinico> historiales;

    // Funciones de gestión
    void agregarDoctor(int id, const string &nombre, const string &especialidad)
    {
        if (existeDoctor(id))
        {
            cout << "Error: Ya existe un doctor con el ID " << id << ". No se puede agregar.\n";
            return;
        }
        doctores.push_back({id, nombre, especialidad});
        cout << "Doctor " << nombre << " agregado correctamente.\n";
        guardarBackup(); // Guardar cambios automáticamente
    }

    bool existeDoctor(int id)
    {
        return any_of(doctores.begin(), doctores.end(), [id](const Doctor &d)
                      { return d.id == id; });
    }

    void agregarPaciente(int id, const string &nombre, int edad, int idDoctor, const string &fechaIngreso)
    {
        if (existePaciente(id))
        {
            cout << "Error: El ID del paciente ya existe.\n";
            return;
        }
        if (!existeDoctor(idDoctor))
        {
            cout << "Error: El ID del doctor asociado no existe.\n";
            return;
        }
        pacientes.push_back({id, nombre, edad, idDoctor, fechaIngreso});
        cout << "Paciente " << nombre << " agregado correctamente.\n";
        guardarBackup(); // Guardar cambios automáticamente
    }

    bool existePaciente(int id)
    {
        return any_of(pacientes.begin(), pacientes.end(), [id](const Paciente &p)
                      { return p.id == id; });
    }

    void agregarHistorial(Paciente& paciente, int idHistorial, const string& fecha, const string& descripcion) 
    {
        paciente.historiales.push_back({idHistorial, fecha, descripcion});
        cout << "Historial clinico agregado con exito.\n";
        guardarBackup(); // Guardar cambios automáticamente
    }

    void agregarCita(int idCita, int idPaciente, int idDoctor, const string &fecha, const string &hora)
    {
        if (existeCita(idCita))
        {
            cout << "Error: El ID de la cita ya existe.\n";
            return;
        }
        if (!existePaciente(idPaciente))
        {
            cout << "Error: El ID del paciente no existe.\n";
            return;
        }
        if (!existeDoctor(idDoctor))
        {
            cout << "Error: El ID del doctor no existe.\n";
            return;
        }
        citas.push_back({idCita, idPaciente, idDoctor, fecha, hora});
        cout << "Cita registrada correctamente.\n";
        guardarBackup(); // Guardar cambios automáticamente
    }

    bool existeCita(int idCita)
    {
        return any_of(citas.begin(), citas.end(), [idCita](const Cita &c)
                      { return c.idCita == idCita; });
    }

    void modificarDoctor(int id, const string &nombre, const string &especialidad)
    {
        for (auto &doctor : doctores)
        {
            if (doctor.id == id)
            {
                doctor.nombre = nombre;
                doctor.especialidad = especialidad;
                cout << "Doctor modificado correctamente.\n";
                guardarBackup(); // Guardar cambios automáticamente
                return;
            }
        }
        cout << "Doctor no encontrado.\n";
    }

    void modificarPaciente(int id, const string &nombre, int edad, int idDoctor, const string &fechaIngreso)
    {
        for (auto &paciente : pacientes)
        {
            if (paciente.id == id)
            {
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

    void modificarHistorial(Paciente& paciente, int idHistorial, const string& nuevaFecha, const string& nuevaDescripcion) {
    for (auto& historial : paciente.historiales) {
        if (historial.idHistorial == idHistorial) {
            historial.fecha = nuevaFecha;
            historial.descripcion = nuevaDescripcion;
            cout << "Historial clinico actualizado con exito.\n";
            return;
        }
    }
    cout << "Historial clinico no encontrado.\n";
}


    void modificarCita(int idCita, int idPaciente, int idDoctor, const string &fecha, const string &hora)
    {
        for (auto &cita : citas)
        {
            if (cita.idCita == idCita)
            {
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

    void eliminarDoctor(int id)
    {
        auto it = remove_if(doctores.begin(), doctores.end(), [id](const Doctor &d)
                            { return d.id == id; });
        if (it != doctores.end())
        {
            doctores.erase(it, doctores.end());
            cout << "Doctor eliminado correctamente.\n";
            guardarBackup(); // Guardar cambios automáticamente
        }
        else
        {
            cout << "Doctor no encontrado.\n";
        }
    }

    void eliminarPaciente(int id)
    {
        auto it = remove_if(pacientes.begin(), pacientes.end(), [id](const Paciente &p)
                            { return p.id == id; });
        if (it != pacientes.end())
        {
            pacientes.erase(it, pacientes.end());
            cout << "Paciente eliminado correctamente.\n";
            guardarBackup(); // Guardar cambios automáticamente
        }
        else
        {
            cout << "Paciente no encontrado.\n";
        }
    }

void eliminarHistorial(Paciente& paciente, int idHistorial) {
    auto it = remove_if(paciente.historiales.begin(), paciente.historiales.end(),
                        [idHistorial](const HistorialClinico& h) { return h.idHistorial == idHistorial; });
    if (it != paciente.historiales.end()) {
        paciente.historiales.erase(it, paciente.historiales.end());
        cout << "Historial clinico eliminado con exito.\n";
    } else {
        cout << "Historial clinico no encontrado.\n";
    }
}

    void eliminarCita(int idCita)
    {
        auto it = remove_if(citas.begin(), citas.end(), [idCita](const Cita &c)
                            { return c.idCita == idCita; });
        if (it != citas.end())
        {
            citas.erase(it, citas.end());
            cout << "Cita eliminada correctamente.\n";
            guardarBackup(); // Guardar cambios automáticamente
        }
        else
        {
            cout << "Cita no encontrada.\n";
        }
    }

    // Funciones de backup
    void guardarBackup()
    {
        ofstream archivoDoctores("doctores_backup.txt");
        for (const auto &doctor : doctores)
        {
            archivoDoctores << doctor.id << "," << doctor.nombre << "," << doctor.especialidad << "\n";
        }

        ofstream archivoPacientes("pacientes_backup.txt");
        for (const auto &paciente : pacientes)
        {
            archivoPacientes << paciente.id << "," << paciente.nombre << "," << paciente.edad << "," << paciente.idDoctor << "," << paciente.fechaIngreso << "\n";
        }

        ofstream archivoHistorial("historial_backup.txt");
    for (const auto &paciente : pacientes)
    {
        for (const auto &historial : paciente.historiales)
        {
            archivoHistorial << paciente.id << "," << historial.idHistorial << "," << historial.fecha << "," << historial.descripcion << "\n";
        }
    }

        ofstream archivoCitas("citas_backup.txt");
        for (const auto &cita : citas)
        {
            archivoCitas << cita.idCita << "," << cita.idPaciente << "," << cita.idDoctor << "," << cita.fecha << "," << cita.hora << "\n";
        }

        cout << "Backup guardado correctamente.\n";
    }

    // Funciones de búsqueda
    void buscarDoctor(const string &nombre)
    {
        bool encontrado = false;
        for (const auto &doctor : doctores)
        {
            if (doctor.nombre.find(nombre) != string::npos)
            {
                cout << "ID: " << doctor.id << ", Nombre: " << doctor.nombre << ", Especialidad: " << doctor.especialidad << endl;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se ha encontrado ningun doctor con ese nombre.\n";
        }
    }

    void buscarPaciente(const string &nombre)
    {
        bool encontrado = false;
        for (const auto &paciente : pacientes)
        {
            if (paciente.nombre.find(nombre) != string::npos)
            {
                cout << "ID: " << paciente.id << ", Nombre: " << paciente.nombre << ", Edad: " << paciente.edad << ", ID Doctor: " << paciente.idDoctor << ", Fecha de ingreso: " << paciente.fechaIngreso << endl;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se ha encontrado ningun paciente.\n";
        }
    }

    void buscarCita(int idCita)
    {
        bool encontrado = false;
        for (const auto &cita : citas)
        {
            if (cita.idCita == idCita)
            {
                cout << "Cita ID: " << cita.idCita << ", Paciente ID: " << cita.idPaciente << ", Doctor ID: " << cita.idDoctor << ", Fecha: " << cita.fecha << ", Hora: " << cita.hora << endl;
                encontrado = true;
            }
        }
        if (!encontrado)
        {
            cout << "No se encontró ninguna cita con ese ID.\n";
        }
    }

    // Funciones para mostrar todos los elementos
    // Función para cargar datos desde el archivo de doctores
    void cargarDoctores()
    {
        ifstream archivoDoctores("doctores_backup.txt");
        doctores.clear();
        if (archivoDoctores.is_open())
        {
            string linea;
            while (getline(archivoDoctores, linea))
            {
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
        }
        else
        {
            cout << "No se pudo abrir el archivo de doctores.\n";
        }
    }

    // Función para cargar datos desde el archivo de pacientes
    void cargarPacientes()
    {
        ifstream archivoPacientes("pacientes_backup.txt");
        pacientes.clear();
        if (archivoPacientes.is_open())
        {
            string linea;
            while (getline(archivoPacientes, linea))
            {
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
        }
        else
        {
            cout << "No se pudo abrir el archivo de pacientes.\n";
        }
    }

    // Función para cargar datos desde el archivo de citas
    void cargarCitas()
    {
        ifstream archivoCitas("citas_backup.txt");
        citas.clear();
        if (archivoCitas.is_open())
        {
            string linea;
            while (getline(archivoCitas, linea))
            {
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
        }
        else
        {
            cout << "No se pudo abrir el archivo de citas.\n";
        }
    }

    // Modificar las funciones de mostrar para cargar datos antes de mostrarlos
    void mostrarDoctores()
    {
        cargarDoctores();
        for (const auto &doctor : doctores)
        {
            cout << "ID: " << doctor.id << ", Nombre: " << doctor.nombre << ", Especialidad: " << doctor.especialidad << endl;
        }
    }

    void mostrarPacientes()
    {
        cargarPacientes();
        for (const auto &paciente : pacientes)
        {
            cout << "ID: " << paciente.id << ", Nombre: " << paciente.nombre << ", Edad: " << paciente.edad
                 << ", ID Doctor: " << paciente.idDoctor << ", Fecha de ingreso: " << paciente.fechaIngreso << endl;
        }
    }

void mostrarHistoriales(const Paciente& paciente) {
    if (paciente.historiales.empty()) {
        cout << "No hay historiales clinicos para este paciente.\n";
        return;
    }
    cout << "Historiales clinicos del paciente " << paciente.nombre << ":\n";
    for (const auto& historial : paciente.historiales) {
        cout << "ID: " << historial.idHistorial
             << ", Fecha: " << historial.fecha
             << ", Descripcion: " << historial.descripcion << '\n';
    }
}

    void mostrarCitas()
    {
        cargarCitas();
        for (const auto &cita : citas)
        {
            cout << "Cita ID: " << cita.idCita << ", Paciente ID: " << cita.idPaciente
                 << ", Doctor ID: " << cita.idDoctor << ", Fecha: " << cita.fecha << ", Hora: " << cita.hora << endl;
        }
    }
    void menuPrincipal()
    {
        int opcion;
        do
        {
            cout << "\nMenu Principal:\n";
            cout << "1. Gestion de doctores\n";
            cout << "2. Gestion de pacientes\n";
            cout << "3. Gestion de citas\n";
            cout << "4. Realizar backup\n";
            cout << "5. Salir\n";
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
                menuDoctores();
                break;
            case 2:
                menuPacientes();
                break;
            case 3:
                menuCitas();
                break;
            case 4:
                guardarBackup();
                break;
            case 5:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida, intente de nuevo.\n";
            }
        } while (opcion != 5);
    }

    void menuDoctores()
    {
        int opcion;
        do
        {
            cout << "\nGestion de doctores:\n";
            cout << "1. Agregar doctor\n";
            cout << "2. Modificar doctor\n";
            cout << "3. Eliminar doctor\n";
            cout << "4. Buscar doctor\n";
            cout << "5. Mostrar todos los doctores\n";
            cout << "6. Volver al menu principal\n";
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
            {
                int id;
                string nombre, especialidad;
                cout << "Ingrese el ID del doctor: ";
                cin >> id;
                cout << "Ingrese el nombre del doctor: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la especialidad del doctor: ";
                getline(cin, especialidad);
                agregarDoctor(id, nombre, especialidad);
                break;
            }
            case 2:
            {
                int id;
                string nombre, especialidad;
                cout << "Ingrese el ID del doctor a modificar: ";
                cin >> id;
                cout << "Ingrese el nuevo nombre del doctor: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la nueva especialidad del doctor: ";
                getline(cin, especialidad);
                modificarDoctor(id, nombre, especialidad);
                break;
            }
            case 3:
            {
                int id;
                cout << "Ingrese el ID del doctor a eliminar: ";
                cin >> id;
                eliminarDoctor(id);
                break;
            }
            case 4:
            {
                string nombre;
                cout << "Ingrese el nombre del doctor a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                buscarDoctor(nombre);
                break;
            }
            case 5:
                mostrarDoctores();
                break;
            case 6:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida, intente de nuevo.\n";
            }
        } while (opcion != 6);
    }

    void menuPacientes()
    {
        int opcion;
        do
        {
            cout << "\nGestion de pacientes:\n";
            cout << "1. Agregar paciente\n";
            cout << "2. Modificar paciente\n";
            cout << "3. Eliminar paciente\n";
            cout << "4. Buscar paciente\n";
            cout << "5. Mostrar todos los pacientes\n";
            cout << "6. Gestionar historiales clinicos de un paciente\n";
            cout << "7. Volver al menu principal\n";
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
            {
                int id, edad, idDoctor;
                string nombre, fechaIngreso;
                cout << "Ingrese el ID del paciente: ";
                cin >> id;
                cout << "Ingrese el nombre del paciente: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la edad del paciente: ";
                cin >> edad;
                cout << "Ingrese el ID del doctor asociado: ";
                cin >> idDoctor;
                cout << "Ingrese la fecha de ingreso (DD-MM-YYYY): ";
                cin.ignore();
                getline(cin, fechaIngreso);
                agregarPaciente(id, nombre, edad, idDoctor, fechaIngreso);
                break;
            }
            case 2:
            {
                int id, edad, idDoctor;
                string nombre, fechaIngreso;
                cout << "Ingrese el ID del paciente a modificar: ";
                cin >> id;
                cout << "Ingrese el nuevo nombre del paciente: ";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese la nueva edad del paciente: ";
                cin >> edad;
                cout << "Ingrese el nuevo ID del doctor asociado: ";
                cin >> idDoctor;
                cout << "Ingrese la nueva fecha de ingreso (DD-MM-YYYY): ";
                cin.ignore();
                getline(cin, fechaIngreso);
                modificarPaciente(id, nombre, edad, idDoctor, fechaIngreso);
                break;
            }
            case 3:
            {
                int id;
                cout << "Ingrese el ID del paciente a eliminar: ";
                cin >> id;
                eliminarPaciente(id);
                break;
            }
            case 4:
            {
                string nombre;
                cout << "Ingrese el nombre del paciente a buscar: ";
                cin.ignore();
                getline(cin, nombre);
                buscarPaciente(nombre);
                break;
            }
            case 5:
                mostrarPacientes();
                break;
            case 6: {
                int id;
                cout << "Ingrese el ID del paciente: ";
                cin >> id;
                auto it = find_if(pacientes.begin(), pacientes.end(),
                                [id](const Paciente& p) { return p.id == id; });
                if (it != pacientes.end()) {
                    menuHistoriales(*it);
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
            }
            case 7:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opción invalida, intente de nuevo.\n";
            }
        } while (opcion != 7);
    }

void menuHistoriales(Paciente& paciente) {
    int opcion;
    do {
        cout << "\nGestion de historiales clinicos para el paciente: " << paciente.nombre << "\n";
        cout << "1. Crear historial clinico\n";
        cout << "2. Mostrar historiales clinicos\n";
        cout << "3. Modificar historial clinico\n";
        cout << "4. Eliminar historial clinico\n";
        cout << "5. Volver al menu de pacientes\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            int idHistorial;
            string fecha, descripcion;
            cout << "Ingrese el ID del historial: ";
            cin >> idHistorial;
            cout << "Ingrese la fecha (DD-MM-YYYY): ";
            cin.ignore();
            getline(cin, fecha);
            cout << "Ingrese la descripcion del historial: ";
            getline(cin, descripcion);
            agregarHistorial(paciente, idHistorial, fecha, descripcion);
            break;
        }
        case 2:
            mostrarHistoriales(paciente);
            break;
        case 3: {
            int idHistorial;
            string nuevaFecha, nuevaDescripcion;
            cout << "Ingrese el ID del historial a modificar: ";
            cin >> idHistorial;
            cout << "Ingrese la nueva fecha (DD-MM-YYYY): ";
            cin.ignore();
            getline(cin, nuevaFecha);
            cout << "Ingrese la nueva descripcion: ";
            getline(cin, nuevaDescripcion);
            modificarHistorial(paciente, idHistorial, nuevaFecha, nuevaDescripcion);
            break;
        }
        case 4: {
            int idHistorial;
            cout << "Ingrese el ID del historial a eliminar: ";
            cin >> idHistorial;
            eliminarHistorial(paciente, idHistorial);
            break;
        }
        case 5:
            cout << "Volviendo al menu de pacientes...\n";
            break;
        default:
            cout << "Opcion invalida, intente de nuevo.\n";
        }
    } while (opcion != 5);
}


    void menuCitas()
    {
        int opcion;
        do
        {
            cout << "\nGestion de citas:\n";
            cout << "1. Agregar cita\n";
            cout << "2. Modificar cita\n";
            cout << "3. Eliminar cita\n";
            cout << "4. Buscar cita\n";
            cout << "5. Mostrar todas las citas\n";
            cout << "6. Volver al menu principal\n";
            cout << "Elija una opcion: ";
            cin >> opcion;

            switch (opcion)
            {
            case 1:
            {
                int idCita, idPaciente, idDoctor;
                string fecha, hora;
                cout << "Ingrese el ID de la cita: ";
                cin >> idCita;
                cout << "Ingrese el ID del paciente: ";
                cin >> idPaciente;
                cout << "Ingrese el ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese la fecha de la cita (DD-MM-YYYY): ";
                cin.ignore();
                getline(cin, fecha);
                cout << "Ingrese la hora de la cita (HH:MM): ";
                getline(cin, hora);
                agregarCita(idCita, idPaciente, idDoctor, fecha, hora);
                break;
            }
            case 2:
            {
                int idCita, idPaciente, idDoctor;
                string fecha, hora;
                cout << "Ingrese el ID de la cita a modificar: ";
                cin >> idCita;
                cout << "Ingrese el nuevo ID del paciente: ";
                cin >> idPaciente;
                cout << "Ingrese el nuevo ID del doctor: ";
                cin >> idDoctor;
                cout << "Ingrese la nueva fecha de la cita (DD-MM-YYYY): ";
                cin.ignore();
                getline(cin, fecha);
                cout << "Ingrese la nueva hora de la cita (HH:MM): ";
                getline(cin, hora);
                modificarCita(idCita, idPaciente, idDoctor, fecha, hora);
                break;
            }
            case 3:
            {
                int idCita;
                cout << "Ingrese el ID de la cita a eliminar: ";
                cin >> idCita;
                eliminarCita(idCita);
                break;
            }
            case 4:
            {
                int idCita;
                cout << "Ingrese el ID de la cita a buscar: ";
                cin >> idCita;
                buscarCita(idCita);
                break;
            }
            case 5:
                mostrarCitas();
                break;
            case 6:
                cout << "Volviendo al menu principal...\n";
                break;
            default:
                cout << "Opcion invalida, intente de nuevo.\n";
            }
        } while (opcion != 6);
    }
};

int main()
{
    cout << "Bienvenido al sistema de gestion hospitalaria de MSMK AAM\n";
    cout << "============================================\n";
    Hospital hospital;
    hospital.menuPrincipal();
    return 0;
}
