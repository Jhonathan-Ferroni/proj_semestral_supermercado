
// • Objetivo: Gerar a aplicação em Linguagem C para gerenciar estruturas de dados no contexto de um supermercado.

/*
    Funcionamento:
    1. Login de acesso: Arquivos, struct, ordenação e busca binária;
    2. Abastecimento das Gôndolas: Arquivos, struct e Pilha;
    3. Caixa/PDV: Arquivos, struct e Fila.
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    char nome[50];
    char pront[10];
}reg;

reg registro;

int comparalogin(char nome[50], char pront[10]);

void menu()
{
    printf("\n NOME DO USUARIO : ");
    fgets(registro.nome, sizeof(registro.nome), stdin);

    // Remover o '\n' capturado por fgets
    registro.nome[strcspn(registro.nome, "\n")] = '\0';


    printf("\n PRONTUARIO DO USUARIO : ");
    scanf("%s", registro.pront);

   // Limpar o buffer de entrada após scanf= '\0';
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    //aqui armazenar o login em variaveis e compara-las com os nomes e registro.pronts do arquivo.dat
    int a = comparalogin(registro.nome, registro.pront);
    if(a==0)
    {
        system("cls");
        printf("\nACESSO NEGADO!");
        getch();
        exit(1);
    }
    else
    {
        system("cls");
        printf("\nACESSO CONCEDIDO!");
    }        

}

int comparalogin(char usuario[50], char pront[10])
{
    FILE * Arq;
    Arq = fopen ("USUARIOS.DAT" , "r");
    if ( Arq == NULL )
    {
    	printf ("\nErro ao abrir USUARIOS.DAT");
    	getch();
    	exit(0);
	}
    //aqui irei comparar cada linha com o login inserido pelo usuario
    char linha[200];
    while (fgets(linha, sizeof(linha), Arq)) {
        // Remover o caractere de nova linha e ponto e vírgula, se presentes, pois podem prejudicar a comparação já que ' SP9910200;' != 'SP9910200'
        //linha[strcspn(linha, "\n")]  retorna um indice e nesse indice substituimos o conteudo que escolhermos 
        //por outro que escolhermos, caso encontrado.
        linha[strcspn(linha, "\n")] = '\0';
        linha[strcspn(linha, ";")] = '\0';
        //sendo X o indice onde foi encontrado '\n' e ';'
        //linha[X] = 'vazio';
        //linha[X] = 'vazio';


        // Separar a linha em nome e prontuário usando a vírgula como delimitador
        // armazena em *nome tudo que tem antes da virgula
        char *nome = strtok(linha, ",");
        // armazena em registro.prontLinha o que ha depois da virgula
        char *prontuarioLinha = strtok(NULL, ",");

        // Remover espaços extras, se houver, no começo do prontuário
        if (prontuarioLinha != NULL) {
            while (*prontuarioLinha == ' ') prontuarioLinha++;
        }

        // Comparar o nome e o prontuário com os fornecidos pelo usuário
        if (strcmp(nome, usuario) == 0 && strcmp(prontuarioLinha, pront) == 0) {
            fclose(Arq);
            return 1;  // Retorna 1 se a combinação for encontrada
        }
    }

    fclose(Arq);
    return 0;  // Retorna 0 se não encontrar a combinação
}


int main()
{
    menu();
    return 0;
}
