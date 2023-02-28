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

# Data

The folder '''Data''' has some small matrices that can be used to test the program. 
You can add the 3 'missing' graphs in the folder for the program to be able to find them from the menu.
When running the program there is an option to input the relative path to a file (so the above step can be avoided).
Also you could modify the variable '''file_relative_path''' inside '''main.cu'''.
Finaly the program can take a command line argument an integer to choose an option from the menu that would show up normaly.



