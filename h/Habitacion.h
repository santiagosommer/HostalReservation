#ifndef HABITACION_
#define HABITACION_

#include <map>
#include <set>
#include <vector>
#include <string>

using namespace std;

class Hostal;
class Reserva;
class Fecha;
class DTEstadia;
class DTReserva;

class Habitacion{
    private:
        int numero;
        int precio;
        int capacidad;
        Hostal* hostal;
        map<int, Reserva*> reservas;
    public:
        Habitacion();
        Habitacion(int, int, int, Hostal*);
        int getNumero();
        int getCapacidad();
        int getPrecio();
        Hostal* getHostal();
        map<int, Reserva*> getReservas();
        void addReserva(Reserva*);
        bool isReservado(Fecha checkIn, Fecha checkOut);
        //CalificarEstadia
        vector<DTEstadia> getEstadiasFinalizadas(string);
        //ConsultaEstadia
        vector<DTEstadia> getDTEstadias();
        //consultar reserva
        vector<DTReserva> getDataReservaDeHabitacion();
        //baja reserva
        set<int> listarCodigoReservasDeHabitacion();
        void eliminarReservaDeHabitacion(int);

        set<string> getAllHuespedes();
};

#endif