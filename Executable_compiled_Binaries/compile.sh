& "C:\MinGW\bin\g++.exe" -std=c++11 -I eigen Main_eigensolver.cpp -o runme.exe 
.\runme.exe (Windows/powershell mothode) 

g++ -std=c++17 -I /usr/include/eigen3 Main_eigensolver.cpp -o new_runme ( ubuntu)

g++ -std=c++17 -I eigen-3.4.0/ Hamiltonian_Eigensolvers/Hamiltonian_FDM_Build.cpp -o generate_data ( ubuntu)

g++ -std=c++17 -I eigen-3.4.0 MAIN_CPP_CODES/Main.cpp $(/snap/bin/root-config --cflags --libs) -o oscillator
g++ -std=c++17 -I eigen-3.4.0 MAIN_CPP_CODES/what you wanna run file $(/snap/bin/root-config --cflags --libs) -o oscillator
root -l -b -q MAIN_CPP_CODES/plot_wave_and_density.C ( for .C files )

root -l -b -q PHASE_SPACE_stuff/what you wanna run file

g++ -std=c++17 -I eigen-3.4.0 PHASE_SPACE_stuff/classical_phase_space.cpp $(/snap/bin/root-config --cflags --libs) -o phase