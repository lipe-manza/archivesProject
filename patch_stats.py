import re
content = open('src/sql/09_insert_into_ab.c').read()

# Replace update_statistics with incremental updates
content = content.replace('update_statistics(f_data, data_header);', '/* no update_statistics */')

open('src/sql/09_insert_into_ab.c', 'w').write(content)
