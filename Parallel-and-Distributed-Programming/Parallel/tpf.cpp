#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <omp.h>
#include <cstdio>
#include <unistd.h>
#include <iomanip>


using namespace std;

string NumberToString (int Number){
    stringstream ss;
    ss << Number;
    return ss.str();
}

struct no{
    short x,y,z;
    bool condicao;
    string caminho;
};

typedef no TipoChave;

struct TipoItem{
    TipoChave chave;
};

struct TipoCelula{
    TipoItem item;
    TipoCelula* prox;
};

struct TipoLista{
    TipoCelula *primeiro, *ultimo;
};

void FLVazia(TipoLista *lista){
    lista->primeiro = new TipoCelula;
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
}

int Vazia(TipoLista lista){return (lista.primeiro == lista.ultimo);}

void Insere(TipoLista *lista, int x,int y,int z,bool condicao, string s){
    lista->ultimo->prox = new TipoCelula;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->item.chave.x = x;
    lista->ultimo->item.chave.y = y;
    lista->ultimo->item.chave.z = z;
    lista->ultimo->item.chave.condicao = condicao;
    //cout<<s<<endl;
    lista->ultimo->item.chave.caminho = s;
    //cout<<lista->ultimo->item.chave.caminho<<endl;
    lista->ultimo->prox = NULL;
}

void Retira(TipoCelula *p, TipoLista *lista, TipoItem *item){
    if(Vazia (*lista) || (p == NULL) || (p->prox == NULL)) return;

    TipoCelula *q = p->prox;
    *item = q->item;

    p->prox = q->prox;

    if(p->prox == NULL)lista->ultimo = p;
    delete q;
}

int logicaPrograma(TipoLista *lista,int xDest, int yDest, int zDest, int pi){
    TipoCelula *aux = lista->primeiro->prox;
    int i = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    string s = "(0,0,0)";
    bool c = false;
    int contador = 0;
    int soma = 0;

    //TipoCelula *aux = lista->primeiro->prox;
    try{
    #pragma omp parallel shared(aux) num_threads(4)
    {
	    while(i<pi){
	    sleep(0.0001);

	        if(((pi == (i+1) && i!=0 && (lista->primeiro->prox != NULL))))break;
		else{
			if(lista->primeiro->prox == NULL || x>xDest || y>yDest || z>zDest){break;}
		}
	        #pragma omp critical
		{	
			#pragma omp nowait atomic
			{
				x = lista->primeiro->prox->item.chave.x;		        
				y = lista->primeiro->prox->item.chave.y;
		        	z = lista->primeiro->prox->item.chave.z;
		        	c = lista->primeiro->prox->item.chave.condicao;
				s = lista->primeiro->prox->item.chave.caminho;
				//
			}

			//cout<<endl;
			//cout<<"("<<x<<","<<y<<","<<z<<")"<<omp_get_thread_num()<<endl;
			if((x != xDest) && (y != yDest) && (z != zDest)){
			    Insere(lista,x+1,y,z,c,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z) + ")")); pi++;			    //cout<<(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z) + ")");
		            Insere(lista,x,y+1,z,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y+1) + "," + NumberToString(z) + ")")); pi++;
		            Insere(lista,x,y,z+1,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y) + "," + NumberToString(z+1) + ")")); pi++;
		            Insere(lista,x+1,y+1,z,true,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y+1) + "," + NumberToString(z) + ")")); pi++;
		            Insere(lista,x+1,y,z+1,true,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z+1) + ")")); pi++;
		            Insere(lista,x,y+1,z+1,true,(s + "->("+ NumberToString(x) + "," + NumberToString(y+1) + "," + NumberToString(z+1) + ")")); pi++;
		            Insere(lista,x+1,y+1,z+1,true,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y+1) + "," + NumberToString(z+1) + ")")); pi++;
		        }

		        if((x == xDest) && (y != yDest) && (z != zDest)){
			    Insere(lista,x,y+1,z,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y+1) + "," + NumberToString(z) + ")")); pi++;
		            Insere(lista,x,y,z+1,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y) + "," + NumberToString(z+1) + ")")); pi++;
		            Insere(lista,x,y+1,z+1,true,(s + "->("+ NumberToString(x) + "," + NumberToString(y+1) + "," + NumberToString(z+1) + ")")); pi++;
		        }

		        if((x != xDest) && (y == yDest) && (z != zDest)){
		            Insere(lista,x+1,y,z,c,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z) + ")")); pi++;
		            Insere(lista,x,y,z+1,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y) + "," + NumberToString(z+1) + ")")); pi++;
		            Insere(lista,x+1,y,z+1,true,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z+1) + ")")); pi++;
		        }

		        if((x != xDest) && (y != yDest) && (z == zDest)){
		            Insere(lista,x+1,y,z,c,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z) + ")")); pi++;
		            Insere(lista,x,y+1,z,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y+1) + "," + NumberToString(z) + ")")); pi++;
		            Insere(lista,x+1,y+1,z,true,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y+1) + "," + NumberToString(z) + ")")); pi++;
		        }

		        if((x == xDest) && (y == yDest) && (z != zDest)){
		            Insere(lista,x,y,z+1,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y) + "," + NumberToString(z+1) + ")")); pi++;
		        }

		        if((x == xDest) && (y != yDest) && (z == zDest)){
		            Insere(lista,x,y+1,z,c,(s + "->("+ NumberToString(x) + "," + NumberToString(y+1) + "," + NumberToString(z) + ")")); pi++;
		        }

		        if((x != xDest) && (y == yDest) && (z == zDest)){
		            Insere(lista,x+1,y,z,c,(s + "->("+ NumberToString(x+1) + "," + NumberToString(y) + "," + NumberToString(z) + ")")); pi++;
		        }

		        if(c && (x == xDest) && (y == yDest) && (z == zDest)){
		            contador++;
			    //cout<<s<<NumberToString(x+1);
		            cout<<s<<endl<<endl;
		        }

			Retira(lista->primeiro, lista, &lista->primeiro->item);        	
		        //delete aux;
	        }
		
	        i++;
	    }
    }
}
    catch(std::exception& e){return contador;}
    return contador;
}

double calcula_resultado(clock_t fim, clock_t inicio){
	return (fim - inicio)/(double)CLOCKS_PER_SEC;
}

int main(){
    
    TipoLista lista;
    FLVazia(&lista);
    unsigned long long int pi = 1;
    TipoItem item;
    int xDest = 5;
    int yDest = 5;
    int zDest = 5;
    int contador;
    double time;
    
    clock_t fim, inicio;
    double tempo;
    inicio = clock();
    Insere(&lista,0,0,0,false,"0,0,0");
    contador = logicaPrograma(&lista, xDest, yDest, zDest, pi);
    fim = clock();

    cout<<endl<<"Numero de caminhos: "<< contador<<endl;
    time = calcula_resultado(fim, inicio);
    cout << "Tempo de execução: " << calcula_resultado(fim, inicio) << "ms" <<endl;


    FILE *f;
    f = fopen("exec-parallel-555.txt", "w");
    fprintf(f, "%.6f segundos\n", time);
    fprintf(f, "%d caminhos \n", contador);

    return 0;
}

