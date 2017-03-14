# muse : a promise based test system

All docs in muse/docs folder.

Build and test muse needs cmake and gtest.

- install cmake
- download [gtest](https://github.com/google/googletest)
- build gtest, generate the `libgtest.a`
- mkdir `lib` under gtest root folder, copy `libgtest.a` to `lib`
- modify the muse/project/build.sh, set the `gtest_home_path` to your gtest folder path.
- run `build.sh` to build and test muse
