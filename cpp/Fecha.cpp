#include "../h/Fecha.h"

const int Fecha::getAnio() const{
    return anio;
}
const int Fecha::getMes() const{
    return mes;
}
const int Fecha::getDia() const{
    return dia;
}
const int Fecha::getHora() const{
    return hora;
}
Fecha::Fecha()
{
    this->hora = 0;
    dia = 0;
    mes = 0;
    anio = 0;
}

Fecha::Fecha(float hora, int dia, int mes, int anio){
    this->hora = hora;
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

bool Fecha::before(Fecha fechaAComparar)
{

    if (fechaAComparar.getAnio() - this->anio  > 0) return true;
    else if (fechaAComparar.getAnio() - this->anio  == 0)
    {

        if (fechaAComparar.getMes() - this->mes  > 0) return true;
        else if (fechaAComparar.getMes() - this->mes  == 0)
        {
            if (fechaAComparar.getDia() - this->dia  > 0) return true;
            else if (fechaAComparar.getDia() - this->dia  == 0)
            {
                if(fechaAComparar.getHora() - this->hora >= 0) return true;
            }
        }
    }
    return false;
}

// Checkea si los inicios o finales de cualquiera de las dos fechas estan dentro del otro
bool Fecha::areOverlapping(Fecha primerCheckIn, Fecha primerCheckOut, Fecha segundoCheckIn, Fecha segundoCheckOut)
{
    bool inicioPrimerIntervaloEntreSegundoIntervalo = (primerCheckIn.before(segundoCheckOut) && segundoCheckIn.before(primerCheckIn));
    bool finalPrimerIntervaloEntreSegundoIntervalo = (primerCheckOut.before(segundoCheckOut) && segundoCheckIn.before(primerCheckOut));
    bool inicioSegundoIntervaloEntrePrimerIntervalo = (segundoCheckIn.before(primerCheckOut) && primerCheckIn.before(segundoCheckIn));
    bool finalSegundoIntervaloEntrePrimerIntervalo = (segundoCheckOut.before(primerCheckOut) && primerCheckIn.before(segundoCheckOut));

    return ((inicioPrimerIntervaloEntreSegundoIntervalo || finalPrimerIntervaloEntreSegundoIntervalo) || (inicioSegundoIntervaloEntrePrimerIntervalo || finalSegundoIntervaloEntrePrimerIntervalo));
}