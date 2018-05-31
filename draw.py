
import sys, time, xmlrpclib



proxy =  xmlrpclib.ServerProxy("https://r-language-hibati.c9users.io:8080/RPC2") 


result = proxy.retrieve_map()