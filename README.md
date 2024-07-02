There were too many braincells lost on this project.
Written by Aryan*

This code was extensively tested against programs that are known to work. For example, below is a side-by-side comparison of Desmos and the graphs produced by this code.

![alt text](./README_Pictures/Annotation%202024-06-29%20225632.png)

A note on the computation of $`\langle p \rangle`$ is that I relied heavily on the (potentially less common, but very powerful) approach:

```math
SE = \frac{\sigma}{\sqrt{n}}
```

*(That is, everything except for the graphing library, "matplotlibcpp.h". That was cloned from https://github.com/lava/matplotlib-cpp.git)