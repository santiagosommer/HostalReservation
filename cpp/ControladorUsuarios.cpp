#include "../h/ControladorUsuarios.h"
#include "../h/ControladorHostales.h"
#include "../h/Usuario.h"
#include "../h/ControladorReservas.h"
#include "../h/DTUsuario.h"
#include "../h/DTNotificacion.h"

ControladorUsuarios* ControladorUsuarios::instance = NULL;

ControladorUsuarios* ControladorUsuarios::getInstance()
{
    if (!instance)
    {
        instance = new ControladorUsuarios();
    }
    return instance;
}

void ControladorUsuarios::setUserInfo(string nombre, string email, string password)
{
    nombreUsuario = nombre;
    emailUsuario = email;
    passwordUsuario = password;
}

void ControladorUsuarios::esEmpleado(bool status)
{
    esEmpleadoUsuario = status;
}
void ControladorUsuarios::esFinger(bool status)
{
    esFingerUsuario = status;
}
void ControladorUsuarios::setCargoEmpleado(CargoEmpleado cargo)
{
    cargoUsuario = cargo;
}

bool ControladorUsuarios::esUsuarioRepetido()
{
    return (usuarios.find(emailUsuario) != usuarios.end());
}

void ControladorUsuarios::reingresarDatos()
{
}
void ControladorUsuarios::cancelarAltaUsuario()
{
}

void ControladorUsuarios::confirmarAltaUsuario()
{
    Usuario* user;
    if (esEmpleadoUsuario)
    {
        Empleado* empleado = new Empleado(nombreUsuario, emailUsuario, passwordUsuario, cargoUsuario);
	    empleados.insert({emailUsuario, empleado});
        user = empleado;
    }
    else
    {
        Huesped* huesped = new Huesped(nombreUsuario, emailUsuario, passwordUsuario, esFingerUsuario);
	    huespedes.insert({emailUsuario, huesped});
        user = huesped;
    }
	usuarios.insert(pair<string,Usuario*>(emailUsuario, user));
}

Empleado* ControladorUsuarios::getEmpleado(string emailUsuario)
{
    return empleados.find(emailUsuario)->second;
}

set<string> ControladorUsuarios::getHuespedes()
{
    set<string> listaHuespedes;
    map<string, Huesped*>::iterator it = huespedes.begin();
    for (; it != huespedes.end(); it++)
    {
        listaHuespedes.insert(it->second->getEmail());
    }
    return listaHuespedes;
}

Huesped* ControladorUsuarios::getHuesped(string emailUsuario)
{
    return huespedes.find(emailUsuario)->second;
}

set<string> ControladorUsuarios::getUsuarios()
{
    map<string,Usuario*>::iterator it = usuarios.begin();
    set<string> mails;
    for (; it != usuarios.end(); it++)
    {
        mails.insert(it->second->getEmail());
    }
    return mails;
}

void ControladorUsuarios::seleccionarUsuario(string u){
    this->usuarioSeleccionado = u;
}

//Registrar Estadia
set<string> ControladorUsuarios::getHostales(){
	set<string> res = ControladorHostales::getInstance()->getHostales();
	return res;
}
void ControladorUsuarios::seleccionarHostal(string nombreHostal){
	this->nombreHostal = nombreHostal;
} 
set<int> ControladorUsuarios::getReservasDelHuesped(string emailHuesped) {
	this->emailHuesped = emailHuesped;
	map<string,Huesped*>::iterator it = huespedes.find(emailHuesped); 
	set<int> res = it->second->getCodigosReservas();
	return res;
}

void ControladorUsuarios::seleccionarReserva(int codigoReserva){
	this->codigoReserva = codigoReserva;
} 

void ControladorUsuarios::registrarEstadia(){
	Huesped* hues = huespedes.find(this->emailHuesped)->second;
    ControladorReservas* cr = ControladorReservas::getInstance();
	cr->registrarEstadia(this->codigoReserva, hues); //mandar la funcion de controldorReservas
}

void ControladorUsuarios::finalizarConsultaUsuario(){}
void ControladorUsuarios::eliminarEmpleado()
{
    set<Empleado*>::iterator observer = observers.begin();
    while ((observer != observers.end()) && ((*observer)->getEmail() != emailEmpleadoASuscribir))
    {
        observer++;
    }
    if (observer != observers.end())
            observers.erase(observer);
}

vector<DTNotificacion> ControladorUsuarios::listaNotificaciones()
{
    Empleado* e = empleados.find(emailEmpleadoASuscribir)->second;
    return e->getNotificaciones();
}
void ControladorUsuarios::finalizarConsultaNotis(){}
void ControladorUsuarios::finalizarEliminacion(){}

vector<DTCalificacion> ControladorUsuarios::getCalificacionesSinResponder(string emailEmpleado){
    Empleado e = *empleados.find(emailEmpleado)->second;
    vector<DTCalificacion> res = e.getCalificacionesSinResponder();
    return res;
}


map<string,Empleado*> ControladorUsuarios::getEmpleados()
{
    return empleados;
}


void ControladorUsuarios::notificarObservadores(Notificacion* n)
{
    set<Empleado*>::iterator it = observers.begin();
    for (; it != observers.end(); it++)
    {
        (*it)->notificarCalificacion(n);
    }
}

map<string, string> ControladorUsuarios::getListaEmpleados()
{
    map<string, string> listaEmpleados;
    map<string, Empleado*>::iterator it = empleados.begin();
    for (; it != empleados.end(); it++)
    {
        listaEmpleados.insert({it->first, it->second->getNombre()});
    }
    return listaEmpleados;
}

void ControladorUsuarios::seleccionarEmpleado(string email)
{
    emailEmpleadoASuscribir = email;
}
void ControladorUsuarios::suscribirEmpleado()
{
    observers.insert(empleados.find(emailEmpleadoASuscribir)->second);
}
void ControladorUsuarios::finalizarSuscripcion()
{

}

bool ControladorUsuarios::esEmp(){
    return (this->empleados.find(this->usuarioSeleccionado) != this->empleados.end());
}

DTEmpleado ControladorUsuarios::getDTEmpleado(){
    map<string,Empleado*>::iterator ite = this->empleados.find(this->usuarioSeleccionado);
    return (*ite).second->getDTEmpleado();
}

DTHuesped ControladorUsuarios::getDTHuesped(){
    map<string,Huesped*>::iterator ite = this->huespedes.find(this->usuarioSeleccionado);
    return (*ite).second->getDTHuesped();
}

void ControladorUsuarios::cargaDatos()
{
    //Empleados
    Empleado* emilia = new Empleado("Emilia", "emilia@mail.com", "123", CargoEmpleado::Recepcion);
    empleados.insert({emilia->getEmail(), emilia});
    usuarios.insert({emilia->getEmail(), emilia});

    Empleado* leonardo = new Empleado("Leonardo", "leo@mail.com", "123", CargoEmpleado::Recepcion);
    empleados.insert({leonardo->getEmail(), leonardo});
    usuarios.insert({leonardo->getEmail(), leonardo});

    Empleado* alina = new Empleado("Alina", "alina@mail.com", "123", CargoEmpleado::Administracion);
    empleados.insert({alina->getEmail(), alina});
    usuarios.insert({alina->getEmail(), alina});

    Empleado* barliman = new Empleado("Barliman", "barli@mail.com", "123", CargoEmpleado::Recepcion);
    empleados.insert({barliman->getEmail(), barliman});
    usuarios.insert({barliman->getEmail(), barliman});


    //Huesped

    Huesped* sofia = new Huesped("Sofia", "sofia@mail.com", "123", true);
    huespedes.insert({sofia->getEmail(), sofia});
    usuarios.insert({sofia->getEmail(), sofia});

    Huesped* frodo = new Huesped("Frodo", "frodo@mail.com", "123", true);
    huespedes.insert({frodo->getEmail(), frodo});
    usuarios.insert({frodo->getEmail(), frodo});

    Huesped* sam = new Huesped("Sam", "sam@mail.com", "123", false);
    huespedes.insert({sam->getEmail(), sam});
    usuarios.insert({sam->getEmail(), sam});

    Huesped* merry = new Huesped("Merry", "merry@mail.com", "123", false);
    huespedes.insert({merry->getEmail(), merry});
    usuarios.insert({merry->getEmail(), merry});

    Huesped* pippin = new Huesped("Pippin", "pippin@mail.com", "123", false);
    huespedes.insert({pippin->getEmail(), pippin});
    usuarios.insert({pippin->getEmail(), pippin});

    Huesped* seba = new Huesped("Seba", "seba@mail.com", "123", true);
    huespedes.insert({seba->getEmail(), seba});
    usuarios.insert({seba->getEmail(), seba});
}