The files in this folder are organized as follows:

    General
        clean.sh : remove some useless files.
        compile_and_run_mkldnn.sh : compile MKL-DNN code and run it.
        compile_and_run_mkl.sh : compile MKL code and run it. 
        configure.h: define some configuration constants.

    Tiramisu
        densenet_block_generator_tiramisu.cpp: Tiramisu code generator.

    Wrapper
        wrapper_nn_block.cpp: wrapper file that calls the code generated by Tiramisu.

    Intel MKL-DNN
        densenet_block_generator_mkldnn.cpp : code that calls Intel MKL-DNN DenseNet block.

    Intel MKL
        densenet_block_generator_mkl.c: code that calls Intel MKL DenseNet block. 

To run this benchmark:

    At the directory build/benchmarks/DNN/blocks/DenseNetBlock execute 
	    make 

    wrapper_nn_block_densenet executable will be created in the current directory. 

    To compare the result of tiramisu with MKL-DNN execute :
        ./compile_and_run_mkldnn.sh
    then 
        ./wrapper_nn_block_densenet
    
    To compare the result of tiramisu with MKL execute :
        ./compile_and_run_mkl.sh
    then 
        ./wrapper_nn_block_densenet
    
    execution results could be found in the text files : 
        mkl_result.txt (same for Intel MKL and Intel MKL-DNN)
        tiramisu_result.txt