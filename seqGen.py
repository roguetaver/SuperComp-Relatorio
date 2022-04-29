# GERADOR DE INSTÂNCIAS PARA COMPARAÇÃO DE SEQUENCIAS DE DNA

# Para usar este gerador, você deve fornecer três parâmetros:

# n = tamanho da primeira sequencia

# m = tamanho da segunda instância

# file = nome do arquivo da instância a ser gerada

import random

i = 1

for n in range(25, 251, 25):
    for m in range(25, 251, 25):
        file = 'dna{}.seq'.format(i)
        f = open(file, 'w')
        seq = [str(n)+'\n',
               str(m)+'\n',
               ''.join(random.choices(['A', 'T', 'C', 'G', '-'], k=n))+'\n',
               ''.join(random.choices(['A', 'T', 'C', 'G', '-'], k=m))]
        f.writelines(seq)
        f.close()
        i += 1
