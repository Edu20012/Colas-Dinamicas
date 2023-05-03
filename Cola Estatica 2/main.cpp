#include <iostream>
#include <ostream>
#include <queue>
using namespace std;

// Clase Solicitud que contiene los datos de una solicitud de constancia de estudio
class Solicitud {
  private:
    string nombre; // Nombre del alumno
    string carrera; // Nombre de la carrera que cursa
    int materias; // Total de materias aprobadas
    float promedio; // Promedio general
  public:
    // Constructor que inicializa los atributos con los valores dados
    Solicitud(string nom, string car, int mat, float pro) {
      nombre = nom;
      carrera = car;
      materias = mat;
      promedio = pro;
    }
    // Sobrecarga del operador << para imprimir los datos de una solicitud por pantalla
    friend ostream& operator<<(ostream& os, const Solicitud& s) {
      os << "Nombre: " << s.nombre << endl;
      os << "Carrera: " << s.carrera << endl;
      os << "Materias aprobadas: " << s.materias << endl;
      os << "Promedio general: " << s.promedio << endl;
      return os;
    }
};

// Plantilla Cola que implementa una cola din�mica
template<class T>
class Cola {
  private:
    // Clase Nodo que contiene un dato y un puntero al siguiente nodo
    class Nodo {
      public:
        T data; // Dato almacenado en el nodo
        Nodo *sig; // Puntero al siguiente nodo
        // Constructor que inicializa el atributo data con el dato dado
        Nodo(T d) : data(d) {}
    };
    Nodo *lista; // Puntero al frente de la cola
    Nodo *ultimo()const; // M�todo privado que devuelve el puntero al final de la cola
  public:
    // Constructor que inicializa el puntero a NULL
    Cola() : lista(NULL) {}
    // Destructor que libera la memoria ocupada por los nodos de la cola
    ~Cola() {
      Nodo *reco = lista;
      Nodo *bor;
      while (reco != NULL) {
        bor = reco;
        reco = reco->sig;
        delete bor;
      }
    }
    // M�todo que verifica si la cola est� vac�a y devuelve un valor booleano
    bool vacia()const {
      if (lista == NULL) // Si el puntero es NULL, la cola est� vac�a
        return true;
      else // Si no, la cola tiene al menos un elemento
    return false;
    }
    // M�todo que imprime todos los datos de la cola por pantalla
    void imprimir()const {
      Nodo *aux = lista; // Se crea un puntero auxiliar que apunta al frente de la cola
      while (aux != NULL) { // Se recorre la cola mientras el puntero no sea NULL
        cout << aux->data << endl; // Se imprime el dato del nodo actual
        aux = aux->sig; // Se avanza el puntero al siguiente nodo
      }
    }
    // M�todo que inserta un dato al final de la cola
    void Enqueue(T d) {
      Nodo *nuevo = new Nodo(d); // Se crea un nuevo nodo con el dato dado
      nuevo->sig = NULL; // El nuevo nodo apunta a NULL
      if (vacia()) { // Si la cola est� vac�a, el nuevo nodo es el frente de la cola
        lista = nuevo;
      }
      else { // Si no, el final actual de la cola apunta al nuevo nodo
        ultimo()->sig = nuevo;
      }
    }
    // M�todo que extrae un dato del frente de la cola y lo devuelve
    T Dequeue() {
      if (!vacia()) { // Si la cola no est� vac�a, se extrae el dato del nodo frente
        T informacion = lista->data; // Se guarda el dato en una variable local
        Nodo *bor = lista; // Se guarda el puntero al nodo frente en una variable local
        lista = lista->sig; // El frente pasa a ser el siguiente nodo
        delete bor; // Se libera la memoria del nodo borrado
        return informacion; // Se devuelve el dato extra�do
      }
    }
    // M�todo que devuelve el dato del frente de la cola sin extraerlo
    T Front() {
      if (!vacia()) { // Si la cola no est� vac�a, se devuelve el dato del nodo frente
        return lista->data;
      }
    }
};

// M�todo privado que devuelve el puntero al final de la cola
template<class T>
typename Cola<T>::Nodo* Cola<T>::ultimo()const {
  if (vacia()) { // Si la cola est� vac�a, se devuelve NULL
    return NULL;
  }
  else { // Si no, se busca el �ltimo nodo de la cola
    Nodo *aux = lista; // Se crea un puntero auxiliar que apunta al frente de la cola
    while (aux->sig != NULL) { // Se recorre la cola mientras el puntero no apunte a NULL
      aux = aux->sig; // Se avanza el puntero al siguiente nodo
    }
    return aux; // Se devuelve el puntero al �ltimo nodo
  }
}

// Sobrecarga del operador >> para leer los datos de una solicitud desde el teclado e insertarla en la cola
istream& operator>>(istream& is, Cola<Solicitud>& c) {
  string nombre; // Variable para guardar el nombre del alumno
  string carrera; // Variable para guardar el nombre de la carrera que cursa
  int materias; // Variable para guardar el total de materias aprobadas
  float promedio; // Variable para guardar el promedio general
  cout << "Ingrese el nombre del alumno: "; // Se pide el nombre por pantalla
  cin.ignore(); // Se ignora el salto de l�nea anterior
  getline(cin, nombre); // Se lee el nombre por teclado
  cout << "Ingrese el nombre de la carrera que cursa: "; // Se pide la carrera por pantalla
  getline(cin, carrera); // Se lee la carrera por teclado
  cout << "Ingrese el total de materias aprobadas: "; // Se pide las materias por pantalla
  cin >> materias; // Se lee las materias por teclado
  cout << "Ingrese el promedio general: "; // Se pide el promedio por pantalla
  cin >> promedio; // Se lee el promedio por teclado
  Solicitud s(nombre, carrera, materias, promedio);//Se crea una solicitud con los datos le�dos
  c.Enqueue(s); // Se inserta la solicitud en la cola usando el m�todo Enqueue de la plantilla Cola
  return is;
}

// Funci�n que crea un men� con las opciones del programa y devuelve la opci�n elegida por el usuario
int menu() {
  int opcion; // Variable para guardar la opci�n elegida por el usuario
  cout << "Men� de opciones\n"; // Se muestra el men� por pantalla
  cout << "1. Dar de alta una solicitud\n";
  cout << "2. Elaborar una constancia\n";
  cout << "3. Salir\n";
  cout << "Ingrese su opci�n: "; // Se pide la opci�n por pantalla
  cin >> opcion; // Se lee la opci�n por teclado
  return opcion; // Se devuelve la opci�n elegida
}

// Funci�n principal del programa
int main() {
  Cola<Solicitud> *cola1 = new Cola<Solicitud>(); // Se crea una cola din�mica vac�a usando la plantilla Cola con el tipo de dato Solicitud
  int opcion; // Variable para guardar la opci�n del men�
  do { // Se repite el siguiente bloque mientras la opci�n no sea salir
    opcion = menu(); // Se llama a la funci�n menu y se guarda la opci�n devuelta
    switch (opcion) { // Se ejecuta un caso seg�n la opci�n elegida
      case 1: // Si la opci�n es dar de alta una solicitud
        cin >> *cola1; // Se llama al operador >> para leer los datos de una solicitud e insertarla en la cola
        break; // Se sale del switch
      case 2: // Si la opci�n es elaborar una constancia
        if (!cola1->vacia()) { // Si la cola no est� vac�a, se extrae una solicitud y se muestra sus datos por pantalla con un formato adecuado
          Solicitud s = cola1->Dequeue();
          cout << "Constancia de estudio\n";
          cout << "---------------------\n";
          cout << s;
          cout << "---------------------\n";
        }
        else { // Si la cola est� vac�a, se muestra un mensaje de error por pantalla
          cout << "No hay solicitudes pendientes\n";
        }
        break; // Se sale del switch
      case 3: // Si la opci�n es salir
        cout << "Gracias por usar el programa\n"; // Se muestra un mensaje de despedida por pantalla
        break; // Se sale del switch
      default: // Si la opci�n no es ninguna de las anteriores
        cout << "Opci�n inv�lida\n"; // Se muestra un mensaje de error por pantalla
        break; // Se sale del switch
    }
  } while (opcion != 3); // Se repite el bucle mientras la opci�n no sea salir
  delete cola1; // Se libera la memoria ocupada por la cola
  return 0; // Se termina el programa
}
