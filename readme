### Features

##### 1. Thresholding

    const mfl::Threshold thresh(3 * std::numeric_limits<double>::epsilon(), 0.3d, 127); // create threshold object
    const auto neededParam1 = 3.14d; // expected value 1
    const auto neededParam2 = 180; // expected value 2
    const auto neededParam3 = 255; // expected value 3
    const auto realParam1 = 3.16f; // get value 1
    const auto realParam2 = 180ul; // get value 2
    const auto realParam3 = 200ll; // get value 3
    // check if all constraints were satisfied between the expected and real values
    const bool good = thresh(
        neededParam1, neededParam2, neededParam3, 
        realParam1, realParam2, realParam3
    );
    // soon
    // const mfl::Threshold threshFuture(
    //  neededParam1, 3 * std::numeric_limits<double>::epsilon(),
    //  neededParam2, 0.3d,
    //  neededParam3, 127
    // );
    // const bool goodFuture = threshFuture(realParam1, realParam2, realParam3);

### Build

##### Cmake

###### Building this library

    mkdir build/
    cd build/
    cmake -DCMAKE_BUILD_TYPE=Release ../
    sudo make install

###### Using in your project

Include ./CMakeLists.txt to your CMakeLists.txt

###### Options

-DMFL_BUILD_EXAMPLES=ON for building examples

-DMFL_BUILD_TESTS=ON for building tests

### Reference & Documentation (to be done)
