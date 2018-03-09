#ifndef INT_CANIBAIS
#define INT_CANIBAIS
#include <iostream>
#include <cmath>
class Node_Tree{

public:
	int missionaries;
	int cannibals;
	int position;
	Node_Tree *father;

	Node_Tree(){
		father = 0;
	}
	Node_Tree(int missio, int canni, int posi, Node_Tree *dad){
		missionaries = missio;
		cannibals = canni;
		position = posi;
		father = dad;
	}


};

class Node_List{
public:
	Node_Tree *info;
	Node_List *next;
	Node_List(){
		next = 0;
	}
	Node_List(Node_Tree *received){
		info = received;
		next = 0;
	}
};

class Linked_List{

private:
	Node_List *first;
	Node_List *last;

public:
	Linked_List(){
		first = last = 0;
	}

	void add_Node(Node_Tree *new_Node){
		if(last == 0){
			first = new Node_List(new_Node);
			last = first;
		}
		else{
			last->next = new Node_List(new_Node);
			last = last->next;
		}
	}

	void move_first(){
		first = first->next;
	}
	Node_List* get_first(){
		if(first!= 0){
			return first;
		}
		else{
			std::cout << "deu ruim" << '\n';
		}
	}
};

class Tree{

public:
	Node_Tree *root;
	Node_List *actual;
	Linked_List *list;
	int left[4][4];
	int right[4][4];
	int posi;
	Tree(){
		root = new Node_Tree(3,3,0,0);
		list = new Linked_List();
		for(int i = 0; i < 4; i++) {
        	for(int j = 0; j < 4; j++) {
            	left[i][j] = 0;
            	right[i][j] = 0;
        	}
    	}
		posi = 0;
	}
	void creat_Tree(){
		list->add_Node(root);
		left[3][3] = 1;
		while(1){
			actual = list->get_first();
			posi = std::abs(actual->info->position);

			if(actual->info->missionaries  == 3 && actual->info->cannibals == 3 && actual->info->position == -1){
				std::cout << "Caminho percorrido até o resultado:" << '\n';
				while(actual->info != 0){
					std::cout << "[" << actual->info->missionaries << "]"<< "[" << actual->info->cannibals<< "]"
					          << "[" << actual->info->position << "]" << " --> ";
					actual->info = actual->info->father;
				}
				break;
			}

			else{
			// transportar 1 canibal
				if((actual->info->cannibals >= 1) && ((3 - actual->info->missionaries == 0) ||
				   ((3 - actual->info->missionaries) - (3 - actual->info->cannibals) >= 1))){

					   if((std::abs(actual->info->position)-1) == 0){
						   if(left[3 - actual->info->missionaries][3 - actual->info->cannibals + 1] == 0){
							   Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries, 3 - actual->info->cannibals + 1,
		   									                  (std::abs(actual->info->position)-1), actual->info);
		   						list->add_Node(new_son);
								left[3 - actual->info->missionaries][ 3 - actual->info->cannibals + 1] = 1;

						   }
					   }
					   else{
						   if(right[3 - actual->info->missionaries][3 - actual->info->cannibals + 1] == 0){
							    Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries, 3 - actual->info->cannibals + 1,
   														   (std::abs(actual->info->position)-1), actual->info);
								right[3 - actual->info->missionaries][3 - actual->info->cannibals + 1] = 1;
   								list->add_Node(new_son);

						   }

					   }


				}
			// transportar 2 canibal
				if((actual->info->cannibals >= 2) && ((3 - actual->info->missionaries == 0) ||
				   ((3 - actual->info->missionaries) - (3 - actual->info->cannibals) >= 2))){

						if((std::abs(actual->info->position)-1) == 0){
   							if(left[3 - actual->info->missionaries][3 - actual->info->cannibals + 2] == 0){
								Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries, 3 - actual->info->cannibals + 2,
												                  (std::abs(actual->info->position)-1), actual->info);
								left[3 - actual->info->missionaries][3 - actual->info->cannibals + 2] = 1;
								list->add_Node(new_son);

							}
						}
						else{
							if(right[3 - actual->info->missionaries][3 - actual->info->cannibals + 2] == 0){
							   Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries, 3 - actual->info->cannibals + 2,
																 (std::abs(actual->info->position)-1), actual->info);
				 				right[3 - actual->info->missionaries][3 - actual->info->cannibals + 2] = 1;
							    list->add_Node(new_son);

						    }

						}
				}
			// transportar 1 missionário
				if((actual->info->missionaries >= 1) && ((actual->info->missionaries - 1 >= actual->info->cannibals) ||
				   (actual->info->missionaries - 1 == 0) && ((3 - actual->info->cannibals == 0) || ((3 -
					actual->info->cannibals) - (3 - actual->info->missionaries) <= 1 )))){

						if((std::abs(actual->info->position)-1) == 0){
   							if(left[3 - actual->info->missionaries + 1][3 - actual->info->cannibals] == 0){
								Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries + 1, 3 - actual->info->cannibals,
											                      (std::abs(actual->info->position) - 1), actual->info);
								list->add_Node(new_son);
								left[3 - actual->info->missionaries + 1][3 - actual->info->cannibals] = 1;

							}
						}
						else{
							if(right[3 - actual->info->missionaries][3 - actual->info->cannibals] == 0){
							   Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries + 1, 3 - actual->info->cannibals,
																 (std::abs(actual->info->position) - 1), actual->info);
								right[3 - actual->info->missionaries][3 - actual->info->cannibals] = 1;
							   list->add_Node(new_son);

						}
					}
				}
			// transportar 2 missionário
				if((actual->info->missionaries >= 2) && ((actual->info->missionaries - 2 >= actual->info->cannibals) ||
				   (actual->info->missionaries - 2 == 0) && ((3 - actual->info->cannibals == 0) || ((3 -
					actual->info->cannibals) - (3 - actual->info->missionaries) <= 2 )))){

						if((std::abs(actual->info->position)-1) == 0){
   							if(left[3 - actual->info->missionaries + 2][3 - actual->info->cannibals] == 0){
   								left[3 - actual->info->missionaries + 2][3 - actual->info->cannibals] = 1;
								Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries + 2, 3 - actual->info->cannibals,
											                      (std::abs(actual->info->position) - 1), actual->info);
								list->add_Node(new_son);
							}
						}
						else{
							if(right[3 - actual->info->missionaries + 2][3 - actual->info->cannibals] == 0){
 							   right[3 - actual->info->missionaries + 2][3 - actual->info->cannibals] = 1;
							   Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries + 2, 3 - actual->info->cannibals,
																 (std::abs(actual->info->position) - 1), actual->info);
							   list->add_Node(new_son);
						   }
						}
				}
			// transportar 1 missionário e 1 canibal
				if((actual->info->cannibals >= 1) && (actual->info->missionaries >= 1) && ((3 - actual->info->cannibals == 0)
					||(3 - actual->info->cannibals <= 3 - actual->info->missionaries))){
						if((std::abs(actual->info->position)-1) == 0){
   							if(left[3 - actual->info->missionaries + 1][3 - actual->info->cannibals + 1] == 0){
								left[3 - actual->info->missionaries + 1][3 - actual->info->cannibals + 1] = 1;
								Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries + 1, 3 - actual->info->cannibals + 1,
												                  (std::abs(actual->info->position) - 1), actual->info);
								list->add_Node(new_son);
							}
						}
						else{
							if(right[3 - actual->info->missionaries + 1][3 - actual->info->cannibals + 1] == 0){
 							   right[3 - actual->info->missionaries + 1][3 - actual->info->cannibals + 1] = 1;
							   Node_Tree *new_son = new Node_Tree(3 - actual->info->missionaries + 1, 3 - actual->info->cannibals + 1,
																 (std::abs(actual->info->position) - 1), actual->info);
							   list->add_Node(new_son);
						   }
						}
				}
			}
			list->move_first();
		}
	}
};

int main(){

	Tree *tree = new Tree();
	tree->creat_Tree();
	return 0;

}
#endif
