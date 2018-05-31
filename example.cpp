#include <cstdlib>
#include <string>
#include <iostream>

#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>

#include "extend.hpp"

using namespace std;


vector<vector<int>> extend_area(){
   
   map< int , vector<int> > data;
   
   data[1] = {1,2,3};
   data[2] = {10,2,4};
   
   ExtendArea e(data);
   
   e.set_degree(5);
   e.set_offset(20);
   
   e.enlarge_area();
   
   vector<vector<int>> result = e.get_result();
   
   return result;
}

class RetrieveMap : public xmlrpc_c::method{
  
  public:
  
  void
    execute(xmlrpc_c::paramList const& paramList,
            xmlrpc_c::value *   const  retvalP){

         paramList.verifyEnd(0);
         
         vector<vector<int>> result = extend_area();
         
         xmlrpc_c::carray area;
         
         for(auto it = result.begin();it!=result.end();it++){
         
            vector<int> row = *it;
            
            xmlrpc_c::carray new_row = {
               xmlrpc_c::value_int(row[0]),
               xmlrpc_c::value_int(row[1]),
               xmlrpc_c::value_int(row[2])
               
            };
            
            area.push_back(xmlrpc_c::value_array(new_row));
         }
            
         
         *retvalP = xmlrpc_c::value_array(area);
    }
};

int main(){
    
    try {
        
        xmlrpc_c::registry myRegistry;

        xmlrpc_c::methodPtr const retrievemap(new RetrieveMap);
    
        myRegistry.addMethod("retrieve_map", retrievemap);

        xmlrpc_c::serverAbyss myAbyssServer(
            xmlrpc_c::serverAbyss::constrOpt()
            .registryP(&myRegistry)
            .portNumber(8090)
            .logFileName("/tmp/xmlrpc_log"));

        myAbyssServer.run();
        

    } catch (exception const& e) {
        cerr << "Client threw error: " << e.what() << endl;
    } catch (...) {
        cerr << "Client threw unexpected error." << endl;
    }

    return 0;
    
}