#include<bits/stdc++.h>
using namespace std;

struct trie{
	int leaf;
	trie *child[26];
};

trie* New_node(){
	trie* temp = new trie();
	for(int i = 0 ; i < 26 ; i++){temp->child[i] = NULL;}
	temp->leaf = false;
	return temp;
}

trie* Root = New_node();

void InsertInTrie(string inp_s) {
	trie* temp_node = Root;
	int n = inp_s.size();

	for(char c : inp_s) {
		if (NULL != temp_node->child[c-'a']) {
			temp_node = temp_node->child[c-'a'];
		} else {
			temp_node->child[c-'a'] = New_node();
			temp_node = temp_node->child[c-'a'];
		}
	}

	temp_node->leaf = true;
}

pair<int , trie*> FindInTrie(string inp_s) {
	int len = 0;
	bool ok = true;
	trie* temp_node = Root;

	for(char c : inp_s) {
		if (NULL != temp_node->child[c-'a']) {
			len++;
			temp_node = temp_node->child[c-'a'];
		} else {
			ok = false;
			break;
		}
	}

	//if (ok && temp_node->leaf) {return {len , temp_node};}
	return {len , temp_node};
}

bool CanExtend(trie* node) {
	for(int i = 0 ; i < 26 ; i++){
		if (NULL != node->child[i]) {return true;}
	}
	return false;
}

vector<string> answer;
int no_sugg = 20;

void dfs(trie* node , string curr) {
	if (answer.size() >= no_sugg) {return;}
	if (node->leaf)	 {
		answer.push_back(curr);
	}

	for(int i = 0 ; i < 26 ; i++){
		if (node->child[i] != NULL) {
			dfs(node->child[i] , curr+(char)('a'+i));
		}
	}
}

void IsHavingSuggestion(string inp_s){
	answer = vector<string>();

	trie* temp_node = Root;
	auto val = FindInTrie(inp_s);
	int n = inp_s.size();

	if (CanExtend(val.second) && val.first == n){
		dfs(val.second , inp_s);
		for(string s : answer){
			cout << "-> " << s << endl;
		}
	} else {
		if (val.first == n && val.second->leaf) {
			cout << "No recommendations , It is itself a word no one else similar to it." << endl;
		} else {
			cout << inp_s << " Does not exists!" << endl;
		}
	}
}

int main(){
	ifstream vals ("all_words.txt");
	string temp;
	vector<string> v;

	if (vals.is_open()) {
		while(getline(vals , temp)) {
			v.push_back(temp);
		}
		vals.close();
	}

	for(string x : v){
		InsertInTrie(x);
	}

	cout << "REMEBER :: " << endl;
	cout << "Edit maximum suggestions?\tPress 1" << endl;
	cout << "Exit ?\t\t\t\t\tPress 0" << endl << endl;

	while(1){
        cout << "Enter the word / country / place etc.. for which you want the suggestions." << endl;
        string s;
        cin >> s;

        if (s == "1") {
            cout << "\nEnter number of suggestions you may want :: ";
            int x;
            cin >> x;

            no_sugg = x;
        } else if (s == "0") {
            cout << "\n\tThank You!" << endl;
            break;
        } else {
            transform(s.begin() , s.end() , s.begin() , ::tolower);
            IsHavingSuggestion(s);
        }
	}

	return 0;
}
