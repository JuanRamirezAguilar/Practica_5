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
    ifstream archivoChequesSalida(NAMEFILECHEQUE, ios::out | ios::app | ios::binary);
    ifstream archivoChequesReSalida(NAMEFILECHEQUERE, ios::out | ios::app | ios::binary);
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
                    cheques + miCheque;
                    cout << endl << endl << "Cheque añadido a la pila."; pausa();
                } else {
                    cout << "La pila de cheques ya esta llena..." <<endl; pausa();
                }
            break;

            case PROCESARCHEQUE:
                if (!cheques.vacia()) {
                    cout << endl << "Se va procesar el cheque: " <<endl;
                    cheques.top().imprimeDatos(); pausa();

                    cheques.pop();
                    cout << endl << "Cheque procesado..."; pausa();

                } else {
                    cout << "La pila de cheques esta vacia: " <<endl; pausa();
                }
                break;

            case REGISTRARCHEQUERE:
                break;
            case PROCESARCHEQUERE:
                break;

            case SALIR: {
                ofstream archivoChequesEntrada;
                ofstream archivoChequesRechazadosEntrada;
                Cheque chequeAux;
                ChequeRechazado chequeReAux;

                // Guardar en el archivo. Se abre en modo trunc para que los datos anteriores se borren
                archivoChequesEntrada.open(NAMEFILECHEQUE, ios::in | ios::trunc | ios::binary);
                archivoChequesRechazadosEntrada.open(NAMEFILECHEQUERE, ios::in | ios::trunc | ios::binary);
                if (!archivoChequesSalida.is_open() or !archivoChequesRechazadosEntrada.is_open()) {
                    throw ios_base::failure("Error al abrir el archivo.");
                }

                // Revisa si las pila no esta vacia
                if (!cheques.vacia()) {
                    for (int i = 0; i < cheques.getTam(); i++) {
                        chequeAux = cheques.top();
                        archivoChequesEntrada.seekp((cheques.top().getNumero() - 1) * int(sizeof(Cheque)));
                        archivoChequesEntrada.write(reinterpret_cast<char*>(&chequeAux), sizeof(Cheque));
                        cheques.pop();
                    }    
                }

                // Revisa si las pila no esta vacia
                if (!chequesRechazados.vacia()) {
                    for (int i = 0; i < chequesRechazados.getTam(); i++) {
                        chequeReAux = chequesRechazados.top();
                        archivoChequesRechazadosEntrada.seekp((chequesRechazados.top().getNumero() - 1) * int(sizeof(Cheque)));
                        archivoChequesRechazadosEntrada.write(reinterpret_cast<char*>(&chequeReAux), sizeof(Cheque));
                        chequesRechazados.pop();
                    }
                }

                archivoChequesSalida.close();
                archivoChequesRechazadosEntrada.close();
            }break;

            case 6:
                if (!cheques.vacia()) {
                    cheques.top().imprimeDatos(); pausa();
                } else {
                    cout << endl << "Vacia..."; pausa();
                }
                break;
            default:
                break;
        }

    } while (opc != SALIR);

    return 0;
}

void pausa () { cin.clear(); cin.sync(); cin.ignore(); }