import matplotlib.pyplot as plt
from scipy import interpolate 
import numpy as np
import math

#Generate 1D LUT
x1d = np.linspace(-10,50,100);
y1d = np.zeros((len(x1d)),dtype=np.float);
for xi in range(0,len(x1d)):
    y1d[xi] = 5*math.sin(x1d[xi]/5) + abs(x1d[xi]);

LUT1D = interpolate.interp1d(x1d,y1d);

#Generate 2D LUT
x2d = np.linspace(-10,50,100);
y2d = [1,5,10];
z2d = np.zeros((len(y2d),len(x2d)),dtype=np.float);

for xi in range(0,len(x2d)):
    for yi in range(0,len(y2d)):
        z2d[yi][xi] = y2d[yi] + 5*math.sin(x2d[xi]/5) + abs(x2d[xi]);

LUT2D = interpolate.interp2d(x2d,y2d,z2d, kind='linear');

#Generate test Points
numTestPoints = 1000;
LUT1D_In = (max(x1d)-min(x1d))*np.random.rand(numTestPoints)+min(x1d);
LUT1D_Out = np.zeros(numTestPoints,dtype=np.float)
for i in range(0,numTestPoints):
    LUT1D_Out[i] = LUT1D(LUT1D_In[i])
 
LUT2D_In1 = (max(x2d)-min(x2d))*np.random.rand(numTestPoints)+min(x2d);
LUT2D_In2 = (max(y2d)-min(y2d))*np.random.rand(numTestPoints)+min(y2d);
LUT2D_Out = np.zeros(numTestPoints,dtype=np.float);
for i in range(0,numTestPoints):
    LUT2D_Out[i] = LUT2D(LUT2D_In1[i],LUT2D_In2[i])
    
#Plot the Test Tables
plt.plot(x1d,y1d);
plt.show();

plt.plot(x2d,np.transpose(z2d));
plt.show();

# Read the test hardness into a string
with open ("test_harness_template.cpp", "r") as myfile:
    data=myfile.readlines()
data = "".join(data);

# Put 1D table in template file
data = data.replace( "_1D_XDATA_", ", ".join(map(str, x1d)) )
data = data.replace( "_1D_XSIZE_", str(len(x1d)) )
data = data.replace( "_1D_ZDATA_", ", ".join(map(str, y1d)) )
data = data.replace( "_1D_ZSIZE_", str(len(y1d)) )

# Put 1D test data in file
data = data.replace( "_1D_NUMTESTPTS_", str(numTestPoints ))
data = data.replace( "_1D_TESTDATA_IN_", ", ".join(map(str, LUT1D_In)) )
data = data.replace( "_1D_TESTDATA_OUT_", ", ".join(map(str, LUT1D_Out)) )


# Put 2D table in template file
data = data.replace( "_2D_XDATA_", ", ".join(map(str, x2d)) )
data = data.replace( "_2D_XSIZE_", str(len(x2d)) )
data = data.replace( "_2D_YDATA_", ", ".join(map(str, y2d)) )
data = data.replace( "_2D_YSIZE_", str(len(y2d)) )
z2d_string = []
for yi in range(0,len(y2d)):
    z2d_string.append( "{" + ", ".join(map(str, z2d[yi])) + "}");
data = data.replace( "_2D_ZDATA_", ",\n".join(map(str,z2d_string)));
data = data.replace( "_2D_ZSIZE_", str(len(z2d)) )

# Put 2D test data in file
data = data.replace( "_2D_NUMTESTPTS_", str(numTestPoints ))
data = data.replace( "_2D_TESTDATA_IN1_", ", ".join(map(str, LUT2D_In1)) )
data = data.replace( "_2D_TESTDATA_IN2_", ", ".join(map(str, LUT2D_In2)) )
data = data.replace( "_2D_TESTDATA_OUT_", ", ".join(map(str, LUT2D_Out)) )

# WRite Test Harness
fout = open("test_harness.cpp","w");
fout.write( data);
fout.close();