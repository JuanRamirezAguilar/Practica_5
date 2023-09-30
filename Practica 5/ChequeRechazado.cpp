#include "ChequeRechazado.hpp"

#include <iostream>

ChequeRechazado::ChequeRechazado() {}

ChequeRechazado::ChequeRechazado(int numCta, const char nomBco[], int cta, double mon) : Cheque(numCta, nomBco, cta, mon) {
    cargo = mon * 0.10;
}

ChequeRechazado::ChequeRechazado(const ChequeRechazado& copia) : Cheque(copia), cargo(copia.cargo) {}

ChequeRechazado::~ChequeRechazado() {}

void ChequeRechazado::imprimeDatos() {
    Cheque::imprimeDatos();
    std::cout << std::endl << "Cargo por rechazo: " << cargo <<std::endl;
}

ChequeRechazado& ChequeRechazado::operator = (const ChequeRechazado& copia) {
    if (this == &copia) { return *this; }

    Cheque::operator=(copia);
    cargo = copia.cargo;
    return *this;
}