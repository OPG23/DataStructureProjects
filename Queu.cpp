#include <iostream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <fstream>

using namespace std;

class Cola{
  protected:
    class NodoUsuarios{
    public:			
        string Datos;
        string Nombre, Problema, Numero;
        NodoUsuarios* siguiente;
      };
      NodoUsuarios* Raiz;
      int frente;
      int final;
      int MaxTamC;
      string *listaCola;
    public:
      Cola(int maxTamC); 
      ~Cola(); 
      void borrarC();
      string frenteC();
      bool colavaciaC();
      bool colallenaC();
      void AgregarUsuario();
      void Atender(Cola &A);
      void Imprimir();
      void Calificacion_Bot();
      void centrarTexto(string texto, int x);
      void CargarDatos();
      void Menu_U(Cola &A);
      void Menu_S(Cola &A);
      void Asesor(Cola &A);
      void Menu_A(Cola &A);
      void Menu_I(Cola &A);
      void Plan(Cola &A);
      void Saldo_Pagos(Cola &A);
      int NumeroUsuarios();
      void BorrarArchivo();

};	


Cola::Cola(int maxTamC){
  frente = 2;
  final = 1;
  Raiz = NULL;
  MaxTamC = maxTamC;
  listaCola = new string[MaxTamC];
}


Cola::~Cola(){
  while (Raiz != NULL){

      NodoUsuarios* borrar = Raiz;
      Raiz = Raiz->siguiente;
      delete borrar;
    }
}


void Cola::borrarC(){
  frente = 2;
    final = 1;
}


bool Cola::colavaciaC(){
  return frente > final;
}


bool Cola::colallenaC(){
  return final == MaxTamC;
}


int Cola::NumeroUsuarios(){
  NodoUsuarios* Recorrido = Raiz;
  int Cantidad = 0;
  while (Recorrido != NULL){

      Cantidad++;
      Recorrido = Recorrido->siguiente;
    }
    return Cantidad;
}


void Cola::AgregarUsuario(){
  string _nombre, _problema,_numero;
    if (colallenaC()){
      centrarTexto("Lo sentimos la cola esta llena y no podemos agregar mas clientes", 1);	
    }else{
    cin.ignore();
      centrarTexto(" Ingrese su nombre: ", 0);
      getline(cin, _nombre);
      cout << endl;
      centrarTexto("Ingrese su numero de linea movil: ",0);
      getline(cin, _numero);
      centrarTexto("Ingrese la descripcion del problema que presenta: ",0);
      getline(cin, _problema);

    if(NumeroUsuarios() > 0){
      NodoUsuarios* nuevo = new NodoUsuarios();
        nuevo->Nombre = _nombre;
        nuevo->Numero = _numero;
        nuevo->Problema = _problema;
        NodoUsuarios* recorrido = Raiz;
        while(recorrido->siguiente != NULL){
          recorrido = recorrido->siguiente;
        }
        recorrido->siguiente = nuevo;
        nuevo->siguiente = NULL;
        final ++;
    }else{
      NodoUsuarios* nuevo = new NodoUsuarios();
        nuevo->Nombre = _nombre;
        nuevo->Numero = _numero;
        nuevo->Problema = _problema;
        nuevo->siguiente = NULL;
        Raiz = nuevo;
        final ++;
      }
    }

    ofstream Archivo ("Usuarios.csv", ios::app);
    Archivo << _nombre << ";" << _numero << ";" << _problema << endl;
    Archivo.close();	  
} 


void Cola::Imprimir(){
  NodoUsuarios* recorrido = Raiz;
    centrarTexto("Los clientes en cola para atender son: ",1);

    while (recorrido != NULL){
      string Mensaje = "Nombre: " + recorrido->Nombre;
      centrarTexto(Mensaje,1);
      cout << endl;
      recorrido = recorrido->siguiente;
    }
    if(frente > final){
      centrarTexto("La cola está vacía",1); 
    }
}


void Cola::Atender(Cola &A){
  int opc;
  if (!colavaciaC()){
    NodoUsuarios* UsuarioAtendido = Raiz;
      Raiz = UsuarioAtendido->siguiente;
      final--;

      centrarTexto("Se esta atendiendo a: ",1);
      string MensajeN = "Nombre: " + UsuarioAtendido->Nombre;
      string MensajeL = "Linea: " + UsuarioAtendido->Numero;
      string MensajeP = "Problema: " + UsuarioAtendido->Problema;
      centrarTexto(MensajeN,1);
      centrarTexto(MensajeL,1);
      centrarTexto(MensajeP,1);
      centrarTexto("Atendiendo Cliente...",1);
      cout << endl;
      centrarTexto("Cliente Atendido con Exito.",1);
      centrarTexto("¿Resolvio su problema?",1);
      centrarTexto("1. Si",1);
      centrarTexto("2. No",1);
      centrarTexto("Digite la opcion: ",0); cin >> opc;
      if (opc == 1){
        Calificacion_Bot();
      centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
      centrarTexto("Volviendo al Menu Principal...",1);
      cout << endl;
      Menu_I(A);
          }else{
            cout << endl;
            Menu_U(A);       
      }
  }else{
      centrarTexto("La Cola se Encuentra Vacia, No hay Clientes por Atender.",1);
      cout << endl;
  }
}


void Cola::centrarTexto(string texto, int x){
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


void Cola::CargarDatos(){
  string datos;
  ifstream Archivo("Usuarios.csv");
  Archivo.open("Usuarios.csv",ios::in);

    while(getline(Archivo,datos)){
      if(colallenaC()){
        centrarTexto("La cola se encuentra llena.",1);
          break;
        }else{
        if (NumeroUsuarios() > 0){
          NodoUsuarios* nuevo = new NodoUsuarios();
            nuevo->Datos = datos;
            NodoUsuarios* recorrido = Raiz;
              while(recorrido->siguiente != NULL){
                recorrido = recorrido->siguiente;
              }
            recorrido->siguiente = nuevo;
            nuevo->siguiente = NULL;
            final ++;
          }else{

              NodoUsuarios* nuevo = new NodoUsuarios();
            nuevo->Datos = datos;
            nuevo->siguiente = NULL;
            Raiz = nuevo;
            final ++;
          }
        }
    }
    Archivo.close();
}


void Cola::BorrarArchivo(){
  ofstream Archivo("Usuarios.csv", ios::out);
  Archivo << "Nombre;Linea Movil;Problema" << endl;
  Archivo.close();
}



void Cola::Saldo_Pagos(Cola &A){
  int opc;
  string num;
  cin.ignore();
  centrarTexto("SALDO Y PAGOS.",1);
    centrarTexto("Indique la Linea que Desea Consultar: " ,0); getline(cin, num);
    string Mensaje = "Su linea " + num + " se encuentra al dia en sus pagos y el ultimo pago fue el 15/11/2023. ";
    centrarTexto(Mensaje,1);
    cout << endl;
    centrarTexto("¿Resolvio su problema?",1);
    centrarTexto("1. Si",1);
    centrarTexto("2. No",1);
    centrarTexto("Digite la opcion: ",0); cin >> opc;
    if (opc == 1){
        Calificacion_Bot();
    centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
    centrarTexto("Volviendo al Menu Principal...",1);
    cout << endl;
    Menu_I(A);
        }else{
          cout << endl;
            Menu_U(A);       
        }
}


void Cola::Plan(Cola &A){
  int opc;
  string num;
  cin.ignore();
  centrarTexto("CONOCE TU PLAN.",1);
  centrarTexto("Indique la Linea que Desea Consultar: " ,0); getline(cin, num);
  string Mensaje = "Su linea " + num + " Cuenta con el Plan:";
  centrarTexto(Mensaje,1);
  centrarTexto("Minutos y Mensajes Ilimitados todo Destino Nacional",1);
  centrarTexto("80 GB de Datos Moviles",1);
  centrarTexto("WhatsApp, Facebook, Twitter e Instagram Ilimitado",1);
  cout << endl;
  centrarTexto("¿Resolvio su problema?",1);
  centrarTexto("1. Si",1);
  centrarTexto("2. No",1);
  centrarTexto("Digite la opcion: ",0); cin >> opc;
  if (opc == 1){
    Calificacion_Bot();
    centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
    centrarTexto("Volviendo al Menu Principal...",1);
    cout << endl;
    Menu_I(A);
    }else{
      cout << endl;
      Menu_U(A);       
    }
}


void Cola::Asesor(Cola &A){
  A.AgregarUsuario();
  cout << endl;
  centrarTexto("En minutos seras atentido por un asesor encargado de resolver su problema", 1);
  cout << endl;
}



void Cola::Menu_S(Cola &A){	
    int opcion;
    int opc;
  do{
      centrarTexto("MENU SOPORTE.",1);
    centrarTexto("0. Volver al Menu Anterior",1);
      centrarTexto("1. Soporte Voz y Mensajes",1);
      centrarTexto("2. Soporte Datos Moviles",1);
      centrarTexto("3. Gestionar Plan",1);
      centrarTexto("Indique sobre que servicio esta presentando problemas: ",0); cin >> opcion;
      cout << endl;
      switch(opcion){
        case 0:
          centrarTexto("Volviendo al Menu Usuarios ...",1);
            Menu_U(A); 
            break;
          case 1:
            cout << "\033[0;0H\033[2J";
            //system("cls");
            centrarTexto("Soporte Voz y Mensajes",1);
            centrarTexto("Si experimentas problemas con llamadas o mensajes, te recomendaría reiniciar tu teléfono. A veces, eso resuelve pequeños problemas de conexión.",1);
            cout << endl;
        centrarTexto("¿Resolvio su problema?",1);
            centrarTexto("1. Si",1);
            centrarTexto("2. No",1);
            centrarTexto("Digite la opcion: ",0); cin >> opc;
            if (opc == 1){
              Calificacion_Bot();
          centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
          centrarTexto("Volviendo al Menu Principal...",1);
          cout << endl;
          Menu_I(A);
                }else{
                  cout << endl;
                  Menu_U(A);       
            }
            break;
          case 2:
            cout << "\033[0;0H\033[2J";
            //system("cls");
            centrarTexto("Soporte Datos Moviles",1);
            centrarTexto("Para problemas con datos móviles, asegúrate de que la función esté habilitada en la configuración de tu teléfono. Si aún así no funciona, reinicia tu dispositivo o verifica si hay actualizaciones de software.",1);
            cout << endl;
        centrarTexto("¿Resolvio su problema?",1);
            centrarTexto("1. Si",1);
            centrarTexto("2. No",1);
            centrarTexto("Digite la opcion: ",0); cin >> opc;
            if (opc == 1){
              Calificacion_Bot();
          centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
          centrarTexto("Volviendo al Menu Principal...",1);
          cout << endl;
          Menu_I(A);
                }else{
                  cout << endl;
                  Menu_U(A);       
            }
            break;
          case 3:
            cout << "\033[0;0H\033[2J";
            //system("cls");
            centrarTexto("Gestionar Plan",1);
            centrarTexto("Para gestionar tu plan, debes comunicarte a la línea de atención al cliente 6004505000 (Bogota) en los horarios de L-V 8 AM a 5 PM y S 8 AM a 2 PM.",1);
            cout << endl;
        centrarTexto("¿Resolvio su problema?",1);
            centrarTexto("1. Si",1);
            centrarTexto("2. No",1);
            centrarTexto("Digite la opcion: ",0); cin >> opc;
            if (opc == 1){
              Calificacion_Bot();
          centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
          centrarTexto("Volviendo al Menu Principal...",1);
          cout << endl;
          Menu_I(A);
                }else{
                  cout << endl;
                  Menu_U(A);       
            }
            break;
        default:
            centrarTexto("Opcion no valida.", 1);
            cout << endl;
            break;	    
      }
    }while (opcion != 3);
}



void Cola::Menu_U(Cola &A){
  int opcion;
  do{
      centrarTexto("MENU USUARIOS.",1);
      centrarTexto("0. Volver al Menu Principal",1);
      centrarTexto("1. Saldo y Pagos",1);
      centrarTexto("2. Conoce tu Plan",1);
      centrarTexto("3. Soporte Tecnico",1);
      centrarTexto("4. Asesor",1);
      centrarTexto("Digite la opcion: ",0); cin >> opcion;
      cout << endl;
      switch(opcion){
        case 0:
            centrarTexto("Volviendo al Menu Principal...",1);
            cout << endl;
        Menu_I(A);
            break;
          case 1:
            cout << "\033[0;0H\033[2J";
            //system("cls");
            Saldo_Pagos(A);
            break;
          case 2:
            cout << "\033[0;0H\033[2J";
            //system("cls");
            Plan(A);
            break;
          case 3:
            cout << "\033[0;0H\033[2J";
            //system("cls");
            Menu_S(A);
            break;
        case 4:
          cout << "\033[0;0H\033[2J";
          //system("cls");
          Asesor(A);
            break;
        default:
            centrarTexto("Opcion no valida.", 1);
            cout << endl;
            break;
      }
  }while (opcion != 0);
}

void Cola::Menu_I(Cola &A){
  int opcion;
    do{
      centrarTexto("MENU.",1);
      centrarTexto("0. Salir",1);
      centrarTexto("1. Menu Usuarios",1);
      centrarTexto("2. Menu Asesores",1);
      centrarTexto("Digite la opcion: ",0); cin >> opcion;
      cout << endl;
      switch(opcion){
        case 0:
            centrarTexto("Gracias por Usar Nuestro Chat de Servicio al Cliente",1);
            centrarTexto("Saliendo del programa...",1);
            exit(0);
            break;
          case 1:
            centrarTexto("Pasando al Menu Usuarios ...",1);
            cout << endl;
        Menu_U(A);		        
            break;
          case 2:
            centrarTexto("Pasando al Menu Asesores ...",1);
            cout << endl;
            Menu_A(A);
            break;
          default:
            centrarTexto("Opcion no valida.", 1);
            cout << endl;
            break;        
      }
  }while(opcion != 2);
}

void Cola::Menu_A(Cola &A){
  int opc;
    do{
      if(A.colavaciaC()){
        centrarTexto("La cola se encuentra vacia y no hay clientes en espera ",1);
    return; 
      }else{
        cout << "\033[0;0H\033[2J";
        //system("cls");
        Imprimir();
          centrarTexto("MENU ASESORES.",1);
          centrarTexto("0. Volver al Menu Principal",1);
          centrarTexto("1. Atender un Cliente",1);
          centrarTexto("2. Borrar Cola",1);
          centrarTexto("Digite la opción: ",0); cin >> opc;
          cout<<endl;
          switch(opc){
            case 0:
              centrarTexto("Volviendo al Menu Principal...",1);
              break;
            case 1:
              cout << "\033[0;0H\033[2J";
              //system("cls");
              centrarTexto("Ha seleccinado la opción 1. Atender un cliente de la cola",1);
              Atender(A);      
              cout << endl;
            break;
            case 2:
              cout << "\033[0;0H\033[2J";
              //system("cls");
              centrarTexto("Ha seleccinado la opción 2. Borrar Cola",1);
              centrarTexto("¿Estas Seguro de Borrar la Cola de Clientes?",1);
              centrarTexto("1. Si ",1);
              centrarTexto("2. No ",1);
              cin>> opc;
              if(opc==1){
                A.borrarC();
                exit(0);
              }else{
                cout << endl;
                Menu_A(A);
          }
            break;
            default:
              centrarTexto("Opcion no valida.", 1);
              cout << endl;
              break;
            }  
      }
    }while(opc != 2);
}

void Cola::Calificacion_Bot(){
  int calificacion;
  bool out = false;
  ofstream archivo;

  archivo.open("calificacion.txt", ios::app);//Abrir Archivo en modo añadir
    if(archivo.fail()){
      centrarTexto("No se pudo abrir el archivo",1);
    }
    centrarTexto("Gracias por Usar Nuestros Servicios. ",1);
    centrarTexto("Califica la Atencion Recibida del 1 al 5 (Donde 1 -> Pesimo Servicio y 5 -> Excelente Servicio)",1);
    do{
      centrarTexto("Digite su Puntuacion: ",0);
      cin >> calificacion;
    if(calificacion < 6 && calificacion > 0){
      archivo << calificacion << endl;
      archivo.close();
      out = true;
    }else{
      centrarTexto("Lo sentimos, el numero ingresado no es valido. Intente de nuevo con un numero valido (1-5)",1);
      }	
    }while(out==false);
};


int main(){

  int maxTamC = 20;
  Cola A(maxTamC);

  A.centrarTexto("---BIENVENIDO A NUESTRO CHAT DE ATENCIÓN AL CLIENTE DE CLARO---",1);;
    cout << endl;
  A.BorrarArchivo();
    cout<<endl;

    A.Menu_I(A);

    return 0;
}