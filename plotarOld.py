import csv
import matplotlib.pyplot as plt
import random

# Dicionário de cores para cada título

class Titulo:
    def __init__(self, nome, cor):
        self.nome =nome
        self.dados = {}
        self.parametros = []
        self.modelosValores = {}
        self.cor = cor

def gerarCor(cores):
    '''gera cor aleatória que nao esteja no vetor cores'''
    while True:
        # Gerar uma cor aleatória no formato RGB
        cor = (random.randint(0, 255)/255.0, random.randint(0, 255)/255.0, random.randint(0, 255)/255.0)

        # Verificar se a cor já existe na lista
        if cor not in cores:
            cores.append(cor)
            return cor

# Leitura dos dados do arquivo CSV
titulos = []
with open('dadosPlotar.csv', 'r') as arquivo:
    leitor = csv.reader(arquivo)
    cores = []
    for linha in leitor:
        titulo = linha[0]
        titulos.append(Titulo(titulo, gerarCor(cores)))
        for dados in linha[1:]:
            dados = dados.split(';')
            titulos[-1].parametros.append(float(dados[0]))

            for i in range(1, len(dados[1:]), 2):
                if dados[i] not in titulos[-1].modelosValores:
                    titulos[-1].modelosValores[dados[i]] = []
                titulos[-1].modelosValores[dados[i]].append(float(dados[i+1]))

# Configuração do gráfico
plt.figure(figsize=(10, 6))
plt.xlabel('Variância')
plt.ylabel('Preço')

# Plotagem das curvas
for titulo in titulos:
    cor = []
    nomes = list(titulo.modelosValores.keys())
    plt.figure(figsize=(10, 6))
    plt.xlabel('Variância')
    plt.ylabel('Preço')
    plt.title('Gráfico de preço em relação à variância\n'+titulo.nome)
    for nome in nomes:
        plt.plot(titulo.parametros, titulo.modelosValores[nome],label=nome, color=gerarCor(cor))
    plt.legend()
    plt.show()


