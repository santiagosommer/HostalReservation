#ifndef DTHOSTAL_
#define DTHOSTAL_

#include <string>
#include <vector>
#include <map>

using namespace std;
class Hostal;
class DTHabitacion;
class Habitacion;

class DTHostal
{
    private:
        string nombre;
        string direccion;
        string telefono;
        float promCalif;
        vector<DTHabitacion> habs;
    public:
        DTHostal(string nombre, string direccion, string telefono, float promCalif);
        DTHostal(string, string, string, float, map<int,Habitacion*>);
        DTHostal(const Hostal& hostal);
        const string getNombre() const;
        const string getDireccion() const;
        const string getTelefono() const;
        const float getPromCalif() const;
        const vector<DTHabitacion> getDTHabs() const;
};

#endif