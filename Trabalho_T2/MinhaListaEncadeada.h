#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 * 
 * @tparam T O tipo dos dados armazenados na lista.
 */
template<typename T>
class MinhaListaEncadeada: public ListaEncadeadaAbstrata<T>
{
    //Implemente aqui as funcões marcadas com virtual na ListaEncadeadaAbstrata
    //Lembre-se de implementar o construtor e destrutor da classe
    virtual ~MinhaListaEncadeada()
    {
        while (this->_primeiro != nullptr)
        {
            Elemento<T> *atual = this->_primeiro;
            this->_primeiro = this->_primeiro->proximo;
            delete atual;
        }
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     * 
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };

    /**
     * @brief Indica se há algum item na lista ou não.
     * 
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const
    {
        return this->_tamanho == 0;
    };

    /**
     * @brief Obtém a posição de um item na lista. Lança
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item cuja posição deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posição da primeira ocorrência.
     */
    virtual std::size_t posicao(T dado) const
    {
        if (this->vazia()) 
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else
        {
            Elemento<T>* _primeiro = this->_primeiro;
            std::size_t posicao = 0;                                                                                 

            while (_primeiro != nullptr) 
            {
                if (_primeiro->dado == dado) 
                {
                    return posicao;
                }
                _primeiro = _primeiro->proximo;
                posicao++;
            }
        throw ExcecaoDadoInexistente();
        } 
    };

    /**
     * @brief Indica se um dado item está contido na lista ou não.
     * 
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const 
    {
        Elemento<T>* _primeiro = this->_primeiro;

        while (_primeiro != nullptr) 
        {
            if (_primeiro->dado == dado) 
            {
                return true;  
            }
            _primeiro = _primeiro->proximo;
        }

        return false; 
    };

    /**
     * @brief Insere um item no início da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado) 
    {
        Elemento<T>* novo_elemento = new Elemento<T>{dado, this->_primeiro};
        this->_primeiro = novo_elemento;

        // Desalocar o elemento anterior
        if (this->_primeiro != nullptr) 
        {
            Elemento<T>* elemento_anterior = this->_primeiro->proximo;
        }

        this->_tamanho++;
    }

    /**
     * @brief Insere um item em uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa
     * [0, tamanho].
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posição já ocupada, a posição do item que já estava naquela posição
     * será posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {
        if (posicao >= 0 && posicao <= this->_tamanho)
        {
            if (posicao == this->_tamanho)
            {
                inserirNoFim(dado); 
            }
            else
            {
                Elemento<T>* _atual = this->_primeiro;
                Elemento<T>* _anterior = nullptr;
                std::size_t i = 0;

                while (i < posicao)
                {
                    _anterior = _atual;
                    _atual = _atual->proximo;
                    i++;
                }

                Elemento<T>* novo_elemento = new Elemento<T>{dado};
                novo_elemento->proximo = _atual;

                if (_anterior != nullptr)
                {
                    _anterior->proximo = novo_elemento;
                }
                else
                {
                    this->_primeiro = novo_elemento;
                }

                this->_tamanho++;
            }
        }
        else
        {
            throw ExcecaoPosicaoInvalida(); 
        }
    }

    /**
     * @brief Insere um item no fim da lista.
     * 
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        Elemento<T>* novo_elemento = new Elemento<T>{dado};

        if (this->vazia()) 
        {
            this->_primeiro = novo_elemento;
        } 
        else 
        {
            Elemento<T>* ultimo = this->_primeiro;
            while (ultimo->proximo != nullptr) 
            {
                ultimo = ultimo->proximo;
            }
            ultimo->proximo = novo_elemento;
        }

        this->_tamanho++;
    }


    /**
     * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        if (this->vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        Elemento<T>* elemento_removido = this->_primeiro;
        T dado = elemento_removido->dado;
        
        this->_primeiro = elemento_removido->proximo;
        delete elemento_removido; // Libere a memória do elemento removido

        this->_tamanho--;
        return dado;
    }


    /**
     * @brief Remove um item de uma posição específica da lista. Lança
     * ExcecaoPosicaoInvalida caso a posição não esteja na faixa [0, tamanho).
     * 
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
    if (posicao < 0 || posicao >= this->_tamanho)
    {
        throw ExcecaoPosicaoInvalida();
    }

    if (posicao == 0)
    {
        return removerDoInicio();
    }

    Elemento<T>* elemento_anterior = this->_primeiro;

    for (std::size_t i = 0; i < posicao - 1; i++)
    {
        elemento_anterior = elemento_anterior->proximo;
    }

    Elemento<T>* elemento_removido = elemento_anterior->proximo;
    T dado = elemento_removido->dado;
    elemento_anterior->proximo = elemento_removido->proximo;
    this->_tamanho--;

    return dado;
    }


    /**
     * @brief Remove o último item da lista. Lança ExcecaoListaEncadeadaVazia
     * caso não haja nenhum item na lista.
     * 
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
    if (this->vazia())
    {
        throw ExcecaoListaEncadeadaVazia();
    }

    if (this->_tamanho == 1)
    {
        T dado = this->_primeiro->dado;
        this->_primeiro = nullptr;
        this->_tamanho = 0;

        return dado;
    }

    Elemento<T>* penultimo_elemento = this->_primeiro;

    while (penultimo_elemento->proximo->proximo != nullptr)
    {
        penultimo_elemento = penultimo_elemento->proximo;
    }

    Elemento<T>* ultimo_elemento = penultimo_elemento->proximo;
    T dado = ultimo_elemento->dado;
    penultimo_elemento->proximo = nullptr;
    this->_tamanho--;

    return dado;
    }

    /**
     * @brief Remove um item específico da lista. Lança
     * ExcecaoListaEncadeadaVazia caso não haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item não esteja contido na lista.
     * 
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorrência.
     */
    virtual void remover(T dado)
    {
        if (this->vazia())
        {
            throw ExcecaoListaEncadeadaVazia();
        }

        if (this->_primeiro->dado == dado)
        {
            removerDoInicio();
            return; 
        }

        Elemento<T>* elemento_anterior = this->_primeiro;
        Elemento<T>* elemento_atual = elemento_anterior->proximo;

        while (elemento_atual != nullptr)
        {
            if (elemento_atual->dado == dado)
            {
                elemento_anterior->proximo = elemento_atual->proximo;
                this->_tamanho--;

                return;
            }
            elemento_anterior = elemento_atual;
            elemento_atual = elemento_atual->proximo;
        }

        throw ExcecaoDadoInexistente();
    }
};

#endif