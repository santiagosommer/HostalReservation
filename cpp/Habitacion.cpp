#include "../h/Habitacion.h"
#include "../h/Reserva.h"
#include "../h/Fecha.h"
#include "../h/DTEstadia.h"
#include "../h/DTReserva.h"
#include "../h/Usuario.h"

#include <iterator>
#include <vector>

using namespace std;

     
Habitacion::Habitacion(int numero, int precio, int capacidad, Hostal* phostal){
    this->numero = numero;
    this->precio = precio;
    this->capacidad = capacidad;
    this->hostal = phostal;
    map<int, Reserva*> preservas;
    this->reservas = preservas;
}

int Habitacion::getNumero(){
    return this->numero;
}

int Habitacion::getCapacidad(){
    return this->capacidad;
}

int Habitacion::getPrecio(){
    return this->precio;
}

Hostal* Habitacion::getHostal(){
    return this->hostal;
}

map<int, Reserva*> Habitacion::getReservas(){
    return this->reservas;
}

vector<DTEstadia> Habitacion::getEstadiasFinalizadas(string emailHuesped){
    map<int, Reserva*> rs = reservas;
    map<int, Reserva*>::iterator itr;
    vector<DTEstadia> res;
    for (itr = rs.begin(); itr != rs.end(); ++itr) {
        vector<DTEstadia> aux = itr->second->getEstadiasFinalizadas(emailHuesped);
        // agregar aux a res
        vector<DTEstadia>::iterator itr2;
        for (itr2 = aux.begin(); itr2 != aux.end(); ++itr2){
            res.emplace_back(*itr2);
        }
    }
    return res;
}
vector<DTEstadia> Habitacion::getDTEstadias(){
    map<int, Reserva*>::iterator itr;
    vector<DTEstadia> res;
    map<int, Reserva*> aux = this->getReservas();
    for (itr = aux.begin(); itr != aux.end(); itr++) {
        vector<DTEstadia> aux2 = itr->second->getDTEstadias();
        vector<DTEstadia>::iterator itr2;
        for (itr2 = aux2.begin(); itr2 != aux2.end(); itr2++){
            res.emplace_back(*itr2);
        }
    }
    return res;
}
void Habitacion::addReserva(Reserva* reserva)
{
    reserva->addHabitacion(this);
    reservas.insert(pair<int,Reserva*>(reserva->getCodigoReserva(), reserva));
    reserva->calcularCosto();
}
bool Habitacion::isReservado(Fecha checkIn, Fecha checkOut){
    map<int, Reserva*>::iterator it = reservas.begin();
    for(; it != reservas.end(); it++)
    {   
        Reserva* reserva = it->second;
        bool estaReservada = Fecha::areOverlapping(checkIn, checkOut, reserva->getCheckIn(), reserva->getCheckOut());
        if (estaReservada) return true;
    }
    return false;

}

//consulta reserva
vector<DTReserva> Habitacion::getDataReservaDeHabitacion(){
    map<int, Reserva*> rs = this->getReservas();
    map<int, Reserva*>::iterator itr;
    vector<DTReserva> res;
    for (itr = rs.begin(); itr != rs.end(); ++itr) {
        res.emplace_back(itr->second->getDTReserva());
    }
    return res;
}

//baja reserva
set<int> Habitacion::listarCodigoReservasDeHabitacion(){
    map<int, Reserva*> rs = this->getReservas();
    map<int, Reserva*>::iterator itr;
    set<int> res;
    for (itr = rs.begin(); itr != rs.end(); ++itr) {
        res.insert(itr->second->getCodigoReserva());
    }
    return res;
}

void Habitacion::eliminarReservaDeHabitacion(int codigoReservaEstadia){
    reservas.erase(codigoReservaEstadia);
}

set<string> Habitacion::getAllHuespedes()
{
    map<int, Reserva*> allReservas = reservas;
    map<int, Reserva*>::iterator resIt = allReservas.begin();
    set<string> huespedes;

    for(; resIt != allReservas.end(); resIt++)
    {
        ReservaGrupal* rg = dynamic_cast<ReservaGrupal*>(resIt->second);
        ReservaIndividual* ri = dynamic_cast<ReservaIndividual*>(resIt->second);
        if(rg)
        {
            huespedes.insert(rg->getHuesped()->getEmail());
            set<string> huespedesRg = rg->getHuespedes();
            set<string>::iterator huesped = huespedesRg.begin();
            for(; huesped != huespedesRg.end(); huesped++)
            {
                huespedes.insert(*huesped);
            }
        }
        else if (ri)
        {
            huespedes.insert(rg->getHuesped()->getEmail());
        }
    }
    return huespedes;
}
