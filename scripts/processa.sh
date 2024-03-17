#!/bin/bash

# Função para fazer a requisição HTTP
fazer_requisicao() {
    local url=$1
    local response=$(curl -s "$url")
    echo "$response"
}

# Verifica se foi fornecida uma URL como argumento
if [[ -z "$1" ]]; then
    echo "Uso: $0 <URL>"
    exit 1
fi

# Recebe a URL como argumento
url=$1

# Faz a requisição HTTP
resposta=$(fazer_requisicao "$url")

# Verifica se a requisição foi bem-sucedida
if [[ $? -eq 0 ]]; then
    echo "$resposta"
else
    echo "Erro ao processar requisição: $url"
fi
