import re
content = open('src/sql/09_insert_into_ab.c').read()

insert_check = """
    int target_key = data_record_get_codEstacao(new_record);
    if (btree_search_key(f_btree, btree_header, target_key) != BTREE_NOT_FOUND) {
        data_record_destroy(&new_record);
        continue;
    }
"""

content = content.replace('int top_stack = data_header_get_topo(data_header);', insert_check + '\\n    int top_stack = data_header_get_topo(data_header);')

open('src/sql/09_insert_into_ab.c', 'w').write(content)
