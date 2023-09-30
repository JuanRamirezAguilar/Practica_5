#ifndef CHEQUE_HPP
#define CHEQUE_HPP

class Cheque {
    private:
        int numero, cuentaADepositar;
        char banco[10];
        double monto;

    public:
        Cheque();
        Cheque(int, const char[], int, double);
        Cheque(const Cheque& copia);
        ~Cheque();
        
        int getNumero();
        void imprimeDatos();

        Cheque& operator = (const Cheque& copia);
};

#endif // CHEQUE_HPP