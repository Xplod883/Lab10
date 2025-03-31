#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

using namespace std;

class miembroClub {
private:
	string nombre;
	int edad;
	string correo;

public:
	miembroClub(string n, int e, string c) {
		nombre = n;
		edad = e;
		correo = c;
	}

	void guardarenArchivo() {
		ofstream archivo("club.txt", ios::app);
		if (archivo.is_open()) {
			archivo << nombre << " " << edad << " " << correo << endl;
			archivo.close();
			cout << "Datos guardados exitosamente.\n";
		} else {
			cout << "Error al abrir el archivo.\n";
		}
	}

	static void leerdesdeaArchivo() {
		ifstream archivo("club.txt");
		string n, c;
		int e;

		if (archivo.is_open()) {
			cout << "\nLista de miembros:\n";
			while (archivo >> n >> e >> c) {
				cout << "Nombre: " << n << ", Edad: " << e << ", Correo: " << endl;
			}
			archivo.close();
		} else {
			cout << "Error al abrir el archivo/el archivo no existe.\n";
		}
	}

	static void actualizarMiembro(string nombreBuscar, int nuevaEdad, string nuevoCorreo) {
		ifstream archivo("club.txt");
		ofstream archivoTemp("temp.txt");
		string n, c;
		int e;
		bool encontrado = false;

		if (archivo.is_open() && archivoTemp.is_open()) {
			while (archivo >> n >> e >> c) {
				if (n == nombreBuscar) {
					archivoTemp << n << " " << nuevaEdad << " " << nuevoCorreo << endl;
					encontrado = true;
				} else {
					archivoTemp << n << " " << e << " " << c << endl;
				}
			}

			archivo.close();
			archivoTemp.close();
			remove("club.txt");
			rename("temp.txt", "club.txt");
			if (encontrado) {
				cout << "Miembro actualizado exitosamente.\n";
			} else {
				cout << "Miembro no encontrado.\n";
			}
		} else {
			cout << "Error al abrir el archivo.\n";
		}
	}

	static void eliminarMiembro(string nombreBuscar) {
		ifstream archivo("club.txt");
		ofstream archivoTemp("temp.txt");
		string n, c;
		int e;
		bool eliminado = false;

		if (archivo.is_open() && archivoTemp.is_open()) {
			while (archivo >> n >> e >> c) {
				if (n == nombreBuscar) {
					eliminado = true;
				} else {
					archivoTemp << n << " " << e << " " << c << endl;
				}
			}

			archivo.close();
			archivoTemp.close();
			remove("club.txt");
			rename("temp.txt", "club.txt");
			if (eliminado) {
				cout << "Miembro eliminado exitosamente.\n";
			} else {
				cout << "Miembro no encontrado.\n";
			}
		} else {
			cout << "Error al abrir el archivo.\n";
		}
	}
};

int main() {
	setlocale(LC_ALL, "es_ES.UTF-8");

	int opcion;
	do {
		cout << "-- Menu del Club --\n";
		cout << "1. Agregar nuevo miembro.\n";
		cout << "2. Mostrar miembros.\n";
		cout << "3. Actualizar miembros.\n";
		cout << "4. Eliminar miembros.\n";
		cout << "5. Salir.\n";
		cout << "Seleccione una opción: ";
		cin >> opcion;

		if (opcion == 1) {
			string nombre, correo;
			int edad;
			cout << "Ingrese nombre: ";
			cin >> nombre;
			cout << "Ingrese edad: ";
			cin >> edad;
			cout << "Ingrese correo: ";
			cin >> correo;

			miembroClub nuevo(nombre, edad, correo);
			nuevo.guardarenArchivo();
		} else if (opcion == 2) {
			miembroClub::leerdesdeaArchivo();
		} else if (opcion == 3) {
			string nombre;
			int edad;
			string correo;
			cout << "Ingrese nombre del miembro a actualizar: ";
			cin >> nombre;
			cout << "Ingrese nueva edad: ";
			cin >> edad;
			cout << "Ingrese nuevo correo: ";
			cin >> correo;
			miembroClub::actualizarMiembro(nombre, edad, correo);
		} else if (opcion == 4) {
			string nombre;
			cout << "Ingrese nombre del miembro a eliminar: ";
			cin >> nombre;
			miembroClub::eliminarMiembro(nombre);
		} else if (opcion == 5) {
			cout << "Saliendo del programa, por favor espere...\n";
		} else {
			cout << "Opción inválida. Intente de nuevo\n";
		}
	} while (opcion != 5);

	return 0;
}