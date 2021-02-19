
#include <iostream>
#include <memory>
#include <string>

#include "BST.h"
#include "UPC.h"

int main() {
	const string file_path = "files/";
	string filename = file_path + "database.csv";
	BST<UPC> tree = buildTree(filename);  //build binary search tree of UPC objects
	
	string code;
	cout << "Please enter a UPC code(! to quit): ";
	cin >> code;
	while (code != "!") {
		long long entry = stoll(code); //convert user inputted string to type long int
		UPC key(entry);
		performSearchBST(tree, key);
		
		cout << "\nPlease enter a UPC code(! to quit): ";
		cin >> code;
	}

	return 0;
} 
