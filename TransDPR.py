# TransDPR tool: Design Pattern Recognition using Programming Language models
#
# License: MIT
#
# This file contains is the pipeline to extract embeddings and use them to calculate
# distances to Singleton and Prototype patterns

# In[1]:

# imports
import tensorflow as tf
import tensorflow_hub as hub
import tensorflow_text as text

import pandas as pd

# read the file with the data to be analyzed
df1 = pd.read_csv("data/final.csv")




# In[4]:
# show the data and a bit of summary
df1.head(5)

print(df1['class'].value_counts())
print(df1.shape)


# In[54]:
# create prediction classes
X1, y1 = df1.iloc[:, :-1].values, df1.iloc[:, -1].values
print(X1.shape, y1.shape)

# In[22]:
# instantiate the models

from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score

# split the data into train and test
X1_train, X1_test, y1_train, y1_test = train_test_split(X1, y1, test_size=0.2, random_state=1)
print(X1_train.shape, X1_test.shape, y1_train.shape, y1_test.shape)

# In[23]:
# train the model - first Random Forest
model = RandomForestClassifier(random_state=1)
model.fit(X1_train, y1_train)


# In[24]:
# make inference and calculate accuracy
y1rf = model.predict(X1_test)
acc_rf = accuracy_score(y1_test, y1rf)

print(y1rf)
print('Accuracy: %.3f' % acc_rf)


# In[25]:
# train the logistic regression model
from sklearn.linear_model import LogisticRegression
logisticRegr = LogisticRegression()
logisticRegr.fit(X1_train, y1_train)

# and evaluate the accuracy
y1lg = logisticRegr.predict(X1_test)
acc_lg = logisticRegr.score(X1_test, y1_test)

print(y1lg)
print(acc_rf )


# In[27]:
# analyze the data from the industrial partner
import pandas as pd
df2 = pd.read_csv("vc_test3.csv")
df2.head(5)


# In[28]:
# remove the name of the module from the dataframe
# as it makes the model learn the name instead
df2 = df2.drop(['module'], axis=1)


# In[31]:
X2, y2 = df2.iloc[:, :-1].values, df2.iloc[:, -1].values


# In[32]:
# make the inference
y2rf = model.predict(X2)

print(y2rf)



# In[34]:
# make the inference using the logistic regression model
y2lg = logisticRegr.predict(X2)
print(y2lg)



# In[44]:
# analyze the data from the industrial partner with the
# superficially created non-singleton programs
df3 = pd.read_csv("final_minus_example.csv")

df3.head(5)
print(df3['class1'].value_counts())
print(df3['class'].value_counts())
print(df3.shape)


# In[51]:
# remove the name of the module from the dataframe
df3 = df3.drop(['class1'], axis=1)


# In[57]:
X3, y3 = df3.iloc[:, :-1].values, df3.iloc[:, -1].values
print(X3.shape, y3.shape, X1.shape, y1.shape)


# In[58]:
# training the models
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score
X3_train, X3_test, y3_train, y3_test = train_test_split(X3, y3, test_size=0.2, random_state=1)
print(X3_train.shape, X3_test.shape, y3_train.shape, y3_test.shape)


# In[59]:


model = RandomForestClassifier(random_state=1)
model.fit(X3_train, y3_train)


# In[60]:


y3rf = model.predict(X3_test)
print(y3rf)
acc_rf = accuracy_score(y3_test, y3rf)
print('Accuracy: %.3f' % acc_rf)


# In[61]:


from sklearn.linear_model import LogisticRegression
logisticRegr = LogisticRegression()
logisticRegr.fit(X3_train, y3_train)


# In[62]:


y3lg = logisticRegr.predict(X3_test)
print(y3lg)
acc_lg = logisticRegr.score(X3_test, y3_test)
print(acc_lg )


# In[63]:


y3lg = logisticRegr.predict(X2)
print(y3lg)


# In[64]:


y3rf = model.predict(X2)
print(y3rf)


# In[ ]:




