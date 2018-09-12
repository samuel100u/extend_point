#include "extend.hpp"

ExtendArea::ExtendArea(map< int , vector<int> > &data){

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


ExtendArea::ExtendArea(map< int , vector<int> > &data, int from, int to){

    map<int , vector<int>>::iterator it;

    
    for ( it = data.begin(); it != data.end(); it++ )
    {

        if( (from <= to && it->second[2]>= from && it->second[2]<=to) ||
                (from > to && (it->second[2]>= from || it->second[2]<=to))
            )
        {

            round(it->second);
            this->data.push_back(it->second);
        }

    }
    
    
    

    sort(this->data.begin(), this->data.end(),cmp_sort);

    this->data.erase(
                     unique(this->data.begin(), this->data.end(), cmp_unique),
                     this->data.end());
}


void ExtendArea::enlarge_area(){

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



vector<vector <int>> ExtendArea::get_result(){

    vector<vector<int>> result;

    for (map<pair<int,int>,vector<int>>::iterator it=area.begin(); it!=area.end(); ++it){

        pair<int,int> p = it->first;

        result.push_back({p.first,p.second,count_group(it->second)});

    }

    return result;
}

void ExtendArea::set_degree(const int & degree)
{
    this->degree = degree;
}

void ExtendArea::set_offset(const int & offset){
    this->offset = offset%360;
}

int ExtendArea::abs(int n){
    return n>=0 ? n : -n;
}

bool ExtendArea::cmp_unique (const vector<int> &i, const vector<int> &j){
    return i[0]==j[0]&&i[1]==j[1]&& abs(i[2]-j[2])<30;
    //return i[0]==j[0]&&i[1]==j[1]&& i[2]==j[2];
}

bool ExtendArea::cmp_sort (const vector<int> &i, const vector<int> &j) {
    return i[0] < j[0] || (i[0]==j[0]&&i[1]==j[1]&&i[2]==j[2]);
}

void ExtendArea::mark_area(const vector<int> &i){

    if ( area.find(make_pair(i[0],i[1])) == area.end() ) {
        area[make_pair(i[0],i[1])] = {0,0,0,0};
        area[make_pair(i[0],i[1])][i[2]]=1;

    } else {
        area[make_pair(i[0],i[1])][i[2]]++;
    }
}

void ExtendArea::round(vector<int> &p){

    int x = (p[0]/base)*base;
    int y = (p[1]/base)*base;

    x = (p[0]-x>=(base/2) ? x+base: x);
    y = (p[1]-y>=(base/2) ? y+base: y);
    p[0] = x;
    p[1] = y;
}


int ExtendArea::grouping(int theta){


    int group = 0;

    int newTheta = offset_theta(theta);

    if(newTheta >= 0 && newTheta<=90){
        group = 0;
    }else if(newTheta >= 90 && newTheta<=180){
        group = 1;
    }else if(newTheta >= -180 && newTheta<=-90){
        group = 2;
    }else{
        group = 3;
    }
    return  group;
}

int ExtendArea::count_group(const vector<int> &i){

    int c = 0;

    for(auto it = i.begin();it!=i.end();it++){
        if(*it != 0) c++;
    }

    return c-1;
}

vector<vector<int>> ExtendArea::enlarge_point(vector<int> p){

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

int ExtendArea::offset_theta(int theta){

    int _theta = theta - offset;

    _theta  = _theta < -180 ?  360+_theta : _theta;
    _theta  = _theta > 180  ?  _theta-360 : _theta; 

    return _theta;
}
