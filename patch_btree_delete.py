import re
content = open('src/btree/btree_delete.c').read()

merge_right_target = """    // Remove a chave do pai
    remove_key_from_page(parent, child_idx);"""

merge_right_replacement = """    // PREVINE O BUG DE PONTEIRO: O `remove_key_from_page` shiftará P[child_idx+1] -> P[child_idx].
    btree_page_set_child_pointer(parent, child_idx + 1, child_rrn);
    
    // Remove a chave do pai
    remove_key_from_page(parent, child_idx);"""

content = content.replace(merge_right_target, merge_right_replacement)
open('src/btree/btree_delete.c', 'w').write(content)
