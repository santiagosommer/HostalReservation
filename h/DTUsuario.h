#ifndef DTUSUARIO_
#define DTUSUARIO_

#include <string>
#include "Enum.h"

using namespace std;

class DTUsuario
{
    protected:
        string nombre;
        string email;
    public:

};

class DTHuesped : public DTUsuario
{
    private:
        bool esFinger;
    public:
        DTHuesped(string nombre, string email, bool esFinger);
        const string getNombre() const;
        const string getEmail() const;
        const bool getEsFinger() const;

};

class DTEmpleado : public DTUsuario
{
    private:
        CargoEmpleado cargo;
        string nombreHostal;
    public:
        DTEmpleado(string nombre, string email, CargoEmpleado cargo, string nombreHostal);
        const string getNombre() const;
        const string getEmail() const;
        const CargoEmpleado getCargo() const;
        const string getNombreHostal() const;

};

#endif