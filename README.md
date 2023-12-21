# BehaviorTreeTuto
Simple Tutorial of Behaviortree.CPP in VC++ environment

## Dependency preparation
Though I have been using BehaviorTree in Linux environment for a while, today I tried for the first time to run it on Windows. 
So I git clone firstly the [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP) repo, and build it as per instructions in its official doc (except for the last step, I added `--config` option):
```
mkdir build; cd build
conan install ../BehaviorTree.CPP --output-folder=. --build=missing
cmake ../BehaviorTree.CPP -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake"
cmake --build . --config Release --parallel
```
I got `behaviortree_cpp.lib` and `behaviortree_cpp.dll` when this step finished successfully.


## Run the project
Open this project in Visual Studio, and run it by `CTRL+F5`. If there is no error, one should see output as
```
----------------
root
   AlwaysSuccess
   MySubTree
      test_sequence
         SaySomething
         SayGreat
   ThinkWhatToSay
   SaySomething
----------------
BehaviorTree.CPP works!!
BehaviorTree.CPP Rocks!!
The answer is 42

```
If any error occurs, please check firstly the presence of `behaviortree_cpp.dll` in the output folder (where the `.exe` file is located). If not, please copy it from `.\behaviortree_cpp\` to target folder. If error still occurs, please check if the dependency header path and library path are well configured.

### Reference

- [BehaviorTree.CPP](https://github.com/BehaviorTree/BehaviorTree.CPP)

- [official sample](https://github.com/BehaviorTree/btcpp_sample)