import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Read wavefunction data from file
data = []
with open('OUTPUT/wavefunctions.dat', 'r') as f:
    for line in f:
        # Parse the line, keeping only x, real, and imag components
        parts = line.strip().split()
        if len(parts) >= 7:  # Ensure we have at least 7 values
            x = float(parts[0])
            real = float(parts[-2])  # Second last value
            imag = float(parts[-1])  # Last value
            data.append((x, real, imag))

# Convert to numpy arrays
x_vals = np.array([d[0] for d in data])
real_vals = np.array([d[1] for d in data])
imag_vals = np.array([d[2] for d in data])

# Calculate probability density
probability_density = real_vals**2 + imag_vals**2

# Normalize probability density for better visualization
probability_density /= np.max(probability_density)

# Create 3D visualization
fig = plt.figure(figsize=(12, 8))
fig.suptitle('Python alternative 3D wigner Visualization', fontsize=16)

# 3D Probability Density Plot
ax1 = fig.add_subplot(121, projection='3d')
ax1.plot(x_vals, np.zeros_like(x_vals), np.zeros_like(x_vals), 
         'k-', alpha=0.3, label='x-axis')
scatter = ax1.scatter(x_vals, np.zeros_like(x_vals), np.zeros_like(x_vals), 
                     c=probability_density, s=probability_density*100, 
                     cmap='viridis', alpha=0.7)
ax1.set_xlabel('X Position')
ax1.set_ylabel('Y')
ax1.set_zlabel('Z')
ax1.set_title('Probability Density along X-axis')
ax1.legend()
fig.colorbar(scatter, ax=ax1, label='Probability Density')

# Wavefunction Components Plot
ax2 = fig.add_subplot(122)
ax2.plot(x_vals, real_vals, 'b-', label='Real Part')
ax2.plot(x_vals, imag_vals, 'r-', label='Imaginary Part')
ax2.plot(x_vals, probability_density, 'g-', label='Probability Density')
ax2.set_xlabel('X Position')
ax2.set_ylabel('Value')
ax2.set_title('Wavefunction Components')
ax2.legend()
ax2.grid(True)

# Adjust layout and show
plt.tight_layout(rect=[0, 0, 1, 0.96])
plt.savefig("PHASE_SPACE_stuff/Beautiful_python_wave_stuff")
plt.show()