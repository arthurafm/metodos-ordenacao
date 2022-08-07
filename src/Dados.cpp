#include "../include/Dados.h"

#include <iostream>     // std::cout
#include <algorithm>    // std::sort


//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

Dados::Dados()
{
    //construtor

    // Inicializa gerador de numeros aleatorios (da biblioteca random)
    std::random_device r;
    gerador = new std::default_random_engine(r());

}

Dados::~Dados()
{
    // destrutor

    delete(gerador);
}

////////////////////////////////////
/// METODOS DE ORDENACAO - LAB 2 ///
////////////////////////////////////

int Dados::particione(int pi, int pf){
    int pivo;
    int i, j, buffer;
    Registro temp;
    j = pf;
    i = pi;
    std::uniform_int_distribution <int> numero_aleatorio(pi, pf); // Pivô iniciando em posição aleatória
    pivo = numero_aleatorio(*gerador);

    while(j > i){ // Laço de zerar o intervalo entre variaveis
        estatisticasTotais.comparacoes++;
        while((registros[i] <= registros[pivo]) && (i < pf)){ // Laço de aumentar o inicio do intervalo
            i++;
        }
        estatisticasTotais.comparacoes++;
        while((registros[j] > registros[pivo]) && (j > pi)){ // Laço de diminuir o final do intervalo
            j--;
        }
        estatisticasTotais.comparacoes++;
        if((i < j) && (registros[i] > registros[j])){ // Se há erro na separação, faz-se a troca
            if(i == pivo){
                pivo = j;
            }
            if(j == pivo){
                pivo = i;
            }
            temp = registros[i];
            registros[i] = registros[j];
            registros[j] = temp;
            estatisticasTotais.trocas++;
        }
    }
    estatisticasTotais.comparacoes++;
    if(registros[j] < registros[pivo]){ // Se o pivô não estiver no meio, troca a posição
        temp = registros[j];
        registros[j] = registros[pivo];
        registros[pivo] = temp;
        estatisticasTotais.trocas++;
        //imprimeRegistros();
    }
    return j;
}

void Dados::quickSort(int i, int f)
{
    // TODO: implementar funcao recursiva de quicksort que chama particionamento
    int p;
    if(f > i){
        p = particione(i, f);
        quickSort(i, p - 1);
        quickSort(p + 1, f);
    }
}

Estatisticas Dados::ordenaComQuickSort()
{
    estatisticasTotais.trocas = 0;
    estatisticasTotais.comparacoes = 0;
    quickSort(0,registros.size()-1);
    return estatisticasTotais;
}

void Dados::heapify(int i)
{
    int esq, dir, maior;
    esq = filhoEsquerdoHeap(i);
    dir = filhoDireitoHeap(i);
    maior = i;
    Registro temp;
    estatisticasTotais.comparacoes++;
    if((esq < heapSize) && (registros[esq] > registros[maior])){
        maior = esq;
    }
    estatisticasTotais.comparacoes++;
    if((dir < heapSize) && (registros[dir] > registros[maior])){
        maior = dir;
    }
    estatisticasTotais.comparacoes++;
    if(maior != i){
        temp = registros[i];
        registros[i] = registros[maior];
        registros[maior] = temp;
        estatisticasTotais.trocas++;
        heapify(maior);
    }
}

void Dados::buildHeap()
{
    heapSize = registros.size();
    estatisticasTotais.comparacoes++;
    for(int i = heapSize/2 - 1; i >= 0; i--){
        estatisticasTotais.comparacoes++;
        heapify(i);
    }
}

Estatisticas Dados::ordenaComHeapSort()
{
    estatisticasTotais.trocas = 0;
    estatisticasTotais.comparacoes = 0;
    int i;
    Registro temp;
    heapSize = 0;
    buildHeap();
    estatisticasTotais.comparacoes++;
    for(i = heapSize-1; i > 0; i--){
        estatisticasTotais.comparacoes++;
        temp = registros[i];
        registros[i] = registros[0];
        registros[0] = temp;
        estatisticasTotais.trocas++;
        heapSize--;
        heapify(0);
    }
    return estatisticasTotais;
}

void Dados::ordenaComCountingSort(int K)
{
    estatisticasTotais.trocas = 0;
    estatisticasTotais.comparacoes = 0;

    int i, j, n;
    Registro temp;
    n = registros.size();

    std::vector<int> vettempini(K+1, 0);
    std::vector<Registro> vettempfinal(n);


    for (i = 0; i < n; i++)
    {
        vettempini[registros[i].getChave()] = vettempini[registros[i].getChave()] + 1;
    }
    for (i = 1; i <= K; i++)
    {
        vettempini[i] = vettempini[i] + vettempini[i-1];
    }
    for (j = n-1; j >= 0; j--)
    {
        vettempfinal[vettempini[registros[j].getChave()]-1] = registros[j];

        vettempini[registros[j].getChave()] = vettempini[registros[j].getChave()] - 1;
    }

    for (i = 0; i < n; i++)
    {
        registros[i] = vettempfinal[i];
    }
    registros = vettempfinal;
}

////////////////////////////////////
/// METODOS DE ORDENACAO - LAB 1 ///
////////////////////////////////////

Estatisticas Dados::ordenaComBubbleSort()
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    int i, k = 0, m, n;
    Registro temp;
    n = registros.size();

    bool troca = true;
    m = n - 1;
    est.comparacoes++;

    while(troca){
        troca = false;
        est.comparacoes++;
        // Varre o vetor ate o local em que houve a ultima troca
        for(i = 0; i < m; i++){
            est.comparacoes++;
            // O if indica que havera troca, entao joga o elemento uma posicao para a direita
            if(registros[i] > registros[i+1]){
                est.comparacoes++;
                temp = registros[i];
                registros[i] = registros[i+1];
                registros[i+1] = temp;
                est.trocas++;
                k = i;
                troca = true;
            }
        }
        m = k;  // Guarda a posicao da ultima troca para otimizacao da funcao
    }
    return est;
}

Estatisticas Dados::ordenaComInsertionSort()
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;
    // Declara��o de vari�veis de controle
    int i, j, n;
    Registro temp;
    n = registros.size();
    est.comparacoes++;
    for(j = 1; j < n; j++){ // La�o de leitura crescente do vetor total
            est.comparacoes++;
            temp = registros[j];
            for(i = (j-1); (i >= 0) && (registros[i] > temp); i--){  // La�o de leitura decrescente do vetor ordenado
                est.comparacoes++;
                registros[i+1] = registros[i]; // Movimento crescente dos valores maiores que o inserido
                est.trocas++;
            }
            registros[i+1] = temp;
    }
    return est;
}

Estatisticas Dados::ordenaComShellSort(TipoShellSort tipo)
{
    Estatisticas est;
    est.trocas = 0;
    est.comparacoes = 0;

    // Declaracao de variaveis de controle
    int tamanhogaps;
    int n = registros.size();
    int i = 0, j, k, l, h = 1;
    Registro temp;

    std::vector<int> sequenciaDeGaps = geraSequenciaDeGaps(n,tipo);

    est.comparacoes++;
    tamanhogaps = sequenciaDeGaps.size();
    // Atribui a h o seu devido valor de acordo com o tipo passado de argumento
    do
    {
        est.comparacoes++;
        i++;
    } while (i < tamanhogaps);
    i = i-2;
    h = sequenciaDeGaps[i];

    est.comparacoes++;
    // Enquanto h for maior ou igual a 1, reduzindo seu valor de acordo com o vetor sequenciaDeGaps:
    while(h >= 1)
    {
        est.comparacoes++;
        // Varre todas os segmentos divididas pelo shellsort
        for (j = 0; j < h; j++)
        {
            est.comparacoes++;
            // Varre segmento por segmento
            for (k = j + h; k < n; k = k + h)
            {
                est.comparacoes++;
                temp = registros[k];
                l = k - h;
                // Se o segmento estiver desorganizado, ordena ele
                while (l >= 0 && registros[l] > temp)
                {
                    est.comparacoes++;
                    registros[l + h] = registros[l];
                    l = l - h;
                    est.trocas++;
                }
                registros[l + h] = temp;
            }
        }
        est.comparacoes++;
        // Para evitar que h recebe um valor invalido fora do vetor
        // sequenciaDeGaps, testa se i eh diferente de 0 antes
        if (i != 0)
        {
            i--;
            h = sequenciaDeGaps[i];
        }
        else
        {
            h = 0;
        }
    }
    return est;
}

bool Dados::checaSeOrdenacaoFoiEstavel()
{
    bool ehEstavel = true;
    for(unsigned int i = 0; i < registros.size() - 1; i++)
        if(registros[i].getChave() == registros[i+1].getChave()){
            if(registros[i].getDadoSatelite() > registros[i+1].getDadoSatelite())
                ehEstavel = false;
        }
    return ehEstavel;
}

//////////////////////////
/// METODOS AUXILIARES ///
//////////////////////////

int Dados::filhoEsquerdoHeap(int i)
{
    return 2*i+1;
}

int Dados::filhoDireitoHeap(int i)
{
    return 2*i+2;
}

int Dados::paiHeap(int i)
{
    return (i-1)/2;
}

void Dados::imprimeHeap()
{
    int nivel=-1;
    int nodos_no_nivel=1;

    std::cout << "\nHEAP\n";
    for(int i=0;i<heapSize; i++){
        if(i==nodos_no_nivel-1){
            nivel++;
            nodos_no_nivel *= 2;
        }
        for(int j=0;j<nivel;j++)
            std::cout << " ";
        std::cout << registros[i];

        int e = filhoEsquerdoHeap(i);
        int d = filhoDireitoHeap(i);

        if(e<heapSize)
            std::cout << " filho_esq: " << registros[e];
        if(d<heapSize)
            std::cout << " filho_dir: " << registros[d];
        if(i>=heapSize/2)
            std::cout << " FOLHA";
        std::cout << std::endl;
    }
}

void Dados::troca(Registro &x, Registro &y)
{
    Registro temp;
    temp = x;
    x = y;
    y = temp;
}

bool Dados::checaSeRegistrosOrdenados()
{
    for(unsigned int i=0; i<registros.size() - 1; i++)
        if(registros[i]>registros[i+1])
            return false;

    return true;
}

std::vector<int> Dados::geraSequenciaDeGaps(int tamanho, TipoShellSort tipo)
{
    std::vector<int> v;

    int e=1;
    v.push_back(e);

    if(tipo==SHELL59){         // (Shell,1959) - sequencia 1, 2, 4, 8, 16, 32, ...
        while(e<tamanho){
            e *= 2;
            v.push_back(e);
        }

    }else if(tipo==KNUTH71){   // (Knuth,1971) - sequencia 1, 4, 13, 40, 121, 364, ...
        while(e<tamanho){
            e = e*3+1;
            v.push_back(e);
        }

    }else if(tipo==TOKUDA92){  // (Tokuda,1992) - sequencia 1, 4, 9, 20, 46, 103, ...
        int i=1;
        while((e=ceil((9.0 * pow(9.0,i)/pow(4.0,i) - 4.0)/5.0)) < tamanho){
            v.push_back(e);
            i++;
        }
    }else if(tipo==CIURA01){  // (Ciura,2001) - sequencia 1, 4, 10, 23, 57, 132, 301, 701 - daqui em diante nao tem prova de otimalidade
        int seq[8]={1,4,10,23,57,132,301,701};

        int i=1;
        while(i<8 && seq[i]<tamanho){
            v.push_back(seq[i]);
            i++;
        }

        int e=701;
        while((e=floor(2.25*(float)e))<tamanho)
            v.push_back(e);
    }

    return v;
}

void Dados::inicializaRegistrosComVetor(const std::vector<int>& vetor_auxiliar)
{
    // Reseta vetor de registros
    registros.clear();

    // Reserva novo tamanho do vetor de registros
    unsigned int tamanho = vetor_auxiliar.size();
    registros.reserve(tamanho);

    // Copia valores para vetor de registros
    for(unsigned int i=0; i<tamanho; i++){
        int c = vetor_auxiliar[i];
        int s = i+1;

        registros.push_back(Registro(c,s));
    }
}

void Dados::geraVetorAleatorio(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Seta distribuicao de chaves como valor aleatorio uniforme entre 'minimo_possivel' e 'maximo_possivel'
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);

    // Cria vetor auxiliar e preenche com valores aleatorios
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++){
        vetor_auxiliar[i] = chave_aleatoria(*gerador);
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorQuaseOrdenado(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end());

    // Da uma leve embaralhada, dentro de uma distancia 'range'
    int range=tamanho/50;
    if(range<5)
        range=5;
    std::uniform_int_distribution<int> gap_para_troca(0,range);

    for(unsigned int i=0; i<tamanho; i++){
        int k = gap_para_troca(*gerador);
        if(k%5==0 && i+k<tamanho){
            int temp = vetor_auxiliar[i+k];
            vetor_auxiliar[i+k] = vetor_auxiliar[i];
            vetor_auxiliar[i] = temp;
        }
    }

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::geraVetorReverso(unsigned int tamanho, int minimo_possivel, int maximo_possivel)
{
    // Gera valores aleatorios iniciais em um vetor auxiliar
    std::uniform_int_distribution<int> chave_aleatoria(minimo_possivel, maximo_possivel);
    std::vector<int> vetor_auxiliar(tamanho);
    for(unsigned int i=0; i<tamanho; i++)
        vetor_auxiliar[i] = chave_aleatoria(*gerador);

    // Ordena o vetor com funcao de ordenacao da std library
    std::sort (vetor_auxiliar.begin(), vetor_auxiliar.end(), std::greater<int>());

    // Inicializa registros a partir do vetor
    inicializaRegistrosComVetor(vetor_auxiliar);
}

void Dados::imprimeRegistros()
{
    for(unsigned int i=0; i<registros.size(); i++){
        std::cout << registros[i] << ' ';
    }
    std::cout << std::endl;
}

