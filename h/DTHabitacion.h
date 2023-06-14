#ifndef DTHABITACION_
#define DTHABITACION_

#include <string>
#include <map>
#include <vector>


using namespace std;

class DTCalificacion;

class DTHabitacion{
    private:
        int numero;
        int precio;
        int capacidad;
        vector<DTCalificacion> *calificaciones;
    public:
        DTHabitacion(int, int, int, vector<DTCalificacion>*);
        const int getNumero() const;
        const int getPrecio() const;
        const int getCapacidad() const;
        const vector<DTCalificacion>* getCalificaciones() const;
        void setCalificaciones(vector<DTCalificacion>*);
};

#endif