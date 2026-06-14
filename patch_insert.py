import re

content = open('src/btree/btree_insert.c').read()
content = content.replace('return false;', 'do { printf("Failed at btree_insert.c line %d\\n", __LINE__); return false; } while(0);')
open('src/btree/btree_insert.c', 'w').write(content)
