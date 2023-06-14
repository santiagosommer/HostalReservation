#include "../h/ControladorReloj.h"

ControladorReloj* ControladorReloj::instance = NULL;

ControladorReloj* ControladorReloj::getInstance()
{
    if (!instance)
    {
        instance = new ControladorReloj();
    }
    return instance;
}

void ControladorReloj::modificarFecha(float hora, int dia, int mes, int anio)
{
    this->fechaActual = Fecha(hora, dia, mes, anio);
}

Fecha ControladorReloj::getFechaActual(){
    return fechaActual;
}

void ControladorReloj::cargaDatos()
{
    this->fechaActual = Fecha(12.00, 20, 4, 2000);
}