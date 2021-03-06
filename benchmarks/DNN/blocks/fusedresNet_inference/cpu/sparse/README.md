The files in this folder are organized as follows:

    General
        clean.sh : remove some useless files.
        compile_and_run_mkldnn.sh : compile mkldnn code and run it.
        configure.h: define size of input matrices.

    Tiramisu
        fused_sparse_resnet_block_generator.cpp: Tiramisu code generator.

    Wrapper
        fused_sparse_resnet_block_wrapper.cpp: wrapped file that calls the code generated by Tiramisu.

    Intel MKLDNN
        fused_resnet_block_generator_mkldnn.cpp: code that calls Intel MKL DNN ResNet block.

To run this benchmark:

    At the directory build/benchmarks/DNN/blocks/fusedresNet_inference/cpu/sparse execute
	    make

    fused_sparse_resnet_block_wrapper executable will be created in the current directory.

    To compare the result of tiramisu with MKL DNN execute :
        ./compile_and_run_mkldnn.sh
    then
        ./fused_sparse_resnet_block_wrapper

    execution results could be found in the text files :
        mkl_result.txt (Intel MKL-DNN)
        tiramisu_result.txt
