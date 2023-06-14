#ifndef CONTROLADORHOSTALES_
#define CONTROLADORHOSTALES_

#include "IHostales.h"

#include <map>
#include <set>
#include <vector>

class Hostal;

class ControladorHostales : public IHostales{
	
	private:
		static ControladorHostales* instance;
		map<string, Hostal*> hostales;
		
		//Caso de Uso: Alta de Hostal
		string nombreHostal, direccionHostal, telefonoHostal;

		//Caso de Uso: Alta de Habitacion
		string hostalSeleccionado;
		int numeroHab, precioHab, capacidadHab;

		//Caso de Uso: Asignar Empleado a Hostal
		string nombreEmpleadoAAsignar, nombreHostalAAsignar;
		CargoEmpleado cargoEmpleadoAAsignar;

		//Caso de Uso: Realizar Reserva
		string nombreHostalAReservar;
		Fecha checkInReserva, checkOutReserva;
		bool esReservaGrupalReserva;
		int habitacionAReservar;
		set<string> huespedesAElegir;
	


	public: 
		static ControladorHostales* getInstance();


		//Caso de uso: Alta de Hostal
		void setHostalInfo(string nombre, string direccion, string telefono);
		void confirmarAltaHostal();
		void cancelarAltaHostal();

		//Caso de uso: Alta de Habitacion
		set<string> getHostales();
		void seleccionarHostal(string);
		void altaHabitacion(int, int, int);
		void confirmarAltaHabitacion();
		void cancelarAltaHabitacion();
		bool checkearHab(int);

		//Caso de uso: Consulta de Hostal
		DTHostal getDTHostal();
		DTHostal getDTHostalConsulta();
		void finalizarConsultaHostal();

		//Caso de uso: Realizar Reserva
		bool existeHostal(string nombreHostal);
		vector<DTHostal> getHostalesPlus();
		void seleccionarHostalParaReserva(string nombreHostal, Fecha checkIn, Fecha checkOut, bool esReservaGrupal);
		void seleccionarHabitacion(int habitacion);
		void seleccionarHuesped(string nombreHuesped);

		map<int,string> getTop3Hostales();
		vector<DTCalificacion> getDetallesHostal(string);
		void asignarEmpleado(string nombreEmpleado, CargoEmpleado cargo);
		void cancelarAsignacion();
		void confirmarAsignacion();
		set<string> getEmpleadosFueraDeHostal(string);
		void cancelarReserva();
		void confirmarReserva();
		set<int> getHabitacionesLibres();

		//CalificarEstadia
		Hostal* getHostal(string);
		void cargaDatos();		


		set<string> getHuespedesConReserva(string nombreHostal);
};

#endif