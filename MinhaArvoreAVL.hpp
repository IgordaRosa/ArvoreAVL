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
    public:
    ~MinhaArvoreAVL()
    {
        
    };

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
     */
    //bool vazia() const {};
    
    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    //int quantidade() const {};
    
    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    //bool contem(T chave) const {};
    
    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos. Se chave é nula, retorna a altura da arvore.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    //std::optional<int> altura(T chave) const {};

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */        
    //void inserir(T chave) {};

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     * @return Retorna a chave removida ou nullptr se a chave nao esta na arvore
     */        
    //void remover(T chave) {};

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    //std::optional<T> filhoEsquerdaDe(T chave) const {};

    ///////////////////////////////////////////////////////////////////////
    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */     
    //std::optional<T> filhoDireitaDe(T chave) const {};

    ///////////////////////////////////////////////////////////////////////
};

#endif