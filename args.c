#include "args.h"

typedef struct dire{
    char *geo;
    char *ec;
    char *pm;
    char *svg;
    char *qry;
    char *svgQry;
    char *txtQry;
}diretorios;

int countLen(char *str){ // RETORNA O NUMERO DE CARACTERES NO NOME DO ARQUIVO SEM CONTAR COM A EXTENSAO
    int len = strlen(str) - 5;
    int count = 0;
    for(len;len>=0;len--){
        if(str[len]=='/') break;
        count++;
    }
    return count;
}

char *ajeitaBase(char *dirEntrada){ // RETORNA A MESMA STRING RECEBIDA COM / NO FINAL 
    int len = strlen(dirEntrada);
    char *aux;
    if(dirEntrada[len-1]!='/'){
        aux = malloc(sizeof(char)*len+2);
        strcpy(aux,dirEntrada);
        aux[len]='/';
        aux[len+1]='\0';
    }
    else{
        aux = malloc(sizeof(char)*len+1);
        strcpy(aux,dirEntrada);
    }
    return aux;
}

char *getFileName(char *arq, int ext){ // RETORNA UMA STRING QUE POSSUI O NOME DO ARQUIVO DA STRING RECEBIDA (ext=1 retorna nome+extensao ext=0 retorna apenas nome)
    int len = countLen(arq);
    int start = strlen(arq) - len - 4;
    char *aux;
    if(ext==1){
        aux = malloc(sizeof(char)*len+5);
        strcpy(aux,arq+start);
    }
    else if(ext==0){
        aux = malloc(sizeof(char)*len+2);
        strncpy(aux,arq+start,len);
        aux[len]='-';
        aux[len+1]='\0';
    }
    return aux;
}

void trocaExt(char *arq, char type){ // TROCA A EXTENSAO DO ARQUIVO PARA .SVG OU .TXT
    int len = strlen(arq);
    switch(type){
        case 's':
            arq[len-4]='.';
            arq[len-3]='s';
            arq[len-2]='v';
            arq[len-1]='g';
            break;
        case 't':
            arq[len-4]='.';
            arq[len-3]='t';
            arq[len-2]='x';
            arq[len-1]='t';
            break;
    }
}

char *getDirEntrada(char *dirEntrada, char *arqGeo){ // RETORNA O DIRETORIO DO ARQUIVO GEO
    char *base = ajeitaBase(dirEntrada);
    char *file;
    if(arqGeo[0]=='.'){
        if(arqGeo[1]=='.'){
             file = malloc(sizeof(char)*strlen(arqGeo)-2);
             strcpy(file,arqGeo+3);
        }else{
            file = malloc(sizeof(char)*strlen(arqGeo)-1);
            strcpy(file,arqGeo+2);
        }
    }
    else if(arqGeo[0]=='/'){
        file = malloc(sizeof(char)*strlen(arqGeo));
        strcpy(file,arqGeo+1);
    }
    else{
        file = malloc(sizeof(char)*strlen(arqGeo)+1);
        strcpy(file,arqGeo);        
    }
    char *str = malloc(sizeof(char)*(strlen(base)+strlen(file))+1);
    strcpy(str,base);
    strcat(str,file);
    free(base);
    free(file);
    return str;
}

char *getDirFile(char *arqGeo, char *dirSaida, char type){ // RETORNA O DIRETORIO DO ARQUIVO SVG OU TXT
    char *aux1 = ajeitaBase(dirSaida);
    char *aux2 = getFileName(arqGeo,1);
    trocaExt(aux2,type);
    char *str = malloc(sizeof(char)*(strlen(aux1)+strlen(aux2))+1);
    strcpy(str,aux1);
    strcat(str,aux2);
    free(aux1);
    free(aux2);
    return str;
}

char *getDirFileQry(char *dirSaida, char *arqGeo, char *arqQry, char type){ // RETORNA O DIRETORIO DO ARQUIVO SVG OU TXT APÓS O ARQUIVO QRY
    char *base = ajeitaBase(dirSaida);
    char *geoFile = getFileName(arqGeo,0);
    char *qryFile = getFileName(arqQry,1);
    char *exitFile = malloc(sizeof(char)*strlen(geoFile)+strlen(qryFile)+1); //ALOCA MEMORIA PARA JUNTAR A PARTE GEO E QRY
    strcpy(exitFile,geoFile);
    strcat(exitFile,qryFile);
    trocaExt(exitFile,type);
    char *str = malloc(sizeof(char)*strlen(base)+strlen(exitFile)+1); // ALOCA MEMORIA PARA JUNTAR A PARTE DIRETORIO E NOME DO ARQUIVO
    strcpy(str,base);
    strcat(str,exitFile);
    free(base);
    free(geoFile);
    free(qryFile);
    free(exitFile);
    return str;
}

Diretorios defineArgs(int argc, char* argv[]){ // DEFINE CADA ARGUMENTO EM SUA RESPECTIVA VARIAVEL
    char *dirEntrada = NULL;
    char *dirSaida = NULL;
    char *arqGeo = NULL;
    char *arqQry = NULL;
    char *arqEC = NULL;
    char *arqPM = NULL;

    diretorios *dir = (diretorios*)malloc(sizeof(diretorios));
    dir->qry = NULL;
    dir->svgQry = NULL;
    dir->txtQry = NULL;
    dir->ec = NULL;
    dir->pm = NULL;
    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-e")==0){
            i++;
            dirEntrada = malloc(sizeof(char)*strlen(argv[i])+1);
            strcpy(dirEntrada,argv[i]);
        }
        else if(strcmp(argv[i],"-f")==0){
            i++;
            arqGeo = malloc(sizeof(char)*strlen(argv[i])+1);
            strcpy(arqGeo,argv[i]);
        }
        else if(strcmp(argv[i],"-q")==0){
            i++;
            arqQry = malloc(sizeof(char)*strlen(argv[i])+1);
            strcpy(arqQry,argv[i]);
        }
        else if(strcmp(argv[i],"-o")==0){
            i++;
            dirSaida = malloc(sizeof(char)*strlen(argv[i])+1);
            strcpy(dirSaida,argv[i]);
        }else if(strcmp(argv[i],"-ec")==0){
            i++;
            arqEC = malloc(sizeof(char)*strlen(argv[i])+1);
            strcpy(arqEC,argv[i]);
        }else if(strcmp(argv[i],"-pm")==0){
            i++;
            arqPM = malloc(sizeof(char)*strlen(argv[i])+1);
            strcpy(arqPM,argv[i]);
        }
    }
    if(dirEntrada==NULL){
        dir->geo = malloc(sizeof(char)*strlen(arqGeo)+1);
        strcpy(dir->geo,arqGeo);
        
        if(arqEC != NULL){
            dir->ec = malloc(sizeof(char)*strlen(arqEC)+1);
            strcpy(dir->ec,arqEC);
        }

        if(arqPM != NULL){
            dir->pm = malloc(sizeof(char)*strlen(arqPM)+1);
            strcpy(dir->pm,arqPM);
        }
    }
    else{
        dir->geo = getDirEntrada(dirEntrada,arqGeo);
        if(arqEC != NULL) dir->ec = getDirEntrada(dirEntrada,arqEC);

        if(arqPM != NULL) dir->pm = getDirEntrada(dirEntrada,arqPM);
    }
    dir->svg = getDirFile(arqGeo,dirSaida,'s');
    if(arqQry!=NULL){
        if(dirEntrada==NULL){
            dir->qry = malloc(sizeof(char)*strlen(arqQry)+1);
            strcpy(dir->qry,arqQry);
        }
        else{
            dir->qry = getDirEntrada(dirEntrada,arqQry);
        }
        dir->svgQry = getDirFileQry(dirSaida,arqGeo,arqQry,'s');
        dir->txtQry = getDirFileQry(dirSaida,arqGeo,arqQry,'t');
        free(arqQry);
    }

    if(arqEC != NULL) free(arqEC);
    if(arqPM != NULL) free(arqPM);

    free(dirEntrada);
    free(dirSaida);
    free(arqGeo);
    return dir;
}

void deleteDir(Diretorios d){ // DESALOCA A MEMÓRIA DOS DIRETORIOS DE ENTRADA E SAIDA
    diretorios *dir = (diretorios*) d;
    free(dir->geo);
    free(dir->svg);
    if(dir->qry!=NULL){
        free(dir->svgQry);
        free(dir->txtQry);
        free(dir->qry);
    }
    if(dir->ec != NULL) free(dir->ec);
    if(dir->pm != NULL) free(dir->pm);
    free(dir);
}

char *getPathGeo(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->geo;
}

char *getPathQry(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->qry;
}

char *getPathSvg(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->svg;
}

char *getPathSvgQry(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->svgQry;
}

char *getPathTxtQry(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->txtQry;
}

char *getPathEC(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->ec;
}

char *getPathPM(Diretorios d){
    diretorios *dir = (diretorios*) d;
    return dir->pm;
}

char *getPathSufix(Diretorios d, char *sufixo){
    diretorios *dir = (diretorios*) d;
    int tam = strlen(dir->svgQry) + strlen(sufixo) + 2;
    char *pathSufix = (char *)malloc(sizeof(char) * tam); //svgQry -> geo-qry.svg   pathSufix -> geo-qry-sufix.svg
    
    for(int i=0; i<tam; i++){
        pathSufix[i] = '\0';
    }

    for(int i=0; i<strlen(dir->svgQry)-4; i++){
        pathSufix[i] = dir->svgQry[i];
    }

    pathSufix[strlen(dir->svgQry)-4] = '-';
    strcat(pathSufix,sufixo);
    strcat(pathSufix,".svg");
    
    return pathSufix;
}