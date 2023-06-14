#include "../h/Hostal.h"
#include "../h/DTHostal.h"
#include "../h/Calificacion.h"
#include "../h/Habitacion.h"
#include "../h/Usuario.h"
#include "../h/DTCalificacion.h"
#include "../h/DTEstadia.h"
#include "../h/DTHabitacion.h"
#include "../h/DTReserva.h"

Hostal::Hostal(){
}

Hostal::Hostal(string nombreHostal, string direccion, string telefono)
{
    this->nombreHostal = nombreHostal;
    this->direccion = direccion;
    this->telefono = telefono;
}

Hostal::Hostal(string nombreHostal, string direccion, string telefono, map<int, Habitacion*> habitaciones, set<Calificacion*> calificaciones, map<string, Empleado*> empleados){
	this->nombreHostal = nombreHostal;
	this->direccion = direccion;
	this->telefono = telefono;
	this->habitaciones = habitaciones;
	this->calificaciones = calificaciones;
	this->empleados = empleados;
}

const string Hostal::getNombreHostal() const{
    return this->nombreHostal;
}

const string Hostal::getDireccion() const{
    return this->direccion;
}

const string Hostal::getTelefono() const {
    return this->telefono;
}

map<int, Habitacion*> Hostal::getHabitaciones(){
    return this->habitaciones;
}

set<Calificacion*> Hostal::getCalificaciones(){
    return this->calificaciones;
}

map<string, Empleado*> Hostal::getEmpleados(){
    return this->empleados;
}

void Hostal::agregarCalificacion(Calificacion* c){
    this->calificaciones.insert(c);
}

const float Hostal::getPromedioPuntaje() const{
    float sum = 0;
	float iteraciones = 0;
    set<Calificacion*>::iterator iter;
	for(iter = this->calificaciones.begin(); iter != this->calificaciones.end(); iter++ ) {
		sum = sum + (*iter)->getPuntaje();
		iteraciones++;
	}
	if (iteraciones == 0){
        return 0;
    }else{
	    return sum/iteraciones;
    }
}

 
vector<DTCalificacion> Hostal::getDetalles(){
	vector<DTCalificacion> res;
    set<Calificacion*> calif = this->getCalificaciones(); 
    set<Calificacion*>::iterator iter;
	for (iter = calif.begin(); iter != calif.end(); iter++){
		DTCalificacion nuevo = DTCalificacion((*iter)->getPuntaje(), (*iter)->getComentario() /*TEMPORAL"temporal", 0*/);
		res.emplace_back(nuevo); 
	}
	return res;
}

void Hostal::nuevaHabitacion(int numero, int precio, int capacidad, Hostal* h){
    Habitacion* nueva = new Habitacion(numero, precio, capacidad, h);
    this->habitaciones.insert(pair<int,Habitacion*>(numero, nueva));

}

DTHostal Hostal::getDataHostal()
{
    int promedio = getPromedioPuntaje();
    return DTHostal(nombreHostal, direccion, telefono, promedio);
}

vector<DTEstadia> Hostal::getEstadiasFinalizadas(string emailHuesped){
    map<int, Habitacion*> hs = this->getHabitaciones();
    map<int, Habitacion*>::iterator itr;
    vector<DTEstadia> res;
    for (itr = hs.begin(); itr != hs.end(); ++itr) {
        vector<DTEstadia> aux = itr->second->getEstadiasFinalizadas(emailHuesped);
        // agregar aux a res
        vector<DTEstadia>::iterator itr2;
        for (itr2 = aux.begin(); itr2 != aux.end(); ++itr2){
            res.emplace_back(*itr2);
        }
    }
    return res;
}

vector<DTCalificacion> Hostal::getCalificacionesSinResponder(){
    // set<Calificacion*> cals = this->calificaciones;
    set<Calificacion*>::iterator itr;
    vector<DTCalificacion> res;
    for (itr = calificaciones.begin(); itr != calificaciones.end(); itr++) {
        Calificacion* aux = *itr;
        if (aux->noEstaRespuesta()){
            res.emplace_back(aux->getDTCalificacion());
        }
    }
    return res;
}

vector<DTEstadia> Hostal::getDTEstadias(){
    map<int, Habitacion*>::iterator itr;
    vector<DTEstadia> res;
    map<int, Habitacion*> aux = this->getHabitaciones();
    for (itr = aux.begin(); itr != aux.end(); itr++) {
        vector<DTEstadia> aux2 = itr->second->getDTEstadias();
        vector<DTEstadia>::iterator itr2;
        for (itr2 = aux2.begin(); itr2 != aux2.end(); itr2++){
            res.emplace_back(*itr2);
        }
    }
    return res;
}

void Hostal::asignarEmpleado(Empleado* empleado)
{
	empleados.insert(pair<string, Empleado*>(empleado->getEmail(), empleado));
}

void Hostal::reservarHabitacion(Reserva* reserva, int habitacion)
{
    Habitacion* habitacionAReservar = habitaciones.find(habitacion)->second;

    habitacionAReservar->addReserva(reserva);

}

set<int> Hostal::getHabitacionesLibres(Fecha CheckIn, Fecha CheckOut)
{
    set<int> habitacionesLibres;
    map<int,Habitacion*>::iterator it = habitaciones.begin();
    for (; it != habitaciones.end(); it++)
    {
        if (!(it->second->isReservado(CheckIn, CheckOut))) 
            habitacionesLibres.insert(it->second->getNumero());
    }
    return habitacionesLibres;
}

Habitacion* Hostal::getHabitacion(int num)
{
    return habitaciones.find(num)->second;
}

bool Hostal::checkHab(int h){
    return this->habitaciones.find(h) != this->habitaciones.end();
}

//consultar reserva
vector<DTReserva> Hostal::listarReservasDeHostal(){
    map<int, Habitacion*> hs = this->getHabitaciones();
    map<int, Habitacion*>::iterator itr;
    vector<DTReserva> res;
    for (itr = hs.begin(); itr != hs.end(); ++itr) {
        vector<DTReserva> aux = itr->second->getDataReservaDeHabitacion();
        vector<DTReserva>::iterator itr2;
        for (itr2 = aux.begin(); itr2 != aux.end(); ++itr2){
            res.emplace_back(*itr2);
        }
    }
    return res;
}

//baja reserva
set<int> Hostal::listarCodigoReservasDeHostal(){
    map<int, Habitacion*> hs = this->getHabitaciones();
    map<int, Habitacion*>::iterator itr;
    set<int> res;
    for (itr = hs.begin(); itr != hs.end(); ++itr) {
        set<int> aux = itr->second->listarCodigoReservasDeHabitacion();
        set<int>::iterator itr2;
        for (itr2 = aux.begin(); itr2 != aux.end(); ++itr2){
            res.insert(*itr2);
        }
    }
    return res;
}

void Hostal::eliminarCalificacion(Calificacion* calificacionEliminar){
    set<Calificacion*>::iterator it;
    it = calificaciones.find(calificacionEliminar);
    calificaciones.erase(it);
}

DTHostal Hostal::getDTHostal(){
    DTHostal nuevo = DTHostal(this->nombreHostal, this->direccion, this->telefono, this->getPromedioPuntaje(), this->habitaciones);
    return nuevo;
}

set<string> Hostal::getHuespedesConReserva()
{
    map<int, Habitacion*> habs = habitaciones;
    map<int, Habitacion*>::iterator itHabs = habs.begin();
    set<string> resultado;

    for (; itHabs != habs.end(); itHabs++)
    {
        set<string> allHuespedes = itHabs->second->getAllHuespedes();
        set<string>::iterator allIt = allHuespedes.begin();
        for(; allIt != allHuespedes.end(); allIt++)
        {
            resultado.insert(*allIt);
        }
    }

    return resultado;
}