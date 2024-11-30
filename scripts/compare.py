import os
import re


def agrupar_por_folhas(lista_arquivos):
    """Agrupa arquivos por número de folhas.

    Args:
        lista_arquivos: Uma lista de strings no formato 'Tree-Xl-Y.arv'.

    Returns:
        Um dicionário onde as chaves são os números de folhas e os valores são listas
        de arquivos com aquele número de folhas.
    """

    padrao = r"Tree-(\d+)l-(\d+)\.arv"  # Expressão regular para extrair o número de folhas
    grupos = {}

    for arquivo in lista_arquivos:
        match = re.match(padrao, arquivo)
        if match:
            num_folhas = int(match.group(1))
            grupos.setdefault(num_folhas, []).append(arquivo)

    return grupos

def compare(lista):
    bashCommand = "../build/release/distance"
    for a in range(0, len(lista)-2):
        for b in range(1, len(lista)-1):
            for c in range(2, len(lista)):
              string = "../instances/1st_dataset/"
              listaa = "".join([string, lista[a]])
              listab = "".join([string, lista[b]])
              listac = "".join([string, lista[c]])
              command = " ".join([bashCommand, listaa, listab, listac])
              os.system(command)  


def main():
    directory = '../instances/1st_dataset'

    # Lista os arquivos
    arquivos = os.listdir(directory)

    grupos = agrupar_por_folhas(arquivos)

    for a in grupos:
        compare(grupos[a])


if __name__ == "__main__":
    main()