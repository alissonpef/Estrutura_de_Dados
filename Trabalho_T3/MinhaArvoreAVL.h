#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
public:
    MinhaArvoreAVL(){};
    virtual ~MinhaArvoreAVL()
    {
        if (this->raiz)
        {
            this->destrutor_aux(this->raiz);
        }
    }
    void destrutor_aux(Nodo<T> *nodo)
    {
        if (nodo)
        {
            this->destrutor_aux(nodo->filhoDireita);
            this->destrutor_aux(nodo->filhoEsquerda);
            delete nodo;
        }
    }

    /**
     * @brief Verifica se a árvore está vazia
     * @return Verdade se a árvore está vazia.
     */
    virtual bool vazia() const
    {
        // Nao precisamos fazer um if else, pois um bool so retorna true ou false, então como fazemos a comparação
        // se this->_tamanho == 0, retorna true, caso contrario retorna false.
        return this->raiz == nullptr;
    }

    /**
     * @brief Retornar quantidade de chaves na árvore
     * @return Numero natural que representa a quantidade de chaves na árvore
     */
    virtual int quantidade() const
    {
        return quantidade_aux(this->raiz); // Chamado da função quantidade_aux para contar recursivamente
    }
    int quantidade_aux(Nodo<T> *nodo) const
    {
        if (nodo == nullptr) // Verifica se ainda a nós para contar, logo nossa condição de parada
        {
            return 0;
        }
        else // Caso o nó atual nao for nulo, contaremos ele
        {
            // Conta o nó atual + chamada recursiva dos filhos esquerdo + chamada recursiva dos filhos direito.
            return 1 + quantidade_aux(nodo->filhoEsquerda) + quantidade_aux(nodo->filhoDireita);
        }
    }

    /**
     * @brief Verifica se a árvore contém uma chave
     * @param chave chave a ser procurada na árvore
     * @return Verdade se a árvore contém a chave
     */
    virtual bool contem(T chave) const
    {
        Nodo<T> *nodo = this->raiz; // Inicializa o nodo atual como a raiz
        while (nodo)                // Loop enquanto o nodo não for nulo
        {
            if (chave == nodo->chave)
            {
                return true; // Caso encontrada, retorna true
            }
            else if (chave < nodo->chave)
            {
                nodo = nodo->filhoEsquerda; // Se nodo for menor que o nó atual, muda para a subárvore a esquerda
            }
            else if (chave > nodo->chave)
            {
                nodo = nodo->filhoDireita; // Se nodo for menor que o nó atual, muda para a subárvore a direita
            }
        }

        return false; // Se percorrermos ela inteira e não encontrarmos, retornamos false
    }

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const
    {
        return altura_aux(this->raiz, chave); // Chamado da função altura_aux para contar recursivamente
    }
    std::optional<int> altura_aux(Nodo<T> *nodo, T chave) const
    {
        // Basicamente utilizamos a mesma lógica da função contem
        while (nodo) // Loop enquanto o nodo não for nulo
        {
            if (chave == nodo->chave)
            {
                return nodo->altura; // Caso encontrada, retorna a altura do nodo
            }
            else if (chave < nodo->chave)
            {
                return altura_aux(nodo->filhoEsquerda, chave); // Se nodo for menor que o nó atual, muda para a subárvore a esquerda
            }
            else if (chave > nodo->chave)
            {
                return altura_aux(nodo->filhoDireita, chave); // Se nodo for menor que o nó atual, muda para a subárvore a direita
            }
        }

        return std::nullopt; // Se percorrermos ela inteira e não encontrarmos, retornamos nullopt
    }
    int altura_max(Nodo<T> *nodo) const
    {
        int altura_esquerda;
        int altura_direita;

        if (nodo == nullptr)
        {
            return -1; // Quando o nó é nulo, ele não tem altura
        }

        altura_esquerda = altura_max(nodo->filhoEsquerda); // Chamado da função altura_max para contar recursivamente a esquerda
        altura_direita = altura_max(nodo->filhoDireita);   // Chamado da função altura_max para contar recursivamente a direita

        if (altura_esquerda > altura_direita) // Verifica qual a maior altura entre a esquerda e direita
        {
            return altura_esquerda + 1; // Caso a esquerda for maior retorna a altura do mesmo + 1, pois conta o nó atual
        }
        else
        {
            return altura_direita + 1; // Caso a direita for maior retorna a altura do mesmo + 1, pois conta o nó atual
        }
    }
    int balancear_altura(Nodo<T> *nodo) const
    {
        int altura_esquerda = -1; // Inicializa as altura como -1.
        int altura_direita = -1;  // Inicializa as altura como -1.

        if (nodo == nullptr) // Caso a o nó for nulo, a altura será 0
        {
            return 0;
        }
        if (nodo->filhoEsquerda != nullptr) // Verifica se possui nó a esquerda, caso tenha obtém a altura dele
        {
            altura_esquerda = nodo->filhoEsquerda->altura;
        }
        if (nodo->filhoDireita != nullptr) // Verifica se possui nó a direita, caso tenha obtém a altura dele
        {
            altura_direita = nodo->filhoDireita->altura;
        }

        return altura_esquerda - altura_direita; // Cacula a altura da arvore a esquerda - a arvore a direita
    };
    Nodo<T> *rotacao_direita(Nodo<T> *nodo)
    {
        Nodo<T> *novoPai = nodo->filhoEsquerda;     // Armazena o nó a esquerda do nó fornecido como o novo pai
        Nodo<T> *novoFilho = novoPai->filhoDireita; // Armazena o filho a direita do novo pai como o novo filho do nó original
        novoPai->filhoDireita = nodo;
        nodo->filhoEsquerda = novoFilho;

        if (nodo == this->raiz) // Verifica se o nodo é a raiz da árvore
        {
            this->raiz = novoPai;
        }

        nodo->altura = altura_max(nodo);       // Atualiza as alturas do nodo
        novoPai->altura = altura_max(novoPai); // Atualiza as alturas do novoPai

        return novoPai; // Retorna o novo pai, que é a raiz da subárvore
    }
    Nodo<T> *rotacao_esquerda(Nodo<T> *nodo)
    {
        Nodo<T> *novoPai = nodo->filhoDireita;       // Armazena o nó a esquerda do nó fornecido como o novo pai
        Nodo<T> *novoFilho = novoPai->filhoEsquerda; // Armazena o filho a direita do novo pai como o novo filho do nó original
        novoPai->filhoEsquerda = nodo;
        nodo->filhoDireita = novoFilho;

        if (nodo == this->raiz) // Verifica se o nodo é a raiz da árvore
        {
            this->raiz = novoPai;
        }

        nodo->altura = altura_max(nodo);
        novoPai->altura = altura_max(novoPai);

        return novoPai; // Retorna o novo pai, que é a raiz da subárvore
    }
    Nodo<T> *balancear_arvore(Nodo<T> *raiz)
    {
        int fator_balanceamento = balancear_altura(raiz);

        if (fator_balanceamento > 1) // Se for >1, a árvore esta desbalanceada a esquerda
        {
            if (balancear_altura(raiz->filhoEsquerda) >= 0)
            {
                return rotacao_direita(raiz); // Realiza uma rotação a direita
            }
            if (raiz->filhoEsquerda != nullptr)
            {
                raiz->filhoEsquerda = rotacao_esquerda(raiz->filhoEsquerda); // Realiza uma rotação a esquerda na subárvore a esquerda
            }
            return rotacao_direita(raiz); // Realiza uma rotação a direita
        }

        else if (fator_balanceamento < -1) // Se for <-1, a árvore esta desbalanceada a direita
        {
            if (balancear_altura(raiz->filhoDireita) <= 0)
            {
                return rotacao_esquerda(raiz); // Realiza uma rotação a esquerda
            }
            if (raiz->filhoDireita != nullptr)
            {
                raiz->filhoDireita = rotacao_direita(raiz->filhoDireita); // realiza uma rotação a direita na subárvore a direita
            }
            return rotacao_esquerda(raiz); // Realiza uma rotação a esquerda
        }

        return raiz; // Caso já esteja balanceada, retorna a raiz sem alterações
    }

    /**
     * @brief Função para inserir uma chave na árvore.
     * @param chave A chave a ser inserida.
     */
    virtual void inserir(T chave)
    {
        Nodo<T> *novo_nodo = new Nodo<T>{chave}; // Cria um novo nodo com a chave fornecida

        if (this->raiz == nullptr) // Se a árvore está vazia, o novo nodo se torna a raiz da árvore
        {
            this->raiz = novo_nodo;
        }

        this->inserir_aux(this->raiz, novo_nodo, chave); // Chamado da função auxiliar para inserir o novo nodo na árvore
    }
    Nodo<T> *inserir_aux(Nodo<T> *raiz, Nodo<T> *nodo, T chave)
    {

        if (raiz == nullptr)
        {
            raiz = nodo; // Se a árvore está vazia, o novo nodo se torna a raiz da árvore
        }
        else if (chave < raiz->chave)
        {
            raiz->filhoEsquerda = inserir_aux(raiz->filhoEsquerda, nodo, chave); // Insere o novo nodo na subárvore a esquerda
        }
        else if (chave > raiz->chave)
        {
            raiz->filhoDireita = inserir_aux(raiz->filhoDireita, nodo, chave); // Insere o novo nodo na subárvore a direita
        }

        raiz = balancear_arvore(raiz);   // Balanceia a árvore atualizada
        raiz->altura = altura_max(raiz); // Atualiza a altura da árvore atualizada

        return raiz;
    }

    /**
     * @brief Remove uma chave da árvore.
     * @param chave chave a ser removida.
     */
    virtual void remover(T chave)
    {
        if (this->raiz != nullptr)
        {
            this->raiz = remover(this->raiz, chave); // Chamado da função auxiliar para remover o novo nodo na árvore
        }
    }
    Nodo<T> *remover(Nodo<T> *raiz, T chave)
    {
        if (raiz == nullptr) // Se a raiz é nula, retorna nulo
        {
            return nullptr;
        }
        if (chave < raiz->chave) // Se a chave é menor que a chave da raiz, procura na subárvore esquerda
        {
            raiz->filhoEsquerda = remover(raiz->filhoEsquerda, chave);
        }
        else if (chave > raiz->chave) // Se a chave é maior que a chave da raiz, procura na subárvore direita
        {
            raiz->filhoDireita = remover(raiz->filhoDireita, chave);
        }
        else // Se a chave é igual a chave da raiz, remove o nó
        {
            if (raiz->filhoEsquerda == nullptr)
            {
                Nodo<T> *temp = raiz->filhoDireita;
                delete raiz;
                return temp;
            }
            else if (raiz->filhoDireita == nullptr)
            {
                Nodo<T> *temp = raiz->filhoEsquerda;
                delete raiz;
                return temp;
            }
            Nodo<T> *sucessor = encontrar_sucessor(raiz->filhoDireita);
            raiz->chave = sucessor->chave;
            raiz->filhoDireita = remover(raiz->filhoDireita, sucessor->chave);
        }

        raiz->altura = altura_max(raiz); // Atualiza a altura e balanceia a árvore

        return balancear_arvore(raiz);
    }
    Nodo<T> *encontrar_sucessor(Nodo<T> *raiz)
    {
        while (raiz->filhoEsquerda != nullptr) // Se o nó tem um filho a esquerda, vai até encontrar o nó com a menor chave
        {
            raiz = raiz->filhoEsquerda;
        }

        return raiz; // Retorna o nó com a menor chave
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)árvore
     * @param chave chave da árvore que é pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave não está na árvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        return filhoEsquerdaDe_aux(this->raiz, chave); // Chamado recursiva da função filhoEsquerdaDe_aux
    }
    std::optional<T> filhoEsquerdaDe_aux(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr || nodo->filhoEsquerda == nullptr) // Verifica se o nodo atual é nulo ou não possui um filho a esquerda
        {
            return std::nullopt;
        }

        if (chave == nodo->chave) // Verifica se a chave do nodo atual é igual a chave buscada
        {
            return nodo->filhoEsquerda->chave;
        }

        if (chave < nodo->chave) // Verifica se a chave do nodo atual é menor que a chave buscada
        {
            return filhoEsquerdaDe_aux(nodo->filhoEsquerda, chave);
        }

        else // Verifica se a chave do nodo atual é menor que a chave buscada
        {
            return filhoEsquerdaDe_aux(nodo->filhoDireita, chave);
        }
    }
    /**
     * @brief Busca a chave do filho a direita de uma (sub)árvore
     * @param chave chave da árvore que é pai do filho a direita
     * @return Chave do filho a direita. Se a chave não está na árvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        return filhoDireitaDe_aux(this->raiz, chave); // Chamado recursiva da função filhoDireitaDe_aux
    }
    std::optional<T> filhoDireitaDe_aux(Nodo<T> *nodo, T chave) const
    {
        if (nodo == nullptr || nodo->filhoDireita == nullptr) // Verifica se o nodo atual é nulo ou não possui um filho a esquerda
        {
            return std::nullopt;
        }

        if (chave == nodo->chave) // Verifica se a chave do nodo atual é igual a chave buscada
        {
            return nodo->filhoDireita->chave;
        }

        if (chave < nodo->chave) // Verifica se a chave do nodo atual é menor que a chave buscada
        {
            return filhoDireitaDe_aux(nodo->filhoEsquerda, chave);
        }

        else // Verifica se a chave do nodo atual é menor que a chave buscada
        {
            return filhoDireitaDe_aux(nodo->filhoDireita, chave);
        }
    }

    /**
     * @brief Lista chaves visitando a árvore em ordem.
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        emOrdem_aux(this->raiz, lista); // Chamado da função auxiliar para preencher a lista em ordem

        return lista;
    }
    void emOrdem_aux(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (nodo != nullptr) // Verifica se o nodo atual não é nulo
        {
            emOrdem_aux(nodo->filhoEsquerda, lista); // Chamada recursiva da função para a esquerda
            lista->inserirNoFim(nodo->chave);        // Inserção atual no final da lista
            emOrdem_aux(nodo->filhoDireita, lista);  // Chamada recursiva da função para a direita
        }
    }

    /**
     * @brief Lista chaves visitando a árvore em pré-ordem.
     * @return Lista encadeada contendo as chaves em pré-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        preOrdem_aux(this->raiz, lista); // Chamado da função auxiliar para preencher a lista em ordem

        return lista;
    }
    void preOrdem_aux(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (nodo != nullptr)
        {
            lista->inserirNoFim(nodo->chave);         // Inserção atual no final da lista
            preOrdem_aux(nodo->filhoEsquerda, lista); // Chamada recursiva da função para a esquerda
            preOrdem_aux(nodo->filhoDireita, lista);  // Chamada recursiva da função para a direita
        }
    }

    /**
     * @brief Lista chaves visitando a árvore em pós-ordem.
     * @return Lista encadeada contendo as chaves em pós-ordem.
     */
    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        ListaEncadeadaAbstrata<T> *lista = new MinhaListaEncadeada<T>;
        posOrdem_aux(this->raiz, lista);

        return lista; // Chamado da função auxiliar para preencher a lista em ordem
    }
    void posOrdem_aux(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *lista) const
    {
        if (nodo != nullptr)
        {
            posOrdem_aux(nodo->filhoEsquerda, lista); // Chamada recursiva da função para a esquerda
            posOrdem_aux(nodo->filhoDireita, lista);  // Chamada recursiva da função para a direita
            lista->inserirNoFim(nodo->chave);         // Inserção atual no final da lista
        }
    }
};

#endif