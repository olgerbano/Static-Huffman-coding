#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <bits/stl_algo.h>
#include <bitset>
#include <cassert>
#include <fstream>
using namespace std;

typedef pair<unsigned char, unsigned long int> Pereche;
typedef pair<string,Pereche> p;
typedef map<unsigned char, pair<string, unsigned long int> > Sir_codificat;
typedef vector<Pereche> vector_Pereche;
map<char, string> codes;
struct ListaGraf{
	Pereche info;
	ListaGraf *stanga;
	ListaGraf *dreapta;
	ListaGraf *urm;
	ListaGraf *ant;
};

bool cmp (const pair<unsigned char, unsigned  int>  &a,const pair<unsigned char, unsigned int>  &b) {
    return a.second != b.second ? a.second > b.second : a.first < b.first;
};

void displayPereche(vector_Pereche VP) {
    for (Pereche &x: VP) {
        cout<<(int)x.first<<" "<<x.second<<endl;
    }
}
ListaGraf *Constr_Lista(vector_Pereche lista_cuvinte_finala) {

    ListaGraf *parent, *currentItem, *newItem;
    Pereche tempinfo;
    parent = NULL;
    for (Pereche &x: lista_cuvinte_finala) {
     if (parent == NULL) {
            parent = new ListaGraf;
            parent->info = x;
            parent->stanga = NULL;
            parent->dreapta = NULL;
            parent->urm = NULL;
            parent->ant = NULL;
            currentItem = parent;
       } else {
            newItem = new ListaGraf;
            newItem->info = x;
            newItem->stanga = NULL;
            newItem->dreapta = NULL;
            newItem->urm = NULL;
            newItem->ant = currentItem;
            currentItem->urm = newItem;
            currentItem = newItem;
        }
    }
    return parent;
}

ListaGraf *ultima_pereche(ListaGraf *graph) {
    while (graph->urm != NULL) {
        graph = graph->urm;
    }
    return graph;
}

bool compareNodes(ListaGraf *nodeA, ListaGraf *nodeB) {

     if ((nodeA->info).second > (nodeB->info).second
         || ((nodeA->info).second == (nodeB->info).second
             and ((nodeA->info).first >= (nodeB->info).first) ))

                    return true;
        else
        return false;
}

int dim_lista(ListaGraf *temp){

    if(!temp)
     return(0);
    return(1 + dim_lista(temp->urm));

}
bool isSizetwo(struct ListaGraf* root){
	return (dim_lista(root)== 2);
}

ListaGraf *MakeHuffmanTree(ListaGraf *graph) {

	ListaGraf *itemGraph, *lastItem, *iteration, *parent;

   while (!isSizetwo(graph)){
            parent = graph;
            lastItem = ultima_pereche(parent);
            itemGraph = new ListaGraf;
            itemGraph->stanga = lastItem->ant;
            itemGraph->dreapta = lastItem;
            lastItem = lastItem->ant->ant;
            itemGraph->info = Pereche('$', (itemGraph->stanga->info).second + (itemGraph->dreapta->info).second);
            if (itemGraph->stanga->ant->urm != NULL)
                itemGraph->stanga->ant->urm = NULL;
        itemGraph->stanga->urm = NULL;
        itemGraph->stanga->ant = NULL;
        itemGraph->dreapta->urm = NULL;
        itemGraph->dreapta->ant = NULL;
        iteration = lastItem;

        while (iteration->ant) {
            if (compareNodes(itemGraph, iteration) == true) {
                iteration = iteration->ant;
            } else {
                break;
            }
        }
        if (!iteration->ant ){
            itemGraph->urm = graph;
            graph->ant = itemGraph;
            graph = itemGraph;
            itemGraph->ant = NULL;
        } else {
            itemGraph->urm = iteration->urm;
            iteration->urm->ant = itemGraph;
            itemGraph->ant = iteration;
            iteration->urm = itemGraph;
        }
    }
    itemGraph = new ListaGraf;
    itemGraph->stanga = graph;
    itemGraph->ant = NULL;
    itemGraph->urm = NULL;
    itemGraph->dreapta = graph->urm;
    graph->dreapta->ant = NULL;
    graph->urm = NULL;
    itemGraph->info = Pereche('$', (itemGraph->stanga->info).second + (itemGraph->dreapta->info).second);
    graph = itemGraph;
    return graph;
}

bool este_frunza(ListaGraf *root){
    return !(root->stanga) && !(root->dreapta) ;
}
Sir_codificat map_code;
void FinalMap(ListaGraf *tree, string tempChar, int tip, unsigned long int dim_bit ) {

    if (tip == 1) {
        tempChar.push_back('1');
    } else if (tip == 0) {
        tempChar.push_back('0');
    }
   if(este_frunza(tree)){
        std::pair<std::string, unsigned int> tempPereche = {tempChar, dim_bit};
        map_code.insert(map_code.begin(),pair<unsigned char, std::pair<std::string, unsigned int>>((tree->info).first, tempPereche));
    } else {
        FinalMap(tree->stanga, tempChar, 0, dim_bit + 1);
        FinalMap(tree->dreapta, tempChar, 1, dim_bit + 1);
    }
}

struct pnode
{
  char ch;
  float p;
};

void view_pnode(pnode *ptable, int tsize){
    for( int i=0; i<tsize; i++ )
      cout<<ptable[i].ch<<" "<<ptable[i].p<<endl;
}
void popullate(vector_Pereche VP, pnode *p ){
    int i = 0;
    for (Pereche &x: VP) {
        p[i].ch=x.first;
        p[i].p=float(x.second);
        i++;
    }
}

void ShannonFano( int stanga, int dreapta ,pnode *ptable){
    int i, split;
    float p;
    float suma;
    float jumate;
    if( stanga == dreapta ){
      return;
    }
    else if( dreapta - stanga == 1 ){
      codes[ptable[stanga].ch] += '0';
      codes[ptable[dreapta].ch] += '1';
    }
    else{
      suma = 0;
      for( i=stanga; i<=dreapta; ++i )
        suma += ptable[i].p;
        p = 0;
        split = -6;
        jumate = suma/2;
        for( i=stanga; i<=dreapta; ++i ){
            p += ptable[i].p;
            if(p <= jumate) {
                codes[ptable[i].ch] += '0';
            }
            else{
                codes[ptable[i].ch] += '1';
                if( split < 0 ) split = i;
            }
        }
        ShannonFano( stanga, split-1,ptable );
        ShannonFano( split, dreapta,ptable );
    }
}
int main(){
	string nume_fisier, nume_fisier_comp;
	cout<<"Alege Fisier: ";
	getline(cin,nume_fisier);
	size_t found = nume_fisier.find('.');
    string str2 = nume_fisier.substr(0,found);
    string str5 = str2;
    str2 = str2+"_comp";
    string str3 = nume_fisier.substr(found,nume_fisier.length());
    string str4 = str3;
    str2 = str2+str3;
    nume_fisier_comp = str2 ;
	vector<long int> per(256);
	unsigned char temp;
	FILE *inputFile;
    inputFile = fopen( nume_fisier.c_str(), "r" );
    assert( inputFile );
    long long int nr_total = 0;;
     while( fscanf( inputFile, "%c", &temp ) != EOF )
    {
      per[temp]++;
      nr_total++;
    }
    fclose( inputFile );
	Pereche temp_p;
	unsigned long long int dim=0;
	vector_Pereche vec_perec;
	for(int i = 0 ; i < per.size() ; i ++){
		if(per[i] > 0){
			temp_p.first = (char) i;
			temp_p.second = per[i];
			vec_perec.push_back(temp_p);
			dim++;
		}
	}
	sort(vec_perec.begin(),vec_perec.end(),cmp);
	vector_Pereche lista_cuvinte_finala;
	std::vector<Pereche>::iterator it;
	it = lista_cuvinte_finala.begin();
	lista_cuvinte_finala.insert(it,vec_perec.begin(),vec_perec.begin()+dim);

    cout<<"1.Huffman Static"<<endl;
    cout<<"2.Shannon-Fano"<<endl;
    int option;
    cin>>option;
    if(option == 1){
        ListaGraf *huffman;
        huffman = Constr_Lista(lista_cuvinte_finala);
        huffman = MakeHuffmanTree(huffman);
        string b="";
        FinalMap(huffman,b,'c',0);
        ofstream file;
        file.open (nume_fisier_comp);
        for(auto elem: map_code){
            file << elem.first << " " << elem.second.first << " " << elem.second.second << "\n";
            cout<< elem.first << " " << elem.second.first << " " << elem.second.second << "\n";
        }
        string cod="";
        inputFile = fopen( nume_fisier.c_str(), "r" );
        assert( inputFile );
        while( fscanf( inputFile, "%c", &temp ) != EOF ){
            cod = cod+ map_code[temp].first;
        }
        file<<cod;
        cout<<cod;
        file.close();
    }
    else{
        int  dime = lista_cuvinte_finala.size();
        pnode *ptable ;
        ptable= new pnode[dime];
        popullate(lista_cuvinte_finala,ptable);
        ShannonFano( 0,lista_cuvinte_finala.size() - 1,ptable );
        ofstream file;
        file.open (nume_fisier_comp);
        for( int i=0; i<dime; i++ ){
            cout<<ptable[i].ch<<" "<< codes[ptable[i].ch]<<" "<<codes[ptable[i].ch].size()<<  "\n";
            file<<ptable[i].ch<<" "<< codes[ptable[i].ch]<<" "<<codes[ptable[i].ch].size()<<  "\n";
        }
        cout<<endl;
        file<<"\n";
        unsigned char ch;
        string cod="";
        inputFile = fopen( nume_fisier.c_str(), "r" );
        assert( inputFile );
        while( fscanf( inputFile, "%c", &ch ) != EOF )
        cod=cod+codes[ch];
        file<<cod;
        cout<<cod;
        file.close();
        cout<<endl;
        codes.clear();
        delete[] ptable;
    }
    int o;
    getchar();
    cin>>o;
}
