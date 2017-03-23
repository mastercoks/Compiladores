#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> /* necessário para métodos isalpha, isdigit, isalnum */
#define TRUE 1
#define FALSE 0

//Elementos de entrada
enum Elemento {
  T_NUM,            //0
  T_LETRA,          //1
  T_LINHA,          //2
  T_MENOR,          //3
  T_MAIOR,          //4
  T_IGUAL,          //5
  T_ABREP,          //6
  T_FECHAP,         //7
  T_ADD,            //8
  T_SUB,            //9
  T_MULT,           //10
  T_DIV,            //11
  T_2P,             //12
  T_PEV,            //13
  T_DESCONHECIDO,   //14
  T_ESPACO          //15
};

//Estados do AFD
enum Estado {

	INI,   //0
	ID,    //1
  NUM,   //2
	COM,   //3
  DP,    //4
	ATRI,  //5
	SUB,   //6
	MENOR, //7
	MAIOR, //8
	DIV,   //9
	IGUAL, //10
	MULT,  //11
	ADD,   //12
	ABRE,  //13
	FECHA, //14
	PEV,   //15
  ERRO,  //16
  FIM    //17
};

//Atributos
char lookahead;
int linha = 1;
char *palavra;
int primeira_vez = TRUE;


enum Estado tabela[16][16] =
/*ESTADO\ENTRADA       NUM    LETRA LINHA MENOR  MAIOR	IGUAL	 ABREP FECHAP	ADD	  SUB	  MULT   DIV	 DP  	 PEV   DESC   ESPACO  */
/*INICIAL**********/ {{NUM,   ID,	  INI,	MENOR, MAIOR,	IGUAL, ABRE, FECHA,	ADD,  SUB,	MULT,  DIV,  DP,   PEV,  ERRO,  INI},
/*IDENTIFICADOR****/  {ID,	  ID,	  FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*NUMERO***********/  {NUM,	  ERRO,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*COMENTARIO*******/  {COM,	  COM,	INI,	COM,	 COM,	  COM,	 COM,	 COM,	  COM,  COM,	COM,	 COM,	 COM,	 COM,  COM,   COM},
/*DOIS_PONTOS******/  {ERRO,  ERRO,	ERRO,	ERRO,	 ERRO,	ATRI,  ERRO, ERRO,  ERRO, ERRO,	ERRO,  ERRO, ERRO, ERRO, ERRO,  ERRO},
/*ATRIBUICAO*******/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  ATRI,  FIM,  FIM,  	FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*SUBTRACAO********/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  COM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*MENOR_QUE********/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*MAIOR_QUE********/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*DIVISAO**********/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*IGUALDADE********/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*MULTIPLICACAO****/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*ADICAO***********/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*ABRE_PARENTESES**/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*FECHA_PARENTESES*/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,	 ERRO,  FIM},
/*PONTO_E_VIRGULA**/  {FIM,	  FIM,	FIM,	FIM,	 FIM,	  FIM,	 FIM,	 FIM,	  FIM,  FIM,	FIM,	 FIM,	 FIM,	 FIM,  ERRO,  FIM}};

int aceita[18] = {FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE};

typedef struct {
  int linha;
  char *tag;
  char *lexema;
} Token;

enum Estado estado_atual;

Token proximo_token();

char* checar_palavra_reservada() {
  char* palavra_reservada = (char*)malloc(sizeof(char));
  if(strcmp (palavra, "if") == 0) {
      strcpy(palavra_reservada, "T_IF");
  } else if (strcmp (palavra, "then") == 0) {
      strcpy(palavra_reservada, "T_THEN");
  } else if (strcmp (palavra, "endif") == 0) {
      strcpy(palavra_reservada, "T_ENDIF");
  } else if (strcmp (palavra, "while") == 0) {
      strcpy(palavra_reservada, "T_WHILE");
  } else if (strcmp (palavra, "do") == 0) {
      strcpy(palavra_reservada, "T_DO");
  } else if (strcmp (palavra, "enddo") == 0) {
      strcpy(palavra_reservada, "T_ENDDO");
  } else if (strcmp (palavra, "read") == 0) {
      strcpy(palavra_reservada, "T_READ");
  } else if (strcmp (palavra, "write") == 0) {
      strcpy(palavra_reservada, "T_WRITE");
  } else if (strcmp (palavra, "true") == 0) {
      strcpy(palavra_reservada, "T_TRUE");
  } else if (strcmp (palavra, "false") == 0) {
      strcpy(palavra_reservada, "T_FALSE");
  } else {
      strcpy(palavra_reservada, "T_ID");
  }
  return palavra_reservada;
}

enum Estado checar_tabela() {
  enum Estado estado;
  switch (lookahead) {
   	case ';': estado = tabela[estado_atual][T_PEV]; break;
   	case ':': estado = tabela[estado_atual][T_2P]; break;
   	case '+': estado = tabela[estado_atual][T_ADD]; break;
   	case '-': estado = tabela[estado_atual][T_SUB]; break;
   	case '*': estado = tabela[estado_atual][T_MULT]; break;
   	case '/': estado = tabela[estado_atual][T_DIV]; break;
   	case '<': estado = tabela[estado_atual][T_MENOR]; break;
   	case '>': estado = tabela[estado_atual][T_MAIOR]; break;
   	case '=': estado = tabela[estado_atual][T_IGUAL]; break;
   	case '(': estado = tabela[estado_atual][T_ABREP]; break;
   	case ')': estado = tabela[estado_atual][T_FECHAP]; break;
    case '\n': estado = tabela[estado_atual][T_LINHA]; break;
    case ' ': estado = tabela[estado_atual][T_ESPACO]; break;
    case '\t': estado = tabela[estado_atual][T_ESPACO]; break;
    default:
      if(isalpha(lookahead)) {
        estado = tabela[estado_atual][T_LETRA];
      } else if (isdigit(lookahead)) {
        estado = tabela[estado_atual][T_NUM];
      } else {
        estado = tabela[estado_atual][T_DESCONHECIDO];
      }
  }
  return estado;
}

char* get_tag() {
  char *tag = (char*) malloc(sizeof(char));
  switch (lookahead) {
   	case ';': strcpy(tag, "T_PEV"); break;
   	case ':': strcpy(tag, "T_ATRIB"); break;
   	case '+': strcpy(tag, "T_ADD"); break;
   	case '-': strcpy(tag, "T_SUB"); break;
   	case '*': strcpy(tag, "T_MULT"); break;
   	case '/': strcpy(tag, "T_DIV"); break;
   	case '<': strcpy(tag, "T_MENOR"); break;
   	case '>': strcpy(tag, "T_MAIOR"); break;
   	case '=': strcpy(tag, "T_IGUAL"); break;
   	case '(': strcpy(tag, "T_ABREP"); break;
   	case ')': strcpy(tag, "T_FECHAP"); break;
    default:
      if(isalpha(lookahead)) {
        strcpy(tag, "T_ID");
      } else if (isdigit(lookahead)) {
        strcpy(tag, "T_NUM");
      }
  }
  return tag;
}

Token proximo_token() {
  Token token;
  estado_atual = INI;
  enum Estado novo_estado;
  int pegar_tag = TRUE;
  palavra = (char*) malloc(sizeof(char));
  if(primeira_vez == TRUE) {
    primeira_vez = FALSE;
    lookahead = getchar();
  }
  while (aceita[estado_atual] != TRUE && estado_atual != ERRO && lookahead != EOF) {
    novo_estado = checar_tabela();
    if((novo_estado != INI && pegar_tag == TRUE)) {
      token.tag = get_tag();
      pegar_tag = FALSE;
    } else if (estado_atual == INI && ((strcmp(token.tag, "T_SUB") == 0) || (strcmp(token.tag = get_tag(), "") == 0))) {
      token.tag = get_tag();
    }
    if (novo_estado != ERRO && aceita[novo_estado] != TRUE) {
      if(lookahead != ' ' && lookahead != '\t') {
        if (lookahead == '\n') {
          linha++;
          strcpy(palavra, "");
        } else {
          sprintf(palavra, "%s%c", palavra, lookahead); //concatena o lookahead na palavra
        }
      }
      lookahead = getchar();  //pega o proximo lookahead
    }
    estado_atual = novo_estado;
  }//fim while
    if (aceita[estado_atual] == TRUE){
      token.linha = linha;
      token.lexema = palavra;
      if(strcmp(token.tag, "T_ID") == 0) {
        token.tag = checar_palavra_reservada();
      }
    };
    if (estado_atual == ERRO) {
      printf("Erro léxico na linha %d\n", linha);
      exit(1);
    }
    return token;
}


int main(int argc, char* argv[]) {
  freopen(argv[1], "r", stdin);
  printf("Linha\tToken\t\tLexema\n");
  //lookahead = getchar();
  while (lookahead != EOF){
    Token token = proximo_token(); // continue a construir token
    if (lookahead != EOF) { //para não imprimir no ultimo loop
		    printf("%d\t%s\t\t%s\n",token.linha, token.tag, token.lexema); //imprima categoria, lexema completo, linha onde foi encontrado
    }
    strcpy(palavra, "");
  }
  return 1;
}
