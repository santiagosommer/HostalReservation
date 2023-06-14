#ifndef IRELOJ_
#define IRELOJ_

#include <string>
#include <map>
#include "Fecha.h"

using namespace std;


class IReloj {
	public:
		virtual Fecha getFechaActual() = 0;
		virtual void modificarFecha(float, int, int, int) = 0;
		virtual void cargaDatos() = 0;
};

#endif