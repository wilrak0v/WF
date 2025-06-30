#!/bin/bash

# Vérifier que le fichier binaire est passé en argument
if [ -z "$1" ]; then
    echo "Veuillez spécifier le fichier binaire."
    exit 1
fi

# Lire le fichier binaire et formater la sortie
s=$(xxd -p "$1" | tr -d '\n' | sed 's/\(..\)/\1 /g')
j=1
for ((i=0; i<${#s}; i++)); do
  printf "%s" "${s:i:1}"
  if ((j % 8 == 0)); then
    printf "  "
  fi
  if ((j % 56 == 0)); then
    echo
  fi
  if [ " " != "${s:i:1}" ]; then
    j=$j+1
  fi
done

echo
