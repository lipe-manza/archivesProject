import re

content = open('src/btree/btree_insert.c').read()
content = content.replace('return BTREE_ERROR;', '{ printf("Error at line %d\\n", __LINE__); return BTREE_ERROR; }')
open('src/btree/btree_insert.c', 'w').write(content)
