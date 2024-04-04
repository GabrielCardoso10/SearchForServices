// inclusão das estruturas


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "imp.h"

int escolha_empresa;
int total_servicos_realizados = 0;



// Função para agendar um serviço para o cliente
void agendarServico(Cliente clientes[], int num_clientes, Empresa empresas[], int num_empresas, char *usuario) {

    char tipo_servico [ 50 ];
    int escolha;
    int empresa_selecionada;
    char horario [ 50 ];
    int horario_indisponivel = 0;


            printf("+------------------------------------------------+\n");
            printf("|                AGENDAR SERVIÇOS                |\n");
            printf("+------------------------------------------------+");
            printf("                                                 \n");
            printf(" 1 - CORTE DE CABELO                             \n");
            printf("                                                 \n");
            printf(" 2 - MANICURE/PEDICURE                           \n");
            printf("                                                 \n");
            printf(" 3 - MAQUIAGEM                                   \n");
            printf("                                                 \n");
            printf("                                                  \n");




    scanf("%d", &escolha);
    system ("cls");

    //switch case para agendamento de serviços
    switch ( escolha ) {
        case 1:
            strcpy(tipo_servico, "Corte de cabelo");
            break;
        case 2:
            strcpy(tipo_servico, "Manicure/Pedicure");
            break;
        case 3:
            strcpy(tipo_servico, "Maquiagem");
            break;
        default:
            printf("Opção inválida!\n");
            return;
    }

    printf("Empresas que oferecem %s:\n", tipo_servico);

    int encontrou_empresa = 0;

    for (int i = 0; i < num_empresas; i++) {
        if (strcmp(empresas[i].tipo_servico, tipo_servico) == 0) {
            printf("%d. %s\n", i + 1, empresas[i].nome);
            encontrou_empresa = 1;
        }
    }

    if (!encontrou_empresa) {
        printf("Nenhuma empresa oferece o serviço selecionado.\n");

        return;
    }

    printf("Escolha a empresa desejada: ");
    scanf("%d", &empresa_selecionada);

    empresa_selecionada--; // Ajusta para o índice do array

    if (empresa_selecionada < 0 || empresa_selecionada >= num_empresas) {
        printf("Opção inválida!\n");
        return;
    }

    printf("Digite o horário desejado (formato hh:mm): ");
    scanf("%s", horario);

    // Verifica se o horário escolhido está indisponível para a mesma empresa

    for (int i = 0; i < MAX_SERVICOS; i++) {

        if (strcmp(empresas[empresa_selecionada].horarios_agendados[i], horario) == 0) {

            horario_indisponivel = 1;
            break;

        }
    }

    if ( horario_indisponivel ) {

        printf("Este horário está indisponível para esta empresa! \n");
        return;

    }

    printf("Serviço agendado com sucesso!\n");

    // Calcula o preço do serviço agendado
    float preco_servico = empresas[empresa_selecionada].preco_servico;

    // Atualiza o número de serviços realizados do cliente

    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].usuario, usuario) == 0) {

            clientes[i].servicos_realizados++;
            clientes[i].gasto_total += preco_servico; // Atualiza o gasto total do cliente

            break;
        }
    }

    // Atualiza o lucro total da empresa
    empresas[empresa_selecionada].lucro_total += preco_servico;

    // Atualiza o contador de serviços realizados pela empresa
    empresas[empresa_selecionada].servicos_realizados++;

    // Adiciona o horário ao array de horários agendados da empresa
    for (int i = 0; i < MAX_SERVICOS; i++) {
        if (strlen(empresas[empresa_selecionada].horarios_agendados[i]) == 0) {

            strcpy(empresas[empresa_selecionada].horarios_agendados[i], horario);

            break;
        }
    }
}


// Funçao para cadastrar um cliente
void cadastrarCliente(Cliente clientes[], int *num_clientes) {
               printf("+--------------------------------------------------+\n");
               printf("|                CADASTRO CLIENTE                  |\n");
               printf("+--------------------------------------------------+\n");

    printf("Informe o nome: ");
    scanf("%s", clientes[*num_clientes].nome);
    printf("Informe o CPF: ");
    scanf("%s", clientes[*num_clientes].cpf);
    printf("Informe o nome de usuário: ");
    scanf("%s", clientes[*num_clientes].usuario);
    printf("Informe a senha: ");
    scanf("%s", clientes[*num_clientes].senha);

    system ("cls");


    (*num_clientes)++;


               printf("+--------------------------------------------------+\n");
               printf("|            CADASTRO FEITO COM SUCESSO            |\n");
               printf("+--------------------------------------------------+\n");
}


// Função para ver a quantidade de serviços feitos pelo cliente
void verQuantidadeServicosFeitos(Cliente clientes[], int num_clientes, char *usuario) {

    int encontrado = 0; // Variável para indicar se o cliente foi encontrado

        printf("+--------------------------------------------------+\n");
        printf("|         QUANTIDADE DE SERVIÇOS FEITOS            |\n");
        printf("+--------------------------------------------------+\n");
        printf("\n");
        printf("Nome de usuário: %s\n", usuario);

    // Verifica se o usuário corresponde a algum cliente cadastrado
    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].usuario, usuario) == 0) {

            encontrado = 1; // Cliente encontrado
            printf("Você realizou %d serviço(s).\n", clientes[i].servicos_realizados);

            break; // Sai do loop após encontrar o cliente
        }
    }

    // Se o cliente não for encontrado, exibe uma mensagem de erro

    if (!encontrado) {

        printf("Cliente não encontrado!\n");
    }
}


// Funçã recursiva para calcular o gasto total do cliente
float calcularGastoTotalClienteRecursivo(Cliente clientes[], int num_clientes, int index, char *usuario) {
    if (index == num_clientes) {
        return 0; // Condição de parada: todos os clientes foram processados


    } else {
        // Se o nome de usuário do cliente atual corresponde ao especificado, soma seu gasto total

        if (strcmp(clientes[index].usuario, usuario) == 0) {

            return clientes[index].gasto_total + calcularGastoTotalClienteRecursivo(clientes, num_clientes, index + 1, usuario);

        } else {

            // Caso contrário, continua para o próximo cliente
            return calcularGastoTotalClienteRecursivo(clientes, num_clientes, index + 1, usuario);
        }
    }
}

// Função para calcular o gasto total do cliente (inicia o processo recursivo)
void verGastoTotalCliente(Cliente clientes[], int num_clientes, char *usuario) {

    float gasto_total = calcularGastoTotalClienteRecursivo(clientes, num_clientes, 0, usuario);
    printf("O total gasto pelo cliente %s foi: R$ %.2f\n", usuario, gasto_total);


}



// Função para atualizar dados do cliente
void atualizarDadosCliente(Cliente clientes[], int num_clientes, char *usuario) {
               printf("+--------------------------------------------------+\n");
               printf("|          ATUALIZAÇÃO DE DADOS CLIENTE            |\n");
               printf("+--------------------------------------------------+\n");

    int encontrado = 0; // Variável para indicar se o cliente foi encontrado

    // Procura o cliente pelo nome de usuário
    for (int i = 0; i < num_clientes; i++) {

        if (strcmp(clientes[i].usuario, usuario) == 0) {
            encontrado = 1; // Cliente encontrado

            // Solicita ao usuário que insira os novos dados
            printf("Informe o novo nome: ");
            scanf("%s", clientes[i].nome);
            printf("Informe o novo CPF: ");
            scanf("%s", clientes[i].cpf);
            printf("Informe a nova senha: ");
            scanf("%s", clientes[i].senha);
            system ("cls");

               printf("+--------------------------------------------------+\n");
               printf("|          DADOS ATUALIZADOS COM SUCESSO           |\n");
               printf("+--------------------------------------------------+\n");

            break; // Sai do loop após encontrar o cliente
        }
    }

    // Se o cliente não for encontrado, exibe uma mensagem de erro
    if (!encontrado) {
        printf("Cliente não encontrado!\n");
    }
}


//função para avaliar a empresa
void avaliarEmpresa(Empresa empresas[], int num_empresas, char *usuario) {

    int empresa_selecionada;
    float nota;

    printf("Empresas disponíveis para avaliação:\n");

    for (int i = 0; i < num_empresas; i++) {

        printf("%d. %s\n", i + 1, empresas[i].nome);
    }

    printf("Escolha a empresa que deseja avaliar: ");
    scanf("%d", &empresa_selecionada);

    empresa_selecionada--; // Ajusta para o índice do array

    if (empresa_selecionada < 0 || empresa_selecionada >= num_empresas) {
        printf("Opção inválida!\n");
        return;
    }

    printf("Digite a nota que deseja atribuir (de 0 a 10): ");
    //recolhe a nota de avaliação
    scanf("%f", &nota);

    if (nota < 0 || nota > 10) {
        printf("Nota inválida(insira uma nota acima de 0)!\n");
        return;
    }

    empresas[empresa_selecionada].avaliacoes[empresas[empresa_selecionada].num_avaliacoes++] = nota;

    printf("Avaliação registrada com sucesso!\n");
}

//função para calcular a media de nota das avaliaçoes de uma empresa
float calcularMediaAvaliacoes(Empresa empresas[], int empresa_index) {

    if (empresas[empresa_index].num_avaliacoes == 0) {
        return 0.0; // Retorna 0 se nao houver avaliaçoes
    }

    float soma = 0.0;

    for (int i = 0; i < empresas[empresa_index].num_avaliacoes; i++) {
        soma += empresas[empresa_index].avaliacoes[i];


    }
    return soma / empresas[empresa_index].num_avaliacoes;
}


// Função para listar empresas e permitir que o usuário escolha uma para ver a mídia das avaliações
void verMediaAvaliacoesEmpresas(Empresa empresas[], int num_empresas) {

    printf("Empresas disponíveis:\n");
    for (int i = 0; i < num_empresas; i++) {
        printf("%d. %s\n", i + 1, empresas[i].nome);
    }

    int escolha;

    printf("Escolha uma empresa para ver a média das avaliações: ");
    scanf("%d", &escolha);

    // Verifica se a escolha está dentro do intervalo válido
    if (escolha < 1 || escolha > num_empresas) {

        printf("Opção inválida!\n");
        return;

    }

    int empresa_index = escolha - 1; // Ajusta para o índice do array
    float media = calcularMediaAvaliacoes(empresas, empresa_index);

    printf("A média das avaliações da empresa %s é: %.2f\n", empresas[empresa_index].nome, media);
}


// Função para entrar na conta do cliente
void entrarContaCliente(Cliente clientes[], int num_clientes, Empresa empresas[], int num_empresas) {

    char usuario[50];
    char senha[50];
    char nome_empresa [50] ;
    int encontrado = 0; // Variável para indicar se o cliente foi encontrado

               printf("+--------------------------------------------------+\n");
               printf("|               LOGIN CLIENTE                      |\n");
               printf("+--------------------------------------------------+\n");
     printf("Digite o nome de usuário: ");
     scanf("%s", usuario);
     printf("Digite a senha: ");
     scanf("%s", senha);
     system("cls");


    // Verifica se o usuário e a senha correspondem a algum cliente cadastrado
    for (int i = 0; i < num_clientes; i++) {
        if (strcmp(clientes[i].usuario, usuario) == 0 && strcmp(clientes[i].senha, senha) == 0) {
            encontrado = 1; // Cliente encontrado
               printf("+--------------------------------------------------+\n");
               printf("|          ACESSO CONCEDIDO COM SUCESSO            |\n");
               printf("+--------------------------------------------------+\n");

            int opcao_cliente;

     //menu para quando usuário fizer login bem sucedido

    printf("+----------------------------------------------+\n");
    printf("|                 MENU  CLIENTE                |\n");
    printf("+----------------------------------------------+\n");
    printf("                                                \n");
    printf(" 1 - AGENDAR SERVIÇO                            \n");
    printf("                                                \n");
    printf(" 2 - QUANTIDADE DE SERVIÇOS FEITOS:             \n");
    printf("                                                \n");
    printf(" 3 - VER GASTO TOTAL:                           \n");
    printf("                                                \n");
    printf(" 4 - ATUALIZAR DADOS:                           \n");
    printf("                                                \n");
    printf(" 5 - FAZER AVALIAÇÃO                            \n");
    printf("                                                \n");
    printf(" 6 - VER MÉDIA DE AVALIAÇÃO DA EMPRESA          \n");
    printf("\n");
            printf("Opcao:");
            scanf("%d", &opcao_cliente);
            system("cls");

            switch(opcao_cliente) {
                case 1:
                    agendarServico(clientes, num_clientes, empresas, num_empresas, usuario);
                    break;
                case 2:
                    verQuantidadeServicosFeitos(clientes, num_clientes, usuario); // Passando o nome de usuário como parâmetro
                    break;
                case 3:
                    verGastoTotalCliente(clientes, num_clientes, usuario);
                    break;
                case 4:
                     atualizarDadosCliente(clientes, num_clientes, usuario);
                     break;
                case 5:
                     avaliarEmpresa(empresas, num_empresas, usuario);
                     break;
                case 6:
                     verMediaAvaliacoesEmpresas(empresas, num_empresas);
                     break;
                default:
                    printf("Opção inválida!\n");
            }

            break; // Sai do loop após encontrar o cliente
        }
    }

    // Se o cliente não for encontrado, exibe uma mensagem de erro
    if (!encontrado) {

            printf("+--------------------------------------------------+\n");
            printf("|            USUARIO OU SENHA INCORRETOS           |\n");
            printf("+--------------------------------------------------+\n");
    }

}


// Função recursiva para calcular o lucro total da empresa específica
float calcularLucroTotalEmpresaRecursivo(Empresa empresas[], int num_empresas, int index, char *usuario) {

    if (index == num_empresas) {
        return 0; // Condição de parada: todas as empresas foram processadas

    } else {

        // Se encontrarmos a empresa com o nome de usuário especificado, retornamos seu lucro total
        if (strcmp(empresas[index].usuario, usuario) == 0) {

            return empresas[index].lucro_total;
        } else {

            // Caso contrário, continuamos para a próxima empresa
            return calcularLucroTotalEmpresaRecursivo(empresas, num_empresas, index + 1, usuario);
        }
    }
}

// Função para calcular o lucro total de uma empresa específica
void verLucroTotalEmpresa(Empresa empresas[], int num_empresas, char *usuario) {

    float lucro_total = calcularLucroTotalEmpresaRecursivo(empresas, num_empresas, 0, usuario);
    printf("O lucro total da empresa %s foi: R$ %.2f\n", usuario, lucro_total);


}






// Função recursiva para calcular a quantidade total de serviços realizados por uma empresa específica
int calcularQuantidadeTotalServicosRecursivo(Empresa empresas[], int num_empresas, int index, char *usuario) {
    if (index == num_empresas) {
        return 0; // Condição de parada: todas as empresas foram processadas


    } else {
        // Se encontrarmos a empresa com o nome de usuário especificado, retornamos a quantidade total de serviços realizados

        if (strcmp(empresas[index].usuario, usuario) == 0) {
            return empresas[index].servicos_realizados;


        } else {


            // Caso contrário, continuamos para a próxima empresa
            return calcularQuantidadeTotalServicosRecursivo(empresas, num_empresas, index + 1, usuario);


        }
    }
}

// Função para calcular a quantidade total de serviços realizados por uma empresa específica
void verQuantidadeTotalServicos(Empresa empresas[], int num_empresas, char *usuario) {


    int quantidade_total_servicos = calcularQuantidadeTotalServicosRecursivo(empresas, num_empresas, 0, usuario);
    printf("A quantidade total de serviços realizados pela empresa %s foi: %d\n", usuario, quantidade_total_servicos);


}

//funçao para abrir um arquivo e fechar
void FLEE_WRITEstring ( const char * FILE_NAME , const char * STRING )
{
    FILE * fp = fopen ( FILE_NAME , "a" );

    fprintf ( fp , "%s" , STRING );

    fclose ( fp );
}



// Função para atualizar dados da empresa
void atualizarDadosEmpresa(Empresa empresas[], int num_empresas, char *usuario) {


            printf("+--------------------------------------------------+\n");
            printf("|         ATUALIZAÇÃO DE DADOS DA EMPRESA          |\n");
            printf("+--------------------------------------------------+\n");

    int encontrado = 0; // Variável para indicar se a empresa foi encontrada

    // Procura a empresa pelo nome de usuário
    for (int i = 0; i < num_empresas; i++) {


        if (strcmp(empresas[i].usuario, usuario) == 0) {
            encontrado = 1; // Empresa encontrada

            // Solicita ao usuário que insira os novos dados
            printf("Informe o novo nome da empresa: ");
            getchar(); // Limpa o buffer do teclado

            fgets(empresas[i].nome, sizeof(empresas[i].nome), stdin);

            printf("Informe o novo tipo de serviço: ");

            fgets(empresas[i].tipo_servico, sizeof(empresas[i].tipo_servico), stdin);

            printf("Informe o novo preço do serviço: ");
            scanf("%f", &empresas[i].preco_servico);

            printf("Informe o novo horário de atendimento: ");

            getchar(); // Limpa o buffer do teclado

            fgets(empresas[i].horario_atendimento, sizeof(empresas[i].horario_atendimento), stdin);

            printf("Informe a nova senha: ");
            scanf("%s", empresas[i].senha);

            system ("cls");


            printf("+--------------------------------------------------+\n");
            printf("|         DADOS ATUALIZADOS COM SUCESSO            |\n");
            printf("+--------------------------------------------------+\n");


            break; // Sai do loop após encontrar a empresa


        }
    }

    // Se a empresa não for encontrada, exibe uma mensagem de erro
    if ( !encontrado ) {

        printf("Empresa não encontrada!\n");
    }
}


// Função para cadastrar uma empresa
void cadastrarEmpresa(Empresa empresas[], int *num_empresas) {


            printf("+--------------------------------------------------+\n");
            printf("|                CADASTRO EMPRESA                  |\n");
            printf("+--------------------------------------------------+\n");

    printf("Informe o nome da empresa: ");
    getchar();
    fgets(empresas[*num_empresas].nome, sizeof(empresas[*num_empresas].nome), stdin);

    // ESCREVE NO ARQUIVO UMA STRING
    FLEE_WRITEstring ( FILENAME , "- " );
    FLEE_WRITEstring ( FILENAME , empresas[*num_empresas].nome );
    FLEE_WRITEstring ( FILENAME , "\n");

    printf("Escolha o tipo de serviço:\n");
    printf("1. Corte de cabelo\n");
    printf("2. Manicure/Pedicure\n");
    printf("3. Maquiagem\n");

    char tipo_servico_str[50];
    fgets(tipo_servico_str, sizeof(tipo_servico_str), stdin);
    int tipo_servico = atoi(tipo_servico_str);

    switch (tipo_servico) {


        case 1:

            strcpy(empresas[*num_empresas].tipo_servico, "Corte de cabelo");
            break;


        case 2:

            strcpy(empresas[*num_empresas].tipo_servico, "Manicure/Pedicure");
            break;


        case 3:

            strcpy(empresas[*num_empresas].tipo_servico, "Maquiagem");
            break;


        default:

            printf("Opção inválida!\n");
            return;
    }

    printf("Informe o preço do serviço: ");
    scanf("%f", &empresas[*num_empresas].preco_servico);

    printf("Informe o horário de atendimento: ");

    getchar(); // Limpa o buffer do teclado
    fgets(empresas[*num_empresas].horario_atendimento, sizeof(empresas[*num_empresas].horario_atendimento), stdin);

    printf("Informe o nome de usuário: ");
    scanf("%s", empresas[ *num_empresas ].usuario );

    printf("Informe a senha: ");
    scanf("%s", empresas[ *num_empresas ].senha );

    (*num_empresas)++;


            printf("+--------------------------------------------------+\n");
            printf("|            CADASTRO FEITO COM SUCESSO            |\n");
            printf("+--------------------------------------------------+\n");

    system ("pause");

     system ("cls");
}


// função para entrar na conta da empresa


void entrarContaEmpresa(Empresa empresas[], int num_empresas) {


    char usuario[50];
    char senha[50];
    int encontrado = 0; // Variável para indicar se a empresa foi encontrada

            printf("+--------------------------------------------------+\n");
            printf("|                 LOGIN EMPRESA                    |\n");
            printf("+--------------------------------------------------+\n");

    printf("Digite o nome de usuário: ");
    scanf("%s", usuario);
    printf("Digite a senha: ");
    scanf("%s", senha);
    system("cls");



    // Verifica se o usuário e a senha correspondem a alguma empresa cadastrada
    for (int i = 0; i < num_empresas; i++) {

        if (strcmp(empresas[i].usuario, usuario) == 0) {

            if (strcmp(empresas[i].senha, senha) == 0) {


                printf("Senha correspondente encontrada.\n");
                encontrado = 1; // Empresa encontrada

            printf("+------------------------------------------------+\n");
            printf("|         ACESSO CONCEDIDO COM SUCESSO !         |\n");
            printf("+------------------------------------------------+\n");

            int opcao_empresa;

            printf("+------------------------------------------------+\n");
            printf("|                  MENU EMPRESA                  |\n");
            printf("+------------------------------------------------+\n");
            printf("                                                 \n");
            printf("                                                 \n");
            printf(" 1 - QUANTIDADE DE SERVIÇOS FEITOS               \n");
            printf("                                                 \n");
            printf(" 2 - LUCRO TOTAL DA EMPRESA                      \n");
            printf("                                                 \n");
            printf(" 3 - ATUALIZAR DADOS                             \n");
            printf("                                                 \n");
            printf("\n");

                scanf("%d", &opcao_empresa);
                system("cls");

                switch (opcao_empresa) {

                    case 1:

                        verQuantidadeTotalServicos(empresas, num_empresas, usuario);
                        break;

                    case 2:

                         verLucroTotalEmpresa(empresas, num_empresas, usuario);
                         break;

                    case 3:

                         atualizarDadosEmpresa(empresas, num_empresas, usuario);
                         break;

                    default:

                        printf("Opção inválida!\n");
                }

                break; // Sai do loop após encontrar a empresa


            } else {

                printf("Senha incorreta.\n");
            }
        } else {

            printf("Usuário não encontrado.\n");
        }
    }

    // Se a empresa não for encontrada, exibe uma mensagem de erro
    if (!encontrado) {

            printf("+--------------------------------------------------+\n");
            printf("|           USUARIO OU SENHA INCORRETOS            |\n");
            printf("+--------------------------------------------------+\n");
    }
}

//função para tratar arquivos
void
FLEE_PRINT ( const char * FILE_NAME )
{



    FILE * file = fopen ( FILE_NAME , "r" );

    // if ( file == NULL ) printf ("Error opening the file!\n");

    int c;

    while ( ( c = fgetc ( file ) ) != EOF ) putchar ( c );

    fclose ( file );


}

//funçao para criar arquivos


void
FLEE_CREATEAFILE ( const char* FILE_NAME )
{

                  FILE* file = fopen ( FILE_NAME , "w" );

                  // if ( file == NULL ) printf ("Error creating file!");

                  fclose ( file );
}


// Função principal

int main() {
   
   // CORRIGE OS ERROS DE ACENTUAÇÃO ( OPÇÃO CORRETA A SE USAR
   // NÃO setlocale )
   system ( MAGIC_PORTUGUESE_FIX );

   FLEE_CREATEAFILE(FILENAME);
   FLEE_WRITEstring(FILENAME,"[EMPRESAS]\n\n");
    
   Cliente clientes[MAX_CLIENTES];
   Empresa empresas[MAX_EMPRESAS];

    int opcao, num_clientes = 0, num_empresas = 0;

    do {

// primeiro menu de Escolha

    printf("+------------------------------------------------+\n");
    printf("|  BEM-VINDO AO BUSCA E AGENDAMENTO DE SERVIÇOS  |\n");
    printf("+------------------------------------------------+\n");
    printf("                                                  \n");
    printf("                 MENU PRINCIPAL                   \n");
    printf("                                                  \n");
    printf("                                                  \n");
    printf("                                                  \n");
    printf(" 1 - ACESSAR COMO EMPRESA                         \n");
    printf("                                                  \n");
    printf(" 2 - ACESSAR COMO CLIENTE                         \n");
    printf("                                                  \n");
    printf(" 3 - LISTAR EMPRESAS                              \n");
    printf("                                                  \n");
    printf(" 4 - EXIT                                         \n");
    printf("                                                  \n");
    scanf("%d", &opcao);
        system("cls");


        switch( opcao ) {


            case 1:

                // Menu para empresa

    printf("+------------------------------------------------+\n");
    printf("|                 LOGIN EMPRESA                  |\n");
    printf("+------------------------------------------------+\n");
    printf("                                                 \n");
    printf("                                                 \n");
    printf(" 1 - CRIAR CADASTRO DA EMPRESA                   \n");
    printf("                                                 \n");
    printf(" 2 - ENTRAR NA CONTA                             \n");
    printf("                                                 \n");

                scanf("%d", &opcao);
                system("cls");

                switch(opcao) {


                    case 1:

                        cadastrarEmpresa(empresas, &num_empresas);
                        break;

                    case 2:

                        entrarContaEmpresa(empresas, num_empresas);
                        break;

                    default:

                        printf("Opção inválida!\n");
                }
                break;


            case 2:

                // Menu para cliente
             printf("+------------------------------------------------+\n");
             printf("|               LOGIN CLIENTE                    |\n");
             printf("+------------------------------------------------+\n");
             printf("                                                 \n");
             printf(" 1 - CRIAR LOGIN DE CLIENTE                      \n");
             printf("                                                 \n");
             printf(" 2 - ENTRAR NA CONTA                             \n");
             printf("                                                 \n");
             printf("\n");


                scanf("%d", &opcao);
                system("cls");

                switch(opcao) {
                    case 1:
                        cadastrarCliente(clientes, &num_clientes);
                        break;
                    case 2:
                        entrarContaCliente(clientes, num_clientes, empresas, num_empresas);
                        break;

                    default:
                        printf("Opção inváida!\n");
                }
                break;

            case 3:

                printf("\n");
                FLEE_PRINT ( FILENAME );
                system ( "pause" );
                system ( "cls" );
                break;

            case 4:

                printf("Saindo...\n");
                break;

            default:

                printf("Opção inválida!\n");


        }

    } while(opcao != 4);

    return 0;
}




