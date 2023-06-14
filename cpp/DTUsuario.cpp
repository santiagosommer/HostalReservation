#include "../h/DTUsuario.h"

using namespace std;

DTHuesped::DTHuesped(string nombre, string email, bool esFinger)
{
    this->nombre = nombre;
    this->email = email;
    this->esFinger = esFinger;
}

DTEmpleado::DTEmpleado(string nombre, string email, CargoEmpleado cargo, string nombreHostal)
{
    this->nombre = nombre;
    this->email = email;
    this->cargo = cargo;
    this->nombreHostal = nombreHostal;
}

const string DTEmpleado::getNombre() const{
    return this->nombre;
}
const string DTEmpleado::getEmail() const{
    return this->email;
}
const CargoEmpleado DTEmpleado::getCargo() const{
return this->cargo;
}

const string DTEmpleado::getNombreHostal() const{
    return this->nombreHostal;
}

const string DTHuesped::getNombre() const{
    return this->nombre;
}
const string DTHuesped::getEmail() const{
    return this->email;
}
const bool DTHuesped::getEsFinger() const{
    return this->esFinger;
}