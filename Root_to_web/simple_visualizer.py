# web_visualizer/simple_visualizer.py UNDERSTAND AND RECONSTRUCT
import plotly.graph_objects as go
import numpy as np
from flask import Flask, render_template

app = Flask(__name__)

@app.route('/')
def quantum_showcase():
    # Load precomputed data from file
    x = np.loadtxt('output/x_values.txt')
    psi = np.loadtxt('output/wavefunction.txt')
    
    fig = go.Figure(data=[go.Scatter3d(
        x=x, y=np.zeros_like(x), z=np.abs(psi)**2,
        mode='markers',
        marker=dict(size=5, color=np.angle(psi))
    )])
    
    return render_template('showcase.html', plot=fig.to_html())

if __name__ == '__main__':
    app.run(port=5000)