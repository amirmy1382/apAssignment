import sys
import os
import subprocess

# Path to your input files and target script
input_dir = "input"      # change this to your actual folder
output_dir = "output"
target_script = sys.argv[1]          # change this if the script name is different

# List all files in input_dir (sorted for consistency)
i = 0
suc_runs = 0
for filename in sorted(os.listdir(input_dir)):
    if filename.endswith(".txt"):
        filepath = os.path.join(input_dir, filename)

        # Read input
        with open(filepath, "r") as file:
            input_data = file.read()

        # Run c.py with input_data as stdin
        gpp = ["g++", target_script, "-o", "a.exe","--std=c++20",]
        cmd_result = subprocess.run(
            gpp,
            input=input_data.encode(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )
        exe = "a.exe"
        result = subprocess.run(
            exe,
            input=input_data.encode(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE
        )        
        out = result.stdout.decode().strip()
        
        filename = filename.replace("input","output")
        filepath = os.path.join(output_dir, filename)
        
        with open(filepath, "r") as file:
            output_data = file.read()
            
        if output_data == out:
            suc_runs+=1
            
        if result.stderr:
            print(f"Runtime Error in Test {filename.replace('input','')}")
    i+=1
os.remove(exe)    
print(f"Test Results : {(suc_runs/i)*100}% ")    
