import re

content = open('src/sql/07_create_index_ab.c').read()

# Replace falha_processamento_arquivo with a macro or inline print
content = content.replace('falha_processamento_arquivo(', 'printf("Failed at line %d\\n", __LINE__); falha_processamento_arquivo(')
# Fix the declaration which was mangled
content = content.replace('printf("Failed at line %d\\n", __LINE__); falha_processamento_arquivo(FILE', 'falha_processamento_arquivo(FILE')

open('src/sql/07_create_index_ab.c', 'w').write(content)
