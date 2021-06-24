#include "redblacktree.hpp"

#define NULL nullptr


template class RedBlackTree<int>;
template class Node<int>;

// ---- Node methods ---- //

template <typename T>
Node<T>::Node(int key, T value) {
	this->key = key;
	this->value = value;
	this->color = RED;
	this->left = NULL;
	this->right = NULL;
}

template <typename T>
int Node<T>::get_key() {
	return key;
}

template <typename T>
T Node<T>::get_value() {
	return value;
}

template <typename T>
void  Node<T>::set_value(T value) {
	this->value = value;
}


template <typename T>
Node<T>* Node<T>::get_left() {
	return left;
}

template <typename T>
Color Node<T>::get_color() {
	return color;
}

template <typename T>
void Node<T>::set_color(Color color) {
	this->color = color;
}

template <typename T>
void Node<T>::set_left(Node<T>* left) {
	this->left = left;
}


template <typename T>
Node<T>* Node<T>::get_right() {
	return right;
}

template <typename T>
void Node<T>::set_right(Node<T>* right) {
	this->right = right;
}


// --- RedBlackTree methods --- //

template <typename T>
RedBlackTree<T>::RedBlackTree() {
	root = NULL;
}

template <typename T>
void RedBlackTree<T>::put(int key, T value) {
	root = put(root, key, value);
	root->set_color(BLACK);
}

template <typename T>
Node<T>* RedBlackTree<T>::get(int key) {
	return get(root, key);
}

template <typename T>
void RedBlackTree<T>::clear() {
	delete_node(root);
	root = NULL;
}


template <typename T>
RedBlackTree<T>::~RedBlackTree() {
	delete_node(root);
}

template <typename T>
Node<T>* RedBlackTree<T>::put(Node<T>* node, int key, T value) {
	if (node == NULL) {
		return new Node<T>(key, value);
	}

	if (key > node->get_key()) {
		node->set_right(put(node->get_right(), key, value));
        } else if (key < node->get_key()) {
		node->set_left(put(node->get_left(), key, value));
        } else {
		node->set_value(value);
        }

        node = reorganize_tree(node);

        return node;
}

template <typename T>
Node<T>* RedBlackTree<T>::reorganize_tree(Node<T>* node) {
	if (is_black(node->get_left()) && is_red(node->get_right())) {
		node = rotate_left(node);
	} else if (is_red(node->get_left()) && is_red(node->get_left()->get_left())) {
		node = rotate_right(node);
	}

	if (is_red(node->get_left()) && is_red(node->get_right())) {
		change_colors(node);
	}
	return node;	
}

template <typename T>
Node<T>* RedBlackTree<T>::rotate_left(Node<T>* node) {
	Node<T>* new_sub_root = node->get_right();
	node->set_right(new_sub_root->get_left());
	new_sub_root->set_left(node);
	if (node->get_color() == BLACK) {
		new_sub_root->set_color(BLACK);
		node->set_color(RED);
	}
	return new_sub_root;
}

template <typename T>
Node<T>* RedBlackTree<T>::rotate_right(Node<T>* node) {
	Node<T>* new_sub_root = node->get_left();
	node->set_left(new_sub_root->get_right());
	new_sub_root->set_right(node);
	if (node->get_color() == BLACK) {
		new_sub_root->set_color(BLACK);
		node->set_color(RED);
	}
	return new_sub_root;
}

template <typename T>
void RedBlackTree<T>::change_colors(Node<T>* node) {
	node->set_color(RED);
	node->get_left()->set_color(BLACK);
	node->get_right()->set_color(BLACK);
}

template <typename T>
bool RedBlackTree<T>::is_red(Node<T>* node) {
	return node == NULL ? false : node->get_color() == RED;
}

template <typename T>
bool RedBlackTree<T>::is_black(Node<T>* node) {
	return node == NULL ? true : node->get_color() == BLACK;
}

template <typename T>
Node<T>* RedBlackTree<T>::get(Node<T>* node, int key) {
	if (node == NULL) {
		return NULL;
	} else if (key > node->get_key()) {
		return get(node->get_right(), key);
	} else if (key < node->get_key()) {
		return get(node->get_left(), key);
	} else {
		return node;
	}
}

template <typename T>
void RedBlackTree<T>::delete_node(Node<T>* node) {
	if (node != NULL) {
		delete_node(node->get_left());
		delete_node(node->get_right());
		delete node;
	}
}
