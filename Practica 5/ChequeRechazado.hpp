#pragma once

#include "Cheque.hpp"

class ChequeRechazado : public Cheque {
    private:
        double cargo;

    public:
        ChequeRechazado();
        ChequeRechazado(int, const char[], int, double);
        ChequeRechazado(const ChequeRechazado& copia);
        ~ChequeRechazado();

        void imprimeDatos();
        ChequeRechazado& operator = (const ChequeRechazado& copia);
};