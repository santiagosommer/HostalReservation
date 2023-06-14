#include "../h/Notificacion.h"
#include "../h/Calificacion.h"
#include "../h/DTNotificacion.h"

Notificacion::Notificacion(string s, int i, Calificacion* c){
    this->autor = s;
    this->empleadosLinkeados = i;
    this->calificacion = c;
}

string Notificacion::getAutor(){
    return this->autor;
}
int Notificacion::getEmpleadosLinkeados(){
    return this->empleadosLinkeados;
}
Calificacion* Notificacion::getCalificacion(){
    return this->calificacion;
}
DTNotificacion Notificacion::getDTNotificacion(){
    return DTNotificacion(this->autor, this->calificacion->getPuntaje(), this->calificacion->getComentario());
}
void Notificacion::aumentarNumero(){
    this->empleadosLinkeados++;
}
void Notificacion::disminuirNumero(){
    this->empleadosLinkeados--;
}