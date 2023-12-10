#!/bin/bash

# Specify the path to your algorithm executable
ALGORITHM_EXECUTABLE="./build/main_ex1 ../data/records.csv ../data/sorted.csv"

# Specify the range of max heights you want to test
MIN_K_VALUE=1
MAX_K_VALUE=300
INCREMENT=100
FIELD=1

# Counter for segmentation faults
SEG_FAULT_COUNT=0

for ((k = $MIN_K_VALUE; k <= $MAX_K_VALUE; k++)); do
    $ALGORITHM_EXECUTABLE $k $FIELD

    # Increment FIELD value every 250 runs
    if [ $((k % INCREMENT)) -eq 0 ]; then
        echo "Incrementing FIELD value"
        ((FIELD++))
        k = 1
    fi

    # Display the temporary output in the terminal
    echo "$temp_output"

    # Check the exit status of the last command
    if [ $? -ne 0 ]; then
        echo "Error displaying output for k=$k, field=$FIELD"
        ((SEG_FAULT_COUNT++))
    fi
done
