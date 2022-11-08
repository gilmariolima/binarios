#include <bits/stdc++.h>
using namespace std;

class banca
{
private:
    char nome[100];
    char email[100];
    char curso_aluno[100];
    char celular_aluno[50];
    int semestre;
    int matricula_aluno;

    char nome_orientador[100];
    int frequencia_aluno;

    char nome_avaliador[100];
    char instituicao[100];
    char email_avaliador[100];

    char titulo[100];
    char resumo[600];
    char horario[50];
    char local[100];

public:
    static int bancaCount();
    friend istream& operator >>(istream& in, banca& p);
    friend ostream& operator <<(ostream& saida, banca& p);
    void earquivo() const; // escrever arquivo
    void lerarquivo(int);
    int obtermatricula(){return matricula_aluno;}
};

int banca::bancaCount()
{
    ifstream arquivot;
    arquivot.open("BANCA.TXT");
    arquivot.seekg(0, ios::end);
    return (int)arquivot.tellg() / sizeof(banca);
}

istream& operator>>(istream& in, banca& p) // obter dados da banca
{
    cout << "--------ALUNO--------\n";
    cout << "Nome do aluno: \n";
    in >> p.nome;
    cout << "Email do aluno: \n";
    in >> p.email;
    cout << "Curso do aluno: \n";
    in >> p.curso_aluno;
    cout << "Telefone do aluno: \n";
    in >> p.celular_aluno;
    cout << "Semestre do aluno: \n";
    in >> p.semestre;
    cout << "Matricula do aluno: \n";
    in >> p.matricula_aluno;
    cout << "--------Orientador--------\n";
    cout << "Nome do orientador: \n";
    in >> p.nome_orientador;
    cout <<"Frequência do aluno: \n";
    in >> p.frequencia_aluno;
    cout << "--------AVALIADOR--------\n";
    cout << "Nome do avaliador: \n";
    in >> p.nome_avaliador;
    cout << "Email do avaliador: \n";
    in >> p.email_avaliador;
    cout << "Instituição: \n";
    in >> p.instituicao;
    cout << "--------BANCA--------\n";
    cout << "Título: \n";
    in >> p.titulo;
    cout << "Resumo: \n";
    in >> p.resumo;
    cout << "Horário: \n";
    in >> p.horario;
    cout << "Local: \n";
    in >> p.local;
    return in;
}

ostream& operator << (ostream& saida, banca& p)
{
    cout << "--------ALUNO--------" << endl;
    saida << "Nome: " << p.nome << endl;
    saida << "Email: " << p.email << endl;
    saida << "Curso: " << p.curso_aluno << endl;
    saida << "Telefone: " << p.celular_aluno << endl;
    saida << "Semestre: " << p.semestre << endl;
    saida << "Matricula: " << p.matricula_aluno << endl;
    cout << "--------Orientador--------" << endl;
    saida << "Nome do orientador: " << p.nome_orientador << endl;
    saida << "Frequência do aluno: " << p.frequencia_aluno << endl;
    cout << "--------AVALIADOR--------" << endl;
    saida << "Nome do avaliador: " << p.nome_avaliador << endl;
    saida << "Email do avaliador: " << p.email_avaliador << endl;
    saida << "Instituição: " << p.instituicao << endl;
    saida << "--------BANCA--------" << endl;
    saida << "Título: " << p.titulo << endl;
    saida << "Resumo: " << p.resumo << endl;
    saida << "Horário: " << p.horario << endl;
    saida << "Local: " << p.local << endl;

    return saida;

}

void banca::earquivo() const
{ // gravar banca no final do arquivo
    ofstream arquivot;
    arquivot.open("BANCA.TXT", ios::app | ios::binary);
    arquivot.write((char *)this, sizeof(banca)); // escrever
}

void banca::lerarquivo(int i)
{
    ifstream arquivo;
    arquivo.open("BANCA.TXT");
    arquivo.seekg(i*sizeof(banca));
    arquivo.read((char *)this, sizeof(*this));
}

class FileO
{
    private:
        banca p;
    public:
        void unpack();
        void pack();
        int buscar(int mat);
        void alterar(int mat);
        void apagar(int mat);
};



void FileO::pack() //só um método pra repetir o procedimento
{
    string ch;
    {
        cin >> p;
        p.earquivo();
        cout << "Repetir procedimento? (s/n)? \n" << endl;
        cin >> ch;
    } while (ch == "s");
}

void FileO::unpack()  //visualizar os dados
{
    int n=banca::bancaCount();
    for( int i=0 ; i<n ; ++i)
    {
        p.lerarquivo(i);
        cout<<p;
    }
}

int FileO::buscar(int mat){
    int n=banca::bancaCount();
    for(int i=0 ; i < n ; ++i){
        p.lerarquivo(i);
        if(p.obtermatricula() == mat){
            cout << "Registro encontrado\n";
            cout<<p;
            return i;
        }

    }
    return -1;
}

void FileO::apagar(int mat){
    int n=banca::bancaCount();
    vector< banca >vp;
    int f=buscar(mat);
    for(int i=0; i<n; ++i){
        p.lerarquivo(i);
        if(f!=i)
            vp.push_back(p);
    }
    ofstream arquivos;
    arquivos.open("BANCA.TXT", ios::binary);

    for(int i=0; i < vp.size() ;i++){
        arquivos.write((char *)&vp[i], sizeof(banca));
    }
}

void FileO::alterar(int mat){
    int n=banca::bancaCount();
    vector<banca> vp;
    int f = buscar(mat);
    if(f==-1){cout<<"Não encontrado \n" ; return; }
    for(int i=0 ; i<n ; ++i){

        p.lerarquivo(i);
        if(f!=i)
            vp.push_back(p);
        else
            cin>>p, vp.push_back(p);

    }
    ofstream arquivo;
    arquivo.open("BANCA.TXT", ios::binary);
    for(int i=0;i<vp.size(); i++){
        arquivo.write((char*)&vp[i],sizeof(banca));
    }
}

int main(){
    FileO o;
    while(true){
        cout<< "1.Adicionar\n2.Mostrar tudo\n3.Procurar\n4.Alterar\n5.Deletar\n6.Sair\nDigite uma opção: ";
        int ch;
        cin>>ch;
        switch(ch){
            case 1:{

                o.pack();
                break;
            }case 2:
                o.unpack();
                break;
            case 3:{
                int mat;
                cout << "Digite a matricula: ";
                cin >> mat;
                if(o.buscar(mat)==-1)cout<<"Não encontrado\n";
                break;
            }
            case 4:{
                int mat;
                cout << "Digite a matriula que quer modificar:";
                cin>>mat;
                o.alterar(mat);
                break;
            }
            case 5:{
                int mat;

                cout<<"Digite a matricula para deletar:";
                cin>>mat;
                o.apagar(mat);
                break;
            }
            default:
                exit(0);
            }

        }
        return 0;
    }