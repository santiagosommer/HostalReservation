#ifndef ESTADIA_
#define ESTADIA_

#include "Fecha.h"
#include <string>

class DTReserva;
class Huesped;
class Reserva;
class Calificacion;
class Hostal;
class Fecha;
class DTCalificacion;
class DTEstadia;
class DTEstadiaPlus;

using namespace std;

class Estadia
{
    private:
        Fecha checkInReal;
        Fecha checkOutReal;
        int promo;
        Reserva* reserva;
        Huesped* huesped;
        Calificacion* calificacion;
    public:
        Estadia(Fecha, Fecha, int, Reserva*, Huesped*, Calificacion*);
        Reserva* getReserva();
        Huesped* getHuesped();
        Fecha getCheckOut();
        Fecha getCheckIn();
        int getPromo();
        void setCheckOut(Fecha);
        void setPunteroCalificacion(Calificacion*);
        DTReserva getDTReserva();
        //calificarEstadia
        bool estaFinalizada();
        bool esHues(string);
        DTEstadia getDTEstadia();
        void setCalificacion(string, int, Hostal*);
        Calificacion* getCalificacion();
        //ConsultaEstadia
        DTEstadiaPlus getDTEstadiaPlus();
        DTCalificacion getDTCalificacion();
        //baja reserva
        void eliminarEstadia();
};

#endif