#include "../h/DTEstadiaPlus.h"

DTEstadiaPlus::DTEstadiaPlus(string nomHos, string nomHues, int numHab, int codRes, Fecha in, Fecha out, int prom){
    nombreHostal = nomHos;
    nombreHuesped = nomHues;
    numeroHabitacion = numHab;
    codigoReserva = codRes;
    checkInReal = in;
    checkOutReal = out;
    promo = prom;
}
const string DTEstadiaPlus::getNombreHostal() const{
    return nombreHostal;
}
const string DTEstadiaPlus::getNombreHuesped() const{
    return nombreHuesped;
}
const int DTEstadiaPlus::getNumeroHabitacion() const{
    return numeroHabitacion;
}
const int DTEstadiaPlus::getCodigoReserva() const{
    return codigoReserva;
}
const Fecha DTEstadiaPlus::getCheckInReal() const{
    return checkInReal;
}
const Fecha DTEstadiaPlus::getCheckOutReal() const{
    return checkOutReal;
}
const int DTEstadiaPlus::getPromo() const{
    return promo;
}