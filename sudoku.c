#include <stdio.h>
#define MAX 9

char lista[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

void recebeTabuleiro(char matriz[MAX][MAX]);
int ehPonto(int linha, int coluna, char matriz[MAX][MAX]);
void defineSetor(int linha, int coluna, char matriz[MAX][MAX], char vetor[]);


int main(){
	int i, j;
	char tabuleiro[MAX][MAX];
	recebeTabuleiro(tabuleiro);

	return 0;
}

void recebeTabuleiro(char matriz[MAX][MAX]){
        int i, j;

        for(i = 0; i < MAX; ++i){
                for(j = 0; j < MAX; ++j)
                        scanf("%s", &matriz[i][j]);
	}
}

int ehPonto(int linha, int coluna, char matriz[MAX][MAX]){
	if(matriz[linha][coluna] == '.')
		return 1;
	return 0;
}

void defineSetor(int linha, int coluna, char matriz[MAX][MAX], char vetor[]){
        int i;
        int j;
        int divlinha = linha / 3;
        int divcoluna = coluna / 3;
        int k = 0;

        for(i = 3 * divlinha; i / 3 == divlinha; ++i){
                for(j = 3 * divcoluna; j / 3 == divcoluna; ++j){
                        vetor[k] = matriz[i][j];
                        ++k;
                }
        }
}

