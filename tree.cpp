#include "tree.h"
#include <iostream>
using namespace std; 
void tree::print(node *start) {
	if (start != NULL) {
		start->state.print();
		for (int i = 0; i < 6; i++) {
			print(start->ptrs[i]);
		}
	}
}
void tree::get_children(node *start, short player) {
	board temp; node *_internal_arr[6];
	for (int i = 0; i < 6; i++) {
		temp.copy(&BOARD_NOW);
		flag out = temp.play(player, i);
		if (out.islegal) {
			_internal_arr[i] = new node;
			_internal_arr[i]->state.copy(&temp);
			for (int j = 0; j < 6; j++) {
				_internal_arr[i]->ptrs[j] = NULL;
			}
		}
		else {
			_internal_arr[i] = NULL;
		}
	}
	short count = 0;
	for (int i = 0; i < 6; i++) {
		if (_internal_arr[i] != NULL) {
			start->ptrs[count++] = _internal_arr[i];
		}
	}
}
void tree::traverse(node *root, int level) {
	if (root != NULL && level > 0) {
		get_children(root, (level % 2));
		level--;
		for (int i = 0; i < 6; i++) {
			traverse(root->ptrs[i], level);
		}
	}
}
void tree::eval_leafs(node *start) {
	if (start != NULL) {
		for (int i = 0; i < 6; i++) {
			eval_leafs(start->ptrs[i]);
			start->win_by = isleaf(start) ? eval(start) : -50;
		}
	}
}
void tree::eval_driver() {
	eval_leafs(tree_ptr);
}
bool tree::isleaf(node *start) {
	bool flag = 0;
	for (int i = 0; i < 6; i++) {
		if (start->ptrs[i] != NULL) {
			return 0;
		}
	}
	if (start != NULL) {
		return 1;
	}
	else {
		return  0;
	}
}
short tree::eval(node *nd) {
	return nd->state.calc_eval();
}