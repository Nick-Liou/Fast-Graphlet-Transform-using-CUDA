# Fast-Graphlet-Transform-using-CUDA

This is a project for the class Parallel-and-Distributed-System that attempts to accelerate [FGLT](https://github.com/fcdimitr/fglt) with CUDA. 
FGLT is a C/C++ multi-threading library for Fast Graphlet Transform of large, sparse, undirected networks/graphs.

Only the first $σ_0,σ_1,σ_2,σ_3,σ_4$ are calculated.

# Compile 

After downloading the files go to the folder "Code" and use: ```make```.

If you do not have "make" isntalled you can compile the program with:

```
nvcc    -O3  main.cu    load_stuff.c  sparse_mult.cu  mmio.c csx.c -o CUDA_nick.exe
```


# Run the program

To run the program you can use:

```
make run
```
or:
```
./CUDA_nick.exe
```

