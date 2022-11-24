#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
struct node{
    int frequency;
    node*next;
    string name;
    node(string name="")
    {
        this->name=name;
        this->frequency=0;
        this->next=nullptr;
    }
};
class Search_engine{
    vector<node>cap;
    int size;
public:
    Search_engine()
    {
       // cap.push_back(nullptr);
        size=0;
    }
    int count_total_words(ifstream&fin,string filename)
    {
        fin.open(filename);
        string str;
        if(!fin)
            cout<<"File Not Found\n";
        else {
            while(!fin.eof())
            {
                //32–47 / 58–64 / 91–96 / 123–126
               getline(fin,str,'\n');
               for(int i=0;i<=str.length();i++)
               {
                   if(str[i]==' ' || str[i]=='.' &&!(str[i+1]!='.' && str[i]!=' '))
                       this->size++;
               }
               str="";
            }
        }
        return this->size;
    }
    void initialize()
    {
        cap.reserve(size);
        for(int i=0;i<size;i++)
            cap.push_back(node());
    }
    int get_hash_code(string str)
    {
        int hash=0;
        for(int i=0;i<=str.length();i++)
        {
            if(str[i]!=' ' || str[i]!='.' || str[i]!=',' )
            hash+=int(str[i]);
        }
        return hash%size;

    }
    int Get_size()
    {
        return this->size;
    }
    void insert(int i,string s)
    {
       if(cap[i].frequency==0)
       {
           node n(s);
           cap[i]=n;
           cap[i].frequency+=1;
           return;
       }
       if(cap[i].name.compare(s) == 0)
       {
           cap[i].frequency+=1;
           return;
       }
       if(cap[i].frequency!=0)
       {
           node n=cap[i];
           while(n.next!=nullptr)
               n=*n.next;
           node p(s);
           p.frequency+=1;
           n.next=&p;
           return;
       }
    }
    void make_hash_array(string filename)
    {
        ifstream fin;
        fin.open(filename);
        string str="";
        string s="";
        while(!fin.eof()) {
            getline(fin, str, ' ');
            if(str[str.length()-1]>=32 && str[str.length()-1]<=47 ||(str[str.length()-1]>=58 && str[str.length()-1]<=64) || (str[str.length()-1]>=91 && str[str.length()-1]<=96) || (str[str.length()-1]>=123 && str[str.length()-1]<=126))
                str=str.substr(0,str.length()-1);
            if(str[str.length()-1]>=32 && str[str.length()-1]<=47 ||(str[str.length()-1]>=58 && str[str.length()-1]<=64) || (str[str.length()-1]>=91 && str[str.length()-1]<=96) || (str[str.length()-1]>=123 && str[str.length()-1]<=126))
                str=str.substr(0,str.length()-1);
            //32–47 / 58–64 / 91–96 / 123–126
            if(str[0]>=32 && str[0]<=47 || (str[0]>=58 && str[0]<=64) ||(str[0]>=91 && str[0]<=96) ||(str[0]>=123 && str[0]<=126))
                str=str.substr(1,str.length());
            if(str[0]>=32 && str[0]<=47 || (str[0]>=58 && str[0]<=64) ||(str[0]>=91 && str[0]<=96) ||(str[0]>=123 && str[0]<=126))
                str=str.substr(1,str.length());
            this->insert(get_hash_code(str),str);
            str="";
        }
        fin.close();
    }
    void Search(int i,string str)
    {
        if(cap[i].name.compare(str) == 0)
        {
            cout<<cap[i].name<<"  "<<cap[i].frequency<<endl;
            return;
        }
        node*t=&cap[i];
        while(t)
        {
            if(t->name.compare(str) == 0)
            {
                cout<<cap[i].name<<"  "<<cap[i].frequency<<endl;
                return;
            }
            t=t->next;
        }
    }
    void delete_Str(int i,string str)
    {
        if(cap[i].name.compare(str) == 0)
        {
            cout<<"Deleted Successfully\n";
            cap[i].frequency=0;
            cap[i].name="";
            return;
        }
        node*t=&cap[i];
        while(t)
        {
            if(t->name.compare(str) == 0)
            {
                cout<<"Deleted Successfully\n";
                t->frequency=0;
                t->name="";
                return;
            }
            t=t->next;
        }
    }
    void print()
    {
        for(int i=0;i<size;i++) {
            if(cap[i].frequency!=0)
            {
                node*t=&cap[i];
                while(t)
                {
                    cout << t->name << " " << t->frequency << "   ";
                    t=t->next;

                }
                if(i%10==0)
                    cout<<endl;
            }

        }
    }
};
int main()
{
    ifstream fin;
    Search_engine*s=new Search_engine();
    cout<<"Total Words are:-"<<s->count_total_words(fin,"data1.txt")<<endl;
    s->initialize();
    s->make_hash_array("data1.txt");
  s->print();
  cout<<endl;
   cout<<"Searching I :-\n";
    s->Search(s->get_hash_code("I"),"I");
    cout<<"Deleting I :-\n";
    s->delete_Str(s->get_hash_code("I"),"I");
    cout<<"Searching I Again :-\n";
    s->Search(s->get_hash_code("I"),"I");
    return 0;
}