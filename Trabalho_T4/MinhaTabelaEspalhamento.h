#ifndef MINHAtabela_ESPALHAMENTO_H
#define MINHAtabela_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente

template <typename T, std::size_t capac>
class MinhaTabelaEspalhamento final : public TabelaEspalhamentoAbstrata<T, capac>
{
    virtual ~MinhaTabelaEspalhamento()
    {
    }

    /**
     * @brief Obtém a capacidade da tabela.
     *
     * @return Um inteiro maior do que 0.
     */
    virtual std::size_t capacidade() const
    {
        return capac; //  Retorna o tamanho máximo que a tabela de espalhamento pode ter
    }

    /**
     * @brief Insere um dado na tabela. Se a tabela já contiver o dado, ele não
     * é inserido novamente.
     *
     * @param dado O dado a ser inserido.
     */
    virtual void inserir(T dado)
    {
        size_t indice = funcaoEspalhamento(dado);  // Calcula a posição na tabela
        if (!this->tabela.at(indice).contem(dado)) // Verifica se o elemento esta na lista
        {
            this->tabela.at(indice).inserirNoFim(dado); //  insere no final da lista
        }
    }

    /**
     * @brief Remove um dado da tabela. Se a tabela não contiver o dado, uma
     * exceção ExcecaoDadoInexistente é lançada.
     *
     * @param dado O dado a ser removido.
     */
    virtual void remover(T dado)
    {
        size_t posicaoTabela = funcaoEspalhamento(dado);  // Calcula a posição na tabela
        if (!this->tabela.at(posicaoTabela).contem(dado)) // Verifica se o elemento esta na lista
        {
            throw ExcecaoDadoInexistente(); // lança uma exceção
        }
        else
        {
            this->tabela.at(posicaoTabela).remover(dado); // Remove da lista
        }
    }

    /**
     * @brief Verifica se \p dado está contido na tabela.
     *
     * @param dado O dado sendo buscado.
     * @return true se o dado está contido na tabela; false caso contrário.
     */
    virtual bool contem(T dado) const
    {
        size_t posicaoTabela = funcaoEspalhamento(dado); // Calcula a posição na tabela

        return this->tabela.at(posicaoTabela).contem(dado); // Verifica se o elemento esta na lista
    }

    /**
     * @brief Obtém a quantidade de dados contidos na árvore.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t quantidade() const
    {
        int cont = 0;
        for (const auto &lista : this->tabela) // Para cada lista na tabela
        {
            cont += lista.tamanho(); // Adiciona o tamanho da lista ao total
        }

        return cont; // Retorna o total de elementos na tabela
    }

protected:
    /**
     * @brief Obtém a posição correspondente na tabela para o dado.
     *
     * @param dado O dado.
     * @return Um inteiro na faixa [0, capacidade).
     */
    virtual std::size_t funcaoEspalhamento(T dado) const
    {
        size_t aux = capacidade();                 // Obtem a capacidade
        if constexpr (!std::is_integral<T>::value) // Se o tipo de dado não for um numero inteiro
        {
            size_t somatorio = 0;                            // Inicializa a soma
            size_t expo = 1;                                 // Inicializa o expoente
            for (unsigned int i = 0; i < dado.length(); i++) // Para cada caractere no dado
            {
                int conversao = int(dado[i]);                     // Converte o caractere para um numero inteiro
                size_t potencia = 1;                              // Inicializa a potencia
                for (size_t j = 0; j < dado.length() - expo; j++) // Calcula a potencia para cada caractere restante no dado
                {
                    potencia *= 31;
                }
                somatorio += conversao * potencia; // Adiciona o produto da conversão e da potencia a soma
                expo++;                            // Incrementa o expoente
            }
            size_t indice_esperado = somatorio % aux; // Calcula o indice esperado como o resto da divisão da soma pela capacidade
            return indice_esperado;                   // Retorna o indice esperado
        }
        else // Se o tipo de dado for um numero inteiro
        {
            size_t indice_esperado = dado % aux; // Calcula o indice esperado como o resto da divisão do dado pela capacidade
            return indice_esperado;              // Retorna o indice esperado
        }
    }
};
#endif
