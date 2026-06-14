import re
content = open('src/btree/btree_page.c').read()

new_write = """bool btree_page_write(FILE *bin_file, const BTreePage *page, int rrn) {
  if (bin_file == NULL || page == NULL || rrn < 0)
    return false;

  if (fseek(bin_file, calculate_page_offset(rrn), SEEK_SET) != 0)
    return false;

  if (page->removido == '1') {
      fwrite(&page->removido, sizeof(char), 1, bin_file);
      fwrite(&page->proximo, sizeof(int), 1, bin_file);
      char lixo[48];
      memset(lixo, '$', 48);
      fwrite(lixo, sizeof(char), 48, bin_file);
      return true;
  }

  if (fwrite(&page->removido, sizeof(char), 1, bin_file) != 1)
    return false;
  if (fwrite(&page->proximo, sizeof(int), 1, bin_file) != 1)
"""

content = re.sub(r'bool btree_page_write\(FILE \*bin_file, const BTreePage \*page, int rrn\) \{.*?if \(fwrite\(&page->removido, sizeof\(char\), 1, bin_file\) != 1\)', new_write, content, flags=re.DOTALL)
open('src/btree/btree_page.c', 'w').write(content)
