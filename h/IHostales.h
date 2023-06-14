#ifndef IHOSTALES_
#define IHOSTALES_

#include <string>
#include <map>
#include <set>
#include <vector>

#include "Enum.h"
#include "Fecha.h"
#include "DTCalificacion.h"

class DTHostal;
class DTCalificacion;

using namespace std;

class IHostales{
	public:
		virtual DTHostal getDTHostal() = 0;
		virtual DTHostal getDTHostalConsulta() = 0;
		virtual set<string> getHostales() = 0;
		virtual void seleccionarHostal(string) = 0;
		virtual void altaHabitacion(int, int, int) = 0;
		virtual void confirmarAltaHabitacion() = 0;
		virtual void cancelarAltaHabitacion() = 0;
		virtual map<int,string> getTop3Hostales() = 0;
		virtual vector<DTCalificacion> getDetallesHostal(string) = 0;
		virtual void finalizarConsultaHostal() = 0;
		virtual void setHostalInfo(string, string, string) = 0;
		virtual void cancelarAltaHostal() = 0;
		virtual void confirmarAltaHostal() = 0;
		virtual void asignarEmpleado(string, CargoEmpleado) = 0;
		virtual void cancelarAsignacion() = 0;
		virtual void confirmarAsignacion() = 0;
		virtual set<string> getEmpleadosFueraDeHostal(string) = 0;
		virtual void cancelarReserva() = 0;
		virtual void confirmarReserva() = 0;
		virtual set<int> getHabitacionesLibres() = 0;
		virtual vector<DTHostal> getHostalesPlus() = 0;
		virtual void seleccionarHabitacion(int numeroHabitacion) = 0;
		virtual void seleccionarHostalParaReserva(string nombreHostal, Fecha checkIn, Fecha checkOut, bool esReservaGrupal) = 0;
		virtual void seleccionarHuesped(string nombreHuesped) = 0;
		virtual bool existeHostal(string nombreHostal) = 0;
		virtual bool checkearHab(int) = 0;
		virtual set<string> getHuespedesConReserva(string) = 0;

		virtual void cargaDatos() = 0;
};

#endif