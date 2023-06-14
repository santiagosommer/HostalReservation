#ifndef RESPUESTAEMPLEADO_
#define RESPUESTAEMPLEADO_

#include <string>

using namespace std;

class Calificacion;
class Empleado;


class RespuestaEmpleado
{
private:
    string mensaje;
    Empleado* empleado;
    Calificacion* calificacion;
public:
    RespuestaEmpleado(string, Empleado*, Calificacion*);
    string getMensaje();
    Empleado* getEmpleado();
    Calificacion* getCalificacion();
    void eliminarRespuesta();
};


#endif