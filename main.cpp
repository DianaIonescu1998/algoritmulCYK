#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct reguli{
    char *l; // literele din gramatica
    int nr; // numarul de neterminale din gramatica
};


/// OBS! gramatica va fi scrisa in fisierul de intrare astfel incat sa nu se revina la acelasi neterminal dupa ce am inceput sa citesc un  neterminal diferit

void cauta (char **gramatica, int linii, char *&cuv , char *x, char *y){
    int i;
    char *aux;
    int nr=0;
    aux= new char [20];
    for(int ix=0; ix<strlen(x); ix++){
        for(int iy=0; iy<strlen(y);iy++)
    for(i=0;i<linii; i++)
    {bool ok=true;
        if(gramatica[i][1]==x[ix] && gramatica[i][2]==y[iy]){
            for(int k=0; k<nr; k++)
                if(aux[k]==gramatica[i][0]) ok=false;
            if(ok) {aux[nr]=gramatica[i][0];
                  nr++;}
        }
    }
    }
    cuv= new char [nr+1];
    for(i=0; i<nr; i++)
        cuv[i]=aux[i];
    cuv[nr]='\0';
    //cout<<"\ntest in cauta "<<cuv<<" ";
}

void reuniune (char *&x, char *y){
    char *aux;
    int nr=0;
    aux= new char [strlen(x)+ strlen(y)+1];
    if(strlen(x)>0) {strcpy(aux,x);
                     nr=strlen(x);}
    int i, j;
    for(i=0; i<strlen(y); i++){
        j=0;
        while(j<strlen(x) && y[i]!=x[j]) j++;
        if(j==strlen(x)){
            aux[nr]=y[i];
            nr++;
        }
    }
    aux[nr]='\0';
    //cout<<"\nTEST IN reuniune: "<<aux;
    strcpy(x,aux);
    //cout<<"\nTEST IN reuniune: "<<x;
}


int main() {
    // citirea gramaicii FNC
    ifstream fin ("C:\\Users\\Dell\\Desktop\\LFA\\PROIECTE+TEME\\algoritmulCYK\\gramatica1.txt");
    char **g;//matrice in care memorez gramatica
    char **aux;
    aux= new char* [100];
    for(int i=0; i<100; i++)
    aux[i]= new char [3];
    int nrm=0;
    int count=0; // numar neterminalele
    char x, y[3];
    fin>>x;
    count++;
    aux[nrm][0]=x;
    while(fin>>y){
        aux[nrm][0]=x;
        if(y[0]>='a' && y[0]<='z'){
            aux[nrm][1]=y[0];
            aux[nrm][2]='-';
        }
        else {
            aux[nrm][1] = y[0];
            aux[nrm][2] = y[1];
        }
        nrm++;
        fin>>x;
        if(aux[nrm-1][0]!=x) count++;
    }
    g= new char* [100];
    for(int i=0; i<100; i++)
        g[i]= new char [3];
 for(int i=0; i<nrm; i++)
     for(int j=0; j< 3; j++)
         g[i][j]=aux[i][j];
    for(int i=0; i<100; i++)
        delete [] aux[i];
    delete [] aux;
    // afisare matrice
//     for(int i=0; i<nrm; i++){
//        for(int j=0; j< 3; j++)
//            cout<<g[i][j]<<" ";
//    cout<<endl;}//afisare matrice
     //cout<<count<<endl;

    char cuvant[100];
    int j,i; //j va indica lungimea cuvantului
             // i va indca pozitia in cuvant
    cout<<"Cuvantul: ";
    cin>>cuvant;
    reguli **V;
    V= new reguli*[strlen(cuvant)];
    i= strlen(cuvant);

    for(j=0; j< strlen(cuvant); j++){
            V[j]= new reguli [i];
        i--;}

            i= strlen(cuvant);
    for(j=0; j< strlen(cuvant); j++){
        for(int k=0; k<i;k++)
        V[j][k].nr=count+1; // voi crea cuvinte si pe ultima pozitie voi pune '\0'
        i--;}


        i=strlen(cuvant);
    for(j=0; j< strlen(cuvant); j++){
        for(int k=0; k<i;k++){
            V[j][k].nr=count+1;
            V[j][k].l= new char [count+1];      /// aloc memorie pentru cuvinte formate din neterminale
            V[j][k].l[0]='\0';
        }
        i--;}

    //setez prima linie din matrice
    for(j=0; j<strlen(cuvant); j++)
    {int nrl=0;
        for(int k=0; k<nrm; k++)
      if(g[k][1]==cuvant[j]){
          V[0][j].l[nrl]=g[k][0];
           nrl++;}
        V[0][j].l[nrl]='\0';
      }



    ///////////////////////////////////////test V[j][i]

    int k;//k ia valori de la 0 la j, k<j
    int ii; //indici
    i=strlen(cuvant)-1;
    for(j=1; j<strlen(cuvant); j++){
        for(ii=0; ii<i; ii++){
            for(k=0; k<j; k++){
                char*word= nullptr;
            cauta(g, nrm, word, V[k][ii].l, V[j-k-1][ii+k+1].l);
                reuniune(V[j][ii].l, word);
            }
        }
       i--;
    }




//afisare
    i=strlen(cuvant);
    for(j=0; j< strlen(cuvant); j++){
        for(int k=0; k<i;k++){

            if( strlen(V[j][k].l)==0) cout<<"Ø ";
            else cout<<V[j][k].l<<" ";
            //cout<<j<<k<<" ";
        }
        cout<<endl;
        i--;}
    cout<<endl;




    i=0;
    bool ok=false;

    while((i<strlen(V[strlen(cuvant)-1][0].l))&& ! ok ){if( V[strlen(cuvant)-1][0].l[i]==g[0][0]) ok=true;
            i++;}

    if(!ok)
        cout<<"Cuvantul "<<cuvant<<" nu este generat de gramatica.";
    else cout<<"Cuvantul "<<cuvant<<" este generat de gramatica.";

    return 0;
}