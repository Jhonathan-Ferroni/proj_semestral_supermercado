
// • Objetivo: Gerar a aplicação em Linguagem C para gerenciar estruturas de dados no contexto de um supermercado.

/*
    Funcionamento:
    1. Login de acesso: Arquivos, struct, ordenação e busca binária;
    2. Abastecimento das Gôndolas: Arquivos, struct e Pilha;
    3. Caixa/PDV: Arquivos, struct e Fila.
*/


/* 31/10/2024, O login funciona perfeitamente, preciso implementar um metodo de ordenação no arquivo .dat*/
/* 01/11/2024, Acabo de incluir a ordenação do arquivo .dat.*/
/* 14/11/2024 função criadat funcionando*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>


typedef struct
{
    char nome[50];
    char pront[14];
}reg;

reg registro;

void criadat();
int comparalogin(char nome[50], char pront[10]);
void bubblesort(reg *registros, int n);
int carregavetor(const char *Arq, reg**registros);
void salvadat(const char *Arq, reg *registros, int n);
void exibirRegistros(reg *registros, int n);

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

    //tendo armazenado o login inserido pelo usuario sera chamada a função que ira comparar o dados do login com os cadastros do .DAT
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

void exibirRegistros(reg *registros, int n) {
    printf("\nLista de registros:\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s, Prontuário: %s\n", registros[i].nome, registros[i].pront);
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

        // Pula espaços extras, se houver, no começo do prontuário
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

int carregavetor(const char *Arq, reg**registros )
{
    FILE *file = fopen(Arq, "r");
    if (file==NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    // Inicialização do contador de registros
    int count = 0;
    char linha[200];

    // Primeiro, contamos quantos registros existem para alocar a memória corretamente
    while (fgets(linha, sizeof(linha), file)) {
        count++;
    }

    // Volta para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Aloca memória para o número de registros
    *registros = (reg *)malloc(count * sizeof(reg));
    if (*registros == NULL) {
        perror("Erro ao alocar memória para registros");
        fclose(file);
        return -1;
    }

    int i = 0;  // Índice para armazenar os registros

    // Agora, lê o arquivo novamente e armazena os dados
    while (fgets(linha, sizeof(linha), file)) {
        // Remove a quebra de linha, se houver
        linha[strcspn(linha, "\n")] = '\0';

        // Separar o nome e o prontuário usando a vírgula como delimitador
        char *nome = strtok(linha, ",");
        char *prontuario = strtok(NULL, ",");

        // Remover espaços extras do prontuário, se houver
        if (prontuario != NULL) {
            while (*prontuario == ' ') prontuario++;
        }

        // Copia o nome para o registro garantindo que nome não seja NULL
        strncpy((*registros)[i].nome, nome ? nome : "", sizeof((*registros)[i].nome) - 1);
         // Garantir que termine com '\0'
        (*registros)[i].nome[sizeof((*registros)[i].nome) - 1] = '\0';

        // copia o prontuario para o registro garantindo que prontuario não seja NULL
        strncpy((*registros)[i].pront, prontuario ? prontuario : "", sizeof((*registros)[i].pront) - 1);
        // Garantir que termine com '\0'
        (*registros)[i].pront[sizeof((*registros)[i].pront) - 1] = '\0'; 

        i++;  // Avança para o próximo registro
    }

    fclose(file);
    return count;  // Retorna o número de registros lidos
}

void bubblesort(reg *registros, int n)
{
    FILE * Arq;
    Arq = fopen ("USUARIOS.DAT" , "rb");
    if ( Arq == NULL )
    {
    	printf ("\nErro ao abrir USUARIOS.DAT");
    	getch();
    	exit(0);
	}
    int i, j;
    reg temp;
    for(i=0;i<n-1;i++){
        for(j=0; j<n-i-1;j++){
            if(strcmp(registros[j].nome, registros[j+1].nome)>0){
                temp = registros[j];
                registros[j] = registros[j+1];
                registros[j+1] = temp;
            }
        }
    }
}

void salvadat(const char *Arq, reg *registros, int n)
{
    FILE *file = fopen(Arq, "wb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }
    
    
    int i;
    for(i=0; i<n;i++)
        fprintf(file, "%s, %s\n", registros[i].nome, registros[i].pront);
    fclose(file);
}

void criadat()
{
	FILE *Arq; 
	Arq = fopen( "USUARIOS.DAT", "w");
	if ( Arq == NULL )
    {
    	printf ("\nErro ao abrir USUARIOS.DAT");
    	getch();
    	exit(1);
	}
	reg usuariospadrao[30] = { {"Domingos Lucas Latorre de Oliveira", ", SP146456;"}, {"Leandro Pinto Santana", ", SP220383;"}, {"Rodrigo Ribeiro de Oliveira", ", SP134168;"}, {"Andre Luiz da Silva", ", SP030028;"}, {"Claudia Miyuki Werhmuller", ", SP030041;"}, {"Claudete de Oliveira Alves", ", SP03020X;"}, {"Francisco Verissimo Luciano", ", SP030247;"}, {"Luk Cho Man", ", SP060380;"}, {"Ivan Francolin Martinez", ", SP060835;"}, {"Joao Vianei Tamanini", ", SP060914;"}, {"Jose Oscar Machado Alexandre", ", SP070038;"}, {"Jose Braz de Araujo", ", SP070385;"}, {"Paulo Roberto de Abreu", ", SP070816;"}, {"Eurides Balbino da Silva", ", SP07102X;"}, {"Domingos Bernardo Gomes Santos", ", SP090888;"}, {"Andre Evandro Lourenco", ", SP100092;"}, {"Miguel Angelo Tancredi Molina", ", SP102763;"}, {"Antonio Airton Palladino", ", SP112197;"}, {"Luis Fernando Aires Branco Menegueti", ", SP145385;"}, {"Antonio Ferreira Viana", ", SP200827;"}, {"Leonardo Bertholdo", ", SP204973;"}, {"Marcelo Tavares de Santana", ", SP20500X;"}, {"Wagner de Paula Gomes", ", SP215016;"}, {"Daniel Marques Gomes de Morais", ", SP220097;"}, {"Alexandre Beletti Ferreira", ", SP226117;"}, {"Vladimir Camelo Pinto", ", SP240291;"}, {"Leonardo Andrade Motta de Lima", ", SP24031X;"}, {"Aldo Marcelo Paim", ", SP240497;"}, {"Cesar Lopes Fernandes", ", SP890534;"}, {"Josceli Maria Tenorio", ", SZ124382;"} };
	int i;
	for(i=0;i<30;i++)
	{
		fprintf(Arq , "%s%s\n", usuariospadrao[i].nome , usuariospadrao[i].pront);
	}
	fclose(Arq);
	printf("USUARIOS.DAT criado com sucesso\n");
}

int main()
{
	criadat();
    reg *registros;
    const char *Arq = "USUARIOS.DAT";
    //n = numero de registros
    int n = carregavetor(Arq, &registros);
    if (n < 0) {
        return 1;
    }
    exibirRegistros(reg *registros, int n);
    bubblesort(registros, n);
    salvadat(Arq, registros, n);

    menu();
    return 0;
}
