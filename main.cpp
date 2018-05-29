#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class ExtendArea{

public:

    vector<vector<int>> data;

    map<pair<int,int>,vector<int>> area;

    int degree = 5;
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



    vector<vector <int>> get_result(){

        vector<vector<int>> result;

        for (map<pair<int,int>,vector<int>>::iterator it=area.begin(); it!=area.end(); ++it){

            pair<int,int> p = it->first;

            result.push_back({p.first,p.second,count_group(it->second)});

        }

        return result;
    }


private:

    static int abs(int n){
        return n>=0 ? n : -n;
    }

    static bool cmp_unique (const vector<int> &i, const vector<int> &j){
        return i[0]==j[0]&&i[1]==j[1]&& abs(i[2]-j[2])<30;
        //return i[0]==j[0]&&i[1]==j[1]&& i[2]==j[2];
    }

    static bool cmp_sort (const vector<int> &i, const vector<int> &j) {
        return i[0] < j[0] || (i[0]==j[0]&&i[1]==j[1]&&i[2]==j[2]);
    }

    void mark_area(const vector<int> &i){

        if ( area.find(make_pair(i[0],i[1])) == area.end() ) {
            area[make_pair(i[0],i[1])] = {0,0,0,0};
            area[make_pair(i[0],i[1])][i[2]]=1;

        } else {
            area[make_pair(i[0],i[1])][i[2]]++;
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


    int grouping(int theta){

        int group = 0;

        if(theta >= 0 && theta<=90){
            group = 0;
        }else if(theta >= 90 && theta<=180){
            group = 1;
        }else if(theta >= -180 && theta<=-90){
            group = 2;
        }else{
            group = 3;
        }
        return  group;
    }

    int count_group(const vector<int> &i){

        int c = 0;

        for(auto it = i.begin();it!=i.end();it++){


            if(*it != 0) c++;

        }

        return c-1;


    }

     vector<vector<int>> enlarge_point(vector<int> p){

        vector<vector<int>> r;

        int d = base*degree;

        int group = grouping(p[2]);

        for(int i=p[0]-d;i<=p[0]+d;i+=base){

            for(int j=p[1]-d;j<=p[1]+d;j+=base){
                r.push_back({i,j,group});
            }
        }

        return r;
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

    vector<vector<int>> r = e.get_result();

    ofstream myfile;
    myfile.open ("C:\\Users\\Samuel\\Downloads\\example.txt");


    for(auto it = r.begin();it!=r.end();it++){

        myfile<<it[0][0]<<","<<it[0][1]<<","<<it[0][2]<<endl;

    }

    myfile.close();


    return 0;
}
