#ifndef PILA_H
#define PILA_H

template <class DATO, int MAX_TAM>
class Pila {
    private:
        DATO elementos[MAX_TAM];
        int tope;

    public:
        Pila();
        bool vacia();
        bool llena();
        void push(DATO elemento);
        void pop();
        DATO top();
        int getTam();
        void operator + (const DATO& elemento) {
            if (llena()) {
                std::cout << "Error: la pila está llena." << std::endl;
                return;
            }
            elementos[++tope] = elemento;
        }
        void operator-(DATO& elemento) {
            if (vacia()) {
                std::cout << "Error: la pila está vacía." << std::endl;
                return;
            }
            elemento = elementos[tope--];
        }
};

// Definicion del constructor
template <class DATO, int MAX_TAM>
Pila<DATO, MAX_TAM>::Pila() {
    tope = -1;
}

// Definición del método vacia()
template <class DATO, int MAX_TAM>
bool Pila<DATO, MAX_TAM>::vacia() {
    return tope == -1;
}

// Definición del método llena()
template <class DATO, int MAX_TAM>
bool Pila<DATO, MAX_TAM>::llena() {
    return tope == MAX_TAM - 1;
}

// Definición del método push()
template <class DATO, int MAX_TAM>
void Pila<DATO, MAX_TAM>::push(DATO elemento) {
    if (llena()) {
        std::cout << "Error: la pila está llena." << std::endl;
        return;
    }
    elementos[++tope] = elemento;
}

// Definición del método pop()
template <class DATO, int MAX_TAM>
void Pila<DATO, MAX_TAM>::pop() {
    if (vacia()) {
        std::cout << "Error: la pila está vacía." << std::endl;
        return;
    }
    --tope;
}

// Definición del método top()
template <class DATO, int MAX_TAM>
DATO Pila<DATO, MAX_TAM>::top() {
    if (vacia()) {
        std::cout << "Error: la pila está vacía." << std::endl;
        return DATO();
    }
    return elementos[tope];
}

template<class DATO, int MAX_TAM>
int Pila<DATO, MAX_TAM>::getTam() { return MAX_TAM; }

#endif // PILA_H