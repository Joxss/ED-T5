#include "pessoa.h"

typedef struct{
    char cpf[15];
    char nome[30];
    char sobrenome[30];
    char sexo;
    char dataNascimento[11];
}pessoaTad;

Pessoa createPessoa(char *cpf, char *nome, char *sobrenome, char sexo, char *nascimento){
    pessoaTad *pessoa = malloc(sizeof(pessoaTad));
    strcpy(pessoa->cpf,cpf);
    strcpy(pessoa->nome,nome);
    strcpy(pessoa->sobrenome,sobrenome);
    strcpy(pessoa->dataNascimento,nascimento);
    pessoa->sexo = sexo;

    return pessoa;
}

char * pessoaGetCpf(Pessoa p){
    pessoaTad *pessoa = (pessoaTad*)p;
    return pessoa->cpf;
}

char * pessoaGetNome(Pessoa p){
    pessoaTad *pessoa = (pessoaTad*)p;
    return pessoa->nome;
}

char * pessoaGetSobrenome(Pessoa p){
    pessoaTad *pessoa = (pessoaTad*)p;
    return pessoa->sobrenome;
}

char pessoaGetSexo(Pessoa p){
    pessoaTad *pessoa = (pessoaTad*)p;
    return pessoa->sexo;
}

char * pessoaGetNascimento(Pessoa p){
    pessoaTad *pessoa = (pessoaTad*)p;
    return pessoa->dataNascimento;
}

void freePessoa(Pessoa p){
    free(p);
}