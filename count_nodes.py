import struct
data = open('arq_entrada/estacoesRemBTree.bin', 'rb').read()
nodes = 0
for i in range(17, len(data), 53):
    if i < len(data):
        status = data[i]
        if status == ord('0'): # ativo
            nodes += 1
print("Active nodes:", nodes)
