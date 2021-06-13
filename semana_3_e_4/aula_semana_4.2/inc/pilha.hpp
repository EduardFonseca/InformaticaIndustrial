#ifndef PILHA_H
#define PILHA_H
#include <iostream>

template <typename T>
class Pilha
{
private:
    int tam;
    int top;
    T *pPtr;

public:
    Pilha(int tam = 10);
    ~Pilha();

    bool insere(const T &);
    bool remove(T &);
    bool estaVazio() const;
    bool estaCheio() const;

    int getTam() const;
};

template <typename T>
Pilha<T>::Pilha(int tam)
{
    this->tam = tam > 0 ? tam : 10;
    this->top = -1;
    this->pPtr = new T[this->tam];
}

template <typename T>
Pilha<T>::~Pilha()
{
    std::cout<<"destrutor da classe Pilha invocado"<<std::endl;
    delete[] this->pPtr; //deletar o espaco de memoria do nosso ponteiro
}

template <typename T>
bool Pilha<T>::insere(const T &valor)
{
    if (!estaCheio())
    {
        pPtr[++this->top] = valor; //faco a adicao do valor a ultima posicao da pilha
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Pilha<T>::remove(T &var)
{
    if (!estaVazio())
    {
        var = pPtr[this->top--]; //removo o valor da ultima posicao da pilha
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Pilha<T>::estaCheio() const
{
    return top == tam - 1;
}

template <typename T>
bool Pilha<T>::estaVazio() const
{
    return top == -1;
}

template <typename T>
int Pilha<T>::getTam() const
{
    return this->tam;
}

#endif