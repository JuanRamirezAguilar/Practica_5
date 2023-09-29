#include "ChequeRechazado.hpp"

#include <iostream>

ChequeRechazado::ChequeRechazado() {}

ChequeRechazado::ChequeRechazado(int numCta, char* nomBco, int cta, double mon) : Cheque(numCta, nomBco, cta, mon) {
    cargo = mon * 0.10;
}

ChequeRechazado::~ChequeRechazado() {}

void ChequeRechazado::imprimeDatos() {
    Cheque::imprimeDatos();
    std::cout << std::endl << "Cargo por rechazo: " << cargo <<std::endl;
}

ChequeRechazado ChequeRechazado::operator = (const ChequeRechazado& copia) {
    cargo = copia.cargo;
    return *this;
}