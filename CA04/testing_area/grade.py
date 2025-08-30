import sys
import os
import subprocess
import re
import math


def is_close(a: float, b: float, abs_tol: float = 0.2) -> bool:
    # Handle exact equality
    if a == b:
        return True
        
    # Handle special cases
    if abs(a) == float('inf') or abs(b) == float('inf'):
        return a == b
    
    if math.isnan(a) or math.isnan(b):
        return False
        
    # Use both relative and absolute tolerance
    return abs(a - b) <=  abs_tol
def is_float(text: str) -> bool:
    try:
        float(text)
        return True
    except ValueError:
        return False

def get_test_path(test_num: int, is_input: bool, question_num : int) -> str:
    ques_dir = "Q1_tc/" if question_num==1 else "Q2_tc/"
    
    if is_input:
        sub_dir = "in/" 
        file_name = "input" + str(test_num) + ".txt"
    else: 
        sub_dir = "out/"
        file_name = "output" + str(test_num) + ".txt"
        
    return "testing_area/test_cases/" + ques_dir + sub_dir + file_name

def is_CUT_out_valid(output_data, CUT_outputLines) -> bool:
    matched_lines = 0
    if len(output_data) != len(CUT_outputLines):
        print(f"Expected {len(output_data)} lines but got {len(CUT_outputLines)} lines.")
        print(CUT_outputLines)
        return False
    
    for i in range(len(CUT_outputLines)):
        CUT_line = CUT_outputLines[i]
        expected_line = output_data[i]
        if CUT_line == expected_line:
            matched_lines += 1
            continue
        if is_float(CUT_line) and is_float(expected_line):
            if is_close(float(CUT_line), float(expected_line)):
                matched_lines += 1
                continue
        print(f"line {i}: Expected Output: {expected_line} Actual Output: {CUT_line}")
    if matched_lines == len(output_data):
        return True
# Path to your input files and target script
def test(test_num, exe, ques_num) -> bool:
    input_filepath = get_test_path(test_num, True, ques_num)
    output_filepath = get_test_path(test_num, False, ques_num)

    if not os.path.exists(input_filepath):
        print(f"Error: Input file not found: {input_filepath}")
        sys.exit(1)

    if not os.path.exists(output_filepath):
        print(f"Error: Output file not found: {output_filepath}")
        sys.exit(1)
        
    with open(input_filepath, "r") as file:
        input_data = file.read()
    with open(output_filepath, "r") as file:
        output_data = file.read().split("\n")
          
    result = subprocess.run(
                exe,
                input=input_data.encode(),
                stdout=subprocess.PIPE,
                stderr=subprocess.PIPE,
                shell=True
            ) 
    CUT_outputLines = result.stdout.decode().split("\n")

    if is_CUT_out_valid(output_data, CUT_outputLines):
        print(f"test case {test_num} succeeded")
        return True
        
    else:
        if result.stderr:
            print(f"Runtime Error in Test {test_num}")
            print(result.stderr.decode())
            return False
        else:
            print(f"test case {test_num} failed")
            return False
    

target_script = sys.argv[1]          # change this if the script name is different
ques_num = int(sys.argv[2])          # 1 for Q1, 2 for Q2

# Check if second argument exists
test_num = None
if len(sys.argv) > 3:
    test_num = int(sys.argv[3])

# List all files in input_dir (sorted for consistency)
exe = "a.exe"

gpp = ["g++", target_script, "-o", exe,"--std=c++20"]
cmd_result = subprocess.run(
    gpp,
    stdout=subprocess.PIPE,
    stderr=subprocess.PIPE
)
exe = "./"+exe


suc_runs = 0
i = 1
if test_num is not None:
    if(test(test_num, exe, ques_num)):
        suc_runs+=1
else:
    while os.path.exists(get_test_path(i, True, ques_num)) and os.path.exists(get_test_path(i, False,ques_num)):
        if(test(i, exe, ques_num)):
            suc_runs+=1
        i += 1
print(f"Test Results : {(suc_runs/i)*100}% ")      
# os.remove(exe)    