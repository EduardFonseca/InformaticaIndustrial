#ifndef FILA_H
#define FILA_H
#include <iostream>

template <typename T>
class Fila
{
private:
    int tam;
    int top;
    int bottom;
    T *pPtr;

public:
    Fila(int tam = 10);
    ~Fila();

    bool insere(const T &);
    bool remove(T &);
    bool estaVazio() const;
    bool estaCheio() const;

    int getTam() const;
};

template <typename T>
Fila<T>::Fila(int tam)
{
    this->tam = tam > 0 ? tam : 10;
    this->top = -1;
    this->bottom = -1;
    this->pPtr = new T[this->tam+1];
}

template <typename T>
Fila<T>::~Fila()
{
    std::cout << "destrutor da classe Fila invocado" << std::endl;
    delete[] this->pPtr; //deletar o espaco de memoria do nosso ponteiro
}

template <typename T>
bool Fila<T>::insere(const T &valor)
{
    if (!estaCheio())
    {
        if (this->top == this->tam)
        {
            top = -1;
        }
        pPtr[++top] = valor; //faco a adicao do valor a ultima posicao da pilha
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Fila<T>::remove(T &var)
{
    if (!estaVazio())
    {
        if (bottom == tam)
        {
            bottom = -1;
        }
        var = pPtr[++bottom]; //removo o valor da ultima posicao da pilha
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Fila<T>::estaCheio() const
{
    if (top == tam - 1 && bottom == -1 || bottom == 0 && top == tam)
    {
        return true;
    }
    else
    {
        return bottom - top == 1;
    }
}

template <typename T>
bool Fila<T>::estaVazio() const
{
    return top == bottom;
}

template <typename T>
int Fila<T>::getTam() const
{
    return this->tam;
}

#endif