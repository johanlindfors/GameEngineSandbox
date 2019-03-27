cmake -E remove_directory build/osx
cmake -E make_directory build/osx
cmake -E chdir build/osx cmake ../..
