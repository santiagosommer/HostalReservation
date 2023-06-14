#ifndef DTESTADIAPLUS_
#define DTESTADIAPLUS_

#include <string>
#include "../h/Fecha.h"

using namespace std;


class DTEstadiaPlus
{
private:
    string nombreHostal;
    string nombreHuesped;
    int numeroHabitacion;
    int codigoReserva;
    Fecha checkInReal;
    Fecha checkOutReal;
    int promo;
public:
    DTEstadiaPlus(string, string, int, int, Fecha, Fecha, int);
    const string getNombreHostal() const;
    const string getNombreHuesped() const;
    const int getNumeroHabitacion() const;
    const int getCodigoReserva() const;
    const Fecha getCheckInReal() const;
    const Fecha getCheckOutReal() const;
    const int getPromo() const;
};

#endif