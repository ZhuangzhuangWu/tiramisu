/**
  The goal of this tutorial is to implement in Tiramisu a code that is
  equivalent to the following

  for (int i = 0; i < 10; i++)
      buf0[i] = 3 + 4;

  Every Tiramisu program needs to include the header file tiramisu/tiramisu.h
  which defines classes for declaring and compiling Tiramisu expressions.

  Tiramisu is a code generator, therefore the goal of a Tiramisu program is to
  generate code.  The generated code is supposed to be called from another
  program (the user program).

  A Tiramisu program is structures as follows:
	- It starts with a call to initialize the Tiramisu compiler.  The name of the
	function to be generated is specified during this initialization.
	- The user then declares the algorithm: Tiramisu expressions.
	- The user then specifies how the algorithm should be optimized
	using scheduling and data mapping commands.
	- The user then calls the codegen() function which generates code.
	It compiles the Tiramisu program, generates the optimized program
	in an object file.

  The user can then call the function declared in the generated object file
  from any place in his program.

*/
#include <tiramisu/tiramisu.h>

using namespace tiramisu;

int main(int argc, char **argv)
{
    // Set default tiramisu options.
    tiramisu::init();

    // Declare a function called "tut_01".
    // A function in tiramisu is the equivalent of a function in C.
    // It can have input and output arguments.  These arguments are
    // represented as buffers and are declared later in the tutorial.
    function tut_01("tut_01");


    // -------------------------------------------------------
    // Layer I
    // -------------------------------------------------------

    var i("i");

    // Declare a computation within tut_01.
    // To declare a computation, you need to provide:
    // (1) an ISL set representing the iteration space of the computation.
    // Tiramisu uses the ISL syntax to represent sets and maps.  The ISL syntax
    // is described in http://barvinok.gforge.inria.fr/barvinok.pdf (Section
    // 1.2.1 for sets and iteration domains, and 1.2.2 for maps and access
    // relations),
    // (2) a tiramisu expression: this is the expression that will be computed
    // by the computation.
    // (3) the function in which the computation will be declared.
    computation S0("{S0[i]: 0<=i<10}", expr(3) + expr(4), true, p_uint8, &tut_01);


    // -------------------------------------------------------
    // Layer II
    // -------------------------------------------------------

    // Set the schedule of each computation.
    // Here we are parallelizing the loop.
    S0.parallelize(i);


    // -------------------------------------------------------
    // Layer III
    // -------------------------------------------------------

    // Create a buffer buf0.  This buffer is supposed to be allocated outside
    // the function "tut_01" and passed to it as an argument.
    // (actually any buffer of type a_output or a_input should be allocated
    // by the caller, in contrast to buffers of type a_temporary which are
    // allocated automatically by the Tiramisu runtime within the callee
    // and should not be passed as arguments to the function).
    buffer buf0("buf0", {expr(10)}, p_uint8, a_output, &tut_01);

    // Map the computations to a buffer (i.e. where each computation
    // should be stored in the buffer).
    // This mapping will be updated automatically when the schedule
    // is applied. To disable automatic data mapping updates use
    // global::set_auto_data_mapping(false).
    S0.set_access("{S0[i]->buf0[i]}");


    // -------------------------------------------------------
    // Code Generation
    // -------------------------------------------------------

    // Generate code and compile it to an object file.  Two arguments need
    // to be passed to the code generator:
    //	    - The arguments (buffers) t passed to the generated function.
    //	    - The name of the object file to be generated.
    tut_01.codegen({&buf0}, "build/generated_fct_users_tutorial_01.o");

    return 0;
}
