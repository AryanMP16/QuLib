There were too many braincells lost on this project.
Written by Aryan*

<h1>QuLib</h1>
<h3>A C++ Quantum Mechanics Library</h3>

<h2>1. Introduction, Features, and Background</h2>
The main purpose of this library is to provide methods for physicists to numerically approach elementary quantum mechanics in a manner that is accurate, user-friendly, and of utmost importance, <strong>efficient</strong>.
<ul>
    <li>Schrodinger's equation solver using 4th order Runge Kutta methods for paired ordinary differential equations</li>
    <li>Expectation value computations</li>
    <li>Mathematical foundation: linear algebra and complex number implementations</li>
</ul>

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