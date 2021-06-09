#include "ler_file.h"
#include "pessoa.h"
#include "morador.h"
#include "rua.h"

void _setDDShadow(QuadTree quadras, QuadNode densidade){
    if(densidade == NULL) return;

    Generic elementoDensidade = QtGetInfo(NULL,densidade);
    if(elementoDensidade== NULL){
        printf("deu erro\n");
    }
    Quad dens = genericGetValores(elementoDensidade);

    double x = quadGetX(dens), y = quadGetY(dens), w = quadGetW(dens), h = quadGetH(dens), n = quadGetN(dens);

    List quadrasInside = QtNosDentroRetangulo(quadras,x,y,x+w,y+h);

    Node node = listGetFirst(quadrasInside);
    while(node != NULL){
        Generic elementoQuadra = nodeGetData(node);
        Quadra quadra = genericGetValores(elementoQuadra);

        if(n >= 10 && n <= 500) quadraSetCorSombra(quadra,"shadow1");
        else if(n > 500 && n <= 1500) quadraSetCorSombra(quadra,"shadow2");
        else if(n > 1500 && n <= 3000) quadraSetCorSombra(quadra,"shadow3");
        else if(n > 3000 && n <= 4500) quadraSetCorSombra(quadra,"shadow4");
        else if(n > 4500 && n <= 6000) quadraSetCorSombra(quadra,"shadow5");
        else if(n > 6000) quadraSetCorSombra(quadra,"shadow6");


        node = nodeGetNext(node);
    }
    
    freeLista2(quadrasInside);

    _setDDShadow(quadras,QtGetNW(densidade));
    _setDDShadow(quadras,QtGetNE(densidade));
    _setDDShadow(quadras,QtGetSW(densidade));
    _setDDShadow(quadras,QtGetSE(densidade));
}

void leGeo(QuadTree * trees, Htable cepXQuadra,char input[]){
    double r, x, y, h, w, n;
    int i=1000, nq=1000, nh=1000, ns=1000, nr=1000;
    char comando[10];
    char id[50];
    char texto[200];
    char cfill[20], cstrk[20];
    char swQ[20]="1px", cfillQ[20]="red", cstrkQ[20]="red";
    char swH[20]="1px", cfillH[20]="black", cstrkH[20]="black";
    char swR[20]="1px", cfillR[20]="green", cstrkR[20]="green";
    char swS[20]="1px", cfillS[20]="green", cstrkS[20]="green";

    char swCirc[20]="1px", swRect[20]="1px";

    List circList = createLista();
    List rectList = createLista();
    List textList = createLista();
    List quadraList = createLista();
    List hidranteList = createLista();
    List semaforoList = createLista();
    List radioList = createLista();
    List postoList = createLista();
    List densidadeList = createLista();

    FILE *geo = fopen(input,"r");
    while(!feof(geo)){
        fscanf(geo,"%s",comando);
        
        if(strcmp("nx",comando)==0){
            fscanf(geo,"%d %d %d %d %d\n",&i,&nq,&nh,&ns,&nr);
        } else if (strcmp("c",comando)==0){
            fscanf(geo,"%s %lf %lf %lf %s %s\n",id,&r,&x,&y,cstrk,cfill);
            
            Circ circ = createCircle(id,x,y,r,swCirc,cstrk,cfill);
            Ponto p = circGetPonto(circ);
            Generic elemento = createGeneric("circulo",circ,freeCircle, circGetPonto);


            listInsert(circList,elemento);      

        } else if (strcmp("r",comando)==0){
            fscanf(geo,"%s %lf %lf %lf %lf %s %s\n",id,&w,&h,&x,&y,cstrk,cfill);

            Rect rect = createRect(id,x,y,w,h,swRect,cstrk,cfill);
            Ponto p = rectGetPonto(rect);
            Generic elemento = createGeneric("retangulo",rect,freeRect, rectGetPonto);

            listInsert(rectList,elemento);
        } else if (strcmp("t",comando)==0){
            fscanf(geo,"%s %lf %lf %s %s\n",id,&x,&y,cstrk,cfill);
            fgets(texto,200,geo); // ler o resto da linha
            texto[strlen(texto)]='\0'; //Substituir o \n do final da linha pelo \0

            Text text = createText(id,x,y,cstrk,cfill,texto); //Substitui o 'espaço' entre o ultimo argumento e o começo do texto
            Ponto p = textGetPonto(text);
            Generic elemento = createGeneric("texto",text,freeText, textGetPonto);

            listInsert(textList,elemento);
        } else if(strcmp("q",comando)==0){ // QUADRA
            fscanf(geo,"%s %lf %lf %lf %lf\n",id,&x,&y,&w,&h);
            
            Quadra quadra = createQuadra(id,x,y,w,h,swQ,cstrkQ,cfillQ);
            Generic elemento = createGeneric("quadra",quadra,freeQuadra,quadraGetPonto);

            listInsert(quadraList, elemento);

            hashInsert(cepXQuadra,id,quadra);
        } else if(strcmp("h",comando)==0){ // HIDRANTE
            fscanf(geo,"%s %lf %lf\n",id,&x,&y);

            Circ hidrante = createCircle(id,x,y,2,swH,cstrkH,cfillH);
            Ponto p = circGetPonto(hidrante);
            Generic elemento = createGeneric("circulo",hidrante,freeCircle, circGetPonto);

            listInsert(hidranteList,elemento);
        } else if(strcmp("s",comando)==0){ // SEMAFORO
            fscanf(geo,"%s %lf %lf\n",id,&x,&y);

            Circ semaforo = createCircle(id,x,y,2,swS,cstrkS,cfillS);
            Ponto p = circGetPonto(semaforo);
            Generic elemento = createGeneric("circulo",semaforo,freeCircle, circGetPonto);

            listInsert(semaforoList,elemento);
        } else if(strcmp("rb",comando)==0){ // RADIO-BASES
            fscanf(geo,"%s %lf %lf\n",id,&x,&y);

            Circ radio = createCircle(id,x,y,2,swR,cstrkR,cfillR);
            Ponto p = circGetPonto(radio);
            Generic elemento = createGeneric("circulo",radio,freeCircle, circGetPonto); 

            listInsert(radioList,elemento);
        } else if(strcmp("cq",comando)==0){ // QUADRAS: CORES E BORDA
            fscanf(geo,"%s %s %s\n", swQ,cfillQ,cstrkQ);
        } else if(strcmp("ch",comando)==0){ // HIDRANTES: CORES E BORDA
            fscanf(geo,"%s %s %s\n", swH,cfillH,cstrkH);
        } else if(strcmp("cr",comando)==0){ // RADIO-BASES: CORES E BORDA
            fscanf(geo,"%s %s %s\n", swR,cfillR,cstrkR);
        } else if(strcmp("cs",comando)==0){ // SEMAFOROS: CORES E BORDA
            fscanf(geo,"%s %s %sc", swS,cfillS,cstrkS);
        } else if(strcmp("sw",comando)==0){ // CIRCULOS E RETANGULOS: BORDA
            fscanf(geo,"%s %s\n", swCirc,swRect);
        } else if(strcmp("ps",comando)==0){ 
            fscanf(geo, "%lf %lf\n", &x, &y);

            Ponto point = createPoint(x,y);
            Generic elemento = createGeneric("ponto", point,freePonto, pontoGetPonto);

            listInsert(postoList,elemento);
        } else if(strcmp("dd",comando)==0){
            fscanf(geo, "%lf %lf %lf %lf %lf\n", &x, &y,&w,&h, &n);
            // printf("ENTROU NO DD\n");
            Quad q = createQuad(x,y,w,h,n);
            Ponto p = quadGetPonto(q);
            Generic elemento = createGeneric("densidade", q, freeQuad, quadGetPonto);

            listInsert(densidadeList,elemento);
        }
    }

    QtOrdenarInsercao(trees[0], circList);
    QtOrdenarInsercao(trees[1], rectList);
    QtOrdenarInsercao(trees[2], textList);
    QtOrdenarInsercao(trees[3], quadraList);
    QtOrdenarInsercao(trees[4], hidranteList);
    QtOrdenarInsercao(trees[5], semaforoList);
    QtOrdenarInsercao(trees[6], radioList);
    QtOrdenarInsercao(trees[7], postoList);
    QtOrdenarInsercao(trees[8], densidadeList);    

    freeLista2(circList);
    freeLista2(rectList);
    freeLista2(textList);
    freeLista2(quadraList);
    freeLista2(hidranteList);
    freeLista2(semaforoList);
    freeLista2(radioList);
    freeLista2(postoList);
    freeLista2(densidadeList);

    _setDDShadow(trees[3],QtGetRoot(trees[8]));

    fclose(geo);
}

void _setRegistrador(Ponto registradores[], char string[], Ponto coord){
    if(!strcmp(string,"R0")){
        if(registradores[0] != NULL)
            freePonto(registradores[0]);
        registradores[0] = coord;
    }else if(!strcmp(string,"R1")){
        if(registradores[1] != NULL)
            freePonto(registradores[1]);
        registradores[1] = coord;
    }else if(!strcmp(string,"R2")){
        if(registradores[2] != NULL)
            freePonto(registradores[2]);
        registradores[2] = coord;
    }else if(!strcmp(string,"R3")){
        if(registradores[3] != NULL)
            freePonto(registradores[3]);
        registradores[3] = coord;
    }else if(!strcmp(string,"R4")){
        if(registradores[4] != NULL)
            freePonto(registradores[4]);
        registradores[4] = coord;
    }else if(!strcmp(string,"R5")){
        if(registradores[5] != NULL)
            freePonto(registradores[5]);
        registradores[5] = coord;
    }else if(!strcmp(string,"R6")){
        if(registradores[6] != NULL)
            freePonto(registradores[6]);
        registradores[6] = coord;
    }else if(!strcmp(string,"R7")){
        if(registradores[7] != NULL)
            freePonto(registradores[7]);
        registradores[7] = coord;
    }else if(!strcmp(string,"R8")){
        if(registradores[8] != NULL)
            freePonto(registradores[8]);
        registradores[8] = coord;
    }else if(!strcmp(string,"R9")){
        if(registradores[9] != NULL)
            freePonto(registradores[9]);
        registradores[9] = coord;
    }else if(!strcmp(string,"R10")){
        if(registradores[10] != NULL)
            freePonto(registradores[10]);
        registradores[10] = coord;
    }
}

void _freeRegistradores(Ponto registradores[]){
    for(int i=0; i<11; i++){
        if(registradores[i] != NULL){
            printf("Registrador R%d: %lf %lf\n",i,pontoGetX(registradores[i]),pontoGetY(registradores[i]));
            freePonto(registradores[i]);
        }
    }
}

void leQry(Grafo ruas, QuadTree *trees,List qryFigures, Htable cpfXpessoa, Htable tipoXdescricao, Htable cpfXcep, Htable cepXquadra, Diretorios dir){
    
    
    int id1, id2;
    int n;
    double x, y, r, w, h, num;
    char corBorda[20], corPreench[20];
    char id[50], opcional[20];
    char comando[10];
    char cpf[15], cnpj[17], compl[50];
    char sufix[100];
    char face;

    Ponto registradores[11];
    char registrador[10];
     
    for(int i=0;i<11;i++)
        registradores[i] = NULL;

    FILE *txt = fopen(getPathTxtQry(dir),"w");
    FILE *qry = fopen(getPathQry(dir),"r");
    
    while(!feof(qry)){
        fscanf(qry,"%s",comando);

        if(!strcmp(comando,"o?")){
            fscanf(qry, "%d %d\n",&id1,&id2);
            fprintf(txt, "%s %d %d\n",comando,id1,id2); //Grava o comando no txt
            oQry(txt,trees[0],trees[1],qryFigures, id1, id2);

        }else if(!strcmp(comando,"i?")){
            fscanf(qry, "%d %lf %lf\n",&id1,&x,&y);
            fprintf(txt, "%s %d %lf %lf\n",comando,id1,x,y); //Grava o comando no txt
            iQry(txt,trees[0],trees[1],qryFigures,id1,x,y);
            
        }else if(!strcmp(comando, "pnt")){
            fscanf(qry,"%d %s %s\n",&id1,corBorda, corPreench);
            fprintf(txt, "%s %d %s %s\n",comando,id1,corBorda,corPreench); //Grava o comando no txt
            qryPnt(txt, trees[0], trees[1], trees[2], id1, corBorda, corPreench);

        }else if(!strcmp(comando, "pnt*")){
            fscanf(qry,"%d %d %s %s\n",&id1, &id2, corBorda, corPreench);
            fprintf(txt, "%s %d %d %s %s\n",comando,id1,id2,corBorda,corPreench); //Grava o comando no txt
            qryPntAll(txt, trees[0], trees[1], trees[2], id1, id2, corBorda, corPreench);

        }else if(!strcmp(comando, "delf")){
            fscanf(qry,"%d\n",&id1);
            fprintf(txt, "%s %d\n",comando,id1); //Grava o comando no txt
            qryDelf(txt, trees[0], trees[1], trees[2], id1);

        }else if(!strcmp(comando, "delf*")){
            fscanf(qry,"%d %d\n",&id1, &id2);
            fprintf(txt, "%s %d %d\n",comando,id1,id2); //Grava o comando no txt
            qryDelfAll(txt, trees[0], trees[1], trees[2], id1, id2);

        }
        else if(!strcmp(comando, "dq")){
            fscanf(qry,"%s",opcional);
            
            if(!strcmp(opcional,"#")){
                fscanf(qry,"%s %lf\n",id,&r);
                
                fprintf(txt, "%s %s %s %lf\n",comando,opcional,id,r); //Grava o comando no txt
                qryDq(txt,cepXquadra,trees[3],trees[4],trees[5],trees[6],qryFigures,id,r,1);
            }else{
                fscanf(qry,"%lf\n",&r);

                fprintf(txt,"%s %s %lf\n",comando,opcional,r); //Grava o comando no txt
                qryDq(txt,cepXquadra,trees[3],trees[4],trees[5],trees[6],qryFigures,opcional,r,0);
            }
        }else if(!strcmp(comando, "del")){
            fscanf(qry,"%s\n", id);
            fprintf(txt, "%s %s\n",comando,id); //Grava o comando no txt
            qryDel(txt, cepXquadra, trees[3], trees[4], trees[5], trees[6], qryFigures, id);
        }else if(!strcmp(comando, "cbq")){
            fscanf(qry,"%lf %lf %lf %s\n", &x, &y, &r, corBorda);
            fprintf(txt, "%s %lf %lf %lf %s\n",comando,x, y, r, corBorda); //Grava o comando no txt
            qryCbq(txt,trees[3],x,y,r,corBorda,qryFigures);
        }else if(!strcmp(comando, "crd?")){
            fscanf(qry,"%s\n", id);
            fprintf(txt, "%s %s\n",comando,id); //Grava o comando no txt
            qryCrd(txt, trees[3], trees[4], trees[5], trees[6], id);
        }else if(!strcmp(comando, "car")){
            fscanf(qry,"%lf %lf %lf %lf\n", &x,&y,&w,&h);
            fprintf(txt, "%s %lf %lf %lf %lf\n",comando,x,y,w,h); //Grava o comando no txt
            qryCar(txt,trees[3],qryFigures,x,y,w,h);
        }
       //************ T3 ************//
        else if(!strcmp(comando,"cv")){
            fscanf(qry,"%d %s %c %lf\n", &n, id, &face, &num);
            fprintf(txt, "%s %d %s %c %lf\n",comando,n,id,face,num); //Grava o comando no txt
            qryCv(trees[9], cepXquadra, n, id, face, num);
        }
        else if(!strcmp(comando,"ci")){
            fscanf(qry,"%lf %lf %lf\n", &x, &y, &r);
            fprintf(txt, "%s %lf %lf %lf\n",comando, x, y, r); //Grava o comando no txt
            qryCi(txt, trees[7], trees[9], trees[8], qryFigures, x, y, r);
        }
        else if(!strcmp(comando, "soc")){
            fscanf(qry,"%d %s %c %lf\n", &n, id, &face, &num);
            fprintf(txt, "%s %d %s %c %lf\n",comando,n,id,face,num); //Grava o comando no txt
            
            qrySoc(txt, trees[7], cepXquadra, qryFigures, n, id, face, num);
        }
        //************ T4 ************//
        else if(!strcmp(comando,"m?")){
            fscanf(qry,"%s\n", id);
            fprintf(txt,"%s %s\n",comando,id); //Grava o comando no txt

            qryM(txt,cpfXpessoa,cepXquadra,id);
        }
        else if(!strcmp(comando,"dm?")){
            fscanf(qry,"%s\n", cpf);
            fprintf(txt,"%s %s\n",comando,cpf); //Grava o comando no txt

            qryDm(txt,qryFigures,trees[10],cpfXpessoa,cpf);
        }
        else if(!strcmp(comando,"de?")){
            fscanf(qry,"%s\n", cnpj);
            fprintf(txt,"%s %s\n",comando,cnpj); //Grava o comando no txt

            qryDe(txt,trees[11],cpfXpessoa,cnpj);
        }
        else if(!strcmp(comando,"mud")){
            //cpf cep face num compl
            fscanf(qry,"%s %s %c %d %s\n", cpf, id, &face, &n, compl);
            fprintf(txt,"%s %s %s %c %d %s\n", comando, cpf, id, face, n, compl); //Grava o comando no txt

            qryMud(txt, trees[10], cepXquadra, cpfXpessoa, cpfXcep, qryFigures, cpf, id, face, n, compl);
        }
        else if(!strcmp(comando,"eplg?")){
            fscanf(qry, "%s %lf %lf %lf %lf\n", opcional,&x,&y,&w,&h);
            fprintf(txt,"%s %lf %lf %lf %lf\n",opcional,x,y,w,h);

            if(!strcmp(opcional,"*")) qryEplg(txt,trees[11],tipoXdescricao,cpfXpessoa,qryFigures,x,y,w,h,NULL);
            else qryEplg(txt,trees[11],tipoXdescricao,cpfXpessoa,qryFigures,x,y,w,h,opcional);
            
        }
        else if(!strcmp(comando,"dmprbt")){
            fscanf(qry, " %c %s\n", &face, compl); //face=t compl=sufx
            fprintf(txt,"%s %c %s\n", comando, face, compl);
            char *pathSufix = getPathSufix(dir,compl);
            
            if(face == 'q') qryDmprbt(trees[3],pathSufix);
            else if(face == 'h') qryDmprbt(trees[4],pathSufix);
            else if(face == 's') qryDmprbt(trees[5],pathSufix);
            else if(face == 't') qryDmprbt(trees[6],pathSufix);

            free(pathSufix);
        }
        else if(!strcmp(comando,"catac")){
            fscanf(qry, "%lf %lf %lf\n", &x, &y, &r); 
            fprintf(txt,"%s %lf %lf %lf\n", comando, x, y, r);

            //chamar-func
            qryCatac(txt, trees[3], trees[4], trees[5], trees[6], trees[10], trees[11], qryFigures, x, y, r);

        }
        //************ T5 ************//
        else if(!strcmp(comando,"@m?")){
            fscanf(qry,"%s %s",registrador,cpf);
            QuadNode nodeMorador = QtGetById(trees[10],cpf);
            if(nodeMorador == NULL) continue;
            Ponto p = genericGetPonto(QtGetInfo(trees[10],nodeMorador));
            Ponto copia = createPoint(pontoGetX(p),pontoGetY(p));
            _setRegistrador(registradores,registrador,copia);
        }
        else if(!strcmp(comando,"@e?")){
            fscanf(qry,"%s %s %c %d",registrador,id,&face,&n);
            Quadra quadra = hashGetKey(cepXquadra,id);
            if(quadra == NULL) continue;
            Ponto p = quadraGetEndereco(quadra,face,n);
            _setRegistrador(registradores,registrador,p);
        }
        else if(!strcmp(comando,"@g?")){
            fscanf(qry,"%s %s",registrador,id);
            QuadNode nodeEquipamento = QtGetById(trees[4],id);
            if(nodeEquipamento == NULL) nodeEquipamento = QtGetById(trees[5],id);
            if(nodeEquipamento == NULL) nodeEquipamento = QtGetById(trees[6],id);
            if(nodeEquipamento == NULL) nodeEquipamento = QtGetById(trees[7],id);
            if(nodeEquipamento == NULL) continue;
            Ponto p = genericGetPonto(QtGetInfo(NULL,nodeEquipamento));
            Ponto copia = createPoint(pontoGetX(p),pontoGetY(p));
            _setRegistrador(registradores,registrador,copia);
        }
        else if(!strcmp(comando,"@xy")){
            fscanf(qry,"%s %lf %lf",registrador,&x,&y);
            Ponto p = createPoint(x,y);
            _setRegistrador(registradores,registrador,p);
        }
        else if(!strcmp(comando,"ccv")){
            fscanf(qry,"%s",sufix);
            char *pathSufix = getPathSufix(dir,sufix);
            qryCCV(trees,ruas, pathSufix);
            free(pathSufix);
        }
    }
    
    _freeRegistradores(registradores);

    fclose(txt);
    fclose(qry);
}

void leEc(QuadTree quadras, QuadTree estabelecimentos, Htable tipoXdescricao, char input[]){
    char comando[10];     

    char codt[10], descricao[100];
    char cnpj[17], cpf[15], cep[30], nome[50];
    int num;
    char face;

    FILE *ec = fopen(input,"r");
    while(!feof(ec)){
        fscanf(ec,"%s",comando);
        
        if(strcmp("t",comando)==0){
            fscanf(ec,"%s %s\n",codt,descricao);

            char *valor = malloc(sizeof(char)*strlen(descricao)+1);
            strcpy(valor,descricao);

            hashInsert(tipoXdescricao,codt,valor);
        }else if(strcmp("e",comando)==0){
            fscanf(ec,"%s %s %s %s %c %d %s\n", cnpj, cpf, codt, cep, &face, &num, nome);
            char *desc = hashGetKey(tipoXdescricao, codt); // PEGA A DESCRIÇÃO
            if(desc == NULL) continue;

            QuadNode node = QtGetById(quadras,cep); // PEGA A QUADRA
            if(node != NULL){
                Generic g = QtGetInfo(quadras,node);
                Quadra quadra = genericGetValores(g);

                Estabelecimento est = createEstabelecimento(cnpj,cpf,desc,quadra, face, num,nome);
                Ponto p = estabelecimentoGetCoord(est);
                Generic elemento = createGeneric("ec",est,freeEstabelecimento, estabelecimentoGetCoord);
                QtInsert(estabelecimentos,p,elemento);
            }
        }
    }
    fclose(ec);
}

void lePm(QuadTree quadras, QuadTree moradores, Htable cpfXpessoa, Htable cpfXcep, char input[]){
    char comando[10];     

    char cpf[15], nome[30], sobrenome[30], nasc[11];
    char cep[30], compl[50];
    int num;
    char sexo, face;

    FILE *pm = fopen(input,"r");
    while(!feof(pm)){
        fscanf(pm,"%s",comando);
        
        if(strcmp("p",comando)==0){
            fscanf(pm,"%s %s %s %c %s\n",cpf,nome,sobrenome,&sexo,nasc);

            Pessoa pessoa = createPessoa(cpf,nome,sobrenome,sexo,nasc);

            hashInsert(cpfXpessoa,cpf,pessoa);
        }else if(strcmp("m",comando)==0){
            fscanf(pm,"%s %s %c %d %s\n",cpf,cep,&face,&num,compl);
            
            QuadNode node = QtGetById(quadras,cep); // PEGA A QUADRA
            if(node != NULL){

                char *valor = malloc(sizeof(char)*strlen(cep)+1);
                strcpy(valor,cep);

                hashInsert(cpfXcep,cpf,valor);

                QuadNode node = QtGetById(quadras,cep);
                Generic g = QtGetInfo(quadras,node);
                Quadra quadra = genericGetValores(g);

                Morador morador = createMorador(cpf, quadra, face, num, compl);
                Ponto p = moradorGetPonto(morador);
                Generic elemento = createGeneric("morador",morador,freeMorador, moradorGetPonto);

                QtInsert(moradores,p,elemento);

                quadraInserirMorador(quadra,elemento);
            }
        }
    }
    
    fclose(pm);
}

void leVia(Htable cepXquadra, QuadTree vertices, Grafo ruas, char input[]){
    char comando[5];
    double x, y, distancia, velocidade;
    char id[100], id1[100], id2[100], cepDireito[50], cepEsquerdo[50], nome[100];

    FILE *via = fopen(input,"r");
    while(!feof(via)){
        fscanf(via,"%s",comando);

        if(strcmp("v",comando) == 0){
            fscanf(via,"%s %lf %lf",id,&x,&y);
            Ponto p = createPoint(x,y);
            Vertice vertice = grafoInsereVertice(ruas,id,p);
            QtInsert(vertices,p,vertice);
        }else if(strcmp("e",comando) == 0){
            fscanf(via,"%s %s %s %s %lf %lf %s",id1,id2,cepDireito,cepEsquerdo,&distancia,&velocidade,nome);
            Quadra quadraDireita = hashGetKey(cepXquadra,cepDireito);
            Quadra quadraEsquerda = hashGetKey(cepXquadra,cepEsquerdo);
            Rua r = createRua(nome,quadraDireita,quadraEsquerda,distancia,velocidade);
            grafoInsereAresta(ruas,id1,id2,r);
        }
    }
    fclose(via);
}

int getQtdVerticesVia(char input[]){
    FILE *via = fopen(input,"r");
    int contador=0;
    char comando[5];
    double x, y, distancia, velocidade;
    char id[100], id1[100], id2[100], cepDireito[50], cepEsquerdo[50], nome[100];
    while(!feof(via)){
        fscanf(via,"%s",comando);

        if(strcmp("v",comando) == 0){
            fscanf(via,"%s %lf %lf",id,&x,&y);
            contador++;
        }else if(strcmp("e",comando) == 0){
            fscanf(via,"%s %s %s %s %lf %lf %s",id1,id2,cepDireito,cepEsquerdo,&distancia,&velocidade,nome);
        }
    }
    fclose(via);
    return contador;
}
//