#ifndef PILA_H
#define PILA_H

template <class DATO, std::size_t MAX_TAM>
class Pila {
    private:
        DATO elementos[MAX_TAM];
        int tope;

    public:
        // Constructores
        Pila();
        Pila(const Pila& otra);

        // Metodos de la pila
        bool vacia();
        bool llena();
        void push(DATO elemento);
        void pop();
        DATO top();

        // Getters
        std::size_t getTam();

        // Operadores sobrecargados
        Pila<DATO, MAX_TAM>& operator=(const Pila<DATO, MAX_TAM>& otra);
        void operator + (const DATO& elemento);
        void operator-(DATO& elemento);

};

// Definicion del constructor default
template <class DATO, std::size_t MAX_TAM>
Pila<DATO, MAX_TAM>::Pila() {
    tope = -1;
}

// Definicion del constructor por parametros
template <class DATO, std::size_t MAX_TAM>
Pila<DATO, MAX_TAM>::Pila(const Pila& otra) {
    std::copy(otra.elementos, otra.elementos + MAX_TAM, elementos);
    tope = otra.tope;
}

// Definición del método vacia()
template <class DATO, std::size_t MAX_TAM>
bool Pila<DATO, MAX_TAM>::vacia() {
    return tope == -1;
}

// Definición del método llena()
template <class DATO, std::size_t MAX_TAM>
bool Pila<DATO, MAX_TAM>::llena() {
    return tope == MAX_TAM - 1;
}

// Definición del método push()
template <class DATO, std::size_t MAX_TAM>
void Pila<DATO, MAX_TAM>::push(DATO elemento) {
    if (llena()) {
        std::cout << "Error: la pila está llena." << std::endl;
        return;
    }
    elementos[++tope] = elemento;
}

// Definición del método pop()
template <class DATO, std::size_t MAX_TAM>
void Pila<DATO, MAX_TAM>::pop() {
    if (vacia()) {
        std::cout << "Error: la pila está vacía." << std::endl;
        return;
    }
    --tope;
}

// Definición del método top()
template <class DATO, std::size_t MAX_TAM>
DATO Pila<DATO, MAX_TAM>::top() {
    if (vacia()) {
        std::cout << "Error: la pila está vacía." << std::endl;
        return DATO();
    }
    return elementos[tope];
}

// Definición del getter geTam
template <class DATO, std::size_t MAX_TAM>
std::size_t Pila<DATO, MAX_TAM>::getTam() { return MAX_TAM; }

// Definición de la sobreacarga de operador "+"
template <class DATO, std::size_t MAX_TAM>
void Pila<DATO, MAX_TAM>::operator + (const DATO& elemento) {
    if (llena()) {
        std::cout << "Error: la pila está llena." << std::endl;
        return;
    }
    elementos[++tope] = elemento;
}

// Definición de la sobreacarga de operador "-"
template <class DATO, std::size_t MAX_TAM>
void Pila<DATO, MAX_TAM>::operator - (DATO& elemento) {
    if (vacia()) {
        std::cout << "Error: la pila está vacía." << std::endl;
        return;
    }
    elemento = elementos[tope--];
}

// Definición de la sobreacarga de operador "="
template <class DATO, std::size_t MAX_TAM>
Pila<DATO, MAX_TAM>& Pila<DATO, MAX_TAM>::operator=(const Pila<DATO, MAX_TAM>& otra) {
    if (this == &otra) {
        return *this; // Evitar autoasignación
    }

    std::copy(otra.elementos, otra.elementos + MAX_TAM, elementos);
    tope = otra.tope;

    return *this;
}

#endif // PILA_H