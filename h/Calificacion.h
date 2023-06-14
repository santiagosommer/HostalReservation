#ifndef CALIFICACION_
#define CALIFICACION_

#include <string>
#include <map>
#include "Fecha.h"

using namespace std;

class Estadia;
class RespuestaEmpleado;
class Hostal;
class Empleado;
class Notificacion;
class DTCalificacion;

class Calificacion{
    private:
        int puntaje;
        string comentario;
        Fecha fecha;
        Estadia* estadia;
        Hostal* hostal;
        RespuestaEmpleado* respuestaEmpleados;
    public:
        Calificacion(int, string, Fecha, Estadia*, Hostal*, RespuestaEmpleado*);
        int getPuntaje();
        string getComentario();
        Estadia* getEstadia();
        Hostal* getHostal();
        RespuestaEmpleado* getRespuestaempleados();
        //CalificarEstadia
        Notificacion* crearNotificacion(string);
        //ComentarCalificacion
        bool noEstaRespuesta();
        DTCalificacion getDTCalificacion();
        void setComentarioCalificacion(string, Empleado*, Calificacion*);
        //baja reserva
        void eliminarCalificacion();
};

#endif