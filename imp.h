#ifndef ESTRUTURA_H_INCLUDED
#define ESTRUTURA_H_INCLUDED

# define MAX_CLIENTES 100
# define MAX_SERVICOS 3
# define MAX_AVALIACOES 100
# define MAX_EMPRESAS 100
# define MAGIC_PORTUGUESE_FIX "CHCP 65001 > nul"

const char FILENAME [] = "nomes_empresas.txt";
 
// Struct para representar um serviço
typedef struct {
     char nome[50];
     float preco;
     char horario_atendimento[50];
} Servico;
 
// Struct para representar uma empresa
typedef struct {
      char nome[50];
      char tipo_servico[50];
      float preco_servico;
      char horario_atendimento[50];
      char usuario[50];
      char senha[50];
      int servicos_realizados;
      float lucro_total;
      float avaliacao_media;
      char horarios_agendados[MAX_SERVICOS][50]; // Array de strings para armazenar os horários já agendados
      float avaliacoes[MAX_AVALIACOES]; // Array para armazenar as avaliações dos clientes
      int num_avaliacoes; // Número atual de avaliações recebidas
  
} Empresa;
  
// Struct para representar um cliente
typedef struct {
    char nome[50];
    char cpf[12];
    char usuario[50];
    char senha[50];
    float gasto_total;
    int servicos_realizados; // Adicionado para manter o controle de serviços realizados pelo cliente
} Cliente;

#endif // ESTRUTURA_H_INCLUDE