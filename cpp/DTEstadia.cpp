#include "../h/DTEstadia.h"

DTEstadia::DTEstadia(string em, int cod, Fecha in, Fecha out, int pro){
    emailHuesped = em;
    codigoReserva = cod;
    checkInReal = in;
    checkOutReal = out;
    promo = pro;
}
const string DTEstadia::getEmailHuesped() const{
    return emailHuesped;
}
const int DTEstadia::getCodigoReserva() const{
    return codigoReserva;
}
const Fecha DTEstadia::getCheckInReal() const{
    return checkInReal;
}
const Fecha DTEstadia::getCheckOutReal() const{
    return checkOutReal;
}
const int DTEstadia::getPromo() const{
    return promo;
}