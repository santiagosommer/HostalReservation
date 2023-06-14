#include "../h/Estadia.h"
#include "../h/Usuario.h"
#include "../h/Reserva.h"
#include "../h/DTEstadia.h"
#include "../h/DTEstadiaPlus.h"
#include "../h/Hostal.h"
#include "../h/Habitacion.h"
#include "../h/DTCalificacion.h"
#include "../h/Calificacion.h"
#include "../h/DTReserva.h"
#include "../h/ControladorReloj.h"
#include "../h/Fecha.h"

Estadia::Estadia(Fecha in, Fecha out, int pro, Reserva* res, Huesped* hue, Calificacion* cal){
    this->checkInReal = in;
    this->checkOutReal = out;
    this->promo = pro;
    this->reserva = res;
    this->huesped = hue;
    this->calificacion = cal;
}

Reserva* Estadia::getReserva(){
    return this->reserva;
}

Huesped* Estadia::getHuesped(){
    return this->huesped;
}

Fecha Estadia::getCheckOut(){
    return this->checkOutReal;
}

Fecha Estadia::getCheckIn(){
    return this->checkInReal;
}

int Estadia::getPromo(){
    return this->promo;
}

Calificacion* Estadia::getCalificacion(){
    return this->calificacion;
}

void Estadia::setCheckOut(Fecha f){
    this->checkOutReal = f;
}

bool Estadia::estaFinalizada(){
    return this->getCheckOut().getAnio() != 0;
}

bool Estadia::esHues(string hues){
    return this->getHuesped()->getEmail() == hues;
}

DTEstadia Estadia::getDTEstadia(){
    DTEstadia res = DTEstadia(this->getHuesped()->getEmail(), this->getReserva()->getCodigoReserva(), this->getCheckIn(), this->getCheckOut(), this->getPromo());
    return res;
}

void Estadia::setCalificacion(string comentario, int puntaje, Hostal* h){
    ControladorReloj* cr = ControladorReloj::getInstance();
    Calificacion* c = new Calificacion(puntaje, comentario, cr->getFechaActual(), this, h, NULL);
    this->calificacion = c;
    h->agregarCalificacion(c);
}

/*DTEstadia Estadia::getDTEstadia(){
    DTEstadia res(this->getHuesped()->getEmail(), this->getReserva()->getCodigoReserva(), this->checkInReal, this->checkOutReal, this->getPromo());
    return res;
}*/

DTEstadiaPlus Estadia::getDTEstadiaPlus(){
    DTEstadiaPlus res(this->getReserva()->getHabitacion()->getHostal()->getNombreHostal(), this->getHuesped()->getNombre(), this->getReserva()->getHabitacion()->getNumero(), this->getReserva()->getCodigoReserva(), this->getCheckIn(), this->getCheckOut(), this->getPromo());
    return res;
}

DTCalificacion Estadia::getDTCalificacion(){
    DTCalificacion nuevo = this->calificacion->getDTCalificacion();
    return nuevo;
}

DTReserva Estadia::getDTReserva(){
    return this->getReserva()->getDTReserva();
}

void Estadia::setPunteroCalificacion(Calificacion* c){
    calificacion = c;
}

void Estadia::eliminarEstadia(){
    huesped->eliminarEstadia(this);
    if(calificacion){
        calificacion->eliminarCalificacion();
        calificacion->~Calificacion();
    }
}