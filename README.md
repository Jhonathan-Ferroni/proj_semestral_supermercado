<h1>Projeto Estrutura de Dados</h1>

## Descrição

Este projeto é uma aplicação de gerenciamento de usuários e produtos utilizando estruturas de dados como pilhas e filas. O objetivo é fornecer uma interface para adicionar, excluir e exibir usuários, além de gerenciar produtos em um carrinho de compras e em gondolas.

## Linguagens Utilizadas

-[![My Skills](https://skillicons.dev/icons?i=c)](https://skillicons.dev)

## Estrutura do Projeto

O projeto é composto pelos seguintes arquivos:

- `main.c`: Contém a função principal e a lógica de gerenciamento de usuários.
- `pilhas.c`: Implementa as operações relacionadas às pilhas de produtos.
- `fila.c`: Implementa as operações relacionadas às filas de atendimento.
- `main.h`: Declarações de funções e definições de tipos utilizados em `main.c`.
- `pilhas.h`: Declarações de funções e definições de tipos utilizados em `pilhas.c`.
- `fila.h`: Declarações de funções e definições de tipos utilizados em `fila.c`.

## Principais Métodos

### main.c

- `void criadat()`: Cria o arquivo de usuários padrão se não existir.
- `int comparalogin(char nome[50], char pront[10])`: Compara o login do usuário com os registros no arquivo.
- `void bubblesort(reg* registros, int n)`: Ordena os registros de usuários pelo nome.
- `int carregavetor(const char* Arq, reg** registros)`: Carrega os registros de usuários do arquivo para um vetor.
- `void salvadat(const char* Arq, reg* registros, int n)`: Salva os registros de usuários do vetor para o arquivo.
- `void menuprincipal(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario)`: Exibe o menu principal do programa.
- `void exibirRegistros(reg* registros, int n)`: Exibe os registros de usuários.
- `int adicionarusuario()`: Adiciona um novo usuário ao sistema.
- `int excluirusuarios()`: Exclui todos os usuários e recria o arquivo de usuários padrão.

### pilhas.c

- `void inicializarGondolas(PILHA gondolas[])`: Inicializa as pilhas de produtos (gondolas).
- `void menupilhas(PILHA gondolas[], int numGondolas, CARRINHO* carrinho, char usuario)`: Exibe o menu de operações com as pilhas de produtos.

### fila.c

- `void inicializarFila(FILA* f)`: Inicializa a fila de atendimento.
- `bool estaVaziaFila(FILA* f)`: Verifica se a fila está vazia.
- `bool inserirNaFila(FILA* f, REGISTRO reg)`: Insere um registro na fila.
- `bool removerDaFila(FILA* f, REGISTRO* reg)`: Remove um registro da fila.
- `void caixaEletronico(CARRINHO* carrinho, PILHA gondolas[])`: Simula o atendimento no caixa eletrônico.

## Roadmap

### Versão 1.0

- [x] Implementar gerenciamento de usuários (adicionar, excluir, exibir).
- [x] Implementar operações com pilhas de produtos (gondolas).
- [x] Implementar operações com filas de atendimento.
- [x] Criar arquivo de usuários padrão.
- [x] Ordenar registros de usuários.
- [x] Exibir menu principal e menus de operações.

### Versão 2.0

- [ ] Adicionar interface gráfica para o programa.
- [ ] Implementar persistência de dados em banco de dados.
- [ ] Adicionar autenticação de usuários.
- [ ] Melhorar a usabilidade e a experiência do usuário.

### Versão 3.0

- [ ] Adicionar interface gráfica para o programa.
- [ ] Implementar persistência de dados em banco de dados.
- [ ] Adicionar autenticação de usuários.
- [ ] Melhorar a usabilidade e a experiência do usuário.

## Como Executar

1. Clone o repositório:
 git clone https://github.com/seu-usuario/projeto-estrutura.git
2. Navegue até o diretório do projeto:
 cd projeto-estrutura  
3. Compile o projeto:
 gcc main.c pilhas.c fila.c -o supermercado
4. Execute o programa:
 ./supermercado
## Contribuição

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests para melhorias e correções.
