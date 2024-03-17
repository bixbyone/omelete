duvica capitão C++


0) Remova o ponto de entrada main() e funcionalidades de linha de comando.

int main() {

char *ptr_port = getenv("PORT");

if (ptr_port == NULL) {

port = 8080;

} else {

port = atoi(ptr_port);

}


char *ptr_pool_size = getenv("POOL_SIZE");

if (ptr_pool_size != NULL) {

pool_size = atoi(ptr_pool_size);

} else {

pool_size = 10;

}


char *ptr_thread_pool_size = getenv("THREAD_POOL_SIZE");

int thread_pool_size = 2;


if (ptr_thread_pool_size != NULL) {

thread_pool_size = atoi(ptr_thread_pool_size);

}


char *connection_string = getenv("CONNECTION_STRING");


if (signal(SIGINT, sighandler) == SIG_ERR) {

fprintf(stderr, "Failed to set the signal handler\n");

return 1;

}


if (signal(SIGTERM, sighandler) == SIG_ERR) {

fprintf(stderr, "Failed to set the signal handler\n");

return 1;

}


if (create_pool(connection_string)) {

return 1;

}


main_daemon = MHD_start_daemon(

MHD_USE_EPOLL_INTERNAL_THREAD | MHD_USE_EPOLL_TURBO,

port, NULL, NULL,

&handle_request,

NULL,

MHD_OPTION_CONNECTION_TIMEOUT, 30,

MHD_OPTION_THREAD_POOL_SIZE, thread_pool_size,

MHD_OPTION_END);


if (!main_daemon) {

fprintf(stderr, "Failed to start the server\n");

return 1;

} else {

printf("Thread pool size: %d\n", thread_pool_size);

}


printf("Server running on port %d.\n", port);

fflush(stdout);


pause();

}


1) Remover a função main() completa, já que não será mais o ponto de entrada.

2) Exporte as funções públicas que serão usadas por programas clientes, como 

get_cliente, salva_cliente etc, colocando declarações de protótipo em um header.

main.c ja aceita requisições http: rest crud

3) Inicializar estruturas globais como pool no início do arquivo para poderem ser acessadas por outras funções de outras linguagens

4) Remover código específico de execução como parseamento dos argumentos de linha de comando, tratamento de sinais.?

5) Deixar apenas lógica encapsulada sem depender de interfaces como MHD_start_daemon.

6) api.sh carrega a biblioteca compilada, chame as funções exportadas e testa o fluxo.


duvidas


0) Remova o ponto de entrada main() e funcionalidades de linha de comando.

1) Remover a função main() completa, já que não será mais o ponto de entrada.

2) Exporte as funções públicas que serão usadas por programas clientes, como 

get_cliente, salva_cliente etc, colocando declarações de protótipo em um header.

ja aceita requisições http: rest 

3) Inicializar estruturas globais como pool no início do arquivo para poderem ser acessadas por outras funções.

4) Remover código específico de execução como parseamento dos argumentos de linha de comando, tratamento de sinais.?

5) Deixar apenas lógica encapsulada sem depender de interfaces como MHD_start_daemon.

6) api.sh carrega a biblioteca compilada, chame as funções exportadas e testa o fluxo.

7) duvica capitão C++


0) Remova o ponto de entrada main() e funcionalidades de linha de comando.

1) Remover a função main() completa, já que não será mais o ponto de entrada.

2) Exporte as funções públicas que serão usadas por programas clientes, como 

get_cliente, salva_cliente etc, colocando declarações de protótipo em um header.

ja aceita requisições http: rest 

3) Inicializar estruturas globais como pool no início do arquivo para poderem ser acessadas por outras funções.

4) Remover código específico de execução como parseamento dos argumentos de linha de comando, tratamento de sinais.?

5) Deixar apenas lógica encapsulada sem depender de interfaces como MHD_start_daemon.

6) api.sh carrega a biblioteca compilada, chame as funções exportadas e testa o fluxo.

7) gcc -fPIC -shared main.c -lpq -lmicrohttpd -lpthread -o libcodorna.so este?

8) gcc -o main main.c -I/usr/include/postgresql -L/usr/lib -lpq -lmicrohttpd -lcjson este?



9) gcc .....


#----------------api.sh------se apoiando em ombro de gigantes -----------# 


#!/bin/bash


# Carrega a biblioteca C

. ./libcodorna.so


# Socket do Nginx

ngx_socket=/tmp/nginx_proxy.socket


# Loop infinito recebendo requisições

while socat -u UNIX-LISTEN:$ngx_socket,fork STDOUT; do


 # Lê requisição do Nginx

 request=$(socat - READLINE)


 # Parse headers da requisição

 method=$(echo "$request" | head -n 1 | cut -d' ' -f1) 

 url=$(echo "$request" | head -n 1 | cut -d' ' -f2)


 # Roteia para função C correspondente

 case $method in


   GET)


     # Chama função C para GET

     response=$(get_cliente "${url}")


   ;;


   POST)


     # Chama função C para POST 

     response=$(salva_cliente "${url}" "${body}")


   ;;


 esac


 # Retorna resposta para o Nginx

 echo "$response"


done


# Pool de processos para escalabilidade

MAX_WORKERS=100


while [[ "$#" -gt 0 ]]; do


 # processa requisição em background

 bash processa.sh "$1" &


 # aguardaWorker 

 shift


 if [[ "${#}" -eq "$MAX_WORKERS" ]]; then

   wait

 fi


done


#--------main.c----------#


#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <microhttpd.h>

#include <regex.h>

#include <time.h>

#include <ctype.h>

#include <pthread.h>

#include <signal.h>

#include <cJSON.h>


int port;

int pool_size;

struct MHD_Daemon *main_daemon;



typedef struct {

 char valor[11];

 char tipo;

 char descricao[11];

 char realizada_em[28];

 int em_uso;

} transacao;


typedef struct {

 char id[2];

 int saldo;

 int limite;

 transacao ultimas_transacoes[10];

} cliente;


struct post_status {

 int status;

 char data[1024];

};


 struct MutexPool {

 pthread_mutex_t *mutexes;

 int num_mutexes; 

};


void create_mutex_pool(struct MutexPool *pool, int pool_size) {


 pool->mutexes = malloc(pool_size * sizeof(pthread_mutex_t));


 pthread_mutex_init(&pool->lock, NULL);


 pool->num_mutexes = 0;


 for(int i=0; i<pool_size; i++) {


   pthread_mutex_init(&pool->mutexes[i], NULL);


   printf("Mutex %d created\n", i);


 }


}


pthread_mutex_t* get_mutex() {


 pthread_mutex_lock(&pool.lock);


 pthread_mutex_t* mutex = &pool->mutexes[pool->num_mutexes];


 pool->num_mutexes++;


 pthread_mutex_unlock(&pool.lock);


 return mutex;


}



void now(char *dt) {

 time_t t = time(NULL);

 struct tm tm = *localtime(&t);

 struct timeval tv;

 gettimeofday(&tv, NULL);

 sprintf(dt, "%d-%02d-%02dT%02d:%02d:%02d.%06dZ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, (int)tv.tv_usec);

}


void monta_ultimas_transacoes(transacao transacoes_array[10], char *ultimas_transacoes) {

 char transacoes[2000];

 char *token = ultimas_transacoes;


 int i = 0;

 while (*token) {

   switch (*token) {

     case '\\':

       token++;

       break;

     case '"':

       if (*(token + 1) != '{') {

         transacoes[i] = *token;

         i++;

       }

       token++;

       break;

     case '}':

       transacoes[i] = *token;

       i++;

       if (*(token + 1) == '"') {

         token += 2;

       } else token++;

       break;

     default:

       transacoes[i] = *token;

       i++;

       token++;

     break;

   }

 }


 transacoes[0] = '[';

 transacoes[i - 1] = ']';

 transacoes[i] = '\0';


 if (strcmp(transacoes, "[]") == 0) {

   return;

 }


 cJSON *json = cJSON_Parse(transacoes);


 if (json == NULL) {

   fprintf(stderr, "Failed to parse the JSON data\n");

   return;

 }


 int j = 0;

 cJSON *item = NULL;

 cJSON_ArrayForEach(item, json) {

   cJSON *valor = cJSON_GetObjectItem(item, "valor");

   cJSON *tipo = cJSON_GetObjectItem(item, "tipo");

   cJSON *descricao = cJSON_GetObjectItem(item, "descricao");

   cJSON *realizada_em = cJSON_GetObjectItem(item, "realizada_em");


   sprintf(transacoes_array[j].valor, "%d", valor -> valueint);

   transacoes_array[j].tipo = tipo -> valuestring[0];

   strncpy(transacoes_array[j].descricao, descricao -> valuestring, 10);

   transacoes_array[j].descricao[10] = '\0';

   strncpy(transacoes_array[j].realizada_em, realizada_em -> valuestring, 27);

   transacoes_array[j].realizada_em[27] = '\0';

   transacoes_array[j].em_uso = 1;

   j++;

 }


 cJSON_Delete(json);

}


   regmatch_t matches[2];

   reti = regexec(&regex, url, 2, matches, 0);


   if (!reti) {

     strncpy(id, url + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);

     id[matches[1].rm_eo - matches[1].rm_so] = '\0';

   } else {

     char regex_error[100];

     regerror(reti, &regex, regex_error, sizeof(regex_error));

     printf("Regex match failed: %s\n", regex_error);

   }


   regfree(&regex);

}


int get_cliente_for_update(cliente *c, char *id, PGconn *pg_conn) {

 char query[85];

 sprintf(query, "select saldo, limite, ultimas_transacoes from clientes where id = %s FOR UPDATE", id);


 return _get_cliente(c, id, query, pg_conn);

}


int get_cliente(cliente *c, char *id) {

 char query[70];

 sprintf(query, "select saldo, limite, ultimas_transacoes from clientes where id = %s", id);


 PGconn *pg_conn = get_connection();

 int result = _get_cliente(c, id, query, pg_conn);

 release_connection(pg_conn);

 return result;

}


void serializar_transacoes(char *transacoes, cliente *c) {

 if (!c -> ultimas_transacoes[0].em_uso) {

   transacoes[0] = '{';

   transacoes[1] = '}';

   transacoes[2] = '\0';

   return;

 }


 transacoes[0] = '{';

 transacoes[1] = '\0';

 int i = 0;

 while (i < 10 && c -> ultimas_transacoes[i].em_uso) {

   char transacao[200];

   sprintf(transacao, 

       "\"{\\\"valor\\\":%s,\\\"tipo\\\":\\\"%c\\\",\\\"descricao\\\":\\\"%s\\\",\\\"realizada_em\\\":\\\"%s\\\"}\",", 

       c -> ultimas_transacoes[i].valor, 

       c -> ultimas_transacoes[i].tipo, 

       c -> ultimas_transacoes[i].descricao, 

       c -> ultimas_transacoes[i].realizada_em);


   strcat(transacoes, transacao);

   i++;

 }


 transacoes[strlen(transacoes) - 1] = '}';

 transacoes[strlen(transacoes)] = '\0';

}


int salva_cliente(cliente *c, transacao t, PGconn *pg_conn) {

 int valor = atoi(t.valor);

 if (t.tipo == 'd') {

   valor = -valor;

 }


 char query[2000];

 if (!c -> ultimas_transacoes[0].em_uso) {

   memcpy(&c -> ultimas_transacoes[0], &t, sizeof(transacao));

   c -> ultimas_transacoes[0].em_uso = 1;

 } else {

   int i = 0;

   while (i < 8 && c -> ultimas_transacoes[i].em_uso) {

     i++;

   }


   c -> ultimas_transacoes[i + 1].em_uso = 0;


   while (i >= 1) {

     memcpy(&c -> ultimas_transacoes[i], &c -> ultimas_transacoes[i - 1], sizeof(transacao));

     i--;

   }


   memcpy(&c -> ultimas_transacoes[0], &t, sizeof(transacao));

 }


 char ultimas_transacoes[2000];

 serializar_transacoes(ultimas_transacoes, c);


 sprintf(query, "update clientes set saldo = saldo + %d, ultimas_transacoes = '%s' where id = %s returning saldo", valor, ultimas_transacoes, c -> id);


 PGresult *res = PQexec(pg_conn, query);


 if (PQresultStatus(res) != PGRES_TUPLES_OK) {

   char *error_message = PQerrorMessage(pg_conn);

   if (strstr(error_message, "saldo_maior_que_o_limite") != NULL) {

     PQclear(res);

     rollback_transaction(pg_conn);

     release_connection(pg_conn);

     return -1;

   } else {

     PQclear(res);

     fprintf(stderr, "%s: %s\n", PQresStatus(PQresultStatus(res)), PQerrorMessage(pg_conn));

     rollback_transaction(pg_conn);

     release_connection(pg_conn);

     return 0;

   }

 }


 int novo_saldo = atoi(PQgetvalue(res, 0, 0));


 PQclear(res);

 commit_transaction(pg_conn);

 release_connection(pg_conn);


 c -> saldo = novo_saldo;

 return 1;

}


cliente *inicia_cliente() {

 cliente *c = (cliente *)calloc(1, sizeof(cliente));

 if (c == NULL) {

   fprintf(stderr, "Failed to allocate memory for the client\n");

 }

 return c;

}


void parse_transacao(transacao *t, char *data) {

 cJSON *json = cJSON_Parse(data);

 if (json == NULL) {

   fprintf(stderr, "Failed to parse the JSON data\n");

   return;

 }


 cJSON *valor = cJSON_GetObjectItem(json, "valor");

 cJSON *tipo = cJSON_GetObjectItem(json, "tipo");

 cJSON *descricao = cJSON_GetObjectItem(json, "descricao");


 double valor_double = valor -> valuedouble;

 if (valor_double - (int)valor_double > 0) {

   sprintf(t -> valor, "%.2f", valor -> valuedouble);

 } else {

   sprintf(t -> valor, "%d", valor -> valueint);

 }


 t -> tipo = tipo -> valuestring[0];

 if (descricao -> valuestring != NULL && strlen(descricao -> valuestring) <= 10){

   strncpy(t -> descricao, descricao -> valuestring, 10);

   t -> descricao[10] = '\0';

 } else {

   t -> descricao[0] = '\0';

 }


 cJSON_Delete(json);


 now(t -> realizada_em);

 t -> em_uso = 1;

}


int valida_transacao(transacao *t) {

 if (strlen(t -> valor) == 0 || strchr(t -> valor, '.') > 0) {

   return 0;

 }


 if (t -> tipo != 'c' && t -> tipo != 'd') {

   return 0;

 }


 if (strlen(t -> descricao) == 0){

   return 0;

 }


 return 1;

}


void serializa_ultimas_transacoes(char *transacoes, cliente *c) {

 if (!c -> ultimas_transacoes[0].em_uso) {

   transacoes[0] = '[';

   transacoes[1] = ']';

   transacoes[2] = '\0';

   return;

 }


 transacoes[0] = '[';

 transacoes[1] = '\0';

 int i = 0;

 while (c -> ultimas_transacoes[i].em_uso) {

   char transacao[300];


   sprintf(transacao, 

       "{\"valor\":%s,\"tipo\":\"%c\",\"descricao\":\"%s\",\"realizada_em\":\"%s\"},", 

       c -> ultimas_transacoes[i].valor, 

       c -> ultimas_transacoes[i].tipo, 

       c -> ultimas_transacoes[i].descricao, 

       c -> ultimas_transacoes[i].realizada_em);


   strcat(transacoes, transacao);

   i++;

 }

 transacoes[strlen(transacoes) - 1] = ']';

 transacoes[strlen(transacoes)] = '\0';

}


enum MHD_Result handle_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {


 if (strcmp(method, "POST") == 0) {

   struct post_status *post = (struct post_status *)*con_cls;


   if (!post) {

     post = (struct post_status *)calloc(1, sizeof(struct post_status));

     *con_cls = post;

   }


   if (!post->status) {

     post -> status = 1;

     return MHD_YES;

   } else {

     if (*upload_data_size) {

       strncat(post->data, upload_data, *upload_data_size);

       *upload_data_size = 0;

       return MHD_YES;

     } else {

       printf("%s %s\n", method, url);

       char id[2] = "0";

       get_cliente_id(id, url, "\\/clientes\\/([0-9]+)\\/transacoes");


       if (strcmp(id, "0") == 0) {

         return send_response(connection, "{\"error\": \"Invalid URL\"}", 400, 0);

       }


       char *data = (char *)calloc(1, 1024);

       strncpy(data, post -> data, 1024);

       char *ptr_data = data;

       while (*ptr_data != '{')

         ptr_data++;


       transacao t;

       parse_transacao(&t, ptr_data);


       free(data);

       free(post);


       if (!valida_transacao(&t)) {

         return send_response(connection, "{\"error\": \"Unprocessable Entity\"}", 422, 0);

       }


       cliente *c = inicia_cliente();

void handle_request(struct MHD_Connection *connection) {


 char id[2];

 char *method = get_request_method(); 


 if(strcmp(method, "POST") == 0) {


   get_cliente_id(id, url);


   cliente *c = get_cliente_from_memory(id);


   if(!c) {

     return send_error("Cliente não encontrado");

   }


   transacao t;

   parse_request_body(&t);


   pthread_mutex_lock(&mem_lock);


   switch(process_transaction_in_memory(c, t)) {


     case SUCCESS:


       send_success_response(c);


     case INSUFFICIENT_FUNDS:


       send_error("Saldo insuficiente");


     // outros casos


   }


   pthread_mutex_unlock(&mem_lock);


 } else if(strcmp(method, "GET") == 0){


   get_cliente_id(id, url);


   cliente *c = get_cliente_from_memory(id);


   if(!c) {

     return send_error("Cliente não encontrado"); 

   }


   send_cliente_data_response(c);


 }


}


   cliente *c = inicia_cliente();


  void handle_request(struct MHD_Connection *connection) {


 char id[2];

 char *method = get_request_method(); 


 if(strcmp(method, "POST") == 0) {


   get_cliente_id(id, url);


   cliente *c = get_cliente_from_memory(id);


   if(!c) {

     return send_error("Cliente não encontrado");

   }


   transacao t;

   parse_request_body(&t);


   pthread_mutex_lock(&mem_lock);


   switch(process_transaction_in_memory(c, t)) {


     case SUCCESS:


       send_success_response(c);


     case INSUFFICIENT_FUNDS:


       send_error("Saldo insuficiente");


     // outros casos


   }


   pthread_mutex_unlock(&mem_lock);


 } else if(strcmp(method, "GET") == 0){


   get_cliente_id(id, url);


   cliente *c = get_cliente_from_memory(id);


   if(!c) {

     return send_error("Cliente não encontrado"); 

   }


   send_cliente_data_response(c);


 }


}


void sighandler(int signum) {

 if (signum == SIGINT || signum == SIGTERM) {

   printf("\nShutting down the service\n");

   fflush(stdout);

   close_pool();

   MHD_stop_daemon(main_daemon);

   exit(0);

 }

}
