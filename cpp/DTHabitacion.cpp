#include "../h/DTHabitacion.h"
#include <vector>

DTHabitacion::DTHabitacion(int num, int pre, int cap, vector<DTCalificacion>* cals){
    numero = num;
    precio = pre;
    capacidad = cap;
    calificaciones = cals;
}
 const int DTHabitacion::getNumero() const {
    return numero;
}
 const int DTHabitacion::getPrecio() const {
    return precio;
}
 const int DTHabitacion::getCapacidad() const {
    return capacidad;
}
 const vector<DTCalificacion>* DTHabitacion::getCalificaciones() const {
    return calificaciones;
}

void DTHabitacion::setCalificaciones(vector<DTCalificacion>* cal){
    this->calificaciones = cal;
}