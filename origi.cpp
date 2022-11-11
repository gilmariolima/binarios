#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

class planeta{
    private:
        string nome;
        float gravidade;
        double habitantes;
    public:
        planeta(string nome, float gravidade, double habitantes){
            set_nome(nome);
            set_gravidade(gravidade);
            set_habitantes(habitantes);
        }
        planeta(){}
        void set_nome(string nome){this->nome = nome;}
        void set_gravidade(float gravidade){this->gravidade = gravidade;}
        void set_habitantes(double habitantes){this->habitantes = habitantes;}

        string get_nome(){return nome;}
        float get_gravidade(){return gravidade;}
        double get_habitantes(){return habitantes;}

};

int num = 0;
vector <planeta> lista;
vector <planeta> novalista;

void salvar(planeta aux){
    ofstream arq;
    arq.open("planetas.dat",ios_base::binary|ios_base::app);
    arq.write((char*)&aux, sizeof(planeta));  
    arq.close();
}

void add_planeta(){
    string nome; float gravidade; double habitantes;
    cout << "Nome: "; cin >> nome;
    cout << "Gravidade: "; cin >> gravidade;
    cout << "Habitantes: "; cin >> habitantes;

    planeta aux(nome, gravidade, habitantes);

    salvar(aux);
}

void ler(){
    planeta aux;
    ifstream arq;
    lista.clear();
    
    arq.open("planetas.dat",ios_base::binary);

    while(arq.read((char*)&aux, sizeof(planeta))){
        lista.push_back(aux);
    }
    arq.close();
}

void novoler(){
    planeta aux;
    ifstream arq;
    lista.clear();
    
    arq.open("novo.dat",ios_base::binary);

    while(arq.read((char*)&aux, sizeof(planeta))){
        lista.push_back(aux);
    }
    arq.close();
}

void apagar(int gravidade){
    planeta aux;
    ifstream arq;
    ofstream fout;
    lista.clear();
    
    arq.open("planetas.dat",ios_base::binary);
    fout.open("novo.dat",ios_base::binary|ios_base::app);

    while(arq.read((char*)&aux, sizeof(planeta))){
        if(aux.get_gravidade() != gravidade){
            fout.write((char*)&aux, sizeof(planeta));  
        }
    }
    fout.close();
    arq.close();
    remove("planetas.dat");
    rename("novo.dat","planetas.dat");  
}

void ver_lista(){
    for(int i=0; i<lista.size();i++){
        cout << lista[i].get_nome() << "-" << lista[i].get_gravidade() << "-" <<lista[i].get_habitantes()<< endl;
    }
}

int main(){
    int opc = 1;
    int gravidade;

    while(opc != 0){
        cout << "[ 1 ] Cadastrar\n";
        cout << "[ 2 ] Ver lista\n";
        cout << "[ 3 ] Filtrar\n";
        cout << "[ 4 ] Deletar\n";
        cout << "[ 0 ] Sair\n";
        cout << ">> ";
        cin >> opc;

        switch(opc){
            case 1:
                add_planeta();
                break;
            case 2:
                ler();
                ver_lista();
                break;
            case 4:
                cout << "gravidade: ";
                cin >> gravidade; 
                apagar(gravidade);
                break;
            default:
                break;
        }
    }
    return 0;
}