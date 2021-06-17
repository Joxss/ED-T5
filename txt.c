#include "txt.h"

void txtPntQry(FILE *txt, Generic data){
    char *tipo = genericGetTipo(data);
    
    if(!strcmp(tipo,"circulo")){
        Circ circ = genericGetValores(data);
        fprintf(txt,"Círculo x=%lf y=%lf\n",circGetX(circ),circGetY(circ));

    }else if(!strcmp(tipo,"retangulo")){
        Rect rect = genericGetValores(data);
        fprintf(txt,"Retângulo x=%lf y=%lf\n",rectGetX(rect),rectGetY(rect));

    }else if(!strcmp(tipo,"texto")){
        Text text = genericGetValores(data);
        fprintf(txt,"Texto x=%lf y=%lf\n",textGetX(text),textGetY(text));
    }
}

void txtDelfQry(FILE *txt, Generic data){
    char *tipo = genericGetTipo(data);
    char corBorda[20], corPreench[20], borda[20];
    
    if(!strcmp(tipo,"circulo")){
        Circ circ = genericGetValores(data);
        
        strcpy(corBorda,circGetCorBorda(circ));
        strcpy(corPreench,circGetCorPreench(circ));
        strcpy(borda,circGetBorda(circ));
        
        fprintf(txt,"Círculo x=%lf y=%lf r=%lf corb=%s corp=%s borda=%s\n",circGetX(circ),circGetY(circ),circGetR(circ),corBorda,corPreench,borda);

    }else if(!strcmp(tipo,"retangulo")){
        Rect rect = genericGetValores(data);

        strcpy(corBorda,rectGetCorBorda(rect));
        strcpy(corPreench,rectGetCorPreench(rect));
        strcpy(borda,rectGetBorda(rect));
        
        fprintf(txt,"Retângulo x=%lf y=%lf w=%lf h=%lf corb=%s corp=%s borda=%s\n",rectGetX(rect),rectGetY(rect),rectGetW(rect),rectGetH(rect),corBorda,corPreench,borda);

    }else if(!strcmp(tipo,"texto")){
        Text text = genericGetValores(data);
        
        strcpy(corBorda,textGetCorBorda(text));
        strcpy(corPreench,textGetCorPreench(text));

        fprintf(txt,"Texto x=%lf y=%lf corb=%s corp=%s texto=%s\n",textGetX(text),textGetY(text),corBorda,corPreench,textGetTxt(text));
    }
}

void txtInsQry(FILE *txt, Generic data, int boolean){
    char *tipo = genericGetTipo(data);
    char buffer[50];
    
    if(!strcmp(tipo,"circulo")){
        fprintf(txt,"círculo "); 

    }else if(!strcmp(tipo,"retangulo")){
        fprintf(txt,"retângulo "); 
    }

    if(boolean){
        fprintf(txt,"INTERNO\n");
    }else{
        fprintf(txt,"NAO INTERNO\n");
    }
}

void txtOverQry(FILE *txt, Generic data1, Generic data2, int boolean){
    char *tipo1 = genericGetTipo(data1);
    char *tipo2 = genericGetTipo(data2);
    fprintf(txt,"%s: ",genericGetId(data1));
    if(!strcmp(tipo1,"circulo")){
        fprintf(txt,"círculo ");
    }else{
        fprintf(txt,"retângulo ");
    }
    fprintf(txt,"%s: ",genericGetId(data2));
    if(!strcmp(tipo2,"circulo")){
        fprintf(txt,"círculo ");
    }else{
        fprintf(txt,"retângulo ");
    }
    if(boolean){
        fprintf(txt,"SIM\n");
    }else{
        fprintf(txt,"NAO\n");
    }
}

void txtDqQry(FILE *txt, Quadra quadra, Circ equipamento, char tipo[]){
    if(!strcmp(tipo,"hidrante")){
        fprintf(txt,"Hidrante ID=%s x=%lf y=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n",
            circGetId(equipamento),
            circGetX(equipamento),
            circGetY(equipamento),
            circGetCorPreench(equipamento),
            circGetCorBorda(equipamento),
            circGetBorda(equipamento)
        );

    }else if(!strcmp(tipo,"semaforo")){
        fprintf(txt,"Semaforo ID=%s x=%lf y=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n\n",
            circGetId(equipamento),
            circGetX(equipamento),
            circGetY(equipamento),
            circGetCorPreench(equipamento),
            circGetCorBorda(equipamento),
            circGetBorda(equipamento)
        );
        
    }else if(!strcmp(tipo,"radio")){
        fprintf(txt,"Radio-base ID=%s x=%lf y=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n\n",
            circGetId(equipamento),
            circGetX(equipamento),
            circGetY(equipamento),
            circGetCorPreench(equipamento),
            circGetCorBorda(equipamento),
            circGetBorda(equipamento)
        );
    }
}

void txtDetalhes(FILE *txt, void * data, char tipo[]){
    if(!strcmp(tipo,"quadra")){
        fprintf(txt,"Quadra CEP=%s x=%lf y=%lf w=%lf h=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n\n",
            quadraGetCep(data),
            quadraGetX(data),
            quadraGetY(data),
            quadraGetW(data),
            quadraGetH(data),
            quadraGetCorPreench(data),
            quadraGetCorBorda(data),
            quadraGetBorda(data)
        );

    }else if(!strcmp(tipo,"hidrante")){
        fprintf(txt,"Hidrante ID=%s x=%lf y=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n\n",
            circGetId(data),
            circGetX(data),
            circGetY(data),
            circGetCorPreench(data),
            circGetCorBorda(data),
            circGetBorda(data)
        );

    }else if(!strcmp(tipo,"semaforo")){
        fprintf(txt,"Semaforo ID=%s x=%lf y=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n\n",
            circGetId(data),
            circGetX(data),
            circGetY(data),
            circGetCorPreench(data),
            circGetCorBorda(data),
            circGetBorda(data)
        );
        
    }else if(!strcmp(tipo,"radio")){
        fprintf(txt,"Radio-base ID=%s x=%lf y=%lf cor-preenchimento=%s cor-borda=%s expessura-borda=%s\n\n",
            circGetId(data),
            circGetX(data),
            circGetY(data),
            circGetCorPreench(data),
            circGetCorBorda(data),
            circGetBorda(data)
        );
    }
}

void txtCepQuadra(FILE *txt, Quadra quadra){
    fprintf(txt, "Cep: %s\n", quadraGetCep(quadra));
}

void txtCrdQry(FILE *txt, void * data, char tipo[]){
    if(!strcmp(tipo,"quadra")){
        fprintf(txt,"x=%lf y=%lf Quadra\n",quadraGetX(data),quadraGetY(data));
    }else if(!strcmp(tipo,"hidrante")){
        fprintf(txt,"x=%lf y=%lf Hidrante\n",circGetX(data),circGetY(data));
    }else if(!strcmp(tipo,"semaforo")){
        fprintf(txt,"x=%lf y=%lf Semaforo\n",circGetX(data),circGetY(data));
    }else if(!strcmp(tipo,"radio")){
        fprintf(txt,"x=%lf y=%lf Radio-base\n",circGetX(data),circGetY(data));
    }
}

void txtAreaQuadra(FILE *txt, char area[], char cep[]){
    fprintf(txt, "CEP: %s, Area: %s\n", cep, area);
}

void txtAreaTotal(FILE *txt, char area[]){
    fprintf(txt,"Area total: %s\n",area);
}

void txtCoordenadas(FILE *txt, double x, double y){
    fprintf(txt,"x: %lf -- y: %lf\n",x,y);
}

void txtCiQry(FILE *txt, int totalCasos, double area, char incidencia){
    fprintf(txt,"Número de casos: %d -- Area: %lf -- Categoria de incidência: %c\n",totalCasos,area,incidencia);
}

void txtMQry(FILE *txt, Morador morador, Pessoa pessoa){
    fprintf(txt, "Nome completo: %s %s CPF: %s\n", pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetCpf(pessoa));
    fprintf(txt, "Endereço: %s %c %d %s\n\n", moradorGetCep(morador), moradorGetFace(morador), moradorGetNum(morador), moradorGetCompl(morador));
}

void txtDmQry(FILE *txt, Morador morador, Pessoa pessoa){
    fprintf(txt,"CPF: %s Nome: %s Sobrenome: %s Sexo: %c Data de nascimento: %s\n",pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
    fprintf(txt,"Endereço: %s %c %d %s\n\n",moradorGetCep(morador), moradorGetFace(morador), moradorGetNum(morador), moradorGetCompl(morador));
}

void txtDeQry(FILE *txt, Estabelecimento estabelecimento, Pessoa pessoa){
    fprintf(txt,"CNPJ: %s CPF: %s Descrição: %s Nome: %s\n",estabelecimentoGetCnpj(estabelecimento), estabelecimentoGetCpf(estabelecimento), estabelecimentoGetDescricao(estabelecimento), estabelecimentoGetNome(estabelecimento));
    fprintf(txt,"Endereço do estabelecimento: %s %c %d\n",estabelecimentoGetCep(estabelecimento), estabelecimentoGetFace(estabelecimento), estabelecimentoGetNum(estabelecimento));
    fprintf(txt,"Dados do proprietário: CPF: %s Nome: %s Sobrenome: %s Sexo: %c Data de nascimento: %s\n\n",pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
}

void txtMudQry(FILE *txt, Pessoa pessoa, Morador morador, char *cep_A, char face_A, int num_A, char *compl_A){
    fprintf(txt,"Dados do morador: CPF: %s Nome: %s Sobrenome: %s Sexo: %c Data de nascimento: %s\n",pessoaGetCpf(pessoa), pessoaGetNome(pessoa), pessoaGetSobrenome(pessoa), pessoaGetSexo(pessoa), pessoaGetNascimento(pessoa));
    fprintf(txt,"Endereço antigo: %s %c %d %s\n",cep_A, face_A,num_A,compl_A);
    fprintf(txt,"Endereço novo: %s %c %d %s\n\n",moradorGetCep(morador),moradorGetFace(morador),moradorGetNum(morador),moradorGetCompl(morador));
}

void txtEplgQry(FILE *txt, Pessoa pessoa, Estabelecimento estabelecimento){
    fprintf(txt,"Nome estabelecimento: %s - CNPJ: %s - Descrição: %s - Endereço: %s %c %d - Nome proprietario: %s - CPF: %s\n",
    estabelecimentoGetNome(estabelecimento),
    estabelecimentoGetCnpj(estabelecimento),
    estabelecimentoGetDescricao(estabelecimento),
    estabelecimentoGetCep(estabelecimento),
    estabelecimentoGetFace(estabelecimento),
    estabelecimentoGetNum(estabelecimento),
    pessoaGetNome(pessoa),
    pessoaGetCpf(pessoa)
    );
}

void txtCatacQry(FILE *txt, Generic elemento){
   
    if(!strcmp(genericGetTipo(elemento), "quadra")){
        Quadra quadra = genericGetValores(elemento);
        fprintf(txt,"Quadra - Cep: %s, X=%lf, Y=%lf, W=%lf, H=%lf\n", quadraGetCep(quadra), quadraGetX(quadra), quadraGetY(quadra), quadraGetW(quadra), quadraGetH(quadra));
    
    }else if(!strcmp(genericGetTipo(elemento), "circulo")){
        Circ circ = genericGetValores(elemento);
        fprintf(txt,"Equipamento urbano - Id: %s, X=%lf, Y=%lf, R=%lf\n", circGetId(circ), circGetX(circ), circGetY(circ), circGetR(circ));

    }else if(!strcmp(genericGetTipo(elemento), "ec")){
        Estabelecimento est = genericGetValores(elemento);
        fprintf(txt,"Estabelecimento comercial - Nome: %s. Endereço: %s %c %d. CPF: %s, CNPJ: %s. Descrição: %s\n",estabelecimentoGetNome(est), estabelecimentoGetCep(est), estabelecimentoGetFace(est), estabelecimentoGetNum(est), estabelecimentoGetCpf(est), estabelecimentoGetCnpj(est), estabelecimentoGetDescricao(est));
    
    }else if(!strcmp(genericGetTipo(elemento), "morador")){
        Morador morador = genericGetValores(elemento);
        fprintf(txt,"Morador - CPF: %s. Endereço: %s %c %d %s\n", moradorGetCpf(morador), moradorGetCep(morador), moradorGetFace(morador), moradorGetNum(morador),  moradorGetCompl(morador));
    }        
}

// TXT: listar cep e face referente ao trecho
// interditado e o número total de casos de
// coviid naquela face.
void txtBfQry(FILE *txt,Quadra quadra,char face,int qtd){
    fprintf(txt,"CEP: %s, FACE: %c, Quantidade de casos: %d\n",quadraGetCep(quadra),face,qtd);
}


