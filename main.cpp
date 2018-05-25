#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class ExtendArea{

public:

    vector<vector<int>> data;
    vector<vector<int>> result;

    int degree = 4;
    int base = 10;

    ExtendArea(map< int , vector<int> > &data){

        map<int , vector<int>>::iterator it;

        for ( it = data.begin(); it != data.end(); it++ )
        {
              round(it->second);
              this->data.push_back(it->second);
        }

        sort(this->data.begin(), this->data.end(),cmp_sort);

        this->data.erase(
                         unique(this->data.begin(), this->data.end(), cmp_unique),
                         this->data.end());

    }

    void enlarge_area(){

        vector<vector<int>>::iterator it;
        for ( it = data.begin(); it != data.end(); it++ )
        {
            vector<vector<int>> small = enlarge_point(*it);

            for(auto it2 = small.begin(); it2 != small.end(); it2++){

                vector<int> &p = *it2;

                if(!mark_area(p)){
                    result.push_back(p);
                }
            }

            sort(result.begin(), result.end(),cmp_sort);
        }
    }

    vector<vector<int>> enlarge_point(vector<int> p){

        vector<vector<int>> r;

        int d = base*degree;

        for(int i=p[0]-d;i<=p[0]+d;i+=base){

            for(int j=p[1]-d;j<=p[1]+d;j+=base){

                r.push_back({i,j,0});
            }
        }

        return r;
    }

    vector<vector <int>> get_result(){
        return result;
    }

    void debug(){

        vector<vector<int>>::iterator it;
        for ( it = result.begin(); it != result.end(); it++ )
        {
            vector<int> &t = *it;
            cout<< t[0]
                <<","
                <<t[1]
                <<","
                <<t[2]
                <<endl;
        }
    }

private:

    static bool cmp_unique (const vector<int> &i, const vector<int> &j) {
        return i[0]==j[0]&&i[1]==j[1]&&i[2]==j[2];
    }

    static bool cmp_sort (const vector<int> &i, const vector<int> &j) {
        return i[0] < j[0] || (i[0]==j[0]&&i[1]==j[1]&&i[2]==j[2]);
    }

    bool mark_area(const vector<int> &i){

        vector<vector<int>>::iterator it;
        for ( it = result.begin(); it != result.end(); it++ )
        {
            vector<int> &t = *it;

            if(it[0][0]==i[0] && it[0][1]==i[1]){
                t[2]++;
                return true;
            }
        }

        return false;
    }

    void round(vector<int> &p){

        int x = (p[0]/base)*base;
        int y = (p[1]/base)*base;

        x = (p[0]-x>=(base/2) ? x+base: x);
        y = (p[1]-y>=(base/2) ? y+base: y);
        p[0] = x;
        p[1] = y;
    }
};

int main()
{
    ifstream infile("C:\\Users\\Samuel\\Downloads\\db888.txt");

    map< int , vector<int> > data;
    int a, b, c, d;
    while (infile >> a >> b >>c>>d)
    {
        data[a] = {b,c,d};
    }
    infile.close();

    ExtendArea e(data);

    e.enlarge_area();

    //e.debug();

    vector<vector<int>> r = e.get_result();

    ofstream myfile;
    myfile.open ("C:\\Users\\Samuel\\Downloads\\example.txt");


    for(auto it = r.begin();it!=r.end();it++){

        myfile<<it[0][0]<<","<<it[0][1]<<","<<it[0][2]<<endl;

    }

  
    myfile.close();


    return 0;
}
