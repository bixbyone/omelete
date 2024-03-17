#!/bin/bash

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
      # Extrai o ID do cliente da URL
      id=$(echo "$url" | awk -F'/' '{print $3}')
      
      # Chama função C para GET
      response=$(get_cliente "$id")
    ;;

    POST)
      # Extrai o ID do cliente e o saldo do corpo da requisição
      id=$(echo "$url" | awk -F'/' '{print $3}')
      body=$(echo "$request" | tail -n 1)
      
      # Chama função C para POST 
      response=$(salva_cliente "$id" "$body")
    ;;

  esac

  # Retorna resposta para o Nginx
  echo "$response"

done

# Pool de processos para escalabilidade
MAX_WORKERS=100

while [[ "$#" -gt 0 ]]; do

  # processa requisição em background
   bash "$(dirname "$0")/scripts/processa.sh" "$1" &

  # aguardaWorker 
  shift
  
  if [[ "${#}" -eq "$MAX_WORKERS" ]]; then
    wait
  fi

done
