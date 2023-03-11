#! /bin/bash

# experiment 1: finding the best d, l, v
k=10
for d in 1 2 3; do
	for l in 1 3 5 7 9 10; do
		for v in 1 3 4 6 7 9 10; do
			output="./experiment/hyperparameter/10_patients/${k}_${d}_${l}_${v}.csv"
			echo "k: $k, d: $d, l: $l, v: $v"
			echo "Output: $output"
			start=`date +%s.%N`
			./build/nutriomics_main -n /Users/nyxfer/Docu/github/cse282-nutriomics-project-1/res/nims.csv -p /Users/nyxfer/Docu/github/cse282-nutriomics-project-1/res/patient_inputs_10.csv -k $k -d $d -l $l -v $v -o $output -a proposed
			end=`date +%s.%N`

			runtime=$( echo "$end - $start" | bc -l )
			echo "Runtime: $runtime"
			echo "$k,$d,$l,$v,$runtime" >> "./experiment/hyperparameter/runtime_p10.csv"
		done
	done
done

# experiment 2: comparison with brute force and greedy
k=3
p=10
output="./experiment/comparison/p10_k3/bruteforce.csv"
start=`date +%s.%N`
./build/nutriomics_main -n /Users/nyxfer/Docu/github/cse282-nutriomics-project-1/res/nims.csv -p /Users/nyxfer/Docu/github/cse282-nutriomics-project-1/res/patient_inputs.csv -o $output -k $k -a bruteforce 
end=`date +%s.%N` 
runtime=$( echo "$end - $start" | bc -l )
echo "$runtime" >> "./experiment/comparison/p10_k3/run_time_bruteforce.csv"

for d in 1 2; do
	for l in 1 10; do
		for v in 1 10; do
			output="./experiment/comparison/p10_k3/${k}_${d}_${l}_${v}.csv"
			echo "k: $k, d: $d, l: $l, v: $v"
			echo "Output: $output"
			start=`date +%s.%N`
			./build/nutriomics_main -n /Users/nyxfer/Docu/github/cse282-nutriomics-project-1/res/nims.csv -p /Users/nyxfer/Docu/github/cse282-nutriomics-project-1/res/patient_inputs.csv -k $k -d $d -l $l -v $v -o $output -a proposed
			end=`date +%s.%N`

			runtime=$( echo "$end - $start" | bc -l )
			echo "Runtime: $runtime"
			echo "$k,$d,$l,$v,$runtime" >> "./experiment/runtime_p10.csv"
		done
	done
done