import sys
import os
import subprocess
import re

# Path to your input files and target script
input_dir = sys.argv[2]      # change this to your actual folder
output_dir = sys.argv[3]
target_script = sys.argv[1]          # change this if the script name is different

# print(input_dir,output_dir,target_script)
# List all files in input_dir (sorted for consistency)
exe = "a.exe"

gpp = ["g++", target_script, "-o", exe,"--std=c++20"]
cmd_result = subprocess.run(
    gpp,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE
)
exe = "./"+exe
        
i = 0
suc_runs = 0
for filename in sorted(os.listdir(input_dir)):
    if (filename.endswith(".in") or filename.endswith(".dpp")):
        filepath = os.path.join(input_dir, filename)

        # Read input
        with open(filepath, "r") as file:
            input_data = file.read()

        # Run c.py with input_data as stdin
        result = subprocess.run(
            exe,
            input=input_data.encode(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            shell=True
        )        
        
        out = result.stdout.decode().strip()
        print(out)
        filename = re.sub(r"\.\w+", ".out", filename)

        filepath = os.path.join(output_dir, filename)
        
        with open(filepath, "r") as file:
            output_data = file.read()
            
        if output_data == out:
            suc_runs+=1
            print(f"test case {i} succeeded")
            i+=1
            continue
        if result.stderr:
            print(f"Runtime Error in Test {filename.replace('input','')}")
            i+=1
            continue
        i+=1 
        
os.remove(exe)    
print(f"Test Results : {(suc_runs/i)*100}% ")    
