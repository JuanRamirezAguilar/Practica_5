#pragma once

#include "Cheque.hpp"

class ChequeRechazado : public Cheque {
    private:
        double cargo;

    public:
        ChequeRechazado();
        ChequeRechazado(int, char[], int, double);
        ~ChequeRechazado();

        void imprimeDatos();
        ChequeRechazado operator = (const ChequeRechazado& copia);
};