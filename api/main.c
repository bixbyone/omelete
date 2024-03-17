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
