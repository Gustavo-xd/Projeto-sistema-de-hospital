// Aviso: usar a IDE code::blocks em outras não tem um funcionamento
// Longin: pode ser qualquer palavra e senha: unip123
// testa se o sistema é Windows, pois o "cls" funciona somente no Windows
// senão utiliza o "clear" que é o comando para limpar a tela no Linux
#ifdef __WIN64
#define limpar_tela "cls"
#else
#define limpar_tela "clear"
#endif

// inclusão de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// quantidade máxima de letras no nome do paciente e nome do medico
#define MAX 100

// definição da struct medico
typedef struct medico
{
	int id;
	char nome[MAX];
	char cpf[MAX];
    char cargo[MAX];
    char email[MAX];
    char rua[MAX];
    char bairro[MAX];
    char telefone[11];
} t_medico;

// definição da struct paciente
typedef struct paciente
{
	int id;
	char nome[MAX];
	char cpf[MAX];
	char medico[MAX];
	char consulta[MAX];
	char email[MAX];
	char telefone[11];
} t_paciente;

// protótipos de funções

/*
  Exibe o menu com todas as opções do programa
  retorno: um caractere do número correspondente a opção
 */
char menu();

/*
  Cadastro um paciente pedindo as informaçoes
 */
void cadastrar_paciente();

/*
  Cadastra um medico com as informaçoes
 */
void cadastrar_medico();

/*
  Mostra todos os medicos cadastrados
 */
void listar_medicos();

/*
  mostra todos os paciente cadastrados
 */
void listar_pacientes();

/*
  Procura um medico pelo id
  Parâmetros:
    arq_medicos: ponteiro para um arquivo aberto
    id_medico: ID do medico que será buscado
  retorno: um ponteiro para o medico encontrado ou NULL caso o ID não exista
 */
t_medico *obter_medico(FILE *arq_medicos, int id_medico);

/*
  Procura um paciente pelo id
  Parâmetros:
    arq_pacientes: ponteiro para um arquivo aberto
    id_paciente: ID do paciente que será buscado
  retorno: um ponteiro para o paciente encontrado ou NULL caso o ID não exista
 */
t_paciente *obter_paciente(FILE *arq_pacientes, int id_paciente);

/*
  Pesquisa um medico e exibe suas informações
 */
void pesquisar_medico();

/*
  Pesquisa um paciente e exibe suas informações
 */
void pesquisar_paciente();

/*
  Procura um medico pelo seu id e informa se ele foi encontrado
  Parâmetros:
    arq_medicos: ponteiro para um arquivo aberto
    id_medico: ID do medico que será buscado
  retorno: 1 para medico encontrado ou 0 caso o ID não exista
 */
int existe_medico(FILE *arq_medicos, int id_medico);

/*
  Procura um paciente pelo seu id e informa se ele foi encontrado
  Parâmetros:
    arq_paciente: ponteiro para um arquivo aberto
    id_paciente: ID do paciente que será buscado
  retorno: 1 se o paciente existe ou 0 caso o ID não exista
 */
int existe_paciente(FILE *arq_pacientes, int id_paciente);

/*
  Exclui um medico do arquivo
 */
void excluir_medico();

/*
  Exclui um paciente do arquivo
 */
void excluir_paciente();

/*
  Informa se a string é um número
  Parâmetros:
  str: ponteiro para uma cadeia de caracteres
  retorno: 1 se a string só conter números ou 0 caso contrário
 */
int str_somente_numeros(char str[]);

int main(int argc, char *argv[])
{
/*
 Login e senha:
 o login pode ser qualquer palavra e a senha ja está definida como: unip123
*/
       char c;
       char login[20];
       char senha[20];
       int a=10;
       int i=0;
       int verifica_senha=0;
      while(verifica_senha==0){
       printf("\n\t\t======= HOSPITAL X =======\n\n login: ");
       fflush(stdin);  //Limpando o buffer do teclado
       gets(login);
       printf("\n senha: ");
       while((c=getch())!=13){ //13 é o valor de ENTER na tabela ASCII
           senha[i]=c;
           i++;
           printf("*");      //imprime o * asterisco
           }
          senha[i]='\0';
          i=0;
       system("cls");
       a= strcmp(senha,"unip123"); //Senha ja definida
       if(a==0){printf("SENHA CORRETA");system("color 0a");verifica_senha=1;Beep(1500,200);} //troca a cor para verde e faz um beep
           else{printf("%s SENHA ERRADA\n",senha);system("color 0c");Beep(1200,200);} //troca a cor para vermelho e faz um beep
       printf("\n");
    }
    system(limpar_tela);

	char resp;

	// loop infinito do programa
	while(1)
	{
		// obtém a escolha do usuário
		resp = menu();

		// testa o valor de "resp"
		if(resp == '1')
			cadastrar_medico();
		else if(resp == '2')
			cadastrar_paciente();
		else if(resp == '3')
			listar_medico();
		else if(resp == '4')
			listar_paciente();
		else if(resp == '5')
			pesquisar_medico();
		else if(resp == '6')
			pesquisar_paciente();
		else if(resp == '8')
			excluir_medico();
        else if(resp == '9')
            excluir_paciente();
		else if(resp == '0') // se for igual a 0, então sai do loop while
			break;
		else
		{
			printf("\nOpcao invalida! Pressione <Enter> para continuar...");
			scanf("%*c");
			// uma forma de "limpar" o buffer de entrada
			fseek(stdin, 0, SEEK_END);
		}
		system(limpar_tela);
	}

	return 0;
}

// função que exibe o menu e retorna a opção escolhida pelo usuário
char menu()
{

	char resp[2];

	printf("============================== hospital x ==============================");
	printf("\n\n(1) - Cadastrar um medico\n");
	printf("(2) - Cadastrar um paciente\n");
	printf("(3) - Listar todos os medico\n");
	printf("(4) - Listar todos os paciente\n");
	printf("(5) - Pesquisar por medico\n");
	printf("(6) - Pesquisar por paciente\n");
	printf("(8) - Excluir um medico\n");
	printf("(9) - Excluir um paciente\n");
	printf("(0) - Sair\n");
	printf("Digite o numero da opcao: ");
	scanf("%1s%*c", resp); // o *c pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);

	// se chegou aqui, é porque a opção é válida
	return resp[0];
}

// função que verifica se uma string contém somente números
int str_somente_numeros(char str[])
{
	int i = 0;
	int len_str = strlen(str);

	for(i = 0; i < len_str; i++)
	{
		if(str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

// função para cadastrar paciente
void cadastrar_paciente()
{
	// abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_pacientes = fopen("pacientes.txt", "a+b");

	// testa a abertura do arquivo
	if(arq_pacientes == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // sai do programa
	}
	/*
		NÃO é interessante que o usuário digite o ID do paciente, esse
		ID tem que ser gerado automático, então temos que pegar o
		ID do último usuário cadastrado
	*/
	int cont_bytes = 0;

	// cont irá guardar o número total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_pacientes, 0, SEEK_END);
	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_pacientes);

	t_paciente paciente;

	if(cont_bytes == 0)
	{
		// se for 0, então não existe paciente cadastrado
		// coloca o ID começando do 1
		paciente.id = 1;
	}
	else
	{
		t_paciente ultimo_paciente;

		// utiliza a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(t_paciente) serve para posicionar
		// para que possamos pegar o último paciente cadastrado
		fseek(arq_pacientes, cont_bytes - sizeof(t_paciente), SEEK_SET);

		// ler o paciente
		fread(&ultimo_paciente, sizeof(t_paciente), 1, arq_pacientes);

		// o ID do paciente é o ID do último paciente acrescentado em 1
		paciente.id = ultimo_paciente.id + 1;
	}
	// obtém o nome do medico
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
	printf("\nDigite o nome do paciente: ");
	scanf("%99[^\n]%*c", paciente.nome);
	printf("\nDigite o cpf do paciente: ");
	scanf("%99[^\n]%*c", paciente.cpf);
	printf("\nDigite o medico do paciente: ");
	scanf("%99[^\n]%*c", paciente.medico);
	printf("\nDigite a consulta do paciente: ");
	scanf("%99[^\n]%*c", paciente.consulta);
	printf("\nDigite o email do paciente: ");
	scanf("%99[^\n]%*c", paciente.email);
	printf("\nDigite o telefone do paciente: ");
	scanf("%99[^\n]%*c", paciente.telefone);

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_pacientes, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&paciente, sizeof(t_paciente), 1, arq_pacientes);

	// fecha o arquivo
	fclose(arq_pacientes);

	printf("\nPaciente \"%s\" cadastrado com sucesso!\n", paciente.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);
}

// função para cadastrar medico
void cadastrar_medico()
{
	// abre o arquivo para escrita
	// a+b => acrescenta dados ao final do arquivo ou cria
	// um arquivo binária para leitura e escrita
	FILE *arq_medicos = fopen("medicos.bin", "a+b");

	// testa a abertura do arquivo
	if(arq_medicos == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // sai do programa
	}
	/*
		NÃO é interessante que o usuário digite o ID do medico, esse
		ID tem que ser gerado automático, então temos que pegar o
		ID do último usuário cadastrado
	*/
	int cont_bytes = 0;

	// cont irá guardar o número total de bytes
	// seta o ponteiro do arquivo para o final do arquivo
	fseek(arq_medicos, 0, SEEK_END);
	// pegamos a quantidade de bytes com a função ftell
	cont_bytes = ftell(arq_medicos);

	t_medico medico;

	if(cont_bytes == 0)
	{
		// se for 0, então não existe medico cadastrado
		// coloco o ID começando de 1
		medico.id = 1;
	}
	else
	{
		t_medico ultimo_medico;

		// utiliza a função fseek para posicionar o arquivo
		// cont_bytes - sizeof(t_medico) serve para posicionar
		// para que possamos pegar o último medico cadastrado
		fseek(arq_medicos, cont_bytes - sizeof(t_medico), SEEK_SET);

		// ler o medico
		fread(&ultimo_medico, sizeof(t_medico), 1, arq_medicos);

		// o ID do medico é o ID do último medico acrescentado em 1
		medico.id = ultimo_medico.id + 1;
	}
	// obtém o nome do medico
	// ^\n indica para pegar até a quebra de linha (enter)
	// %*c descarta o enter
	printf("\nDigite o nome do medico: ");
	scanf("%99[^\n]%*c", medico.nome);
	printf("\nDigite o cpf do medico: ");
	scanf("%99[^\n]%*c", medico.cpf);
    printf("\nDigite o cargo do medico: ");
	scanf("%99[^\n]%*c", medico.cargo);
	printf("\nDigite o email do medico: ");
	scanf("%99[^\n]%*c", medico.email);
	printf("\nDigite a rua do medico: ");
	scanf("%99[^\n]%*c", medico.rua);
	printf("\nDigite o bairro do medico: ");
	scanf("%99[^\n]%*c", medico.bairro);
	printf("\nDigite o telefone do medico: ");
	scanf("%99[^\n]%*c", medico.telefone);

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);

	// se o ponteiro não estiver no final do arquivo nada é escrito
	fseek(arq_medicos, 0, SEEK_END);
	// escreve no arquivo
	fwrite(&medico, sizeof(t_medico), 1, arq_medicos);

	// fecha o arquivo
	fclose(arq_medicos);

	printf("\nMedico \"%s\" cadastrado com sucesso!\n", medico.nome);
	printf("\nPressione <Enter> para continuar...");
	scanf("%*c"); // pega o Enter e descarta

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);
}

// função para listar todos os paciente
void listar_paciente()
{
	// rb => abre arquivo binário para leitura apenas
	FILE *arq_pacientes = fopen("pacientes.txt", "r");

	// testa a abertura do arquivo
	if(arq_pacientes == NULL)
	{
		printf("\nFalha ao abrir arquivo(s) ou ");
		printf("Nenhum paciente cadastrado.\n");
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c"); // pega o Enter e descarta

		// uma forma de "limpar" o buffer de entrada
		fseek(stdin, 0, SEEK_END); // não recomendável o uso
		return;
	}

	// variável que indica se encontrou pelo menos 1 paciente
	int encontrou_pacientes = 0;
	t_paciente paciente;

	printf("\nListando todos os pacientes...\n");
	// loop para percorrer o arquivo
	while(1)
	{
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&paciente, sizeof(t_paciente), 1, arq_pacientes);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		// atualiza a variável indicando que encontrou
		// pelo menos um paciente
		encontrou_pacientes = 1;

		// mostra os dados do paciente
		printf("\nID do paciente:     %d\n", paciente.id);
		printf("Nome do paciente:     %s\n", paciente.nome);
		printf("CPF do paciente:      %s\n", paciente.cpf);
		printf("Medico do paciente:   %s\n", paciente.medico);
		printf("Consulta do paciente: %s\n", paciente.consulta);
		printf("Email do paciente:    %s\n", paciente.email);
		printf("Telefone do paciente:   %s\n", paciente.telefone);
		printf("-----------------------------------------------");
	}

	if(encontrou_pacientes == 0)
		printf("\nNenhum paciente cadastrado.\n");

	fclose(arq_pacientes);

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);
}

// função que obtém um paciente pelo ID
t_paciente *obter_paciente(FILE *arq_pacientes, int id_paciente)
{
	// vai para o início do arquivo
	rewind(arq_pacientes);

	t_paciente *paciente;

	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	// aloca espaço mesmo sem saber se o paciente existe
	paciente = (t_paciente *)malloc(sizeof(t_paciente));
	while(1)
	{

		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(paciente, sizeof(t_paciente), 1, arq_pacientes);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
		{
			free(paciente); // libera a mémoria, pois o paciente não foi encontrado
			return NULL;
		}
		// verifica se os ID's são iguais
		if(paciente->id == id_paciente)
			break;
	}
	return paciente;
}

// função para listar todos os medico
void listar_medico()
{
	// rb => abre arquivo binário para leitura apenas
	FILE *arq_medicos = fopen("medicos.bin", "rb");

	// testa a abertura do arquivo
	if(arq_medicos == NULL)
	{
		printf("\nFalha ao abrir arquivo(s) ou ");
		printf("Nenhum medico cadastrado.\n");
		printf("\nPressione <Enter> para continuar...");
		scanf("%*c"); // pega o Enter e descarta

		// uma forma de "limpar" o buffer de entrada
		fseek(stdin, 0, SEEK_END); // não recomendável o uso
		return;
	}

	// variável que indica se encontrou pelo menos 1 medico
	int encontrou_medicos = 0;
	t_medico medico;

	printf("\nListando todos os medicos...\n");
	// loop para percorrer o arquivo
	while(1)
	{
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&medico, sizeof(t_medico), 1, arq_medicos);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		// atualiza a variável indicando que encontrou
		// pelo menos um medico
		encontrou_medicos = 1;

		// mostra os dados do medico
		printf("\nID do medico:   %d\n", medico.id);
		printf("Nome do medico:   %s\n", medico.nome);
		printf("Cargo do medico:   %s\n", medico.cargo);
		printf("Rua do medico:    %s\n", medico.rua);
		printf("Bairro do medico: %s\n", medico.bairro);
		printf("Email do medico:  %s\n", medico.email);
		printf("Telefone do medico: %s\n", medico.telefone);
		printf("----------------------------------------------");
	}

	if(encontrou_medicos == 0)
		printf("\nNenhum medico cadastrado.\n");

	fclose(arq_medicos);

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);
}

// função que obtém um medico pelo ID
t_medico *obter_medico(FILE *arq_medicos, int id_medico)
{
	// vai para o início do arquivo
	rewind(arq_medicos);

	t_medico *medico;

	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	// aloca espaço mesmo sem saber se o medico existe
	medico = (t_medico *)malloc(sizeof(t_medico));
	while(1)
	{

		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(medico, sizeof(t_medico), 1, arq_medicos);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
		{
			free(medico); // libera a mémoria, pois o medico não foi encontrado
			return NULL;
		}
		// verifica se os ID's são iguais
		if(medico->id == id_medico)
			break;
	}
	return medico;
}

// função para pesquisar por algum medico
void pesquisar_medico()
{
	char nome[MAX];
	int encontrou_medicos = 0;

	// rb+ => abre para leitura somente
	FILE *arq_medicos = fopen("medicos.bin", "rb");

	// testa a abertura do arquivo
	if(arq_medicos == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // aborta o programa
	}

	printf("\nDigite o nome do medico: ");
	scanf("%99[^\n]%*c", nome);

	printf("\nmedico com o nome \"%s\":\n\n", nome);
	// loop para percorrer o arquivo
	t_medico medico;
	while(1)
	{
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&medico, sizeof(t_medico), 1, arq_medicos);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		char nome_aux[MAX];
		// faz uma cópia para não alterar medico->nome
		strcpy(nome_aux, medico.nome);

		// verifica se é igual
		if(strcmp(strupr(nome_aux), strupr(nome)) == 0)
		{
			// mostra os dados do medico
			printf("ID do medico: %d\n\n", medico.id);
			encontrou_medicos = 1;
		}
	}

	if(encontrou_medicos == 0)
		printf("Nenhum medico encontrado.\n\n");

	// fecha o arquivo
	fclose(arq_medicos);

	printf("Pressione <Enter> para continuar...");
	scanf("%*c");

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);
}

// função para pesquisar por algum paciente
void pesquisar_paciente()
{
	char nome[MAX];
	int encontrou_pacientes = 0;

	// rb+ => abre para leitura somente
	FILE *arq_pacientes = fopen("pacientes.bin", "rb");

	// testa a abertura do arquivo
	if(arq_pacientes == NULL)
	{
		printf("\nFalha ao abrir arquivo(s)!\n");
		exit(1); // sai do programa
	}

	printf("\nDigite o nome do paciente: ");
	scanf("%99[^\n]%*c", nome);

	printf("\npaciente com o nome \"%s\":\n\n", nome);
	// loop para percorrer o arquivo
	t_paciente paciente;
	while(1)
	{
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&paciente, sizeof(t_paciente), 1, arq_pacientes);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		char nome_aux[MAX];
		// faz uma cópia para não alterar paciente->nome
		strcpy(nome_aux, paciente.nome);

		// verifica se é igual
		if(strcmp(strupr(nome_aux), strupr(nome)) == 0)
		{
			// mostra os dados do paciente
			printf("ID do paciente: %d\n\n", paciente.id);
			encontrou_pacientes = 1;
		}
	}

	if(encontrou_pacientes == 0)
		printf("Nenhum paciente encontrado.\n\n");

	// fecha o arquivo
	fclose(arq_pacientes);

	printf("Pressione <Enter> para continuar...");
	scanf("%*c");

	// uma forma de "limpar" o buffer de entrada
	fseek(stdin, 0, SEEK_END);
}

// função que verifica se um medico existe
// retorna 0 se NÃO existe e 1 caso contrário
int existe_medico(FILE *arq_medicos, int id_medico)
{
	// vai para o início do arquivo
	rewind(arq_medicos);

	t_medico medico;
	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	while(1)
	{
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&medico, sizeof(t_medico), 1, arq_medicos);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		// verifica se o ID é igual
		if(medico.id == id_medico)
			return 1;
	}

	// se chegou aqui é porque NÃO existe o medico, então retorna 0
	return 0;
}

// função que verifica se um paciente existe
// retorna 0 se NÃO existe e 1 caso contrário
int existe_paciente(FILE *arq_pacientes, int id_paciente)
{
	// vai para o início do arquivo
	rewind(arq_pacientes);

	t_paciente paciente;
	// loop para percorrer o arquivo
	// busca linear O(n), como o ID é crescente é possível fazer uma busca binária O(log(n))
	while(1)
	{
		// fread retorna o número de elementos lidos com sucesso
		size_t result = fread(&paciente, sizeof(t_paciente), 1, arq_pacientes);

		// se for 0, é porque não há mais elemento, então sai do loop
		if(result == 0)
			break;

		// verifica se o ID é igual
		if(paciente.id == id_paciente)
			return 1;
	}

	// se chegou aqui é porque NÃO existe o paciente, então retorna 0
	return 0;
}

// função responsável por excluir medicos
void excluir_medico()
{
	char str_id_medico[10];
	int id_medico;

	printf("\nDigite o ID do medico: ");
	scanf("%10s%*c", str_id_medico);

	fseek(stdin, 0, SEEK_END);

	// verifica se str_id_medico só contém números
	if(str_somente_numeros(str_id_medico) == 1)
	{
		// se chegou aqui é porque o ID do medico é válido
		sscanf(str_id_medico, "%d", &id_medico);

		// rb abre para leitura (o arquivo deve existir)
		FILE *arq_medicos = fopen("medicos.bin", "rb");

		if(arq_medicos == NULL)
		{
			printf("\nFalha ao abrir arquivo(s)!\n");
			exit(1); // aborta o programa
		}

		// verifica se o medico existe
		if(existe_medico(arq_medicos, id_medico) == 1)
		{
			char nome_medico[MAX];
			// abre um novo arquivo temporário
			FILE *arq_temp = fopen("temp_medicos.bin", "a+b");
			if(arq_temp == NULL)
			{
				printf("\nFalha ao criar arquivo temporario!\n");
				fclose(arq_medicos);
				exit(1); // sai do programa
			}
			rewind(arq_medicos); // vai para o início do arquivo

			t_medico medico;
			while(1) // loop para percorrer o arquivo
			{

				// fread retorna o número de elementos lidos com sucesso
				size_t result = fread(&medico, sizeof(t_medico), 1, arq_medicos);

				// se for 0, é porque não há mais elemento, então sai do loop
				if(result == 0)
					break;

				// só copia pro novo arquivo se for diferente
				if(medico.id != id_medico)
				{
					// escreve no arquivo temporário
					fwrite(&medico, sizeof(t_medico), 1, arq_temp);
				}
				else
					strcpy(nome_medico, medico.nome);
			}

			// antes de fazer operações de remover arquivo e renomear,
			// é preciso fechar os dois arquivos
			fclose(arq_medicos);
			fclose(arq_temp);

			// depois de fechar o arquivo, então tentamos remover
			if(remove("medicos.bin") != 0)
				printf("\nErro ao deletar o arquivo \"medicos.bin\"\n");
			else
			{
				// renomeia o arquivo
				int r = rename("temp_medicos.bin", "medicos.bin");
				if(r != 0)
				{
					printf("\nPermissao negada para renomear o arquivo!\n");
					printf("Feche esse programa bem como o arquivo \"temp_medicos.bin\" e renomeie manualmente para \"medicos.bin\"\n");
				}
				else
					printf("\nMedico \"%s\" removido com sucesso!\n", nome_medico);
			}
		}
		else
		{
			fclose(arq_medicos);
			printf("\nNao existe medico com o ID \"%d\".\n", id_medico);
		}
	}
	else
		printf("\nO ID so pode conter numeros!\n");

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
	fseek(stdin, 0, SEEK_END);
}

// função responsável por excluir pacientes
void excluir_paciente()
{
	char str_id_paciente[10];
	int id_paciente;

	printf("\nDigite o ID do paciente: ");
	scanf("%10s%*c", str_id_paciente);

	fseek(stdin, 0, SEEK_END);

	// verifica se str_id_paciente só contém números
	if(str_somente_numeros(str_id_paciente) == 1)
	{
		// se chegou aqui é porque o ID do paciente é válido
		sscanf(str_id_paciente, "%d", &id_paciente);

		// rb abre para leitura (o arquivo deve existir)
		FILE *arq_pacientes = fopen("pacientes.bin", "rb");

		if(arq_pacientes == NULL)
		{
			printf("\nFalha ao abrir arquivo(s)!\n");
			exit(1); // sai do programa
		}

		// verifica se o paciente existe
		if(existe_paciente(arq_pacientes, id_paciente) == 1)
		{
			char nome_paciente[MAX];
			// abre um novo arquivo temporário
			FILE *arq_temp = fopen("temp_pacientes.bin", "a+b");
			if(arq_temp == NULL)
			{
				printf("\nFalha ao criar arquivo temporario!\n");
				fclose(arq_pacientes);
				exit(1); // sai do programa
			}
			rewind(arq_pacientes); // vai para o início do arquivo

			t_paciente paciente;
			while(1) // loop para percorrer o arquivo
			{

				// fread retorna o número de elementos lidos com sucesso
				size_t result = fread(&paciente, sizeof(t_paciente), 1, arq_pacientes);

				// se for 0, é porque não há mais elemento, então sai do loop
				if(result == 0)
					break;

				// só copia pro novo arquivo se for diferente
				if(paciente.id != id_paciente)
				{
					// escreve no arquivo temporário
					fwrite(&paciente, sizeof(t_paciente), 1, arq_temp);
				}
				else
					strcpy(nome_paciente, paciente.nome);
			}

			// antes de fazer operações de remover arquivo e renomear,
			// é preciso fechar os dois arquivos
			fclose(arq_pacientes);
			fclose(arq_temp);

			// depois de fechar o arquivo, então tentamos remover
			if(remove("pacientes.bin") != 0)
				printf("\nErro ao deletar o arquivo \"pacientes.bin\"\n");
			else
			{
				// renomeia o arquivo
				int r = rename("temp_pacientes.bin", "pacientes.bin");
				if(r != 0)
				{
					printf("\nPermissao negada para renomear o arquivo!\n");
					printf("Feche esse programa bem como o arquivo \"temp_pacientes.bin\" e renomeie manualmente para \"pacientes.bin\"\n");
				}
				else
					printf("\nPaciente \"%s\" removido com sucesso!\n", nome_paciente);
			}
		}
		else
		{
			fclose(arq_pacientes);
			printf("\nNao existe paciente com o ID \"%d\".\n", id_paciente);
		}
	}
	else
		printf("\nO ID so pode conter numeros!\n");

	printf("\nPressione <Enter> para continuar...");
	scanf("%*c");
	fseek(stdin, 0, SEEK_END);
}
