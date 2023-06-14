#ifndef DTCALIFICACION_
#define DTCALIFICACION_

#include <string>
#include "Fecha.h"

using namespace std;

class DTCalificacion{
    private:
        int puntaje;
        string comentario;
        Fecha fecha;
        string emailHuesp;
        int codigoReserva;
    public:
        DTCalificacion(int, string, Fecha, string, int);
        DTCalificacion(int, string, string, int);
        DTCalificacion(int, string);
        const int getPuntaje() const;
        const string getComentario() const;
        const Fecha getFecha() const;
        const string getEmailHuesp() const;
        const int getCodigoReserva() const;
};

#endif