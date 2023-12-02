from os import walk, system

_, _, filenames = next(walk('Testcases'))

# Run each test x times with different seeds to check for segfaults by chance
# Then, use the last seed for the final output files
TEST_SEED = 1000
ITER_COUNT = 100

for name in filenames:
    if 'input' in name:
        # Only try different seeds for newgame related tests, since other tests need the seed to work properly
        for i in range(TEST_SEED - (ITER_COUNT if 'newGame' in name else 0), TEST_SEED+1):
            cmd = f"./qwirkle {i} < Testcases/{name}"
            # If last test, save output
            if i == TEST_SEED:
                cmd += f" > Testcases/{name.split('.')[0]}.output"
                print(cmd)
            else: # ignore output
                cmd += " > /dev/null"
            return_code = system(cmd)
            # Only catches critical errors. Logical errors can be checked by using Git's diffcheck on staging
            if return_code != 0:
                raise Exception(f"Test case {name} failed with seed {i}")
