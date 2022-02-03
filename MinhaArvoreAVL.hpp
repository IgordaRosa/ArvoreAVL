#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "MinhaArvoreDeBuscaBinaria.hpp" 

/**
 * @brief Representa uma árvore AVL.
 * 
 * @tparam T O tipo de dado guardado na árvore.
 */ 
template <typename T>
class MinhaArvoreAVL final : public MinhaArvoreDeBuscaBinaria<T>
{
    ///////////////////////////////////////////////////////////////////////
    private:
    Nodo<T> * RotacaoSimplesEsquerda(Nodo<T> * A)
    {
        
        Nodo<T> * C = A->filhoDireita;
        Nodo<T> * D = C->filhoEsquerda;
        C->filhoEsquerda = A;
        A->filhoDireita = D;
        return C;
    };

    Nodo<T> * RotacaoSimplesDireita(Nodo<T> * A)
    {
        Nodo<T> * B = A->filhoEsquerda;
        Nodo<T> * E = B->filhoDireita;
        B->filhoDireita = A;
        A->filhoEsquerda = E;
        return B;
    };

    Nodo<T> * RotacaoEsquerdaDireita(Nodo<T> * A)
    {
        A->filhoEsquerda = RotacaoSimplesEsquerda(A->filhoEsquerda);
        return RotacaoSimplesDireita(A);
    };

    Nodo<T> * RotacaoDireitaEsquerda(Nodo<T> * A)
    {
        A->filhoDireita = RotacaoSimplesDireita(A->filhoDireita);
        return RotacaoSimplesEsquerda(A);
    };  
    
    ///////////////////////////////////////////////////////////////////////
    Nodo<T> * Balancear(Nodo<T> * nodoPai)
    {
        if(!nodoPai)
            return nullptr;
        int b = B(nodoPai);

        if(b < -1 and B(nodoPai->filhoDireita) <= 0)
            return RotacaoSimplesEsquerda(nodoPai);
        
        else if(b < -1 and B(nodoPai->filhoDireita) > 0)
            return RotacaoDireitaEsquerda(nodoPai);
        
        else if(b > 1 and B(nodoPai->filhoEsquerda) >= 0)
            return RotacaoSimplesDireita(nodoPai);
        
        else if(b > 1 and B(nodoPai->filhoEsquerda) < 0)
            return RotacaoEsquerdaDireita(nodoPai);
        
        if(nodoPai->chave = this->NodoRaiz->chave)
            return nodoPai;

        return Balancear(BuscarPai(this->NodoRaiz, nodoPai->chave));
    };

    ///////////////////////////////////////////////////////////////////////
    int B(Nodo<T> * nodo) const
    {
        if(nodo)
            return (this->AlturaDoNodo(nodo->filhoEsquerda) - this->AlturaDoNodo(nodo->filhoDireita));
        return 0;
    };

    int Maior(int a, int b) const
    {
        if(a > b)
            return a;
        return b;
    };

    int AlturaDoNodo(Nodo<T> * nodo) const
    {
        if(nodo == nullptr)
            return -1;
        return AtualizarAltura(nodo);
    };

    int AtualizarAltura(Nodo<T> * nodo) const
    {
        return Maior(this->AlturaDoNodo(nodo->filhoEsquerda), this->AlturaDoNodo(nodo->filhoDireita)) + 1;
    };

    ///////////////////////////////////////////////////////////////////////
    Nodo<T> * BuscarPai(Nodo<T> * nodo, T chave) const
    {
        if(nodo == nullptr)
        {
            return nodo; 
        }

        if(nodo->chave != chave) 
        {
            return nodo;
        }

        if(nodo->filhoEsquerda != nullptr and\
        nodo->filhoEsquerda->chave == chave)
        {
            return nodo; 
        }

        if(nodo->filhoDireita != nullptr and\
        nodo->filhoDireita->chave == chave)
        {
            return nodo; 
        }

        if(nodo != nullptr and nodo->filhoEsquerda != nullptr)
        {
            return BuscarPai(nodo->filhoEsquerda, chave);
        }
        
        if(nodo != nullptr and nodo->filhoDireita != nullptr)
        {
            return BuscarPai(nodo->filhoDireita, chave);
        }
        return nodo;
    };
    
    ///////////////////////////////////////////////////////////////////////
    protected:
    void ins(Nodo<T> * nodo, T chave) const
    {
        if(chave < nodo->chave)
        {
            if(nodo->filhoEsquerda == nullptr)
            {
                Nodo<T> * novoNodo = new Nodo<T>();
                novoNodo->chave = chave;
                nodo->filhoEsquerda = novoNodo;
                novoNodo->altura = nodo->altura + 1;
            }
            else
            {
                ins(nodo->filhoEsquerda, chave);
            }
        }
        else
        {
            if(nodo->filhoDireita == nullptr)
            {
                Nodo<T> * novoNodo = new Nodo<T>();
                novoNodo->chave = chave;
                nodo->filhoDireita = novoNodo;
                novoNodo->altura = nodo->altura + 1;
            }
            else
            {
                ins(nodo->filhoDireita, chave);
            }
        }
    };
    
    public:
    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
    void inserir(T chave) override
    {
        if(this->vazia())
        {
            Nodo<T> * novoNodo = new Nodo<T>();
            novoNodo->chave = chave;
            novoNodo->altura = 0;
            this->NodoRaiz = novoNodo;
            return;
        }
        ins(this->NodoRaiz, chave);
        Nodo<T> * nodoPai = this->BuscarPai(this->NodoRaiz, chave);
        this->NodoRaiz = this->Balancear(nodoPai);
D    };

    ///////////////////////////////////////////////////////////////////////
    public:
    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    void remover(T chave) override
    {
        MinhaArvoreDeBuscaBinaria<T>::remover(chave);
    };

    ///////////////////////////////////////////////////////////////////////
};

#endif