#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <vector>
#include <cmath>

#include "h/Fabrica.h"
#include "h/Reserva.h"
#include "h/Usuario.h"
#include "h/Enum.h"
#include "h/Fecha.h"
#include "h/DTHostal.h"
#include "h/DTEstadia.h"
#include "h/DTEstadiaPlus.h"
#include "h/DTReserva.h"
#include "h/DTUsuario.h"
#include "h/DTNotificacion.h"
#include "h/DTHabitacion.h"

int CheckIntCin() // Usado en lugar de cin >> (int) para asegurarse que es un int correcto y no ocurra el Cin Infinite Loop
{
    int newNum;
    std::cin >> newNum;
    bool invalido = cin.fail();
    while (invalido)
    {
        if (std::cin.fail())
        {
            std::cout << "Por favor ingrese un numero valido" << endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> newNum;
        }
        else 
        {
            invalido = false;
        }
    }
    return newNum;
}

using namespace std;

int main()
{
    bool loop = true;
    Fabrica* fabrica = new Fabrica();
    while (loop)
    {
        std::cout << 
        "Ingrese un numero:\n" <<
        "1. Alta de Usuario\n" << 
        "2. Alta de Hostal\n" << 
        "3. Alta de Habitacion\n" <<
        "4. Asignar Empleado a Hostal\n" <<
        "5. Registrar Reserva\n" << 
        "6. Consulta top 3 de Hostales\n" << 
        "7. Registrar Estadia\n" << 
        "8. Finalizar Estadia\n" << 
        "9. Calificar Estadia\n" << 
        "10. Comentar Calificacion\n" << 
        "11. Consulta de Usuario\n" << 
        "12. Consulta de Hostal\n" << 
        "13. Consulta de Reserva\n" << //no esta aun
        "14. Consulta de Estadia\n" << 
        "15. Baja de Reserva\n" << //no esta aun
        "16. Subscribirse a notificaciones \n" <<
        "17. Consultar notificaciones\n" << 
        "18. Eliminar suscripcion\n"<< 
        "19. Salir\n" << 
        endl <<
        "DEBUG:\n"
        "20. Cargar Datos de Prueba\n" << 
        "21. Ajustar Fecha\n";
        

        int num = CheckIntCin();
        switch (num)
        {
            case 1: 
            {
                IUsuarios* interfazUsuario = fabrica->getIUsuarios();
                bool usuarioRepetido = true;
                bool terminarCasoDeUso = false;
                while (usuarioRepetido)
                {
                    string email, nombre, password;
                    bool esEmpleado, esFinger;
                    cout << "Ingrese nombre" << endl;;
                    cin.ignore();
                    getline(cin, nombre);
                    cout << "Ingrese email" << endl;
                    getline(cin, email);
                    cout << "Ingrese password" << endl;
                    getline(cin, password);
                    cout << "Es empleado?\n" << "(1) Si" << endl << "(2) No" << endl;
                    bool incorrecto = true;
                    while (incorrecto)
                    {
                        string fin;
                        cin >> fin;
                        if (fin == "1" || fin == "2")
                        {
                            incorrecto = false;
                            if (fin == "1")
                                esEmpleado = true;
                            else
                                esEmpleado = false;
                        }
                        else
                        {
                            cout << "Por favor, elija una opcion correcta" << endl;
                        }
                    }
                    CargoEmpleado cargo;   
                    if (esEmpleado)
                    {
                        cout << "Elija el cargo del empleado\n" << "(1) Administracion\n" << "(2) Limpieza\n" << "(3) Recepcion\n" << "(4) Infraestructura\n";
                        bool repetir = true;
                        while (repetir)
                        {
                            int option = CheckIntCin();
                            repetir = false;
                            switch (option)
                            {
                                case 1:
                                    cargo = CargoEmpleado::Administracion;
                                break;
                                case 2:
                                    cargo = CargoEmpleado::Limpieza;
                                break;
                                case 3:
                                    cargo = CargoEmpleado::Recepcion;
                                break;
                                case 4:
                                    cargo = CargoEmpleado::Infraestructura;
                                break;
                                default:
                                    repetir = true;
                                    cout << "Por favor, elija una opcion correcta" << endl;
                                break;
                            }
                        }
                    }
                    else
                    {
                        cout << "Es finger?\n" << "(1) Si\n" << "(2) No\n";
                        bool incorrecto = true;
                        while (incorrecto)
                        {
                            string fin;
                            cin >> fin;
                            if (fin == "1" || fin == "2")
                            {
                                incorrecto = false;
                                if (fin == "1")
                                    esFinger = true;
                                else
                                    esFinger = false;
                            }
                            else
                            {
                                cout << "Por favor, elija una opcion correcta" << endl;
                            }
                        }
                    }
                    interfazUsuario = fabrica->getIUsuarios();
                    interfazUsuario->setUserInfo(nombre, email, password);
                    interfazUsuario->esEmpleado(esEmpleado);

                    if (esEmpleado) 
                        interfazUsuario->setCargoEmpleado(cargo);
                    else 
                        interfazUsuario->esFinger(esFinger);

                    if (interfazUsuario->esUsuarioRepetido())
                    {
                        cout << "El usuario que ha ingresado ya existe en el sistema, desea ingresar otro usuario?" << endl << "(1) Si" << endl << "(2) No" << endl;
                        incorrecto = true;
                        while (incorrecto)
                        {
                            string fin;
                            cin >> fin;
                            if (fin == "1" || fin == "2")
                            {
                                incorrecto = false;
                                if (fin == "1")
                                    interfazUsuario->reingresarDatos();
                                else
                                {
                                    terminarCasoDeUso = true;
                                    interfazUsuario->cancelarAltaUsuario();
                                }
                            }
                            else
                            {
                                cout << "Por favor, elija una opcion correcta" << endl;
                            }
                        }

                    }
                    else 
                        usuarioRepetido = false;
                    
                }
                if (!terminarCasoDeUso)
                {
                    cout << "Desea confirmar la creacion del usuario?\n" << "(1) Si\n" << "(2) No\n";
                    bool incorrecto = true;
                    while (incorrecto)
                    {
                        string fin;
                        cin >> fin;
                        if (fin == "1" || fin == "2")
                        {
                            incorrecto = false;
                            if (fin == "1")
                                interfazUsuario->confirmarAltaUsuario();
                            else
                                interfazUsuario->cancelarAltaUsuario();
                        }
                        else
                        {
                            cout << "Por favor, elija una opcion correcta" << endl;
                        }
                    }
                }
                break;
            }  

            case 2: 
            { 
                string nombre, email, telefono;

                cout << "Ingrese nombre del Hostal: \n";
                cin.ignore();
                getline(cin, nombre);
                cout << "Ingrese direccion del Hostal: \n";
                getline(cin, email);
                cout << "Ingrese telefono del Hostal: \n";
                getline(cin, telefono);

                IHostales* interfazHostales = fabrica->getIHostales();
                interfazHostales->setHostalInfo(nombre, email, telefono);
                cout << "Desea confirmar la creacion del hostal?\n" << "(1) Si\n" << "(2) No\n";
                bool incorrecto = true;
                while (incorrecto)
                {
                    string fin;
                    cin >> fin;
                    if (fin == "1" || fin == "2")
                    {
                        incorrecto = false;
                        if (fin == "1")
                            interfazHostales->confirmarAltaHostal();
                        else
                            interfazHostales->cancelarAltaHostal();
                    }
                    else
                    {
                        cout << "Por favor, elija una opcion correcta" << endl;
                    }
                }
                break;
            }

            case 3:{
                //getHostales
                IHostales* interfazHostales = fabrica->getIHostales();

                set<string> allHostales = interfazHostales->getHostales();

                if (allHostales.empty()){
                    cout << "No hostales registrados" << endl;
                    break;
                }
                else{
                    int i = 1;
                    for(set<string>::iterator it = allHostales.begin(); it != allHostales.end(); ++it)
                    {
                        cout << i << ". " << *it << endl;
                        ++i;
                    }
                    string nombreHostal;
                    bool nombreHostalValido = false;
                    cout << "Ingrese nombre del hostal\n";
                    while (!nombreHostalValido)
                    {
                        cin.ignore();
                        getline(cin, nombreHostal);

                        if (allHostales.find(nombreHostal) != allHostales.end())
                        {
                            nombreHostalValido = true;
                        }
                        else
                        {
                            cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                        }
                    }

                    interfazHostales->seleccionarHostal(nombreHostal);

                    //altaHabitacion
                    int numero, precio, capacidad;
                    cout << "Ingrese numero" << endl;
                    numero = CheckIntCin();
                    cout << "Ingrese precio" << endl;
                    precio = CheckIntCin();
                    cout << "Ingrese capacidad" << endl;
                    capacidad = CheckIntCin();
                    interfazHostales->altaHabitacion(numero, precio, capacidad);

                    //Confirmar/Cancelar
                    cout << "Desea confirmar la creacion de la habitacion?\n" << "(1) Si\n" << "(2) No\n";
                    bool incorrecto = true;
                    while (incorrecto)
                    {
                        string fin;
                        cin >> fin;
                        if (fin == "1" || fin == "2")
                        {
                            incorrecto = false;
                            if (fin == "1"){
                                if (interfazHostales->checkearHab(numero)){
                                    cout << "Ya existe una habitacion registrada con ese numero" << endl;
                                    break;
                                }
                                interfazHostales->confirmarAltaHabitacion();
                            }
                            else
                                interfazHostales->cancelarAltaHabitacion();
                        }
                        else
                        {
                            cout << "Por favor, elija una opcion correcta" << endl;
                        }
                    }
                }
                break;


            }

            case 4: 
            {   
                IHostales* interfazHostales = fabrica->getIHostales();

                set<string> allHostales = interfazHostales->getHostales();
                if (allHostales.empty()){
                    cout << "No hay hostales registrados" << endl;
                    break;
                }
                int i = 1;
                for(set<string>::iterator it = allHostales.begin(); it != allHostales.end(); ++it)
                {
                    cout << i << ". " << *it << endl;
                    ++i;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal\n";
                while (!nombreHostalValido)
                {
                    cin.ignore();
                    getline(cin, nombreHostal);

                    if (allHostales.find(nombreHostal) != allHostales.end())
                    {
                        nombreHostalValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }
                bool masEmpleados = true;
                while (masEmpleados)
                {
                    set<string> EmpleadosFueraHostal = interfazHostales->getEmpleadosFueraDeHostal(nombreHostal);
                    if (EmpleadosFueraHostal.empty()){
                        cout << "No hay empleados libres para asignar" << endl;
                        break;
                    }
                    i = 1;
                    for(set<string>::iterator it = EmpleadosFueraHostal.begin(); it != EmpleadosFueraHostal.end(); ++it)
                    {
                        cout << i << ". " << *it << endl;
                        ++i;
                    }
                    bool mailEmpleadoValido = false;
                    string mailEmpleado;
                    cout << "Ingrese mail del empleado a asignar:" << endl;
                    while (!mailEmpleadoValido)
                    {
                        cin >> mailEmpleado;

                        if (EmpleadosFueraHostal.find(mailEmpleado) != EmpleadosFueraHostal.end())
                        {
                            mailEmpleadoValido = true;
                        }
                        else
                        {
                            cout << "Por favor, escriba un empleado que este en la lista." << endl;
                        }
                    }

                    CargoEmpleado cargo;
                    cout << "Elija el cargo del empleado\n" << "(1) Administracion\n" << "(2) Limpieza\n" << "(3) Recepcion\n" << "(4) Infraestructura\n";
                    bool repetir = true;
                    while (repetir)
                    {
                        int option = CheckIntCin();
                        repetir = false;
                        switch (option)
                        {
                            case 1:
                                cargo = CargoEmpleado::Administracion;
                            break;
                            case 2:
                                cargo = CargoEmpleado::Limpieza;
                            break;
                            case 3:
                                cargo = CargoEmpleado::Recepcion;
                            break;
                            case 4:
                                cargo = CargoEmpleado::Infraestructura;
                            break;
                            default:
                            {
                                repetir = true;
                                cout << "Por favor, elija una opcion correcta" << endl;
                                break;
                            }
                        }
                    }
                    interfazHostales->asignarEmpleado(mailEmpleado, cargo);
                    cout << "Desea confirmar la asignacion del empleado?\n" << "(1) Si\n" << "(2) No\n";
                    bool incorrecto = true;
                    while (incorrecto)
                    {
                        string fin;
                        cin >> fin;
                        if (fin == "1" || fin == "2")
                        {
                            incorrecto = false;
                            if (fin == "1")
                            {
                                interfazHostales->confirmarAsignacion();
                                cout << "Asignacion exitosa." << endl;
                            }
                                
                            else
                                interfazHostales->cancelarAsignacion();
                        }
                        else
                        {
                            cout << "Por favor, elija una opcion correcta" << endl;
                        }
                    }
                    cout << "Desea agregar mas empleados al mismo hostal?\n" << "(1) Si\n" << "(2) No\n";
                    incorrecto = true;
                    while (incorrecto)
                    {
                        string fin;
                        cin >> fin;
                        if (fin == "1" || fin == "2")
                        {
                            incorrecto = false;
                            if (fin == "2")
                                masEmpleados = false;
                        }
                        else
                        {
                            cout << "Por favor, elija una opcion correcta" << endl;
                        }
                    }
                }
                break;
            }
            case 5:
            {
                IHostales* interfazHostales = fabrica->getIHostales();
                vector<DTHostal> listaHostales = interfazHostales->getHostalesPlus();
                if (listaHostales.empty())
                {
                    cout << "No existen hostales en los que reservar." << endl;
                    break;
                }
                vector<DTHostal>::iterator auxiliarLista = listaHostales.begin();
                int i = 1;
                for(; auxiliarLista != listaHostales.end(); auxiliarLista++ )
                {
                    cout << i << ". " << auxiliarLista->getNombre() << " - " << auxiliarLista->getDireccion() << " - " << auxiliarLista->getPromCalif() << endl;
                    i++;
                }
                string nombreHostal;
                cout << "Ingrese nombre del Hostal que desea reservar: \n";
                cin.ignore();
                getline(cin, nombreHostal);

                bool existeHostal = interfazHostales->existeHostal(nombreHostal);

                if (!existeHostal)
                {
                    cout << "El hostal que ha ingresado no existe." << endl;
                    break;
                }
                bool fechaValida = false;

                cout << "Ingrese fecha para check-in: " << endl;
                cout << "Hora (Formato H.HH/HH.HH): ";
                
                float horaCheckIn = 9999;
                fechaValida = false;

                while(!fechaValida)
                {
                    cin >> horaCheckIn;
                    if ((0 <= horaCheckIn) && (horaCheckIn < 24) && (horaCheckIn - floor(horaCheckIn) < 0.60))
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }

                cout << endl;
                cout << "Dia (Formato D/DD): ";
                
                fechaValida = false;
                int diaCheckIn = 9999;

                while(!fechaValida)
                {
                    diaCheckIn = CheckIntCin();
                    if ((0 < diaCheckIn) && (diaCheckIn < 32))
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }

                cout << endl;
                cout << "Mes (Formato M/MM): ";


                fechaValida = false;
                int mesCheckIn = 9999;

                while(!fechaValida)
                {
                    mesCheckIn = CheckIntCin();
                    if ((0 < mesCheckIn) && (mesCheckIn < 13))
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }

                cout << endl;
                cout << "Anio (Formato YYYY): ";

                fechaValida = false;
                int anioCheckIn = 9999;
                while(!fechaValida)
                {
                    anioCheckIn = CheckIntCin();
                    if (0 < anioCheckIn)
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }

                cout << endl;

                cout << "Ingrese fecha para check-out: " << endl;
                cout << "Hora (Formato H.HH/HH.HH): ";

                float horaCheckOut = 9999;
                fechaValida = false;

                while(!fechaValida)
                {
                    cin >> horaCheckOut;
                    if ((0 <= horaCheckOut) && (horaCheckOut < 24) && (horaCheckOut - floor(horaCheckOut) < 0.60))
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }

                cout << endl;
                cout << "Dia (Formato D/DD): ";

                fechaValida = false;
                int diaCheckOut = 9999;

                while(!fechaValida)
                {
                    diaCheckOut = CheckIntCin();
                    if ((0 < diaCheckOut) && (diaCheckOut < 32))
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }
                cout << endl;
                cout << "Mes (Formato M/MM): ";

                fechaValida = false;
                int mesCheckOut = 9999;

                while(!fechaValida)
                {
                    mesCheckOut = CheckIntCin();
                    if ((0 < mesCheckOut) && (mesCheckOut < 13))
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }


                cout << endl;
                cout << "Anio (Formato YYYY): ";


                fechaValida = false;
                int anioCheckOut = 9999;
                while(!fechaValida)
                {
                    anioCheckOut = CheckIntCin();
                    if (0 < anioCheckOut)
                    {
                        fechaValida = true;
                    }
                    else
                    {
                        cout << "Por favor, ingrese una fecha valida." << endl;
                    }
                }
                cout << endl;

                if (!Fecha(horaCheckIn,diaCheckIn,mesCheckIn, anioCheckIn).before(Fecha(horaCheckOut,diaCheckOut,mesCheckOut,anioCheckOut)))
                {
                    cout << "ERROR: El check-out no puede ser anterior al check-in" << endl;
                    break;
                }

                bool esReservaGrupal = false;
                cout << "Es Reserva Grupal?\n" << "(1) Si\n" << "(2) No\n";
                bool incorrecto = true;
                while (incorrecto)
                {
                    string fin;
                    cin >> fin;
                    if (fin == "1" || fin == "2")
                    {
                        incorrecto = false;
                        if (fin == "1")
                            esReservaGrupal = true;
                    }
                    else
                    {
                        cout << "Por favor, elija una opcion correcta" << endl;
                    }
                }
                interfazHostales->seleccionarHostalParaReserva(nombreHostal, Fecha(horaCheckIn,diaCheckIn,mesCheckIn,anioCheckIn), Fecha(horaCheckOut, diaCheckOut, mesCheckOut, anioCheckOut), esReservaGrupal);
                set<int> habitacionesLibres = interfazHostales->getHabitacionesLibres();
                if (habitacionesLibres.empty())
                {
                    cout << "No hay habitaciones libres." << endl;
                    break;
                }
                set<int>::iterator it = habitacionesLibres.begin();
                for (; it != habitacionesLibres.end(); it++)
                {
                    cout << "Habitacion " << (*it) << endl;
                }
                cout << "Escriba el numero de la habitacion a elegir: ";
                int numHabitacion;
                bool habitacionValida = false;
                while (!habitacionValida)
                {
                    numHabitacion = CheckIntCin();
                    if (habitacionesLibres.find(numHabitacion) != habitacionesLibres.end())
                    {
                        habitacionValida = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba una habitacion de la lista." << endl;
                    }
                }

                //seleccionarHabitacion
                interfazHostales->seleccionarHabitacion(numHabitacion);

                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                set<string> huespedesListados = interfazUsuarios->getHuespedes();
                if (huespedesListados.empty())
                {
                    cout << "No hay huespedes registrados" << endl;
                    break;
                }
                set<string>::iterator aux = huespedesListados.begin();
                cout << "Lista de huespedes registrados: " << endl;
                i = 1;
                for (; aux != huespedesListados.end(); aux++)
                {
                    cout << i << ". " << *aux << endl;
                    i++;
                }
                cout << "Ingrese el email del huesped a registrar: " ;
                set<string> nombreHuespedes;
                bool mailHuespedValido = false;
                string mailHuesped;
                while (!mailHuespedValido)
                {
                    cin >> mailHuesped;
                    
                    if (huespedesListados.find(mailHuesped) != huespedesListados.end())
                    {
                        mailHuespedValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un huesped que este en la lista." << endl;
                    }
                }
                interfazHostales->seleccionarHuesped(mailHuesped);
                nombreHuespedes.insert(mailHuesped);
                if (esReservaGrupal)
                {
                    bool quiereAgregar = true;
                    while (quiereAgregar)
                    {
                        cout << "Ingrese el mail de otro huesped a agregar a la reserva grupal: ";
                        mailHuespedValido = false;
                        while (!mailHuespedValido)
                        {
                            cin >> mailHuesped;
                            
                            if (huespedesListados.find(mailHuesped) != huespedesListados.end())
                            {
                                if (nombreHuespedes.find(mailHuesped) != nombreHuespedes.end())
                                {
                                    cout << "Escriba un huesped que no este asignado a esta reserva: " << endl;
                                }
                                else mailHuespedValido = true;
                            }
                            else
                            {
                                cout << "Por favor, escriba un huesped que este en la lista." << endl;
                            }
                        }
                        interfazHostales->seleccionarHuesped(mailHuesped);
                        nombreHuespedes.insert(mailHuesped);
                        cout << "Desea agregar mas huespedes?\n" << "(1) Si\n" << "(2) No\n";
                        bool incorrecto = true;
                        while (incorrecto)
                        {
                            string fin;
                            cin >> fin;
                            if (fin == "1" || fin == "2")
                            {
                                incorrecto = false;
                                if (fin == "2")
                                    quiereAgregar = false;
                            }
                            else
                            {
                                cout << "Por favor, elija una opcion correcta" << endl;
                            }
                        }
                    }
                }
                cout << "Datos de la reserva:" << endl;
                cout << "Hostal: " << nombreHostal << endl;
                cout << "Check-in: " << diaCheckIn << "/" << mesCheckIn << "/" <<  anioCheckIn << " " << horaCheckIn << endl;
                cout << "Check-out: " << diaCheckOut << "/" << mesCheckOut << "/" <<  anioCheckOut << " " << horaCheckOut << endl;
                cout << "Es reserva grupal: " << (esReservaGrupal ? "Si" : "No") << endl;
                cout << "Huespedes: " << endl;
                for (set<string>::iterator huespedIt = nombreHuespedes.begin(); huespedIt != nombreHuespedes.end(); huespedIt++)
                {
                    cout << *huespedIt << endl;
                }
                cout << "Desea confirmar la reserva?\n" << "(1) Si\n" << "(2) No\n";
                incorrecto = true;
                string fin;
                while (incorrecto)
                {
                    string fin;
                    cin >> fin;
                    if (fin == "1" || fin == "2")
                    {
                        incorrecto = false;
                    }
                    else
                    {
                        cout << "Por favor, elija una opcion correcta" << endl;
                    }
                }
                if (fin == "2") break;
                
                interfazHostales->confirmarReserva();
                break;
            }
            case 6:
            {
                IHostales* interfazHostales = fabrica->getIHostales();
                set<string> hostales = interfazHostales->getHostales();
                if (hostales.empty()){
                    cout << "No hay Hostales ingresados en el sistema\n";
                }else{
                    map<int,string> top3Hostales = interfazHostales->getTop3Hostales();
                    int i = 1;
                    cout << "Los hoteles con las mejores calificaciones son:\n";
                    map<int,string>::iterator it;
                    for(it = top3Hostales.begin(); it != top3Hostales.end(); ++it)
                    {
                        cout << i << ". " << (it->second) << endl;
                        ++i;
                    }

                    cout << "Desea ver detalles de algun hostal?\n" << "(1) Si\n" << "(2) No\n";
                    int op = CheckIntCin();
                    if (op == 2) {break;}

                    cout << "De cual?\n" << "(1) Primero\n" << "(2) Segundo\n"<< "(3) Tercero\n";
                    bool repetir = true;
                    string nomHost;
                    while (repetir)
                    {
                        int option = CheckIntCin();
                        repetir = false;
                        if (option == 1){
                            it = top3Hostales.begin();
                            nomHost = (it->second);
                        } else if (option == 2) {
                            it = top3Hostales.find(2);
                            nomHost = (it->second);
                        } else if (option == 3){
                            it = top3Hostales.find(3);
                            nomHost = (it->second);
                        }
                    }
                    vector<DTCalificacion> calif = interfazHostales->getDetallesHostal(nomHost);
					i = 1;
                    for(vector<DTCalificacion>::iterator it = calif.begin(); it != calif.end(); ++it)
                    {
                        DTCalificacion DTCalif = *it;
                        cout << i << ".Puntaje: " << DTCalif.getPuntaje()<< "\n.Comentario: " << DTCalif.getComentario() << endl;
                        ++i;
                    }
                }
                break;
            }
            case 7:
            {
                IHostales* interfazHostales = fabrica->getIHostales();
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                set<string> allHostales = interfazHostales->getHostales();
                int i = 1;
                for(set<string>::iterator it = allHostales.begin(); it != allHostales.end(); ++it)
                {
                    cout << i << ". " << (*it) << endl;
                    ++i;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal\n";
                while (!nombreHostalValido)
                {
                    cin.ignore();
                    getline(cin, nombreHostal);

                    if (allHostales.find(nombreHostal) != allHostales.end())
                    {
                        nombreHostalValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }

                set<string> HuespedesRegistrados = interfazHostales->getHuespedesConReserva(nombreHostal);

                if (HuespedesRegistrados.empty()){
                    cout << "No hay huespedes registrados" << endl;
                    break;
                }
                else{
                int i = 1;
                for(set<string>::iterator it = HuespedesRegistrados.begin(); it != HuespedesRegistrados.end(); ++it)
                {
                    cout << i << ". " << *it << endl;
                    ++i;
                }
                string emailHuesped;
                bool emailHuespedValido = false;
                cout << "Ingrese mail del huesped a registrar su estadia\n";
                while (!emailHuespedValido)
                {
            
                    getline(cin, emailHuesped);
                    if (HuespedesRegistrados.find(emailHuesped) != HuespedesRegistrados.end())
                    {
                        emailHuespedValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un usuario que este en la lista." << endl;
                    }
                }
            
                set<int> ReservasNoCanceladasDelHuesped = interfazUsuarios->getReservasDelHuesped(emailHuesped);
                if (ReservasNoCanceladasDelHuesped.empty()){
                    cout << "No hay reservas abiertas para este Huesped" << endl;
                    break;
                }
                else{
                    i = 1;
                    for(set<int>::iterator it = ReservasNoCanceladasDelHuesped.begin(); it != ReservasNoCanceladasDelHuesped.end(); ++it)
                    {
                        cout << i << ". " << *it << endl;
                        ++i;
                    }
                    bool codResValido = false;
                    int codRes;
                    cout << "Ingrese el codigo de la reserva para registrar la estadia\n";
                    while (!codResValido)
                    {
                        codRes = CheckIntCin();

                        if (ReservasNoCanceladasDelHuesped.find(codRes) != ReservasNoCanceladasDelHuesped.end())
                        {
                            codResValido = true;
                            interfazUsuarios->seleccionarReserva(codRes);
                        }
                        else
                        {
                            cout << "Por favor, escriba un codigo de reserva que este en la lista." << endl;
                        }
                    }
                    interfazUsuarios->registrarEstadia();
                    cout << "Estadia agregada existosamente." << endl;
                    }
                }
                break;
            }
            case 8:
            {
                IHostales* interfazHostales = fabrica->getIHostales();
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                IReservas* interfazReservas = fabrica->getIReservas();
                set<string> allHostales = interfazHostales->getHostales();
                int i = 1;
                for(set<string>::iterator it = allHostales.begin(); it != allHostales.end(); ++it)
                {
                    cout << i << ". " << (*it) << endl;
                    ++i;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal" << endl;
                while (!nombreHostalValido)
                {
                    cin.ignore();
                    getline(cin, nombreHostal);

                    if (allHostales.find(nombreHostal) != allHostales.end())
                    {
                        nombreHostalValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }
                set<string> HuespedesRegistrados = interfazUsuarios->getHuespedes();
                bool emailHuespedValido = false;
                string emailHuesped;
                cout << "Ingrese el email del huesped a finalizar su estadia:" << endl;
                while (!emailHuespedValido)
                {
                    getline(cin, emailHuesped);

                    if (HuespedesRegistrados.find(emailHuesped) != HuespedesRegistrados.end())
                    {
                        emailHuespedValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un email de un huesped." << endl;
                    }
                }
                interfazReservas->seleccionarEstadia(1, emailHuesped);
                interfazReservas->finalizarEstadia();
                cout << "Se ha finalizado la estadia." << endl;
                break;
            }
            case 9:
            {
                IHostales* ihostales = fabrica->getIHostales();
                set<string> nombresHostales = ihostales->getHostales();
                cout << "Nombres Hostales:" << endl;
                set<string>::iterator itr;
                for (itr = nombresHostales.begin(); itr != nombresHostales.end(); itr++){
                    cout << *itr << endl;
                }
                IReservas* ireservas = fabrica->getIReservas();
                string hostalSeleccionado;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal" << endl;
                while (!nombreHostalValido)
                {
                    // cin.ignore();
                    getline(cin, hostalSeleccionado);

                    if (nombresHostales.find(hostalSeleccionado) != nombresHostales.end())
                    {
                        nombreHostalValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }
                ireservas->seleccionarHostal(hostalSeleccionado);
                string emailHuesped;
                bool emailHuespedValido = false;
                IUsuarios* iusuarios = fabrica->getIUsuarios();
                set<string> emailsHuespedes = iusuarios->getHuespedes();
                cout << "Ingresar Email Huesped:" << endl << endl;
                while (!emailHuespedValido)
                {
                    // cin.ignore();
                    getline(cin, emailHuesped);
                    if (emailsHuespedes.find(emailHuesped) != emailsHuespedes.end() && !ireservas->getEstadiasFinalizadas(emailHuesped).empty()){
                        emailHuespedValido = true;
                    }else if (ireservas->getEstadiasFinalizadas(emailHuesped).empty()){
                        cout << "No hay reservas finalizadas de este Huesped, pruebe otro" << endl;
                    }else
                        cout << "Por favor, escriba un email valido." << endl;
                }
                
                vector<DTEstadia> estadiasFinalizadas = ireservas->getEstadiasFinalizadas(emailHuesped);
                vector<DTEstadia>::iterator itrEstadias;
                cout << endl << "Estaidas: " << endl;
                for (itrEstadias = estadiasFinalizadas.begin(); itrEstadias != estadiasFinalizadas.end(); itrEstadias++){
                    DTEstadia DTEst = *itrEstadias;
                    cout << "Email Huesped: " << DTEst.getEmailHuesped() << endl;
                    cout << "Codigo Reserva: " << DTEst.getCodigoReserva() << endl;
                    cout << "CheckIn: " << DTEst.getCheckInReal().getDia() << "/" << DTEst.getCheckInReal().getMes() << "/" << DTEst.getCheckInReal().getAnio() << ":" << DTEst.getCheckInReal().getHora() << "hs." << endl;
                    cout << "CheckOut: " << DTEst.getCheckOutReal().getDia() << "/" << DTEst.getCheckOutReal().getMes() << "/" << DTEst.getCheckOutReal().getAnio() << ":" << DTEst.getCheckOutReal().getHora() << "hs." << endl;
                    cout << "Codigo Promo: " << DTEst.getPromo() << endl << endl;
                }
                cout << "Seleccione Estadia:\nCodigo Reserva:" << endl;
                int codigoRes;
                bool esValidoCodigo = false;
                while (!esValidoCodigo)
                {
                    codigoRes = CheckIntCin();

                    for (itrEstadias = estadiasFinalizadas.begin(); itrEstadias != estadiasFinalizadas.end(); itrEstadias++){
                        DTEstadia DTEst = *itrEstadias;
                        if (codigoRes == DTEst.getCodigoReserva()){
                            esValidoCodigo = true;
                        }
                    }
                    if (!esValidoCodigo){
                        cout << "Por favor, escriba un codigo valido." << endl;
                    }
                }
                ireservas->seleccionarEstadia(codigoRes, emailHuesped);
                cout << "Ingresar Comentario: " << endl;
                string comentario;
                cin.ignore();
                getline(cin, comentario);
                cout << "Ingresar Calificacion (1-5):" << endl;
                int cal;
                cin >> cal;
                ireservas->setCalificacion(comentario, cal);
                break;
            }
            case 10:
            {
                IReservas* ireservas = fabrica->getIReservas();
                cout << "Ingrese Email Empleado:" << endl;
                string emailEmpleado;
                cin.ignore();
                getline(cin, emailEmpleado);
                vector<DTCalificacion> calificacionesSinResponder = ireservas->getCalificacionesSinResponder(emailEmpleado);
                vector<DTCalificacion>::iterator itr;
                cout << endl << "Calificaciones: " << endl << endl;
                for (itr = calificacionesSinResponder.begin(); itr != calificacionesSinResponder.end(); itr++){
                    cout << "Codigo Reserva: " << itr->getCodigoReserva() << endl;
                    cout << "Email Hueped: " << itr->getEmailHuesp() << endl;
                    cout << "Puntaje: " << itr->getPuntaje() << endl;
                    cout << "Comentario: " << itr->getComentario() << endl;
                    cout << "Fecha: " << itr->getFecha().getDia() << "/" << itr->getFecha().getMes() << "/" << itr->getFecha().getAnio() << ":" << itr->getFecha().getHora() << "hs" << endl << endl;
                }
                cout << "Seleccionar Calificacion:" << endl;
                int codigoReserva;
                string emailHuesped;
                cout << "Codigo Reserva:" << endl;
                codigoReserva = CheckIntCin();
                cout << "Email Huesped:" << endl;
                cin.ignore();
                getline(cin, emailHuesped);
                ireservas->selectCalificacion(emailHuesped, codigoReserva);
                cout << "Dejar Comentario: " << endl;
                string comentario;
                // cin.ignore();
                getline(cin, comentario);
                ireservas->setComentarioCalificacion(comentario);
                break;
            }
            case 11:{
                //getUsuarios
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();

                set<string> allUsers = interfazUsuarios->getUsuarios();

                if (allUsers.empty()){
                    cout << "No hay usuarios registrados" << endl;
                    break;
                }
                else{
                int i = 1;
                for(set<string>::iterator it = allUsers.begin(); it != allUsers.end(); ++it)
                    {
                        cout << i << ". " << *it << endl;
                        ++i;
                    }
                    string mailUsuario;
                    bool mailUsuarioValido = false;
                    cout << "Ingrese mail del usuario\n";
                    while (!mailUsuarioValido)
                    {
                        cin.ignore();
                        getline(cin, mailUsuario);

                        if (allUsers.find(mailUsuario) != allUsers.end())
                        {
                            mailUsuarioValido = true;
                     }
                        else
                        {
                            cout << "Por favor, escriba un usuario que este en la lista." << endl;
                        }
                    }

                    //seleccionarUsuario
                    interfazUsuarios->seleccionarUsuario(mailUsuario);

                    //listarDatos
                    if (interfazUsuarios->esEmp()){
                        DTEmpleado e = interfazUsuarios->getDTEmpleado();
                        cout << "Email: " << e.getEmail() << endl;
                        cout << "Nombre: " << e.getNombre() << endl;
                        cout << "Cargo: " << e.getCargo() << endl;
                        cout << "Hostal: " << e.getNombreHostal() << endl;
                    }
                    else{
                        DTHuesped h = interfazUsuarios->getDTHuesped();
                        cout << "Email: " << h.getEmail() << endl;
                        cout << "Nombre: " << h.getNombre() << endl;
                        if (h.getEsFinger()){
                            cout << "Es finger: Si" << endl;
                        }
                        else{
                            cout << "Es finger: No" << endl;
                        }
                    }
                }
                break;
            }
            case 12:
            {
                //getHostales
                IHostales* interfazHostales = fabrica->getIHostales();

                set<string> allHostales = interfazHostales->getHostales();
                int i = 1;
                for(set<string>::iterator it = allHostales.begin(); it != allHostales.end(); ++it)
                {
                    cout << i << ". " << *it << endl;
                    ++i;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal\n";
                while (!nombreHostalValido)
                {
                   
                    getline(cin, nombreHostal);

                    if (allHostales.find(nombreHostal) != allHostales.end())
                    {
                        nombreHostalValido = true;
                    }
                    else 
                    {
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }

                //seleccionarHostal
                interfazHostales->seleccionarHostal(nombreHostal);


                //getDTHostal
                DTHostal h = interfazHostales->getDTHostalConsulta();
                cout << "\n" << "Informacion basica del hostal: " << "\n" << endl;
                cout << "Nombre: " << h.getNombre() << endl;
                cout << "Direccion: " << h.getDireccion() << endl;
                cout << "Telefono: " << h.getTelefono() << endl;
                cout << "Promedio de calificaciones: " << h.getPromCalif() << "\n" << endl;
                
                //Habitaciones
                vector<DTHabitacion> dthabs = h.getDTHabs();
                if (dthabs.empty())
                    break;
                cout << "Informacion de las habitaciones:" << "\n" << endl;

                for (auto ite = dthabs.begin(); ite != dthabs.end(); ite++){
                    cout << "Habitacion Nro: " << (*ite).getNumero() << endl;
                    cout << "Precio: " << (*ite).getPrecio() << endl;
                    cout << "Capacidad: " << (*ite).getCapacidad() << "\n" << endl;

                if (!((*ite).getCalificaciones() == NULL)){
                    cout << "Calificaciones: " << "\n" << endl;
                    
                    for (auto itecalis = (*ite).getCalificaciones()->begin(); itecalis != (*ite).getCalificaciones()->end(); itecalis++){
                        cout << "Comentario: " << (*itecalis).getComentario() << endl;
                        cout << "Puntaje: " << (*itecalis).getPuntaje() << "\n" << endl;
                    } 
                }
                    
                }
                //Reservas
                
                
                    ControladorReservas* cr = ControladorReservas::getInstance();
                    set<int> intRes = cr->listarCodigoReservasDeHostal(nombreHostal);
                    if (intRes.empty())
                        break;
                    cout << "Reservas: " << endl;
                    int p = 1;
                    for (auto itera = intRes.begin(); itera != intRes.end(); itera++){
                        cout << p << "." << (*itera) << "\n" << endl;
                        p++;
                    }
                

                //finalizarConsultaHostal
                interfazHostales->finalizarConsultaHostal();

                break;
            }
            case 13:{
                
                IHostales* ihostales = fabrica->getIHostales();
                set<string> nombresHostales = ihostales->getHostales();
                set<string>::iterator itrHostales;
                cout << "Hostales" << endl; 
                for (itrHostales = nombresHostales.begin(); itrHostales != nombresHostales.end(); itrHostales++){
                    cout << *itrHostales << endl;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal" << endl;
                while (!nombreHostalValido)
                {
                    cin.ignore();
                    getline(cin, nombreHostal);
                    if (nombresHostales.find(nombreHostal) != nombresHostales.end()){
                        nombreHostalValido = true;
                    }
                    else{
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }
                IReservas* ireservas = fabrica->getIReservas();
                vector<DTReserva> reservas = ireservas->listarReservasDeHostal(nombreHostal);
                if (reservas.empty())
                {
                    cout << "No hay reservas en el hostal seleccioando." << endl;
                    break;
                }
                vector<DTReservaIndividual> reservasIndividuales = ireservas->getReservasIndividuales(reservas);
                vector<DTReservaGrupal> reservasGrupales = ireservas->getReservasGrupales(reservas);
                


                vector<DTReservaIndividual>::iterator itrReservasInd;
                for (itrReservasInd = reservasIndividuales.begin(); itrReservasInd != reservasIndividuales.end(); itrReservasInd++){
                    (*itrReservasInd).imprimir();
                }
                vector<DTReservaGrupal>:: iterator itrReservasGrupales;
                for (itrReservasGrupales = reservasGrupales.begin(); itrReservasGrupales != reservasGrupales.end(); itrReservasGrupales++){
                    (*itrReservasGrupales).imprimir();
                }
                break;
            }
            case 14:
            {
                IHostales* ihostales = fabrica->getIHostales();
                IReservas* ireservas = fabrica->getIReservas();
                set<string> nombresHostales = ihostales->getHostales();
                set<string>::iterator itrHostales;
                cout << "Hostales" << endl; 
                for (itrHostales = nombresHostales.begin(); itrHostales != nombresHostales.end(); itrHostales++){
                    cout << *itrHostales << endl;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal" << endl;
                cin.ignore();
                while (!nombreHostalValido)
                {
                    getline(cin, nombreHostal);

                    if (nombresHostales.find(nombreHostal) != nombresHostales.end())
                    {
                        nombreHostalValido = true;
                    }
                    else
                    {
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }
                ireservas->seleccionarHostal(nombreHostal);
                vector<DTEstadia> estadias = ireservas->getEstadias();
                vector<DTEstadia>::iterator itrEstadias;
                cout << endl << "Estadias: " << endl << endl;
                for (itrEstadias = estadias.begin(); itrEstadias != estadias.end(); itrEstadias++){
                    DTEstadia DTEst = *itrEstadias;
                    cout << "Email Huesped: " << DTEst.getEmailHuesped() << endl;
                    cout << "Codigo Reserva: " << DTEst.getCodigoReserva() << endl;
                    cout << "CheckIn: " << DTEst.getCheckInReal().getDia() << "/" << DTEst.getCheckInReal().getMes() << "/" << DTEst.getCheckInReal().getAnio() << ":" << DTEst.getCheckInReal().getHora() << "hs." << endl;
                    cout << "CheckOut: " << DTEst.getCheckOutReal().getDia() << "/" << DTEst.getCheckOutReal().getMes() << "/" << DTEst.getCheckOutReal().getAnio() << ":" << DTEst.getCheckOutReal().getHora() << "hs." << endl;
                    cout << "Codigo Promo: " << DTEst.getPromo() << endl << endl;
                }
                cout << "Seleccione Estadia:" << endl;
                int codigoRes;
                string emailHues;
                cout << "Codigo Reserva:" << endl;
                codigoRes = CheckIntCin();
                cout << "Email Huesped:" << endl;
                cin.ignore();
                getline(cin, emailHues);
                ireservas->seleccionarEstadia(codigoRes, emailHues);
                cout << endl << "Datos extra de Estadia Seleccionada: " << endl << endl; 
                DTEstadiaPlus estadiaSeleccionada = ireservas->getEstadiaPlus();
                cout << "Nombre Hostal: " << estadiaSeleccionada.getNombreHostal() << endl;
                cout << "Nombre Huesped: " << estadiaSeleccionada.getNombreHuesped() << endl;
                cout << "Numero Habitacion: " << estadiaSeleccionada.getNumeroHabitacion() << endl;
                cout << "Codigo Reserva: " << estadiaSeleccionada.getCodigoReserva() << endl;
                cout << "CheckIn: " << estadiaSeleccionada.getCheckInReal().getDia() << "/" << estadiaSeleccionada.getCheckInReal().getMes() << "/" << estadiaSeleccionada.getCheckInReal().getAnio() << ":" << estadiaSeleccionada.getCheckInReal().getHora() << "hs." << endl;
                cout << "CheckOut: " << estadiaSeleccionada.getCheckOutReal().getDia() << "/" << estadiaSeleccionada.getCheckOutReal().getMes() << "/" << estadiaSeleccionada.getCheckOutReal().getAnio() << ":" << estadiaSeleccionada.getCheckOutReal().getHora() << "hs." << endl;
                cout << "Codigo Promo: " << estadiaSeleccionada.getPromo() << endl << endl;
                if (ireservas->existeCalificacion()){
                    cout << "Desea ver la Info de la Calificacion: \n(1)Si\n(0)No " << endl;
                    bool verCal;
                    cin >> verCal;
                    if (verCal){
                        cout << endl << "Info Calificacion: " << endl << endl;
                        DTCalificacion cal = ireservas->getDTCalificacion();
                        cout << "Puntaje: " << cal.getPuntaje() << endl;
                        cout << "Comentario: " << cal.getComentario() << endl;
                        cout << "Fecha: " << cal.getFecha().getDia() << "/" << cal.getFecha().getMes() << "/" << cal.getFecha().getAnio() << ":" << cal.getFecha().getHora() << "hs" << endl << endl;
                        if (ireservas->existeRespuestaEmpleado())
                            cout << "Respuesta Empleado: " << ireservas->getRespuestaEmpleado() << endl << endl;
                    }
                }else{
                    cout << "No tiene Calificacion." << endl << endl;
                }
                cout << "Desea ver la Info de la Reserva: \n(1)Si\n(0)No " << endl;
                bool verRes;
                cin >> verRes;
                if (verRes){
                    DTReserva res = ireservas->getDTReserva();
                    cout << endl << "Info Reserva: " << endl << endl;
                    cout << "Codigo Reserva " << res.getCodigo() << endl
                    << "CheckIn: " << res.getCheckIn().getDia() << "/" << res.getCheckIn().getMes() << "/" << res.getCheckIn().getAnio() << ":" << res.getCheckIn().getHora() << "hs." << endl
                    << "CheckOut: " << res.getCheckOut().getDia() << "/" << res.getCheckOut().getMes() << "/" << res.getCheckOut().getAnio() << ":" << res.getCheckOut().getHora() << "hs." << endl;
                    cout << "Estado Reserva: ";
                    switch (res.getEstado())
                    {
                    case 0:
                    {
                        cout << "Abierta" << endl;
                        break;
                    }
                    case 1:
                    {
                        cout << "Cerrada" << endl;
                        break;
                    }
                    case 2:
                    {
                        cout << "Cancelada" << endl;
                        break;
                    }
                    
                    default:
                        break;
                    }
                    cout << "Costo: " << res.getCosto() << endl
                    << "Numero Habitacion: " << res.getNumeroHabitacion() << endl;
                }
                break;
            }
            case 15:
            {
                IHostales* ihostales = fabrica->getIHostales();
                set<string> nombresHostales = ihostales->getHostales();
                set<string>::iterator itrHostales;
                cout << "Hostales:" << endl; 
                for (itrHostales = nombresHostales.begin(); itrHostales != nombresHostales.end(); itrHostales++){
                    cout << *itrHostales << endl;
                }
                string nombreHostal;
                bool nombreHostalValido = false;
                cout << "Ingrese nombre del hostal" << endl;
                while (!nombreHostalValido)
                {
                    cin.ignore();
                    getline(cin, nombreHostal);

                    if (nombresHostales.find(nombreHostal) != nombresHostales.end()){
                        nombreHostalValido = true;
                    }
                    else{
                        cout << "Por favor, escriba un hostal que esta en la lista." << endl;
                    }
                }
                IReservas* ireservas = fabrica->getIReservas();
                set<int> reservas = ireservas->listarCodigoReservasDeHostal(nombreHostal);

                
                if (reservas.empty())
                {
                    cout << "No hay reservas en el hostal seleccioando." << endl;
                    break;
                }


                set<int>::iterator itrReservas;
                cout << "Codigos de reservas:" << endl;
                for (itrReservas = reservas.begin(); itrReservas != reservas.end(); itrReservas++){
                    cout << *itrReservas << endl;
                }


                int codigoRes;
                cout << "Seleccione el codigo de reserva deseado" << endl;
                cin >> codigoRes;
                ireservas->seleccionarReserva(codigoRes);


                cout << "Desea confirmar la baja de reserva?\n" << "(1) Si\n" << "(2) No\n";
                bool incorrecto = true;
                while (incorrecto){
                    string fin;
                    cin >> fin;
                    if (fin == "1" || fin == "2"){
                        incorrecto = false;
                        if (fin == "1"){
                            ireservas->confirmarBajaReserva();
                        }
                    }
                    else{
                        cout << "Por favor, elija una opcion correcta" << endl;
                    }
                }

                break;
            }
            case 16:
            {
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                map<string, string> lista = interfazUsuarios->getListaEmpleados();
                if (lista.size() == 0)
                {
                    cout << "No hay empleados registrados." << endl;
                    break;
                }
                map<string,string>::iterator it = lista.begin();
                cout << "Lista de Empleados" << endl;
                int i = 1;
                for (; it != lista.end(); it++)
                {
                    cout << i << ". " << it->first << endl;
                    i++;
                }
                cout << "Escriba el nombre del empleado a suscribir: ";
                string nombreEmpleado;

                bool nombreExiste = false;
                while (!nombreExiste)
                {
                    cin.ignore();
                    getline(cin, nombreEmpleado);
                    if (lista.find(nombreEmpleado) != lista.end())
                    {
                        nombreExiste = true;
                    }
                    else 
                    {
                        cout << "Empleado no existe, por favor elija un empleado de la lista: ";
                    }
                }
                string emailEmpleado = lista.find(nombreEmpleado)->second;
                interfazUsuarios->seleccionarEmpleado(emailEmpleado);

                cout << "Desea confirmar la suscripcion?" << endl << "(1) Si" << endl << "(2) No" << endl;
                bool incorrecto = true;
                while (incorrecto)
                {
                    string fin;
                    cin >> fin;
                    if (fin == "1" || fin == "2")
                    {
                        incorrecto = false;
                        if (fin == "1")
                        {
                            interfazUsuarios->suscribirEmpleado();
                            cout << "Suscripcion exitosa" << endl;
                        }
                        else
                        {
                            cout << "Se ha cancelado la suscripcion" << endl;
                        }
                    }
                    else
                    {
                        cout << "Por favor, elija una opcion correcta" << endl;
                    }
                }
            break;
            }
            case 17:
            {
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                map<string, string> lista = interfazUsuarios->getListaEmpleados();
                if (lista.size() == 0)
                {
                    cout << "No hay empleados registrados." << endl;
                    break;
                }
                map<string,string>::iterator it = lista.begin();
                cout << "Lista de Empleados" << endl;
                int i = 1;
                for (; it != lista.end(); it++)
                {
                    cout << i << ". " << it->first << endl;
                    i++;
                }
                cout << "Escriba el email del empleado a consultar: ";
                string emailEmpleado;

                bool emailExiste = false;
                while (!emailExiste)
                {
                    cin.ignore();
                    getline(cin, emailEmpleado);
                    if (lista.find(emailEmpleado) != lista.end())
                    {
                        emailExiste = true;
                    }
                    else 
                    {
                        cout << "Empleado no existe, por favor elija un empleado de la lista: ";
                    }
                }
                interfazUsuarios->seleccionarEmpleado(emailEmpleado);
                vector<DTNotificacion> notis = interfazUsuarios->listaNotificaciones();
                vector<DTNotificacion>::iterator iter = notis.begin();
                if (notis.size() == 0)
                {
                    cout << "No hay notificaciones para ese empleado" << endl;
                    break;
                }
                for (; iter != notis.end(); it++)
                {
                    cout << "Autor: " << iter->getAutor() << endl;
                    cout << "Puntaje: " << iter->getPuntaje() << endl;
                    cout << "Comentario: " << iter->getComentario() << endl;
                    cout << endl;
                }
            break;
            }
            case 18:
            {
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                map<string, string> lista = interfazUsuarios->getListaEmpleados();
                if (lista.size() == 0)
                {
                    cout << "No hay empleados registrados." << endl;
                    break;
                }
                map<string,string>::iterator it = lista.begin();
                cout << "Lista de Empleados" << endl;
                int i = 1;
                for (; it != lista.end(); it++)
                {
                    cout << i << ". " << it->first << endl;
                    i++;
                }
                cout << "Escriba el nombre del empleado a desuscribir: ";
                string nombreEmpleado;

                bool nombreExiste = false;
                while (!nombreExiste)
                {
                    getline(cin, nombreEmpleado);
                    if (lista.find(nombreEmpleado) != lista.end())
                    {
                        nombreExiste = true;
                    }
                    else 
                    {
                        cout << "Empleado no existe, por favor elija un empleado de la lista: ";
                    }
                }
                string emailEmpleado = lista.find(nombreEmpleado)->second;
                interfazUsuarios->seleccionarEmpleado(emailEmpleado);

                cout << "Desea confirmar la desuscripcion?" << endl << "(1) Si" << endl << "(2) No" << endl;
                bool incorrecto = true;
                while (incorrecto)
                {
                    string fin;
                    cin >> fin;
                    if (fin == "1" || fin == "2")
                    {
                        incorrecto = false;
                        if (fin == "1")
                        {
                            interfazUsuarios->eliminarEmpleado();
                            cout << "Operacion exitosa" << endl;
                        }
                        else
                        {
                            cout << "Se ha cancelado la desuscripcion" << endl;
                        }
                    }
                    else
                    {
                        cout << "Por favor, elija una opcion correcta" << endl;
                    }
                }
                break;
            }
            case 19:
                {
                    loop = false;
                    break;
            }

            case 20:
            {
                IUsuarios* interfazUsuarios = fabrica->getIUsuarios();
                IHostales* interfazHostales = fabrica->getIHostales();
                IReloj* interfazReloj = fabrica->getIReloj();
                IReservas* interfazReservas = fabrica->getIReservas();

                interfazUsuarios->cargaDatos();
                interfazHostales->cargaDatos();
                interfazReloj->cargaDatos();
                interfazReservas->cargaDatos();

                cout << "Carga de datos existosa" << endl << endl;
                
                break;
            }

            case 21:
            {
                IReloj* interfazReloj = ControladorReloj::getInstance();
                cout << "Ingrese la nueva fecha: " << endl;
                cout << "Hora (Formato H.HH/HH.HH): ";
                float hora;
                cin >> hora;
                cout << endl;
                cout << "Dia: ";
                int dia = CheckIntCin();
                cout << endl;
                cout << "Mes: ";
                int mes = CheckIntCin();
                cout << endl;
                cout << "Anio: ";
                int anio = CheckIntCin();
                cout << endl;

                interfazReloj->modificarFecha(hora,dia,mes,anio);
                break;
            }
            
            default:
            {
                cout << "Por favor ingrese un numero valido" << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
        }
    }
    return 0;
}

