#ifndef MINHALISTAENCADEADA_H
#define MINHALISTAENCADEADA_H

#include "ListaEncadeadaAbstrata.h"

template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
public:
    virtual ~MinhaListaEncadeada()
    {
        Elemento<T> *elemento_removido = this->_primeiro; // Criamos um elemento com o primeiro elemento da lista, usaremos ele para ir destruindo a lista

        while (elemento_removido != nullptr) // Loop executara até o fim da lista, ou seja elemento_removido apontara para nullptr
        {
            Elemento<T> *proximo = elemento_removido->proximo; // Armazena o valor do próximo elemento da lista
            delete elemento_removido;                          // Liberando a memória
            elemento_removido = proximo;                       // Aponta para o próximo elemento da lista
        }
        // Zeramos a lista e declaramos o primeiro elemento como nullptr
        this->_primeiro = nullptr;
        this->_tamanho = 0;
    }

    /**
     * @brief Obtém a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho; // Retorna o valor de _tamanho da classe MinhaListaEncadeada
    }
    /**
     * @brief Indica se há algum item na lista ou não.
     *
     * @return false se houver algum item na lista; true caso contrário.
     */
    virtual bool vazia() const
    {
        // Nao precisamos fazer um if else, pois um bool so retorna true ou false, então como fazemos a comparação
        // se this->_tamanho == 0, retorna true, caso contrario retorna false.
        return this->_tamanho == 0;
    }

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
        // Primeiro verificamos se a lista não está vazia
        if (this->_tamanho <= 0)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else
        {
            Elemento<T> *_primeiro = this->_primeiro; // Ponteiro para o primeiro elemento da lista
            std::size_t cont = 0;                     // Variavel que guarda a posição

            while (_primeiro != nullptr) // Loop executara até o fim da lista, ou seja _primeiro apontara para nullptr
            {
                if (_primeiro->dado == dado) // Caso o dado desejado seja igual ao dado apontado na lista, entao retornaremos a posição
                {
                    return cont;
                }
                else
                {
                    _primeiro = _primeiro->proximo; // Aponta para o proximo elemento da lista
                    cont++;                         // Incrementa o valor da posição
                }
            }
            throw ExcecaoDadoInexistente(); // Caso ela não esteja vazia e o valor não for encontrado, então executara a exceção
        }
    }
    
    /**
     * @brief Indica se um dado item está contido na lista ou não.
     *
     * @param dado O item sendo buscado.
     * @return true se o item está contido na lista; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        // Basicamente usaremos a mesma lógica da função  posicao(T dado), só que não retornaremos true ou false em vez da posição
        Elemento<T> *_primeiro = this->_primeiro;

        while (_primeiro != nullptr) // Loop executara até o fim da lista, ou seja _primeiro apontara para nullptr
        {
            if (_primeiro->dado == dado) // Caso o dado desejado seja igual ao dado apontado na lista, entao retornaremos a true
            {
                return true;
            }
            _primeiro = _primeiro->proximo; // Aponta para o proximo elemento da lista
        }
        return false; // Caso não estiver na lista,
    }

    /**
     * @brief Insere um item no início da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {
        Elemento<T> *novo_elemento = new Elemento<T>{dado, this->_primeiro}; // Criamos um elemento chamado novo_elemento, dado é o valor armazenado e aponta para o começo da lista
        this->_primeiro = novo_elemento;                                     // Novo elemento se torna o primeiro elemento da lista
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
        if (posicao > this->_tamanho) // Caso posição seja maior que a lista
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao < 0) // Caso posição seja menor que 0
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao >= 0 && posicao <= this->_tamanho) // Verificamos se a posição desejada é >=0 e se é menor ou igual ao tamanho da lista
        {
            if (posicao == 0) // Caso a posição seja zero, inserimos no inicio chamando inserirNoInicio
            {
                inserirNoInicio(dado);
            }
            else if (posicao == this->_tamanho) // Caso a posição for igual ao tamanho, então teremos que inserir no fim, logo chamamos inserirNoFim
            {
                inserirNoFim(dado);
            }
            else // Caso for nenhum dos anteriores
            {
                Elemento<T> *_primeiro = this->_primeiro; // Ponteiro para o primeiro elemento da lista
                Elemento<T> *_anterior = nullptr;         // Ponteiro para o elemento anterior da lista, precisaremos para atualizar quando inserir o novo elemento na lista
                std::size_t cont = 0;

                while (cont < posicao) // Loop para achar a posição desejada
                {
                    _anterior = _primeiro;          // Armazena atual (ainda não atualizamos para o proximo, ai ele se torna o anterior)
                    _primeiro = _primeiro->proximo; // atualiza a lista para o proximo valor
                    cont++;                         // Incrementa a variavel contadora
                }

                Elemento<T> *novo_elemento = new Elemento<T>{dado}; // Criamos o novo elemento com o valor desejado
                novo_elemento->proximo = _primeiro;

                if (_anterior != nullptr) // Verifica se o número não está na primeira posição
                {
                    _anterior->proximo = novo_elemento;
                }
                else // Caso estiver coloca no começo da lista
                {
                    this->_primeiro = novo_elemento;
                }
                this->_tamanho++; // Incrementa o tamanho da lista
            }
        }
    }

    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoFim(T dado)
    {
        {
            Elemento<T> *novo_elemento = new Elemento<T>{dado}; // Criamos o novo elemento que será inserido no fim da lista

            if (this->_primeiro == nullptr) // Verifica se a lista está vazia, caso estiver inserimos no inicio
            {
                inserirNoInicio(dado);
                delete novo_elemento; // Deletemos o elemento criado dentro de inserirNoInicio para não ter vazamento de memória
                return;
            }
            else
            {
                Elemento<T> *ultimo = this->_primeiro; // Cria um elemento que vai percorrer até o fim da lista

                while (ultimo->proximo != nullptr)
                {
                    ultimo = ultimo->proximo;
                }
                ultimo->proximo = novo_elemento; // Atualizamos o ultimo elemento para o novo elemento
            }
            this->_tamanho++; // Aumentamos o tamanho da lista
        }
    }

        /**
         * @brief Remove o primeiro item da lista. Lança ExcecaoListaEncadeadaVazia
         * caso não haja nenhum item na lista.
         *
         * @return O item removido.
         */
        virtual T removerDoInicio()
        {
            if (this->_tamanho <= 0) // Caso a lista for menor ou igual a zero, chamamos a exceção
            {
                throw ExcecaoListaEncadeadaVazia();
            }

            Elemento<T> *elemento_removido = this->_primeiro; // Cria um elemento apontado para o primeiro elemento da lista
            T dado = elemento_removido->dado;                 // Armazenar o valor a ser removido
            this->_primeiro = elemento_removido->proximo;     // Aponta par o novo primeiro elemento
            delete elemento_removido;                         // Libere a memória do elemento removido
            this->_tamanho--;                                 // Decrementa a lista
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
            if (posicao < 0 || posicao >= this->_tamanho) // Caso a posicao for < 0 ou >= o tamanho da lista, chamamos a exceção
            {
                throw ExcecaoPosicaoInvalida();
            }
            else if (this->_tamanho <= 0) // Caso a lista estiver, chamamos a exceção
            {
                throw ExcecaoPosicaoInvalida();
            }
            else if (posicao == 0) // Caso a posição for a inicial chamamos removerDoInicio()
            {
                return removerDoInicio();
            }
            else if (posicao == this->_tamanho) // Caso a posição = _tamanho chamamos removerDoFim()
            {
                return removerDoFim();
            }

            Elemento<T> *elemento_anterior = this->_primeiro; // Criamos o ponteiro que vai armazenar o elemento anterior
            for (std::size_t i = 0; i < posicao - 1; i++)     // Loop para achar o elemento anterior do que será removido
            {
                elemento_anterior = elemento_anterior->proximo;
            }

            Elemento<T> *elemento_removido = elemento_anterior->proximo;
            T dado = elemento_removido->dado;                        // Armazenar o valor a ser removido
            elemento_anterior->proximo = elemento_removido->proximo; // Atualiza o elemento anterior para apontar para o lugar do elemento removido
            delete elemento_removido;                                // Libere a memória do elemento removido
            this->_tamanho--;                                        // Decrementa a lista
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
            if (this->_tamanho <= 0) // Caso a lista estiver vazia chamamos a excessão
            {
                throw ExcecaoListaEncadeadaVazia();
            }
            if (this->_tamanho == 1) // Caso a lista for de tamanho 1, o ultimo também é o primeiro
            {
                return removerDoInicio();
            }

            Elemento<T> *penultimo_elemento = this->_primeiro;      // Ponteiro para armazenar o penultimo elemento da lista
            while (penultimo_elemento->proximo->proximo != nullptr) // Vai percorrer até o penultimo elemento da lista
            {
                penultimo_elemento = penultimo_elemento->proximo;
            }

            Elemento<T> *ultimo_elemento = penultimo_elemento->proximo; // Aponta para o ultimo elemento
            T dado = ultimo_elemento->dado;                             // Armazenar o valor a ser removido
            penultimo_elemento->proximo = nullptr;                      // O proximo do ultimo elemento vira nullptr
            delete ultimo_elemento;                                     // Libere a memória do elemento removido
            this->_tamanho--;                                           // Decrementa a lista
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
            if (this->_tamanho <= 0) // Se a lista estiver vazia ou seja <= 0 chamamos a excessão
            {
                throw ExcecaoListaEncadeadaVazia();
            }
            else if (!contem(dado)) // Se a lista não conter o dado chamamos a excessão
            {
                throw ExcecaoDadoInexistente();
            }
            else
            {
                size_t cont = posicao(dado); // Primeiro encontramos a sua posição na lista
                removerDe(cont);             // Depois removemos com a função removerDe
            }
        }
    };
#endif