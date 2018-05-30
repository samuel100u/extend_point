#ifndef EXTEND_HPP_INCLUDED
#define EXTEND_HPP_INCLUDED


#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class ExtendArea{

public:

    ExtendArea(map< int , vector<int> > &data);

    ExtendArea(map< int , vector<int> > &data, int from, int to);

    void enlarge_area();

    vector<vector <int>> get_result();

    void set_degree(const int & degree);

    void set_offset(const int & offset);


private:

    static int abs(int n);
   
    static bool cmp_unique (const vector<int> &i, const vector<int> &j);
    
    static bool cmp_sort (const vector<int> &i, const vector<int> &j);
    
    void mark_area(const vector<int> &i);
    
    void round(vector<int> &p);

    int grouping(int theta);

    int count_group(const vector<int> &i);

    vector<vector<int>> enlarge_point(vector<int> p);

    int offset_theta(int theta);

    
    vector<vector<int>> data;
    map<pair<int,int>,vector<int>> area;
    
    int degree = 5;
    int base = 10;
    int offset = 0;
};

#endif
