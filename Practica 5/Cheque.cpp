#include "Cheque.hpp"

#include <iostream>
#include <string.h>

Cheque::Cheque() {}

Cheque::Cheque(int numCta, const char nomBco[], int cta, double mon) {
    numero = numCta;
    cuentaADepositar = cta;
    monto = mon;
    strcpy(banco, nomBco);
}

Cheque::~Cheque() {}

Cheque::Cheque(const Cheque& copia) : numero(copia.numero), cuentaADepositar(copia.cuentaADepositar), monto(copia.monto) {
    strcpy(banco, copia.banco);
}

int Cheque::getNumero() { return numero; }

void Cheque::imprimeDatos() {
    std::cout << std::endl << "Numero de cheques: " << numero;
    std::cout << std::endl << "Del banco: " << banco;
    std::cout << std::endl << "Depositado en la cuenta: " << cuentaADepositar;
    std::cout << std::endl << "Monto: " << monto <<std::endl;
}

Cheque& Cheque::operator = (const Cheque& copia) {
    if (this == &copia) { return *this; }
    
    numero = copia.numero;
    cuentaADepositar = copia.cuentaADepositar;
    strcpy(banco, copia.banco);
    monto = copia.monto;
    return *this;
}