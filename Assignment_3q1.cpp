#include <bits/stdc++.h>
using namespace std;
vector<pair<int, char>> frequency_Counter(string s)
{
    map<char, int> mp;
    for (int i = 0; i < s.size(); i++)
        mp[s[i]]++;
    vector<pair<int, char>> v;
    for (int i = 0; i < s.size(); i++)
    {
        if (mp[s[i]] != 0)
        {
            v.push_back(make_pair(mp[s[i]], s[i]));
            mp[s[i]] = 0;
        }
    }
    // for (int i = 0; i < v.size(); i++)
    //     cout << v[i].first << " " << v[i].second << endl;
    return v;
}
struct MinHeapHash
{
    char ch;
    int frequency;
    MinHeapHash *left, *right;
    MinHeapHash(char ch, int f)
    {
        this->ch = ch;
        this->frequency = f;
        this->left = this->right = nullptr;
    }
};
void insert(queue<MinHeapHash *> &q, MinHeapHash *n)
{
    if (q.empty() || q.front()->frequency >= n->frequency)
    {
        q.push(n);
        return;
    }
    MinHeapHash *t = q.front();
    q.pop();
    insert(q, n);
    q.push(t);
}
void get_vector(MinHeapHash *root, vector<pair<char, string>> &V, string str)
{
    if (!root)
        return;
    if (root->ch != '$')
    {
        pair<char, string> p;
        p.first = root->ch;
        p.second = str;
        V.push_back(p);
    }
    get_vector(root->left, V, str + "0");
    get_vector(root->right, V, str + "1");
}
void print(MinHeapHash *root, string str)
{
    if (!root)
        return;

    if (root->ch != '$')
        cout << root->ch << ": " << str << "\n";

    print(root->left, str + "0");
    print(root->right, str + "1");
}
vector<pair<char, string>> make_Huffman_tree(vector<pair<int, char>> v, int size)
{
    queue<MinHeapHash *> q;
    for (int i = 0; i < size; i++)
    {
        MinHeapHash *m = new MinHeapHash(v[i].second, v[i].first);
        q.push(m);
    }
    MinHeapHash *left, *right, *temp;
    while (q.size() != 1)
    {
        left = q.front();
        q.pop();
        right = q.front();
        q.pop();
        temp = new MinHeapHash('$', left->frequency + right->frequency);
        temp->left = left;
        temp->right = right;
        insert(q, temp);
    }
    print(q.front(), "");
    vector<pair<char, string>> V;
    get_vector(q.front(), V, "");
    return V;
}
string get_str(char ch, vector<pair<char, string>> V)
{
    for (int i = 0; i < V.size(); i++)
        if (ch == V[i].first)
            return V[i].second;
    return "";
}
void storing_in_file_bin(string str, vector<pair<char, string>> V)
{
    ofstream fout;
    fout.open("bin.txt", ios::out);
    for (int i = 0; i < str.size(); i++)
    {
        string s = get_str(str[i], V);
        fout << s;
        fout << " ";
    }
    fout.close();
}
char get_ch(string str, vector<pair<char, string>> V)
{
    for (int i = 0; i < V.size(); i++)
    {
        if (str.compare(V[i].second) == 0)
            return V[i].first;
    }
    return ' ';
}
void storing_in_file_string(vector<pair<char, string>> V)
{
    ifstream fin;
    fin.open("bin.txt");
    if (!fin)
        return;
    ofstream fout;
    fout.open("stringfile.txt", ios::out);
    string str;
    while (!fin.eof())
    {
        getline(fin, str, ' ');
        char ch = get_ch(str, V);
        fout << ch;
    }
}
int main()
{
    string str;
    ifstream fin;
    fin.open("data1.txt");
    if (!fin)
        exit;
    else
    {
        char ch = fin.eof();
        getline(fin, str, ch);
    }
    fin.close();
    vector<pair<int, char>> v = frequency_Counter(str);
    sort(v.begin(), v.end());
    cout << "__________________\n";
    vector<pair<char, string>> record;
    record = make_Huffman_tree(v, v.size());
    storing_in_file_bin(str, record);
    storing_in_file_string(record);

    return 0;
}