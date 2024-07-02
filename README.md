There were too many braincells lost on this project.
Written by Aryan*

<h1>QuLib</h1>
<h3>A C++ Quantum Mechanics Library</h3>

<h2>1. Introduction and Features</h2>
The main purpose of this library is to provide methods for physicists to numerically approach elementary quantum mechanics in a manner that is accurate, user-friendly, and of utmost importance, <strong>efficient</strong>.
<ul>
    <li>Schrodinger's equation solver using 4th order Runge Kutta methods for paired ordinary differential equations</li>
    <li>Expectation value computations</li>
    <li>Mathematical elements: linear algebra and complex number implementations</li>
</ul>

<h2>2. Schrodinger's equation solver</h2>
Background:
Schrodinger's equation (whose time-independent part I am refering to, of course) is a second-order partial differential equation that describes the properties (states) of a quantum particle.
$`
-\frac{\hbar^2}{2\mu}\nabla^2 \psi(\vec{r}) + V(\vec{r})\psi(\vec{r}) = E\psi(\vec{r})
`$
There exist, however, very few cases in which this equation is analytically solvable. The rest have to be solved numerically. To achieve this task, I implemented the Runge Kutta method, which can solve first order, linear, ordinary differential equations. It is defined as follows:
```math
y_{n+1}=y_n + h \Sum_{i=1}^s b_i k_i \ \ : \ \ k_i \equiv \frac{dy}{dx}(x_n + c_i h, y_n + h \Sum_{j = 1}^s a_{ij} k_j)
```
The Runge Kutta method is found to be extremely efficient when expanded to the 4th order:
```math
y_{n+1} = y_n + \frac{h}{6}(k_1 + 2k_2 + 2k_3 + k_4)
```
```math
x_{n+1}=x_n + h
```
```math
begin{cases}
k_1 = \frac{dy}{dx}(x_n, y_n) \\
k_2 = \frac{dy}{dx}(x_n + \frac{h}{2}, y_n + h\frac{k_1}{2}) \\
k_3 = \frac{dy}{dx}(x_n + \frac{h}{2}, y_n + h\frac{k_2}{2}) \\
k_1 = \frac{dy}{dx}(x_n+h, y_n+hk_3)
end{cases}
```


This code was extensively tested against programs that are known to work. For example, below is a side-by-side comparison of Desmos and the graphs produced by this code.

<img src="./README_Pictures/1.png"/>

A note on the computation of $`\langle p \rangle`$ is that I relied heavily on the (potentially less common, but very powerful) approach:

```math
\langle p | \psi \rangle = \psi(p)
```
```math
\langle \psi | \hat{p} | \psi \rangle = \langle \hat{p} \rangle = \int_{all \ \ p \ \ space} dp \ \langle \psi | p \rangle \ \ [\hat{p}]_{p\ \ basis} \ \ \langle p | \psi \rangle
```
```math
\langle p | \psi \rangle = \int \langle x | \psi \rangle e^{-ipx/\hbar}dx
```
```math
\langle \hat{p} \rangle = \int dp \ \ (\int \langle \psi | x \rangle e^{ipx/\hbar}dx) \ \ p \ \ (\int \langle x | \psi \rangle e^{-ipx/\hbar}dx)
```

Tests I ran on the particle-in-a-box and quantum-harmonic-oscillator problems (two analytically solvable setups) were in agreeance with calculations ran on Desmos:

<img src="./README_Pictures/2.png" height="300px"/>
<img src="./README_Pictures/3.png"/>

<hr>
Footnotes:

*(That is, everything except for the graphing library, "matplotlibcpp.h". That was cloned from https://github.com/lava/matplotlib-cpp.git)