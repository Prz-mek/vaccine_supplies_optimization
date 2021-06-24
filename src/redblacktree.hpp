#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

enum Color {RED, BLACK};

template <typename T>
class Node {
	private:
		int key;
		T value;
		Color color;
		Node<T>* left;
		Node<T>* right;
	public:
		Node(int key, T value);
		int get_key();
		T get_value();
		void set_value(T value);
		Node<T>* get_left();
		void set_left(Node<T>* left);
		Node<T>* get_right();
		void set_right(Node<T>* left);
		Color get_color();
		void set_color(Color color);
};

template <typename T>
class RedBlackTree {
	private:
		Node<T>* root;
	public:
		RedBlackTree();
		void put(int key, T value);
		Node<T>* get(int key);
		void clear();
		~RedBlackTree();
	private:
		Node<T>* put(Node<T>* node, int key, T value);
		Node<T>* reorganize_tree(Node<T>* node);
		Node<T>* rotate_left(Node<T>* node);
		Node<T>* rotate_right(Node<T>* node);
		void change_colors(Node<T>* node);
		bool is_red(Node<T>* node);
		bool is_black(Node<T>* node);
		Node<T>* get(Node<T>* node, int key);
		void delete_node(Node<T>* node);
};

#endif
