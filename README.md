# CLAS12_analysis
Starter for CLAS12 analysis using hipo C++ library and multithread

## To build it 
First you have to build hipo library

### Dependencies
Click each for details
<details>
<summary>🔸 Meson and Ninja</summary>

> - Meson: <https://mesonbuild.com/>
> - Ninja: <https://ninja-build.org/>
>
> Likely available in your package manager (`apt`, `brew`, `dnf`, _etc_.),
> but the versions may be too old, in which case, use `pip` (`python -m pip install meson ninja`)
</details>

Use standard [Meson commands](https://mesonbuild.com/Quick-guide.html) to build HIPO.

For example, run the following command from the hipo source code directory:
```bash
meson setup build --prefix=`pwd`/install
```

And then, the build directory is where you can compile, test, and more:
```bash
cd build
ninja           # compiles
ninja install   # installs to your specified prefix (../install/, in the example)
```

You can check more detail instructions in the hipo github repository



