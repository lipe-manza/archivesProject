#!/usr/bin/env fish

echo "Empacotando projeto para o Run.codes..."
zip -r programa.zip src include Makefile
echo "Feito! Arquivo programa.zip gerado com sucesso."
