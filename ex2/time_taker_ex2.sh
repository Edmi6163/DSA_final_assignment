#!/bin/bash

# Specify the path to your algorithm executable
ALGORITHM_EXECUTABLE="./build/main_ex2 ../data/dictionary.txt ../data/correctme.txt"

# Specify the range of max heights you want to test
MIN_HEIGHT=15
MAX_HEIGHT=110

# Counter for segmentation faults
SEG_FAULT_COUNT=0

# Loop through max heights
for ((height = $MIN_HEIGHT; height <= $MAX_HEIGHT; height++)); do
    # Run your algorithm with the current max height and measure the time
    $ALGORITHM_EXECUTABLE $height

    # Check the exit status of the last command
    if [ $? -ne 0 ]; then
        echo "Segmentation fault detected for max height: $height"
        ((SEG_FAULT_COUNT++))
    fi
done

echo "Script completed"
echo "Number of segmentation faults: $SEG_FAULT_COUNT"

