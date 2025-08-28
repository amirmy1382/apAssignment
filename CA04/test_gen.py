import random
import os
import re
import subprocess

target_script = "Q1/Q1.cpp"   
input_folder="test_cases/Q1_tc/in"
output_folder="test_cases/Q1_tc/out"

def get_next_map_index(folder):
    """Find the next map number by scanning existing *.txt files in the folder."""
    max_index = 0
    if os.path.exists(folder):
        for filename in os.listdir(folder):
            match = re.match(r"([A-Za-z]+)(\d+)\.txt$", filename)
            if match:
                max_index = max(max_index, int(match.group(2)))
    return max_index + 1

start_index = get_next_map_index(input_folder)

exe = "a.exe"  
gpp = ["g++", target_script, "-o", exe,"--std=c++20"]
cmd_result = subprocess.run(
    gpp,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE
)
exe = "./"+exe    

for filename in sorted(os.listdir(input_folder)):
    if (filename.endswith(".txt")):

        file_path = os.path.join(input_folder, filename)
    
        # generated output:
        
        with open(file_path, "r") as file:
            input_data = file.read()
            
        
        result = subprocess.run(
            exe,
            input=input_data.encode(),
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            shell=True
        )        
        
        out = result.stdout.decode().strip()

        filename_out = filename.replace("input","output")
        file_path = os.path.join(output_folder, filename_out)
        with open(file_path, "w") as f:
            f.write(result.stdout.decode().strip())
                        
        if result.stderr:
            print("===== Errors =====")
            print(filename)
            print(result.stderr.decode().strip())
                
        print(f"test {filename.replace('input','').replace('.txt','')} generated")


os.remove(exe)    

