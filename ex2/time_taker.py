import subprocess

# Specify the path to your algorithm executable
ALGORITHM_EXECUTABLE = "./your_algorithm_executable"

# Specify the range of max heights you want to test
MIN_HEIGHT = 1
MAX_HEIGHT = 10

# Output file to store results
OUTPUT_FILE = "results.txt"

# Loop through max heights
with open(OUTPUT_FILE, "w") as output_file:
    for height in range(MIN_HEIGHT, MAX_HEIGHT + 1):
        print(f"Running algorithm with max height: {height}")
        
        # Run your algorithm with the current max height
        # Redirect the standard output to a file
        try:
            result = subprocess.run([ALGORITHM_EXECUTABLE, str(height)], capture_output=True, text=True, timeout=60)
            
            # Write the results to the output file
            output_file.write(f"{height} {result.stdout}")
            
        except subprocess.TimeoutExpired:
            # Handle cases where the algorithm takes too long to run
            print(f"Algorithm with max height {height} timed out.")
            output_file.write(f"{height} TIMEOUT\n")

print("Script completed")
