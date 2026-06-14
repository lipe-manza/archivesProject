#!/usr/bin/env fish

# Compila o projeto com símbolos de debug (-g)
echo "🔨 Compilando o projeto com símbolos de debug..."
make debug
if test $status -ne 0
    echo "❌ Falha na compilação!"
    exit 1
end

# Define os caminhos
set TEST_DIR "./tests"
set ENTRADA_DIR "./arq_entrada"
set EXECUTABLE "./programTrab"

# Contador de erros, vazamentos e sucessos
set passed 0
set leaks 0
set failed 0

echo "🚀 Iniciando os testes com Valgrind..."
echo "----------------------------------------"

# Remove resquícios de arquivos .bin antes de iniciar sem causar erros se não existirem
find . -maxdepth 1 -name "*.bin" -delete

# Busca por todos os arquivos .in no diretório de testes
for in_file in (ls -v $TEST_DIR/*.in)
    # Extrai o nome base do caso de teste
    set base_name (string replace -r '\.in$' '' $in_file)
    set out_got "$base_name.got"
    set valgrind_log "$base_name.valgrind"

    echo -n "Running valgrind (case: "(basename $base_name)") ... "

    # 1. SETUP: Copia os arquivos originais do arq_entrada para a raiz
    cp $ENTRADA_DIR/* ./ 2>/dev/null

    # 2. EXECUÇÃO: Executa o programa com Valgrind salvando logs
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --error-exitcode=99 \
             --log-file=$valgrind_log \
             $EXECUTABLE < $in_file > $out_got

    set valgrind_status $status

    # 3. VERIFICAÇÃO DE VAZAMENTO / ERRO DE MEMÓRIA
    if test $valgrind_status -eq 99
        echo "❌ LEAK/ERROR DETECTED"
        set leaks (math $leaks + 1)
        echo "--- Detalhes do Valgrind: ---"
        if test -f $valgrind_log
            cat $valgrind_log
        else
            echo "Erro: Log do Valgrind não pôde ser gerado."
        end
        echo "-----------------------------"
    else if test $valgrind_status -ne 0
        echo "💥 CRASH / EXECUTION ERROR (Exit code: $valgrind_status)"
        set failed (math $failed + 1)
        echo "--- Detalhes do Valgrind: ---"
        if test -f $valgrind_log
            cat $valgrind_log
        else
            echo "Erro: Log do Valgrind não pôde ser gerado."
        end
        echo "-----------------------------"
    else
        echo "✅ OK"
        set passed (math $passed + 1)
        # Remove o log temporário e saída do teste se não houve erro
        rm -f $valgrind_log $out_got
    end

    # 4. TEARDOWN: Limpa todos os arquivos binários
    find . -maxdepth 1 -name "*.bin" -delete
end

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
