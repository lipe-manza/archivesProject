#!/usr/bin/env fish

echo "🔨 Compilando o projeto com símbolos de debug..."
make debug
if test $status -ne 0
    echo "❌ Falha na compilação!"
    exit 1
end

echo "🚀 Iniciando os testes com Valgrind..."
echo "----------------------------------------"

# Limpa resquícios
find . -maxdepth 1 -name "*.bin" -delete 2>/dev/null
rm -f *.txt *.valgrind 2>/dev/null

# Copia entradas
cp arq_entrada/*.bin ./ 2>/dev/null

set passed 0
set leaks 0
set failed 0

# Função auxiliar para rodar valgrind
function run_valgrind -d "Roda teste com valgrind"
    set name $argv[1]
    set input_str $argv[2]
    set log_file "$name.valgrind"

    echo -n "Executando Valgrind no teste: $name ... "

    echo $input_str | valgrind --leak-check=full \
                               --show-leak-kinds=all \
                               --track-origins=yes \
                               --error-exitcode=99 \
                               --log-file=$log_file \
                               ./programTrab > /dev/null

    set valgrind_status $status

    if test $valgrind_status -eq 99
        echo "❌ LEAK/ERROR DETECTED"
        set -g leaks (math $leaks + 1)
        cat $log_file
    else if test $valgrind_status -ne 0
        echo "💥 CRASH / EXECUTION ERROR (Exit code: $valgrind_status)"
        set -g failed (math $failed + 1)
        cat $log_file
    else
        echo "✅ OK"
        set -g passed (math $passed + 1)
        rm -f $log_file
    end
end

run_valgrind "Join_11" "11
estacoes1.bin codProxEstacao
estacoes2.bin codEstacao"

run_valgrind "Join_12" "12
estacoes1.bin codProxEstacao
estacoes2.bin codEstacao
indice_estacoes1.bin"

run_valgrind "Sort_13_cod" "13
estacoes1.bin codEstacao estacoesOrdCod_test.bin"

run_valgrind "Sort_13_prox" "13
estacoes1.bin codProxEstacao estacoesOrdProx_test.bin"

run_valgrind "Join_14" "14
estacoes1.bin codProxEstacao
estacoes2.bin codEstacao"

# Limpeza
find . -maxdepth 1 -name "*.bin" -delete 2>/dev/null
find . -maxdepth 1 -name "*.txt" -delete 2>/dev/null
find . -maxdepth 1 -name "*.valgrind" -delete 2>/dev/null

echo "----------------------------------------"
echo "📊 Resumo dos Testes com Valgrind:"
echo "   Sem leaks/erros: $passed"
if test $leaks -gt 0
    echo "   Com leaks/erros: $leaks"
end
if test $failed -gt 0
    echo "   Com falhas/crash: $failed"
end

if test $leaks -gt 0 -o $failed -gt 0
    exit 1
else
    exit 0
end
