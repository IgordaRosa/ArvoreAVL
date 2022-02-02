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
    protected:
    Nodo<T> * RotacaoSimplesEsquerda(Nodo<T> * nodoPai, T chave) const
    {
        Nodo<T> * nodo = this->FilhoQueContem(nodoPai, chave);
        Nodo<T> * aux = nodo->filhoDireita;
        nodoPai->filhoEsquerda->filhoDireita = nodoPai;
        nodoPai->filhoEsquerda = aux;

        if(this->NodoRaiz->chave == nodoPai->chave)
            this->NodoRaiz->chave = nodo->chave;

        return nodoPai;
    };

    Nodo<T> * RotacaoSimplesDireita(Nodo<T> * nodoPai, T chave) const
    {
        Nodo<T> * nodo = this->FilhoQueContem(nodoPai, chave);
        Nodo<T> * aux = nodo->filhoEsquerda;
        nodoPai->filhoDireita->filhoEsquerda = nodoPai;
        nodoPai->filhoDireita = aux;

        nodoPai = nodo;

        return nodoPai;
    };

    Nodo<T> * RotacaoEsquerdaDireita(Nodo<T> * nodoPai, T chave) const
    {
        
    };

    Nodo<T> * RotacaoDireitaEsquerda(Nodo<T> * nodoPai, T chave) const
    {
        
    };  

    ///////////////////////////////////////////////////////////////////////
    //Busca pai refeita de forma recursiva
    Nodo<T> * BuscarPai(Nodo<T> * nodo, T chave) const
    {
        if(nodo == nullptr)
        {
            return nodo;
        }
        
        if(nodo->chave == chave)
        {
            return nodo;
        }

        if(nodo->filhoEsquerda != nullptr and nodo->filhoEsquerda->chave == chave)
        {
            return nodo;
        }

        if(nodo->filhoDireita != nullptr and nodo->filhoDireita->chave == chave)
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
    void Balancear(Nodo<T> * nodoPai, T chave) const
    {
        while(nodoPai->chave != this->NodoRaiz->chave)
        {    
            if(nodoPai == nullptr)
                return;
            int b = B(nodoPai);
            if(b < -1 and B(nodoPai->filhoDireita) <= 0)
            {
                nodoPai = RotacaoSimplesEsquerda(nodoPai, chave);
            }
            else if(b < -1 and B(nodoPai->filhoDireita) > 0)
            {
                nodoPai = RotacaoDireitaEsquerda(nodoPai, chave);
            }
            else if(b > 1 and B(nodoPai->filhoEsquerda) >= 0)
            {
                nodoPai = RotacaoSimplesDireita(nodoPai, chave);
            }
            else if(b > 1 and B(nodoPai->filhoEsquerda) < 0)
            {
                nodoPai = RotacaoEsquerdaDireita(nodoPai, chave);
            }
        }
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
        return Maior(this->AlturaDoNodo(nodo->filhoEsquerda), this->AlturaDoNodo(nodo->filhoDireita)) + 1;;
    };

    ///////////////////////////////////////////////////////////////////////
    public:
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    std::optional<int> altura(T chave) const override
    {
        Nodo<T> * nodo = MinhaArvoreDeBuscaBinaria<T>::BuscaNaArvore(this->NodoRaiz, chave);
        if(nodo == nullptr)
            return std::nullopt;
        return AlturaDoNodo(nodo);
    };
    
    ///////////////////////////////////////////////////////////////////////
    public:
    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
    void inserir(T chave)
    {
        MinhaArvoreDeBuscaBinaria<T>::inserir(chave);
        Nodo<T> * nodoPai = BuscarPai(this->NodoRaiz, chave);
        if(nodoPai)
            Balancear(nodoPai, chave);
    };

    ///////////////////////////////////////////////////////////////////////
    public:
    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    void remover(T chave)
    {
        MinhaArvoreDeBuscaBinaria<T>::remover(chave);
        Nodo<T> * nodoPai = BuscarPai(this->NodoRaiz, chave);
        if(nodoPai)
            Balancear(nodoPai, chave);
    };

    ///////////////////////////////////////////////////////////////////////
};

#endif