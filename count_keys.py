import struct
data = open('arq_entrada/estacoesRemBTree.bin', 'rb').read()
keys = 0
for i in range(17, len(data), 53):
    if i < len(data):
        status = chr(data[i])
        if status == '0': # ativo
            num_keys = struct.unpack('<i', data[i+9:i+13])[0]
            keys += num_keys
print("Keys:", keys)
