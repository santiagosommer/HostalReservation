#include "../h/RespuestaEmpleado.h"
#include "../h/Usuario.h"

RespuestaEmpleado::RespuestaEmpleado(string mensaje, Empleado* emp, Calificacion* cali){
    this->mensaje = mensaje;
    this->empleado = emp;
    this->calificacion = cali;
}

string RespuestaEmpleado::getMensaje(){
    return this->mensaje;
}
Empleado* RespuestaEmpleado::getEmpleado(){
    return this->empleado;
}
Calificacion* RespuestaEmpleado::getCalificacion(){
    return this->calificacion;
}

void RespuestaEmpleado::eliminarRespuesta(){
	empleado->eliminarRespuesta(this);
}