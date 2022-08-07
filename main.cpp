#include <iostream>

#include "include/Dados.h"

int main()
{
    std::cout << "LAB 2" << std::endl;

    Dados dados;
    Timer timer;
    Estatisticas est;
    float tempo;

    int VALOR_MAXIMO=1000;

    for(int tamanho=1000; tamanho<1000000; tamanho*=2){

        est.trocas = est.comparacoes = 0;

        VALOR_MAXIMO = tamanho;

        dados.geraVetorAleatorio(tamanho,0,VALOR_MAXIMO);
//        dados.geraVetorOrdenado(tamanho,0,VALOR_MAXIMO);
//        dados.geraVetorQuaseOrdenado(tamanho,0,VALOR_MAXIMO);
//        dados.geraVetorReverso(tamanho,0,VALOR_MAXIMO);

        std::cout << "N " << tamanho;
        std::cout.flush();

        timer.iniciaContagem();

        /// MÉTODOS DO LAB 1 ///

//        est = dados.ordenaComBubbleSort();
//        est = dados.ordenaComInsertionSort();
//        est = dados.ordenaComShellSort(SHELL59);
//        est = dados.ordenaComShellSort(KNUTH71);
//        est = dados.ordenaComShellSort(TOKUDA92);
//        est = dados.ordenaComShellSort(CIURA01);

        /// MÉTODOS DO LAB 2 ///

        est = dados.ordenaComQuickSort();
//        est = dados.ordenaComHeapSort();
//        dados.ordenaComCountingSort(VALOR_MAXIMO);

        tempo = timer.finalizaContagem();

        std::cout << " tempo " << tempo << " trocas " << est.trocas << " comparacoes " << est.comparacoes << std::endl;

//        dados.imprimeRegistros();

        bool estaOrdenado = dados.checaSeRegistrosOrdenados();
        bool ordenacaoEstavel = dados.checaSeOrdenacaoFoiEstavel();
        std::cout << (estaOrdenado ? "Vetor ordenado" : "Vetor NAO ordenado") << " - "
                  << (ordenacaoEstavel ? "Ordenacao foi estavel" : "Ordenacao NAO foi estavel") << std::endl;

    }

    return 0;
}
