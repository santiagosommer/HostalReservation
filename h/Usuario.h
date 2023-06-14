#ifndef USUARIO_
#define USUARIO_

#include <string>
#include <map>
#include <vector>
#include <set>
#include "Enum.h"

class Reserva;
class ReservaGrupal;
class ReservaIndividual;
class RespuestaEmpleado;
class Estadia;
class Calificacion;
class Notificacion;
class Hostal;
class DTHuesped;
class DTEmpleado;
class DTNotificacion;
class DTCalificacion;


using namespace std;

class Observer { 
    protected:
        set<Notificacion*> n;
    public:
        //CalificarEstadia
        virtual void notificarCalificacion(Notificacion*) = 0;
};


class Usuario {
    protected:
        string nombre;
        string email;
        string password;
    public:
        string getEmail();
        string getNombre();
        string getPassword();
};

class Huesped : public Usuario {

    private:
        bool esFinger;
        map<int,ReservaIndividual*> r;
        map<int,ReservaGrupal*> rg;
        set<Estadia*> e;
    public:
        Huesped(string nombre, string email, string password, bool esFinger);
        DTHuesped getDTHuesped();
        set<int> getCodigosReservas();
        set<Estadia*> getEstadiasHuesped();
        bool getEsFinger();
        //baja reserva
        void eliminarReservaDeHuesped(int);
        void eliminarReservaDeHuespedGrupal(int);
        void eliminarEstadia(Estadia*);


        
        void finalizarEstadia();
        void addReserva(Reserva* reserva);
        void agregarEstadia(Estadia* e);
};

class Empleado : public Usuario, public Observer {
    
    private:
        CargoEmpleado cargo;
        set<RespuestaEmpleado*> re;
        Hostal *hostal;

    public:
        Empleado(string nombre, string email, string password, CargoEmpleado cargo);
        
        // GETTERS
        CargoEmpleado getCargoEmpleado();

        // SETTERS
        void setCargo(CargoEmpleado cargo) {this->cargo = cargo;}
        void setHostal(Hostal* hostal) {this->hostal = hostal;}


        DTEmpleado getDTEmpleado();
        void notificarCalificacion(Notificacion*);
        vector<DTNotificacion> getNotificaciones();
        void setRespuestaEmpleado(RespuestaEmpleado*);

        //Consulta de Usuario
        string getHostalDeEmpleado();

        //ComentarCalificacion
        vector<DTCalificacion> getCalificacionesSinResponder();
        //baja reserva
        void eliminarRespuesta(RespuestaEmpleado*);
};

#endif
