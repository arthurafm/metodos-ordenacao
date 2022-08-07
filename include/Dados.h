#ifndef DADOS_H
#define DADOS_H

#include <vector>
#include <random>

#include "../include/Registro.h"
#include "../include/Utils.h"

enum TipoShellSort { SHELL59, KNUTH71, TOKUDA92, CIURA01};

class Dados
{
    public: // elementos que podem ser acessados externamente

        Dados(); // construtor
        ~Dados(); // destrutor

        // funcoes de ordenacao (a serem completadas no LAB 1)
        Estatisticas ordenaComInsertionSort();
        Estatisticas ordenaComBubbleSort();
        Estatisticas ordenaComShellSort(TipoShellSort tipo);

        // funcoes de ordenacao (a serem completadas no LAB 2)
        Estatisticas ordenaComQuickSort();
        Estatisticas ordenaComHeapSort();
        void ordenaComCountingSort(int K);


        // funcoes que geram vetor de registros com valores aleatorios, em ordem, etc
        // caso os parametros 'minimo_possivel' e 'maximo_possivel' nao sejam informados receberão os valores padrao 0 e 1000
        void geraVetorAleatorio(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);
        void geraVetorOrdenado(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);
        void geraVetorQuaseOrdenado(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);
        void geraVetorReverso(unsigned int tamanho, int minimo_possivel=0, int maximo_possivel=1000);

        // funcao que imprime vetor de registros
        void imprimeRegistros();

        // funcao que retorna True se vetor estiver ordenado, senao False
        bool checaSeRegistrosOrdenados();

        // funcao que retorna True se ordenacao estavel aconteceu, senao False
        bool checaSeOrdenacaoFoiEstavel();

    private: // elementos que somente podem ser acessados dentro da classe

        // vetor de registros
        std::vector<Registro> registros;

        // variavel para armazenar estatisticas
        Estatisticas estatisticasTotais;

        // gerador de numeros aleatorios
        std::default_random_engine* gerador;

        // funcao que recebe um vetor por referencia (constante, pois nao será alterado) e inicializa vetor de registros
        void inicializaRegistrosComVetor(const std::vector<int>& vetor_auxiliar);

        // funcao que gera sequencia de gaps para ShellSort
        std::vector<int> geraSequenciaDeGaps(int tamanho, TipoShellSort tipo);

        // funcoes auxiliares para o metodo QuickSort
        void quickSort(int i, int f); // funcao recursiva do quicksort (A SER COMPLETADA)
        int particione(int pi, int pf); // funcao de particionamento (A SER COMPLETADA)

        // variaveis e funcoes auxiliares para o metodo HeapSort
        int heapSize;                   // tamanho da heap
        int filhoEsquerdoHeap(int i);   // funcao que calcula indice do filho esquerdo do nodo i
        int filhoDireitoHeap(int i);    // funcao que calcula indice do filho direito do nodo i
        int paiHeap(int i);            // funcao que calcula indice do pai do nodo i
        void heapify(int i);            // funcao recursiva de heapificação (A SER COMPLETADA)
        void buildHeap();               // funcao de construção bottom-up da heap
        void imprimeHeap();             // funcao de impressao indicando os filhos de cada nodo

        // funcao auxiliar que realiza a troca dos valores de dois registros
        void troca(Registro &x, Registro &y);

};

#endif // DADOS_H
