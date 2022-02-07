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
    //Rotações
    protected:
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
    //Balanceamento
    Nodo<T> * ReBalancear(Nodo<T> * nodo)
    {
        if(nodo->filhoEsquerda)
            nodo->filhoEsquerda = Balancear(nodo->filhoEsquerda);
                
        if(nodo->filhoDireita)
            nodo->filhoDireita = Balancear(nodo->filhoDireita);
        return nodo;
    };

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
        
        if(nodoPai->chave == this->NodoRaiz->chave)
            return nodoPai;

        return nodoPai;
    };

    ///////////////////////////////////////////////////////////////////////
    //Fator B
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
    //Inserir um nodo
    protected:
    Nodo<T> * NovoNodo(Nodo<T> * nodo, T chave)
    {
        Nodo<T> * novoNodo = new Nodo<T>();
        novoNodo->chave = chave;
        novoNodo->altura = nodo->altura + 1;
        return novoNodo;
    };

    void NovoNodoRaiz(T chave)
    {
        Nodo<T> * novoNodo = new Nodo<T>();
        novoNodo->chave = chave;
        novoNodo->altura = 0;
        this->NodoRaiz = novoNodo;
    };

    void ins(Nodo<T> * nodo, T chave)
    {
        if(chave < nodo->chave)
        {
            if(!nodo->filhoEsquerda)
                nodo->filhoEsquerda = NovoNodo(nodo, chave);
            
            else
            {
                ins(nodo->filhoEsquerda, chave);
                nodo = ReBalancear(nodo);
            }
        }
        else
        {
            if(!nodo->filhoDireita)
                nodo->filhoDireita = NovoNodo(nodo, chave);
            
            else
            {
                ins(nodo->filhoDireita, chave);
                nodo = ReBalancear(nodo);
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
            return NovoNodoRaiz(chave);
        ins(this->NodoRaiz, chave);
        this->NodoRaiz = Balancear(this->NodoRaiz);
    };

    ///////////////////////////////////////////////////////////////////////
    //Remover um nodo
    protected:
    void re(Nodo<T> * nodoPai, T chave)
    {
        if(!nodoPai)
            return;

        Nodo<T> * nodo = this->FilhoQueContem(nodoPai, chave);

        if(nodoPai == nodo and !nodoPai->filhoEsquerda and !nodoPai->filhoDireita)
        {
            nodoPai = nullptr;
            delete nodoPai;
            return;
        }
    
        else if(nodoPai->filhoEsquerda == nodo and !nodo->filhoEsquerda and !nodo->filhoDireita)
        {
            nodoPai->filhoEsquerda = nullptr;
            delete nodo;
            return;
        }

        else if(nodoPai->filhoDireita == nodo and !nodo->filhoEsquerda and !nodo->filhoDireita)
        {
            nodoPai->filhoDireita = nullptr;
            delete nodo;
            return;
        }

        if(nodo->filhoDireita)
        {
            Nodo<T> * aux = nodo->filhoDireita;
            Nodo<T> * auxPai = nodo;
            while(aux->filhoEsquerda)
            {
                auxPai = aux;
                aux = aux->filhoEsquerda;
            }
            nodo->chave = aux->chave;
            aux->chave = chave;
            re(auxPai, chave);
            nodoPai = ReBalancear(nodoPai);
        }
    };

    public:
    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    void remover(T chave) override
    {
        if(this->NodoRaiz->chave == chave and\
        !this->NodoRaiz->filhoEsquerda and\
        !this->NodoRaiz->filhoDireita)
        {
            delete this->NodoRaiz;
            this->NodoRaiz = nullptr;
            return;
        }
        if(this->contem(chave))
        {
            re(this->BuscaPaiNaArvore(this->NodoRaiz, chave), chave);
            this->NodoRaiz = Balancear(this->NodoRaiz);
        }
    };

    ///////////////////////////////////////////////////////////////////////
};

#endif