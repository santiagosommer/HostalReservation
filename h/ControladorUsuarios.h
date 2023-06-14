#ifndef CONTROLADORUSUARIOS_
#define CONTROLADORUSUARIOS_

#include "IUsuarios.h"

class Huesped;
class Empleado;
class Usuario;
class Notificacion;
class DTUsuario;
class DTNotificacion;

class ControladorUsuarios : public IUsuarios
{
	private:
		static ControladorUsuarios* instance;

		set<Empleado*> observers;
		
		map<string, Huesped*> huespedes;
		map<string, Empleado*> empleados;
		map<string, Usuario*> usuarios;

		// Caso de Uso: Alta de Usuario
		string nombreUsuario, emailUsuario, passwordUsuario;
		bool esEmpleadoUsuario, esFingerUsuario;
		CargoEmpleado cargoUsuario;
		
		//Registrar Estadia
		string nombreHostal;

		//Consulta de Usuario
		string usuarioSeleccionado;

		//Arreglos Nacho
		string emailHuesped;
		int codigoReserva;

		//Caso de uso: Subscribirse a notis
		string emailEmpleadoASuscribir;

	public: 

		static ControladorUsuarios* getInstance();

		// Caso de Uso: Alta de Usuario
		void setUserInfo(string nombre, string email, string password);
		void esEmpleado(bool esEmpleado);
		void setCargoEmpleado(CargoEmpleado cargo);
		void esFinger(bool esFinger);
		bool esUsuarioRepetido();
		void reingresarDatos();
		void cancelarAltaUsuario();
		void confirmarAltaUsuario();
		
		// Caso de Uso: Asignar Empleado a Hostal
		Empleado* getEmpleado(string emailEmpleado);

		set<string> getUsuarios();
		void seleccionarUsuario(string);

		// Caso de Uso: Realizar Reserva
		set<string> getHuespedes();
		Huesped* getHuesped(string emailHuesped);

		//Registrar Estadia
		set<string> getHostales();
		void seleccionarHostal(string);
		set<int> getReservasDelHuesped(string); 
		void seleccionarReserva(int);
		void registrarEstadia();
		void suscribirEmpleado();
		void finalizarSuscripcion();
		void eliminarEmpleado();
		vector<DTNotificacion> listaNotificaciones();
		void finalizarConsultaNotis();
		void finalizarEliminacion();

		map<string,Empleado*>  getEmpleados();

		//Consulta de Usuario
		DTEmpleado getDTEmpleado();
		DTHuesped getDTHuesped();
		void finalizarConsultaUsuario();
		bool esEmp();

		//CalificarEstadia
		void notificarObservadores(Notificacion*);
		//ComentarCalificacion
		vector<DTCalificacion> getCalificacionesSinResponder(string);

		// Caso de Uso: Subscribirse a Notis
		map<string, string> getListaEmpleados();
		void seleccionarEmpleado(string empleado);
		void cargaDatos();		
		
	    
};

#endif