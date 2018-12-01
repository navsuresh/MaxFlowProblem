#!/usr/bin/env python
# coding: utf-8

# In[1]:


import matplotlib.pyplot as plt


# In[8]:


def density(x):
    v=x[0]
    e=x[1]
    return e/(v*(v-1))


# In[40]:


ver=[100,200,500,1000,2000]


# In[41]:


edges=[2500,5000,20000,50000,100000]


# In[9]:


g=[(100,2500),(100,5000),(500,5000),(500,20000),(1000,20000),(2000,50000),(2000,100000)]


# In[11]:


density_g=list(map(density,g))


# In[13]:


density_g


# In[14]:


ford_times=[0.00299298,0.003874956667,0.0212,0.0612792,0.140597,0.611492,0.899139]


# In[47]:


plt.xlabel("Density of graph")
plt.ylabel("Time")
plt.plot(density_g,ford_times,'r+--')
plt.show()


# In[ ]:





# In[18]:


plt.xlabel("Density of graph")
plt.ylabel("Time")
plt.plot(ver,ford_times,'r+--')
plt.show()


# In[34]:


plt.xticks(density_g, [1,2,3,4,5,6,7])


# In[33]:


plt.set_xlim=density_g[6]


# In[38]:


plt.locator_params(axis='x', nticks=20)


# In[ ]:






dinic = 
[0.00710659,
 0.014059413,
 0.01047053,
 0.18965075,
 0.0228827,
 0.0857504,
 0.237616
]

pr = 
[ 0.384860333,
  0.673989333,
  15.75022143,
  35.8350915,
  0.634071,
  2.99278,
  5.03422
]

rtf =
[ 0.215148,
  0.541367333,
  1.480116207,
  7.52464075,
  0.0626332,
  0.256205,
  0.594326
]