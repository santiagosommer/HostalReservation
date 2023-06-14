#include "../h/ControladorHostales.h"
#include "../h/ControladorUsuarios.h"
#include "../h/Hostal.h"
#include "../h/Usuario.h"
#include "../h/DTHostal.h"
#include "../h/Reserva.h"
#include "../h/ControladorReservas.h"
#include "../h/Fecha.h"
#include "../h/DTHabitacion.h"

ControladorHostales* ControladorHostales::instance = NULL;

ControladorHostales* ControladorHostales::getInstance(){
    if (!instance)
    {
        instance = new ControladorHostales();
    }
    return instance;
}

void ControladorHostales::setHostalInfo(string nombre, string direccion, string telefono)
{
    nombreHostal = nombre;
    direccionHostal = direccion;
    telefonoHostal = telefono;
}

void ControladorHostales::confirmarAltaHostal()
{
    Hostal* h = new Hostal(nombreHostal, direccionHostal, telefonoHostal);
    hostales.insert(pair<string,Hostal*>(nombreHostal, h));
}
void ControladorHostales::cancelarAltaHostal()
{
}


//Caso de Uso: Asignar Empleado a Hostal
set<string> ControladorHostales::getEmpleadosFueraDeHostal(string nombreHostal)
{
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    map<string,Empleado*> empleados = cu->getEmpleados();
    Hostal* hostalElegido = hostales.find(nombreHostal)->second;
    map<string, Empleado*> empleadosAEliminar = hostalElegido->getEmpleados();

    map<string, Empleado*>::iterator iter = empleadosAEliminar.begin();
    for (;iter != empleadosAEliminar.end(); iter++)
    {
        empleados.erase(iter->first);
    }
    set<string> empleadosSinHostalSeleccionado;


    map<string, Empleado*>::iterator aux = empleados.begin();
    for (; aux != empleados.end(); aux++)
    {
        empleadosSinHostalSeleccionado.insert(aux->first);
    }
    nombreHostalAAsignar = nombreHostal;

    return empleadosSinHostalSeleccionado;
}

void ControladorHostales::asignarEmpleado(string nombre, CargoEmpleado cargo)
{
    nombreEmpleadoAAsignar = nombre;
    cargoEmpleadoAAsignar = cargo;
}
void ControladorHostales::confirmarAsignacion()
{
    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    Empleado* empleado = cu->getEmpleado(nombreEmpleadoAAsignar);

    Hostal* hostal = hostales.find(nombreHostalAAsignar)->second;

    empleado->setCargo(cargoEmpleadoAAsignar);
    empleado->setHostal(hostal);

    hostal->asignarEmpleado(empleado);

}
void ControladorHostales::cancelarAsignacion()
{
}


//Caso de uso: Realizar Reserva
bool ControladorHostales::existeHostal(string nombreHostal)
{
    return (hostales.find(nombreHostal) != hostales.end());
}


DTHostal ControladorHostales::getDTHostal(){
    map<string, Hostal*>::iterator h = this->hostales.find(this->hostalSeleccionado);
    return h->second->getDataHostal();
}


set<string> ControladorHostales::getHostales(){
    set<string> aRetornar;
    map<string, Hostal*>::iterator it = hostales.begin();
    for (; it != hostales.end(); it++)
    {
        aRetornar.insert(it->first);
    }
    return aRetornar;
}

//Caso de uso: Alta de Habitacion
void ControladorHostales::seleccionarHostal(string nombre){
    this->hostalSeleccionado = nombre;
}

void ControladorHostales::altaHabitacion(int numero, int precio, int capacidad){
    this->numeroHab = numero;
    this->precioHab = precio;
    this->capacidadHab = capacidad;
}
void ControladorHostales::confirmarAltaHabitacion(){
   map<string,Hostal*>::iterator ite = this->hostales.find(this->hostalSeleccionado);
    (*ite).second->nuevaHabitacion(this->numeroHab, this->precioHab, this->capacidadHab, (*ite).second);
}


void ControladorHostales::cancelarAltaHabitacion(){
    ;
}

//Consulta Top 3 Hostales
map<int,string> ControladorHostales::getTop3Hostales(){
    map<int,string> res;
    if (!hostales.empty()){
	    float prom = 0;
	    float prom1 = 0;
	    float prom2 = 0;
	    float prom3 = 0;
	    Hostal* h1 = NULL; 
	    Hostal* h2 = NULL;
	    Hostal* h3 = NULL;
    	for (map<string,Hostal*>::iterator it =  hostales.begin(); it != hostales.end(); it++){
	    	prom = it->second->getPromedioPuntaje();
		    if (prom > prom1){
			    prom3 = prom2;
			    prom2 = prom1;
    			prom1 = prom;
	    		h3 = h2;
		    	h2 = h1;
			    h1 = it->second;
		    }else if (prom > prom2){
		    	prom3 = prom2;
		    	prom2 = prom;
		    	h3 = h2;
		    	h2 = it->second;
		    }else if (prom > prom3){
			    prom3 = prom;
			    h3 = it->second;
	    	}
	    }
        if (h3!=NULL){	
            res.insert(pair<int,string>(3, h3->getNombreHostal()));
        }
        if (h2!=NULL){
	        res.insert(pair<int,string>(2, h2->getNombreHostal()));
        }
        if (h1!=NULL){
            res.insert(pair<int,string>(1, h1->getNombreHostal()));
        }
    } 
    return res;

}
vector<DTCalificacion> ControladorHostales::getDetallesHostal(string nombreHostal){
    map<string,Hostal*>::iterator it = hostales.find(nombreHostal);
	vector<DTCalificacion> res = it->second->getDetalles();
	return res;
}


void ControladorHostales::finalizarConsultaHostal(){}


void ControladorHostales::cancelarReserva(){}
void ControladorHostales::confirmarReserva()
{
    Reserva* r;
    ControladorReservas* cr = ControladorReservas::getInstance();
    
    if (esReservaGrupalReserva)
    {

        r = new ReservaGrupal(cr->getCodigoReservaACrear(), checkInReserva, checkOutReserva, EstadoReserva::Abierta, 0);
    }
    else
    {
        r = new ReservaIndividual(cr->getCodigoReservaACrear(), checkInReserva, checkOutReserva, EstadoReserva::Abierta, 0);
    }
    r->setHuespedes(huespedesAElegir);
    Hostal* hostalAReservar = hostales.find(nombreHostalAReservar)->second;
    hostalAReservar->reservarHabitacion(r,habitacionAReservar);
    r->calcularCosto();
    cr->addReserva(r);
}
set<int> ControladorHostales::getHabitacionesLibres()
{
    Hostal* hostal = hostales.find(nombreHostalAReservar)->second;
    return hostal->getHabitacionesLibres(checkInReserva, checkOutReserva);
}
vector<DTHostal> ControladorHostales::getHostalesPlus()
{
    map<string, Hostal*>::iterator it = hostales.begin();
    vector<DTHostal> listaDTs;
    for (; it != hostales.end(); it++)
    {
        const Hostal& hostal = *(it->second);
        listaDTs.emplace_back(DTHostal(hostal));
    }
    return listaDTs;
}
void ControladorHostales::seleccionarHabitacion(int habitacion)
{
    habitacionAReservar = habitacion;
}
void ControladorHostales::seleccionarHostalParaReserva(string nombreHostal, Fecha checkIn, Fecha checkOut, bool esReservaGrupal)
{
    nombreHostalAReservar = nombreHostal;
    checkInReserva = checkIn;
    checkOutReserva = checkOut;
    esReservaGrupalReserva = esReservaGrupal;
}
void ControladorHostales::seleccionarHuesped(string mailHuesped)
{
    huespedesAElegir.insert(mailHuesped);
}


Hostal* ControladorHostales::getHostal(string nombreHostal){
    return hostales.find(nombreHostal)->second;
}

void ControladorHostales::cargaDatos()
{
    //Hostales
    Hostal* finger = new Hostal("La posada del finger", "Av de la playa 123, Maldonado", "09911111");
    hostales.insert({finger->getNombreHostal(), finger});

    Hostal* mochileros = new Hostal("Mochileros", "Rambla Costanera 333, Rocha", "42579512");
    hostales.insert({mochileros->getNombreHostal(), mochileros});

    Hostal* pony = new Hostal("El Pony Pisador", "Bree (preguntar por Gandalf)", "000");
    hostales.insert({pony->getNombreHostal(), pony});

    Hostal* altos = new Hostal("Altos de Fing", "Av. del Toro 1424", "099892992");
    hostales.insert({altos->getNombreHostal(), altos});

    Hostal* caverna = new Hostal("Caverna Lujosa", "Amaya 2515", "233233235");
    hostales.insert({caverna->getNombreHostal(), caverna});

    finger->nuevaHabitacion(1, 40, 2, finger);
    finger->nuevaHabitacion(2, 10, 7, finger);
    finger->nuevaHabitacion(3, 30, 3, finger);
    finger->nuevaHabitacion(4, 5, 12, finger);
    caverna->nuevaHabitacion(1, 3, 2, caverna);
    pony->nuevaHabitacion(1, 9, 5, pony);

    ControladorUsuarios* cu = ControladorUsuarios::getInstance();
    finger->asignarEmpleado(cu->getEmpleado("emilia@mail.com"));
    cu->getEmpleado("emilia@mail.com")->setHostal(finger);
    mochileros->asignarEmpleado(cu->getEmpleado("leo@mail.com"));
    cu->getEmpleado("leo@mail.com")->setHostal(mochileros);
    mochileros->asignarEmpleado(cu->getEmpleado("alina@mail.com"));
    cu->getEmpleado("alina@mail.com")->setHostal(mochileros);
    pony->asignarEmpleado(cu->getEmpleado("barli@mail.com"));
    cu->getEmpleado("barli@mail.com")->setHostal(pony);

}

bool ControladorHostales::checkearHab(int h){
    return this->hostales.find(this->hostalSeleccionado)->second->checkHab(h);
}

DTHostal ControladorHostales::getDTHostalConsulta(){
    map<string, Hostal*>::iterator h = this->hostales.find(this->hostalSeleccionado);
    return h->second->getDTHostal();
}

set<string> ControladorHostales::getHuespedesConReserva(string nombreHostal)
{
    Hostal* hostal = hostales.find(nombreHostal)->second;
    return hostal->getHuespedesConReserva();
}