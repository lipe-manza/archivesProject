import re

content = open('src/sql/09_insert_into_ab.c').read()
content = content.replace('BinarioNaTela', 'printf("Data=%lf\\n", cs_data); BinarioNaTela')

# Let's write a quick fix manually
