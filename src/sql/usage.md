1. CREATE TABLE
`[funcao: 1] [entrada: nome_arquivo_csv] [saida: nome_arquivo_binario]`

2. SELECT FROM
`[funcao: 2] [entrada: nome_arquivo_binario]`

3. SELECT FROM WHERE
`[funcao: 3] [entrada: nome_arquivo_binario] [numero_consultas]`
`[numero_campos_1] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
...
`[numero_campos_n] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`

4. DELETE FROM WHERE
`[funcao: 4] [entrada: nome_arquivo_binario] [numero_consultas]`
`[numero_campos_1] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
...
`[numero_campos_n] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`

5. INSERT INTO
`[funcao: 5] [entrada: nome_arquivo_binario] [numero_insercoes]`
`[codestacao_1], [nomeestacao_1], [codlinha_1], [nomelinha_1], [codproxestacao_1], [distproxestacao_1], [codlinhaintegra_1], [codestacaointegra_1]`
...
`[codestacao_n], [nomeestacao_n], [codlinha_n], [nomelinha_n], [codproxestacao_n], [distproxestacao_n], [codlinhaintegra_n], [codestacaointegra_n]`

6. UPDATE SET WHERE
`[funcao: 6] [entrada: nome_arquivo_binario] [numero_consultas]`
`[numero_campos_selecao_1] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
`[numero_campos_atualizacao_1] [nome_campo_1] [valor_campo_1] ... [nome_campo_m] [valor_campo_m]`
...
`[numero_campos_selecao_n] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
`[numero_campos_atualizacao_n] [nome_campo_1] [valor_campo_1] ... [nome_campo_m] [valor_campo_m]`

7. CREATE INDEX
`[funcao: 7] [entrada: nome_arquivo_entrada] [saida: nome_arquivo_bt]`

8. SELECT FROM WHERE BT
`[funcao: 8] [entrada: nome_arquivo_entrada] [indice: nome_arquivo_bt] [numero_consultas]`
`[numero_campos_1] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
...
`[numero_campos_n] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`

9. INSERT INTO BT
`[funcao: 9] [entrada: nome_arquivo_entrada] [indice: nome_arquivo_bt] [numero_insercoes]`
`[codestacao_1], [nomeestacao_1], [codlinha_1], [nomelinha_1], [codproxestacao_1], [distproxestacao_1], [codlinhaintegra_1], [codestacaointegra_1]`
...
`[codestacao_n], [nomeestacao_n], [codlinha_n], [nomelinha_n], [codproxestacao_n], [distproxestacao_n], [codlinhaintegra_n], [codestacaointegra_n]`

10. DELETE FROM WHERE BT
`[funcao: 10] [entrada: nome_arquivo_entrada] [indice: nome_arquivo_bt] [numero_consultas]`
`[numero_campos_1] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
...
`[numero_campos_n] [nome_campo_1] [valor_campo_1] ... [nome_campo_n] [valor_campo_n]`
