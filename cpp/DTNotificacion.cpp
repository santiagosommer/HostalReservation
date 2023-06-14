#include "../h/DTNotificacion.h"

DTNotificacion::DTNotificacion(string aut, int pun, string com){
    autor = aut;
    puntaje = pun;
    comentario = com;
}
const string DTNotificacion::getAutor() const{
    return autor;
}
const int DTNotificacion::getPuntaje() const {
    return puntaje;
}
const string DTNotificacion::getComentario() const {
    return comentario;
}