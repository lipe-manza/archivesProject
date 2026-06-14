import struct
data = open('arq_entrada/variasInsercoes.bin', 'rb').read()
header = data[:17]
records = data[17:]
existing_keys = set()
for i in range(0, len(records), 80):
    record = records[i:i+80]
    if record[0] == ord('0'): # removido
        continue
    codEstacao = struct.unpack('<i', record[5:9])[0]
    existing_keys.add(codEstacao)

print("Existing keys:", sorted(existing_keys))
inserts = list(range(1, 51))
dups = [k for k in inserts if k in existing_keys]
news = [k for k in inserts if k not in existing_keys]
print(f"Duplicates: {dups}")
print(f"New inserts: {news}")
