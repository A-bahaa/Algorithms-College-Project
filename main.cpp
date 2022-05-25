#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll N = 1e5 + 5, MOD = 1e9 + 7, oo = 1e18;
map<int, set<int> > adj_1, adj_2;
vector<pair<int, int> > influencers;
int str_int(string s)
{
    int ans = 0;
    for (int i = 0; i < (int) s.size(); i++)
        ans = (ans * 10) + (s[i] - '0');
    return ans;
}

void build_tsk_1()
{
    for (auto x : adj_2)
    {
        int ft = x.first, sc = x.second.size();
        influencers.push_back({sc, ft});
    }
    sort(influencers.begin(), influencers.end());
    reverse(influencers.begin(), influencers.end());
}

void tsk_1()
{
    int number;
    cout << "Enter the rank of influencer you want : " << endl;
    cin >> number;
    number--;
    cout << "The influencer ID = " << influencers[number].second;
    cout << " and the number of followers of the influencer = " << influencers[number].first << endl;
}
void tsk_2()
{
    int number;
    cout << "Enter the ID of influencer you want : " << endl;
    cin >> number;
    int mx = 0, user = -1;
    map<int, int> freq;
    for (auto x:adj_1[number])
    {
        for (auto y:adj_2[x])
        {
            if (y != number && (adj_1[number].lower_bound(y) == adj_1[number].end() || *(adj_1[number].lower_bound(y)) != y))
            {
                freq[y]++;
                if (freq[y] > mx)
                {
                    mx = freq[y];
                    user = y;
                }
            }
        }
    }
    if (user == -1) cout << "No recommendations" << endl;
    else cout << "The ID of influencer : " << user <<" and the number of common influencer : "<<mx<< endl;
}
void tsk_3()
{
    vector<int>mutual;
    int number_1, number_2;
    cout << "Enter the ID of the first person and the ID of the second one : " << endl;
    cin >> number_1 >> number_2;
    while(number_1==number_2)
    {
        cout<<"Enter two different IDs :"<<endl;
        cin>>number_1>>number_2;
    }

    auto it_1 = adj_1[number_1].begin(), it_2 = adj_1[number_2].begin() ;

    auto lst_1 = adj_1[number_1].end(), lst_2 = adj_1[number_2].end() ;

    while(it_1!=lst_1 && it_2!=lst_2)
    {

        if(*it_1<*it_2)
            it_1++;
        else if(*it_1>*it_2)
            it_2++;
        else
        {
            mutual.push_back(*it_1);
            it_1++;
            it_2++;
        }

    }
    if(mutual.size()!=1)
    {
        if(!mutual.empty())
            cout<<"There are "<<mutual.size()<<" mutual friends between ID = "<<number_1<<" and ID = "<<number_2<<" and the list of mutual friends is : "<<endl;
        else
            cout<<"There are "<<mutual.size()<<" mutual friends between ID = "<<number_1<<" and ID = "<<number_2<<endl;
    }
    else
        cout<<"There are "<<mutual.size()<<" mutual friend between ID = "<<number_1<<" and ID = "<<number_2<<" and the list of mutual friends is : "<<endl;
    if(!mutual.empty())
    {
        for(auto x : mutual)
            cout<<x<<'\n';
        cout<<endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    ifstream infile("twitter.csv");
    if (infile.fail())
    {
        cerr << "Error Opening file" << endl;
        exit(1);
    }
    string c;
    while (!infile.eof())
    {
        string a, b;
        infile >> c;
        a = "", b = "";
        int idx = 0;
        for (int i = 0; i < (int) c.size(); i++)
        {
            if (c[i] == ',')
            {
                idx = i + 1;
                break;
            }
            a.push_back(c[i]);
        }
        for (int i = idx; i < c.size(); i++)
            b.push_back(c[i]);
        int x = str_int(a);
        int y = str_int(b);
        if(x==y)
            continue;
        adj_1[x].insert(y);
        adj_2[y].insert(x);
    }
    infile.close();
    build_tsk_1();
    while (1)
    {
        cout << "Enter number of task: " << endl;
        string num;
        cin >> num;
        if (num == "1") tsk_1();
        else if (num == "2") tsk_2();
        else if(num=="3") tsk_3();
        else if (num == "0") break;
        else cout << "Invalid input!" << endl;
    }
    return 0;
}
