#include "../h/Reserva.h"
#include "../h/ControladorUsuarios.h"
#include "../h/Fecha.h"
#include "../h/Estadia.h"
#include "../h/DTReserva.h"
#include "../h/DTEstadia.h"
#include "../h/Usuario.h"
#include "../h/Habitacion.h"

ReservaIndividual::ReservaIndividual(int codRes, Fecha checkIn, Fecha checkOut, EstadoReserva estado, Habitacion* h)
{
    this->codigoReserva = codRes;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->estado = estado;
    this->habitacion = h;
}

ReservaIndividual::ReservaIndividual(int codRes, Fecha checkIn, Fecha checkOut, EstadoReserva estado, int costo)
{
    this->codigoReserva = codRes;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->estado = estado;
    this->costo = costo;
}

ReservaGrupal::ReservaGrupal(int codRes, Fecha checkIn, Fecha checkOut, EstadoReserva estado, int costo)
{
    this->codigoReserva = codRes;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->estado = estado;
    this->costo = costo;
}

ReservaGrupal::ReservaGrupal(int codRes, Fecha checkIn, Fecha checkOut, EstadoReserva estado, Habitacion* h)
{
    this->codigoReserva = codRes;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->estado = estado;
    this->habitacion = h;
}



int Reserva::getCodigoReserva(){
    return this->codigoReserva;
}

Fecha Reserva::getCheckIn(){
    return this->checkIn;
}

Fecha Reserva::getCheckOut(){
    return this->checkOut;
}

EstadoReserva Reserva::getEstado(){
    return this->estado;
}

int Reserva::getCosto(){
    return this->costo;
}

Habitacion* Reserva::getHabitacion(){
    return this->habitacion;
}

set<Estadia*> Reserva::getEstadias(){
    return this->estadias;
}

Huesped* Reserva::getHuesped(){
    return this->huesped;
}

void Reserva::setCerradaReserva(Fecha fechaAct, int promo, Reserva* res, Huesped* hues){  
    Estadia nueva = Estadia(fechaAct, Fecha(), promo, res, hues, NULL); //links de estadia a reserva y huesped
	Estadia* e = &nueva; 
    this->estado = Cerrada;
	this->estadias.insert(e); //link de reserva a estadia
	hues->agregarEstadia(e); //link de huesped a estadia
}

vector<DTEstadia> Reserva::getEstadiasFinalizadas(string emailHuesped){
    set<Estadia*> es = this->getEstadias();
    set<Estadia*>::iterator itr;
    vector<DTEstadia> res;
    for (itr = es.begin(); itr != es.end(); ++itr) {
        //si esta finalizada
        if ((*itr)->esHues(emailHuesped) && (*itr)->estaFinalizada() && (*itr)->getCalificacion() == NULL){
            DTEstadia aux = (*itr)->getDTEstadia();
            res.emplace_back(aux);
        }
    }
    return res;
}
Estadia* Reserva::getEstadia(string emailHuesped){
    set<Estadia*> es = this->getEstadias();
    set<Estadia*>::iterator itr;
    Estadia* res;
    for (itr = es.begin(); itr != es.end(); ++itr) {
        if ((*itr)->esHues(emailHuesped)){
            res = *itr;
        }
    }
    return res;
}
vector<DTEstadia> Reserva::getDTEstadias(){
    set<Estadia*>::iterator itr;
    vector<DTEstadia> res;
    set<Estadia*> aux = this->getEstadias();
    for (itr = aux.begin(); itr != aux.end(); itr++) {
        res.emplace_back((*itr)->getDTEstadia());
    }
    return res;
}
DTReserva Reserva::getDTReserva(){
    return DTReserva(this->codigoReserva, this->checkIn, this->checkOut, this->estado, this->costo, habitacion->getNumero());
}

void Reserva::setCheckIn(Fecha checkIn)
{
    this->checkIn = checkIn;
}

void Reserva::setCheckOut(Fecha checkOut)
{
    this->checkOut = checkOut;
}
void Reserva::setHuespedes(set<string> huespedes)
{
    set<string>::iterator it = huespedes.begin();
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    Huesped* huesped = cu->getHuesped(*it);
    huesped->addReserva(this);
    this->huesped = huesped;
    it++;
    ReservaGrupal* aux = dynamic_cast<ReservaGrupal*>(this);
    if (aux)
    {
        for (; it != huespedes.end(); it++)
        {
            huesped = cu->getHuesped(*it);
            aux->agregarHuespedExtra(huesped);
            huesped->addReserva(this);
        }
    }
}

void Reserva::setEstadia(Estadia* est){
    estadias.emplace(est);
}

void ReservaGrupal::agregarHuespedExtra(Huesped* h)
{
    this->huespedesExtra.insert(pair<string,Huesped*>(h->getNombre(), h));
}

void ReservaGrupal::calcularCosto() 
{
    int diferenciaAnio = checkOut.getAnio() - checkIn.getAnio();
    int diferenciaMes = checkOut.getMes() - checkIn.getMes();
    int diferenciaDia = checkOut.getDia() - checkIn.getDia();
    
    int cantidadFingers = 0;
    if (huesped->getEsFinger()) ++cantidadFingers;
    map<string, Huesped*>::iterator it = huespedesExtra.begin();
    for (; it != huespedesExtra.end(); ++it)
    {
        if (it->second->getEsFinger()) ++cantidadFingers;
    } 
    costo = ((diferenciaAnio * 365) + (diferenciaMes * 31) + (diferenciaDia)) * habitacion->getPrecio() * ((cantidadFingers >=2) ? 0.70 : 1);
}

void Reserva::addHabitacion(Habitacion* h)
{
    this->habitacion = h;
}

void ReservaIndividual::calcularCosto()
{
    int diferenciaAnio = checkOut.getAnio() - checkIn.getAnio();
    int diferenciaMes = checkOut.getMes() - checkIn.getMes();
    int diferenciaDia = checkOut.getDia() - checkIn.getDia();

    costo = ((diferenciaAnio * 365) + (diferenciaMes * 31) + (diferenciaDia)) * habitacion->getPrecio();
    
}

DTReserva ReservaIndividual::getDTReserva(){
    return DTReservaIndividual(this->codigoReserva, this->checkIn, this->checkOut, this->estado, this->costo, habitacion->getNumero());
}

DTReserva ReservaGrupal::getDTReserva(){
    set<string> nombreHuesped;
    map<string, Huesped*> huespedes = this->huespedesExtra;
    map<string, Huesped*>::iterator itr;
    for (itr = huespedes.begin(); itr != huespedes.end(); ++itr) {
        nombreHuesped.insert(itr->first);
    }
    return DTReservaGrupal(this->codigoReserva, this->checkIn, this->checkOut, this->estado, this->costo, habitacion->getNumero(), nombreHuesped);
}

//baja reserva
//void Reserva::eliminarReservaDeHabitacion(int codigoReservaEstadia){
//    habitacion->eliminarReservaDeHabitacion(codigoReservaEstadia);
//    huesped->eliminarReservaDeHuesped(codigoReservaEstadia);
//    set<Estadia*>::iterator it = estadias.begin();
//    for (; it != estadias.end(); ++it){
//        //eliminar instancia de estadia
//        (*it)->eliminarEstadia();
//    }
//}
void ReservaIndividual::eliminarReservaDeHabitacion(int codigoReservaEstadia){
    habitacion->eliminarReservaDeHabitacion(codigoReservaEstadia);
    huesped->eliminarReservaDeHuesped(codigoReservaEstadia);
    set<Estadia*>::iterator it = estadias.begin();
    for (; it != estadias.end(); ++it){
        //eliminar instancia de estadia
        (*it)->eliminarEstadia();
        (*it)->~Estadia();
    }
}

void ReservaGrupal::eliminarReservaDeHabitacion(int codigoReservaEstadia){
    habitacion->eliminarReservaDeHabitacion(codigoReservaEstadia);
    huesped->eliminarReservaDeHuesped(codigoReservaEstadia);
    set<Estadia*>::iterator it = estadias.begin();
    for (; it != estadias.end(); ++it){
        //eliminar instancia de estadia
        (*it)->eliminarEstadia();
        (*it)->~Estadia();
    }
    map<string, Huesped*>::iterator itr = huespedesExtra.begin();
    for (; itr != huespedesExtra.end(); ++it){
        //eliminar instancia de estadia
        itr->second->eliminarReservaDeHuespedGrupal(codigoReservaEstadia);
    }
}

set<string> ReservaGrupal::getHuespedes()
{
    set<string> huespedesRet;
    huespedesRet.insert(this->huesped->getEmail());
    map<string, Huesped*>::iterator it = this->huespedesExtra.begin();
    
    for(; it != this->huespedesExtra.end(); it++)
    {
        huespedesRet.insert(it->second->getEmail());
    }
    
    return huespedesRet;
}
