#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float Resistencias[12] = {100,200,330,470,680,1000,2000,3300,4700,6800,33000,100000};
float ImpedanciasPossiveis[500000]={100,200,330,470,680,1000,2000,3300,4700,6800,33000,100000};
int Combinacoes = 0;

void swap(int *xp, int *yp);
void bubbleSort(float arr[], int n);
int RemoverElementosDuplicados(float arr[], int n);
int RemoverElementosSimilares(float arr[], int n);
float power(x,y);
void ZeroParaleloQuatroSerie();
float ResEquivParalelo(float res1, float res2, float res3, float res4);
float ResEquivSerie(float res1, float res2, float res3, float res4);
void ImprimeImpedanciasPossiveis();

#define INFINITY 999999999999

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubbleSort(float arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}

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

float ResEquivParalelo(float res1, float res2, float res3, float res4)
{
    float res = pow(res1,-1) + pow(res2,-1) + pow(res3,-1) + pow(res4,-1);
    res = 1/res;
    return res;
}

float ResEquivSerie(float res1, float res2, float res3, float res4)
{
    return res1 + res2 + res3 + res4;
}

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

    QuatroParaleloZeroSerie();
    TresParaleloUmSerie();
    DoisParaleloDoisSerie();
    UmParaleloTresSerie();
    ZeroParaleloQuatroSerie();

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
