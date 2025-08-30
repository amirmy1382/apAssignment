import random
import os
import re
import subprocess

target_script = "Q1/Q1.cpp"   
input_folder="testing_area/test_cases/Q1_tc/in"
output_folder="testing_area/test_cases/Q1_tc/out"


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
        
        out = result.stdout.decode()
        filename_out = filename.replace("input","output")
        file_path = os.path.join(output_folder, filename_out)
        with open(file_path, "w") as f:
            f.write(out)
                        
        if result.stderr:
            print("===== Errors =====")
            print(filename)
            print(out)
                
        print(f"test {filename.replace('input','').replace('.txt','')} generated")
