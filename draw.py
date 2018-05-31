import matplotlib
import matplotlib.pyplot as plt

import sys, time, xmlrpclib



proxy =  xmlrpclib.ServerProxy("http://localhost:8080/RPC2") 


data = proxy.retrieve_map()

fig1 = plt.figure(1)
ax1 = fig1.add_subplot(111)


for d in data:

	if d[2]==0 :
		c='#DAF7A6'
	elif d[2]==1 :
		c='#FFC300'
	elif(d[2]==2):
		c='#FF5733'
	elif(d[2]==3):
		c='#C70039'
	elif(d[2]==4):
		c='#900C3F'
	else:
		c='#581845'
	
	square = matplotlib.patches.Rectangle((d[0], d[1]), 10, 10, color=c)
	ax1.add_patch(square)
	
	
maxX = max([d[0] for d in data])+10
minX = min([d[0] for d in data])-10

maxY = max([d[1] for d in data])+10
minY = min([d[1] for d in data])-10

a = max(maxX-minX,maxY-minY)

maxX = maxX+a-(maxX-minX)
maxY = maxY+a-(maxY-minY)

ax1.set_xlim([minX, maxX])
ax1.set_ylim([minY, maxY])


plt.show()
