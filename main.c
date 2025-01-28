#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "pilhas.h"

reg registro;

void criadat();
int comparalogin(char nome[50], char pront[10]);
void bubblesort(reg* registros, int n);
int carregavetor(const char* Arq, reg** registros);
void salvadat(const char* Arq, reg* registros, int n);
void exibirRegistros(reg* registros, int n);
int adicionarusuario();
int excluirusuarios();

void menuprincipal(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario)
{
    system("color 17");
    printf("\n NOME DO USUARIO : ");
    fgets(registro.nome, sizeof(registro.nome), stdin);

    // Remover o '\n' capturado por fgets
    registro.nome[strcspn(registro.nome, "\n")] = '\0';

    printf("\n PRONTUARIO DO USUARIO : ");
    scanf("%s", registro.pront);

    // Limpar o buffer de entrada após scanf= '\0';
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    //tendo armazenado o login inserido pelo usuario sera chamada a função que ira comparar o dados do login com os cadastros do .DAT
    int a = comparalogin(registro.nome, registro.pront);
    if (a == 0)
    {
        system("cls");
        system("color 40");
        printf("\nACESSO NEGADO!");
        getch();
        exit(1);
    }
    else
    {

        system("cls");
        system("color 17");
        printf("\nACESSO CONCEDIDO!\n");
        menupilhas(gondolas, numGondolas, carrinho, registro.user[0]); // Chamada correta da função menupilhas
        getch();
    }
}

void exibirRegistros(reg* registros, int n) {
    printf("\nLista de registros:\n");
    for (int i = 0; i < n; i++) {
        printf("Nome: %s, Prontuario: %s, Usuario: %s\n", registros[i].nome, registros[i].pront, registros[i].user); // Adicionando a nova informação
    }
}

int comparalogin(char usuario[50], char pront[10])
{
    FILE* Arq;
    Arq = fopen("USUARIOS.DAT", "r");
    if (Arq == NULL)
    {
        printf("\nErro ao abrir USUARIOS.DAT");
        getch();
        exit(0);
    }
    //aqui irei comparar cada linha com o login inserido pelo usuario
    char linha[200];
    while (fgets(linha, sizeof(linha), Arq)) {
        // Remover o caractere de nova linha e ponto e vírgula, se presentes, pois podem prejudicar a comparação já que ' SP9910200;' != 'SP9910200'
        linha[strcspn(linha, "\n")] = '\0';

        // Separar a linha em nome, prontuário e usuário usando ponto e vírgula como delimitador
        char* nome = strtok(linha, ";");
        char* prontuarioLinha = strtok(NULL, ";");
        char* usuarioLinha = strtok(NULL, ";");

        // Pula espaços extras, se houver, no começo do prontuário
        if (prontuarioLinha != NULL) {
            while (*prontuarioLinha == ' ') prontuarioLinha++;
        }

        // Comparar o nome e o prontuário com os fornecidos pelo usuário
        if (strcmp(nome, usuario) == 0 && strcmp(prontuarioLinha, pront) == 0) {
            strncpy(registro.user, usuarioLinha, sizeof(registro.user) - 1);
            registro.user[sizeof(registro.user) - 1] = '\0'; // Garante terminação '\0'
            fclose(Arq);
            return 1;  // Retorna 1 se a combinação for encontrada
        }
    }

    fclose(Arq);
    return 0;  // Retorna 0 se não encontrar a combinação
}

int carregavetor(const char* Arq, reg** registros)
{
    FILE* file = fopen(Arq, "r");
    if (file == NULL) {
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
    *registros = (reg*)malloc(count * sizeof(reg));
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

        // Separar o nome, prontuário e usuário usando ponto e vírgula como delimitador
        char* nome = strtok(linha, ";");
        char* prontuario = strtok(NULL, ";");
        char* usuario = strtok(NULL, ";");

        // Remover espaços extras do prontuário, se houver
        if (prontuario != NULL) {
            while (*prontuario == ' ') prontuario++;
        }

        // Copia o nome para o registro garantindo que nome não seja NULL
        strncpy((*registros)[i].nome, nome ? nome : "", sizeof((*registros)[i].nome) - 1);
        // Garantir que termine com '\0'
        (*registros)[i].nome[sizeof((*registros)[i].nome) - 1] = '\0';

        // Copia o prontuário para o registro garantindo que prontuário não seja NULL
        strncpy((*registros)[i].pront, prontuario ? prontuario : "", sizeof((*registros)[i].pront) - 1);
        // Garantir que termine com '\0'
        (*registros)[i].pront[sizeof((*registros)[i].pront) - 1] = '\0';

        // Copia o usuário para o registro garantindo que usuário não seja NULL
        strncpy((*registros)[i].user, usuario ? usuario : "", sizeof((*registros)[i].user) - 1);
        // Garantir que termine com '\0'
        (*registros)[i].user[sizeof((*registros)[i].user) - 1] = '\0';

        i++;  // Avança para o próximo registro
    }

    fclose(file);
    return count;  // Retorna o número de registros lidos
}

void bubblesort(reg* registros, int n)
{
    FILE* Arq;
    Arq = fopen("USUARIOS.DAT", "rb");
    if (Arq == NULL)
    {
        printf("\nErro ao abrir USUARIOS.DAT");
        getch();
        exit(0);
    }
    int i, j;
    reg temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(registros[j].nome, registros[j + 1].nome) > 0) {
                temp = registros[j];
                registros[j] = registros[j + 1];
                registros[j + 1] = temp;
            }
        }
    }
}

void salvadat(const char* Arq, reg* registros, int n)
{
    FILE* file = fopen(Arq, "wb");
    if (!file) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    int i;
    for (i = 0; i < n; i++)
        fprintf(file, "%s;%s;%s\n", registros[i].nome, registros[i].pront, registros[i].user); // Adicionando a nova informação
    fclose(file);
}

void criadat()
{
    FILE* Arq;
    Arq = fopen("USUARIOS.DAT", "a+");
    if (Arq == NULL)
    {
        printf("\nErro ao abrir USUARIOS.DAT");
        getch();
        exit(1);
    }
    fseek(Arq, 0, SEEK_END);
    long tamanho = ftell(Arq);
    if (tamanho == 0) {
        // Se o arquivo estiver vazio, escreve os usuários padrão
        reg usuariospadrao[30] = {
            {"Domingos Lucas Latorre de Oliveira", "SP146456", "r"},
            {"Leandro Pinto Santana", "SP220383", "r"},
            {"Rodrigo Ribeiro de Oliveira", "SP134168", "r"},
            {"Andre Luiz da Silva", "SP030028", "r"},
            {"Claudia Miyuki Werhmuller", "SP030041", "r"},
            {"Claudete de Oliveira Alves", "SP03020X", "r"},
            {"Francisco Verissimo Luciano", "SP030247", "r"},
            {"Luk Cho Man", "SP060380", "r"},
            {"Ivan Francolin Martinez", "SP060835", "r"},
            {"Joao Vianei Tamanini", "SP060914", "r"},
            {"Jose Oscar Machado Alexandre", "SP070038", "r"},
            {"Jose Braz de Araujo", "SP070385", "r"},
            {"Paulo Roberto de Abreu", "SP070816", "r"},
            {"Eurides Balbino da Silva", "SP07102X", "r"},
            {"Domingos Bernardo Gomes Santos", "SP090888", "r"},
            {"Andre Evandro Lourenco", "SP100092", "r"},
            {"Miguel Angelo Tancredi Molina", "SP102763", "r"},
            {"Antonio Airton Palladino", "SP112197", "r"},
            {"Luis Fernando Aires Branco Menegueti", "SP145385", "r"},
            {"Antonio Ferreira Viana", "SP200827", "r"},
            {"Leonardo Bertholdo", "SP204973", "r"},
            {"Marcelo Tavares de Santana", "SP20500X", "r"},
            {"Wagner de Paula Gomes", "SP215016", "r"},
            {"Daniel Marques Gomes de Morais", "SP220097", "r"},
            {"Alexandre Beletti Ferreira", "SP226117", "r"},
            {"Vladimir Camelo Pinto", "SP240291", "r"},
            {"Leonardo Andrade Motta de Lima", "SP24031X", "r"},
            {"Aldo Marcelo Paim", "SP240497", "r"},
            {"Cesar Lopes Fernandes", "SP890534", "r"},
            {"Josceli Maria Tenorio", "SZ124382", "r"}
        };
        int i;
        for (i = 0; i < 30; i++) {
            fprintf(Arq, "%s;%s;%s\n", usuariospadrao[i].nome, usuariospadrao[i].pront, usuariospadrao[i].user);
        }
    }
    fclose(Arq);
}

int main()
{
    system("cls");
    criadat();
    reg* registros;
    const char* Arq = "USUARIOS.DAT";
    //n = numero de registros
    int n = carregavetor(Arq, &registros);
    if (n < 0) {
        return 1;
    }
    bubblesort(registros, n);
    salvadat(Arq, registros, n);

    PILHA gondolas[NUM_GONDOLAS];
    CARRINHO carrinho;
    carrinho.topo = NULL;
    inicializarGondolas(gondolas);

    menuprincipal(gondolas, NUM_GONDOLAS, &carrinho, 'u'); // Passando os parâmetros necessários
    return 0;
}

int adicionarusuario()
{
    
    reg novo;
    fflush(stdin);
    printf("Nome do usuario: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';
    fflush(stdin);
    printf("Prontuario: ");
    fgets(novo.pront, sizeof(novo.pront), stdin);
    novo.pront[strcspn(novo.pront, "\n")] = '\0';
    fflush(stdin);
    printf("Tipo de usuario (r/u): ");
    scanf(" %c", &novo.user[0]);
    novo.user[1] = '\0';
    // Carregar registros existentes
    reg* registros;
    int n = carregavetor("USUARIOS.DAT", &registros);
    if (n < 0) {
        printf("Erro ao carregar registros existentes.\n");
        return 1;
    }
    // Realocar memória para o novo registro
    registros = (reg*)realloc(registros, (n + 1) * sizeof(reg));
    if (registros == NULL) {
        printf("Erro ao alocar memória para o novo registro.\n");
        return 2;
    }
    // Adicionar o novo registro
    registros[n] = novo;

    // Salvar todos os registros de volta no arquivo
    salvadat("USUARIOS.DAT", registros, n + 1);

    // Liberar a memória alocada
    free(registros);
    bubblesort(registros, n);
    printf("Usuario adicionado com sucesso.\n");
}

int excluirusuarios()
{
    criadat();
    reg* registros;
    const char* Arq = "USUARIOS.DAT";
    int n = carregavetor(Arq, &registros);
    if (n < 0) {
        return 1;}
	salvadat(Arq, registros, n);
	printf("Sistema reiniciado!\n");
}


