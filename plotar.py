import csv
import matplotlib.pyplot as plt
from pathlib import Path
import random

# Dicionário de cores para cada título

class Titulo:
    def __init__(self, nome):
        self.nome =nome
        self.dados = {}
        self.parametros = []
        self.modelosValores = {}

def gerarCor(cores):
    '''gera cor aleatória que nao esteja no vetor cores'''
    while True:
        # Gerar uma cor aleatória no formato RGB
        cor = (random.randint(0, 255)/255.0, random.randint(0, 255)/255.0, random.randint(0, 255)/255.0)

        # Verificar se a cor já existe na lista
        if cor not in cores:
            cores.append(cor)
            return cor

def imprimeTitulo(titulo):
    # Configuração do gráfico
    plt.figure(figsize=(10, 6))
    plt.xlabel('Variância')
    plt.ylabel('Preço')

    # Plotagem das curvas
    cor = []#para colorir cada modelo com uma diferente
    nomes = list(titulo.modelosValores.keys())
    plt.title('Gráfico de preço em relação à variância\n'+titulo.nome)
    for nome in nomes:
        plt.plot(titulo.parametros, titulo.modelosValores[nome],label=nome, color=gerarCor(cor))
    plt.legend()
    plt.show()


def main(path):
    '''Abre todos arquivos em path e os le como titulos diferentes'''
    titulos = []
    arquivos = sorted(Path(path).glob('*'))
    for file in arquivos:
        #"MODELO,VARIANCIA,PRECO"
        with open(file, 'r') as arquivo:  
            titulos.append(Titulo(str(file).split('.')[0].split('/')[1]))
            leitor = csv.reader(arquivo)
            for linha in list(leitor)[1:]:#ignorando o header
                #guarda variancia, se ela ja não estiver la
                if float(linha[1]) not in titulos[-1].parametros:
                    titulos[-1].parametros.append(float(linha[1]))
                #verifica se modelo ja tem uma entrada no dicionario
                if linha[0] not in titulos[-1].modelosValores:
                    titulos[-1].modelosValores[linha[0]] = []
                #guarda valor do preco
                titulos[-1].modelosValores[linha[0]].append(float(linha[2]))
            imprimeTitulo(titulos[-1])


main("precos/")
