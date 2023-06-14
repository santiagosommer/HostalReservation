#ifndef NOTIFICACION_
#define NOTIFICACION_

#include <map>
#include <string>


using namespace std;

class Calificacion;
class DTNotificacion;

class Notificacion{
    private:
        string autor;
        int empleadosLinkeados;
        Calificacion* calificacion;
    public:
        Notificacion(string, int, Calificacion*);
        string getAutor();
        int getEmpleadosLinkeados();
        Calificacion* getCalificacion();
        DTNotificacion getDTNotificacion();
        void aumentarNumero();
        void disminuirNumero();
};


#endif