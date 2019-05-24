#include<iostream>
#include <stdlib.h>
using namespace std;

const int P = 5;//Número de processos
const int R = 3;//Número de recursos

int** calculateNeed(int maximo[P][R], int alocado[P][R]){// Calcula numero de recurso necessario para cada processo
    // Matriz da necessidade de recursos
    int **necessita = (int**)malloc(P*sizeof(int*));
    for(int i = 0; i < P ; i++)
    	necessita[i] = (int*) malloc (R*sizeof(int));
    for (int i = 0 ; i < P ; i++){
    	for (int j = 0 ; j < R ; j++)
    		necessita[i][j] = maximo[i][j] - alocado[i][j];
    }
    return necessita;
}

bool isSafe(int processos[], int disponivel[], int maximo[][R], int alocado[][R]){// Descobrir se o sistema está seguro ou nao
    int **necessita = calculateNeed(maximo, alocado);

    bool terminado[P] = {0};// processos ainda não foram finalizados

    int sequencia[P];// Salva a sequência dos processos

    int recursos[R];// Cópia dos recursos

    for (int i = 0; i < R ; i++)
        recursos[i] = disponivel[i];
    int cont = 0;
    while (cont < P){
    	//encontra processo que ainda não foi finalizado e dá recursos a ele
        bool encontrado = false;
        for (int p = 0; p < P; p++){
            if (terminado[p] == 0){
            	int j;
                for (j = 0; j < R; j++){
                    if (necessita[p][j] > recursos[j])
                        break;
                }
                if (j == R){
                    for (int k = 0 ; k < R ; k++)
                        recursos[k] += alocado[p][k];

                    sequencia[cont++] = p;
                    terminado[p] = 1;
                    encontrado = true;
                }
            }
        }
        if (encontrado == false){
            cout << "O sistema nao se encontra em estado seguro" << endl;
            return false;
        }
    }
    cout << "O sistema se encontra em estado seguro.\nA sequencia eh: ";
    for (int i = 0; i < P ; i++)
        cout << sequencia[i] << " ";
    cout << endl;
    return true;
}

int main(){
    int processos[] = {0, 1, 2, 3, 4};
    int disponivel[] = {3, 3, 2};

    int maximo[][R] = {{7, 5, 3},
                       {3, 2, 2},
                       {9, 0, 2},
                       {2, 2, 2},
                       {4, 3, 3}};

    int alocado[][R] = {{0, 1, 0},
                        {2, 0, 0},
                        {3, 0, 2},
                        {2, 1, 1},
                        {0, 0, 2}};
    isSafe(processos, disponivel, maximo, alocado);
    return 0;
}
