import struct
data = open('arq_entrada/estacoesRemBTree.bin', 'rb').read()
for i in range(17, len(data), 53):
    if i < len(data):
        status = chr(data[i])
        if status == '0': # ativo
            tipo = struct.unpack('<i', data[i+5:i+9])[0]
            print("Node RRN", (i-17)//53, "type", tipo)
