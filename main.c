#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float Resistencias[12] = {100,200,330,470,680,1000,2000,3300,4700,6800,33000,100000};
float ImpedanciasPossiveis[500000]={100,200,330,470,680,1000,2000,3300,4700,6800,33000,100000};
int Combinacoes = 0;

/* Inicializacao das funcoes */
void swap(int *xp, int *yp);
void bubbleSort(float arr[], int n);
int RemoverElementosDuplicados(float arr[], int n);
int RemoverElementosSimilares(float arr[], int n);
float power(x,y);
void ZeroParaleloQuatroSerie();
float ResEquivParalelo(float res1, float res2, float res3, float res4);
float ResEquivSerie(float res1, float res2, float res3, float res4);
void ImprimeImpedanciasPossiveis();

/* Troca dois elementos num array */
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

/* Ordena um array por ordem crescente */
void bubbleSort(float arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

/* Remove elementos duplicados num array */
int RemoverElementosDuplicados(float arr[], int n)
{

    if (n == 0 || n == 1)
        return n;

    int temp[n];

    int j = 0;
    int i;
    for (i = 0; i < n - 1; i++)
        if (arr[i] != arr[i + 1])
            temp[j++] = arr[i];
    temp[j++] = arr[n - 1];

    for (i = 0; i < j; i++)
        arr[i] = temp[i];

    return j;
}

/* Remove elementos consecutivos que variam menos de 0.1% */
int RemoverElementosSimilares(float arr[], int n)
{

    if (n == 0 || n == 1)
        return n;

    int temp[n];

    int j = 0;
    int i;
    for (i = 0; i < n - 1; i++)
        if (arr[i+1] > 1.001*arr[i])
            temp[j++] = arr[i];
    temp[j++] = arr[n - 1];

    for (i = 0; i < j; i++)
        arr[i] = temp[i];

    return j;
}

/* Combinacao de resistencias 1 */
float QuatroParaleloZeroSerie()
{
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<12; k++)
            {
                for(int l=0; l<12; l++)
                {
                    ImpedanciasPossiveis[Combinacoes] = ResEquivParalelo(Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 2 */
float TresParaleloUmSerie()
{
    float res;
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<12; k++)
            {
                for(int l=0; l<12; l++)
                {
                    res = ResEquivParalelo(Resistencias[i], Resistencias[j], Resistencias[k], INFINITY);
                    ImpedanciasPossiveis[Combinacoes] = ResEquivSerie(res, Resistencias[l], 0, 0);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 3 */
float DoisParaleloDoisSerie()
{
    float res;
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<12; k++)
            {
                for(int l=0; l<12; l++)
                {
                    res = ResEquivParalelo(Resistencias[i], Resistencias[j], INFINITY, INFINITY);
                    ImpedanciasPossiveis[Combinacoes] = ResEquivSerie(res, Resistencias[k], Resistencias[l], 0);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 4 */
float UmParaleloTresSerie()
{
    float res;
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<12; k++)
            {
                for(int l=0; l<12; l++)
                {
                    res = ResEquivSerie(Resistencias[i], Resistencias[j], Resistencias[k], 0);
                    ImpedanciasPossiveis[Combinacoes] = ResEquivParalelo(res, Resistencias[l], INFINITY, INFINITY);
                    Combinacoes++;
                }
            }
        }
    }
}

/* Combinacao de resistencias 5 */
void ZeroParaleloQuatroSerie()
{
    for(int i=0; i<12; i++)
    {
        for(int j=0; j<12; j++)
        {
            for(int k=0; k<12; k++)
            {
                for(int l=0; l<12; l++)
                {
                    ImpedanciasPossiveis[Combinacoes] = ResEquivSerie(Resistencias[i], Resistencias[j], Resistencias[k], Resistencias[l]);
                    Combinacoes++;
                }
            }
        }
    }

}

/* Calcula a resistencia equivalente em paralelo */
float ResEquivParalelo(float res1, float res2, float res3, float res4)
{
    float res = pow(res1,-1) + pow(res2,-1) + pow(res3,-1) + pow(res4,-1);
    res = 1/res;
    return res;
}

/* Calcula a resistencia equivalente em serie */
float ResEquivSerie(float res1, float res2, float res3, float res4)
{
    return res1 + res2 + res3 + res4;
}

/* Imprime as impedancias do array de combinacoes */
void ImprimeImpedanciasPossiveis()
{
    for(int i=0; i<Combinacoes; i++)
    {
        printf("%.1f ", ImpedanciasPossiveis[i]);
    }
}

int main()
{
    printf("\n Loading . . .");

    /* Carrega as 5 possiveis combinacoes de resistencias */
    QuatroParaleloZeroSerie();
    TresParaleloUmSerie();
    DoisParaleloDoisSerie();
    UmParaleloTresSerie();
    ZeroParaleloQuatroSerie();

    /* Ordena, remove duplicado e similares do array de combinacoes */
    bubbleSort(ImpedanciasPossiveis, Combinacoes);
    Combinacoes = RemoverElementosDuplicados(ImpedanciasPossiveis, Combinacoes);
    Combinacoes = RemoverElementosSimilares(ImpedanciasPossiveis, Combinacoes);

    float imp, tol;
    int i;

    system("cls");

    do
    {
        system("cls");
        printf("-----------------------------------------------\n");
        printf("\n* Associacao de resistencias serie e paralelo *\n");
        printf("\n-----------------------------------------------\n\n");
        printf("Qual o valor de impedancia desejado? (Ohm)\n");
        scanf("%f",&imp);
        printf("Qual o valor de tolerancia desejado? (Percentagem)\n");
        scanf("%f",&tol);
        tol = tol/100;

        /* Percorre o array e encontra impedancias dentro dos limites pedidos */
        for(i=0;i<Combinacoes;i++){
            if(abs(ImpedanciasPossiveis[i]-imp)<=tol*imp){
                printf("Impedancia possivel: %2.f Ohms\n",ImpedanciasPossiveis[i]);
            }
        }
        printf("\n\n");
        system("pause");
    }
    while(imp!=0);

    return 0;
}
