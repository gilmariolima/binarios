#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
vector<planeta> lista;

void salvar(planeta aux){
    ofstream arq;
    arq.open("planetas.dat",ios::binary|ios::app);
    arq.write((char*)&aux, sizeof(aux));  
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
    
    arq.open("planetas.dat",ios::binary);

    while(arq.read((char*)&aux, sizeof(aux))){
        lista.push_back(aux);    
    }
    arq.close();
}

void ver_lista(){
    for(int i=0; i<lista.size();i++){
        cout << lista[i].get_nome() << "-" << lista[i].get_gravidade() << "-" <<lista[i].get_habitantes()<< endl;
    }
}

void filtrar(){
    int gravidade;
    cout << "Gravidade: "; cin >> gravidade;
    cout << "Planetas com gravidade " << gravidade << endl;
    for(int i=0; i < lista.size(); i++){
        if(lista[i].get_gravidade() == gravidade){
            cout << lista[i].get_nome() << endl;
        }
    }
}

int main(){
    int opc = 1;

    while(opc != 0){
        cout << "[ 1 ] Cadastrar\n";
        cout << "[ 2 ] Ver lista\n";
        cout << "[ 3 ] Filtrar\n";
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
            case 3:
                filtrar();
                break;
            default:
                break;
        }
    }
    return 0;
}