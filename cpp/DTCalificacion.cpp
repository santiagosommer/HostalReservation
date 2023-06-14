#include "../h/DTCalificacion.h"

DTCalificacion::DTCalificacion(int pun, string com, Fecha fech, string em, int cod){
    puntaje = pun;
    comentario = com;
    fecha = fech;
    emailHuesp = em;
    codigoReserva = cod;
}

DTCalificacion::DTCalificacion(int pun, string com, string em, int cod){
    puntaje = pun;
    comentario = com;
    emailHuesp = em;
    codigoReserva = cod;
}

DTCalificacion::DTCalificacion(int punt, string com){
    this->puntaje = punt;
    this->comentario = com;
}

const int DTCalificacion::getPuntaje() const {
    return puntaje;
}
const string DTCalificacion::getComentario() const{
    return comentario;
}
const Fecha DTCalificacion::getFecha() const{
    return fecha;
}
const string DTCalificacion::getEmailHuesp() const{ 
    return emailHuesp;
}
const int DTCalificacion::getCodigoReserva() const{
    return codigoReserva;
}