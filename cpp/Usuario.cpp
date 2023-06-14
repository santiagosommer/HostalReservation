#include "../h/Usuario.h"
#include "../h/Hostal.h"
#include "../h/Reserva.h"
#include "../h/DTCalificacion.h"
#include "../h/DTUsuario.h"
#include "../h/DTNotificacion.h"
#include "../h/Notificacion.h"

Empleado::Empleado(string nombre, string email, string password, CargoEmpleado cargo)
{
    this->nombre = nombre;
    this->email = email;
    this->password = password;
    this->cargo = cargo;
}

Huesped::Huesped(string nombre, string email, string password, bool esFinger)
{
    this->nombre = nombre;
    this->email = email;
    this->password = password;
    this->esFinger = esFinger;
}

string Usuario::getNombre()
{
    return this->nombre;
}

string Usuario::getPassword(){ 
	return this->password;
}

CargoEmpleado Empleado::getCargoEmpleado(){
    return this->cargo;
}

string Empleado::getHostalDeEmpleado(){
    return this->hostal->getNombreHostal();
}

bool Huesped::getEsFinger(){
    return this->esFinger;
}

string Usuario::getEmail()
{
    return email;
}

void Empleado::notificarCalificacion(Notificacion* noti){
    n.insert(noti);
}

vector<DTCalificacion> Empleado::getCalificacionesSinResponder(){
    return this->hostal->getCalificacionesSinResponder();
}

void Empleado::setRespuestaEmpleado(RespuestaEmpleado* res){
    this->re.insert(res);
}

set<int> Huesped::getCodigosReservas() {
	set<int> res;
    map<int, ReservaIndividual*>::iterator it = r.begin();
	for (; it != r.end(); it++){
		if (it->second->getEstado() == Abierta) {
			res.insert(it->second->getCodigoReserva());
		}
	}

    map<int, ReservaGrupal*>::iterator iter = rg.begin();
    for (; iter != rg.end(); iter++)
    {
        if (iter->second->getEstado() == Abierta) {
			res.insert(iter->second->getCodigoReserva());
		}
    }
	return res;
}

set<Estadia*> Huesped::getEstadiasHuesped(){
    return this->e;
}

void Huesped::addReserva(Reserva* r)
{
    ReservaIndividual* ri = dynamic_cast<ReservaIndividual*>(r);
    if (ri)
    {
	this->r.insert(pair<int, ReservaIndividual*>(ri->getCodigoReserva(), ri));
    }
    else
    {
        ReservaGrupal* rg = dynamic_cast<ReservaGrupal*>(r);
        this->rg.insert(pair<int, ReservaGrupal*>(rg->getCodigoReserva(), rg));
    }
}

void Huesped::agregarEstadia(Estadia* est){
    this->e.emplace(est);
}


DTHuesped Huesped::getDTHuesped(){
    DTHuesped nuevo = DTHuesped(this->getNombre(), this->getEmail(), this->getEsFinger());
    return nuevo;
}

DTEmpleado Empleado::getDTEmpleado(){
    DTEmpleado nuevo = DTEmpleado(this->getNombre(), this->getEmail(), this->getCargoEmpleado(), this->getHostalDeEmpleado());
    return nuevo;
}

vector<DTNotificacion> Empleado::getNotificaciones()
{   
    vector<DTNotificacion> notisADevolver;
    set<Notificacion*>::iterator iter = this->n.begin();
    for(; iter != n.end(); iter = n.begin())
    {
        notisADevolver.emplace_back((*iter)->getDTNotificacion());
        (*iter)->disminuirNumero();
        Notificacion* puntero = *iter;
        n.erase(iter);

        if (puntero->getEmpleadosLinkeados() == 0)
        {
            puntero->~Notificacion();
        }
    }
    return notisADevolver;
}

//baja reserva
void Huesped::eliminarReservaDeHuesped(int codigoReservaEstadia){
    //map<int, ReservaIndividual*>::iterator it;
    //it = r.find(codigoReservaEstadia);
    r.erase(codigoReservaEstadia);

}

void Huesped::eliminarReservaDeHuespedGrupal(int codigoReservaEstadia){
    //map<int, ReservaGrupal*>::iterator it;
    //it = rg.find(codigoReservaEstadia);
    rg.erase(codigoReservaEstadia);
}

void Huesped::eliminarEstadia(Estadia* estadiaEliminar){
    //set<Estadia*>::iterator it;
    //it = e.find(estadiaEliminar);
    //e.erase(it);
    e.erase(estadiaEliminar);
}

void Empleado::eliminarRespuesta(RespuestaEmpleado* RespuestaEliminar){
    //set<RespuestaEmpleado*>::iterator it;
    //it = re.find(RespuestaEliminar);
    //re.erase(it);
    re.erase(RespuestaEliminar);
}
