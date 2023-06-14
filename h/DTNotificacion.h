#ifndef DTNOTIFICACION_
#define DTNOTIFICACION_

#include <string>

using namespace std;

class DTNotificacion{
    private:
        string autor;
        int puntaje;
        string comentario;
    public:
        DTNotificacion(string, int, string);
        const string getAutor() const;
        const int getPuntaje() const;
        const string getComentario() const;
};

#endif