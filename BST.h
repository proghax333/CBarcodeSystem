
#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <time.h>

#include "pair.h"
#include "UPC.h"

using namespace std;

template<class PairType>
class Node :
	public Pair<typename PairType::key_type,
				typename PairType::value_type>
{
	public:
		shared_ptr<Node<PairType>> left = nullptr;
		shared_ptr<Node<PairType>> right = nullptr;
		Node() = default;
		
		Node(const PairType& pair) {
			this->key = pair.key;
			this->value = pair.value;
		}
		
		virtual ~Node() { }
};

template<class PairType>
class BST {
	public:
		using key_type = typename PairType::key_type;
		using value_type = typename PairType::value_type;
		using NodeType = Node<PairType>;
		
		BST() = default;
		
		shared_ptr<NodeType> get(const key_type& key) const {
			return get(root, key);
		}
		
		void put(PairType& p) {
			if(root != nullptr) {
				putRecursive(root, p);
			} else {
				root = make_shared<NodeType>(p);
			}
		}
	private:
		// Root node of the BST
		shared_ptr<NodeType> root = nullptr;
		
		/* BST Get Recursive Helper Function */
		shared_ptr<NodeType> get(const shared_ptr<NodeType>& node, const key_type& key) const {
			if(node != nullptr) {
				if(key == node->key) {
					return node;
				} else if(key < node->key) {
					auto result = get(node->left, key);
					return result;
				} else {
					auto result = get(node->right, key);
					return result;
				}
			}
			return nullptr;
		}
		
		/* BST Put Recursive Helper Function */
		void putRecursive(shared_ptr<NodeType>& node, PairType& pair) {
			if(node != nullptr) {
				if(pair.key < node->key) {
					if(node->left == nullptr) {
						node->left = make_shared<NodeType>(pair);
					} else {
						putRecursive(node->left, pair);
					}
				} else if(pair.key > node->key) {
					if(node->right == nullptr) {
						node->right = make_shared<NodeType>(pair);
					} else {
						putRecursive(node->right, pair);
					}
				}
			}
		}
};

/*
	getUPC() : Parses a CSV entry and creates a
		UPC object.
*/
UPC getUPC(const string& line) {
	string key, value;
	UPC upc;
	stringstream seperator(line);
	
	getline(seperator, key, ',');
	getline(seperator, value);
	
	upc.key = stoll(key.c_str(), 0, 10);
	upc.value = std::move(value);
	
	return upc;
}

/*
	buildTree() : Creates binary search tree,
		reads all the data from the file, parses it,
		and adds the entries to the binary search tree.
*/
BST<UPC> buildTree(const string& filename) {
	BST<UPC> tree;
	ifstream inputFile(filename, ios::in);
	
	if(inputFile.bad() || !inputFile.is_open()) {
		throw "Error while opening the file!";
	}
	
	string line;
	// Header information
	getline(inputFile, line);
	
	// All items
	while(getline(inputFile, line)) {
		UPC p = getUPC(line);
		tree.put(p);
	}
	
	return tree;
}

/*
	performSearchBST() :
		Searches the binary search tree,
			prints out the entry if found
		Else it prints "Not found".
*/
template<class PairType>
void performSearchBST(const BST<PairType>& tree, const PairType& key) {
	clock_t t;
	t = clock();
	
	auto result = tree.get(key.key);
	
	t = clock() - t;
	if(result != nullptr) {
		cout << result->value << endl;
		cout << "Lookup Time: " << t << " miliseconds" << endl;
	} else {
		cout << "Not found" << endl;
	}
}
