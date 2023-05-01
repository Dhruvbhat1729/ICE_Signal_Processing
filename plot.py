import matplotlib.pyplot as plt
import numpy as np

# Open the text file and read the data
with open('orignal_signals.txt', 'r') as file:
    data = file.read().splitlines()

# Convert the data from string to fl
data = data[0].split(' ')
data = [float(x) for x in data if x!= '']

with open('orignal_signals_with_noise.txt', 'r') as file:
    data2 = file.read().splitlines()
data2 = data2[0].split(' ')
data2 = [float(x) for x in data2 if x!= '']


with open('denoised.txt', 'r') as file:
    data3 = file.read().splitlines()
data3 = data3[0].split(' ')
data3 = [float(x) for x in data3 if x!= '']

# Create a list of x-coordinates (assuming the data points are evenly spaced)
x =  np.arange(0,len(data[:100]),0.0001)[0:len(data[:100])]

# Plot the data[:100] as a line graph
plt.plot(x, data[:100],label='original')
plt.plot(x, data2[:100],label='noise',alpha=0.85)
plt.plot(x, data3[:100],label='denoised')

# Add labels and title to the graph
plt.xlabel('Data Point')
plt.ylabel('Value')
plt.title('Data Plot')
plt.legend()

# Display the graph
plt.show()
