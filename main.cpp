#include<bits/stdc++.h>

using namespace std;
int mnsup;
vector<set<string> >datatable;
set<string>products;
map<string, int>freq1;
void run()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else

#endif
}
set<int> splitting(string str)					//returns the sets integers of str ...
{
    set<int> st;
    int tmp ;
    stringstream ss(str);
    while (ss >> tmp)
    {
        st.insert(tmp);
    }
    return st;
}
// store L sets for every K
vector<set<int>>LL;
//stores for every set from C which indx transaction;
map<set<int>,vector<int>>IndT;
set<set<int>>Unique;
void check(set<int>a,set<int>b,int i)
{
    set<int>d=a;
    for(auto it:b)a.insert(it);
    if(b.size()+1==a.size()&&d.size()==d.size())
    {
        Unique.insert(a);
    }
}
int main()
{
    run();
    cin>>mnsup;
    string line;
    cin.ignore();
    int ind=0;
    while(getline(cin,line))
    {
        set<int>st=splitting(line);
        //splitting integers from every transaction
        //genration  C1;
        for(auto it:st)
        {
            set<int>sup;
            sup.insert(it);
            IndT[sup].push_back(ind);
        }
        ind++;
    }
    //rever stores for every transaction sets which was generated from L (a) to be using on C (a+1)
    map<int,set<set<int>>>rever;
    for(auto it:IndT)
    {
        if(it.second.size()>=mnsup)
        {
            LL.push_back(it.first);
            for(auto Ij:it.second)
            {
                rever[Ij].insert(it.first);
            }
        }
    }
    IndT.clear();
    int k=1;
    while(LL.size()>0)
    {
        cout<<"The "<<k<<" th LL has "<<LL.size()<<" Sets \n";
        for(auto Row:LL)
        {
            cout<<"Set ";
            for(auto col:Row)cout<<" : "<<col;
            cout<<endl;
        }
        for(int i=0; i<10; i++)cout<<"**";
        cout<<endl;
        // generat  C for k+1
        for(auto Nex:rever)
        {
            vector<set<int>>cop;// copy the sets which 'll be using to Generat  C
            for(auto i:Nex.second)cop.push_back(i);
            int indTrans=Nex.first;// index of current  transaction
            for(int i=0; i<cop.size(); i++)
            {
                for(int j=i+1; j<cop.size(); j++)
                {

                    check(cop[i],cop[j],indTrans);// check is valid two sets to be one and store the unique sets for current transaction
                }
            }
            for(auto it:Unique)
            {
                IndT[it].push_back(indTrans); // assign each set to current transaction
            }
            Unique.clear();
        }
        rever.clear();
        LL.clear();
        // repeating the process on 62th line
        for(auto it:IndT)
        {
            if(it.second.size()>=mnsup)
            {
                LL.push_back(it.first);
                for(auto Ij:it.second)
                {
                    rever[Ij].insert(it.first);
                }
            }
        }
        IndT.clear();
        k++;

    }

}
