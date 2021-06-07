siguel: xablau

FLAGS = -fstack-protector-all -std=c99

xablau: main.o list.o qry.o convexHull.o calculos.o ler_file.o svg.o txt.o generico.o quadrilatero.o ponto.o poligono.o circulo.o retangulo.o quadra.o texto.o linha.o args.o QuadTree.o hashTable.o pessoa.o morador.o estabelecimento.o chaveXvalor.o grafo.o rua.o
	gcc -o siguel main.o list.o qry.o convexHull.o calculos.o ler_file.o svg.o txt.o generico.o quadrilatero.o ponto.o poligono.o circulo.o retangulo.o quadra.o texto.o linha.o args.o QuadTree.o hashTable.o pessoa.o morador.o estabelecimento.o chaveXvalor.o grafo.o rua.o -lm $(FLAGS) 
	rm -rf *.o *~

main.o: main.c ler_file.h args.h 
	gcc -o main.o main.c -c $(FLAGS)

list.o: list.c list.h
	gcc -o list.o list.c -c $(FLAGS)

qry.o: qry.c qry.h
	gcc -o qry.o qry.c -c $(FLAGS)

convexHull.o: convexHull.c convexHull.h
	gcc -o convexHull.o convexHull.c -c $(FLAGS)

calculos.o: calculos.c calculos.h
	gcc -o calculos.o calculos.c -c $(FLAGS)

ler_file.o: ler_file.c ler_file.h
	gcc -o ler_file.o ler_file.c -c $(FLAGS)

svg.o: svg.c svg.h
	gcc -o svg.o svg.c -c $(FLAGS)

txt.o: txt.c txt.h
	gcc -o txt.o txt.c -c $(FLAGS)

generico.o: generico.c generico.h
	gcc -o generico.o generico.c -c $(FLAGS)

quadrilatero.o: quadrilatero.c quadrilatero.h
	gcc -o quadrilatero.o quadrilatero.c -c $(FLAGS)

poligono.o: poligono.c poligono.h
	gcc -o poligono.o poligono.c -c $(FLAGS)

ponto.o: ponto.c ponto.h
	gcc -o ponto.o ponto.c -c $(FLAGS)

circulo.o: circulo.c circulo.h
	gcc -o circulo.o circulo.c -c $(FLAGS)

retangulo.o: retangulo.c retangulo.h
	gcc -o retangulo.o retangulo.c -c $(FLAGS)

quadra.o: quadra.c quadra.h
	gcc -o quadra.o quadra.c -c $(FLAGS)
	
texto.o: texto.c texto.h
	gcc -o texto.o texto.c -c $(FLAGS)

linha.o: linha.c linha.h
	gcc -o linha.o linha.c -c $(FLAGS)

args.o: args.c args.h
	gcc -o args.o args.c -c $(FLAGS)

QuadTree.o: QuadTree.c QuadTree.h
	gcc -o QuadTree.o QuadTree.c -c $(FLAGS)

hashTable.o: hashTable.c hashTable.h
	gcc -o hashTable.o hashTable.c -c $(FLAGS)

pessoa.o: pessoa.c pessoa.h
	gcc -o pessoa.o pessoa.c -c $(FLAGS)

morador.o: morador.c morador.h
	gcc -o morador.o morador.c -c $(FLAGS)

estabelecimento.o: estabelecimento.c estabelecimento.h
	gcc -o estabelecimento.o estabelecimento.c -c $(FLAGS)

chaveXvalor.o: chaveXvalor.c chaveXvalor.h
	gcc -o chaveXvalor.o chaveXvalor.c -c $(FLAGS)

grafo.o: grafo.c grafo.h
	gcc -o grafo.o grafo.c -c $(FLAGS)

rua.o: rua.c rua.h
	gcc -o rua.o rua.c -c $(FLAGS)

clean:
	rm -rf *.o *~ siguel