#ifndef IUSUARIOS_
#define IUSUARIOS_

#include <string>
#include <map>
#include <set>
#include <vector>
#include "Enum.h"

using namespace std;

class DTUsuario;
class DTNotificacion;
class DTCalificacion;
class DTEmpleado;
class DTHuesped;


class IUsuarios{
	public:
		// Caso de Uso: Alta de Usuario
		virtual void setUserInfo(string nombre, string email, string password) = 0;
		virtual void esEmpleado(bool esEmpleado) = 0;
		virtual void setCargoEmpleado(CargoEmpleado cargo) = 0;
		virtual void esFinger(bool esFinger) = 0;
		virtual bool esUsuarioRepetido() = 0;
		virtual void reingresarDatos() = 0;
		virtual void cancelarAltaUsuario() = 0;
		virtual void confirmarAltaUsuario() = 0; 

		//Caso de Uso: Consulta de Usuario
		virtual bool esEmp() = 0;
		virtual DTEmpleado getDTEmpleado() = 0;
		virtual DTHuesped getDTHuesped() = 0;

		virtual set<string> getHuespedes() = 0;

		virtual set<string> getUsuarios() = 0;
		virtual void seleccionarUsuario(string) = 0;
		virtual set<int> getReservasDelHuesped(string) = 0;
		virtual void seleccionarReserva(int) = 0;
		virtual void registrarEstadia() = 0;
		virtual void finalizarConsultaUsuario() = 0;
		virtual void suscribirEmpleado() = 0;
		virtual void finalizarSuscripcion() = 0;
		virtual void eliminarEmpleado() = 0;
		virtual vector<DTNotificacion> listaNotificaciones() = 0;
		virtual void finalizarConsultaNotis() = 0;
		virtual void finalizarEliminacion() = 0;
		virtual vector<DTCalificacion> getCalificacionesSinResponder(string) = 0;

		//Caso de uso: Subscribirse a notis
		virtual map<string,string> getListaEmpleados() = 0;
		virtual void seleccionarEmpleado(string nombreEmpleado) = 0;
		virtual void cargaDatos() = 0;		
};

#endif