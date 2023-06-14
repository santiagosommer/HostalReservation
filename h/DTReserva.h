#ifndef DTRESERVA_
#define DTRESERVA_

#include <string>
#include "Fecha.h"
#include "Enum.h"
#include <set>
#include <iostream>

using namespace std;

class DTReserva
{
private:
    int codigo;
    Fecha checkIn;
    Fecha checkOut;
    EstadoReserva estado;
    int costo;
    int numeroHabitacion;
public:
    int getCodigo();
    Fecha getCheckIn();
    Fecha getCheckOut();
    EstadoReserva getEstado();
    int getCosto();
    int getNumeroHabitacion();
    DTReserva(int codigo, Fecha checkIn, Fecha checkOut, EstadoReserva estado, int costo, int numeroHabitacion);
    void imprimir(){};
};

class DTReservaGrupal : public DTReserva
{
private:
    set<string> nombreHuesped;
public:
    DTReservaGrupal(int codigo, Fecha checkIn, Fecha checkOut, EstadoReserva estado, int costo, int numeroHabitacion, set<string> nombreHuespedes);
    void imprimir();
};

class DTReservaIndividual : public DTReserva
{
private:
    string nombreHuesped;
public:
    DTReservaIndividual(int codigo, Fecha checkIn, Fecha checkOut, EstadoReserva estado, int costo, int numeroHabitacion);
    DTReservaIndividual(int codigo, Fecha checkIn, Fecha checkOut, EstadoReserva estado, int costo, int numeroHabitacion, string nombreHuesped);
    void imprimir();
};

#endif