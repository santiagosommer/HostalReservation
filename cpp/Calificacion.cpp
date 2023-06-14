#include "../h/Calificacion.h"
#include "../h/DTCalificacion.h"
#include "../h/Estadia.h"
#include "../h/Usuario.h"
#include "../h/Reserva.h"
#include "../h/RespuestaEmpleado.h"
#include "../h/Notificacion.h"
#include "../h/Hostal.h"

Calificacion::Calificacion(int i, string c, Fecha f, Estadia* e, Hostal* h, RespuestaEmpleado* emp){
    this->puntaje = i;
    this->comentario = c;
    this->fecha = f;
    this->estadia = e;
    this->hostal = h;
    this->respuestaEmpleados = emp;
}

int Calificacion::getPuntaje(){
    return this->puntaje;
}
string Calificacion::getComentario(){
    return this->comentario;
}
Estadia* Calificacion::getEstadia(){
    return this->estadia;
}
Hostal* Calificacion::getHostal(){
    return this->hostal;
}
Notificacion* Calificacion::crearNotificacion(string emailHuesped){
    return new Notificacion(emailHuesped, 0, this);   
}
RespuestaEmpleado* Calificacion::getRespuestaempleados(){
    return this->respuestaEmpleados;
}
bool Calificacion::noEstaRespuesta(){
    return this->respuestaEmpleados == NULL;
}
DTCalificacion Calificacion::getDTCalificacion(){
    DTCalificacion res(this->puntaje, this->comentario, this->fecha, this->estadia->getHuesped()->getEmail(), this->estadia->getReserva()->getCodigoReserva());
    return res;
}
void Calificacion::setComentarioCalificacion(string mensaje, Empleado* empleado, Calificacion* calificacion){
    RespuestaEmpleado* res = new RespuestaEmpleado(mensaje, empleado, calificacion);
    empleado->setRespuestaEmpleado(res);
    this->respuestaEmpleados = res;
}

void Calificacion::eliminarCalificacion(){
    hostal->eliminarCalificacion(this);
    if(respuestaEmpleados){
        respuestaEmpleados->eliminarRespuesta();
        respuestaEmpleados->~RespuestaEmpleado();
    }
//Que tan bien anda el destructor si no lo defini en la clase? (usa el por defecto supongo)
//ELIMINAR NOTIFICACIOOOON
}