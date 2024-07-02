There were too many braincells lost on this project.
Written by Aryan*

This code was extensively tested against programs that are known to work. For example, below is a side-by-side comparison of Desmos and the graphs produced by this code.

<img src="./README_Pictures/1.png"/>

A note on the computation of $`\langle p \rangle`$ is that I relied heavily on the (potentially less common, but very powerful) approach:

```math
\langle p | \psi \rangle = \psi(p)
```
```math
\langle \psi | \hat{p} | \psi \rangle = \langle \hat{p} \rangle = \int_{all \ \ p \ \ space} dp \ \psi^*(p) \ \ [\hat{p}]_{p\ \ basis} \ \ \psi(p)
```
Given $`\langle x | \psi \rangle`$:
```math
\langle p | \psi \rangle = \int \langle x | \psi \rangle e^{-ipx/\hbar}dx
```
```math
\langle \hat{p} \rangle = \int dp \ \ (\int \langle x | \psi \rangle e^{-ipx/\hbar}dx)^* \ \ p \ \ \int \langle x | \psi \rangle e^{-ipx/\hbar}dx
```

Tests I ran on the particle-in-a-box and quantum-harmonic-oscillator problems (two analytically solvable setups) were in agreeance with calculations ran on Desmos:
<img src="./README_Pictures/2.png"/>
<img src="./README_Pictures/3.png"/>

<hr>
Footnotes:

*(That is, everything except for the graphing library, "matplotlibcpp.h". That was cloned from https://github.com/lava/matplotlib-cpp.git)