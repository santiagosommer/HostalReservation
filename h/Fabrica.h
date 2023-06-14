#ifndef FABRICA_
#define FABRICA_

#include "IUsuarios.h"
#include "ControladorUsuarios.h"
#include "IReservas.h"
#include "ControladorReservas.h"
#include "IHostales.h"
#include "ControladorHostales.h"
#include "IReloj.h"
#include "ControladorReloj.h"

class Fabrica
{
    public:
    IUsuarios* getIUsuarios() { return ControladorUsuarios::getInstance(); };
    IReservas* getIReservas() { return ControladorReservas::getInstance(); };
    IHostales* getIHostales() { return ControladorHostales::getInstance(); };
    IReloj* getIReloj() { return ControladorReloj::getInstance(); };

};

#endif