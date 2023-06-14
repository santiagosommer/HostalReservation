#include "../h/ControladorReservas.h"
#include "../h/ControladorUsuarios.h"
#include "../h/ControladorReloj.h"
#include "../h/ControladorHostales.h"
#include "../h/Reserva.h"
#include "../h/Estadia.h"
#include "../h/Calificacion.h"
#include "../h/DTReserva.h"
#include "../h/Hostal.h"
#include "../h/DTEstadiaPlus.h"
#include "../h/DTCalificacion.h"
#include "../h/DTEstadia.h"
#include "../h/RespuestaEmpleado.h"
#include "../h/Usuario.h"
#include "../h/DTHostal.h"
#include "../h/Habitacion.h"

using namespace std;

ControladorReservas* ControladorReservas::instance = NULL;

ControladorReservas* ControladorReservas::getInstance(){
    if (!instance)
    {
        instance = new ControladorReservas();
    }
    return instance;
}

// Registrar Estadia
void ControladorReservas::registrarEstadia(int codigoReserva, Huesped* hues)
{
	ControladorReloj* cr = ControladorReloj::getInstance();
	Fecha fechaAct = cr->getFechaActual();
	map<int, Reserva*>::iterator it = reservas.find(codigoReserva);
	Reserva* res = it->second;
	int promo = 0;
	res->setCerradaReserva(fechaAct, promo, res, hues);
}

set<string> ControladorReservas::getHostales(){
    ControladorHostales* ch = ControladorHostales::getInstance();
    set<string> res = ch->getHostales(); //Por que no vas directo a controlador hostales para pedir los hostales? 
	return res;
}

void ControladorReservas::seleccionarEstadia(int i, string s){
    codigoReservaEstadia = i;
    emailHuespedEstadia = s;
}

void ControladorReservas::seleccionarEstadiaConHostal(string hostal, string email) {
	this->hostalSeleccionado = hostal;
	this->emailHuespedEstadia = email;
}

void ControladorReservas::finalizarEstadia(){
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
	ControladorReloj* cr = ControladorReloj::getInstance();
	Fecha fechaA = cr->getFechaActual();
	Huesped* h = cu->getHuesped(emailHuespedEstadia); 

    set<Estadia*> estadias = h->getEstadiasHuesped();
    set<Estadia*>::iterator iter;
	for (iter = estadias.begin(); iter != estadias.end(); iter++){
        Estadia* e = *iter;
		if (!(e->estaFinalizada())){
			e->setCheckOut(fechaA);
		}
	}
}
void ControladorReservas::setCalificacion(string comentario, int calificacion){
    map<int, Reserva*>::iterator itr = reservas.find(codigoReservaEstadia);
    Reserva* res = itr->second;
    Estadia* est = res->getEstadia(emailHuespedEstadia);
    ControladorHostales* ch = ControladorHostales::getInstance();
    Hostal* h = ch->getHostal(hostalSeleccionado);
    est->setCalificacion(comentario, calificacion, h);
    Calificacion* c = est->getCalificacion();
    Notificacion* n = c->crearNotificacion(emailHuespedEstadia);
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    cu->notificarObservadores(n);
}
vector<DTCalificacion> ControladorReservas::getCalificacionesSinResponder(string emailEmpleado){
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    vector<DTCalificacion> res = cu->getCalificacionesSinResponder(emailEmpleado);
    empleadoGuardado = cu->getEmpleado(emailEmpleado);
    return res;
}
void ControladorReservas::setComentarioCalificacion(string comentario){
    Reserva* res = reservas.find(codigoReservaEstadia)->second;
    Estadia* est = res->getEstadia(emailHuespedEstadia);
    Calificacion* cal = est->getCalificacion();
    cal->setComentarioCalificacion(comentario, empleadoGuardado, cal);
}
void ControladorReservas::selectCalificacion(string email, int codigo){
    codigoReservaEstadia = codigo;
    emailHuespedEstadia = email;
}
vector<DTEstadia> ControladorReservas::getEstadias(){
    ControladorHostales* ch = ControladorHostales::getInstance();
    Hostal* h = ch->getHostal(hostalSeleccionado);
    return h->getDTEstadias();
}
DTEstadiaPlus ControladorReservas::getEstadiaPlus(){
    Estadia* est = reservas.find(codigoReservaEstadia)->second->getEstadia(emailHuespedEstadia);
    DTEstadiaPlus res = est->getDTEstadiaPlus();
    return res;
}
DTReserva ControladorReservas::getDTReserva(){
    Estadia* est = reservas.find(codigoReservaEstadia)->second->getEstadia(emailHuespedEstadia);
    DTReserva res = est->getDTReserva();
    return res;
}
DTCalificacion ControladorReservas::getDTCalificacion(){
    Estadia* est = reservas.find(codigoReservaEstadia)->second->getEstadia(emailHuespedEstadia);
    DTCalificacion res = est->getDTCalificacion();
    return res;
}
void ControladorReservas::seleccionarHostal(string h){
    hostalSeleccionado = h;
}
vector<DTEstadia> ControladorReservas::getEstadiasFinalizadas(string emailHuesped){
    ControladorHostales* ch = ControladorHostales::getInstance();
    Hostal* h = ch->getHostal(hostalSeleccionado);
    vector<DTEstadia> res = h->getEstadiasFinalizadas(emailHuesped);
    return res;
}
void ControladorReservas::finConsultaEstadia(){

}

void ControladorReservas::addReserva(Reserva* r)
{
	reservas.insert(pair<int, Reserva*>(r->getCodigoReserva(), r));
}

int ControladorReservas::getCodigoReservaACrear()
{
    int codigo = sigCodigoReserva;
    sigCodigoReserva++;
    return codigo;
}

bool ControladorReservas::existeCalificacion(){
    Estadia* est = reservas.find(codigoReservaEstadia)->second->getEstadia(emailHuespedEstadia);
    return est->getCalificacion() != NULL;
}

bool ControladorReservas::existeRespuestaEmpleado(){
    Estadia* est = reservas.find(codigoReservaEstadia)->second->getEstadia(emailHuespedEstadia);
    bool existe = false;
    if (est->getCalificacion() != NULL){
        if (est->getCalificacion()->getRespuestaempleados() != NULL){
            existe = true;
        }
    }
    return existe;
}

string ControladorReservas::getRespuestaEmpleado(){
    Estadia* est = reservas.find(codigoReservaEstadia)->second->getEstadia(emailHuespedEstadia);
    return est->getCalificacion()->getRespuestaempleados()->getMensaje();
}

void ControladorReservas::cargaDatos()
{
    ControladorHostales* ch = ControladorHostales::getInstance();
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();


    //R1
    Hostal* finger = ch->getHostal("La posada del finger");
    Habitacion* habFinger = finger->getHabitacion(1);
    Reserva* r = new ReservaIndividual(1, Fecha(14.00, 1, 5, 2022), Fecha(10.00, 10, 5, 2022), EstadoReserva::Abierta, habFinger);
    set<string> huespedes;
    huespedes.insert("sofia@mail.com");
    Huesped* huesSofia = cu->getHuesped("sofia@mail.com");
    r->setHuespedes(huespedes);
    finger->reservarHabitacion(r, 1);
    this->addReserva(r);
    //crear Estadia
    Estadia* estSofia = new Estadia(Fecha(18.00, 1, 5, 2022), Fecha(9.00, 10, 5, 2022), 0, r, huesSofia, NULL);
    r->setEstadia(estSofia);
    huesSofia->agregarEstadia(estSofia);
    //crear Calificacion Estadia
    Calificacion* calSofia = new Calificacion(3, "Un poco caro para lo que ofrecen. El famoso gimnasio era una caminadora (que hacía tremendo ruido) y 2 pesas, la piscina parecía el lago del Parque Rodó y el desayuno eran 2 tostadas con mermelada. Internet se pasaba cayendo. No vuelvo.", Fecha(18.00, 11, 5, 2022), estSofia, finger, NULL);
    estSofia->setPunteroCalificacion(calSofia);
    finger->agregarCalificacion(calSofia);


    //R2
    Hostal* pony = ch->getHostal("El Pony Pisador");
    Habitacion* habPony = pony->getHabitacion(1);
    Reserva* re = new ReservaGrupal(2, Fecha(20.00,4,1,2001), Fecha(2.00, 5,1,2001), EstadoReserva::Abierta, habPony);
    set<string> huespedesPony;
    huespedesPony.insert("frodo@mail.com");
    Huesped* huesFrodo = cu->getHuesped("frodo@mail.com");
    huespedesPony.insert("sam@mail.com");
    Huesped* huesSam = cu->getHuesped("sam@mail.com");
    huespedesPony.insert("merry@mail.com");
    Huesped* huesMerry = cu->getHuesped("merry@mail.com");
    huespedesPony.insert("pippin@mail.com");
    Huesped* huesPippin = cu->getHuesped("pippin@mail.com");
    re->setHuespedes(huespedesPony);
    pony->reservarHabitacion(re, 1);
    this->addReserva(re);
    //crear Estadias
    Estadia* estFrodo = new Estadia(Fecha(21.00, 4, 1, 2001), Fecha(2.00, 5, 1, 2001), 0, re, huesFrodo, NULL);
    re->setEstadia(estFrodo);
    huesFrodo->agregarEstadia(estFrodo);
    Estadia* estSam = new Estadia(Fecha(21.00, 4, 1, 2001), Fecha(), 0, re, huesSam, NULL);
    re->setEstadia(estSam);
    huesSam->agregarEstadia(estSam);
    Estadia* estMerry = new Estadia(Fecha(21.00, 4, 1, 2001), Fecha(), 0, re, huesMerry, NULL);
    re->setEstadia(estMerry);
    huesMerry->agregarEstadia(estMerry);
    Estadia* estPippin = new Estadia(Fecha(21.00, 4, 1, 2001), Fecha(), 0, re, huesPippin, NULL);
    re->setEstadia(estPippin);
    huesPippin->agregarEstadia(estPippin);
    //crear Calificacion Estadia
    Calificacion* calFrodo = new Calificacion(2, "Se pone peligroso de noche, no recomiendo. Además no hay caja fuerte para guardar anillos.", Fecha(3.00, 5, 1, 2001), estFrodo, pony, NULL);
    estFrodo->setPunteroCalificacion(calFrodo);
    pony->agregarCalificacion(calFrodo);
    //crear Comentario a Calificacion
    Empleado* empl = cu->getEmpleado("barli@mail.com");
    calFrodo->setComentarioCalificacion("Desapareció y se fue sin pagar.", empl, calFrodo);


    //R3
    Habitacion* habFingerDos = finger->getHabitacion(3);
    Reserva* res = new ReservaIndividual(3, Fecha(14.00, 7,6,2022), Fecha(11.00,30,6,2022), EstadoReserva::Abierta, habFingerDos);
    set<string> huespedesFingerDos;
    huespedesFingerDos.insert("sofia@mail.com");
    res->setHuespedes(huespedesFingerDos);    
    finger->reservarHabitacion(res, 3);
    this->addReserva(res);


    //R4
    Hostal* caverna = ch->getHostal("Caverna Lujosa");
    Habitacion* habCaverna = caverna->getHabitacion(1);
    Reserva* rese = new ReservaIndividual(4, Fecha(14.00, 10, 6, 2022), Fecha(11.00, 30, 6, 2022), EstadoReserva::Abierta, habCaverna);
    set<string> huespedesCaverna;
    huespedesCaverna.insert("seba@mail.com");
    Huesped* huesSeba = cu->getHuesped("seba@mail.com");
    rese->setHuespedes(huespedesCaverna);
    caverna->reservarHabitacion(rese, 1);
    this->addReserva(rese);
    //crear Estadia
    Estadia* estSeba = new Estadia(Fecha(6.00, 7, 6, 2022), Fecha(22.00, 15, 6, 2022), 0, rese, huesSeba, NULL);
    rese->setEstadia(estSeba);
    huesSeba->agregarEstadia(estSeba);
    //crear Calificacion Estadia
    Calificacion* calSeba = new Calificacion(1, "Había pulgas en la habitación. Que lugar más mamarracho!!", Fecha(23.00, 15, 6, 2022), estSeba, caverna, NULL);
    estSeba->setPunteroCalificacion(calSeba);
    caverna->agregarCalificacion(calSeba);

}
//consulta reserva
vector<DTReserva> ControladorReservas::listarReservasDeHostal(string nombreHostal){
    ControladorHostales* ch = ControladorHostales::getInstance();
    Hostal* h = ch->getHostal(nombreHostal);
    vector<DTReserva> res = h->listarReservasDeHostal();
    return res;
}
//baja reserva
set<int> ControladorReservas::listarCodigoReservasDeHostal(string nombreHostal){
    ControladorHostales* ch = ControladorHostales::getInstance();
    Hostal* h = ch->getHostal(nombreHostal);
    set<int> res = h->listarCodigoReservasDeHostal();
    return res;
}

void ControladorReservas::confirmarBajaReserva(){
    //acordarse de eliminar la instancia de reserva
    map<int, Reserva*>::iterator it;
    //hacer una variable codigoreserva especifica para esto?
    it = reservas.find(codigoReservaEstadia);
    it->second->eliminarReservaDeHabitacion(codigoReservaEstadia);
    it->second->~Reserva();
    reservas.erase(codigoReservaEstadia);
}

void ControladorReservas::seleccionarReserva(int codigo){
    codigoReservaEstadia = codigo;
}

vector<DTReservaIndividual> ControladorReservas::getReservasIndividuales(vector<DTReserva> reservasInd)
{
    vector<DTReservaIndividual> ret;
    vector<DTReserva>::iterator retIt = reservasInd.begin();
    for(; retIt != reservasInd.end(); retIt++)
    {
        Reserva* r = reservas.find(retIt->getCodigo())->second;
        if (r)
        {
            if(dynamic_cast<ReservaIndividual*>(r))
            {
                ret.emplace_back(DTReservaIndividual(r->getCodigoReserva(), r->getCheckIn(), r->getCheckOut(), r->getEstado(), r->getCosto(), r->getHabitacion()->getNumero(), r->getHuesped()->getEmail())); 
            }
        }
    }
    return ret;
}

vector<DTReservaGrupal> ControladorReservas::getReservasGrupales(vector<DTReserva> reservasGrup)
{
    vector<DTReservaGrupal> ret;
    vector<DTReserva>::iterator retIt = reservasGrup.begin();
    for(; retIt != reservasGrup.end(); retIt++)
    {
        Reserva* r = reservas.find(retIt->getCodigo())->second;
        if (r)
        {
            ReservaGrupal* rg = dynamic_cast<ReservaGrupal*>(r);
            if(rg)
            {
                ret.emplace_back(DTReservaGrupal(rg->getCodigoReserva(), rg->getCheckIn(), rg->getCheckOut(), rg->getEstado(), rg->getCosto(), rg->getHabitacion()->getNumero(), rg->getHuespedes())); 
            }
        }
    }
    return ret;
}
