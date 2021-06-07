#include "convexHull.h"

static Ponto p0;

void swap2(void* v1, void* v2, int size){ 
    char buffer[size]; 

    memcpy(buffer, v1, size); 
    memcpy(v1, v2, size); 
    memcpy(v2, buffer, size); 
} 
  
void quickSort(void* vetor, int type_size, int left, int right, int (*comp)(void*, void*)){ 
    void *vt, *v3; 
    int i, last, mid = (left + right) / 2; 
    if (left >= right) 
        return;

    void* vl = (char*)(vetor + (left * type_size)); 
    void* vr = (char*)(vetor + (mid * type_size)); 
    swap2(vl, vr, type_size); 
    last = left; 
    for (i = left + 1; i <= right; i++) { 

        vt = (char*)(vetor + (i * type_size)); 
        if ((*comp)(vl, vt) > 0) { 
            ++last; 
            v3 = (char*)(vetor + (last * type_size)); 
            swap2(vt, v3, type_size); 
        } 
    } 
    v3 = (char*)(vetor + (last * type_size)); 
    swap2(vl, v3, type_size); 
    quickSort(vetor, type_size, left, last - 1, comp); 
    quickSort(vetor, type_size, last + 1, right, comp); 
} 

void swap(Generic *a, Generic *b) { 
    Generic t = *a; 
    *a = *b; 
    *b = t; 
}

Generic *_listToArrayGeneric(List l, int n){
    int i=0;
    Generic *arr = (Generic*)malloc(sizeof(Generic)*n);
    Node node = listGetFirst(l);
    
    while(node != NULL){
        arr[i] = nodeGetData(node);
        //printf("TIPO: %s x=%lf y=%lf\n",genericGetTipo(arr[i]),pontoGetX(genericGetPonto(arr[i])),pontoGetY(genericGetPonto(arr[i])));
        i++;
        node = nodeGetNext(node);
    }
    return arr;
}

Ponto *_listToArrayPonto(List l, int n){
    int i=0;
    Ponto *arr = (Ponto*)malloc(sizeof(Ponto)*n);
    Node node = listGetFirst(l);
    
    while(node != NULL){
        Generic elemento = nodeGetData(node);
        if(!strcmp(genericGetTipo(elemento),"cv")){
            Quad temp = genericGetValores(elemento);
            Ponto aux = createPoint(quadGetXc(temp), quadGetYc(temp));
            arr[i] = aux;
        }else{
            Ponto temp = genericGetValores(elemento);
            Ponto aux = createPoint(pontoGetX(temp), pontoGetY(temp));
            arr[i] = aux;
        }
        i++;
        node = nodeGetNext(node);
    }
    return arr;
}

void QuadTreeToList(QuadNode qt, List l){
    if(qt == NULL) return;

    Generic elemento = QtGetInfo(NULL,qt);
    if(elemento != NULL) listInsert(l,elemento);

    QuadTreeToList(QtGetNW(qt),l);
    QuadTreeToList(QtGetNE(qt),l);
    QuadTreeToList(QtGetSW(qt),l);
    QuadTreeToList(QtGetSE(qt),l);
}

void freeArray(Ponto arr[], int n){
    for(int i=0;i<n;i++){
        free(arr[i]);
    }
    free(arr);
}

double distSq(Ponto p1, Ponto p2) { 
    return (pontoGetX(p1) - pontoGetX(p2))*(pontoGetX(p1) - pontoGetX(p2)) + (pontoGetY(p1) - pontoGetY(p2))*(pontoGetY(p1) - pontoGetY(p2)); 
}

int orientation(Ponto p, Ponto q, Ponto r) { 
    double val = (pontoGetY(q) - pontoGetY(p)) * (pontoGetX(r) - pontoGetX(q)) - (pontoGetX(q) - pontoGetX(p)) * (pontoGetY(r) - pontoGetY(q)); 
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1 : 2; // horario ou anti-horario
} 

int compare(void *vp1, void *vp2) 
{ 
    Generic *g1 = (Generic*)vp1;
    Generic *g2 = (Generic*)vp2;
    Ponto p1 = genericGetPonto(*g1); 
    Ponto p2 = genericGetPonto(*g2); 
    
    int o = orientation(p0, p1, p2); 
    if (o == 0) 
        return (distSq(p0, p2) >= distSq(p0, p1))? -1 : 1; 
    
    return (o == 2)? -1: 1; 
} 

Generic *convexHull(List l, int *arraySize){
    int n = listLenght(l);
    if(n == 0) return NULL;

    Generic *arr = _listToArrayGeneric(l,n);
    int ymin = pontoGetY(genericGetPonto(arr[0])), min = 0;
    
    for(int i=1;i<n;i++){
        int y = pontoGetY(genericGetPonto(arr[i]));
        if((y<ymin) || (ymin == y && pontoGetX(genericGetPonto(arr[i])) < pontoGetX(genericGetPonto(arr[min])))){
            ymin = pontoGetY(genericGetPonto(arr[i]));
            min = i;
        }
    }

    swap(&arr[0],&arr[min]);
    p0 = genericGetPonto(arr[0]);

    quickSort(arr,sizeof(Generic),1,n-1,compare);
    
    int m = 1;
    for(int i=1; i<n; i++){
        
        while(i < n-1 && orientation(p0,genericGetPonto(arr[i]),genericGetPonto(arr[i+1]))==0){
            i++;            
        }
        arr[m] = arr[i];
        m++;
    }
    *arraySize = n = m;
    if(n<3){
        free(arr);
        return NULL;
    }
    Generic *convex = malloc(sizeof(Generic)*n);
    convex[0] = arr[0];
    convex[1] = arr[1];
    convex[2] = arr[2];

    m = 2;
    for(int i=3; i<n; i++){

        Generic ultimoGen = convex[m];
        Generic penultimoGen = convex[m-1];
    
        Ponto ultimo = genericGetPonto(ultimoGen);
        Ponto penultimo = genericGetPonto(penultimoGen);
        while(orientation(penultimo, ultimo, genericGetPonto(arr[i])) != 2){
            m--;

            ultimoGen = convex[m];
            penultimoGen = convex[m-1];

            ultimo = genericGetPonto(ultimoGen);
            penultimo = genericGetPonto(penultimoGen);
        }
        m++;
        convex[m] = arr[i];
    }

    *arraySize = n = ++m;
    free(arr);
    return convex;
}

int _pointInsPolig(Poligono polig, Ponto p){
    int n = poligGetQtd(polig);
    double *x = poligGetArrayX(polig);
    double *y = poligGetArrayY(polig);
    Ponto p1, p2;
    for(int i=0; i<n; i++){
        if(i==(n-1)){
            p1 = createPoint(x[i],y[i]);
            p2 = createPoint(x[0],y[0]);
            if(orientation(p1,p2,p)!=2){
                free(p1);
                free(p2);
                return 0;
            }
            free(p1);
            free(p2);
        }else{
            p1 = createPoint(x[i],y[i]);
            p2 = createPoint(x[i+1],y[i+1]);
            if(orientation(p1,p2,p)!=2){
                free(p1);
                free(p2);
                return 0;
            }
            free(p1);
            free(p2);
        }
    }
    return 1;
}

int postosSaudeInsPolig(QuadNode postos, Poligono polig){ //QtreeRoot Qtree
    if(postos == NULL) return 0;

    Generic elemento = QtGetInfo(NULL,postos);
    if(elemento != NULL){ // ELEMENTO FOI DELETADO PELA FUNÇÃO QtRemoveNode

        Ponto p = genericGetValores(elemento);

        if(_pointInsPolig(polig,p)){
                return 1;
        }
    }
    
    int result = postosSaudeInsPolig(QtGetNW(postos),polig);
    if(result) return result;

    result = postosSaudeInsPolig(QtGetNE(postos),polig);
    if(result) return result;

    result = postosSaudeInsPolig(QtGetSW(postos),polig);
    if(result) return result;

    result = postosSaudeInsPolig(QtGetSE(postos),polig);
    if(result) return result;
    
    return 0;
}

// FUNÇÕES DA QRY SOC
Ponto * merge(Ponto *arr, int n, int k, Ponto endereco){
    int cont=0;
    
    Ponto *menores = (Ponto*)malloc(sizeof(Ponto)*k);
    Ponto atual[k];

    int index[k];
    double menor, dist;
    int indexMenor;

    for(int i=0;i<k;i++){
        index[i]=0;
    }

    while(cont<k){
        for(int i=0;i<k;i++){
            if(i+k*index[i]<n){
                atual[i] = arr[i+k*index[i]];
            }else{
                atual[i] = NULL;
            }
        }
        
        for(int i=0; i<k; i++){
            if(atual[i] != NULL){
                dist = distSq(endereco,atual[i]);
            }else{
                dist = -1;
            }

            if(i==0){
                menor = dist;
                indexMenor = i;
            }else{
                if(dist < menor && dist >= 0){
                    menor = dist;
                    indexMenor = i;
                }
            }
        }
        
        Ponto p = createPoint(pontoGetX(atual[indexMenor]),pontoGetY(atual[indexMenor]));
        menores[cont] = p;
        index[indexMenor]++;
        cont++;
    }
    return menores;
}

Ponto * shellSortParcial(QuadTree postos, int k, Ponto endereco, int *n){
    Generic elemento;
    Ponto p;

    if(QtGetLenght(postos) == 0){
        *n = 0;
        return NULL;
    }
    
    List postosList = createLista();
    QuadTreeToList(QtGetRoot(postos),postosList);

    Ponto *arr = _listToArrayPonto(postosList,listLenght(postosList));

    if(listLenght(postosList) <= k && listLenght(postosList) != 0){
        *n = listLenght(postosList);
        freeLista2(postosList);
        return arr;
    }

    double distancia;
    int j;
    Ponto value;
    for(int i = k; i < listLenght(postosList); i++) {
        value = arr[i];
        distancia = distSq(arr[i],endereco);
        j = i - k;

        while (j >= 0 && distancia < distSq(arr[j],endereco)) {
            arr[j + k] = arr[j];
            j -= k;
        }
        arr[j + k] = value;
    }

    Ponto *menores = merge(arr, listLenght(postosList),k,endereco);
    freeArray(arr,listLenght(postosList));
    freeLista2(postosList);
    *n = k;
    return menores;
}


