#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <sstream>

using namespace std;

class Inventario{
private:
  class NodoProductos{
    public:
      string Nombre_Producto, Categoria;
      int Stock;
      long int Precio;
      NodoProductos* siguiente;
    };
  NodoProductos* Raiz;
public: 
  Inventario(); //Constructor
  ~Inventario(); //Destructor
  int NumeroProductos();
  void Agregar_Producto();
  void imprimir();
  void Eliminar_Producto();
  bool vacia();
  void centrarTexto(string texto, int x);
  void Menu_Principal();
  void IniciarArchivo();
  void OrdenarProductos();
  void Buscar_Producto();
  void Actualizar_Producto();
  void Cargar_Inventario();
};

Inventario::Inventario() //Constructor
{
  Raiz = NULL;
}

Inventario::~Inventario()
{
  NodoProductos* recorrido = Raiz;
  NodoProductos* borrar;
  while (recorrido!= NULL)
  {
    borrar = recorrido;
    recorrido = recorrido->siguiente;
    delete borrar;
  }
  Raiz = NULL;
}

bool Inventario::vacia()
{
  if (Raiz == NULL)
    return true;
  else
    return false;
}

int Inventario::NumeroProductos()
{
  NodoProductos* recorrido = Raiz;
  int cantidad = 0;
  while (recorrido != NULL)
  {
    cantidad++;
    recorrido = recorrido->siguiente;
  }
  return cantidad;
}

void Inventario::centrarTexto(string texto, int x){
  int espacio = (170 - texto.size()) / 2; 
    if(x > 0){
      for(int i = 0; i < espacio; i++){
        cout << " ";
      }
    cout << texto << endl;
    }else{
      for(int i = 0; i < espacio; i++){
        cout << " ";
      }
    cout << texto;
    }
}

void Inventario::IniciarArchivo(){
  ofstream Archivo("Inventario.csv", ios::app);
  Archivo << "CATEGORIA;NOMBRE PRODUCTO;STOCK;PRECIO" << endl;
  Archivo.close();
}

void Inventario::Agregar_Producto(){	
  int _stock;
  string _nombre, _categoria;
  long int _precio;
  cin.ignore();
  centrarTexto("Indique la Categoria del Producto (Lacteos, Despensa, Frutas y Verduras.): ",0);
  getline(cin,_categoria);
  centrarTexto("Indique el Nombre del Producto: ",0);
  getline(cin,_nombre);
  centrarTexto("Indique el Stock del Producto: ",0);
  cin >> _stock;
  centrarTexto("Indique el Precio del Producto: $ ",0);
  cin >> _precio;

  if(NumeroProductos() > 0){
      NodoProductos* nuevo = new NodoProductos();
        nuevo->Categoria = _categoria;
        nuevo->Nombre_Producto = _nombre;
        nuevo->Stock = _stock;
        nuevo->Precio = _precio;
        NodoProductos* recorrido = Raiz;
        while(recorrido->siguiente != NULL){
          recorrido = recorrido->siguiente;
        }
        recorrido->siguiente = nuevo;
        nuevo->siguiente = NULL;
    }else{
      NodoProductos* nuevo = new NodoProductos();
        nuevo->Categoria = _categoria;
        nuevo->Nombre_Producto = _nombre;
        nuevo->Stock = _stock;
        nuevo->Precio = _precio;
        nuevo->siguiente = NULL;
        Raiz = nuevo;
      }
    ofstream Archivo ("Inventario.csv", ios::app);
    Archivo << _categoria << ";" << _nombre << ";" << _stock << ";" << _precio << endl;
    OrdenarProductos();
    Archivo.close();

    }


void Inventario::Eliminar_Producto(){
  string NombreEliminar;
  cin.ignore();
  centrarTexto("Ingrese el Nombre del Producto que Desea Eliminar: ",0);
  getline(cin,NombreEliminar);

  if (Raiz != NULL){
    if (Raiz->Nombre_Producto == NombreEliminar){
      NodoProductos* borrar = Raiz;
      Raiz = Raiz->siguiente;
      delete borrar;
      centrarTexto("Producto Eliminado con Exito...",1);
    }else{
      NodoProductos* recorrido = Raiz;
      NodoProductos* anterior = NULL;
      while (recorrido != NULL && recorrido->Nombre_Producto != NombreEliminar){
        anterior = recorrido;
        recorrido = recorrido->siguiente;
      }if (recorrido != NULL){
        anterior->siguiente = recorrido->siguiente;
        delete recorrido;
        centrarTexto("Producto Eliminado con Exito...",1);
      }
    }
    OrdenarProductos();
  }	
}


void Inventario::imprimir()
{
  NodoProductos* recorrido = Raiz;
    centrarTexto("Inventario completo: ",1);

    while (recorrido != NULL){
      string MensajeC = "Categoria Producto: " + recorrido->Categoria;
      string MensajeN = "Nombre Producto: " + recorrido->Nombre_Producto;
      string MensajeS = "Stock: " + to_string(recorrido->Stock);
      string MensajeP = "Precio: " + to_string(recorrido->Precio);
      centrarTexto(MensajeC,1);
      centrarTexto(MensajeN,1);
      centrarTexto(MensajeS,1);
      centrarTexto(MensajeP,1);
      cout << endl;
      recorrido = recorrido->siguiente;
    }
  cout << "\n";
  cout << "Número de productos: " <<NumeroProductos() << endl;
}


void Inventario::OrdenarProductos() {
    NodoProductos* recorrido = Raiz;
    NodoProductos* siguiente = NULL;

    while (recorrido != NULL) {
        siguiente = recorrido->siguiente;

        while (siguiente != NULL) {
            if (recorrido->Categoria > siguiente->Categoria){

                swap(recorrido->Categoria, siguiente->Categoria);
                swap(recorrido->Nombre_Producto, siguiente->Nombre_Producto);
                swap(recorrido->Stock, siguiente->Stock);
                swap(recorrido->Precio, siguiente->Precio);
            }else 
      if (recorrido->Categoria == siguiente->Categoria && recorrido->Nombre_Producto > siguiente->Nombre_Producto){
                swap(recorrido->Nombre_Producto, siguiente->Nombre_Producto);
                swap(recorrido->Stock, siguiente->Stock);
                swap(recorrido->Precio, siguiente->Precio);
            }

            siguiente = siguiente->siguiente;
        }

        recorrido = recorrido->siguiente;
    }

    ofstream Archivo("Inventario.csv", ios::out);
    Archivo << "CATEGORIA;NOMBRE PRODUCTO;STOCK;PRECIO" << endl;

    recorrido = Raiz;
    while (recorrido != NULL) {
        Archivo << recorrido->Categoria << ";" << recorrido->Nombre_Producto << ";" << recorrido->Stock << ";" << recorrido->Precio << endl;
        recorrido = recorrido->siguiente;
    }

}


void Inventario::Buscar_Producto(){
  string NombreBuscado;
  cin.ignore();
  centrarTexto("Ingrese el Nombre del Producto que desea Buscar: ",0);
  getline(cin,NombreBuscado);

  NodoProductos* recorrido = Raiz;
  bool encontrado = false;

    while (recorrido != NULL){
        if (recorrido->Nombre_Producto == NombreBuscado) {
            encontrado = true;
            break;
        }
        recorrido = recorrido->siguiente;
    }

    if (encontrado){
        string MensajeC = "Categoria Producto: " + recorrido->Categoria;
        string MensajeN = "Nombre Producto: " + recorrido->Nombre_Producto;
        string MensajeS = "Stock: " + to_string(recorrido->Stock);
        string MensajeP = "Precio: " + to_string(recorrido->Precio);
        centrarTexto("Producto encontrado:", 1);
        centrarTexto(MensajeC, 1);
        centrarTexto(MensajeN, 1);
        centrarTexto(MensajeS, 1);
        centrarTexto(MensajeP, 1);
        cout << endl;
    }else{
        centrarTexto("Producto No Encontrado.", 1);
    }
}


void Inventario::Actualizar_Producto(){
  string NombreActualizar;
  cin.ignore();
  centrarTexto("Ingrese el Nombre del Producto que desea actualizar: ",0);
  getline(cin,NombreActualizar);

  NodoProductos* recorrido = Raiz;
  bool encontrado = false;

    while (recorrido != NULL && recorrido->Nombre_Producto != NombreActualizar){
        recorrido = recorrido->siguiente;
    }
    if (recorrido != NULL){
      encontrado = true;
  }
  if (encontrado){
    centrarTexto("Información Actual del Producto: ", 1);
        centrarTexto(("Categoria Producto: " + recorrido->Categoria), 1);
        centrarTexto(("Nombre Producto: " + recorrido->Nombre_Producto), 1);
        centrarTexto(("Stock: " + to_string(recorrido->Stock)), 1);
        centrarTexto(("Precio: " + to_string(recorrido->Precio)), 1);
        cout << endl;

        int nuevoStock;
        float nuevoPrecio;

        centrarTexto("Ingrese el Nuevo Stock del Producto: ", 0);
        cin >> nuevoStock;

        centrarTexto("Ingrese el Nuevo Precio del Producto: $ ", 0);
        cin >> nuevoPrecio;

        recorrido->Stock = nuevoStock;
        recorrido->Precio = nuevoPrecio;

        OrdenarProductos();

        centrarTexto("Produto Actualizado con Exito...",1);
  }else{
    centrarTexto("Producto No Encontrado.", 1);
  }
}



void Inventario::Menu_Principal(){
  centrarTexto("---BIENVENIDO A NUESTRO INVENTARIO DE SUPERMERCADO LOS INGENIEROS--- ",1);
  cout << endl;
  int opc;
  do{
    if(vacia()){
      centrarTexto("MENU PRINCIPAL.",1);
        centrarTexto("1. Agregar Producto",1);
        centrarTexto("2. Salir del Programa",1);
        centrarTexto("Digite la opción: ",0); cin >> opc;
        switch(opc){
          case 1:
            cout << endl;
            Agregar_Producto();
          break;

          case 2:
            cout << endl;
            centrarTexto("Gracias por Usar Nuestro Inventario SuperMercado Los Ingenieros.",1);
            centrarTexto("Saliendo del Programa...",1);
            exit(0);
          break;

          default:
            centrarTexto("La opcion digitada no esta disponible, intenta de nuevo",1);
          break;
        }
  }else{
    cout << endl;
      centrarTexto("MENU PRINCIPAL",1);
      centrarTexto("1. Agregar Producto",1);
      centrarTexto("2. Eliminar Producto",1);
      centrarTexto("3. Buscar Producto",1);
      centrarTexto("4. Imprimir Inventario Completo",1);
      centrarTexto("5. Actualizar Invetario y Precio de un Producto",1);
      centrarTexto("6. Salir del Programa",1);
      centrarTexto("Digite la opción: ",0); cin >> opc;
      switch(opc){
        case 1:
          //system("cls");
          cout << endl;
          Agregar_Producto();
          break;

          case 2:
            //system("cls");
            cout << endl;
            Eliminar_Producto();
          break;

          case 3:
            //system("cls");
            cout << endl;
            Buscar_Producto();
          break;

          case 4:
            //system("cls");
            cout << endl;
            imprimir();
          break;

          case 5:
            //system("cls");
            cout << endl;
            Actualizar_Producto();
          break;

          case 6:
            cout << endl;
            centrarTexto("Gracias por Usar Nuestro Inventario SuperMercado Los Ingenieros.",1);
            centrarTexto("Saliendo del Programa...",1);
            exit(0);
          break;

          default:
            centrarTexto("La opcion digitada no esta disponible, intenta de nuevo",1);
          break;
        }
    }
  }while(opc != 8);
}


void Inventario::Cargar_Inventario() {
    ifstream archivo("Inventario.csv");
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    string linea;
    getline(archivo, linea); 

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string categoria, nombre, stock_str, precio_str;
        getline(ss, categoria, ';');
        getline(ss, nombre, ';');
        getline(ss, stock_str, ';');
        getline(ss, precio_str, ';');

        int stock = stoi(stock_str);
        long int precio = stol(precio_str);

        NodoProductos* nuevo = new NodoProductos();
        nuevo->Categoria = categoria;
        nuevo->Nombre_Producto = nombre;
        nuevo->Stock = stock;
        nuevo->Precio = precio;
        nuevo->siguiente = NULL;

        if (Raiz == NULL) {
            Raiz = nuevo;
        } else {
            NodoProductos* temp = Raiz;
            while (temp->siguiente != NULL) {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevo;
        }
    }
    if(vacia()){
      centrarTexto("No hay datos para cargar, el invetario esta vacio", 1);
    }else{
      centrarTexto("Se cargaron los datos Exitosamente", 1);
    }


    archivo.close();
}


int main() {


  Inventario* I = new Inventario();
  I->Cargar_Inventario();
  I->Menu_Principal();



  return 0;
}