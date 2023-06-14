#ifndef DTESTADIA_
#define DTESTADIA_

#include <string>
#include "Fecha.h"

using namespace std;

class DTEstadia
{
private:
    string emailHuesped;
    int codigoReserva;
    Fecha checkInReal;
    Fecha checkOutReal;
    int promo;
public:
    DTEstadia(string, int, Fecha, Fecha, int);
    const string getEmailHuesped() const ;
    const int getCodigoReserva() const ;
    const Fecha getCheckInReal() const ;
    const Fecha getCheckOutReal() const ;
    const int getPromo() const;
};

#endif