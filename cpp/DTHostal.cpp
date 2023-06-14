#include "../h/DTHostal.h"
#include "../h/Hostal.h"
#include "../h/DTHabitacion.h"
#include "../h/Habitacion.h"
#include "../h/Reserva.h"
#include "../h/Estadia.h"
#include "../h/DTCalificacion.h"
#include <iostream>

DTHostal::DTHostal(string nom, string dir, string tel, float prom){
    nombre = nom;
    direccion = dir;
    telefono = tel;
    promCalif = prom;
}

DTHostal::DTHostal(string nom, string dir, string tel, float prom, map<int, Habitacion*> habs){
    this->nombre = nom;
    this->direccion = dir;
    this->telefono = tel;
    this->promCalif = prom;
    vector<DTHabitacion> nuevo;

    //getDTHabs
    for (map<int, Habitacion*>::iterator ite = habs.begin(); ite != habs.end(); ite++){

        DTHabitacion h = DTHabitacion(ite->second->getNumero(), ite->second->getPrecio(), ite->second->getCapacidad(), NULL);
        vector<DTCalificacion>* nuevo2 = new vector<DTCalificacion>;
        
        map<int, Reserva*> res = (*ite).second->getReservas();
       

        for (map<int, Reserva*>::iterator ite2 = res.begin(); ite2 != res.end(); ite2++){
            set<Estadia*> est = ite2->second->getEstadias();
            if (!est.empty()){
                
                
                for (set<Estadia*>::iterator ite3 = est.begin(); ite3 != est.end(); ite3++){
                    if ((*ite3)->getCalificacion() != NULL)
                        (*nuevo2).emplace_back((*ite3)->getDTCalificacion());
                }

                h.setCalificaciones(nuevo2);
            }
                // h.setCalificaciones(nuevo2);
               // cout << h.getCalificaciones()->size();
        }nuevo.emplace_back(h);
        
    }
    this->habs = nuevo;
    
}

DTHostal::DTHostal(const Hostal& hostal)
{
    this->nombre = hostal.getNombreHostal();
    this->direccion = hostal.getDireccion();
    this->telefono = hostal.getTelefono();
    this->promCalif = hostal.getPromedioPuntaje();
}

const string DTHostal::getNombre() const{
    return nombre;
}
const string DTHostal::getDireccion() const{
    return direccion;
}
const string DTHostal::getTelefono() const{
    return telefono;
}
const float DTHostal::getPromCalif() const{
    return promCalif;
}

const vector<DTHabitacion> DTHostal::getDTHabs() const{
    return this->habs;
}