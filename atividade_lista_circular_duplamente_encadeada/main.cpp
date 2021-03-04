#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "List.h"
using namespace std;

//USADO A MESMA MAIN DA ATIVIDADE PASSADA
int main()
{
	vector<List *> listas = vector<List *>();

	while (true)
	{
		string cmd;
		getline(cin, cmd);

		std::stringstream ss{cmd};
		vector<string> tokens;
		string buffer;
        
        
        
		while (ss >> buffer)
		{
			tokens.push_back(buffer);
		}
        
		if (tokens[0] == "exit")
		{
			for (int i = 0; i < listas.size(); ++i)
			{
				delete listas[i];
				listas[i] = nullptr;
			}
			listas.clear();
			break;
		}
		// createlist
		else if (tokens[0] == "createlist")
		{
			List *l = new (std::nothrow) List();
			listas.push_back(l);
			if (l != nullptr)
				cout << "lista " << listas.size() - 1 << " criada" << endl;
		}
		// add [x] list [k]
        //add 1 list 0 
		else if (tokens[0] == "add")
		{
			int x = std::stoi(tokens[1]);
			int k = std::stoi(tokens[2]);
			listas[k]->push_back(x);
			cout << x << " adicionado na lista " << k << endl;
		}
		// remove [x] list [k]
        //remove 1 list 0
		else if (tokens[0] == "remove")
		{
			int k = std::stoi(tokens[1]);
			listas[k]->pop_back();
		}
		// empty [k]
        // empty 0
		else if (tokens[0] == "empty")
		{
			int k = std::stoi(tokens[1]);
			if (listas[k]->empty())
				cout << "lista " << k << " vazia" << endl;
			else
				cout << "ha elementos na lista " << k << endl;
		}
		// size [k]
        //size 0
		else if (tokens[0] == "size")
		{
			int k = std::stoi(tokens[1]);
			cout << "cardinalidade da lista " << k << " = " << listas[k]->size() << endl;
		}
		// clear [k]
        //clear 0
		else if (tokens[0] == "clear")
		{
			int k = std::stoi(tokens[1]);
			listas[k]->clear();
			cout << "lista " << k << " vazia" << endl;
		}
		// print [k]
        //print list = 0
		else if (tokens[0] == "print")
		{
			int k = std::stoi(tokens[1]);
			cout << "lista " << k << " = ";
			listas[k]->print();
			cout << endl;
		}
		// removeall [x] list [k]
        // removeall 1 list 0
		else if (tokens[0] == "removeall")
		{
			int x = std::stoi(tokens[1]);
			int k = std::stoi(tokens[2]);
			listas[k]->removeAll(x);
		}
		// insert [x] after [i] list [k]
        // insert 1 after  list 0
		else if (tokens[0] == "insert")
		{
			int x = std::stoi(tokens[1]);
			int i = std::stoi(tokens[3]);
			int k = std::stoi(tokens[5]);
			bool confirm = listas[k]->insertAfter(x, i);
			if(confirm ){
				cout << x << " inserido apos a posicao " << i << " da lista " << k << endl;
			}else {
				cout << "posicao " << i << " nao existe na lista " << endl;
			}
		
		}
		// copy [k]
		else if (tokens[0] == "copy")
		{
			int k = std::stoi(tokens[1]);
			List *cp = listas[k]->copy();
			listas.push_back(cp);
			cout << "uma copia da lista " << k << " foi criada: ela e a lista " << listas.size() - 1 << endl;
		}
		// equal [p] [q]
		else if (tokens[0] == "equal")
		{
			int p = std::stoi(tokens[1]);
			int q = std::stoi(tokens[2]);
			bool iguais = listas[p]->equal(listas[q]);
			if (iguais)
				cout << "listas " << p << " e " << q << " sao iguais" << endl;
			else
				cout << "listas " << p << " e " << q << " sao diferentes" << endl;
		}
		// concat [p] [q]
		// concat 0 1
		else if (tokens[0] == "concat")
		{
			int p = std::stoi(tokens[1]);
			int q = std::stoi(tokens[2]);
			listas[p]->concat(listas[q]);
			cout << "listas " << p << " e " << q << " concatenadas" << endl;
			cout << "lista " << p << ": ";
			listas[p]->print();
			cout << endl;
			cout << "lista " << q << ": ";
			listas[q]->print();
			cout << endl;
		}
		// reverse [k]
		else if (tokens[0] == "reverse")
		{
			int k = std::stoi(tokens[1]);
			cout << "lista " << k << " invertida" << endl;
			cout << "lista " << k << " = ";
			listas[k]->printReverse();
			cout << endl;
		}
		// copyarray [n] [a1] [a2] [a3] .. [an] list [k]
		//copyarray 4 digita 4 elementos list 0
		else if (tokens[0] == "copyarray")
		{
			int n = std::stoi(tokens[1]);
			int k = std::stoi(tokens[n + 3]);
			int arr[n];
			for (int i = 0; i < n; i++)
			{
				arr[i] = std::stoi(tokens[2 + i]);
			}
			listas[k]->copyArray(n, arr);
			cout << "array foi copiado para lista " << k << endl;
		}
		else
		{
			cout << "comando inexistente" << endl;
		}
	}
	return 0;
}
