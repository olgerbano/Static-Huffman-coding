#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>
#include <map>
#include <bits/stl_algo.h>
#include <bitset>
#include <cassert>
#include <fstream>
#include <stdio.h>
using namespace std;

typedef pair<unsigned char, unsigned long long int> Pereche;
typedef pair<string,Pereche> p;
typedef map<unsigned char, pair<string, unsigned long long int>> Sir_codificat;
typedef vector<Pereche> vector_Pereche;
map<unsigned char, string> codes;
bool cmp (const pair<unsigned char, unsigned long long int>  &a,const pair<unsigned char, unsigned long long int>  &b) {
    return a.second != b.second ? a.second > b.second : a.first < b.first;
};
void displayPereche(vector_Pereche VP) {
    for (Pereche &x: VP) {
        cout<<(int)x.first<<" "<<x.second<<endl;
    }
}
struct ListaGraf{
	Pereche info;
	ListaGraf *stanga;
	ListaGraf *dreapta;
	ListaGraf *urm;
	ListaGraf *ant;
};
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
     //   cout<<"dreapta"<<endl;
    } else if (tip == 0) {
       // cout<<"stanga"<<endl;
        tempChar.push_back('0');
    }
   if(este_frunza(tree)){
       // cout<<endl;
        std::pair<std::string, unsigned int> tempPereche = {tempChar, dim_bit};
        map_code.insert(map_code.begin(),pair<unsigned char, std::pair<std::string, unsigned int>>((tree->info).first, tempPereche));
    } else {
        FinalMap(tree->stanga, tempChar, 0, dim_bit + 1);
        FinalMap(tree->dreapta, tempChar, 1, dim_bit + 1);
    }
}
ListaGraf *huffman;
string lal="";
vector<char> lali;
void print_element(ListaGraf *tree, string bit ) {

    if(este_frunza(tree)){
            cout<<(char)(tree->info).first;
        lali.push_back((char)(tree->info).first);
        if (bit.size()==1)
            exit(0);
        print_element(huffman,bit);
}
    string tip;
    if(bit.size()==1){
        tip=bit;
        bit=bit;
    }else{
        tip = bit.substr(0,1);
        bit = bit.substr(1,bit.size());
    }
    if (tip=="1" ) {
          print_element(tree->dreapta, bit);
    } else if (tip=="0" ) {
        print_element(tree->stanga, bit);
    }

}
struct ArboreSannon{
	char info;
	ArboreSannon *stanga;
	ArboreSannon *dreapta;

};
ArboreSannon *shannon;

ArboreSannon *Node_Arbore(char val){
    struct ArboreSannon *temp = new struct ArboreSannon;
    temp->info = val;
    temp->dreapta = NULL;
    temp->stanga = NULL;

  return temp;
}
void makeShannon(ArboreSannon *tree, string bit ){

}
struct pnode
{
  unsigned char ch;
  unsigned int p;
};
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
                 //   cout<<p<<" "<<"u vendos 0 tek: "<<ptable[i].ch<<endl;
                    codes[ptable[i].ch] += '0';
                   // cout<<"u vendos 0"<<endl;
            }
            else{
                codes[ptable[i].ch] += '1';
                //cout<<"u vendos 1"<<endl;
         //   cout<<p<<" "<<"u vendos 1 tek: "<<ptable[i].ch<<endl;
        //    cout<<"split este :"<<split<<endl;
                if( split < 0 ) split = i;
           //     cout<<"split devine: "<<split<<endl;;
            }
        }
        ShannonFano( stanga, split-1,ptable );
        ShannonFano( split, dreapta,ptable );
    }
}
int main(){
    long int dim;
    int c;
    int a;
    FILE *inputFile;
    string nume_fisier;
    cout<<"Alege Fisier: ";
	getline(cin,nume_fisier);
    inputFile = fopen( nume_fisier.c_str(), "r" );
    assert( inputFile );
    //FILE *input = fopen("ll_comp.pdf", "rt");
    Pereche temp_p;
    vector_Pereche vec_perec;
    fscanf(inputFile, "%ld\n", &dim);
    for (int i = 0; i < dim; i++) {

        char buffer[1000];
        fscanf(inputFile, "%[^\n]\n", buffer);
        c = atoi(buffer);
        a = atoi(buffer + 2);
            temp_p.first = (char) c;
			temp_p.second = a;
			vec_perec.push_back(temp_p);
}
    sort(vec_perec.begin(),vec_perec.end(),cmp);
    vector_Pereche lista_cuvinte_finala;
	std::vector<Pereche>::iterator it;
	it = lista_cuvinte_finala.begin();
	lista_cuvinte_finala.insert(it,vec_perec.begin(),vec_perec.begin()+dim);
        char buf[300];
        fscanf(inputFile, "%s", buf);
        string cod(buf);
	cout<<"1.Huffman"<<endl<<"2.Shannon-Fano"<<endl;
	int option;
	cin>>option;
	if (option == 1){
        huffman = Constr_Lista(lista_cuvinte_finala);
        huffman = MakeHuffmanTree(huffman);
cout<<"1"<<endl;
        ofstream inFile;
        // inFile.open("ll_comp.pdf");
        print_element(huffman,cod);
        cout<<"1"<<endl;
        for (std::vector<char>::iterator it = lali.begin() ; it != lali.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';
        fclose(inputFile);
        //  inFile.close();
	}
	else{
        int  dime = lista_cuvinte_finala.size();
        pnode *ptable ;
        ptable= new pnode[dime];
        popullate(lista_cuvinte_finala,ptable);
        ShannonFano( 0,lista_cuvinte_finala.size() - 1,ptable );
        shannon = Node_Arbore((char)0);
	}
        int opt;
        cin>>opt;
        system("pause");

        return 0;
}
