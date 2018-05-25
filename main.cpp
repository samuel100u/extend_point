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

    map<pair<int,int>, int> area;

    int degree = 10;
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
                mark_area(p);
            }
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

        vector<vector<int>> result;

        for (map<pair<int,int>,int>::iterator it=area.begin(); it!=area.end(); ++it){

            pair<int,int> p = it->first;

            result.push_back({p.first,p.second,it->second});

        }

        return result;
    }

    void debug(){
        for (map<pair<int,int>,int>::iterator it=area.begin(); it!=area.end(); ++it){

            pair<int,int> p = it->first;
            cout<<p.first<<","<<p.second<<","<< it->second<<endl;
        }
    }

private:

    static bool cmp_unique (const vector<int> &i, const vector<int> &j) {
        return i[0]==j[0]&&i[1]==j[1]&&i[2]==j[2];
    }

    static bool cmp_sort (const vector<int> &i, const vector<int> &j) {
        return i[0] < j[0] || (i[0]==j[0]&&i[1]==j[1]&&i[2]==j[2]);
    }

    void mark_area(const vector<int> &i){

        if ( area.find(make_pair(i[0],i[1])) == area.end() ) {
            area[make_pair(i[0],i[1])] = 0;
        } else {
            area[make_pair(i[0],i[1])]++;
        }
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


    map< int , vector<int> > data;




    return 0;
}
