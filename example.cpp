#include "extend.hpp"

int main(){
    
   map< int , vector<int> > data;

   data[1] = {1,2,3};
   data[2] = {10,2,4};

   ExtendArea e(data);
   
   e.set_degree(5);
   
   e.set_offset(20);

   e.enlarge_area();
   
   vector<vector<int>> result = e.get_result();
    
}
