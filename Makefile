# Compilador
CC = g++

# Flags del compilador
CFLAGS = -g -Wall -Werror -std=c++11

# Ejecutable
PRINCIPAL = main

# Directorios
HDIR = h
CPPDIR = cpp
ODIR = o

# Clases
CLASES = CargoEmpleado Calificacion ControladorHostales ControladorReloj ControladorReservas ControladorUsuarios DTCalificacion DTEstadia DTEstadiaPlus DTHabitacion DTHostal DTNotificacion DTReserva DTUsuario Estadia Fabrica Fecha Habitacion Hostal IHostales IReloj IReservas IUsuarios Notificacion Reserva RespuestaEmpleado Usuario Enum

# Archivos
HS = $(CLASES:%=$(HDIR)/%.h) Enum.h
CPPS = $(CLASES:%=$(CPPDIR)/%.cpp)
OS = $(CLASES:%=$(ODIR)/%.o)

# Objetos
OBJ = $(CPPS:.cpp=.o)

# Archivo main y los subdirectorios
LAB4 = main.cpp $(HDIR) $(CPPDIR) $(ODIR)

all: make

%.o: $(CPPDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CFLAGS) -c $< -o o/$@

$(PRINCIPAL).o:$(PRINCIPAL).cpp
	$(CC) $(CFLAGS) -c $< -o $@

make: main.cpp Calificacion.o ControladorHostales.o ControladorReloj.o ControladorReservas.o ControladorUsuarios.o DTCalificacion.o DTEstadia.o DTEstadiaPlus.o DTHabitacion.o DTHostal.o DTNotificacion.o DTReserva.o DTUsuario.o Estadia.o Fecha.o Habitacion.o Hostal.o Notificacion.o Reserva.o RespuestaEmpleado.o Usuario.o
	$(CC) $(CFLAGS) -o main main.cpp o/*.o

zip: $(LAB4) Makefile
	rm -f g41_lab4.tar.gz
	tar -cvf g41_lab4.tar $(LAB4) Makefile
	gzip g41_lab4.tar

clean:
	-rm -f o/*.o
	-rm -f main
	-rm -f g41_lab4.tar.gz
