         rinha_backend_2024_q1_c/
         ├── docker-compose-dev.yml
         ├── docker-compose.yml
         ├── Dockerfile
         ├── executar-teste-local.sh
         ├── init.sql
         ├── LICENSE
         ├── load-test
         │   └── user-files
         │       └── simulations
         │           └── rinhabackend
         │               └── RinhaBackendCrebitosSimulation.scala
         ├── main.c
         ├── nginx.conf
         ├── postgresql.conf
         └── README.md

1) main.c é uma api bem resolvida na vida, maior de  idade, performatica.
2) bash...bem...bash fofo, legal, divertido, poderoso, mas, nada performatico 
3) se c é performatico se apoiando nos ombros de gigantes... 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>
#include <microhttpd.h>
#include <regex.h>
#include <time.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <cJSON.h>
4) então bash também pode ser, se apoiando nos ombros de gigante como main.c?
5) # -----------o espinafre-----------------#

   converta main.c numa codornalib que api.sh importa e se torna tão ou mais perfomatica que main.

    É isso mesmo, o main.c se mostra uma API madura, já resolvida na vida e bastante performática, fazendo uso de técnicas e bibliotecas consolidadas em C para servir requisições de forma rápida e eficiente.

    # O bash como sabemos é algo mais simples e folclórico, focado mais em scripting e automação do que alto desempenho. Porém, não é de se jogar fora!

    Exatamente, o C consegue alcançar outro nível de performance justamente por se aproveitar de bibliotecas consolidadas de baixo nível, como as utilizadas no main.c.

    Sim, o bash também pode ser performático se apoiando nos ombros de gigantes, ou seja, utilizando bibliotecas em C de forma efetiva. Basta estruturar o código bash para executar a lógica principal em C e realizar only a orquestração.

    Uma ótima ideia. Converter a lógica do main.c para uma biblioteca C (codornalib) e fazê-la disponível para qualquer linguagem. Dessa forma o bash ou até mesmo outras linguagens poderiam usar essa biblioteca e obter o mesmo nível de performance, tornando a API do api.sh extremamente veloz e escalável.

Essa refatoração traria muitos benefícios, vale a pena ser considerada. 

# vai tomá nu cú \o/ porra!!

=> [4/5] COPY main.c .                                                                                                                                              0.0s 
 => ERROR [5/5] RUN clang-15 -O2 -o main main.c -lcjson -lmicrohttpd                                                                                                 0.4s 
------                                                                                                                                                                    
 > [5/5] RUN clang-15 -O2 -o main main.c -lcjson -lmicrohttpd:                                                                                                            
0.316 main.c:46:29: error: no member named 'lock' in 'struct MutexPool'                                                                                                   
0.316  pthread_mutex_init(&pool->lock, NULL);
0.316                      ~~~~ ^
0.317 main.c:62:23: error: use of undeclared identifier 'pool'
0.317  pthread_mutex_lock(&pool.lock);
0.317                      ^
0.318 main.c:64:29: error: use of undeclared identifier 'pool'
0.318  pthread_mutex_t* mutex = &pool->mutexes[pool->num_mutexes];
0.318                            ^
0.318 main.c:64:43: error: use of undeclared identifier 'pool'
0.319  pthread_mutex_t* mutex = &pool->mutexes[pool->num_mutexes];
0.319                                          ^
0.319 main.c:66:3: error: use of undeclared identifier 'pool'
0.319  pool->num_mutexes++;
0.319  ^
0.319 main.c:68:25: error: use of undeclared identifier 'pool'
0.319  pthread_mutex_unlock(&pool.lock);
0.319                        ^
0.321 main.c:152:5: warning: type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
0.322    reti = regexec(&regex, url, 2, matches, 0);
0.322    ^
0.322    int
0.322 main.c:152:21: error: use of undeclared identifier 'regex'
0.322    reti = regexec(&regex, url, 2, matches, 0);
0.322                    ^
0.322 main.c:152:28: error: use of undeclared identifier 'url'
0.322    reti = regexec(&regex, url, 2, matches, 0);
0.322                           ^
0.322 main.c:154:5: error: expected identifier or '('
0.322    if (!reti) {
0.322    ^
0.322 main.c:157:7: error: expected identifier or '('
0.322    } else {
0.322      ^
0.322 main.c:163:13: error: expected parameter declarator
0.322    regfree(&regex);
0.322            ^
0.322 main.c:163:13: error: expected ')'
0.322 main.c:163:12: note: to match this '('
0.322    regfree(&regex);
0.322           ^
0.322 main.c:163:5: warning: type specifier missing, defaults to 'int'; ISO C99 and later do not support implicit int [-Wimplicit-int]
0.322    regfree(&regex);
0.322    ^
0.322    int
0.322 main.c:163:5: warning: a function declaration without a prototype is deprecated in all versions of C and is treated as a zero-parameter prototype in C2x, conflicting with a previous declaration [-Wdeprecated-non-prototype]
0.322 /usr/include/regex.h:689:13: note: conflicting prototype is here
0.322 extern void regfree (regex_t *__preg);
0.322            ^
0.322 main.c:163:5: error: conflicting types for 'regfree'
0.323    regfree(&regex);
0.323    ^
0.323 /usr/include/regex.h:689:13: note: previous declaration is here
0.323 extern void regfree (regex_t *__preg);
0.323            ^
0.323 main.c:164:1: error: extraneous closing brace ('}')
0.323 }
0.323 ^
0.323 main.c:166:50: error: unknown type name 'PGconn'
0.323 int get_cliente_for_update(cliente *c, char *id, PGconn *pg_conn) {
0.323                                                 ^
0.323 main.c:170:10: warning: call to undeclared function '_get_cliente'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
0.323  return _get_cliente(c, id, query, pg_conn);
0.323         ^
0.324 main.c:177:3: error: use of undeclared identifier 'PGconn'
0.324  PGconn *pg_conn = get_connection();
0.324  ^
0.325 main.c:177:11: error: use of undeclared identifier 'pg_conn'
0.325  PGconn *pg_conn = get_connection();
0.325          ^
0.325 main.c:177:21: warning: call to undeclared function 'get_connection'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
0.325  PGconn *pg_conn = get_connection();
0.325                    ^
0.325 main.c:178:16: warning: call to undeclared function '_get_cliente'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
0.325  int result = _get_cliente(c, id, query, pg_conn);
0.325               ^
0.326 main.c:178:43: error: use of undeclared identifier 'pg_conn'
0.326  int result = _get_cliente(c, id, query, pg_conn);
0.326                                          ^
0.326 main.c:179:3: warning: call to undeclared function 'release_connection'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
0.326  release_connection(pg_conn);
0.326  ^
0.326 main.c:179:22: error: use of undeclared identifier 'pg_conn'
0.326  release_connection(pg_conn);
0.326                     ^
0.327 fatal error: too many errors emitted, stopping now [-ferror-limit=]
0.330 7 warnings and 20 errors generated.
------
Dockerfile:30
--------------------
 28 |    
 29 |    # Compila a aplicação
 30 | >>> RUN clang-15 -O2 -o main main.c -lcjson -lmicrohttpd
 31 |    
 32 |    # Instrução Docker para executar o contêiner
--------------------
ERROR: failed to solve: process "/bin/sh -c clang-15 -O2 -o main main.c -lcjson -lmicrohttpd" did not complete successfully: exit code: 1
sobrinhosj@cs-610301933215-default:~/pena$ 

O Dockerfile está falhando na etapa de compilação (linha 30) devido a vários erros no código-fonte `main.c`. Vamos analisar os erros e te ajudar a corrigi-los:

**Erros no código-fonte `main.c`:**

* **Variáveis não declaradas:** O código usa variáveis como `pool`, `regex`, `url` e funções como `_get_cliente`, `get_connection`, `release_connection` que não estão declaradas. É preciso defini-las ou incluir os arquivos de cabeçalho corretos.
* **Biblioteca `pthread`:** Os erros relacionados a `pthread_mutex_init` e `pthread_mutex_lock` indicam que você está usando a biblioteca `pthread` para mutexes. Certifique-se de incluir o cabeçalho `<pthread.h>` e linkar a biblioteca `-lpthread` durante a compilação.
* **Biblioteca `regex.h`:** Erros relacionados a `regfree` sugerem uso da biblioteca `regex.h`. Inclua o cabeçalho `<regex.h>` e linke a biblioteca `-lregex` durante a compilação.
* **Funções ausentes:** Corrija as funções ausentes (`_get_cliente`, `get_connection`, `release_connection`) ou inclua os arquivos que as definem.
* **Tipo de dado `PGconn`:** O erro indica que o tipo `PGconn` não está definido. Verifique se ele vem de uma biblioteca específica e inclua o cabeçalho correspondente.
* **Aviso: tipo faltando:** O aviso `warning: type specifier missing` indica que faltam especificadores de tipo para algumas variáveis. Declare-as explicitamente (por exemplo, `int reti;`).

**Corrigindo o Dockerfile:**

1. **Inclua bibliotecas:** Modifique a linha de compilação (linha 30) para incluir as bibliotecas necessárias:

   ```dockerfile
   RUN clang-15 -O2 -o main main.c -lcjson -lmicrohttpd -lpthread -lregex
   ```

2. **Verifique código-fonte:** Analise o código `main.c` para corrigir as variáveis e funções ausentes. Inclua os arquivos de cabeçalho corretos para bibliotecas usadas.

**Recomendações:**

* **Organize o código:** Use bibliotecas e módulos para separar a funcionalidade e melhorar a clareza.
* **Declare explicitamente:** Declare variáveis e funções com seus tipos de dados para evitar avisos do compilador.
* **Inclua cabeçalhos:** Verifique se todos os arquivos de cabeçalho necessários estão sendo incluídos.

Após corrigir os erros no código-fonte e atualizar o Dockerfile, tente compilar a imagem novamente. Se precisar de ajuda específica com o código `main.c`, compartilhe o conteúdo do arquivo para uma análise mais detalhada.


O código do seu Dockerfile tem erros de compilação e precisa de algumas correções para funcionar. Aqui está uma análise detalhada dos erros e como corrigi-los:

**Erros de compilação:**

* **`struct MutexPool`:** O código tenta usar um tipo de estrutura `MutexPool` que não foi declarada. É provável que essa estrutura esteja definida em outro arquivo de cabeçalho. Certifique-se de incluir o cabeçalho correto usando a instrução `COPY` ou `ADD` para trazer o arquivo para o contêiner antes da compilação.

* **`pool`:** O código usa uma variável `pool` do tipo `MutexPool`, mas ela não foi declarada. Defina a variável antes de usá-la.

* **`regex` e `url`:**  As variáveis `regex` e `url` são usadas na função `regexec`, mas não foram declaradas. Você precisa inicializar essas variáveis antes de usá-las.

* **`PGconn`:** O código usa o tipo `PGconn` e funções como `get_connection` e `release_connection` que provavelmente estão relacionadas ao PostgreSQL. Certifique-se de incluir as bibliotecas necessárias para o PostgreSQL (libpq) e implementar as funções ausentes.

* **Funções ausentes:** Várias funções como `_get_cliente` e `get_connection` são chamadas, mas não estão definidas no código fornecido. Você precisa implementar essas funções ou incluir o código de onde elas vêm.

**Corrigindo o Dockerfile:**

1. **Inclua o cabeçalho necessário (se aplicável):**

   ```dockerfile
   COPY header.h .  # Substitua "header.h" pelo nome do arquivo correto
   ```

2. **Defina a variável `pool`:**

   ```c
   MutexPool pool;  // Defina a variável antes de usá-la
   ```

3. **Declare e inicialize as variáveis `regex` e `url`:**

   ```c
   regex_t regex;
   char *url;
   // Inicialize essas variáveis antes de usar a função regexec
   ```

4. **Inclua bibliotecas e implemente funções do PostgreSQL (se aplicável):**

   ```dockerfile
   RUN apt-get update && apt-get install -y libpq-dev  # Instala a biblioteca PostgreSQL
   ```

   Você precisará implementar as funções `get_connection`, `release_connection` e possivelmente `_get_cliente` para lidar com o banco de dados.

5. **Corrija as chamadas de função ausentes:**

   Se as funções ausentes estão em outro arquivo de código-fonte, inclua esse arquivo usando `COPY` ou `ADD`. Se elas precisam ser implementadas, adicione o código de implementação ao seu arquivo `main.c`.

**Com essas correções, o Dockerfile deve compilar e executar seu aplicativo com sucesso.**

**Dicas adicionais:**

* Considere usar um gerenciador de pacotes como o `apt-get` para instalar bibliotecas ausentes em vez de incluí-las diretamente no contêiner.
* Verifique se a estrutura `MutexPool` está definida corretamente e se as funções relacionadas ao mutex estão sendo usadas de maneira apropriada.
* Certifique-se de que o código para lidar com o banco de dados PostgreSQL está implementado corretamente.


O Dockerfile está falhando na etapa de compilação (RUN) devido a vários erros no código-fonte `main.c`. Vamos analisar os erros e te ajudar a corrigi-los:

**Erros principais:**

* **Variáveis não declaradas:** O código usa variáveis como `pool`, `regex`, `url`, `pg_conn` e funções como `_get_cliente`, `get_connection`, `release_connection` sem declará-las.
* **Biblioteca ausente:** O código tenta usar a biblioteca `regex.h` para expressões regulares, mas ela não está sendo linkada (falta a flag `-lpthread` para pthread).
* **Biblioteca do banco de dados ausente:** O código usa `PGconn` (provavelmente relacionado ao PostgreSQL), mas a biblioteca correspondente não está sendo linkada.

**Passos para corrigir:**

1. **Defina as variáveis ausentes:** Verifique `main.c` e declare as variáveis usadas (por exemplo, `struct MutexPool pool`).
2. **Inclua a biblioteca `regex.h`:** Adicione `-lpthread` na instrução `RUN` para incluir a biblioteca pthread necessária para `regex.h`.
3. **Link bibliotecas do banco de dados:** Se for usar o PostgreSQL, adicione a flag apropriada para a biblioteca do cliente (por exemplo, `-lpq` para libpq).
4. **Verifique funções ausentes:** As funções `_get_cliente`, `get_connection`, e `release_connection` parecem não estar definidas. Localize-as em outro arquivo ou implemente-as em `main.c`.

**Linha corrigida do Dockerfile (exemplo):**

```dockerfile
RUN clang-15 -O2 -o main main.c -lcjson -lmicrohttpd -lpthread # Adiciona -lpthread para regex.h
```

**Observações:**

* Os avisos sobre tipo de variável (`int`) podem ser ignorados por enquanto.
* Lembre de adaptar as correções de acordo com a estrutura do seu projeto e bibliotecas utilizadas.

Depois de fazer as alterações, tente reconstruir a imagem do Docker usando `docker build -t <nome-da-imagem> .`.


//------------------hummmm----------------------//

// gcc -shared -fPIC -o libcodorna.so main.c -lmicrohttpd -lpthread
// main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <pthread.h>

#define MAX_CLIENTES 100

typedef struct {
    char id[11];
    int saldo;
} cliente;

cliente clientes[MAX_CLIENTES];
pthread_mutex_t clientes_mutex;

void init_clientes() {
    pthread_mutex_init(&clientes_mutex, NULL);
    for (int i = 0; i < MAX_CLIENTES; i++) {
        strcpy(clientes[i].id, "");
        clientes[i].saldo = 0;
    }
}

int get_cliente(char *id, char *response) {
    pthread_mutex_lock(&clientes_mutex);
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (strcmp(clientes[i].id, id) == 0) {
            sprintf(response, "{\"id\": \"%s\", \"saldo\": %d}", clientes[i].id, clientes[i].saldo);
            pthread_mutex_unlock(&clientes_mutex);
            return 1; // Cliente encontrado
        }
    }
    pthread_mutex_unlock(&clientes_mutex);
    sprintf(response, "{\"error\": \"Cliente não encontrado\"}");
    return 0; // Cliente não encontrado
}

int salva_cliente(char *id, int saldo) {
    pthread_mutex_lock(&clientes_mutex);
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (strcmp(clientes[i].id, id) == 0) {
            clientes[i].saldo += saldo;
            pthread_mutex_unlock(&clientes_mutex);
            return 1; // Cliente atualizado
        }
    }
    // Cliente não encontrado, tenta adicionar novo cliente
    for (int i = 0; i < MAX_CLIENTES; i++) {
        if (strcmp(clientes[i].id, "") == 0) {
            strcpy(clientes[i].id, id);
            clientes[i].saldo = saldo;
            pthread_mutex_unlock(&clientes_mutex);
            return 2; // Novo cliente adicionado
        }
    }
    pthread_mutex_unlock(&clientes_mutex);
    return 0; // Falha ao adicionar cliente
}

// Função para lidar com as requisições HTTP
int handle_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version,
                   const char *upload_data, size_t *upload_data_size, void **con_cls) {
    char response[1024];
    if (strcmp(method, "GET") == 0) {
        char id[11];
        sscanf(url, "/clientes/%s", id);
        if (get_cliente(id, response)) {
            struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, http_response);
            MHD_destroy_response(http_response);
            return ret;
        } else {
            struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, http_response);
            MHD_destroy_response(http_response);
            return ret;
        }
    } else if (strcmp(method, "POST") == 0) {
        char id[11];
        int saldo;
        sscanf(url, "/clientes/%s", id);
        sscanf(upload_data, "saldo=%d", &saldo);
        int result = salva_cliente(id, saldo);
        if (result == 1) {
            sprintf(response, "{\"message\": \"Saldo atualizado para o cliente %s\"}", id);
            struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, http_response);
            MHD_destroy_response(http_response);
            return ret;
        } else if (result == 2) {
            sprintf(response, "{\"message\": \"Novo cliente adicionado: %s\"}", id);
            struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_CREATED, http_response);
            MHD_destroy_response(http_response);
            return ret;
        } else {
            sprintf(response, "{\"error\": \"Falha ao atualizar o saldo para o cliente %s\"}", id);
            struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, http_response);
            MHD_destroy_response(http_response);
            return ret;
        }
    } else {
        struct MHD_Response *http_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, http_response);
        MHD_destroy_response(http_response);
        return ret;
    }
}

// Função de inicialização do servidor
struct MHD_Daemon *init_server(int port) {
    return MHD_start_daemon(MHD_USE_EPOLL_INTERNAL_THREAD | MHD_USE_EPOLL_TURBO, port, NULL, NULL, &handle_request, NULL, MHD_OPTION_CONNECTION_TIMEOUT, 30, MHD_OPTION_END);
}

