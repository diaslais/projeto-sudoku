#include <stdio.h>
#define MAX 9

void recebeTabuleiro(char matriz[][MAX]);
void imprimeTabuleiro(char matriz[][MAX]);
int ehPonto(int linha, int coluna, char matriz[][MAX]);
void defineSetor(int linha, int coluna, char matriz[][MAX], char setor[]);
int verificaSePossivel(int linha, int coluna, char matriz[][MAX], char itemDaLista);
char geraProvisorio(int linha, int coluna, char lista[], int posicaoLista, char matriz[][MAX]);
int resolveAi(int i, int j, char lista[], char matriz[][MAX]);

int main(){
	int i, j, solucao;
	char tabuleiro[MAX][MAX], resolvido[MAX][MAX];
	recebeTabuleiro(tabuleiro);
	char lista[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int ponto = 0;

	//cria uma cópia do tabuleiro inicial na matriz do tabuleiro resolvido
	for(int x = 0; x < MAX; ++x){
		for(int y = 0; y < MAX; ++y)
			resolvido[x][y] = tabuleiro[x][y];
	}

	//loop para achar as coordenadas do primeiro ponto
	for(int x = 0; x < MAX; ++x){
		for(int y = 0; y < MAX; ++y){
			ponto = ehPonto(x, y, resolvido);
			if(ponto == 1){
				i = x;
				j = y;
				break;
			}
		}
		if(ponto == 1){
			break;
		}
	}
	if(ponto == 0)
 		printf("O tabuleiro já está resolvido ;)");
	
	solucao = resolveAi(i, j, lista, resolvido);
	if(solucao == 0)
		printf("Não há solução para esse tabuleiro :(");
	else if(solucao == 1){
		printf("A solução deste Sudoku é:\n");
		imprimeTabuleiro(resolvido);
		}
	return 0;
}

//recebe uma matriz vazia representando o tabuleiro
//armazena nela o input do usuário
void recebeTabuleiro(char matriz[][MAX]){
        int i, j;

        for(i = 0; i < MAX; ++i){
         	char lista[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
       		for(j = 0; j < MAX; ++j)
                        scanf("%s", &matriz[i][j]);
	}
}

void imprimeTabuleiro(char matriz[][MAX]){
	for(int x = 0; x < MAX; ++x){
		printf("%2d: ", x);
		for(int y = 0; y < MAX; ++y)
			printf("%2c", matriz[x][y]);
		printf("\n");
	}
}

//recebe o tabuleiro e a linha e coluna de um elemento do tabuleiro
//indica se o elemento em questão é um ponto ou não
int ehPonto(int linha, int coluna, char matriz[][MAX]){
	if(matriz[linha][coluna] == '.')
		return 1;
	return 0;
}

//recebe linha e coluna de um elemento do tabuleiro, o tabuleiro e um vetor vazio
//o vetor vazio receberá os elementos contidos no "setor" daquele elemento
void defineSetor(int linha, int coluna, char matriz[][MAX], char setor[]){
        int i, j;
        int divlinha = linha / 3;
        int divcoluna = coluna / 3;
        int k = 0;

        for(i = 3 * divlinha; i / 3 == divlinha; ++i){
                for(j = 3 * divcoluna; j / 3 == divcoluna; ++j){
                        setor[k] = matriz[i][j];
                        ++k;
                }
        }
}

//recebe linha e coluna de um ponto do tabuleiro, o tabuleiro, um item da lista de 1 a 9 e o setor do ponto
//irá verificar se o item desejado da lista de 1 a 9 pode ser usado como um número substituto para o ponto
//para isso compara o item da lista com a linha, coluna e setor do ponto
int verificaSePossivel(int linha, int coluna, char matriz[][MAX], char itemDaLista){
	char setor[MAX];
	defineSetor(linha, coluna, matriz, setor);
	int i;

	for(i = 0; i < MAX; ++i){
		if(itemDaLista == matriz[linha][i] || itemDaLista == matriz[i][coluna] || itemDaLista == setor[i]){
			return 0;
		}
	}
	return 1;
}

//recebe linha e coluna de um ponto, a lista de 1 a 9, uma posicao dessa lista, o tabuleiro e o setor do ponto
//verifica se cada item da lista pode ser usado como provisório (função verificaSePossível) e se puder, retorna esse item
//a posiçãoLista serve para determinar a partir de que elemento da lista deverá ser feita a verificação (se você já gerou um provisório que não deu certo, você não precisa verificar a lista toda de novo, mas só a partir desse elemento que não deu certo)
char geraProvisorio(int linha, int coluna, char lista[], int posicaoLista, char matriz[][MAX]){
	int i, posicaoProvisorio, pode;
	char numProvisorio;
	pode = 0;
	
	for(i = posicaoLista; i < MAX; ++i){
		pode = verificaSePossivel(linha, coluna, matriz, lista[i]);
		if(pode == 1){
			posicaoProvisorio = i;
			break;
		}
	}
	numProvisorio = lista[posicaoProvisorio];
	if(pode == 0)
		numProvisorio = 'a';
	return numProvisorio;
}

//recebe a linha e coluna (i e j) do primeiro ponto encontrado no tabuleiro, o tabuleiro e o setor
//gera o primeiro provisório, busca as coordenadas do próximo ponto e usa recursividade para repetir esse processo até o último ponto 
int resolveAi(int i, int j, char lista[], char matriz[][MAX]){
	char provisorio = geraProvisorio(i, j, lista, 0, matriz);

	if(provisorio == 'a')
		return 0;//se não houver provisório possível para o primeiro ponto, não há soluao para este tabuleiro
	else
		matriz[i][j] = provisorio;

	int restoSolucao, posicaoLista;
	int ponto = 0;
	int p, q;
	for(int x = 0; x < MAX; ++x){
		for(int y = 0; y < MAX; ++y){
			ponto = ehPonto(x, y, matriz);
			if(ponto == 1){
				p = x;
				q = y;
				break;
			}
		}
		if(ponto == 1){
			break;
		}
	}
	if(ponto == 1){
		while(1){
			restoSolucao = resolveAi(p, q, lista, matriz);
			if(restoSolucao == 1)
				return 1; //significa que não tem mais pontos
			else if(restoSolucao == 0){
				for(int k = 0; k < MAX; ++k){
					if(matriz[i][j] == lista[k])
						posicaoLista = k + 1; //pode checar só a partir do próximo
				}	
				matriz[i][j] = '.';
				provisorio = geraProvisorio(i, j, lista, posicaoLista, matriz);
				if(provisorio == 'a')
					return 0;//não tem solução possível
				else
					matriz[i][j] = provisorio;
			}
		}
	}
	else if(ponto == 0)//significa que não há mais pontos no tabuleiro para serem decifrados, já resolveu
		return 1;
}

