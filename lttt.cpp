
#include<iostream>
#include<string>
#include<cstring>
#include<math.h>
#include<vector>
#include<queue>
#include <unordered_map>

using namespace std;

void swap(float &a, float &b) {
    float temp = a;
    a = b;
    b = temp;
}
//sap xep
void sort(float arr[], int n,  char temp_text[]) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(arr[i] < arr[j]) {
				swap(arr[i], arr[j]);
				char temp = temp_text[j];
				temp_text[j] = temp_text[i];
				temp_text[i] = temp;
			}
        }
    }
}
//chieu dai l
int chieuDai(float x) {
    if(x == 0) return 1;
    return -log2(x);
}

// Ham tinh xac suat cong don
//a la p(xi), p la Pi
void probability(float a[], float p[], int n) {
    p[0] = 0;
    for(int  i = 1; i < n; i++) {
        p[i] = p[i - 1] + a[i - 1];
    }
}
//chuyen nhi phan tu Pi 
void binary(float p[], float p1[], float l[], float l1[], string str[], int n) {
    for(int i = 0; i < n; i++) {
        p1[i] = p[i];
        l1[i] = l[i];
        while(l1[i] > 0) {
            if(p1[i] * 2 >= 1) {
                str[i] += '1';
                p1[i] = p1[i] * 2 - 1;
            } else {
                p1[i] = p1[i] * 2;
                str[i] += '0';
            }
            l1[i]--;
        }
    }
}

void xoa1PhanTu(char a[], int &n, int viTriXoa) {
	for(int i = viTriXoa; i < n; i++) {
		a[i] = a[i + 1];
	}
	n--;
}
void xoaCacPhanTuTrungNhau(char a[], int &n) {
	for(int i = 0; i < n; i++) {
		for(int j = i + 1; j <n ; j++) {
			if(a[i] == a[j]) {
				xoa1PhanTu(a, n, j);
			}
		}
	}
}
void Shannon(char text[]){
	char temp_text[500];
	//copy sang mot chuoi moi
	strcpy(temp_text, text);
	int n = strlen(temp_text);
	xoaCacPhanTuTrungNhau(temp_text, n);
	float a[100];
	int count[100];
	for(int i = 0; i < n; i++) {
		count[i] = 0;
		for(int j = 0; j < strlen(text); j++) {
			if(temp_text[i] == text[j]) count[i]++;
		}
		a[i] = (float)count[i] / strlen(text);
	}
	
	    
        sort(a, n, temp_text);
		
        float p[1000];
        float p1[1000];
        float l[100];
        float l1[100];
        probability(a, p, n);
        string str[100];
        for(int i = 0; i < n; i++) {
            l[i] = chieuDai(a[i]);
        }
        binary(p, p1, l, l1, str, n);
        for(int i = 0; i < n; i++) {
            cout << "\n";
				cout << temp_text[i] << ": ";
               cout << str[i];
            }
		cout << "\nCac xac suat xuat hien cua tung ky tu: ";
	       for(int i = 0; i < n; i++) {
		     cout << a[i] <<" ";
	      }
		cout <<"\nChieu dai tu ma: ";
		for(int i = 0; i < n; i++) {
			cout << l[i] << " ";
		}
		
		float l_trungbinh = 0;
		for(int i = 0; i < n; i++) {
			l_trungbinh += l[i] * a[i];
		}
		
		cout << "\nChieu dai trung binh cua tu ma: " << l_trungbinh;
		float Hx = 0; //Entropy
		for(int i = 0; i < n; i++) {
			Hx += a[i] * log2(1 / a[i]);
		}
	
		cout << "\nKt = " << (float)Hx / l_trungbinh;
			cout << "\nChuoi da duoc ma hoa: " <<endl;
		for(int i = 0; i < strlen(text); i++) {
			for(int j = 0; j < n; j++) {
				if(text[i] == temp_text[j]) cout  << str[j];
			}
		}
}


 struct Node
{
	char ch;
	int freq;
	Node *left, *right;
};

// C???p ph??t m???t n??t c??y m???i

Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}


struct comp
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};


void encode(Node* root, string str,
			unordered_map<char, string> &huffmanCode)
{
	if (root == nullptr)
		return;

	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}


// X??y d???ng Huffman Tree 
void buildHuffmanTree(string text)
{
	// ?????m t???n s??? xu???t hi???n c???a k?? t??? v?? l??u n?? v??o map
	unordered_map<char, int> freq;
	for (char ch: text) {
		freq[ch]++;
	}

	// T???o m???t h??ng ?????i ??u ti??n ????? l??u tr??? c??c n??t tr???c ti???p c???a c??y huffman
	priority_queue<Node*, vector<Node*>, comp> pq;

	// T???o m???t n??t l?? cho m???i k?? t??? v?? th??m n?? ?????n h??ng ?????i ??u ti??n
	for (auto pair: freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	while (pq.size() != 1)
	{
		// Lo???i b??? hai n??t c?? m???c ????? ??u ti??n cao nh???t (t???n su???t th???p nh???t) t??? h??ng ?????i
		Node *left = pq.top(); pq.pop();
		Node *right = pq.top();	pq.pop();

		//T???o m???t n??t m???i v???i hai n??t n??y l?? con v?? v???i t???n su???t b???ng t???ng tu???n su???t c???a hai n??t
        // Th??m n??t m???i ?????n h??ng ?????i ??u ti??n
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}
	Node* root = pq.top();
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "\nMa Huffman :\n" << '\n';
	cout <<'\n';
	
	//T??nh x??c su???t xu???t hi???n c???a t???ng ph???n t???
	int i = 0;
	float a[100];
	for(auto it: huffmanCode) {
		a[i] =(float) freq[it.first] / text.length();
		i++;
	}
	//in ra m??n h??nh x??c su???t
	cout << "\nXac suat xuat hien cua cac phan tu: "<<endl;
	i = 0;
 	for (auto it: huffmanCode) {
		cout << it.first<< ": "<<a[i] <<endl;
		i++;
	}
	
	//T??nh chi???u d??i t??? m??
	int l[100];
	i = 0;
	for (auto pair: huffmanCode) {
		l[i] = (pair.second).length();
		i++;
	}
	//in ra m??n h??nh chi???u d??i t??? m??
	cout << "\nChieu dai tu ma: " << endl;
	i = 0;
	for (auto pair: huffmanCode) {
		cout << pair.first << ": " << l[i] << endl; 
		i++;
	}
	
	
	//T??nh chi???u d??i trung b??nh
	float l_trungbinh = 0;
	i = 0;
	for(auto pair: huffmanCode) {
		l_trungbinh += a[i] * l[i];
		i++;
	}
	cout <<"\nChieu dai trung binh: " <<l_trungbinh<<endl;
	float Hx = 0; //entropy
	i = 0;
	for(auto pair: huffmanCode) {
		Hx += a[i] * log2(1 / a[i]);
		i++;
	}
	cout << "\nKt = " << (float) Hx/ l_trungbinh << endl;
	for (auto pair: huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}
	

	cout << "\nChuoi ban dau :\n" << text << '\n';
	string str = "";
	for (char ch: text) {
		str += huffmanCode[ch];
	}

	cout << "\nChuoi da duoc ma hoa :\n" << str << '\n';	
}

int main() {
	string text = "Dai hoc Bach Khoa Ha Noi.";
	
	cout << "\nShannon: ";
	 char text_char[text.length() + 1]; 
 
    strcpy(text_char, text.c_str());
	Shannon(text_char);
    
    
    buildHuffmanTree(text);
	cout << "\t\t\t-END-";
    return 0;
}
