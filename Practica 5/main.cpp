/*
    I5888 - Estructuras de Datos 2
    D06 - L, Mi 7 a 9 pm - 2023B

    Integrantes equipo 6:

    Ramírez Aguilar Juan Antonio
    Ramírez Martin Angel Omar
    Ramírez Martínez Luis Felipe
    Ríos Ventura Jexan Alexander
*/

#include <iostream>
#include <fstream>
#include <windows.h>

#include "Cheque.hpp"
#include "ChequeRechazado.hpp"
#include "Pila.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define NAMEFILECHEQUE "cheques.dat"
#define NAMEFILECHEQUERE "cheques_rech.dat"

enum OPCIONES { REGISTRARCHEQUE = 1, PROCESARCHEQUE, REGISTRARCHEQUERE, PROCESARCHEQUERE, SALIR };

using namespace std;

void pausa();

int main () {

    // Establece el código de página de salida a UTF-8
    SetConsoleOutputCP(CP_UTF8);

    // Pilas del programa
    Pila<Cheque, 2> cheques;
    Pila<ChequeRechazado, 2> chequesRechazados;

    // Se crean los archivos de los cheques
    ifstream archivoChequesSalida;
    ifstream archivoChequesReSalida;

    if (!ifstream(NAMEFILECHEQUE) or !ifstream(NAMEFILECHEQUERE)) {
        // Si no existen, crea los archivos
        ofstream createFile(NAMEFILECHEQUE);
        ofstream createReFile(NAMEFILECHEQUERE);
        createFile.close();
        createReFile.close();
    }

    // Se abren los archivos
    archivoChequesSalida.open(NAMEFILECHEQUE, ios::in | ios::binary);
    archivoChequesReSalida.open(NAMEFILECHEQUERE, ios::in | ios::binary);   

    if (!archivoChequesSalida.is_open() or !archivoChequesReSalida.is_open()) {
        throw ios_base::failure("No se pudieron abrir los archivos.");
    }

    // Se cargan los datos del archivo binario
    Cheque chequeTemp;
    while (archivoChequesSalida.read(reinterpret_cast<char*>(&chequeTemp), sizeof(Cheque))) {
            cheques.push(chequeTemp);
    }

    // Se cargan los datos del archivo binario
    ChequeRechazado chequeRechazadoTemp; // Objeto temporal para almacenar la lectura
    while (archivoChequesReSalida.read(reinterpret_cast<char*>(&chequeRechazadoTemp), sizeof(ChequeRechazado))) {
        chequesRechazados.push(chequeRechazadoTemp);
    }

    // Se cierran los archivos
    archivoChequesSalida.close();
    archivoChequesReSalida.close();

    int opc(-1);
    // Menu
    do {
        system(CLEAR);
        cout << "\tMenú - Administración de cheques" <<endl<<endl;
        cout << "1. Registrar Cheque - (insertar)" <<endl;
        cout << "2. Procesar Cheque - (eliminar)" <<endl;
        cout << "3. Registrar Cheque Rechazado - (insertar)" <<endl;
        cout << "4. Procesar Cheque Rechazado - (eliminar)" <<endl;
        cout << "5. Salir" <<endl<<endl;
        cout << "Elige tu opción: ";
        cin >> opc;

        // Switch para cada una de las opciones
        switch (opc) {
            case REGISTRARCHEQUE:
                if (!cheques.llena()) {
                    // Variables para el llenado de la clase
                    int numCheque, numCuenta;
                    string nameBanco;
                    double monto;
                    cout<<endl<<endl;

                    cout << "Dame el numero del cheque: ";
                    cin >> numCheque;
                    cout << "Dame el nombre del banco: ";
                    fflush(stdin); getline(cin, nameBanco);
                    cout << "Dame el numero de cuenta: ";
                    cin >> numCuenta;
                    cout << "Dame el monto del cheque: ";
                    cin >> monto;

                    // Se instancia el cheque
                    Cheque miCheque(numCheque, nameBanco.c_str(), numCuenta, monto);

                    // Se añade el cheque a la pila
                    cheques.push(miCheque);
                    cout << endl << "Cheque añadido a la pila."; pausa();
                } else {
                    cout << "La pila de cheques ya esta llena..." <<endl; pausa();
                }
            break;

            case PROCESARCHEQUE:
                if (!cheques.vacia()) {
                    cout << endl << "Se va procesar el cheque: " <<endl;
                    cheques.top().imprimeDatos(); pausa();

                    cheques.pop();
                    cout << "Cheque procesado..."; pausa();

                } else {
                    cout << "La pila de cheques esta vacia: " <<endl; pausa();
                }
                break;

            case REGISTRARCHEQUERE:
                if (!chequesRechazados.llena()) {
                    // Variables para el llenado de la clase
                    int numCheque, numCuenta;
                    string nameBanco;
                    double monto;
                    cout<<endl<<endl;

                    cout << "Dame el numero del cheque rechazado: ";
                    cin >> numCheque;
                    cout << "Dame el nombre del banco: ";
                    fflush(stdin); getline(cin, nameBanco);
                    cout << "Dame el numero de cuenta: ";
                    cin >> numCuenta;
                    cout << "Dame el monto del cheque rechazado: ";
                    cin >> monto;

                    // Se instancia el cheque
                    ChequeRechazado miChequeRe(numCheque, nameBanco.c_str(), numCuenta, monto);

                    // Se añade el cheque a la pila
                    chequesRechazados.push(miChequeRe);
                    cout << endl << "Cheque rechazado añadido a la pila."; pausa();
                } else {
                    cout << "La pila de cheques rechazados ya esta llena..." <<endl; pausa();
                }
                break;

            case PROCESARCHEQUERE:
                if (!chequesRechazados.vacia()) {
                    cout << endl << "Se va procesar el cheque rechazado: " <<endl;
                    chequesRechazados.top().imprimeDatos(); pausa();

                    chequesRechazados.pop();
                    cout << "Cheque rechazado procesado..."; pausa();

                } else {
                    cout << "La pila de cheques rechazados esta vacia: " <<endl; pausa();
                }
                break;

            case SALIR: {
                ofstream archivoChequesEntrada;
                ofstream archivoChequesRechazadosEntrada;

                cout << endl << "Guardando los datos..." <<endl;

                // Abrimos los archivos
                archivoChequesEntrada.open(NAMEFILECHEQUE, ios_base::out | ios_base::binary);
                archivoChequesRechazadosEntrada.open(NAMEFILECHEQUERE, ios_base::out | ios_base::binary);

                // Revisa si los archivos se abrieron correctamente
                if (!archivoChequesEntrada.is_open() or !archivoChequesRechazadosEntrada.is_open()) {
                    throw ios_base::failure("Error al abrir el archivo.");
                }

                // Revisa si las pila cheques no esta vacia
                while (!cheques.vacia()) {
                    Cheque chequeAux = cheques.top();
                    archivoChequesEntrada.write(reinterpret_cast<char*>(&chequeAux), sizeof(Cheque));
                    cheques.pop();
                }

                // Revisa si las pila chequesRechazados no esta vacia
                while (!chequesRechazados.vacia()) {
                    ChequeRechazado chequeReAux = chequesRechazados.top();
                    archivoChequesRechazadosEntrada.write(reinterpret_cast<char*>(&chequeReAux), sizeof(ChequeRechazado));
                    chequesRechazados.pop();
                }
                
                archivoChequesEntrada.close();
                archivoChequesRechazadosEntrada.close();
                cout << "Datos guardados exitosamente..." <<endl;
            }break;

            // Este case solo sirve para checar si las pilas se estaban llenanando correctamente
            // Es una opcion logica
            case 77:{
                int opcImpr;

                cout << endl << "1) cheques." <<endl;
                cout << endl << "2) cheques rechazados" <<endl;
                cin >> opcImpr;

                if (opcImpr == 1) {
                    Pila<Cheque, 2> PilaAux1 = cheques;
                    if (!PilaAux1.vacia()) {
                        while (!PilaAux1.vacia()) {
                            PilaAux1.top().imprimeDatos();
                            PilaAux1.pop();
                        } pausa();
                    } else {
                        cout << "Pila vacia"; pausa();
                    }
                } else if (opcImpr == 2) {
                    Pila<ChequeRechazado, 2> PilaAux2 = chequesRechazados;
                    if (!PilaAux2.vacia()) {
                        PilaAux2 = chequesRechazados;
                        while (!PilaAux2.vacia()) {
                            PilaAux2.top().imprimeDatos();
                            PilaAux2.pop();
                        } pausa();
                    } else {
                        cout << "Pila vacia"; pausa();
                    }
                } else {
                    cout << "opcion equivocada"; pausa();
                }
            }break;

            default:
                cout << endl << "Opcion equivocada, intentelo de nuevo..."; pausa();
                break;
        }

    } while (opc != SALIR);

    return 0;
}

void pausa () { cin.clear(); cin.sync(); cin.ignore(); }