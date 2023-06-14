#ifndef CONTROLADORRESERVAS_
#define CONTROLADORRESERVAS_

#include "IReservas.h"

#include <set>
#include <map>
#include <vector>

class Reserva;
class Empleado;
class DTReserva;
class DTReservaIndividual;
class DTReservaGrupal;

class ControladorReservas : public IReservas
{
	private:
		static ControladorReservas* instance;
		map<int, Reserva*> reservas;
		int sigCodigoReserva = 0;

		string hostalSeleccionado;
		int codigoReservaEstadia;
		string emailHuespedEstadia;
		
		Empleado* empleadoGuardado;


    public:

		static ControladorReservas* getInstance();

		void registrarEstadia(int, Huesped*); 
		set<string> getAllHostales();
	    void finalizarEstadia();
		void setCalificacion(string, int);
		// CalificarEstadia 
		void seleccionarHostal(string);
		vector<DTEstadia> getEstadiasFinalizadas(string);
		void seleccionarEstadia(int, string);
		void seleccionarEstadiaConHostal(string, string);
		//ComentarCalificacion
		vector<DTCalificacion> getCalificacionesSinResponder(string);
		void selectCalificacion(string, int);
		void setComentarioCalificacion(string);
		//ConsultaEstadia
		vector<DTEstadia> getEstadias();
		DTEstadiaPlus getEstadiaPlus();
		DTCalificacion getDTCalificacion();
		DTReserva getDTReserva();
		void finConsultaEstadia();
		set<string> getHostales();
		bool existeCalificacion();
		bool existeRespuestaEmpleado();
		string getRespuestaEmpleado();

		//Caso de uso: Realizar Reserva
		void addReserva(Reserva* r);
		int getCodigoReservaACrear();

		//consultar reservas
		vector<DTReserva> listarReservasDeHostal(string nombreHostal);
		vector<DTReservaIndividual> getReservasIndividuales(vector<DTReserva> reservas);
		vector<DTReservaGrupal> getReservasGrupales(vector<DTReserva> reservas);
		//baja reserva
		set<int> listarCodigoReservasDeHostal(string nombreHostal);
		void confirmarBajaReserva();
		void seleccionarReserva(int);

		void cargaDatos();
};

#endif